|  #   | Category |        Problem        | Difficulty |         Comments         |                      Flag                       |
| :--: | :------: | :-------------------: | :--------: | :----------------------: | :---------------------------------------------: |
|      |   reverse | DebuggeeInDebugger | hard | | `ZCTF{2o25)34)833F#4(<}` |

---

## DebuggeeInDebugger

这道题将一个校验程序嵌入修改过的 Turbo Debugger，并利用异常和单步机制逐条解密指令。解题的关键是展开代码保护，恢复内部真正的校验逻辑。

首先检查文件类型，发现需要使用 16 位 x86 模式，考虑段地址和 DOS 中断。搜索文件内的 `MZ`，在偏移 `0x38EC` 找到一个有效的内嵌 DOS EXE。根据该 EXE 的头部计算，其长度为 `0x2510`，即 9488 字节，可以直接提取：

```python
from pathlib import Path

raw = Path('did.exe').read_bytes()
Path('inner.exe').write_bytes(raw[0x38EC:0x38EC + 0x2510])
```

内嵌程序的头部长度为 `0x200`，所以其代码段在原文件中的起点为 `0x3AEC`。数据段相对代码段的偏移是 `0x1DA0`，即原文件偏移 `0x588C`。下文代码地址均表示内嵌程序的 **CS 相对偏移**，数据地址则写为 `DS:偏移`。

几个关键位置如下：

| 位置 | 用途 |
|---|---|
| `CS:07BA` | 主函数 |
| `CS:0673` | 输入校验函数 |
| `CS:0357` | 非法指令异常处理函数 |
| `CS:03DF` | 断点异常处理函数 |
| `CS:046E` | 单步异常处理函数 |
| `CS:02DB` | CRC 计算函数，初始状态下受保护 |
| `DS:01B5` | 22 字节比较目标 |
| `DS:01CB` | 256 字节 AES S-box |

主函数注册了 `INT 1`、`INT 3`、`INT 6` 和 `INT 8` 的处理函数，然后读取输入并调用 `CS:0673`。校验返回值为 0 时打印 `Incorrect`，非 0 时打印 `Correct`。

直接反汇编校验函数，会看到 `INT3` 后出现大量不合理指令。这些字节经过加密，需要先分析中断处理函数。

外层加载器挂钩了 DOS 的 `INT 21h`，拦截文件读取和程序加载等操作，使内嵌程序能够作为被调试对象加载。此外，它增加了一个自定义调用：

```asm
mov ah, 0DBh
int 21h
```

这个调用返回一个远函数指针，内部程序用它访问外层 Turbo Debugger 的反汇编功能，取得指令长度。保护代码需要知道每条指令有多少字节，才能准确地加密或解密整条指令，这正是题名 DebuggeeInDebugger 的含义。

第一层保护对每条指令的**首字节取负**：

```python
plain_opcode = (-encrypted_opcode) & 0xff
```

例如 `F0 70` 在该执行环境下触发非法指令异常，处理函数跳过标记，将下一字节 `0x70` 取负为 `0x90`，即 `NOP`，同时打开 Trap Flag。之后每执行一条指令，单步处理函数就将上一条的首字节恢复，并解密下一条的首字节。

由于取负两次会恢复原值，这个过程可以同时用于解密和重新加密。离线还原时，只需解密首字节，用反汇编器确定指令长度，再移动到下一条指令。

展开这层后，可以读出第二层保护使用的 CRC 算法：

- 多项式：`0x04C11DB7`。
- 初始值：`0xFFFFFFFF`。
- 按高位优先处理数据，不进行位反射。
- 最终结果异或 `0xFFFFFFFF`。

它与直接调用 `zlib.crc32` 的参数约定不同，不能直接替换。对位于 `CS:p` 的受保护指令，CRC 的输入范围是：

```python
original_code[0x357:p]
```

设结果为 `c`，第二层使用以下 16 字节异或密钥，四个整数均按小端序排列：

```python
key = pack('<IIII', c, c ^ 0xffffffff, rol32(c, 5), rol32(c, 7))
```

将当前位置的密文字节与这个密钥异或，就能还原一条指令。反汇编得到指令长度后，继续处理下一条。校验函数的受保护区间为 `[0x698, 0x751)`。

