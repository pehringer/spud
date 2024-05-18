build: build_bin

build_bin: compile_bin link_bin clean_bin

compile_bin:
	gcc -I simulator/include simulator/src/backend.c -c
	gcc -I simulator/include simulator/src/frontend.c -c
	gcc -I simulator/include simulator/src/simulator.c -c

link_bin:
	gcc backend.o frontend.o simulator.o -o sim.bin

clean_bin:
	rm backend.o
	rm frontend.o
	rm simulator.o
