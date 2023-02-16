from sys import argv

if __name__ == "__main__":
	if len(argv) != 2:
		print("Incorrect number of arguments. Use the following format:")
		print("assembler.py [ASSEMBLY_CODE_FILEPATH]")
		exit()
	if not argv[1].endswith(".ASM"):
		print("File must end with a .ASM extension.")
		exit()
	try:
		file = open(argv[1], "r");
	except:
		print("Cannot open %s" % (argv[1]))
		exit()
	lines = file.readlines()
	for line in lines:
		print(line)
