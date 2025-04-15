               ld  STRING
               st  PRINT_ARGUMENT
               ld  HALT
               ja  PRINT_ROUTINE
HALT           ja  HALT

PRINT_ARGUMENT 0
PRINT_ROUTINE  st  PRINT_RETURN
               ld  PRINT_ARGUMENT
               st  INDEX_STRING
INDEX_STRING   0
               st  PUTC
               st  PRINT_ARGUMENT
               ld  INDEX_STRING
               ad  INCREMENT
               st  INDEX_STRING
               nt  PRINT_ARGUMENT
               ad  INCREMENT
               ad  CHAR_NULL
               js  INDEX_STRING
PRINT_RETURN   0

INCREMENT  1
STRING     ld  CHAR_ARRAY
CHAR_ARRAY 104
           101
           108
           108
           111
           10
CHAR_NULL  0
