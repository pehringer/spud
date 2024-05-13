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
Behaviour                      |Machine Instruction|Assembly Instruction
-------------------------------|-------------------|--------------------
```ac = memory[ADDRESS]```     |```[ADDRESS]000``` |```get [LABEL]```
```memory[ADDRESS] = ac```     |```[ADDRESS]100``` |```set [LABEL]```
```ac = ac + memory[ADDRESS]```|```[ADDRESS]010``` |```add [LABEL]```
```ac = ac - memory[ADDRESS]```|```[ADDRESS]110``` |```sub [LABEL]```
```ip = ADDRESS```             |```[ADDRESS]001``` |```any [LABEL]```
```if(AC < 0) ip = ADDRESS```  |```[ADDRESS]101``` |```neg [LABEL]```
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
### Arithmetic Examples
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
### Assembly Comparison Examples
#### z = x < y
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
#### z = x > y
```
; set true
GET num_1
SET var_z

; check false
GET var_y
SUB var_x
NEG halt
GET num_0
SET var_z

halt:
ANY halt

num_0:
0

num_1:
1

var_x:
2

var_y:
4

var_z:
0
```
#### z = x <= y
```
; set false
GET num_0
SET var_z

; check true
GET var_y
SUB var_x
NEG halt
GET num_1
SET var_z

halt:
ANY halt

num_0:
0

num_1:
1

var_x:
2

var_y:
4

var_z:
0
```
#### z = x >= y
```
; set false
GET num_0
SET var_z

; check true
GET var_x
SUB var_y
NEG halt
GET num_1
SET var_z

halt:
ANY halt

num_0:
0

num_1:
1

var_x:
2

var_y:
4

var_z:
0
```
#### z = x != y
```
; set true
GET num_1
SET var_z

; check false
GET var_x
SUB var_y
NEG halt
GET var_y
SUB var_x
NEG halt
GET num_0
SET var_z

halt:
ANY halt

num_0:
0

num_1:
1

var_x:
2

var_y:
4

var_z:
0
```
#### z = x == y
```
; set false
GET num_0
SET var_z

; check true
GET var_x
SUB var_y
NEG halt
GET var_y
SUB var_x
NEG halt
GET num_1
SET var_z

halt:
ANY halt

num_0:
0

num_1:
1

var_x:
2

var_y:
4

var_z:
0
```
### Assembly Array Examples
#### j = a[i]
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store GET instruction with index address
GET ptr_a
ADD var_i
ADD get_op
SET idx_a
idx_a:
0
SET var_j

halt:
ANY halt

get_op:
000000000000000000

var_i:
2

var_j:
0

var_a:
1
2
4
8

ptr_a:
var_a
```
#### a[i] = j
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store SET instruction with index address
GET ptr_a
ADD var_i
ADD set_op
SET idx_a
GET var_j
idx_a:
0

halt:
ANY halt

set_op:
0b0010000000000000

var_i:
2

var_j:
0

var_a:
1
2
4
8

ptr_a:
var_a
```
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




