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
             |          |
  _____ADDRESS          DATA________________
  |   ______ | ________ | __________     __|__
__|___|__  __|___|__  __|___|__    |     \___/--[~]
|  i p  |  |  i r  |  |  a c  |  __|__   __|__
|_______|  |_______|  |_______|  \    \_/    /__[++]  
    |          |          |       \_________/   
    |__________|__________|____________|

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

Name         |Behaviour                       |Machine Instruction|Assembly Instruction
-------------|--------------------------------|-------------------|--------------------
Load Positive|```ac <- +memory[address]```    |```000[address]``` |```LP [address]```
Load Negative|```ac <- -memory[address]```    |```001[address]``` |```LN [address]```
Load Add     |```ac <- ac + memory[address]```|```010[address]``` |```LA [address]```
Load Subtract|```ac <- ac - memory[address]```|```011[address]``` |```LS [address]```
Save         |```memory[address] <- ac```     |```100[address]``` |```S  [address]```
Jump Negative|```if(AC < 0) ip <- address```  |```101[address]``` |```JN [address]```
Jump Any     |```ip <- address```             |```110[address]``` |```JA [address]```
Halt         |```ip <- ip - 1```              |```111[ n / a ]``` |```H           ```

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
LP varX
LA val1
S  varX
H

val1:
1

varX:
4
```

#### x -= 1  
```
; decrement x by 1
LP varX
LS val1
S  varX
H

val1:
1

varX:
4
```

#### z = x + y
```
; set z to sum of x and y
LP varX
LA valY
S  varZ
H

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
LP varX
LS valY
S  varZ
H

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
LP ptrA
LA varI
LA opLP
S  load

; set j to ith element of a
load:
0
S  varJ

H

; load opcode
opLP:
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
LP ptrA
LA varI
LA opS
S  save

; set ith element of a to j
LP varJ
save:
0

H

; store opcode
opS:
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
; x is less then y
LP varX
LS varY
JN halt
LP false
S  varZ

halt:
H

false:
0

varX:
2

varY:
4

varZ:
1
```

#### z = x <= y
```
; x is less then or equal to y
LP varY
LS varX
JN halt
LP true
S  varZ

halt:
H

true:
1

varX:
2

varY:
4

varZ:
0
```

#### z = x == y //HERHEHRHEHREHRHEHRHEHRHEHREHHREH
```
; x is equal to y
LP varX
LS varY
JN halt
LP varY
LS varX
JN halt
LP true
S  varZ

halt:
H

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
; x is not equal to y
LP varX
LS varY
JN halt
LP varY
LS varX
JN halt
LP false
S  varZ

halt:
H

false:
0

varX:
2

varY:
4

varZ:
1
```

#### z = x >= y
```
; x is greater then or equal to y
LP varX
LS varY
JN halt
LP true
S  varZ

halt:
H

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
; x is greater then y
LP varY
LS varX
JN halt
LP false
S  varZ

halt:
H

false:
0

varX:
2

varY:
4

varZ:
1
```

## Assembly Control Flow Examples

#### if(X > 0) {x = 1} else if(X < 0) {x = -1}
```
; compare x to 0
LN varX
JN if
LP varX
JN elif
JA else

if:
LP var1
S  varX
JA else

elif:
LN var1
S  varX

else:
H

var1:
1

varX:
2
```

#### while(X > 0) {x--}
```
JA chec
loop:
LP varX
LS val1
S  varX
chec:
LN varX
JN loop
H

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




