# Minimal_CPU
A very simple CPU that resembles modern designs (register based / Von Neumann architecture) that is easy use and understand in its entirety.
## Diagrams
###### System Diagram
```
 ___________________________
|Central Processing Unit    |
|   _____________________   |
|  |Control Unit         |  |
|  |_____________________|  |
|   _____________________   |
|  |Datapath             |  |
|  |   _______________   |  |
|  |  |Arithmetic Unit|  |  |
|  |  |_______________|  |  |
|  |   _______________   |  |
|  |  |Registers      |  |  |
|  |  |_______________|  |  |   ___________    __________________________
|  |_____________________|  |  |Memory Unit|  |Memory Mapped Peripherals|
|___________________________|  |___________|  |_________________________|
            |   |                  |   |                 |   |
            |   |__________________|   |_________________|   |
            |Memory Data Bus / Memory Address Bus            |
            |________________________________________________|
```
###### Datapath Diagram
```
   _________________________
  |                         |
  |                    _____|____
  |                   /Arithmetic\                                               Memory Write
  |                  / Unit       \--Carry In (++)                          ____/
  |                 /      /\      \
  |  (0)--.        /______/  \______\                                            Memory Read
  |       |         |              |                                        ____/
  |  (-)--|    __   ]|--Use Input  ]|--Use Input
  |       |   /  |  |              |                                             Memory Address Bus
  |  (+)--|__Sign|__|              |____________________________________________/
  |          \   |  |              |              |              |           |
  |  Opcode   \__|  |              ]|--Read       ]|--Read       ]|--Read    ]|--Read Not (~)
  |  |___________   |___________   |___________   |___________   |___________|
  |  |Instruction|  |Accumulator|  |Program    |  |Temporary  |  |Operand    |
  |  |Register   |  |Register   |  |Counter    |  |Register   |  |Register   |
  |  |           |  |           |  |Register   |  |           |  |           |
  |  |___________|  |___________|  |___________|  |___________|  |___________|
  |  |           |  |           |  |           |  |           |  |           |
  |  |       Write  |       Write  |       Write  |       Write  |       Write   Memory Data Bus
  |__|______________|______________|______________|______________|______________/
  
```
## Instruction Set
###### 4-Bit Opcode Instruction Set
Machine Representation|Assembly Representation| Name     |Behaviour
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
Machine Representation|Assembly Representation| Name     |Behaviour
----------------------|-----------------------|--------------|----------------------------------------------------------------------------------------
```0x0 [VALUE]```     |```LOAD_I [VALUE]```   |Load Immediate|```operand = memory[program_counter++]```
```0x1```             |```LOAD```             |Load          |```operand = memory[operand]```
```0x2```             |```SWAP```             |Swap          |```accumulator <=> operand```
```0x3```             |```ADD```              |Add           |```accumulator += operand```
```0x4```             |```SUB```              |Subtract      |```accumulator -= operand```
```0x5```             |```SAVE```             |Save          |```memory[operand] = accumulator```
```0x6```             |```JUMP_N```           |Jump Negative |```program_counter = accumulator < 0 ? operand : program_counter + 1```
```0x7```             |```JUMP_P```           |Jump Positive |```program_counter = accumulator > 0 ? operand : program_counter + 1```
