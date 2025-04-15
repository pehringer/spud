           ld  STRING
           st  PRINT_ARG
           ld  HALT
           ja  PRINT_CAL
HALT       ja  HALT

PRINT_ARG  0
PRINT_CAL  st  PRINT_RET
           ld  PRINT_ARG
           st  PRINT_IDX
PRINT_IDX  0
           st  PUTC
           st  PRINT_ARG
           ld  PRINT_IDX
           ad  INCREMENT
           st  PRINT_IDX
           nt  PRINT_ARG
           ad  INCREMENT
           ad  CHAR_NULL
           js  PRINT_IDX
PRINT_RET  0

INCREMENT  1

STRING     ld  CHAR_ARRAY
CHAR_ARRAY 104
           101
           108
           108
           111
           10
CHAR_NULL  0
