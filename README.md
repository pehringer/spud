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
Opcode|Assembly            |Name                         |Behaviour Pseudocode
------|--------------------|-----------------------------|--------------------------------------------------------
0x0   |```LOAD_I [VALUE]```|Load Immediate Value         |```operand = memory[program_counter++]```
0x1   |```LOAD```          |Load Operand                 |```operand = memory[operand]```
0x2   |```SWAP```          |Accumulator Swap Operand     |```accumulator <=> operand```
0x3   |```ADD```           |Accumulator Add Operand      |```accumulator += operand```
0x4   |```SUB```           |Accumulator subtract Operand |```accumulator -= operand```
0x5   |```SAVE```          |Save Accumulator             |```memory[operand] = accumulator```
0x6   |```JUMP```          |Jump                         |```program_counter = operand```
0x7   |```JUMP_Z```        |Jump If Accumulator Zero     |```if accumulator == 0 then program_counter = operand```
0x8   |```JUMP_N```        |Jump If Accumulator Negative |```if accumulator < 0 then program_counter = operand```
0x9   |```JUMP_P```        |Jump If Accumulator Positive |```if accumulator > 0 then program_counter = operand```
0xA   |```HALT```          |Halt                         |```exit```
0xB   |```GET_N```         |Get Number                   |```operand = input()```
0xC   |```GET_C```         |Get Character                |```operand = input()```
0xD   |```PUT_N```         |Put Number                   |```print(operand)```
0xE   |```PUT_C```         |Put Character                |```print(operand)```
0xF   | **N/A**            | **RESERVED**                | **N/A**

