build: build_sim build_exam

build_sim: compile_sim link_sim clean_sim

compile_sim:
	gcc -I simulator/include simulator/src/backend.c -c
	gcc -I simulator/include simulator/src/frontend.c -c
	gcc -I simulator/include simulator/src/simulator.c -c

link_sim:
	gcc backend.o frontend.o simulator.o -o sim.bin

clean_sim:
	rm backend.o
	rm frontend.o
	rm simulator.o

build_exam:
	python asm.py example_asm/echo.asm example_bin/echo.bin
	python asm.py example_asm/hello_world.asm example_bin/hello_world.bin
