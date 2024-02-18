--------

# Spud -> Simple Processor Unit Design.

A very processor that resembles modern designs. That is easy to use and understand in its entirety.
 - Von Neumann architecture.
 - Word addressable memory.
 - Memory mapped peripherals.
 - Accumulator based machine.

--------

# Hardware Diagram

```
DATA BUS 16-BITS
------------------------------------------------+--------------------------------------------+
ADDRESS BUS 13-BITS                             |                                            |
----+---------------------+                     |                                            |
    |                     |                     |                                            |
    |          +---------------------+---------------------+------------------+              |
    |          |          |          |          |          |                  |              |
    |          |          |          |          |          |        |    |    |          |   |
+---C---+  +---C---+  +---C---+  +---C---+  +---C---+  +---C---+  +-N----P-+  |        +-B---A-+
|  AND  |  |  AND  |  |  AND  |  |  AND  |  |  AND  |  |  AND  |  |  SIGN  |  |        |  XOR  |
+-A---B-+  +-A---B-+  +-A---B-+  +-A---B-+  +-A---B-+  +-A---B-+  +-A------+  |        +---C---+
  |   |      |   |      |   |      |   |      |   |      |   |      |         |            |
  |          |          |          |          |          |          |         |            |
  +----------+          +----------+          +----------+----------+         |            |
  |                     |                     |                               |            |    |
+-Q----------------+  +-Q----------------+  +-Q----------------+            +-B------+   +-A----C-+
| [0-12]    13-BIT |  | [0-12]    16-BIT |  | [0-15]    16-BIT |             \        \ / 16-BIT /
|        IP        |  |        IR        |  |        AC        |              \        +        /
+-D--------------E-+  +-D--------------E-+  +-D -------------E-+               +-------S-------+
 |               |      |              |      |              |                         |
 |                      |                     |                                        |
 +----------------------+---------------------+----------------------------------------+
```

--------

# Instruction Set Architecture

Fetch/decode behaviour (before each executed instruction):
+ ```IR <- memory[IP]```
+  ```IP <- IP + 1```

Machine Representation|Assembly Representation| Name         |Behaviour
----------------------|-----------------------|--------------|----------------------------------------------------------------------------------------------------------
```000<ADDRESS>```    |RESERVED               |RESERVED      |RESERVED
```001<ADDRESS>```    |```LD <ADDRESS>```     |LOAD          |```AC <- memory[IR]```
```010<ADDRESS>```    |```AD <ADDRESS>```     |Add           |```AC <- AC + memory[IR]```
```011<ADDRESS>```    |```SB <ADDRESS>```     |Subtract      |```AC <- AC - memory[IR]```
```100<ADDRESS>```    |```ST <ADDRESS>```     |Store         |```memory[IR] <- AC```
```101<ADDRESS>```    |```JN <ADDRESS>```     |Jump Negative |```if(AC[15]) IP <- IR```
```110<ADDRESS>```    |```JC <ADDRESS>```     |Jump Carry    |```if(AC[16]) IP <- IR```
```111<ADDRESS>```    |```JA <ADDRESS>```     |Jump Any      |```IP <- IR```
