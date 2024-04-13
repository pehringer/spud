build: build_exe build_dll build_bins

build_exe: compile_exe link_exe clean_exe

compile_exe:
	gcc -I simulator/include simulator/src/binary.c -c
	gcc -I simulator/include simulator/src/simulation.c -c
	gcc -I simulator/include simulator/src/simulator.c -c

link_exe:
	gcc binary.o simulation.o simulator.o -o simulator/simulator

clean_exe:
	rm binary.o
	rm simulation.o
	rm simulator.o

build_dll: compile_dll link_dll clean_dll

compile_dll:
	gcc -I simulator/include -fPIC simulator/src/binary.c -c
	gcc -I simulator/include -fPIC simulator/src/simulation.c -c

link_dll:
	gcc -shared binary.o simulation.o -o assembler/c_dll.so

clean_dll:
	rm binary.o
	rm simulation.o

build_bins:
	cd ./assembler; python assembler.py ../assembly_code/hello_world.ASM ../machine_code/hello_world.BIN
	cd ./assembler; python assembler.py ../assembly_code/echo.ASM ../machine_code/echo.BIN
