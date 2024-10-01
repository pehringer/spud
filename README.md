# ***spud*** - ***S***imple ***P***rocessor ***U***nit ***D***esign
The simplest processor design (that I could think of) that still resembles modern processors:
 - Von Neumann architecture.
 - Accumulator based machine.
 - Word (16-bit) addressable memory.
### Contents
- [Hardware Diagram](#hardware-diagram)
- [Instruction Set](#instruction-set)
- [Machine Code Syntax](#machine-code-syntax)
- [Assembly Code Syntax](#assembly-code-syntax)
- [Assembler](#assembler)
- [Simulator](#simulator)
- [Peripherals](#peripherals)
- [Assembly Code Examples](#assembly-code-examples)
# Hardware Diagram
```
______________________________________
|            m e m o r y             | 
|____________________________________|
             |          |
  _____ADDRESS          DATA________________
  |          |          |                  |
  |   ______ | ________ | __________     __|__
  |   |      |   |      |   |      |     \xor/__BITWISE NOT (~) 
__|___|__  __|___|__  __|___|__  __|__   __|__
|  i p  |  |  i r  |  |  a c  |  \    \_/    /__INCREMENT (++)
|_______|  |_______|  |_______|   \__adder__/  
    |          |          |            |   
    |__________|__________|____________|

ip = instruction pointer
ir = instruction register
ac = accumulator

```
# Instruction Set
Fetch/Decode Behaviour  |Description
------------------------|------------------------------------------------------------
```ir = memory[ip++]``` |Load instruction register and increment instruction pointer.

***Note: instruction address is the 12 least significant bits of ir (instruction register).***  
***Note: instruction opcode is the 4 most significant bits of ir (instruction register).***  

Execute Behaviour              |Description                             |Binary              |Assembly
-------------------------------|----------------------------------------|--------------------|----------------
```ac = memory[ADDRESS]```     |Load accumulator with value.            |```0000[ADDRESS]``` |```ld [LABEL]```
```memory[ADDRESS] = ac```     |Store accumulator.                      |```0001[ADDRESS]``` |```st [LABEL]```
```ac += memory[ADDRESS]```    |Add value to accumulator.               |```0010[ADDRESS]``` |```ad [LABEL]```
```ac = ~memory[ADDRESS]```    |Load accumulator with inverted value.   |```0011[ADDRESS]``` |```nt [LABEL]```
```ip = ADDRESS```             |Jump to address.                        |```0100[ADDRESS]``` |```ja [LABEL]```
```if(AC >> 15) ip = ADDRESS```|Jump to address if accumulator sign bit.|```0101[ADDRESS]``` |```js [LABEL]```
# Machine Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<bit> ::= "0" | "1"
<nibble> ::= <bit><bit><bit><bit>
<word> ::= <nibble><nibble><nibble><nibble>
<opcode> ::= "0000" | "0001" | "0010" | "0011" | "0100" | "0101"
<address> ::= <nibble><nibble><nibble>
<code> ::= <opcode><address><code> | <word><code> | ""     
```
# Assembly Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<number> ::= <digit><number> | <digit>
<letter> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "_"
<label> ::= <upper><label> | <upper>
<whitespace> ::= "\n" | "\s" | "\t"
<space> ::= <whitespace><space> | <whitespace>
<opcode> ::= "ld" | "st" | "ad" | "nt” | "ja" | "js"
<operation> ::= <opcode><space><number> | <opcode><space><label>
<code> ::= <label><space><code> | <number><space><code> | <operation><space><code> | "."

```
# Assembler
The assembler takes two filepaths as arguments:  
```python asm.py [INPUT_ASSEMBLY_FILEPATH] [OUTPUT_BINARY_FILEPATH]```  

For example if you wanted to regenerate the hello world assembly example:  
```python asm.py examples/asm/hello_world.asm examples/bin/hello_world.bin```

If any errors occur try running the Makefile.  
# Simulator
The simulator will run the examples/bin/hello_world.bin if no arguments are given:  
```./sim.bin```
  
Terminal Output:  
```
hello world
$
```
If any errors occur try running the Makefile

The simulator supports the following optional arguments:
- ```-filepath [PATH_TO_BINARY]``` - Run the .bin at the given filepath.
- ```-cycle_time [NUMBER_MILLISECONDS]``` - Make the simulator take the given number of milliseconds per cycle.
- ```-cycle_count [NUMBER_CYCLES]``` - Make the simulator run the given number of cycles before halting.

For example if you wanted to execute hello world 4x faster and have it stop after "hello" has beeen printed:  
```./sim.bin -filepath examples/bin/hello_world.bin -cycle_time 25 -cycle_count 50```
# Peripherals
There are two memory mapped peripherals:
- Input Unit, address ```4094``` (assembly label ```GETC```)
- Output Unit, address ```4095``` (assembly label ```PUTC```)

These peripherals are used to read / print characters to standard in/out (terminal).

***Input Unit***: set memory address ```4094``` to zero value, memory address ```4094``` will then be set to ascii value of the next character from stdin.

***Output Unit***: set memory address ```4095``` to ascii value of next character for stdout, memory address ```4095``` will then be set to zero value.

See ```example_asm/echo.asm``` for an example of how to use the input and output units.
# Assembly Code Examples
---
```
int A = 7;
int B = 2;
int C = A - B;
```
The processor lacks subtraction hardware.
The workaround is to negate one of the numbers then add them together.
To negate a binary number bitwise not the number, then add one to the number.
```
START nt B
      ad ONE
      ad A
      st C
HALT  ja HALT




ONE   1

A     7

B     2

C     0
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int J = A[I];
```
All instructions have fixed memory addresses.
Dynamic memory addresses requires self-modifying code.
Create and store "ld" instruction with array index address (INDEX).
```
START ld A_LD
      ad I
      st INDEX
INDEX 0
      st J
HALT  ja HALT




I     2

J     0

A_LD  ld A
A     1
      2
      4
      8
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int J = A[I] = J;
```
All instructions have fixed memory addresses.
Dynamic memory addresses requires self-modifying code.
Create and store "st" instruction with array index address (INDEX).
```
START ld A_ST
      ad I
      st INDEX
      ld J
INDEX 0
HALT  ja HALT




I     2

J     0

A_ST  st A
A     1
      2
      4
      8
```
---
```
printf("hello world\n");
```
All instructions have fixed memory addresses.
Dynamic memory addresses requires self-modifying code.
Pass "ja" instruction with return address (HALT) to subroutine (PRINT) and store it (PRINT_RET) for later execution to return. 
```
           ld  STRING
           st  PRINT_ARG
           ld  HALT
           ja  PRINT_CAL
HALT       ja  HALT




PRINT_ARG  0
PRINT_CAL  st  PRINT_RET
           ld  PRINT_ARG
           st  PRINT_IDX
PRINT_IDX  0
           st  PUTC
           st  PRINT_ARG
           ld  PRINT_IDX
           ad  INCREMENT
           st  PRINT_IDX
           nt  PRINT_ARG
           ad  INCREMENT
           ad  CHAR_NULL
           js  PRINT_IDX
PRINT_RET  0




INCREMENT  1

CHAR_NULL  0

STRING     ld  CHAR_ARRAY
CHAR_ARRAY 104
           101
           108
           108
           111
           32
           119
           111
           114
           108
           100
           10
           0
```
---
