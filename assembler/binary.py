import ctypes
import os








######## Wrap DLL Structs ########

class struct_binary(ctypes.Structure):
	_fields_ = [
		("size", ctypes.c_int),
		("data", ctypes.POINTER(ctypes.c_int))
	]








######## Wrap DLL Functions ########

class binary:
	def __init__(self, c_dll_path: str):
		######## Load DLL ########
		c_dll = ctypes.CDLL(c_dll_path)
		######## Wrapper binary_write ########
		self._write = c_dll.binary_write
		self._write.argtypes = [ctypes.POINTER(ctypes.c_char), ctypes.POINTER(struct_binary)]
		self._write.restype = ctypes.c_int
		######## Wrapper binary_new ########
		self._read = c_dll.binary_read
		self._read.argtypes = [ctypes.POINTER(ctypes.c_char)]
		self._read.restype = ctypes.POINTER(struct_binary)
		######## Wrapper binary_delete ########
		self._free = c_dll.binary_free
		self._free.argtypes = [ctypes.POINTER(struct_binary)]

	def write(self, filepath: str, data: list[int]) -> int:
		bin = struct_binary()
		bin.size = len(data)
		bin.data = (ctypes.c_int * len(data))(*iter(data))
		path = ctypes.c_char_p(bytes(filepath, encoding="utf-8"))
		return self._write(path, bin)
