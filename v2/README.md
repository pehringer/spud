---

# Spud -> Simple Processor Unit Design.

A very simple processor that resembles modern designs. That is easy to use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Accumulator based machine.

---

# Hardware Diagram

```
DATA_READ    <---  ---[6]

DATA_WTITE   <---  ---[7]

DATA_BUS     <-->  ----------------------------------+----------------+
16 BIT                                               |                |
                                                     |                |
ADDRESS_BUS  <---  --+---------------+               |                |
13 LSB               |               |               |    READ_BUS    |
                     |               |               |    (16 BIT)    |
             +---------------+---------------+--------------------+   |
             |       |       |       |       |       |            |   |
             |       |       |       |       |       |     [13]   |   |  [8]
             |       |       |       |       |       |       |    |   |   |
           +-Q-+   +-Q-+   +-Q-+   +-Q-+   +-Q-+   +-Q-+   +-Q-+  |   A---B
           |AND|   |AND|   |AND|   |AND|   |AND|   |AND|   |OR |  |   |XOR|
           A---B   A---B   A---B   A---B   A---B   A---B   +-A-+  |   +-Q-+
           |   |   |   |   |   |   |   |   |   |   |   |     |    |     |
           |  [0]  |  [1]  |  [2]  |  [3]  |  [4]  |  [5]    |    |     | OPERAND_BUS
           |       |       |       |       |       |         |    |     | (16 BIT)
           +-------+       +-------+       +-------+---------+    |     |
           |               |               |                      |     |
           |     [15-17]---+        [14]---+                      |     |  [9]
           |               |               |                      |     |   |
     +-----Q-----+   +-----Q-----+   +-----Q-----+              +-A-+   B---C
     |IP  D_LATCH|   |IR  D_LATCH|   |AC  D_LATCH|               \   \ /   /
     D-----------E   D-----------E   D-----------E                +---S---+
     |           |   |           |   |           |                    |
     |         [12]  |         [11]  |         [10]        WRITE_BUS  |
     |               |               |                     (16 BIT)   |
     +---------------+---------------+--------------------------------+
```
**Control Bus:**
Bit(s)|Behaviour
------|--------------------------------------
0     |```READ_BUS <- IP```
1     |```ADDRESS_BUS <- IP```
2     |```READ_BUS <- IR```
3     |```ADDRESS_BUS <- IR```
4     |```READ_BUS <- AC```
5     |```DATA_BUS <- AC```
6     |```DATA_READ```
7     |```DATA_WRITE```
8     |```DATA_BUS <- ~DATA_BUS```
9     |```DATA_BUS <- DATA_BUS + 1```
10    |```AC <- WRITE_BUS```
11    |```IR <- WRITE_BUS```
12    |```IP <- WRITE_BUS```
13    |```AC != 0```
14    |```AC < 0 (1 MSB)```
15-17 |```OPCODE (3 MSB)```

---

# Instruction Format

```
 opcode__   address_____________________ 
 15 14 13   12 11 10 9 8 7 6 5 4 3 2 1 0
```

**NOTE:** Instructions are stored in the IR register.

---

# Instruction Set

Name         |Behaviour                       |Machine Instruction|Assembly Instruction
-------------|--------------------------------|-------------------|--------------------
Load         |```AC <- memory[address]```     |```000[address]``` |```LD [address]```
Add          |```AC <- AC + memory[address]```|```001[address]``` |```AD [address]```
Subtract     |```AC <- AC - memory[address]```|```010[address]``` |```SB [address]```
Store        |```memory[address] <- AC```     |```011[address]``` |```ST [address]```
Jump Negative|```if(AC < 0) IP <- address```  |```100[address]``` |```JN [address]```
Jump Positive|```if(AC > 0) IP <- address```  |```101[address]``` |```JP [address]```
Jump Zero    |```if(AC == 0) IP <- address``` |```110[address]``` |```JZ [address]```
Jump Any     |```IP <- address```             |```111[address]``` |```JA [address]```

