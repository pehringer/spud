PRINTC ld ZERO
       st GETC
       ld GETC
       st PUTC
       nt GETC
       ad ONE
       ad CR
       js PRINTC
HALT   ja HALT
ZERO   0
ONE    1
CR     10
