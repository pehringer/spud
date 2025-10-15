# ***spud*** - ***S***imple ***P***rocessor ***U***nit ***D***esign
The simplest processor design (that I could think of) that still resembles modern processors:
 - Von Neumann architecture.
 - Accumulator based machine.
 - Word (16-bits) addressable memory.
### Contents
- [Instruction Set](#instruction-set)
- [Machine Code Syntax](#machine-code-syntax)
- [Assembly Code Syntax](#assembly-code-syntax)
- [Assembler](#assembler)
- [Simulator](#simulator)
- [Peripherals](#peripherals)
- [Assembly Code Examples](#assembly-code-examples)
# Instruction Set
```
______________________________________
|            m e m o r y             | 
|____________________________________|
             |          |
  _____ADDRESS          DATA__________________
  |          |          |                    | ___NOT (~)
  |   ______ | ________ | _____________     _|_|_
  |   |      |   |      |   |         |     \xor/ 
__|___|__  __|___|__  __|___|__     __|__   __|__
|  i p  |  |  i r  |  |  a c  |  ___\    \_/    /__CARRY (+1)
|_______|  |_______|  |_______|  |   \__adder__/  
    |          |          | |____|        |   
    |__________|__________|_______________|

(ip) instruction pointer 13-bits

(ir) instruction register 16-bits
     opcode  bits 13-15 
     address bits  0-12

(ac) accumulator 17-bits
     sign_bit  bit 15
     carry_bit bit 16
```
|Fetch/Decode Behaviour |
|-----------------------|
|```ir = memory[ip++]```|

|Execute Behaviour                                |Operation                |
|-------------------------------------------------|-------------------------|
|```if(opcode == 0) {ac = memory[address]}```     |```ld``` - Load          |
|```if(opcode == 1) {memory[address] = ac}```     |```st``` - Store         |
|```if(opcode == 2) {ac += memory[address]}```    |```ad``` - Add (Unsigned)|
|```if(opcode == 3) {ac = ~memory[address]}```    |```nt``` - Not           |
|```if(opcode == 4) {ip = address}```             |```ja``` - Jump Address  |
|```if(opcode == 5 && sign_bit) {ip = address}``` |```js``` - Jump Sign Bit |
|```if(opcode == 6 && carry_bit) {ip = address}```|```jc``` - Jump Carry Bit|
|```if(opcode == 7) {return address}```           |```ht``` - Halt          |
# Machine Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<bit> ::= "0" | "1"
<nibble> ::= <bit><bit><bit><bit>
<word> ::= <nibble><nibble><nibble><nibble>
<opcode> ::= "000" | "001" | "010" | "011" | "100" | "101" | "110" | "111"
<address> ::= <bit><nibble><nibble><nibble>
<code> ::= <opcode><address><code> | <word><code> | ""
```
# Assembly Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<number> ::= <digit><number> | <digit>
<letter> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "_"
<label> ::= <upper><label> | <upper>
<space> ::= "\n" | "\s" | "\t"
<whitespace> ::= <space><whitespace> | <space>
<opcode> ::= "ld" | "st" | "ad" | "nt" | "ja" | "js" | "jc" | "ht"
<operation> ::= <opcode><whitespace><number> | <opcode><whitespace><label>
<code> ::= <label><whitespace><code> | <number><whitespace><code> | <operation><whitespace><code> | ""

```
# Assembler
The assembler requires two filepaths:  
```python asm.py [INPUT_ASSEMBLY_FILEPATH] [OUTPUT_BINARY_FILEPATH]```

For example if you wanted to regenerate the hello world program:
```
$ python asm.py examples/asm/hello.asm examples/bin/hello.bin
Size 29:
0000000000010101
0010000000000101
0000000000000100
1000000000000110
1110000000000000
0000000000000000
0010000000010011
0000000000000101
0010000000001001
0000000000000000
0011111111111111
0010000000000101
0000000000001001
0100000000010100
0010000000001001
0110000000000101
0100000000010100
0100000000011100
1010000000001001
0000000000000000
0000000000000001
0000000000010110
0000000001101000
0000000001100101
0000000001101100
0000000001101100
0000000001101111
0000000000001010
0000000000000000
Labels:
  GETC: 8190
  PUTC: 8191
  HALT: 4
  PRINT_ARGUMENT: 5
  PRINT_ROUTINE: 6
  INDEX_STRING: 9
  PRINT_RETURN: 19
  INCREMENT: 20
  STRING: 21
  CHAR_ARRAY: 22
  CHAR_NULL: 28
$
```
If any errors occur try running the Makefile.
# Simulator
The simulator requires one filepath:
```./sim.bin [INPUT_BINARY_CODE_FILEPATH]```

For example if you wanted to run the hello world program:
```
$ ./sim.bin examples/bin/hello.bin
hello

HALTED: 0
$
```
If any errors occur try running the Makefile.
# Peripherals
There are two memory mapped peripherals:
- Input Unit, address ```8190``` (assembly label ```GETC```)
- Output Unit, address ```8191``` (assembly label ```PUTC```)

These peripherals are used to read / print characters to standard in/out (terminal).

***Input Unit***: set memory address ```8190``` to zero value, memory address ```8190``` will then be set to ascii value of the next character from stdin.

***Output Unit***: set memory address ```8191``` to ascii value of next character for stdout, memory address ```8191``` will then be set to zero value.

See ```examples/asm/echo.asm``` for an example of how to use the input and output units.
# Assembly Code Examples
See the ```examples/asm``` directory.


