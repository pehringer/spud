build: compile link clean

compile:
	gcc -I include -fPIC -c src/binary.c
	gcc -I include -fPIC -c src/simulation.c

link:
	gcc -shared binary.o simulation.o -o c_dll.so

clean:
	rm binary.o
	rm simulation.o
