import ctypes
import os






######## Wrap DLL Structs ########
class struct_binary(ctypes.Structure):
	_fields_ = [
		("size", ctypes.c_int),
		("data", ctypes.POINTER(ctypes.c_int))
	]








class binary:
	def __init__(self):
		######## Load DLL ########
		try:
			c_dll = ctypes.CDLL("./c_dll.so")
		except:
			os.system("make")
			c_dll = ctypes.CDLL("./c_dll.so")
		######## Wrap DLL Functions ########
		self.write = c_dll.binary_write
		self.write.argtypes = [ctypes.POINTER(ctypes.c_char), ctypes.POINTER(struct_binary)]
		self.write.restype = ctypes.c_int
		self.new = c_dll.binary_new
		self.new.argtypes = [ctypes.POINTER(ctypes.c_char)]
		self.write.restype = ctypes.POINTER(struct_binary)
		self.delete = c_dll.binary_delete
		self.delete.argtypes = [ctypes.POINTER(struct_binary)]
		self.recreate_examples = c_dll.binary_recreate_examples
		self.recreate_examples.restype = ctypes.c_int








if __name__ == "__main__":
	bin = binary()
	bin.recreate_examples();
