build: build_sim build_exam

build_sim: compile_sim link_sim clean_sim

compile_sim:
	gcc -I ./include -c ./src/sim.c -o ./sim.o
	gcc -I ./include -c ./src/cli.c -o ./cli.o

link_sim:
	gcc ./sim.o ./cli.o -o ./sim.bin

clean_sim:
	rm ./sim.o
	rm ./cli.o

build_exam:
	python ./asm.py ./examples/asm/echo.asm ./examples/bin/echo.bin
	python ./asm.py ./examples/asm/hello.asm ./examples/bin/hello.bin
	python ./asm.py ./examples/asm/subtract_ones.asm ./examples/bin/subtract_ones.bin
	python ./asm.py ./examples/asm/subtract_twos.asm ./examples/bin/subtract_twos.bin
