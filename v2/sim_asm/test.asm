; increment stack pointer by 1
GET ptr_s
ADD num_1
SET ptr_s

; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store GET instruction with stack address
GET ptr_s
ADD get_op
SET load
load:
0
SET var_x

halt:
ANY halt

get_op:
0b0000000000000000

num_1:
1

var_x:
0

stack:
0
top_s:
0
42
21

ptr_s:
top_s
