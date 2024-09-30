#ifndef BACKEND_H
#define BACKEND_H


#include <stdio.h>


#define DATA_SIZE 16
#define ADDRESS_SPACE 4096
#define INPUT_ADDRESS 4094
#define OUTPUT_ADDRESS 4095


struct Simulation {
    char ac[DATA_SIZE];
    char ip[DATA_SIZE];
    char ir[DATA_SIZE];
    char memory[ADDRESS_SPACE][DATA_SIZE];
};


void LoadSimulation(struct Simulation *s, FILE *bin);
void SimulateCycle(struct Simulation *s);


#endif
