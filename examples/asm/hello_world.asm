           get STRING
           set PRINT_ARG
           get HALT
           any PRINT_CAL
HALT       any HALT




PRINT_ARG 0
PRINT_CAL set PRINT_RET
          get PRINT_ARG
          set PRINT_IDX
PRINT_IDX 0
          set PUTC
          set PRINT_ARG
          get PRINT_IDX
          add INCREMENT
          set PRINT_IDX
          get CHAR_NULL
          sub PRINT_ARG
          neg PRINT_IDX
PRINT_RET 0




INCREMENT 1

CHAR_NULL 0

STRING      get CHAR_ARRAY
CHAR_ARRAY  104
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
