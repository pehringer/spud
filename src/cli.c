#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char **argv) {
    if(argc != 2) {
        printf("Incorrect number of arguments. Use the following format:\n");
        printf("./sim.bin [INPUT_BINARY_CODE_FILEPATH]\n");
        exit(-1);
    }
    size_t length = strlen(argv[1]);
    if (4 > length) {
        printf("Input file must end with a .bin extension.\n");
        exit(-1);
    }
    if(strncmp(argv[1] + length - 4, ".bin", 4) != 0) {
        printf("Input file must end with a .bin extension.\n");
        exit(-1);
    }
    FILE *file = fopen(argv[1], "r");
    if(!file) {
        printf("Cannot read input file: %s\n", argv[1]);
        exit(-1);
    }
    struct Simulation s;
    LoadSimulation(&s, file);
    fclose(file);
    int state = SimulateCycle(&s);
    while(state == RUNNING) {
        state = SimulateCycle(&s);
    }
    printf("\nHALTED: %d\n", state);
}
