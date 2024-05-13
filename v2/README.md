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
Behaviour                       |Machine Instruction|Assembly Instruction
--------------------------------|-------------------|--------------------
```ac = memory[ADDRESS];```     |```[ADDRESS]000``` |```get [LABEL]```
```memory[ADDRESS] = ac;```     |```[ADDRESS]100``` |```set [LABEL]```
```ac = ac + memory[ADDRESS];```|```[ADDRESS]010``` |```add [LABEL]```
```ac = ac - memory[ADDRESS];```|```[ADDRESS]110``` |```sub [LABEL]```
```ip = ADDRESS;```             |```[ADDRESS]001``` |```any [LABEL]```
```if(AC < 0) ip = ADDRESS;```  |```[ADDRESS]101``` |```neg [LABEL]```
# Machine Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<bit> ::= “0” | “1”
<nibble> ::= <bit><bit><bit><bit>
<address> ::= <nibble><nibble><nibble><bit>
<immediate> ::= <nibble><nibble><nibble><nibble>
<instruction> ::= <address>”000” | <address>”100” |
                  <address>”010” | <address>”110” |
                  <address>”001” | <address>”101”
<expression> ::= <instruction> | <immediate>
<program> ::= <expression> | <program><expression>     
```
# Assembly Code Syntax
[Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form)
```
<letter> ::= "_" | "A" | "B" | "C" | "D" | "E" | "F" | "G" |
             "H" | "I" | "J" | "K" | "L" | "M" | "N" | "O" |
             "P" | "Q" | "R" | "S" | "T" | "U" | "V" | "W" |
             "X" | "Y" | "Z"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" |
            "8" | "9"
<space> ::= "\n" | "\s" | <space>"\n" | <space>"\s" 
<label> ::= <letter> | <label><letter>
<number> ::= <digit> | <number><digit>
<immediate> ::= "lab"<space><label> | "num"<space><number>
<instruction> ::= "get"<space><label> | "set"<space><label> |
                  "add"<space><label> | "sub"<space><label> |
                  "any"<space><label> | "neg"<space><label>
<expression> ::= <instruction> | <immediate> | <label>
<program> ::= <expression> | <code><space><expression>
```
# Assembly Code Examples
---
```
int X = 4;
X++;
```  
```
START
     get X
     add ONE
     set X
END
     any END
ONE
     num 1
X
     num 4
```
---
```
int X = 4;
X--;
```  
```
START
     get X
     sub 1
     set X
END
     any END
ONE
     num 1
X
     num 4
```
---
```
int X = 4;
int Y = 8;
int Z = X + Y;
```
```
START
     get X
     add Y
     set Z
END
     any END
X
     num 4
Y
     num 8
Z
     num 0
```
---
```
int X = 4;
int Y = 8;
int Z = X - Y;
```
```
START
     get X
     sub Y
     set Z
END
     any END
X
     num 4
Y
     num 8
Z
     num 0
```
---
```
int X = 2;
int Y = 4;
int Z = X < Y;
```
```
START
     get TRUE
     set Z
     get X
     sub Y
     neg END
     get FALSE
     set Z
END
     any END
FALSE
     num 0
TRUE
     num 1
X
     num 2
Y
     num 4
Z
     num 0
```
---
```
int X = 2;
int Y = 4;
int Z = X > Y;
```
```
START
     get TRUE
     set Z
     get Y
     sub X
     neg END
     get FALSE
     set Z
END
     any END
FALSE
     num 0
TRUE
     num 1
X
     num 2
Y
     num 4
Z
     num 0
```
---
```
int X = 2;
int Y = 4;
int Z = X <= Y;
```
```
START
     get FALSE
     set Z
     get Y
     sub X
     neg END
     get TRUE
     set Z
END
     any END
FALSE
     num 0
TRUE
     num 1
X
     num 2
Y
     num 4
Z
     num 0
```
---
```
int X = 2;
int Y = 4;
int Z = X >= Y;
```
```
START
     get FALSE
     set Z
     get X
     sub Y
     neg END
     get TRUE
     set Z
END
     any END
FALSE
     num 0
TRUE
     num 1
X
     num 2
Y
     num 4
Z
     num 0
```
---
```
int X = 2;
int Y = 4;
int Z = X != Y;
```
```
START
     get num_1
     set var_z
     get var_x
     sub var_y
     neg halt
     get var_y
     sub var_x
     neg halt
     get num_0
     set var_z
END
     any END
FALSE
     num 0
TRUE
     num 1
X
     num 2
Y
     num 4
Z
     num 0
```
---
```
int X = 2;
int Y = 4;
int Z = X == Y;
```
```
START
     get num_0
     set var_z
     get var_x
     sub var_y
     neg halt
     get var_y
     sub var_x
     neg halt
     get num_1
     set var_z
END
     any END
FALSE
     num 0
TRUE
     num 1
X
     num 2
Y
     num 4
Z
     num 0
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int J = A[I];
```
```
START
      get OPCODE
      add A
      add I
      set INDEX
INDEX
      num 0
      set J
END
      any END
OPCODE
      num 0
I
      num 2
J
      num 0
ARRAY
      num 1
      num 2
      num 4
      num 8
A
      lab ARRAY
```
---
```
int A[4] = {1, 2, 4, 8};
int I = 2;
int A[I] = J;
```
```
START
      get OPCODE
      add A
      add I
      set INDEX
      get J
INDEX
      num 0
END
      any END
OPCODE
      num 8192
I
      num 2
J
      num 0
ARRAY
      num 1
      num 2
      num 4
      num 8
A
      lab ARRAY
```
---
### Assemply Stack Examples
#### push(x)
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store SET instruction with stack address
GET ptr_s
ADD set_op
SET save
GET var_x
save:
0

; decrement stack pointer by 1
GET ptr_s
SUB num_1
SET ptr_s

halt:
ANY halt

set_op:
0b0010000000000000

num_1:
1

var_x:
42

stack:
0
0
top_s:
0
21

ptr_s:
top_s
```
#### x = pop()
```
; increment stack pointer by 1
GET ptr_s
ADD num_1
SET ptr_s

; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store GET instruction with stack address
GET ptr_s
ADD get_op
SET load
load:
0
SET var_x

halt:
ANY halt

get_op:
0b0000000000000000

num_1:
1

var_x:
0

stack:
0
top_s:
0
42
21

ptr_s:
top_s
```
#### x = peek()
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store LD instruction with index address
GET ptr_s
ADD num_1
ADD get_op
SET load     
load:
0
SET var_x

halt:
ANY halt

get_op:
0b0000000000000000

num_1:
1

var_x:
0

stack:
0
top_s:
0
42
21

ptr_s:
top_s
```




