---
# Minimal_Computer

A very simple computer that resembles modern designs. That is easy use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Memory mapped peripherals.
 - Register based instructions.

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
|  |                /Arithmetic\    e  |  e     |                             t
|  |--Positive     /Addition    \______|        |
|  |              /Unit  /\      \ Carry In     |
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
# Instruction Set Examples

When using the instruction set it is useful to keep in mind how data is moved around and used

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

### ++X

Given:

- ```X_ADDRESS``` - Address of variable X.

```
LOAD_A X_ADDRESS    ;Load X
SWAP
LOAD_I 1
ADD
SAVE_A X
```

### X = Y + Z

### Y = ARRAY[X]

### IF X < Y

### IF(X <= Y)

### IF(X == Y)

### IF(X != y)

### IF(X >= Y)

### IF(X > Y)

### PUSH(X)

### PEEK()

### X = POP()

