         get TOKEN_BUFFER
         set READ_INPUT_ARG
         get MAIN_RR
         any READ_INPUT_CAL
MAIN_RR  lab MAIN_R
MAIN_R   set TOKEN_BUFFER_END
MAIN_LOP get TOKEN_BUFFER_END
         sub TOKEN_BUFFER
         neg HALT
         get TOKEN_BUFFER
         set SAME_STRING_ARG
         get STRING_HALT
         set SAME_STRING_ARH
         get MAIN_SS
         any SAME_STRING_CAL
MAIN_SS  lab MAIN_S
MAIN_S   neg HALT
         get TOKEN_BUFFER
         set PRINT_STRING_ARG
         get MAIN_PP
         any PRINT_STRING_CAL
MAIN_PP  lab MAIN_P
MAIN_P   add INCREMENT_ONE
         set TOKEN_BUFFER
         get CHAR_LINE_FEED
         set PUTC
         any MAIN_LOP




HALT any HALT
EXIT lab HALT




PRINT_STRING_ARG num 0
PRINT_STRING_CAL add OPCODE_ANY
                 set PRINT_STRING_RET
                 get OPCODE_GET
                 add PRINT_STRING_ARG
                 set PRINT_STRING_IDX
                 any PRINT_STRING_IDX
PRINT_STRING_INC get PRINT_STRING_IDX
                 add INCREMENT_ONE
                 set PRINT_STRING_IDX
PRINT_STRING_IDX num 0
                 set PUTC
                 set PRINT_STRING_ARG
                 get CHAR_NULL
                 sub PRINT_STRING_ARG
                 neg PRINT_STRING_INC
                 get PRINT_STRING_IDX
                 sub OPCODE_GET
PRINT_STRING_RET num 0



SAME_STRING_ARG num 0
SAME_STRING_ARH num 0
SAME_STRING_CAL add OPCODE_ANY
                set SAME_STRING_RET
                get OPCODE_GET
                add SAME_STRING_ARG
                set SAME_STRING_IDX
                get OPCODE_GET
                add SAME_STRING_ARH
                set SAME_STRING_IDY
SAME_STRING_IDX num 0
                set SAME_STRING_ARG
                get SAME_STRING_IDX
                add INCREMENT_ONE
                set SAME_STRING_IDX
SAME_STRING_IDY num 0
                set SAME_STRING_ARH
                get SAME_STRING_IDY
                add INCREMENT_ONE
                set SAME_STRING_IDY
                get SAME_STRING_ARG
                sub SAME_STRING_ARH
                neg SAME_STRING_FAL
                get SAME_STRING_ARH
                sub SAME_STRING_ARG
                neg SAME_STRING_FAL
                get CHAR_NULL
                sub SAME_STRING_ARG
                neg SAME_STRING_IDX
                get BOOLEAN_TRUE
                any SAME_STRING_RET
SAME_STRING_FAL get BOOLEAN_FALSE
SAME_STRING_RET num 0



IS_DIGIT_ARG num 0
IS_DIGIT_CAL add OPCODE_ANY
             set IS_DIGIT_RET
             get IS_DIGIT_ARG
             sub CHAR_ZERO
             neg IS_DIGIT_FAL
             get CHAR_NINE
             sub IS_DIGIT_ARG
             neg IS_DIGIT_FAL
             get BOOLEAN_TRUE
             any IS_DIGIT_RET
IS_DIGIT_FAL get BOOLEAN_FALSE
IS_DIGIT_RET num 0



IS_NUMBER_ARG num 0
IS_NUMBER_CAL
IS_NUMBER_RET num 0



IS_UPPER_ARG num 0
IS_UPPER_CAL add OPCODE_ANY
             set IS_UPPER_RET
             get IS_UPPER_ARG
             sub CHAR_UPPER_A
             neg IS_UPPER_UND
             get CHAR_UPPER_Z
             sub IS_UPPER_ARG
             neg IS_UPPER_UND
             any IS_UPPER_TRU
IS_UPPER_UND get IS_UPPER_ARG
             sub CHAR_UNDERSCORE
             neg IS_UPPER_FAL
             get CHAR_UNDERSCORE
             sub IS_UPPER_ARG
             neg IS_UPPER_FAL
IS_UPPER_TRU get BOOLEAN_TRUE
             any IS_UPPER_RET
IS_UPPER_FAL get BOOLEAN_FALSE
IS_UPPER_RET num 0



IS_LABEL_ARG num 0
IS_LABEL_CAL
IS_LABEL_RET num 0



IS_SPACE_ARG num 0
IS_SPACE_CAL add OPCODE_ANY
             set IS_SPACE_RET
             get IS_SPACE_ARG
             sub CHAR_TAB
             neg IS_SPACE_SPA
             get CHAR_LINE_FEED
             sub IS_SPACE_ARG
             neg IS_SPACE_SPA
             any IS_SPACE_TRU
