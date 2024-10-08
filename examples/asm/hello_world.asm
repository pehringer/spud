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
           ld  CHAR_NULL
           su  PRINT_ARG
           js  PRINT_IDX
PRINT_RET  0




INCREMENT  1

CHAR_NULL  0

STRING     ld  CHAR_ARRAY
CHAR_ARRAY 104
           101
           108
           108
           111
           32
           119
           111
           114
           108
           100
           10
           0
