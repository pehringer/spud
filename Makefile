build: build_sim build_exam

build_sim: compile_sim link_sim clean_sim

compile_sim:
	gcc -I include src/backend.c -c
	gcc -I include src/frontend.c -c
	gcc -I include src/simulator.c -c

link_sim:
	gcc backend.o frontend.o simulator.o -o sim.bin

clean_sim:
	rm backend.o
	rm frontend.o
	rm simulator.o

build_exam:
	python asm.py examples/asm/echo.asm examples/bin/echo.bin
	python asm.py examples/asm/hello_world.asm examples/bin/hello_world.bin
