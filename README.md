# Minimal_CPU
A very simple CPU that resembles modern designs (register based / Von Neumann architecture) that is easy use and understand in its entirety.


### System Diagram
```
 ___________________________
|central processing unit    |
|   _____________________   |
|  |control unit         |  |
|  |_____________________|  |
|   _____________________   |
|  |datapath             |  |
|  |   _______________   |  |
|  |  |arithmetic unit|  |  |
|  |  |_______________|  |  |
|  |   _______________   |  |
|  |  |registers      |  |  |
|  |  |_______________|  |  |
|  |_____________________|  |
|___________________________|

        ||         /\
       _||_       /__\
       \  /        ||
        \/         ||
 ___________________________
|memory unit                |
|___________________________|
```

### Datapath Diagram
```
   _________________________
  |                         |
  |                    _____|____
  |                   /arithmetic\                                                write memory
  |                  / unit       \--carry in (++)                             __/
  |                 /      /\      \
  |  (0)--.        /______/  \______\                                            read memory
  |       |         |              |                                          __/
  |  (-)--|    __   ]|--use input  ]|--use input
  |       |   /  |  |              |                                             memory address bus
  |  (+)--|__sign|__|              |____________________________________________/
  |          \   |  |              |              |              |           |
  |  opcode   \__|  |              ]|--read       ]|--read       ]|--read    ]|--read not (~)
  |  |___________   |___________   |___________   |___________   |___________|
  |  |instruction|  |accumulator|  |program    |  |temporary  |  |operand    |
  |  |register   |  |register   |  |counter    |  |register   |  |register   |
  |  |           |  |           |  |register   |  |           |  |           |
  |  |___________|  |___________|  |___________|  |___________|  |___________|
  |  |           |  |           |  |           |  |           |  |           |
  |  |       write  |       write  |       write  |       write  |       write   memory data bus
  |__|______________|______________|______________|______________|______________/
  
```
