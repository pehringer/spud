from sys import argv

ESC_CHARS = set(["'\\s'", "'\\n'", "'\\t'", "'\\0'"])
LAB_CHARS = set("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")
BIN_DIGITS = set("01")
DEC_DIGITS = set("-+0123456789")
HEX_DIGITS = set("0123456789abcdefABCDEF")
OPS_ABBREV = set(["GET", "SET", "ADD", "SUB", "ANY", "NEG"])


DATA_SIZE = 16
ADDRESS_SPACE = 8192
INPUT_ADDRESS = 8190
OUTPUT_ADDRESS = 8191


def is_empty(word):
	return not word


def is_comment(word):
	return word[0] == ";"


def is_definition(word):
	return not word[0].isnumeric() and set(word[:-1]).issubset(LAB_CHARS) and word[-1] == ":"


def is_instruction(word):
	return set([word]).issubset(OPS_ABBREV)


def is_reference(word):
	return not word[0].isnumeric() and not set([word]).issubset(OPS_ABBREV) and set(word).issubset(LAB_CHARS)


def is_binary(word):
	return word[:2] == "0b" and set(word[2:]).issubset(BIN_DIGITS)


def is_decimal(word):
	return set(word).issubset(DEC_DIGITS)


def is_hexadecimal(word):
	return word[:2] == "0x" and set(word[2:]).issubset(HEX_DIGITS)


def is_character(word):
	return set(word).issubset(ESC_CHARS) or (len(word) == 3 and word[0] == "'" and word[2] == "'")


def bits(num):
	bits = []
	for i in range(DATA_SIZE):
		if num % 2 == 1:
			bits.append("1")
		if num % 2 == 0:
			bits.append("0")
		num //= 2
	return bits


def get_definition(word):
	return word[:-1]


def get_instruction(word):
	if word == "GET":
		return ["0", "0", "0"]
	if word == "SET":
		return ["1", "0", "0"]
	if word == "ADD":
		return ["0", "1", "0"]
	if word == "SUB":
		return ["1", "1", "0"]
	if word == "ANY":
		return ["0", "0", "1"]
	if word == "NEG":
		return ["1", "0", "1"]
	print("Invalid instruction: %s" % (word))
	exit(-1)


def get_reference(label_lookup, label):
	if label in label_lookup:
		return bits(label_lookup[label])
	print("Undefined label: %s" % (label))
	exit(-1)


def get_binary(word):
	return bits(int(word[2:], 2))


def get_decimal(word):
	return bits(int(word))


def get_hexadecimal(word):
	return bits(int(word[2:], 16))


def get_character(word):
	return bits(ord(word[1:-1]))


if __name__ == "__main__":
	######## Check And Read Arguments ########
	if len(argv) != 3:
		print("Incorrect number of arguments. Use the following format:")
		print("assembler.py [INPUT_ASSEMBLY_CODE_FILEPATH] [OUTPUT_BINARY_CODE_FILEPATH]")
		exit(-1)
	if not argv[1].endswith(".asm"):
		print("Input file must end with a .asm extension.")
		exit(-1)
	if not argv[2].endswith(".bin"):
		print("Output file must end with a .bin extension.")
		exit(-1)
	try:
		file = open(argv[1], "r");
	except:
		print("Cannot read input file: %s" % (argv[1]))
		exit(-1)
	######## First Pass Check Syntax And Get Label Adddresses ########
	assembly_code = file.readlines()
	file.close()
	next_address = 0
	label_lookup = {"putc": OUTPUT_ADDRESS, "getc": INPUT_ADDRESS}
	for number, contents in enumerate(assembly_code):
		words = contents.split()
		first = words[0] if len(words) > 0 else None
		second = words[1] if len(words) > 1 else None
		third = words[2] if len(words) > 2 else None
		if is_empty(first) or is_comment(first):
			continue
		if is_definition(first):
			if not is_empty(second) and not is_comment(second):
				print("Invalid syntax after label definition: %s" % (number+1))
				exit(-1)
			label_lookup[get_definition(first)] = next_address
			continue
		if is_reference(first) or is_binary(first) or is_decimal(first) or is_hexadecimal(first) or is_character(first):
			if not is_empty(second) and not is_comment(second):
				print("Invalid syntax after immediate value: %s" % (number+1))
				exit(-1)
			next_address += 1
			continue
		if is_instruction(first):
			if is_empty(second) or not (is_reference(second) or is_binary(second) or is_decimal(second) or is_hexadecimal(second) or is_character(second)):
				print("Invalid syntax after instruction opcode: %s" % (number+1))
				exit(-1)
			if not is_empty(third) and not is_comment(third):
				print("Invalid syntax after instruction operand: %s" % (number+1))
				exit(-1)
			next_address += 1
			continue
		print("Invalid syntax: %s" % (number+1))
		exit(-1)
	######## Second Pass Check Convert To Binary ########
	machine_code = []
	for number, contents in enumerate(assembly_code):
		words = contents.split()
		first = words[0] if len(words) > 0 else None
		second = words[1] if len(words) > 1 else None
		if is_empty(first) or is_comment(first) or is_definition(first):
			continue
		if is_reference(first):
			machine_code.append(get_reference(label_lookup, first))
			continue
		if is_binary(first):
			machine_code.append(get_binary(first))
			continue
		if is_decimal(first):
			machine_code.append(get_decimal(first))
			continue
		if is_hexadecimal(first):
			machine_code.append(get_hexadecimal(first))
			continue
		if is_character(first):
			machine_code.append(get_character(first))
			continue
		if is_instruction(first):
			opcode = get_instruction(first)
			if is_reference(second):
				machine_code.append(get_reference(label_lookup, second)[:-3] + opcode)
				continue
			if is_binary(second):
				machine_code.append(get_binary(second)[:-3] + opcode)
				continue
			if is_decimal(second):
				machine_code.append(get_decimal(second)[:-3] + opcode)
				continue
			if is_hexadecimal(second):
				machine_code.append(get_hexacimal(second)[:-3] + opcode)
				continue
			if is_character(second):
				machine_code.append(get_character(second)[:-3] + opcode)
				continue
		print("Error converting to machine code: %s" % (number+1))
		exit(-1)
	######## Write Machine Code And Output Result ########
	lines = ["".join(l) for l in machine_code]
	try:
		file = open(argv[2], "w");
	except:
		print("Cannot write output file: %s" % (argv[2]))
		exit(-1)
	for l in lines:
		file.write(l + "\n")
	file.close()
	print("Size %d:" % (next_address))
	for l in lines:
		print(l)
	print("Labels:")
	for key in label_lookup:
		print("  %s: %d" % (key, label_lookup[key]))







