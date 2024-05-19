#ifndef BACKEND_H
#define BACKEND_H


#include <stdio.h>


#define DATA_SIZE 16
#define ADDRESS_SPACE 8192
#define INPUT_ADDRESS 8190
#define OUTPUT_ADDRESS 8191


struct Simulation {
  char ac[DATA_SIZE];
  char ip[DATA_SIZE];
  char ir[DATA_SIZE];
  char memory[ADDRESS_SPACE][DATA_SIZE];
};


void InitializeSimulation(struct Simulation *s, FILE *bin);
void CycleSimulation(struct Simulation *s);


#endif
