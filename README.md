--------

# Spud -> Simple Processor Unit Design.

A very processor that resembles modern designs. That is easy to use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Memory mapped peripherals.
 - Register based machine.

--------

# Table of Contents

[Hardware Diagram](#hardware-diagram)  
  
[Hardware Workarounds](#hardware-workarounds)  
  
[Instruction Set](#instruction-set)  
  
[Assembly Code](#assembly-code)  
- [Assembly Instructions](#assembly-instructions)
- [Assembly Labels](#assembly-labels)
- [Assembly Comments](#assembly-comments)
- [Assembly Arithmetic Examples](#assembly-arithmetic-examples)  
- [Assembly Array Examples](#assembly-array-examples)  
- [Assembly Comparison Examples](#assembly-comparison-examples)  
- [Assembly Control Flow Examples](#assembly-control-flow-examples)  
- [Assemply Stack Examples](#assemply-stack-examples)  

[Assembler](#assembler)  

  
[Simulator](#simulator)  

--------

# Hardware Diagram

```
 ____________________
|Control Unit        |
|                    |
|   Instruction Opcode_______________________
|                    |        ___________    |
|                    |    ___|Instruction|___|
|                    |   |   |Register   |
|    Write Instruction__ | __|           |
|                    |   |   |___________|
|                    |   |
|                    |   |    ___________
|                    |   |___|Accumulator|_________
|                    |   |   |Register   |         |
|    Write Accumulator__ | __|           |         |
|                    |   |   |___________|         |
|                    |   |                         |
|                    |   |         ______          |
| Accumulator Positive__ | _______/Number|         |
|                    |   |       / Sign  |_________|
| Accumulator Negative__ | ______\       |         |
|                    |   |        \______|         |
|            Read Left__ | ___________________     |
|           Read Right   |         _______   _|_   |
|                    |   |        /Adder |___/|\   |
|                    |   |       /       |    |    |
|                    |   |______|       /     |    |
|                    |   |      |       \    _|_   |
|                    |   |       \       |___/ \___|
|                    |   |        \______|         |
| Read Program Counter__ | ___________________     |
|                    |   |    ___________    _|_   |
|                    |   |___|Program    |___/ \___|
|                    |   |   |Counter    |         |
|Write Program Counter__ | __|Register   |         |
|                    |   |   |___________|         |
|       Read Temporary__ | ___________________     |
|                    |   |    ___________    _|_   |
|                    |   |___|Temporary  |___/ \___|
|                    |   |   |Register   |         |
|      Write Temporary__ | __|           |         |
|                    |   |   |___________|         |
|         Read Operand__ | ___________________     |
|     Read Not Operand   |    ___________    _|_   |
|                    |   |___|Operand    |___/|\___|
|                    |   |   |Register   |   _|_   |
|        Write Operand__ | __|           |___/ \___|
|____________________|   |   |___________|         |
                         |                         |
                         |                         |
  ______________________/  Data Bus    Address Bus |
 /                                                 |
|    __________________________________________    |
|___|Memory Unit     Address Range: 0 - 1048575|___|
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|   |__________________________________________|   |
|                                                  |
|    __________________________________________    |
|___|Input Unit                Address: 1048576|___|
|   |__________________________________________|   |
|                                                  |
|    __________________________________________    |
|___|Output Unit               Address: 1048577|___|
    |__________________________________________|

```

--------

# Hardware Workarounds

### Subtraction Operations

The processor lacks subtractor hardware, so how then does the processor support subtraction operations? The processor simply makes the right operand negative and then adds it to the left operand:  

```left - right  --->  left + (-right)```

To get the twos compliments of a binary number (negative version of the number) two steps are required in the following order:

1) Bitwise not the number (use operand registers ```Read Not```).
2) Increment the number by one (use adders carry in).

So to subtract the computer does the following:  

```accumulator_register + (~operand_register) + 1```

### Stack Operations

The processor lacks a stack pointer register, so how then does the processor support stack operations? The computer simply stores the stack pointer in memory and loads it in when needed. So to push a variable onto the stack the processor does the following:

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

[See this section to view more stack examples!](#assemply-stack-examples)

--------

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
```8```             |```JUMP```             |Jump          |```program_counter_register <=> operand_register```
```9 [ADDRESS]```   |```JUMP_A [ADDRESS]``` |Jump Any      |```program_counter_register = memory[program_counter]```
```10 [ADDRESS]```   |```JUMP_Z [ADDRESS]``` |Jump Zero     |```program_counter_register = accumulator_register == 0 ? memory[program_counter_register] : ++program_counter_register```
```13 [ADDRESS]```   |```JUMP_P [ADDRESS]``` |Jump Positive |```program_counter_register = accumulator_register > 0 ? memory[program_counter_register] : ++program_counter_register```
```12 [ADDRESS]```   |```JUMP_N [ADDRESS]``` |Jump Negative |```program_counter_register = accumulator_register < 0 ? memory[program_counter_register] : ++program_counter_register```
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
```6```             |```JUMP_P```           |Jump Positive |```if(accumulator_register > 0) {program_counter_register <=> operand_register}```
```7```             |```JUMP_N```           |Jump Negative |```if(accumulator_register < 0) {program_counter_register <=> operand_register}```

--------

# Assembly Code

When using the instruction set it is useful to keep in mind how data is generally moved around and used.

- Values are loaded into the operand register.
- Values are stored from the accumulator register.
- Arithmetic operations use the accumulator and operand registers.
- Result of arithmetic operations are stored in the accumulator register.
- Values can be swapped between the accumulator and operand registers.
- Values can be swapped between the program counter and operand registers.
- Conditional jumps use the accumulator registers as the condition.

Keep the below diagram in mind when using the instruction set.

```
 _________________________________________________________________
| Memory/Input/Output Unit                                        |
|_________________________________________________________________|
                                ___                         . 
                               |   |                       / \
                              _|   |_                     /   \
                              \     /                    /_   _\
                               \   /                      |   |
                                \./                       |___|    
 ___________                ___________                ___________
|Program    |   /|____|\   |Operand    |   /|____|\   |Accumulator|
|Counter    |  /        \  |Register   |  /        \  |Register   |
|Register   |  \  ____  /  |           |  \  ____  /  |           |
|___________|   \|    |/   |___________|   \|    |/   |___________|
```

## Assembly Instructions

Assembly instructions used human friendly keywords instead of opcode numbers. There are two types of assembly instruction:
  
1) Opcode only instructions:
   - ```LOAD```
   - ```SWAP```
   - ```ADD```
   - ```SUB```
   - ```SAVE```
   - ```JUMP```
   - ```HALT```
  
2) Immediate value instructions:
   - ```LOAD_I [VALUE]```
   - ```LAOD_A [ADDRESS]```
   - ```SAVE_A [ADDRESS]```
   - ```JUMP_A [ADDRESS]```
   - ```JUMP_Z [ADDRESS]```
   - ```JUMP_P [ADDRESS]```
   - ```JUMP_N [ADDRESS]```
  
The following immediate value types are supported:
- Labels (examples on lines 24 and 28 in ```Spud/assembly_code/echo.ASM```)
- Base 10 numbers (examples on lines 19 and 21 in ```Spud/assembly_code/echo.ASM```)
- Characters (examples on lines 10 and 19 in ```Spud/assembly_code/echo.ASM```)

## Assembly Labels

Assembly label are extremely useful. They are simply user defined keywords that repersent an address in memory. They can be used to represent primative variables, see the assembly array examples section. They can also be used for control flow, see the assembly control flow examples section.

## Assembly Comments

Assembly comments behave the same as single line comments in any other programming language. Anything after a ```;``` on a given line is ignored by the assembler.

## Assembly Arithmetic Examples

#### X += 1  
```
; Increment X by 1.
LOAD_A varX
SWAP
LOAD_I 1
ADD

; Save result in X.
SAVE_A varX
HALT

varX:
    4
```

#### X -= 1  
```
; Decrement X by 1.
LOAD_A varX
SWAP
LOAD_I 1
SUB

; Save result in X.
SAVE_A varX
HALT

varX:
    4
```

#### Z = X + Y
```
; Add X and Y.
LOAD_A varX
SWAP
LOAD_A varY
ADD

; Save result in Z.
SAVE_A varZ
HALT

varX:
    4

varY: 
    2

varZ:
    0
```

#### Z = X - Y
```
; Subtract X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB

; Save result in Z.
SAVE_A varZ
HALT

varX:
    4

varY:
    2

varZ:
    0

```

## Assembly Array Examples

#### J = ARR[I]
```
; Get address of Arr at index I.
LOAD_I varARR
SWAP
LOAD_A varI
ADD

; Load value at address.
SWAP
LOAD

; Store value in J.
SWAP
SAVE_A varJ
HALT

varI:
    2
    
varJ:
    0
    
varARR:
    1  ; Index 0
    2
    4
    8  ; Index 3
```

#### ARR[I] = J
```
; Get address of Arr at index I.
LOAD_I varARR
SWAP
LOAD_A varI
ADD

; Load J's value.
LOAD_A varJ

; Store value at address.
SWAP
SAVE
HALT

varI:
    1
    
varJ:
    16
    
varARR:
    1  ; Index 0
    2
    4
    8  ; Index 3
```

## Assembly Comparison Examples

#### if(X < Y) {}
```
; Compare X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB
; Branch equal or less than.
JUMP_Z endIf 
JUMP_P endIf 

;
;
; Conditional code here.
;
;

endIf:
    HALT

varX:
    2

varY:
    4
```

#### if(X <= Y) {}
```
; Compare X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB
; Branch greater than.
JUMP_P endIf

;
;
; Conditional code here.
;
;

endIf:
    HALT

varX:
    2

varY:
    4
```

#### if(X == Y) {}
```
; Compare X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB
; Branch less than or greater than.
JUMP_N endIf
JUMP_P endIf

;
;
; Conditional code here.
;
;

endIf:
    HALT

varX:
    2

varY:
    2
```

#### if (X != y) {}
```
; Compare X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB
; Branch equal to.
JUMP_Z endIf

;
;
; Conditional code here.
;
;

endIf:
    HALT

varX:
    2

varY:
    4

```

#### if(X >= Y) {}
```
; Compare X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB
; Branch less than.
JUMP_N endIf

;
;
; Conditional code here.
;
;

endIf:
    HALT

varX:
    4

varY:
    3
```

#### if(X > Y) {}
```
; Compare X and Y.
LOAD_A varX
SWAP
LOAD_A varY
SUB
; Branch less than.
JUMP_N endIf
JUMP_Z endIf

;
;
; Conditional code here.
;
;

endIf:
    HALT

varX:
    4

varY:
    3
```

## Assembly Control Flow Examples

#### if(X > 0) {} else if(X < 0) {} else {}
```
ifPositive:
    LOAD_A varX
    SWAP
    JUMP_Z elseIfNegative
    JUMP_N elseIfNegative
    ;
    ; if code 
    ;
    ;
    JUMP_A endElse

elseIfNegative:
    JUMP_Z elseZero
    ;
    ; else if code
    ;
    ;
    JUMP_A endElse

elseZero:
    ;
    ; else code
    ;
    ;

endElse:
    HALT

varX:
    0
```

#### while(X-- > 0) {}
```
LOAD_A varX 
SWAP 
LOAD_I 1 
while:
    JUMP_Z endWhile 
    SUB
    ;
    ; while code
    ;
    ;
    JUMP_A while  
endWhile:
    HALT 

varX:
    10
```

## Assemply Stack Examples

#### push(X)
```
; Init stack pointer to top of stack.
; Stack is empty.
LOAD_I stackBottom  
SWAP
SAVE_A stackPointer	

; Load X and store it at the stack pointer.
LOAD_A varX
SWAP
LOAD_A stackPointer
SAVE

; Move and set stack pointer to next empty element (push).
SWAP
LOAD_I 1  
SUB
SAVE_A stackPointer
HALT

varX:
    4

stackPointer:
    0
    
    0
    0
    0
stackBottom:
    0
```

#### X = peek()
```
; Init stack pointer to top of stack.
; Stack has one element with the value 64.
LOAD_I stackBottom
SWAP
LOAD_I 1
SUB
SAVE_A stackPointer

; Move stack pointer to top element.
LOAD_A stackPointer
SWAP
LOAD_I 1
ADD

; Load in the top element.
SWAP
LOAD

; Save element to X
SWAP
SAVE_A varX
HALT

varX:
    0

stackPointer:
    0

    0
    0
    0
stackBottom:
    64
```

#### X = pop()
```
; Init stack pointer to top of stack.
; Stack has one element with the value 64.
LOAD_I stackBottom
SWAP
LOAD_I 1
SUB
SAVE_A stackPointer

; Move and set stack pointer to top element (pop).
LOAD_A stackPointer
SWAP
LOAD_I 1
ADD
SAVE_A stackPointer 

; Load in the top element.
SWAP
LOAD

; Save element to X
SWAP
SAVE_A varX
HALT

varX:
    0

stackPointer:
    0

    0
    0
    0
stackBottom:
    64
```

--------

# Assembler

The assembler is located at ```Spud/assembler/assembler.py```.  
The assembler takes two filepaths as arguments:  
  
- ```python assembler.py [INPUT_ASSEMBLY_CODE_FILEPATH] [OUTPUT_BINARY_CODE_FILEPATH]```
  
For example if you wanted to regenerate the hello world assembly example:  
  
- ```python assembler.py ../assembly_code/hello_world.ASM ../machine_code/hello_world.BIN```  
  
If any errors occur try running the Makefile at ```Spud/Makefile```.

--------

# Simulator

The simulator is located at ```Spud/simulator/simulator```.
The simulator will run the hello_world.BIN example if no arguments are given:
  
- ```./simulator```
  
Terminal Output:
```
                                    
Processor___________________________
                                    
         13 Data Bus                
         62 Address Bus             
         13 Instruction Register    
         10 Accumulator Register    
         62 Program Counter Register
         62 Temporary Register      
         33 Operand Register        
                                    
Memory______________________________
                                    
         54 |           3           
         55 |           7           
         56 |     1048577           
         57 |           0           
         58 |          10           
         59 |           3           
         60 |           7           
         61 |     1048577      
         62 |          13 <- PC
         63 |           0      
         64 |           0      
         65 |           0      
         66 |           0      
         67 |           0      
         68 |           0      
         69 |           0      
         70 |           0           
                                    
Input/Output________________________
                                    





Hello World!
$
```
  
If any errors occur try running the Makefile at ```Spud/Makefile```.
  
The simulator supports the following optional arguments:
- ```program [FILEPATH]``` - Run the .BIN at the given filepath.
- ```cycle [NUMBER_MILLISECONDS]``` - Make each instruction take the given number of milliseconds to run.
- ```halt [PROGRAM_COUNTER_NUMBER]``` - Stop the simulator once the program counter equals the given address.

For example if you wanted to execute hello_world.BIN slower, and have it stop after "Hello" has beeen printed:
  
- ```./simulator -program ../machine_code/hello_world.BIN -cycle 500 -halt 22```
  
Terminal Outut:
```
                                    
Processor___________________________
                                    
         22 Data Bus                
         22 Address Bus             
          7 Instruction Register    
        111 Accumulator Register    
         22 Program Counter Register
         22 Temporary Register      
        108 Operand Register        
                                    
Memory______________________________
                                    
         14 |     1048577           
         15 |           7           
         16 |     1048577           
         17 |           0           
         18 |         111           
         19 |           3           
         20 |           7           
         21 |     1048577           
         22 |           0 <- PC
         23 |          32      
         24 |           3      
         25 |           7      
         26 |     1048577      
         27 |           0      
         28 |          87      
         29 |           3      
         30 |           7      
                                    
Input/Output________________________
                                    






Hello$ 
```
  
If any errors occur try running the Makefile at ```Spud/Makefile```.
  
