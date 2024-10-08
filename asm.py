from sys import argv

#ONLY MODIFY THESE TWO VARIABLES.
OPCODE_WIDTH = 3
ADDRESS_WIDTH = 13

DATA_WIDTH = OPCODE_WIDTH + ADDRESS_WIDTH
ADDRESS_SPACE = (1 << ADDRESS_WIDTH)
INPUT_UNIT_ADDRESS = (ADDRESS_SPACE - 2)
OUTPUT_UNIT_ADDRESS = (ADDRESS_SPACE - 1)

DIGIT = set("0123456789")
def is_number(word):
	return set(word).issubset(DIGIT)

LETTER = set("ABCDEFGHIJKLMNOPQRSTUVWXYZ_")
def is_label(word):
	return set(word).issubset(LETTER)

OPCODE = set(["ld", "st", "ad", "su", "ja", "js"])
def is_opcode(word):
	return set([word]).issubset(OPCODE)

def is_operation(words):
	return is_opcode(words[0]) and (is_label(words[1]) or is_number(word[1]))

def set_label(table, address, word):
	if word in table:
		print("Redefined label: %s" % (word))
		exit(-1)
	table[word] = address

def bits(num, width):
	bits = []
	for i in range(width):
		if num % 2 == 1:
			bits.insert(0, "1")
		elif num % 2 == 0:
			bits.insert(0, "0")
		num //= 2
	return bits

def get_label(table, word, width):
	if not word in table:
		print("Undefined label: %s" % (word))
		exit(-1)
	return bits(table[word], width)

def get_number(word, width):
	return bits(int(word), width)

GET_OPCODE = {
"ld": bits(0, OPCODE_WIDTH),
"st": bits(1, OPCODE_WIDTH),
"ad": bits(2, OPCODE_WIDTH),
"su": bits(3, OPCODE_WIDTH),
"ja": bits(4, OPCODE_WIDTH),
"js": bits(5, OPCODE_WIDTH),
}

def get_operation(table, words):
	if is_label(words[1]):
		return GET_OPCODE[words[0]] + get_label(table, words[1], ADDRESS_WIDTH)
	if is_number(words[1]):
		return GET_OPCODE[words[0]] + get_number(words[1], ADDRESS_WIDTH)

if __name__ == "__main__":
	######## Check And Read Arguments ########
	if len(argv) != 3:
		print("Incorrect number of arguments. Use the following format:")
		print("asm.py [INPUT_ASSEMBLY_CODE_FILEPATH] [OUTPUT_BINARY_CODE_FILEPATH]")
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
	raw = file.read()
	file.close()
	words = raw.split()
	table = {"GETC": INPUT_UNIT_ADDRESS, "PUTC": OUTPUT_UNIT_ADDRESS}
	a = 0
	i = 0
	while i < len(words):
		if is_label(words[i]):
			set_label(table, a, words[i])
			i += 1
			continue
		if is_number(words[i]):
			a += 1
			i += 1
			continue
		if is_operation(words[i:i+2]):
			a += 1
			i += 2
			continue
		print("Invalid syntax: %s" % (words[i]))
		exit(-1)
	######## Second Pass Check Convert To Binary ########
	code = []
	i = 0
	while i < len(words):
		if is_label(words[i]):
			i += 1
			continue
		if is_number(words[i]):
			code.append(get_number(words[i], DATA_WIDTH))
			i += 1
			continue
		if is_operation(words[i:i+2]):
			code.append(get_operation(table, words[i:i+2]))
			i += 2
			continue
		print("Invalid syntax: %s" % (words[i]))
		exit(-1)
	######## Write Machine Code And Output Result ########
	lines = ["".join(l) for l in code]
	try:
		file = open(argv[2], "w");
	except:
		print("Cannot write output file: %s" % (argv[2]))
		exit(-1)
	for l in lines:
		file.write(l + "\n")
	file.close()
	print("Size %d:" % (a))
	for l in lines:
		print(l)
	print("Labels:")
	for key in table:
		print("  %s: %d" % (key, table[key]))
