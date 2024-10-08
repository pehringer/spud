#ifndef BACKEND_H
#define BACKEND_H

#include <stdio.h>

//ONLY MODIFY THESE TWO DEFINES.
#define OPCODE_WIDTH 3
#define ADDRESS_WIDTH 13

#define DATA_WIDTH (OPCODE_WIDTH + ADDRESS_WIDTH)
#define SIGN_BIT (DATA_WIDTH - 1)
#define ADDRESS_SPACE (1 << ADDRESS_WIDTH)
#define INPUT_UNIT_ADDRESS (ADDRESS_SPACE - 2)
#define OUTPUT_UNIT_ADDRESS (ADDRESS_SPACE - 1)

struct Simulation {
    char ac[DATA_WIDTH];
    char ip[ADDRESS_WIDTH];
    char ir[DATA_WIDTH];
    char memory[ADDRESS_SPACE][DATA_WIDTH];
};

void LoadSimulation(struct Simulation *s, FILE *bin);
void SimulateCycle(struct Simulation *s);

#endif
