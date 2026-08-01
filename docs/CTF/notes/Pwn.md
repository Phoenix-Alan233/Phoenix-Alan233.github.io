# Pwn

$$
\text{Pwn = Find the bugs + Exploit them}
$$

## 现成轮子

- IDA，这个在逆向中有讲
- **pwntools**，Pwn 工具库，提供完整的利用开发工具链
    - 安装方式：`pip install pwntools`
    - 使用方式：在 python 中 `from pwn import *`
    - 官方手册：https://docs.pwntools.com/en/stable/
    - 官方仓库：https://github.com/Gallopsled/pwntools/
- **patchelf**，给 ELF 打补丁，指向新的 loader 和 libc
    - 使用方式：`patchelf --set-interpreter [file_name] --set-rpath . [file_name]`
- **pwndbg**，专为 Pwn 和 Reverse 设计的 gdb 插件
    - 安装方式（脚本会自动修改 `~/.gdbinit` 以加载插件）：
        ```bash
        git clone https://github.com/pwndbg/pwndbg
        cd pwndbg && ./setup.sh
        ```
    - 使用方式：`gdb [file_name]`
    - 官方仓库：https://github.com/pwndbg/pwndbg/
- **QEMU**，强大的机器模拟器，支持 x86、arm、MIPS、RISC-V 等指令集架构
- **seccomp-tools**，查看沙箱拦截规则
    - 安装方式：
        ```bash
        sudo apt install gcc ruby-dev # 安装必要的依赖
        sudo gem install seccomp-tools
        ```
    - 使用方式：` seccomp-tools dump [file_name]`
    - 官方仓库：https://github.com/david942j/seccomp-tools/
- 跨架构的交叉编译链，如 `gcc-{aarch64,mips,riscv64}-linux-gnu binutils-{aarch64,mips,riscv64}-linux-gnu`