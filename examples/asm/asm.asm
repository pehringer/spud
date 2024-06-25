         get BUFFER_SET
         set READ_INPUT_ARG
         get MAIN_R
         any READ_INPUT_CAL
MAIN_R   any MAIN_RR
MAIN_RR  set BUFFER_SET
MAIN_LOP get BUFFER_GET
         set PRINT_ARG
         get MAIN_P
         any PRINT_CAL
MAIN_P   any MAIN_PP
MAIN_PP  set BUFFER_GET
         get CHAR_LINE_FEED
         set PUTC
         any MAIN_LOP


PRINT_CAL set PRINT_RET
          get PRINT_ARG
          set PRINT_IDX
PRINT_IDX 0
          set PUTC
          set PRINT_ARG
          get PRINT_IDX
          add PRINT_INC
          set PRINT_IDX
          get PRINT_NUL
          sub PRINT_ARG
          neg PRINT_IDX
          get PRINT_IDX
PRINT_RET 0
PRINT_ARG 0
PRINT_INC 1
PRINT_NUL 0


NEXT_INPUT_CAL set NEXT_INPUT_RET
               any NEXT_INPUT_PER
NEXT_INPUT_GET get CHAR_NULL
               set GETC
NEXT_INPUT_PER get GETC
               sub CHAR_PERIOD
               neg NEXT_INPUT_TAB
               get CHAR_PERIOD
               sub GETC
               neg NEXT_INPUT_TAB
NEXT_INPUT_FAL get BOOLEAN_FALSE
               any NEXT_INPUT_RET
NEXT_INPUT_TAB get GETC
               sub CHAR_TAB
               neg NEXT_INPUT_LNF
               get CHAR_TAB
               sub GETC
               neg NEXT_INPUT_LNF
               any NEXT_INPUT_GET
NEXT_INPUT_LNF get GETC
               sub CHAR_LINE_FEED
               neg NEXT_INPUT_SPA
               get CHAR_LINE_FEED
               sub GETC
               neg NEXT_INPUT_SPA
               any NEXT_INPUT_GET
NEXT_INPUT_SPA get GETC
               sub CHAR_SPACE
               neg NEXT_INPUT_TRU
               get CHAR_SPACE
               sub GETC
               neg NEXT_INPUT_TRU
               any NEXT_INPUT_GET
NEXT_INPUT_TRU get BOOLEAN_TRUE
NEXT_INPUT_RET 0


COPY_INPUT_ARG 0
COPY_INPUT_CAL set COPY_INPUT_RET
               get COPY_INPUT_ARG
               set COPY_INPUT_IDX
               any COPY_INPUT_PER
COPY_INPUT_NXT get CHAR_NULL
               set GETC
COPY_INPUT_PER get GETC
               sub CHAR_PERIOD
               neg COPY_INPUT_TAB
               get CHAR_PERIOD
               sub GETC
               neg COPY_INPUT_TAB
               any COPY_INPUT_NUL
COPY_INPUT_TAB get GETC
               sub CHAR_TAB
               neg COPY_INPUT_LNF
               get CHAR_TAB
               sub GETC
               neg COPY_INPUT_LNF
               any COPY_INPUT_NUL
COPY_INPUT_LNF get GETC
               sub CHAR_LINE_FEED
               neg COPY_INPUT_SPA
               get CHAR_LINE_FEED
               sub GETC
               neg COPY_INPUT_SPA
               any COPY_INPUT_NUL
COPY_INPUT_SPA get GETC
               sub CHAR_SPACE
               neg COPY_INPUT_CHR
               get CHAR_SPACE
               sub GETC
               neg COPY_INPUT_CHR
               any COPY_INPUT_NUL
COPY_INPUT_CHR get GETC
COPY_INPUT_IDX 0
               get COPY_INPUT_IDX
               add INCREMENT_ONE
               set COPY_INPUT_IDX
               any COPY_INPUT_NXT
COPY_INPUT_NUL get COPY_INPUT_IDX
               set COPY_INPUT_IDY
               get CHAR_NULL
COPY_INPUT_IDY 0
               get COPY_INPUT_IDX
               add INCREMENT_ONE
COPY_INPUT_RET 0


READ_INPUT_ARG 0
READ_INPUT_CAL set READ_INPUT_RET
READ_INPUT_NXT get READ_INPUT_N
               any NEXT_INPUT_CAL
READ_INPUT_N   any READ_INPUT_NN
READ_INPUT_NN  neg READ_INPUT_GET
               any READ_INPUT_END
READ_INPUT_GET get READ_INPUT_ARG
               set COPY_INPUT_ARG
               get READ_INPUT_C
               any COPY_INPUT_CAL
READ_INPUT_C   any READ_INPUT_CC
READ_INPUT_CC  set READ_INPUT_ARG
               any READ_INPUT_NXT
READ_INPUT_END get READ_INPUT_ARG
               add INCREMENT_ONE
READ_INPUT_RET 0





INCREMENT_ONE   1
BOOLEAN_FALSE   0
BOOLEAN_TRUE    65535
CHAR_NULL	0
CHAR_TAB        9
CHAR_LINE_FEED  10
CHAR_SPACE	32
CHAR_PERIOD     46
CHAR_ZERO	48
CHAR_NINE	57
CHAR_UPPER_A    65
CHAR_UPPER_Z    90
CHAR_UNDERSCORE 95


BUFFER_END 0
BUFFER_GET get BUFFER
BUFFER_SET set BUFFER
BUFFER_ADD add BUFFER
BUFFER_SUB sub BUFFER
BUFFER     0
           0
           0
           0
           0
           0
           0
           0
