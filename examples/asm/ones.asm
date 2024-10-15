PROMPT_L
         ld GT
         st PUTC
         st PUTC
         ld SP
         st PUTC
READIN_L
         ld ZERO
         st GETC
         ld GETC
         st INPUT
PROMPT_R
         ld GT
         st PUTC
         st PUTC
         ld SP
         st PUTC
READIN_R
         ld ZERO
         st GETC
         ld ZERO
         st GETC
SUBTRACT
         nt GETC
         ad INPUT
         jc CARRY_AD
         ja PRINT_LN
CARRY_AD ad ONE
PRINT_LN
         ad ZR
         st PUTC
         ld CR
         st PUTC
HALT     ja HALT
INPUT  0
ZERO   0
ONE    1
CR     10
SP     32
ZR     48
GT     62
