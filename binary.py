import ctypes
import os






######## Wrap DLL Structs ########
class struct_binary(ctypes.Structure):
	_fields_ = [
		("size", ctypes.c_int),
		("data", ctypes.POINTER(ctypes.c_int))
	]








class binary:
	def __init__(self, c_dll_path: str):
		######## Load DLL ########
		c_dll = ctypes.CDLL(c_dll_path)
		######## Wrap DLL Functions ########
		self.write = c_dll.binary_write
		self.write.argtypes = [ctypes.POINTER(ctypes.c_char), ctypes.POINTER(struct_binary)]
		self.write.restype = ctypes.c_int
		self.new = c_dll.binary_new
		self.new.argtypes = [ctypes.POINTER(ctypes.c_char)]
		self.new.restype = ctypes.POINTER(struct_binary)
		self.delete = c_dll.binary_delete
		self.delete.argtypes = [ctypes.POINTER(struct_binary)]
		self.recreate_examples = c_dll.binary_recreate_examples
		self.recreate_examples.restype = ctypes.c_int
