# Minimal_Computer

A very simple computer that resembles modern designs. That is easy use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Memory mapped peripherals.
 - Register based instructions.

## System Hardware Diagram

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

## Processor Instruction Set

Instruction Set Rules of Thumb
- Instructions with letter abbreviation endings are operations involving immediate values.
- Instructions without letter abbreviation endings are operations involving the operand register (except for HALT).
- Values are loaded into the operand and program counter registers.
- Values are strore from the accumulator register.
- Arithmetic operations use the accumulator and operand registers.
- Result of arithmetic operations are stored in the accumulator register.
- Values can be swapped between the accumulator and operand registers.
- Conditional jumps use the accumulator registers as the condition.

Instruction Set Data Flow Diagram
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

Instruction Set

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|----------------------------------------------------------------------------------------------------------------------------
```0x0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand_register = memory[program_counter_register++]```
```0x1```             |```LOAD```             |Load          |```operand_register = memory[operand_register]```
```0x2 [ADDRESS]```   |```LOAD_A [ADDRESS]``` |Load Address  |```operand_register = memory[memory[program_counter_register++]]```
```0x3```             |```SWAP```             |Swap          |```accumulator_register <=> operand_register```
```0x4```             |```ADD```              |Add           |```accumulator_register += operand_register```
```0x5```             |```SUB```              |Subtract      |```accumulator_register -= operand_register```
```0x6```             |```SAVE```             |Save Operand  |```memory[operand_register] = accumulator_register```
```0x7 [ADDRESS]```   |```SAVE_A [ADDRESS]``` |Save Address  |```memory[memory[program_counter_register++]] = accumulator_register```
```0x8```             |```JUMP```             |Jump          |```program_counter_register = memory[operand_register]```
```0x9 [ADDRESS]```   |```JUMP_A [ADDRESS]``` |Jump Any      |```program_counter_register = memory[program_counter]```
```0xA [ADDRESS]```   |```JUMP_Z [ADDRESS]``` |Jump Zero     |```program_counter_register = accumulator_register == 0 ? memory[program_counter_register] : ++program_counter_register```
```0xB [ADDRESS]```   |```JUMP_N [ADDRESS]``` |Jump Negative |```program_counter_register = accumulator_register < 0 ? memory[program_counter_register] : ++program_counter_register```
```0xC [ADDRESS]```   |```JUMP_P [ADDRESS]``` |Jump Positive |```program_counter_register = accumulator_register > 0 ? memory[program_counter_register] : ++program_counter_register```
```0xD```             |```HALT```             |Halt          |```exit()```

## Processor Reduced Instruction Set (Not Used)

It is possible to further simplify the instruction set down to 8 instructions. However this impacts code density. Note that the conditional jumps now use the operand register instead of immediate values.

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|-----------------------------------------------------------------------------------------------------------
```0x0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand_register = memory[program_counter_register++]```
```0x1```             |```LOAD```             |Load          |```operand_register = memory[operand_register]```
```0x2```             |```SWAP```             |Swap          |```accumulator_register <=> operand_register```
```0x3```             |```ADD```              |Add           |```accumulator_register += operand_register```
```0x4```             |```SUB```              |Subtract      |```accumulator_register -= operand_register```
```0x5```             |```SAVE```             |Save          |```memory[operand_register] = accumulator_register```
```0x6```             |```JUMP_N```           |Jump Negative |```program_counter_register = accumulator_register < 0 ? operand_register : ++program_counter_register```
```0x7```             |```JUMP_P```           |Jump Positive |```program_counter_register = accumulator_register > 0 ? operand_register : ++program_counter_register```

## Processor Instruction Examples

#### LOAD_I

#### LOAD

#### LOAD_A

#### SWAP

#### ADD

#### SUB

#### SAVE

#### SAVE_A

#### JUMP

#### JUMP_A

#### JUMP_Z

#### JUMP_N

#### JUMP_P

#### HALT
