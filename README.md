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
|  |  |_______________|  |  |
|  |_____________________|  |
|___________________________|

        ||         /\
       _||_       /__\
       \  /        ||
        \/         ||
 ___________________________
|Memory Unit                |
|___________________________|
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
Opcode|Assembly              |Name                         |Behaviour Pseudocode
------|----------------------|-----------------------------|----------------------------------------------------------------------------------------
0x0   |```LOAD_V [VALUE]```  |Load Value                   |```operand = memory[program_counter++]```
0x1   |```LOAD```            |Load Operand                 |```operand = memory[operand]```
0x2   |```LOAD_I [ADDRESS]```|Load Immediate               |```operand = memory[memory[program_counter++]]```
0x3   |```SWAP```            |Accumulator Swap Operand     |```accumulator <=> operand```
0x4   |```ADD```             |Accumulator Add Operand      |```accumulator += operand```
0x5   |```SUB```             |Accumulator Subtract Operand |```accumulator -= operand```
0x6   |```SAVE```            |Save Operand                 |```memory[operand] = accumulator```
0x7   |```SAVE_I [ADDRESS]```|Save Immediate               |```memory[memory[program_counter++]] = accumulator```
0x8   |```JUMP```            |Jump                         |```program_counter = operand```
0x9   |```JUMP_Z [ADDRESS]```|Jump If Accumulator Zero     |```program_counter = accumulator == 0 ? memory[program_counter] : program_counter + 1```
0xA   |```JUMP_N [ADDRESS]```|Jump If Accumulator Negative |```program_counter = accumulator < 0 ? memory[program_counter] : program_counter + 1```
0xB   |```JUMP_P [ADDRESS]```|Jump If Accumulator Positive |```program_counter = accumulator > 0 ? memory[program_counter] : program_counter + 1```
0xC   |```INPUT```           |Input                        |```operand = input()```
0xD   |```OUTPUT```          |Output                       |```print(operand)```
0xE   |```HALT```            |Halt                         |```exit(opcode)```