IS_SPACE_SPA get IS_SPACE_ARG
             sub CHAR_SPACE
             neg IS_SPACE_FAL
             get CHAR_SPACE
             sub IS_SPACE_ARG
             neg IS_SPACE_FAL
IS_SPACE_TRU get BOOLEAN_TRUE
             any IS_SPACE_RET
IS_SPACE_FAL get BOOLEAN_FALSE
IS_SPACE_RET num 0




IS_PERIOD_ARG num 0
IS_PERIOD_CAL add OPCODE_ANY
              set IS_PERIOD_RET
              get IS_PERIOD_ARG
              sub CHAR_PERIOD
              neg IS_PERIOD_FAL
              get CHAR_PERIOD
              sub IS_PERIOD_ARG
              neg IS_PERIOD_FAL
              get BOOLEAN_TRUE
              any IS_PERIOD_RET
IS_PERIOD_FAL get BOOLEAN_FALSE
IS_PERIOD_RET num 0




NEXT_INPUT_CAL add OPCODE_ANY
               set NEXT_INPUT_RET
NEXT_INPUT_CMP get GETC
               set IS_SPACE_ARG
               set IS_PERIOD_ARG
               get NEXT_INPUT_DD
               any IS_SPACE_CAL
NEXT_INPUT_DD  lab NEXT_INPUT_D
NEXT_INPUT_D   neg NEXT_INPUT_INC
               get NEXT_INPUT_TT
               any IS_PERIOD_CAL
NEXT_INPUT_TT  lab NEXT_INPUT_T
NEXT_INPUT_T   neg NEXT_INPUT_FAL
               get BOOLEAN_TRUE
               any NEXT_INPUT_RET
NEXT_INPUT_INC get CHAR_NULL
               set GETC
               any NEXT_INPUT_CMP
NEXT_INPUT_FAL get BOOLEAN_FALSE
NEXT_INPUT_RET num 0




COPY_INPUT_ARG num 0
COPY_INPUT_CAL add OPCODE_ANY
               set COPY_INPUT_RET
               get OPCODE_SET
               add COPY_INPUT_ARG
               set COPY_INPUT_IDX
COPY_INPUT_CMP get GETC
               set IS_SPACE_ARG
               set IS_PERIOD_ARG
               get COPY_INPUT_DD
               any IS_SPACE_CAL
COPY_INPUT_DD  lab COPY_INPUT_D
COPY_INPUT_D   neg COPY_INPUT_END
               get COPY_INPUT_TT
               any IS_PERIOD_CAL
COPY_INPUT_TT  lab COPY_INPUT_T
COPY_INPUT_T   neg COPY_INPUT_END
               get GETC
COPY_INPUT_IDX num 0
               get COPY_INPUT_IDX
               add INCREMENT_ONE
               set COPY_INPUT_IDX
               get CHAR_NULL
               set GETC
               any COPY_INPUT_CMP
COPY_INPUT_END get COPY_INPUT_IDX
               set COPY_INPUT_IDY
               get CHAR_NULL
COPY_INPUT_IDY num 0
               get COPY_INPUT_IDX
               add INCREMENT_ONE
               sub OPCODE_SET
COPY_INPUT_RET num 0




READ_INPUT_ARG num 0
READ_INPUT_CAL add OPCODE_ANY
               set READ_INPUT_RET
READ_INPUT_NXT get READ_INPUT_NN
               any NEXT_INPUT_CAL
READ_INPUT_NN  lab READ_INPUT_N
READ_INPUT_N   neg READ_INPUT_GET
               any READ_INPUT_END
READ_INPUT_GET get READ_INPUT_ARG
               set COPY_INPUT_ARG
               get READ_INPUT_CC
               any COPY_INPUT_CAL
READ_INPUT_CC  lab READ_INPUT_C
READ_INPUT_C   set READ_INPUT_ARG
               any READ_INPUT_NXT
READ_INPUT_END get READ_INPUT_ARG
               add INCREMENT_ONE
READ_INPUT_RET num 0




OPCODE_GET      num 0
OPCODE_SET      num 8192
OPCODE_ANY      num 32768
INCREMENT_ONE   num 1
BOOLEAN_FALSE   num 0
BOOLEAN_TRUE    num 65535
CHAR_NULL       num 0
CHAR_TAB        num 9
CHAR_LINE_FEED  num 10
CHAR_SPACE      num 32
CHAR_PERIOD     num 46
CHAR_ZERO       num 48
CHAR_NINE       num 57
CHAR_UPPER_A    num 65
CHAR_UPPER_Z    num 90
CHAR_UNDERSCORE num 95


STRING_HALT lab CHARS_HALT
CHARS_HALT  num 72
            num 65
            num 76
            num 84
            num 0


TOKEN_BUFFER       lab TOKEN_BUFFER_START
TOKEN_BUFFER_END   num 0
TOKEN_BUFFER_START num 0
