build: build_exe

build_exe: compile_exe link_exe clean_exe

compile_exe:
	gcc -I ./include ./src/backend.c -c
	gcc -I ./include ./src/frontend.c -c
	gcc -I .//include ./src/simulator.c -c

link_exe:
	gcc backend.o frontend.o simulator.o -o sim

clean_exe:
	rm backend.o
	rm frontend.o
	rm simulator.o
