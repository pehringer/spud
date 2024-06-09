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
         set PRINT_STRING_ARG
         get MAIN_PP
         any PRINT_STRING_CAL
MAIN_PP  lab MAIN_P
MAIN_P   set TOKEN_BUFFER
         add OPCODE_SET
         set MAIN_LFE
         get CHAR_LINE_FEED
MAIN_LFE num 0
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




IS_DELIMITOR_ARG num 0
IS_DELIMITOR_CAL add OPCODE_ANY
                 set IS_DELIMITOR_RET
                 get IS_DELIMITOR_ARG
                 sub CHAR_TAB
                 neg IS_DELIMITOR_SPA
                 get CHAR_LINE_FEED
                 sub IS_DELIMITOR_ARG
                 neg IS_DELIMITOR_SPA
                 any IS_DELIMITOR_TRU
IS_DELIMITOR_SPA get IS_DELIMITOR_ARG
                 sub CHAR_SPACE
                 neg IS_DELIMITOR_FAL
                 get CHAR_SPACE
                 sub IS_DELIMITOR_ARG
                 neg IS_DELIMITOR_FAL
IS_DELIMITOR_TRU get BOOLEAN_TRUE
                 any IS_DELIMITOR_RET
IS_DELIMITOR_FAL get BOOLEAN_FALSE
IS_DELIMITOR_RET num 0




IS_TERMINATOR_ARG num 0
IS_TERMINATOR_CAL add OPCODE_ANY
                  set IS_TERMINATOR_RET
                  get IS_TERMINATOR_ARG
                  sub CHAR_PERIOD
                  neg IS_TERMINATOR_FAL
                  get CHAR_PERIOD
                  sub IS_TERMINATOR_ARG
                  neg IS_TERMINATOR_FAL
                  get BOOLEAN_TRUE
                  any IS_TERMINATOR_RET
IS_TERMINATOR_FAL get BOOLEAN_FALSE
IS_TERMINATOR_RET num 0




NEXT_INPUT_CAL add OPCODE_ANY
               set NEXT_INPUT_RET
NEXT_INPUT_CMP get GETC
               set IS_DELIMITOR_ARG
               set IS_TERMINATOR_ARG
               get NEXT_INPUT_DD
               any IS_DELIMITOR_CAL
NEXT_INPUT_DD  lab NEXT_INPUT_D
NEXT_INPUT_D   neg NEXT_INPUT_INC
               get NEXT_INPUT_TT
               any IS_TERMINATOR_CAL
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
               set IS_DELIMITOR_ARG
               set IS_TERMINATOR_ARG
               get COPY_INPUT_DD
               any IS_DELIMITOR_CAL
COPY_INPUT_DD  lab COPY_INPUT_D
COPY_INPUT_D   neg COPY_INPUT_END
               get COPY_INPUT_TT
               any IS_TERMINATOR_CAL
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




OPCODE_GET     num 0
OPCODE_SET     num 8192
OPCODE_ANY     num 32768
INCREMENT_ONE  num 1
BOOLEAN_FALSE  num 0
BOOLEAN_TRUE   num 65535
CHAR_NULL      num 0
CHAR_TAB       num 9
CHAR_LINE_FEED num 10
CHAR_SPACE     num 32
CHAR_PERIOD    num 46



TOKEN_BUFFER      lab TOKEN_BUFFER_START
TOKEN_BUFFER_END  num 0
TOKEN_BUFFER_START num 0
