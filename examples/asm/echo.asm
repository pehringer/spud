PROMPT ld GT
       st PUTC
       st PUTC
       ld SP
       st PUTC
PRINTC ld ZERO
       st GETC
       ld GETC
       st PUTC
       ld CR
       su GETC
       js PRINTC
       ja PROMPT
ZERO   0
CR     10
SP     32
GT     62