**NOTE:** Only Load, Subtract, Store, and Jump Negative are needed to be turing complete.

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
; increment x by 1
LD varX
AD val1
ST varX

halt:
JA halt

val1:
1

varX:
4
```

#### x -= 1  
```
; decrement x by 1
LD varX
SB val1
ST varX

halt:
JA halt

val1:
1

varX:
4
```

#### z = x + y
```
; set z to sum of x and y
LD varX
AD valY
ST varZ

halt:
JA halt

varX:
4

varY:
8

varZ:
0
```

#### Z = X - Y
```
; set z to difference of x and y
LD varX
AD valY
ST varZ

halt:
JA halt

varX:
4

varY:
8

varZ:
0
```

### Assembly Array Examples

#### j = a[i]
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store LD instruction with index address
LD ptrA
AD varI
AD opLD
ST load

; set j to ith element of a
load:
0
ST varJ

halt:
JA halt

; load opcode
opLD:
0b0000000000000000

varI:
2

varJ:
0

varA:
1
2
4
8
ptrA:
varA
```

#### a[i] = j
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store ST instruction with index address
LD ptrA
AD varI
AD opST
ST save

; set ith element of a to j
LD varJ
save:
0

halt:
JA halt

; store opcode
opST:
0b0110000000000000

varI:
2

varJ:
0

varA:
1
2
4
8
ptrA:
varA
```

### Assembly Comparison Examples

#### z = x < y
```
; compare x to y
LD varX
SB varY

; x is less then y
JZ halt
JP halt
LD true
ST varZ

halt:
JA halt

true:
1

varX:
2

varY:
4

varZ:
0
```

#### z = x <= y
```
; compare x to y
LD varX
SB varY

; x is less then or equal to y
JP halt
LD true
ST varZ

halt:
JA halt

true:
1

varX:
2

varY:
4

varZ:
0
```

#### z = x == y
```
; compare x to y
LD varX
SB varY

; x is equal to y
JN halt
JP halt
LD true
ST varZ

halt:
JA halt

true:
1

varX:
2

varY:
4

varZ:
0
```

#### z = x != y
```
; compare x to y
LD varX
SB varY

; x is not equal to y
JZ halt
LD true
ST varZ

halt:
JA halt

true:
1

varX:
2

varY:
4

varZ:
0
```

#### z = x >= y
```
; compare x to y
LD varX
SB varY

; x is greater then or equal to y
JN halt
LD true
ST varZ

halt:
JA halt

true:
1

varX:
2

varY:
4

varZ:
0
```

#### z = x > y
```
; compare x to y
LD varX
SB varY

; x is greater then y
JN halt
JZ halt
LD true
ST varZ

halt:
JA halt

true:
1

varX:
2

varY:
4

varZ:
0
```

## Assembly Control Flow Examples

#### if(X > 0) {} else if(X < 0) {} else {}
```
if:
LD varX
JN elif
JZ elif
;
; ... 
;
JA halt

elif:
JZ else
;
; ...
;
JA halt

else:
;
; ...
;

halt:
JA halt

varX:
2
```

#### while(X-- > 0) {}
```
loop:
LD varX
JN halt
JZ halt
SB val1
ST varX
;
; ...
;
JUMP_A loop
  
halt:
JA halt 

val1:
1

varX:
10
```

## Assemply Stack Examples

#### push(x)
```
; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store ST instruction with index address
LD ptrS
AD opST
ST save:

; set top of stack to x
LD varX
save:
0

; decrement stack pointer by 1
LD ptrS
SB val1
ST ptrS

halt:
JA halt

opST:
0b0110000000000000

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
LD ptrS
AD val1
ST ptrS

; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store LD instruction with index address
LD ptrS
AD opLD
ST load:

; set x to top of stack
load:
0
ST varX

halt:
JA halt

opLD:
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
LD ptrS
AD val1
AD opLD
ST load:

; set x to top of stack     
load:
0
ST varX

halt:
JA halt

opLD:
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




