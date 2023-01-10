# Minimal_CPU
A very simple CPU that resembles modern designs (register based / Von Neumann architecture) that is easy use and understand in its entirety.
## Datapath Diagram
```
   _________________________
  |                         |
  |                     ____|___
  |                    /        \                                                wrire memory
  |                   /   adder  \-carry in                                   __/
  |                  /     /\     \
  |  (0) -.         /_____/  \_____\                                             read memory
  |       |         |              |                                          __/
  |  (-) -|    __   ]|-use input   ]|-use input
  |       |   /  |  |              |                                             memory address bus
  |  (+) -|__sign|__|              |____________________________________________/
  |          \   |  |              |              |              |           |
  |  opcode   \__|  |              ]|-read        ]|-read        ]|-read     ]|-read
  |  |___________   |___________   |___________   |___________   |___________|
  |  |instruction|  |accumulator|  |program    |  |temporary  |  |operand    |
  |  |register   |  |register   |  |counter    |  |register   |  |register   |
  |  |           |  |           |  |register   |  |           |  |           |
  |  |___________|  |___________|  |___________|  |___________|  |___________|
  |  |           |  |           |  |           |  |           |  |           |
  |  |       write  |       write  |       write  |       write  |       write   memory data bus
  |__|______________|______________|______________|______________|______________/
  
```
