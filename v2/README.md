---

# Spud -> Simple Processor Unit Design.

A very simple processor that resembles modern designs. That is easy to use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Accumulator based machine.

---

# Hardware Diagram

```
DATA BUS 16-BITS
------------------------------------------------+----------------------------------------------+
ADDRESS BUS 13-BITS                             |                                              |
----+---------------------+                     |                                              |
    |                     |                     |                                              |
    |          +---------------------+---------------------+--------------------+              |
    |          |          |          |          |          |                    |              |
    |          |          |          |          |          |        |      |    |   |          |
+---Q---+  +---Q---+  +---Q---+  +---Q---+  +---Q---+  +---Q---+  +-N----P-+  +-A---B-+        |
|  AND  |  |  AND  |  |  AND  |  |  AND  |  |  AND  |  |  AND  |  |  SIGN  |  |  XOR  |        |
+-A---B-+  +-A---B-+  +-A---B-+  +-A---B-+  +-A---B-+  +-A---B-+  +-A------+  +---Q---+        |
  |   |      |   |      |   |      |   |      |   |      |   |      |             |            |
  |          |          |          |          |          |          |             |            |
  +----------+          +----------+          +----------+----------+             |            |
  |                     |                     |                                   |            |    |
+-Q----------------+  +-Q----------------+  +-Q----------------+                +-A------+   +-B----C-+
| [0-12]    13-BIT |  | [0-12]    16-BIT |  | [0-15]    16-BIT |                 \        \ / 16-BIT /
|        IP        |  |        IR        |  |        AC        |                  \        +        /
+-D--------------E-+  +-D--------------E-+  +-D -------------E-+                   +-------S-------+
 |               |      |              |      |              |                             |
 |                      |                     |                                            |
 +----------------------+---------------------+--------------------------------------------+
```

---

# Instruction Format

```
 opcode__   address_____________________ 
 15 14 13   12 11 10 9 8 7 6 5 4 3 2 1 0
```

**NOTE:** Instructions are stored in the IR register.

---

# Instruction Set

Name         |Behaviour                |Machine Instruction|Assembly Instruction  
-------------|-------------------------|-------------------|--------------------
Load         |AC = memory[address]     |```000[address]``` |```LD [address]```
Add          |AC = AC + memory[address]|```001[address]``` |```AD [address]```
Subtract     |AC = AC - memory[address]|```010[address]``` |```SB [address]```
Store        |memory[address] = AC     |```011[address]``` |```ST [address]```
Jump Negative|if(AC < 0) IP = address  |```100[address]``` |```JN [address]```
Jump Positive|if(AC > 0) IP = address  |```101[address]``` |```JP [address]```
Jump Zero    |if(AC == 0) IP = address |```110[address]``` |```JZ [address]```
Jump Any     |IP <- address            |```111[address]``` |```JA [address]```

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

; stop execution here
halt:
JA halt ;

; immediate value 1
val1:
1

; variable x
varX:
4
```

#### x -= 1  
```
; decrement x by 1
LD varX
SB val1
ST varX

; stop execution here
halt:
JA halt ;

; immediate value 1
val1:
1

; variable x
varX:
4
```

#### z = x + y
```
; set z to sum of x and y
LD varX
AD valY
ST varZ

; stop execution here
halt:
JA halt ;

; variable x
varX:
4

; variable y
varY:
8

; variable x
varZ:
0
```

#### Z = X - Y
```
; set z to difference of x and y
LD varX
AD valY
ST varZ

; stop execution here
halt:
JA halt ;

; variable x
varX:
4

; variable y
varY:
8

; variable x
varZ:
0
```
