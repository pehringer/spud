import ctypes
import os






######## Wrap DLL Structs ########
class struct_simulation(ctypes.Structure):
	_fields_ = [
		("clock_count", ctypes.c_uint64),
		("sign_unit_lines", ctypes.c_uint32),
		("control_unit_lines", ctypes.c_uint32),
		("data_bus", ctypes.c_uint32),
		("address_bus", ctypes.c_uint32),
		("instruction_register", ctypes.c_uint32),
		("accumulator_register", ctypes.c_uint32),
		("program_counter_register", ctypes.c_uint32),
		("temporary_register", ctypes.c_uint32),
		("operand_register", ctypes.c_uint32),
		("input_register", ctypes.c_uint32),
		("output_register", ctypes.c_uint64),
		("memory_unit", ctypes.POINTER(ctypes.c_uint32))
	]








class simulation:
	def __init__(self, c_dll_path: str):
		######## Load DLL ########
		c_dll = ctypes.CDLL(c_dll_path)
		######## Wrap DLL Functions ########
		self.new = c_dll.simulation_new
		self.new.argtypes = [ctypes.POINTER(ctypes.c_char)]
		self.new.restype = ctypes.POINTER(struct_simulation)
		self.delete = c_dll.simulation_delete
		self.delete.argtypes = [ctypes.POINTER(struct_simulation)]
		self.clock_cycle = c_dll.simulation_clock_cycle
		self.clock_cycle.argtypes = [ctypes.POINTER(struct_simulation)]
		self.clock_cycle.restype = ctypes.c_int
