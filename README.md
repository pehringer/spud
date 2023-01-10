# Minimal_CPU
A very simple CPU that resembles modern designs (register based / Von Neumann architecture) that is easy use and understand in its entirety.
## Datapath Diagram
```
   _________________________
  |                         |
  |                     ____|___
  |                    /        \                                                wrire memory
  |                   /   adder  \-CUO0                                         /
  |                  /     /\     \                                        CUO12
  |  CUI1-.         /_____/  \_____\                                             read memory
  |       |         |              |                                            /
  |  CUI2-|    __   ]|-CUO2        ]|-CUO1                                 CUO11
  |       |   /  |  |              |                                             memory address bus
  |  CUI3-|__sign|__|              |____________________________________________/
  |          \   |  |              |              |              |           |
  |  CUI0     \__|  |              ]|--CUO4       ]|-CUO6        ]|-CU08     ]|-CUO9
  |  |___________   |___________   |___________   |___________   |___________|
  |  |instruction|  |accumulator|  |program    |  |temporary  |  |operand    |
  |  |register   |  |register   |  |counter    |  |register   |  |register   |
  |  |           |  |           |  |register   |  |           |  |           |
  |  |___________|  |___________|  |___________|  |___________|  |___________|
  |  |           |  |           |  |           |  |           |  |           |
  |  |        CUO1  |        CU03  |        CU05  |        CU07  |       CUO10   memory data bus
  |__|______________|______________|______________|______________|______________/

CUI0 - control unit input opcode
CUI1 - control unit input accumulator zero
CUI2 - control unit input accumulator negative
CUI3 - control unit input accumulator positive
CUO0 - control unit output adder carry in
CUO1 - control unit output adder input
CUO2 - control unit output accumulator read
CUO3 - control unit output accumulator write
CUO4 - control unit output program counter read
CUO5 - control unit output program counter write
CUO6 - control unit output temporary read
CUO7 - control unit output temporary write
CUO8 - control unit output operand read
CUO9 - control unit output not operand read
CUO10 - control unit output operand write
CUO11 - control unit output memory read
CUO12 - control unit output memory write
```
