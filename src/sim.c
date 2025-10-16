#include "sim.h"

void InputUnit(struct Simulation *s) {
    int value = 0;
    for(int i = 0; i < DATA_WIDTH; i++) {
        if(s->memory[INPUT_UNIT_ADDRESS][i]) {
            value |= 1 << i;
        }
    }
    if(!value) {
        value = getc(stdin);
        for(int i = 0; i < DATA_WIDTH && i < 8; i++) {
            s->memory[INPUT_UNIT_ADDRESS][i] = 1 & value >> i;
        }
    }
}

void OutputUnit(struct Simulation *s) {
    int value = 0;
    for(int i = 0; i < DATA_WIDTH; i++) {
        if(s->memory[OUTPUT_UNIT_ADDRESS][i]) {
            value |= 1 << i;
        }
    }
    if(value) {
        putc(value, stdout);
        fflush(stdout);
        for(int i = 0; i < DATA_WIDTH; i++) {
            s->memory[OUTPUT_UNIT_ADDRESS][i] = 0;
        }
    }
}

char Opcode(char *source) {
    char opcode = 0;
    for(int i = 0; i < OPCODE_WIDTH; i++) {
        if(source[ADDRESS_WIDTH + i]) {
            opcode |= 1 << i;
        }
    }
    return opcode;
}

int Address(char *source) {
    int address = 0;
    for(int i = 0; i < ADDRESS_WIDTH; i++) {
        if(source[i]) {
            address |= 1 << i;
        }
    }
    return address;
}

char Datapath(char *destination, char *source, char *memory, char width, char not, char carry) {
    for(int i = 0; i < width; i++) {
        char value = 0;
        if(memory && memory[i]) {
            value++;
        }
        if(not) {
            value++;
        }
        value %= 2;
        if(source && source[i]) {
            value++;
        }
        if(carry) {
            value++;
        }
        carry = value > 1;
        destination[i] = value % 2;
    }
    return carry;
}

int ProcessorUnit(struct Simulation *s) {
    Datapath(s->ir, 0, s->memory[Address(s->ip)], DATA_WIDTH, 0, 0);
    Datapath(s->ip, s->ip, 0, ADDRESS_WIDTH, 0, 1);
    char opcode = Opcode(s->ir);
    if(opcode == 0) {
        s->ac[CARRY_BIT] = Datapath(s->ac, 0, s->memory[Address(s->ir)], DATA_WIDTH, 0, 0);
    }
    if(opcode == 1) {
        Datapath(s->memory[Address(s->ir)], s->ac, 0, DATA_WIDTH, 0, 0);
    }
    if(opcode == 2) {
        s->ac[CARRY_BIT] = Datapath(s->ac, s->ac, s->memory[Address(s->ir)], DATA_WIDTH, 0, 0);
    }
    if(opcode == 3) {
        s->ac[CARRY_BIT] = Datapath(s->ac, 0, s->memory[Address(s->ir)], DATA_WIDTH, 1, 0);
    }
    if(opcode == 4) {
        Datapath(s->ip, s->ir, 0, ADDRESS_WIDTH, 0, 0);
    }
    if(opcode == 5 && s->ac[SIGN_BIT]) {
        Datapath(s->ip, s->ir, 0, ADDRESS_WIDTH, 0, 0);
    }
    if(opcode == 6 && s->ac[CARRY_BIT]) {
        Datapath(s->ip, s->ir, 0, ADDRESS_WIDTH, 0, 0);
    }
    if(opcode == 7) {
        return Address(s->ir);
    }
    return RUNNING;
}

int SimulateCycle(struct Simulation *s) {
    InputUnit(s);
    OutputUnit(s);
    return ProcessorUnit(s);
}

void LoadSimulation(struct Simulation *s, FILE *bin) {
    for(int i = 0; i < ACCUMULATOR_WIDTH; i++) {
        s->ac[i] = 0;
        if(i < DATA_WIDTH) {
            s->ir[i] = 0;
            s->memory[INPUT_UNIT_ADDRESS][i] = 1 & '\n' >> i;
            s->memory[OUTPUT_UNIT_ADDRESS][i] = 0 & '\0' >> i;
        }
        if(i < ADDRESS_WIDTH) {
            s->ip[i] = 0;
        }
    }
    int address = 0;
    int bit = 15;
    while((s->memory[address][bit] = getc(bin)) != EOF) {
        if(s->memory[address][bit] == '0' || s->memory[address][bit] == '1') {
            s->memory[address][bit] -= '0';
            bit--;
        }
        if(bit < 0) {
            address++;
            bit = 15;
        }
    }
    s->memory[address][bit] = 0;
}
