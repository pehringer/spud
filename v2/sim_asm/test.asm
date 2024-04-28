; set true
GET num_1
SET var_z

; check false
GET var_x
SUB var_y
NEG halt
GET num_0
SET var_z

halt:
ANY halt

num_0:
0

num_1:
1

var_x:
-4

var_y:
+2

var_z:
0