这里要始终使用**未修改的原始代码**计算 CRC，而不是已经解密了一部分的副本。运行时异常处理函数会恢复已执行指令的密文；使用不断变化的离线副本会导致后续密钥计算错误。

还原出来的指令已经具有清晰的校验含义，例如：

```asm
0699: xor si, si
069B: mov di, [bp-8]       ; 输入长度
069E: dec di              ; 指向最后一个字符
...
06CF: add bx, 42h
06D2: and bx, 0FFh
06D6: mov al, [bx+1CBh]   ; S-box 查表
...
070C: add bx, -57h        ; 低 8 位等价于加 A9h
070F: and bx, 0FFh
0713: mov al, [bx+1CBh]
...
0732: cmp al, [si+1B5h]   ; 比较目标字节
073B: cmp si, 16h         ; 比较 22 字节
```

由此可以确认，最终校验使用了 AES 的 S-box，但没有执行完整的 AES 加密流程。

设输入长度为 `n`，每轮从两端各取一个字符：

```python
a = input[i]
b = input[n - 1 - i]
```

将它们的高低半字节交叉组合，再加常量、查 S-box：

```python
x = ((b & 0x0f) << 4) | (a >> 4)
y = (b & 0xf0) | (a & 0x0f)

output[2*i]     = sbox[(x + 0x42) & 0xff]
output[2*i + 1] = sbox[(y + 0xa9) & 0xff]
```

程序先要求输入长度为偶数，之后比较输出的前 22 字节。它没有直接要求输入长度必须为 22；按 22 字节构造答案即可恢复本题 flag。

比较目标位于原文件 `0x5A41`，内容为：

```text
f0 26 6f 86 c6 bd 44 9e b6 48 06 e9
bc 9b 9d b9 a6 1d 48 b5 97 86
```

S-box 是一个排列，因此可以构造逆表。对每两个目标字节，先逆查表、减去常量，再拼回两个输入字符：

```python
from pathlib import Path

raw = Path('did.exe').read_bytes()
target = raw[0x5A41:0x5A57]
sbox = raw[0x5A57:0x5B57]
inverse = bytes(sbox.index(i) for i in range(256))

flag = bytearray(22)
for i in range(11):
    x = (inverse[target[2*i]] - 0x42) & 0xff
    y = (inverse[target[2*i + 1]] - 0xa9) & 0xff
    flag[i] = ((x & 0x0f) << 4) | (y & 0x0f)
    flag[21-i] = (y & 0xf0) | (x >> 4)

print(flag.decode())
```

输出：

```text
ZCTF{2o25)34)833F#4(<}
```

为了验证还原过程，使用 Unicorn 的 16 位 x86 模式执行解密后的 `CS:0673` 校验函数。只将保护区入口与出口的两个 `INT3` 替换为 `NOP`；输入处理、查表运算和成功失败分支保持原样。

候选输入返回 `AX = 1`，且生成的 22 字节与目标完全一致；把最后一个字符改为 `!` 后返回 `AX = 0`。随后实际提交也确认了 flag 正确。

完整的提取、指令解密、flag 恢复和模拟验证代码见同目录的 `solve.py`。在项目根目录执行：

```sh
python3 -m venv /tmp/did-wp-venv
/tmp/did-wp-venv/bin/pip install capstone unicorn
/tmp/did-wp-venv/bin/python did_analysis/solve.py
```

当前工作环境已有依赖，也可以直接执行：

```sh
python3 did_analysis/solve.py
```

预期输出：

```text
Flag: ZCTF{2o25)34)833F#4(<}
Target: f0266f86c6bd449eb64806e9bc9b9db9a61d48b59786
Native checker: AX = 1 (Correct branch)
Modified input: AX = 0 (Incorrect branch)
```

脚本同时导出内嵌程序 `inner.exe`、部分代码还原后的加载映像 `decoded.bin`，以及校验函数反汇编 `checker.asm`。`decoded.bin` 用于分析和模拟，不是完整修复后可直接运行的 DOS EXE。

---

以下是我的赛时 WriteUp（AI 味很重，当时还在用网页版 Gemini，但 AI 的威力已经可见一二）：

!pdf[../../../assets/pdf/ZJUCTF-2025-writeup.pdf]

