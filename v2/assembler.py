from sys import argv

ESC_CHARS = set(["'\\s'", "'\\n'", "'\\t'", "'\\0'"])
LAB_CHARS = set("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
BIN_DIGITS = set("01")
DEC_DIGITS = set("0123456789")
HEX_DIGITS = set("0123456789abcdefABCDEF")
OPS_ABBREV = set(["GET", "SET", "ADD", "SUB", "ANY", "NEG"])


def is_empty(word):
	return not word


def is_comment(word):
	return word[0] == ";"


def is_definition(word):
	return set(word[:-1]).issubset(LAB_CHARS) and word[-1] == ":"


def is_instruction(word):
	return set(word).issubset(OPS_ABBREV)


def is_reference(word):
	return set(word).issubset(LAB_CHARS)


def is_binary(word):
	return word[:2] == "0b" and set(word[2:]).issubset(BIN_DIGITS)


def is_decimal(word):
	return set(word).issubset(DEC_DIGITS)


def is_hexadecimal(word):
	return word[:2] == "0x" and set(word[2:]).issubset(HEX_DIGITS)


def is_character(word):
	return set(word).issubset(ESC_CHARS) or (len(word) == 3 and word[0] == "'" and word[2] == "'")


def Get_definition(word):
	return word[:-1]


if __name__ == "__main__":
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

	assembly_code = file.readlines()
	next_address = 0
	label_lookup = {}
	######## First Pass Get Label Adddress Covert Opcodes and Raw Data ########
	for number, contents in enumerate(assembly_code):
		words = contents.split()
		start = words[0] if len(words) > 0 else None
		if is_empty(start):
			continue
		elif is_comment(start):
			continue
		elif is_definition(start):
			label_lookup[Get_definition(start)] = next_address
		elif is_instruction(start):
			next_address += 1
		elif is_reference(start):
			next_address += 1
		elif is_binary(start):
			next_address += 1
		elif is_decimal(start):
			next_address += 1
		elif is_hexadecimal(start):
			next_address += 1
		elif is_character(start):
			next_address += 1
		else:
			print("Invalid syntax at start of line: %s" % (number+1))
			exit(-1)
	print("Size %d" % (next_address))
	print("Labels:")
	for key in label_lookup:
		print("  %s: %d" % (key, label_lookup[key]))







