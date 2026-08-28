# Cypher

!!! tip
    Steam 上的一款“密码学”小游戏，极简风，难度适中，较为硬核。

    底下贴一小部分题，主要是存档一下编写的代码。

![](https://pica.zhimg.com/70/v2-94342bfd0d8b055a52330536ff24c5ee_1440w.avis?source=172ae18b&biz_tag=Post)

## Chapter 3. Monoalphabetic Substitution

### PUZZLE 3-1

```py
plain_text = "THSWQD THZ RBXP GWXP HG XL ZWRNBRHK UTPQ WQ KBQZBQ, W THZ SWRWGPZ GTP IOWGWRT XMRPMX, HQZ XHZP RPHOFT HXBQD GTP IBBVR HQZ XHNR WQ GTP KWIOHOL OPDHOZWQD GOHQRLKSHQWH; WG THZ RGOMFV XP GTHG RBXP ABOPVQBUKPZDP BA GTP FBMQGOL FBMKZ THOZKL AHWK GB THSP RBXP WXNBOGHQFP WQ ZPHKWQD UWGT H QBIKPXHQ BA GTHG FBMQGOL."
trans_table = {
    'A': 'f',
    'B': 'o',
    'C': '?',
    'D': 'g',
    'E': '?',
    'F': 'c',
    'G': 't',
    'H': 'a',
    'I': 'b',
    'J': '?',
    'K': 'l',
    'L': 'y',
    'M': 'u',
    'N': 'p',
    'O': 'r',
    'P': 'e',
    'Q': 'n',
    'R': 's',
    'S': 'v',
    'T': 'h',
    'U': 'w',
    'V': 'k',
    'W': 'i',
    'X': 'm',
    'Y': '?',
    'Z': 'd',
}

for c in plain_text:
    print(trans_table[c] if c.isalpha() else c, end = '')
print()
```

### PUZZLE 3-2

[Word Frequency Analysis](https://quipqiup.com/).

```
SOON AFTER MY ARRIVAL IN THE HOVEL I DISCOVERED SOME PAPERS IN THE POCKET OF THE DRESS WHICH I HAD TAKEN FROM YOUR LABORATORY. AT FIRST I HAD NEGLECTED THEM, BUT NOW THAT I WAS ABLE TO DECIPHER THE CHARACTERS IN WHICH THEY WERE WRITTEN, I BEGAN TO STUDY THEM WITH DILIGENCE.
```

### PUZZLE 3-3

Same as above.

```
There is ever a flaw, however, in the best laid of human plans, and the murderers of John Openshaw were never to receive the orange pips which would show them that another, as cunning and as resolute as themselves, was upon their track. Very long and very severe were the equinoctial gales that year. We waited long for news of the lone star of savannah but none ever reached us.
```

### PUZZLE 3-4

```
dear livesey as i do not know whether you are at the hall or still in london i send this in double to both places the ship is bought and fitted she lies at anchor ready for sea you never imagined a sweeter schooner a child might sail her two hundred tons name hispaniola
```

## Chapter 4. Polyalphabetic Substitution

Vigenere Cipher.

### PUZZLE 4-1

Decrypt it.

```py
plain_text = "ZTVGLKDBGLRUHABTUOZ"
key = "FLASH"

for i, c in enumerate(plain_text):
    key_c = key[i % len(key)]
    cipher_c = chr((ord(c) - 65 - ord(key_c) + 64) % 26 + 65)
    print(cipher_c, end='')
print()
```

### PUZZLE 4-2

It's easy to guess $\text{len}(\text{key})=3$.

```py
plain_text = "JCWSVLIVLVGSJJFJCWCVL"
key = "JEH"

for i, c in enumerate(plain_text):
    key_c = key[i % len(key)]
    cipher_c = chr((ord(c) - 65 + ord(key_c) - 64) % 26 + 65)
    print(cipher_c, end='')
print()
```

`MAT`.

### PUZZLE 4-3

[Vigenere Cipher Cracker](https://www.guballa.de/vigenere-solver). Guess $\text{len}(\text{key})=3$.

```
ITHINKTHATICANHELPYOUTOPASSANHOURINANINTERESTINGANDPROFITABLEMANNERSAIDHOLMESDRAWINGHISCHAIRUPTOTHETABLEIAMFAIRLYFAMILIARWITHALLFORMSOFSECRETWRITINGSANDAMMYSELFTHEAUTHOROFATRIFLINGMONOGRAPHUPONTHESUBJECTINWHICHIANALYZEONEHUNDREDANDSIXTYSEPARATECIPHERSBUTICONFESSTHATTHISISENTIRELYNEWTOME
```

`MONOGRAPH`.

## Chapter 5. Machanised Cryptography

> Enigma

### PUZZLE 5-1

```py
plain_text = "ZYDNI"

f1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
f2 = "UWYGADFPVZBECKMTHXSLRINQOJ"

r1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
r2 = "YRUHQSLDPXNGOKMIEBFZCWVJAT"

for c in plain_text:
    c = ord(c) - ord('A')
    
    # rotate
    f1 = f1[1:] + f1[0]
    f2 = f2[1:] + f2[0]

    # Scrambler I
    c = f2.index(f1[c])
    
    # Reflector
    c = r2.index(r1[c])

    # Scrambler I
    c = f1.index(f2[c])

    print(chr(c + ord('A')), end='')

print()
```

`ULTRA`.

### PUZZLE 5-2

Brute force. Just need to rotate $4$ times.

```py
plain_text = "QHSGUWIG"

f1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
f2 = "UWYGADFPVZBECKMTHXSLRINQOJ"

r1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
r2 = "YRUHQSLDPXNGOKMIEBFZCWVJAT"

for rot in range(4):
    f1 = f1[1:] + f1[0]
    f2 = f2[1:] + f2[0]

for c in plain_text:
    c = ord(c) - ord('A')
    
    # rotate
    f1 = f1[1:] + f1[0]
    f2 = f2[1:] + f2[0]

    # Scrambler I
    c = f2.index(f1[c])
    
    # Reflector
    c = r2.index(r1[c])

    # Scrambler I
    c = f1.index(f2[c])

    print(chr(c + ord('A')), end='')

print()
```

`PURPLE`.

### PUZZLE 5-3

```py
plain_text = "GYHRVFLRXY"

plugboard = {
    'A': 'B', 'B': 'A',
    'S': 'Z', 'Z': 'S',
    'U': 'Y', 'Y': 'U',
    'G': 'H', 'H': 'G',
    'L': 'Q', 'Q': 'L',
    'E': 'N', 'N': 'E'
}

scrambler1_in  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
scrambler1_out = "UWYGADFPVZBECKMTHXSLRINQOJ"

scrambler2_in  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
scrambler2_out = "AJPCZWRLFBDKOTYUQGENHXMIVS"

scrambler3_in  = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
scrambler3_out = "TAGBPCSDQEUFVNZHYIXJWLRKOM"

r1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
r2 = "YRUHQSLDPXNGOKMIEBFZCWVJAT"

while scrambler1_in[0] != 'E':
    scrambler1_in = scrambler1_in[1:] + scrambler1_in[0]
    scrambler1_out = scrambler1_out[1:] + scrambler1_out[0]

while scrambler3_in[0] != 'B':
    scrambler3_in = scrambler3_in[1:] + scrambler3_in[0]
    scrambler3_out = scrambler3_out[1:] + scrambler3_out[0]

for c in plain_text:
    # plugboard
    if c in plugboard:
        c = plugboard[c]
    c = ord(c) - ord('A')
    
    # rotate
    scrambler2_in = scrambler2_in[1:] + scrambler2_in[0]
    scrambler2_out = scrambler2_out[1:] + scrambler2_out[0]

    # scrambler 2
    c = scrambler2_out.index(scrambler2_in[c])
    # scrambler 1
    c = scrambler1_out.index(scrambler1_in[c])
    # scrambler 3
    c = scrambler3_out.index(scrambler3_in[c])

    # reflector
    c = r2.index(r1[c])

    # scrambler 3
    c = scrambler3_in.index(scrambler3_out[c])
    # scrambler 1
    c = scrambler1_in.index(scrambler1_out[c])
    # scrambler 2
    c = scrambler2_in.index(scrambler2_out[c])

    # plugboard
    c = chr(c + ord('A'))
    if c in plugboard:
        c = plugboard[c]
    print(c, end='')

print()
```

`BLITZKRIEG`.

## Chapter 6. Digital Cryptography

### PUZZLE 6-1

Binary to ASCII. `DATA`.

### PUZZLE 6-2

```py
plain_text = [ord('H'), ord('E'), ord('L'), ord('L'), ord('O')]
matrix = [
    [0, 0, 1, 1, 1, 1, 1, 1],
    [0, 0, 1, 0, 1, 0, 1, 0],
    [0, 0, 1, 1, 1, 1, 1, 0],
    [0, 0, 1, 0, 0, 0, 0, 0],
    [0, 0, 1, 0, 1, 0, 1, 1]
]
for i in range(len(matrix)):
    num = 0
    for j in range(len(matrix[i])):
        matrix[i][j] ^= (plain_text[i] >> (7 - j)) & 1
        num = 2 * num + matrix[i][j]
    print(chr(num), end = '')
print()
```

`WORLD`.

### PUZZLE 6-3

```py
shift = [2, 1, 3, 1, 2, 5, 7, 2]
matrix = [
    [0, 1, 1, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 0, 1, 0, 1],
    [0, 1, 1, 1, 1, 0, 0, 1],
    [0, 1, 1, 0, 0, 0, 1, 1],
    [0, 1, 1, 1, 0, 1, 0, 1],
    [0, 1, 1, 0, 0, 1, 1, 0],
    [0, 1, 1, 0, 1, 0, 0, 1]
]

res = [[0]*8 for _ in range(7)]
for j in range(8):
    for i in range(7):
        res[i][j] = matrix[(i - shift[j]) % 7][j]

ascii_chars = []
for row in res:
    b = ''.join(str(x) for x in row)
    ascii_chars.append(chr(int(b, 2)))

print(''.join(ascii_chars))
```

`BITWISE`.

### PUZZLE 6-4

LSB Steganography. `.JPG`.

### PUZZLE 6-5

```py
from typing import List

def to_block(bits: str) -> List[List[int]]:
    """16-bit string -> 4x4 block"""
    assert len(bits) == 16
    nums = list(map(int, bits))
    return [nums[i:i+4] for i in range(0, 16, 4)]


def from_block(block: List[List[int]]) -> str:
    """4x4 block -> 16-bit string"""
    return ''.join(str(bit) for row in block for bit in row)


def swap_columns(block: List[List[int]]) -> List[List[int]]:
    """Swap col 1/2 and 3/4"""
    new = []
    for row in block:
        new.append([row[1], row[0], row[3], row[2]])
    return new


def xor_blocks(a: List[List[int]], b: List[List[int]]) -> List[List[int]]:
    """XOR two 4x4 blocks"""
    return [
        [a[i][j] ^ b[i][j] for j in range(4)]
        for i in range(4)
    ]


def inv_shift_rows(block):
    new = []
    for i, row in enumerate(block):
        k = i % 4
        new.append(row[k:] + row[:k])
    return new

def bes_round_decrypt(text_block, key_block):
    text_block = inv_shift_rows(text_block)
    key_block = swap_columns(key_block)
    text_block = xor_blocks(text_block, key_block)
    text_block = swap_columns(text_block)
    return text_block

def bes_decrypt(ciphertext_bits: str, round_keys: List[str]) -> str:
    block = to_block(ciphertext_bits)
    for rk in reversed(round_keys):
        key_block = to_block(rk)
        block = bes_round_decrypt(block, key_block)
    return from_block(block)

plaintext = "1001011110110101"
round_keys = [
    "0101100101010011",  # Round 1 key
    "0100001001011000"   # Round 2 key
]

ciphertext = bes_decrypt(plaintext, round_keys)
print(chr(int(ciphertext[0:8], 2)), chr(int(ciphertext[8:16], 2)))
```

`FN`.

## Challenge

### Challenge 1

The shape looks like 元素周期表. 但是有几个格子缺失, 分别是 N, S, Cl, Eu, U. 将它们排列一下得到 `NUCLEUS`.

### Challenge 2

十六进制颜色表, 对应红橙... `RAINBOW`.

### Challenge 8

Braille (Remove noise points which does not align).

```
RESISTOR
REDGREENRED
QCANLJNSKVXIKSKZ
```

From the `REDGREENRED`, we know the resistance is $2500 \Omega$.

将 `QCANLJNSKVXIKSKZ` 拿 `2500` 作为密钥加密，得到 `SHANNONSMAXIMXKZ`. 而 Shannon's maxim: The enemy knows the system. `THEENEMYKNOWSTHESYSTEM`.

