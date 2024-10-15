PROMPT ld GT
       st PUTC
       st PUTC
       ld SP
       st PUTC
PRINTC ld ZERO
       st GETC
       ld GETC
       st PUTC
       nt GETC
       ad ONE
       ad CR
       js PRINTC
       ja PROMPT
ZERO   0
ONE    1
CR     10
SP     32
GT     62
