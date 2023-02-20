; Print user input.

; print input prompt ">> "
LOAD_I '>'
SWAP
SAVE_A 1048577
SAVE_A 1048577
LOAD_I '\s'
SWAP
SAVE_A 1048577

; Prompt input unit to get user input.
LOAD_I '\0'
SWAP
SAVE_A 1048576

; Print out user input.
PrintChar:
	LOAD_A 1048576
	SWAP
	SAVE_A 1048577
	LOAD_I '\n'
	SUB
	JUMP_Z AllCharsPrinted
	LOAD_I '\0'
	SWAP
	SAVE_A 1048576
	JUMP_A PrintChar

AllCharsPrinted:
	HALT
