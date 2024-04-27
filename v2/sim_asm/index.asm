; all instructions have fixed memory addresses
; dynamic memory addresses requires self-modifying code
; create and store GET instruction with index address
GET ptr_a
ADD var_i
ADD get_op
SET idx_a
idx_a:
0
SET var_j

halt:
ANY halt

get_op:
000000000000000000

var_i:
2

var_j:
0

var_a:
1
2
4
8

ptr_a:
var_a
