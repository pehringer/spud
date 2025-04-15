PRINT_CHAR ld ZERO
           st GETC
           ld GETC
           st PUTC
           nt GETC
           ad ONE
           ad NEWLINE
           js PRINT_CHAR

HALT       ja HALT

ZERO    0
ONE     1
NEWLINE 10
