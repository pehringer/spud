# Spud - Simple Processor Unit Design
A very simple processor that resembles modern designs. That is easy to use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Accumulator based machine.
# Hardware Diagram
```
______________________________________
|            m e m o r y             | 
|____________________________________|
             |          |
  _____ADDRESS          DATA________________
  |          |          |                  |
  |   ______ | ________ | __________     __|__
  |   |      |   |      |   |      |     \___/--[~]
__|___|__  __|___|__  __|___|__  __|__   __|__
|  i p  |  |  i r  |  |  a c  |  \    \_/    /__[++]
|_______|  |_______|  |_______|   \____+____/  
    |          |          |            |   
    |__________|__________|____________|

```
# Instruction Set
Fetch/Decode Behaviour  |
------------------------|
```ir = memory[ip++]``` |

***Note: ADDRESS = ir[0:13]***
  
Execute Behaviour               |Machine Instruction|Assembly Instruction
--------------------------------|-------------------|--------------------
```ac = memory[ADDRESS]```      |```[ADDRESS]000``` |```get [LABEL]```
```memory[ADDRESS] = ac```      |```[ADDRESS]100``` |```set [LABEL]```
```ac = ac + memory[ADDRESS]``` |```[ADDRESS]010``` |```add [LABEL]```
```ac = ac - memory[ADDRESS]``` |```[ADDRESS]110``` |```sub [LABEL]```
```ip = ADDRESS```              |```[ADDRESS]001``` |```any [LABEL]```
```if(AC < 0) ip = ADDRESS```   |```[ADDRESS]101``` |```neg [LABEL]```
# Machine Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<bit> ::= “0” | “1”
<nibble> ::= <bit><bit><bit><bit>
<address> ::= <nibble><nibble><nibble><bit>
<immediate> ::= <nibble><nibble><nibble><nibble>
<instruction> ::= <address>”000” | <address>”100” | <address>”010” | <address>”110” | <address>”001” | <address>”101”
<code> ::= <instruction><code> | <immediate><code> | ""     
```
# Assembly Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<space> ::= "\n" | "\s" | "\t"
<upper> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z" | "_"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<ws> ::= <space><ws> | <space>
<label> ::= <upper><label> | <upper>
<number> ::= <digit><number> | <digit>
<immediate> ::= "lab"<ws><label> | "num"<ws><number>
<instruction> ::= "get"<ws><label> | "set"<ws><label> | "add"<ws><label> | "sub"<ws><label> | "any"<ws><label> | "neg"<ws><label>
<code> ::= <instruction><ws><code> | <immediate><ws><code> | <label><ws><code> | ""
```
# Assembler
The assembler takes two filepaths as arguments:  
```python asm.py [INPUT_ASSEMBLY_FILEPATH] [OUTPUT_BINARY_FILEPATH]```  
  
For example if you wanted to regenerate the hello world assembly example:  
```python asm.py example_asm/hello_world.asm example_bin/hello_world.bin```  
  
If any errors occur try running the Makefile.  
# Simulator
The simulator will run the example_bin/hello_world.bin if no arguments are given:  
```./simulator```  
  
Terminal Output:
```
     
Accumulator:             
0101 0000 0000 0000      
Instruction Pointer: 
0101 1000 0000 0     
Instruction Register:
0101 1000 0000 0001     
                        
0010 0100 0000 0000     
1111 1111 1111 1100     
1010 0100 0000 0000     
1111 1111 1111 1100     
0110 0100 0000 0000     
1111 1111 1111 1100     
1110 0100 0000 0000    
1111 1111 1111 1100    
0101 1000 0000 0001  <-
0001 0110 0000 0000    
1010 0110 0000 0000    
0011 0110 0000 0000    
0011 0110 0000 0000    
1111 0110 0000 0000    
0011 0100 0000 0000    
0000 0100 0000 0000    
1110 1110 0000 0000     




hello, world

```
If any errors occur try running the Makefile  
  
The simulator supports the following optional arguments:
- ```filepath [PATH_TO_BINARY]``` - Run the .bin at the given filepath.
- ```cycle_time [NUMBER_MILLISECONDS]``` - Make the simulator take the given number of milliseconds per cycle.
- ```cycle_count [NUMBER_CYCLES]``` - Make the simulator run the given number of cycles before halting.
  
For example if you wanted to execute hello world 4x faster and have it stop after "hello" has beeen printed:  
```./sim.bin -filepath exmaple_bin/hello_world.bin -cycle_time 250 -cycle_count 11```
# Peripherals
There are two memory mapped peripherals:
- Input Unit, address ```8190``` (assembly label ```GETC```)
- Output Unit, address ```8191``` (assembly label ```PUTC```)
  
These peripherals are used to read / print characters to standard in/out (terminal).
  
***Input Unit***: set memory address ```8190``` to zero value, memory address ```8190``` will then be set to ascii value of the next character from stdin.
  
***Output Unit***: set memory address ```8191``` to ascii value of next character for stdout, memory address ```8191``` will then be set to zero value.
  
See ```example_asm/echo.asm``` for an example of how to use the the input and output units.
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
ONE   num 1
X     num 4
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
ONE   num 1
X     num 4
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
X     num 4
Y     num 8
Z     num 0
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
X     num 4
Y     num 8
Z     num 0

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
FALSE num 0
TRUE  num 1
X     num 2
Y     num 4
Z     num 0
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
FALSE num 0
TRUE  num 1
X     num 2
Y     num 4
Z     num 0
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
FALSE num 0
TRUE  num 1
X     num 2
Y     num 4
Z     num 0
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
FALSE num 0
TRUE  num 1
X     num 2
Y     num 4
Z     num 0
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
FALSE num 0
TRUE  num 1
X     num 2
Y     num 4
Z     num 0
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
FALSE num 0
TRUE  num 1
X     num 2
Y     num 4
Z     num 0
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int J = A[I];
```
```
START  get OPCODE
       add A
       add I
       set INDEX
INDEX  num 0
       set J
END    any END
OPCODE num 0
I      num 2
J      num 0
ARRAY  num 1
       num 2
       num 4
       num 8
A      lab ARRAY
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int A[I] = J;
```
```
START  get OPCODE
       add A
       add I
       set INDEX
       get J
INDEX  num 0
END    any END
OPCODE num 8192
I      num 2
J      num 0
ARRAY  num 1
       num 2
       num 4
       num 8
A      lab ARRAY
```
---
```
int X = 42;
push(X);
```
```
START  GET OPCODE
       ADD S
       SET PUSH
       GET X
PUSH   num 0
       get S
       sub ONE
       SET S
END    any END
OPCODE num 8192
ONE    num 1
X      num 42
STACK  num 0
       num 0
TOP    num 0
       num 21
S      lab TOP
```
---
```
int X = pop();
```
```
START  get S
       add ONE
       set S
       get OPCODE
       add S
       set POP
POP    num 0
       set X
END    any END
OPCODE num 0
ONE    num 1
X      num 0
STACK  num 0
TOP    num 0
       num 42
       num 21
S      lab TOP
```
---
```
int X = peek();
```
```
START  get OPCODE
       add S
       add ONE
       set PEEK     
PEEK   num 0
       set X
END    any END
OPCODE num 0
ONE    num 1
X      num 0
STACK  num 0
TOP    num 0
       num 42
       num 21
S      lab TOP
```
---

