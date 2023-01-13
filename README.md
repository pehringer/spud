# Minimal_CPU
A very simple CPU that resembles modern designs (register based / Von Neumann architecture) that is easy use and understand in its entirety.

## System Diagram
```
   ___________________________________________________________________________________
  |Control Unit                                                                       |
  |___________________________________________________________________________________|
                                   |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |  |
                                   Z  P  |  N  I  |  O  W  W  R  W  R  W  R  W  R  W  R
                                   e  o  |  e  n  |  p  r  r  e  r  e  r  e  r  e  r  e
                                   r  s  |  g  p  |  c  i  i  a  i  a  i  a  i  a  i  a
                                   o  i  |  a  u  |  o  t  t  d  t  d  t  d  t  d  t  d
   _________________________          t  |  t  t  |  d  e  w  0  e  1  e  2  e  |  e  |
  |                         |         i  |  i  0  |  e  0  1     2     3     4  N  |  M
  |  .--Zero           _____|____     v  |  v     |                             o  M  e
  |  |                /Arithmetic\    e  |  e     |                             t  e  m
  |  |--Positive     /Addition    \______|        |                                m  o
  |  |              /Unit  /\      \ Carry In     |                                o  r
  |  |--Negative   /______/  \______\             |                                r  y
  |  |              |              |    __________|                                y
  |  |         __   ]|--Input0     ]|--' Input1
  |  |        /  |  |              |
  |  |_______Sign|__|              |____________________________________________
  |          \   |  |              |              |              |     Read  |  |
  |  Opcode   \__|  |      Read0--|[      Read1--|[      Read2--|[     Not--|[  |
  |  |___________   |___________   |___________   |___________   |___________|  |
  |  |Instruction|  |Accumulator|  |Program    |  |Temporary  |  |Operand    |  |
M |  |Register   |  |Register   |  |Counter    |  |Register   |  |Register   |  | M
e |  |           |  |           |  |Register   |  |           |  |           |  | e
m |  |___________|  |___________|  |___________|  |___________|  |___________|  | m
o |  |           |  |           |  |           |  |           |  |           |  | o
r |  |      Write0  |      Write1  |      Write2  |      Write3  |      Write4  | r
y |__|______________|______________|______________|______________|              | y
  |                                                                             |
D |                                                                             | A
a |                                                                             | d
t |   _______________________________________________________________________   | d
a |__|Memory Unit                                                            |__| r
  |  |_______________________________________________________________________|  | e
B |                                                                             | s
u |                                                                             | s
s |                                                                             |
  |   _______________________________________________________________________   | B
  |__|Memory Mapped Peripheral - Terminal Input                              |__| u
  |  |_______________________________________________________________________|  | s
  |                                                                             |
  |                                                                             |
  |                                                                             |
  |   _______________________________________________________________________   |
  |__|Memory Mapped Peripheral - Terminal Output                             |__|
     |_______________________________________________________________________|
```

## Instruction Set

###### Rules of Thumb
- Instructions with letter abbreviation endings are operations involving immediate values.
- Instructions without letter abbreviation endings are operations involving the operand register.
- Values are loaded to the operand register.
- Values are strore fron the accumulator register.
- Arithmetic operations use the accumulator and operand registers.
- Result of arithmetic operations are stored in the accumulator register.
- Values can be swapped between the accumulator and operand registers.
- Conditional jumps use the accumulator register as the condition.

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|----------------------------------------------------------------------------------------
```0x0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand = memory[program_counter++]```
```0x1```             |```LOAD```             |Load          |```operand = memory[operand]```
```0x2 [ADDRESS]```   |```LOAD_A [ADDRESS]``` |Load Address  |```operand = memory[memory[program_counter++]]```
```0x3```             |```SWAP```             |Swap          |```accumulator <=> operand```
```0x4```             |```ADD```              |Add           |```accumulator += operand```
```0x5```             |```SUB```              |Subtract      |```accumulator -= operand```
```0x6```             |```SAVE```             |Save Operand  |```memory[operand] = accumulator```
```0x7 [ADDRESS]```   |```SAVE_A [ADDRESS]``` |Save Address  |```memory[memory[program_counter++]] = accumulator```
```0x8```             |```JUMP```             |Jump          |```program_counter = memory[operand]```
```0x9 [ADDRESS]```   |```JUMP_A [ADDRESS]``` |Jump Address  |```program_counter = memory[program_counter]```
```0xA [ADDRESS]```   |```JUMP_Z [ADDRESS]``` |Jump Zero     |```program_counter = accumulator == 0 ? memory[program_counter] : program_counter + 1```
```0xB [ADDRESS]```   |```JUMP_N [ADDRESS]``` |Jump Negative |```program_counter = accumulator < 0 ? memory[program_counter] : program_counter + 1```
```0xC [ADDRESS]```   |```JUMP_P [ADDRESS]``` |Jump Positive |```program_counter = accumulator > 0 ? memory[program_counter] : program_counter + 1```
```0xD```             |```HALT```             |Halt          |```exit(opcode)```
```0xE```             |                       |**RESERVED**  |
```0xF```             |                       |**RESERVED**  |

###### Reduced 3-Bit Opcode Instruction Set

It is possible to further simplify the instruction set down to 8 instructions. However this impacts code density
- *NOTE*: conditional jumps now use the operand register instead of immediate values.

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|----------------------------------------------------------------------------------------
```0x0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand = memory[program_counter++]```
```0x1```             |```LOAD```             |Load          |```operand = memory[operand]```
```0x2```             |```SWAP```             |Swap          |```accumulator <=> operand```
```0x3```             |```ADD```              |Add           |```accumulator += operand```
```0x4```             |```SUB```              |Subtract      |```accumulator -= operand```
```0x5```             |```SAVE```             |Save          |```memory[operand] = accumulator```
```0x6```             |```JUMP_N```           |Jump Negative |```program_counter = accumulator < 0 ? operand : program_counter + 1```
```0x7```             |```JUMP_P```           |Jump Positive |```program_counter = accumulator > 0 ? operand : program_counter + 1```
