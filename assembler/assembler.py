from sys import argv
from binary import binary


######## Helper Functions ########

def is_comment_or_none(word: str) -> bool:
	return not word or word[0] == ';'

def is_label_define(word: str) -> bool:
	return word and word[:-1].isalpha() and word[-1] == ':'

def get_label_define(word: str) -> str:
	return word[:-1]

def is_label(word: str) -> bool:
	return word and word.isalpha()

def get_label(word: str) -> str:
	return word

def is_character(word: str) -> bool:
	if word == "'\\s'":
		return True
	if word == "'\\n'":
		return True
	if word == "'\\t'":
		return True
	if word == "'\\0'":
		return True
	return word and len(word) == 3 and word[0] == "'" and word[2] == "'"

def get_character(word: str) -> int:
	if word == "'\\s'":
		return 32
	if word == "'\\n'":
		return 10
	if word == "'\\t'":
		return 9
	if word == "'\\0'":
		return 0
	return ord(word[1:-1])

def is_unsigned_numeric(word: str) -> bool:
	return word and word.isnumeric()

def is_positive_numeric(word: str) -> bool:
	return word and len(word) > 1 and word[1:].isnumeric() and word[0] == '+'

def is_negative_numeric(word: str) -> bool:
	return word and len(word) > 1 and word[1:].isnumeric() and word[0] == '-'

def is_numeric(word: str) -> bool:
	return is_unsigned_numeric(word) or is_positive_numeric(word) or is_negative_numeric(word)

def get_numeric(word: str) -> int:
	return int(word)

def is_operand(word: str) -> bool:
	return is_numeric(word) or is_character(word) or is_label(word)








######## Assembler ########

if __name__ == "__main__":
	if len(argv) != 3:
		print("Incorrect number of arguments. Use the following format:")
		print("assembler.py [INPUT_ASSEMBLY_CODE_FILEPATH] [OUTPUT_BINARY_CODE_FILEPATH]")
		exit(-1)
	if not argv[1].endswith(".ASM"):
		print("Input file must end with a .ASM extension.")
		exit(-1)
	if not argv[2].endswith(".BIN"):
		print("Output file must end with a .BIN extension.")
		exit(-1)
	try:
		file = open(argv[1], "r");
	except:
		print("Cannot read input file: %s" % (argv[1]))
		exit(-1)

	assembly_code = file.readlines()
	machine_code = []
	label_addresses = {}
	######## First Pass Get Label Adddress Covert Opcodes and Raw Data ########
	for number, contents in enumerate(assembly_code):
		words = contents.split()
		first = words[0] if len(words) > 0 else None
		second = words[1] if len(words) > 1 else None
		third = words[2] if len(words) > 2 else None
		if is_comment_or_none(first):
			continue
		elif is_label_define(first) and is_comment_or_none(second):
			label_addresses[get_label_define(first)] = len(machine_code)
		elif is_character(first) and is_comment_or_none(second):
			machine_code.append(get_character(first))
		elif is_numeric(first) and is_comment_or_none(second):
			machine_code.append(get_numeric(first))
		elif first == "LOAD_I" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(0)
			machine_code.append(second)
		elif first == "LOAD" and is_comment_or_none(second):
			machine_code.append(1)
		elif first == "LOAD_A" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(2)
			machine_code.append(second)
		elif first == "SWAP" and is_comment_or_none(second):
			machine_code.append(3)
		elif first == "ADD" and is_comment_or_none(second):
			machine_code.append(4)
		elif first == "SUB"  and is_comment_or_none(second):
			machine_code.append(5)
		elif first == "SAVE" and is_comment_or_none(second):
			machine_code.append(6)
		elif first == "SAVE_A" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(7)
			machine_code.append(second)
		elif first == "JUMP"  and is_comment_or_none(second):
			machine_code.append(8)
		elif first == "JUMP_A" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(9)
			machine_code.append(second)
		elif first == "JUMP_Z" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(10)
			machine_code.append(second)
		elif first == "JUMP_P" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(11)
			machine_code.append(second)
		elif first == "JUMP_N" and is_operand(second) and is_comment_or_none(third):
			machine_code.append(12)
			machine_code.append(second)
		elif first == "HALT" and is_comment_or_none(second):
			machine_code.append(13)
		else:
			print("Invalid syntax at line %d" % (number + 1))
			exit(-1)
	######## Second Pass Covert Opcode Operands ########
	for number, contents in enumerate(machine_code):
		if not type(contents) == str:
			continue
		elif is_character(contents):
			machine_code[number] = get_character(contents)
		elif is_numeric(contents):
			machine_code[number] = get_numeric(contents)
		elif is_label(contents):
			label = get_label(contents)
			if label not in label_addresses:
				print("Undefined label used on line %d" % (number + 1))
				exit(-1)
			machine_code[number] = label_addresses[label]
		else:
			print("Invalid operand %s" % (contents))
			exit(-1)
	######## Write Machine Code ########
	bin = binary("./c_dll.so")
	if not bin:
		print("Cound not load c_dll.so")
		exit(-1)
	if not bin.write(argv[2], machine_code):
		print("Cannot write output file: %s" % (argv[2]))
		exit(-1)











