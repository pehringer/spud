---
# Minimal_Computer

A very simple computer that resembles modern designs. That is easy use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Memory mapped peripherals.
 - Register based machine.

---
# Table of Contents

[Hardware Diagram](https://github.com/pehringer/Minimal_Computer/blob/main/README.md#hardware-diagram)  
[Hardware Workarounds](https://github.com/pehringer/Minimal_Computer/blob/main/README.md#hardware-workarounds)  
[Instruction Set](https://github.com/pehringer/Minimal_Computer/blob/main/README.md#instruction-set)  
[Assembly Code Examples](https://github.com/pehringer/Minimal_Computer/blob/main/README.md#assembly-code-examples)  

---
# Hardware Diagram

```
 _____________________________________________________________________________ 
|Control Unit                                                                 |
|_____________________________________________________________________________|
                           |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
                          /  /   Z  P  |  N  I  |  O  W  W  R  W  R  W  R  W  R
             Data Bus Read  /    o  o  |  e  n  |  p  r  r  e  r  e  r  e  r  e
                           /     r  s  |  g  p  |  c  i  i  a  i  a  i  a  i  a
             Data Bus Write      o  i  |  a  u  |  o  t  t  d  t  d  t  d  t  d
 _________________________          t  |  t  t  |  d  e  w  0  e  1  e  2  e  |
|                         |         i  |  i  0  |  e  0  1     2     3     4  N
|  .--Zero           _____|____     v  |  v     |                             o
|  |                /Adder Unit\    e  |  e     |                             t
|  |--Positive     /            \______|        |
|  |              /      /\      \ Carry In     |
|  |--Negative   /______/  \______\             |
|  |              |              |    __________|
|  |         __   ]|--Input0     ]|--' Input1
|  |        /  |  |              |
|  |_______Sign|__|              |____________________________________________
|          \   |  |              |              |              |     Read  |  |
|  Opcode   \__|  |      Read0--|[      Read1--|[      Read2--|[     Not--|[  |
|  |___________   |___________   |___________   |___________   |___________|  |
|  |Instruction|  |Accumulator|  |Program    |  |Temporary  |  |Operand    |  |
|  |Register   |  |Register   |  |Counter    |  |Register   |  |Register   |  |
|  |           |  |           |  |Register   |  |           |  |           |  |
|  |___________|  |___________|  |___________|  |___________|  |___________|  |
|  |           |  |           |  |           |  |           |  |           |  |
|  |      Write0  |      Write1  |      Write2  |      Write3  |      Write4  |
|__|______________|______________|______________|______________|              |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|   _______________________________________________________________________   |
|__|Memory Unit                                    Address Range: 0 - 65499|__|
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|  |_______________________________________________________________________|  |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|                                                                             |
|   _______________________________________________________________________   |
|  |Input Unit                                                             |  |
|  |_______________________________________________________________________|  |
|__|Input Register                                           Address: 65500|__|
|  |_______________________________________________________________________|  |
|                                                                             |
|   _______________________________________________________________________   |
|  |Output Unit                                                            |  |
|  |_______________________________________________________________________|  |
|__|Output Register                                          Address: 65501|__|
|  |_______________________________________________________________________|  |
|                                                                             |
|                                                                             |
Data Bus                                                            Address Bus
```

---
# Hardware Workarounds

### Subtraction Operations

The computer lacks a subtractor unit, so how then does the computer support subtraction operations? The computer simply makes the right operand negative and then adds it to the left operand:  

```left - right  --->  left + (-right)```

To get the twos compliments of a binary number (negative version of the number) two steps are required in the following order:

1) Bitwise not the number (use operand registers ```Read Not```).
2) Increment the number by one (use adders carry in).

So to subtract the computer does the following:  

```accumulator_register + (~operand_register) + 1```

### Stack Operations

The computer lacks a stack pointer register, so how then does the computer support stack operations? The computer simply stores the stack pointer in memory and loads it in when need. So to push a variable onto the stack the computer does the following:

```VAR``` - Address of variable.  
```STK_PTR``` - Address of stack pointer.  

```
LOAD_A VAR
SWAP
LOAD_A STK_PTR
SAVE
SWAP
LOAD_I 1
SUB
SAVE_A STK_PTR
```

---
# Instruction Set

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|---------------------------------------------------------------------------------------------------------------------------
```0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand_register = memory[program_counter_register++]```
```1```             |```LOAD```             |Load          |```operand_register = memory[operand_register]```
```2 [ADDRESS]```   |```LOAD_A [ADDRESS]``` |Load Address  |```operand_register = memory[memory[program_counter_register++]]```
```3```             |```SWAP```             |Swap          |```accumulator_register <=> operand_register```
```4```             |```ADD```              |Add           |```accumulator_register += operand_register```
```5```             |```SUB```              |Subtract      |```accumulator_register -= operand_register```
```6```             |```SAVE```             |Save Operand  |```memory[operand_register] = accumulator_register```
```7 [ADDRESS]```   |```SAVE_A [ADDRESS]``` |Save Address  |```memory[memory[program_counter_register++]] = accumulator_register```
```8```             |```JUMP```             |Jump          |```program_counter_register = memory[operand_register]```
```9 [ADDRESS]```   |```JUMP_A [ADDRESS]``` |Jump Any      |```program_counter_register = memory[program_counter]```
```10 [ADDRESS]```   |```JUMP_Z [ADDRESS]``` |Jump Zero     |```program_counter_register = accumulator_register == 0 ? memory[program_counter_register] : ++program_counter_register```
```11 [ADDRESS]```   |```JUMP_N [ADDRESS]``` |Jump Negative |```program_counter_register = accumulator_register < 0 ? memory[program_counter_register] : ++program_counter_register```
```12 [ADDRESS]```   |```JUMP_P [ADDRESS]``` |Jump Positive |```program_counter_register = accumulator_register > 0 ? memory[program_counter_register] : ++program_counter_register```
```13```             |```HALT```             |Halt          |```exit()```

### Reduced Instruction Set (Not Used)

It is possible to further simplify the instruction set down to 8 instructions. However this impacts code density. Note that the conditional jumps now use the operand register instead of immediate values.

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|----------------------------------------------------------------------------------------------------------
```0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand_register = memory[program_counter_register++]```
```1```             |```LOAD```             |Load          |```operand_register = memory[operand_register]```
```2```             |```SWAP```             |Swap          |```accumulator_register <=> operand_register```
```3```             |```ADD```              |Add           |```accumulator_register += operand_register```
```4```             |```SUB```              |Subtract      |```accumulator_register -= operand_register```
```5```             |```SAVE```             |Save          |```memory[operand_register] = accumulator_register```
```6```             |```JUMP_N```           |Jump Negative |```program_counter_register = accumulator_register < 0 ? operand_register : ++program_counter_register```
```7```             |```JUMP_P```           |Jump Positive |```program_counter_register = accumulator_register > 0 ? operand_register : ++program_counter_register```

---
# Assembly Code Examples

When using the instruction set it is useful to keep in mind how data is moved around and used.

- Values are loaded into the operand and program counter registers.
- Values are strore from the accumulator register.
- Arithmetic operations use the accumulator and operand registers.
- Result of arithmetic operations are stored in the accumulator register.
- Values can be swapped between the accumulator and operand registers.
- Conditional jumps use the accumulator registers as the condition.

Keep the below diagram in mind when using the instruction set.

```
 _____________________________________________________
| Memory/Input/Output Unit                            |
|_____________________________________________________|
     __             __
    |  |           |  |                        /\
   _|  |_         _|  |_                      /  \
   \    /         \    /                     /_  _\
    \  /           \  /                       |  |
     \/             \/                        |__|
 ___________    ___________                ___________
|Program    |  |Operand    |   /|____|\   |Accumulator|
|Counter    |  |Register   |  /        \  |Register   |
|Register   |  |           |  \  ____  /  |           |
|___________|  |___________|   \|    |/   |___________|
```

### X += 1

```VAR_X``` - Address of variable X.  

```
LOAD_A VAR_X
SWAP
LOAD_I 1
ADD
SAVE_A VAR_X
```

### X = Y - Z

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  
```VAR_Z``` - Address of variable Z.  

```
LOAD_A VAR_Y
SWAP
LOAD_A VAR_Z
SUB
SAVE_A VAR_X
```

### X = A[Y]

```ARRAY``` - Address of first array element.  
```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
LOAD_I ARRAY
SWAP
LOAD_A VAR_Y
ADD
SWAP
LOAD
SWAP
SAVE_A VAR_X
```

### IF(X < Y)

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
IF: LOAD_A VAR_X
    SWAP
    LOAD_A VAR_Y
    SUB
    JUMP_Z END_IF
    JUMP_P END_IF
  
    ; Conditional code here.
  
END_IF:
```

### IF(X <= Y)

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
IF: LOAD_A VAR_X
    SWAP
    LOAD_A VAR_Y
    SUB
    JUMP_P END_IF

    ; Conditional code here.

END_IF:
```

### IF(X == Y)

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
IF: LOAD_A VAR_X
    SWAP
    LOAD_A VAR_Y
    SUB
    JUMP_N END_IF
    JUMP_P END_IF

    ; Conditional code here.
  
END_IF:
```

### IF(X != y)

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
IF: LOAD_A VAR_X
    SWAP
    LOAD_A VAR_Y
    SUB
    JUMP_Z END_IF

    ; Conditional code here.
  
END_IF:
```

### IF(X >= Y)

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
IF: LOAD_A VAR_X
    SWAP
    LOAD_A VAR_Y
    SUB
    JUMP_N END_IF

    ; Conditional code here.
  
END_IF:
```

### IF(X > Y)

```VAR_X``` - Address of variable X.  
```VAR_Y``` - Address of variable Y.  

```
IF: LOAD_A VAR_X
    SWAP
    LOAD_A VAR_Y
    SUB
    JUMP_N END_IF
    JUMP_Z END_IF

    ; Conditional code here.
  
END_IF:
```

### WHILE(X != 0)

```VAR_X``` - Address of variable X.  

```
WHILE: LOAD_A VAR_X
       SWAP
       JUMP_Z END

       ; Conditional code here.

       JUMP_A WHILE
END_WHILE:
```

### PUSH(X)

```VAR_X``` - Address of variable X.  
```STK_PTR``` - Address of stack pointer.  

```
LOAD_A VAR_X
SWAP
LOAD_A STK_PTR
SAVE
SWAP
LOAD_I 1
SUB
SAVE_A STK_PTR
```

### X = PEEK()

```VAR_X``` - Address of variable X.  
```STK_PTR``` - Address of stack pointer.  

```
LOAD_A STK_PTR
SWAP
LOAD_I 1
ADD
SWAP
LOAD
SWAP
SAVE_A VAR_X
```

### X = POP()

```VAR_X``` - Address of variable X.  
```STK_PTR``` - Address of stack pointer.  

```
LOAD_A STK_PTR
SWAP
LOAD_I 1
ADD
SAVE_A STK_PTR
SWAP
LOAD
SWAP
SAVE_A VAR_X
```

---
# That is All... For Now!!!
