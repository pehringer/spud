from simulator.binary import *
from simulator.simulation import *
import os
import sys
import time

######## Const Vars ########

MINIMUM_LINES = 40
MINIMUM_COLUMNS = 40

####### Init Window ########

size = os.get_terminal_size()
lines = size.lines
columns = size.columns
if lines < MINIMUM_LINES or columns < MINIMUM_COLUMNS:
	print("Terminal window of (" + str(lines) + "X" + str(columns) + ") is too small.")
	print("Minimum window size (" + str(MINIMUM_LINES) + "X" + str(MINIMUM_COLUMNS) + ").")
	exit(1)

####### Init Simulation ########

bin = binary("./simulator/c_dll.so")
sim = simulation("./simulator/c_dll.so")
bin_file = bin.new(b"machine_code/hello_world.BIN")
sim_state = sim.new(b"machine_code/hello_world.BIN")
if bin_file == 0 or sim_state == 0:
	bin.delete(bin_file)
	sim.delete(sim_state)
	print("Cannot open BIN file.")
	exit(2)

######## Run and Display Simulation ########

# Create new lines terminal.
for line in range(lines):
	print()

while sim.clock_cycle(sim_state) != 0:

	# Save cursor output postion and goto the top of screen.
	print("\033[s\033[H\033[2K", end="")

	# Print Processor State.
	print("                                    ")
	print("State_______________________________")
	print("                                    ")
	print("%11d Data Bus                " % (sim_state.contents.data_bus))
	print("%11d Address Bus             " % (sim_state.contents.address_bus))
	print("%11d Instruction Register    " % (sim_state.contents.instruction_register))
	print("%11d Accumulator Register    " % (sim_state.contents.accumulator_register))
	print("%11d Program Counter Register" % (sim_state.contents.program_counter_register))
	print("%11d Temporary Register      " % (sim_state.contents.temporary_register))
	print("%11d Operand Register        " % (sim_state.contents.operand_register))
	print("                                    ")
	print("Program_____________________________")
	print("                                    ")
	pc = sim_state.contents.program_counter_register
	for line in range(pc - 8, pc + 9):
		if line < 0 or line >= bin_file.contents.size:
			print("        |                            ")
			continue
		print("%7d | %d" % (line, bin_file.contents.data[line]), end="")
		if line == pc:
			print(" <<<<<<<<        ")
		else:
			print("                 ")
	print("                                    ")
	print("Output______________________________")
	print("                                    ")
	print("\033[u", end="")
	sys.stdout.flush()
	time.sleep(0.02)
