---

# Spud -> Simple Processor Unit Design.

A very simple processor that resembles modern designs. That is easy to use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Accumulator based machine.

---

# Hardware Diagram

```
______________________________________
|            m e m o r y             | 
|____________________________________|
             |         |
  _____ADDRESS         DATA________________________
  |   ______ | _______ | __________________     __|__
  |   |      |   |     |  |  _______      |     \___/--[~]
__|___|__  __|___|__  _|__|__|_  __|__  __|__   __|__
|  i p  |  |  i r  |  |  a c  |  \___/  \    \_/    /__[++]
|_______|  |_______|  |_______|    |     \____+____/  
    |          |          |      [-/+]        |   
    |__________|__________|___________________|

```
---

# Instruction Format

```
 opcode__   address_____________________ 
 15 14 13   12 11 10 9 8 7 6 5 4 3 2 1 0
```

---

# Instruction Set

### Fetch/Decode Behaviour

```ir <- memory[ip]```  
```ip <- ip + 1 ```  

### Execute Behaviour

Behaviour                      |Machine Instruction|Assembly Instruction
-------------------------------|-------------------|--------------------
```ac = memory[address]```     |```000[address]``` |```GET [address]```
```memory[address] = ac```     |```001[address]``` |```SET [address]```
```ac = ac + memory[address]```|```010[address]``` |```ADD [address]```
```ac = ac - memory[address]```|```011[address]``` |```SUB [address]```
```ip = address```             |```100[address]``` |```ANY [address]```
```if(AC < 0) ip = address```  |```101[address]``` |```NEG [address]```
```if(AC > 0) ip = address```  |```110[address]``` |```POS [address]```
```if(AC == 0) ip = address``` |```111[address]``` |```ZER [address]```

---

# Assembly Labels

One or more letters or numbers, following by one colon.

Assembly labels are extremely useful. They are simply a user defined keywords that repersent an address in memory.
They are a useful abstraction that can be used for the following:
+ Control Flow
+ Primitive Variables
+ Immediate Values

---

# Assembly Comments

One semicolon, following by zero or more characters.

Assembly comments are extremely helpful. They are equivalent to line comments in higher level programming languages.

---

# Assembly Examples

### Arithmetic Examples

#### x += 1  
```
; increment one
GET var_x
ADD num_1
SET var_x

halt:
ANY halt

num_1:
1

var_x:
4
```

#### x -= 1  
```
; decrement one
GET var_x
SUB num_1
SET var_x

halt:
ANY halt

num_1:
1

var_x:
4
```

#### z = x + y
```
; add values
GET var_x
ADD var_y
SET var_z

halt:
ANY halt

var_x:
4

var_y:
8

var_z:
0
```

#### z = x - y
```
; subtract values
GET var_x
ADD var_y
SET var_z

halt:
ANY halt

var_x:
4

var_y:
8

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
0b0110000000000000

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

### Assembly Comparison Examples

#### z = x < y
```
; set true
GET num_1
SET var_z

; check false
GET var_x
SUB var_y
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
GET var_x
SUB var_y
POS halt
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

#### z = x == y
```
; set true
GET num_1
SET var_z

; check false
GET var_x
SUB var_y
ZER halt
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

#### z = x != y
```
; set false
GET num_0
SET var_z

; check true
GET var_x
SUB var_y
ZER halt
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

; check_true
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

#### z = x > y
```
; set true
GET num_1
SET var_z

; check false
GET var_x
SUB var_y
POS halt
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

### Bitwise Examples

#### z = x & y
```
; Copy values

; Bit 15

; Bit 14

; Bit 13

; Bit 12

; Bit 11

; Bit 10

; Bit 9

; Bit 8

; Bit 7

; Bit 6

; Bit 5

; Bit 4

; Bit 3

; Bit 2

; Bit 1

; Bit 0


halt:
ANY halt

num_0:
0

num_1:
1

bit_x:
0

bit_y:
0

bit_z:
0

var_x:
7

var_y:
5

var_z:
0
```

### Assemply Stack Examples

#### push(x)
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store ST instruction with index address
LP ptrS
LA opS
S  save:

; set top of stack to x
LP varX
save:
0

; decrement stack pointer by 1
LP ptrS
LS val1
S  ptrS
H

opS:
0b1000000000000000

val1:
1

varX:
42

maxS:
0
0
topS:
0
21
ptrS:
topS
```

#### x = pop()
```
; increment stack pointer by 1
LP ptrS
LA val1
S  ptrS

; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store LD instruction with index address
LP ptrS
LA opLP
S  load:

; set x to top of stack
load:
0
S  varX
H

opLP:
0b0000000000000000

val1:
1

varX:
0

maxS:
0
topS:
0
42
21
ptrS:
topS
```

#### x = peek()
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store LD instruction with index address
LP ptrS
LA val1
LA opLP
S  load:

; set x to top of stack     
load:
0
S  varX
H

opLP:
0b0000000000000000

val1:
1

varX:
0

maxS:
0
topS:
0
42
21
ptrS:
topS
```




