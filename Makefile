build: build_exe build_dll

build_exe: compile_exe link_exe clean_exe

compile_exe:
	gcc -I include src/binary.c -c
	gcc -I include src/simulation.c -c
	gcc -I include src/visualizer.c -c

link_exe:
	gcc binary.o simulation.o visualizer.o -o simulator

clean_exe:
	rm binary.o
	rm simulation.o
	rm visualizer.o

build_dll: compile_dll link_dll clean_dll

compile_dll:
	gcc -I include -fPIC src/binary.c -c
	gcc -I include -fPIC src/simulation.c -c

link_dll:
	gcc -shared binary.o simulation.o -o c_dll.so

clean_dll:
	rm binary.o
	rm simulation.o

