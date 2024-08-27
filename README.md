# ***spud*** - ***S***imple ***P***rocessor ***U***nit ***D***esign
The simplest processor design (that I could think of) that still resembles modern processors:
 - Von Neumann architecture.
 - Word addressable memory.
 - Accumulator based machine.
 - Two complement numbers.
### Contents
- [Hardware Diagram](#hardware-diagram)
- [Instruction Set](#instruction-set)
- [Machine Code Syntax](#machine-code-syntax)
- [Assembly Code Syntax](#assembly-code-syntax)
- [Assembler](#assembler)
- [Simulator](#simulator)
- [Peripherals](#peripherals)
- [Interesting Workarounds](#interesting-workarounds)
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
  |   |      |   |      |   |      |     \xor/__[~]
__|___|__  __|___|__  __|___|__  __|__   __|__
|  i p  |  |  i r  |  |  a c  |  \    \_/    /__[++]
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

***Note: instruction address is the 13 least significant bits of ir (instruction register).***  
***Note: instruction opcode is the 3 most significant bits of ir (instruction register).***  

Execute Behaviour            |Description                           |Binary             |Assembly
-----------------------------|--------------------------------------|-------------------|-----------------
```ac = memory[ADDRESS]```   |Load accumulator.                     |```000[ADDRESS]``` |```get [LABEL]```
```memory[ADDRESS] = ac```   |Store accumulator.                    |```001[ADDRESS]``` |```set [LABEL]```
```ac += memory[ADDRESS]```  |Add to accumulator.                   |```010[ADDRESS]``` |```add [LABEL]```
```ac -= memory[ADDRESS]```  |Subtract from accumulator.            |```011[ADDRESS]``` |```sub [LABEL]```
```ip = ADDRESS```           |Jump for any accumulator value.       |```100[ADDRESS]``` |```any [LABEL]```
```if(AC < 0) ip = ADDRESS```|Jump if accumulator value is negative.|```101[ADDRESS]``` |```neg [LABEL]```
# Machine Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<bit> ::= "0" | "1"
<nibble> ::= <bit><bit><bit><bit>
<word> ::= <nibble><nibble><nibble><nibble>
<opcode> ::= "000" | "001" | "010" | "011" | "100" | "101"
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
<whitespace> ::= "\n" | "\s" | "\t"
<space> ::= <whitespace><delimiter> | <whitespace>
<opcode> ::= "get" | "set" | "add" | "sub” | "any" | "neg"
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
- ```filepath [PATH_TO_BINARY]``` - Run the .bin at the given filepath.
- ```cycle_time [NUMBER_MILLISECONDS]``` - Make the simulator take the given number of milliseconds per cycle.
- ```cycle_count [NUMBER_CYCLES]``` - Make the simulator run the given number of cycles before halting.

For example if you wanted to execute hello world 4x faster and have it stop after "hello" has beeen printed:  
```./sim.bin -filepath examples/bin/hello_world.bin -cycle_time 25 -cycle_count 46```
# Peripherals
There are two memory mapped peripherals:
- Input Unit, address ```8190``` (assembly label ```GETC```)
- Output Unit, address ```8191``` (assembly label ```PUTC```)

These peripherals are used to read / print characters to standard in/out (terminal).

***Input Unit***: set memory address ```8190``` to zero value, memory address ```8190``` will then be set to ascii value of the next character from stdin.

***Output Unit***: set memory address ```8191``` to ascii value of next character for stdout, memory address ```8191``` will then be set to zero value.

See ```example_asm/echo.asm``` for an example of how to use the the input and output units.
# Interesting Workarounds
### Subtraction
The processor lacks subtraction hardware.
The workaround is to negate one of the numbers then add them together.
```
number - number  ==  number + (-number)
```  
To negate a binary number (two's complement):
1) Bitwise not the number (XOR one of the adders inputs).
2) Increment the number by one (use adders carry-in input).
### Dynamic Addresses
The instruction set only contains operations with fixed addresses.
The workaround is to use self modifying code:
1) Get instruction with base address.
2) Add offset.
3) Set memory location.
4) Execute memory location.

For example setting an array element.
```
START  get A_GET
       add I
       set INDEX
INDEX  0
       set J
END    any END
I      2
J      0
A_GET  get A
A      1
       2
       4
       8
```
### The Stack
The processor lacks a stack pointer register.
The workaround is to store the stack pointer in memory.
And to use self modifying code to create instructions to load from and store to it.
# Assembly Code Examples
---
```
int X = 4;
X++;
```  
```
START get X
      add ONE
      set X
END   any END
ONE   1
X     4
```
---
```
int X = 4;
X--;
```  
```
START get X
      sub ONE
      set X
END   any END
ONE   1
X     4
```
---
```
int X = 4;
int Y = 8;
int Z = X + Y;
```
```
START get X
      add Y
      set Z
END   any END
X     4
Y     8
Z     0
```
---
```
int X = 4;
int Y = 8;
int Z = X - Y;
```
```
START get X
      sub Y
      set Z
END   any END
X     4
Y     8
Z     0

```
---
```
int X = 2;
int Y = 4;
int Z = X < Y;
```
```
START get TRUE
      set Z
      get X
      sub Y
      neg END
      get FALSE
      set Z
END   any END
FALSE 0
TRUE  1
X     2
Y     4
Z     0
```
---
```
int X = 2;
int Y = 4;
int Z = X > Y;
```
```
START get TRUE
      set Z
      get Y
      sub X
      neg END
      get FALSE
      set Z
END   any END
FALSE 0
TRUE  1
X     2
Y     4
Z     0
```
---
```
int X = 2;
int Y = 4;
int Z = X <= Y;
```
```
START get FALSE
      set Z
      get Y
      sub X
      neg END
      get TRUE
      set Z
END   any END
FALSE 0
TRUE  1
X     2
Y     4
Z     0
```
---
```
int X = 2;
int Y = 4;
int Z = X >= Y;
```
```
START get FALSE
      set Z
      get X
      sub Y
      neg END
      get TRUE
      set Z
END   any END
FALSE 0
TRUE  1
X     2
Y     4
Z     0
```
---
```
int X = 2;
int Y = 4;
int Z = X != Y;
```
```
START get TRUE
      set Z
      get X
      sub Y
      neg END
      get Y
      sub X
      neg END
      get FALSE
      set Z
END   any END
FALSE 0
TRUE  1
X     2
Y     4
Z     0
```
---
```
int X = 2;
int Y = 4;
int Z = X == Y;
```
```
START get FALSE
      set Z
      get X
      sub Y
      neg END
      get Y
      sub X
      neg END
      get TRUE
      set Z
END   any END
FALSE 0
TRUE  1
X     2
Y     4
Z     0
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int J = 0;
J = A[I];
```
All instructions have fixed memory addresses.
Dynamic memory addresses requires self-modifying code.
Create and store "get" instruction with array index address (INDEX).
```
START  get A_GET
       add I
       set INDEX
INDEX  0
       set J
END    any END
I      2
J      0
A_GET  get A
A      1
       2
       4
       8
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int J = 0;
A[I] = J;
```
All instructions have fixed memory addresses.
Dynamic memory addresses requires self-modifying code.
Create and store "set" instruction with array index address (INDEX).
```
START  get A_SET
       add I
       set INDEX
       get J
INDEX  0
END    any END
I      2
J      0
A_SET  set A
A      1
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
Pass "any" instruction with return address (HALT) to subroutine (PRINT) and store it (PRINT_RET) for later execution to return. 
```
           get STRING
           set PRINT_ARG
           get HALT
           any PRINT_CAL
HALT       any HALT




PRINT_ARG 0
PRINT_CAL set PRINT_RET
          get PRINT_ARG
          set PRINT_IDX
PRINT_IDX 0
          set PUTC
          set PRINT_ARG
          get PRINT_IDX
          add INCREMENT
          set PRINT_IDX
          get CHAR_NULL
          sub PRINT_ARG
          neg PRINT_IDX
PRINT_RET 0




INCREMENT 1

CHAR_NULL 0

STRING      get CHAR_ARRAY
CHAR_ARRAY  104
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
