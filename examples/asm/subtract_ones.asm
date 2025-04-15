READ_IN_DIGITS ld ZERO
               st GETC
               ld GETC
               st RESULT
               ld ZERO
               st GETC

SUBTRACT       nt GETC
               ad RESULT
               jc CARRY_ADD_ONE
               ja PRINT
CARRY_ADD_ONE  ad ONE
PRINT          js PRINT_NEGATIVE

PRINT_POSITIVE ad DIGIT
               st PUTC
               ja PRINT_NEWLINE

PRINT_NEGATIVE st RESULT
               ld DASH
               st PUTC
               nt RESULT
               ad DIGIT
               st PUTC

PRINT_NEWLINE  ld ZERO
               st GETC
               ld GETC
               st PUTC

HALT           ja HALT

RESULT 0
ZERO   0
ONE    1
DASH   45
DIGIT  48
