#include "backend.h"


void InputUnit(struct Simulation *s) {
  char value = 0;
  for(int i = 0; i < DATA_SIZE && i < 8; i++) {
    if(s->memory[INPUT_ADDRESS][i]) {
	value |= 1 << i;
    }
  }
  if(!value) {
    value = getc(stdin);
    for(int i = 0; i < DATA_SIZE && i < 8; i++) {
      s->memory[INPUT_ADDRESS][i] = 1 & value >> i;
    }
  }
}


void OutputUnit(struct Simulation *s) {
  char value = 0;
  for(int i = 0; i < DATA_SIZE && i < 8; i++) {
    if(s->memory[OUTPUT_ADDRESS][i]) {
      value |= 1 << i;
    }
  }
  if(value) {
    putc(value, stdout);
    fflush(stdout);
    for(int i = 0; i < DATA_SIZE && i < 8; i++) {
      s->memory[OUTPUT_ADDRESS][i] = 0;
    }
  }
}


char* Memory(struct Simulation *s, char *address) {
  int index = 0;
  for(int i = 0; i < DATA_SIZE-3; i++) {
    if(address[i]) {
      index |= 1 << i;
    }
  }
  return s->memory[index];
}


void Datapath(char *output, char *input0, char *input1, char not, char carry) {
  for(int i = 0; i < DATA_SIZE; i++) {
    char value = 0;
    if(input1 && input1[i]) {
      value++;
    }
    if(not) {
      value++;
    }
    value %= 2;
    if(input0 && input0[i]) {
      value++;
    }
    if(carry) {
      value++;
    }
    carry = value > 1;
    output[i] = value % 2;
  }
}


void ProcessorUnit(struct Simulation *s) {
  Datapath(s->ir, 0, Memory(s, s->ip), 0, 0);
  Datapath(s->ip, s->ip, 0, 0, 1);
  char opcode = 0;
  if(s->ir[DATA_SIZE-1]) {
    opcode |= 4;
  }
  if(s->ir[DATA_SIZE-2]) {
    opcode |= 2;
  }
  if(s->ir[DATA_SIZE-3]) {
    opcode |= 1;
  }
  if(opcode == 0) {
    Datapath(s->ac, 0, Memory(s, s->ir), 0, 0);
  }
  if(opcode == 1) {
    Datapath(Memory(s, s->ir), s->ac, 0, 0, 0);
  }
  if(opcode == 2) {
    Datapath(s->ac, s->ac, Memory(s, s->ir), 0, 0);
  }
  if(opcode == 3) {
    Datapath(s->ac, s->ac, Memory(s, s->ir), 1, 1);
  }
  if(opcode == 4) {
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
  if(opcode == 5 && s->ac[DATA_SIZE-1]) {
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
}


void CycleSimulation(struct Simulation *s) {
  InputUnit(s);
  OutputUnit(s);
  ProcessorUnit(s);
}


void InitializeSimulation(struct Simulation *s, FILE *bin) {
  for(int i = 0; i < DATA_SIZE && i < 8; i++) {
    s->ac[i] = 0;
    s->ip[i] = 0;
    s->ir[i] = 0;
    s->memory[INPUT_ADDRESS][i] = 1 & '\n' >> i;
    s->memory[OUTPUT_ADDRESS][i] = 0 & '\0' >> i;
  }
  char *mem = s->memory[0];
  while((*mem = getc(bin)) != EOF) {
    if(*mem == '0' || *mem == '1') {
      *mem -= '0';
      mem++;
    }
  }
  *mem = 0;
}

