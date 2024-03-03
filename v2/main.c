#include <stdio.h>

#define ADDRESS_WIDTH 13
#define ADDRESS_SPACE 8192
#define DATA_WIDTH 16

struct state {
  // Only valid char values are 0 or 1.
  char accumulator[DATA_WIDTH];
  char addressBus[ADDRESS_WIDTH];
  char controlBus[18];
  char dataBus[DATA_WIDTH];
  char dataRead;
  char dataWrite;
  char instructionPointer[ADDRESS_WIDTH];
  char instructionRegister[DATA_WIDTH];
  char memory[ADDRESS_SPACE][DATA_WIDTH];
  char operandBus[DATA_WIDTH];
  char readBus[DATA_WIDTH];
  char writeBus[DATA_WIDTH];
};

void AndLogic(const char *a, char b, char *q, int width) {
  for(int i = 0; i < width; i++) {
    q[i] = a[i] + b == 2;
  }
}

void OrLogic(const char *a, char *q) {
  *q = 0;
  for(int i = 0; i < DATA_WIDTH; i++) {
    *q = *q + a[i] != 0;
  }
}

void XorLogic(const char *a, char b, char *q) {
  for(int i = 0; i < DATA_WIDTH; i++) {
    q[i] = a[i] + b == 1;
  }
}

void FullAdder(const char *a, const char *b, char c, char *s) {
  for(int i = 0; i < DATA_WIDTH; i++) {
    s[i] = a[i] + b[i] + c;
    c = s[i] > 1;
    s[i] = s[i] % 2 != 0;
  }
}

void DLatch(const char *d, char e, char *q, int width) {
  for(int i = 0; i < width && e; i++) {
    q[i] = d[i];
  }
}

void ControlUnitFetch(char *c) {
  c[0] = 0;
  c[1] = 1;
  c[2] = 0;
  c[3] = 0;
  c[4] = 0;
  c[5] = 0;
  c[6] = 1;
  c[7] = 0;
  c[8] = 0;
  c[9] = 0;
  c[10] = 0;
  c[11] = 1;
  c[12] = 0;
}

void ControlUnitDecode(char *c) {
  c[0] = 1;
  c[1] = 0;
  c[2] = 0;
  c[3] = 0;
  c[4] = 0;
  c[5] = 0;
  c[6] = 0;
  c[7] = 0;
  c[8] = 0;
  c[9] = 1;
  c[10] = 0;
  c[11] = 0;
  c[12] = 1;
}

void ControlUnitExecute(char *c) {
  if(!c[15] && !c[16] && !c[17]) {
  }
  if(!c[15] && !c[16] && c[17]) {
  }
  if(!c[15] && c[16] && !c[17]) {
  }
  if(!c[15] && c[16] && c[17]) {
  }
  if(c[15] && !c[16] && !c[17] && c[14]) { //JN
  }
  if(c[15] && !c[16] && c[17]) && !c[14] && c[13]{ //JP
  }
  if(c[15] && c[16] && !c[17] && !c[13]) { //JZ
  }
  if(c[15] && c[16] && c[17]) { //JA
  }
}

void MemoryUnit(struct state *s) {
  int a = 0;
  for(int i = 0, v = 1; i < ADDRESS_WIDTH; i++, v *= 2) {
    a += s->addressBus[i] * v;
  }
  for(int i = 0; i < DATA_WIDTH && s->dataRead; i++) {
    s->dataBus[i] = s->memory[a][i];
  }
  for(int i = 0; i < DATA_WIDTH && s->dataWrite; i++) {
    s->memory[a][i] = s->dataBus[i];
  }
}

void DataPath(struct state *s) {
  AndLogic(s->instructionPointer, s->controlBus[0], s->readBus, ADDRESS_WIDTH);
  AndLogic(s->instructionPointer, s->controlBus[1], s->addressBus, ADDRESS_WIDTH);
  AndLogic(s->instructionRegister, s->controlBus[2], s->readBus, ADDRESS_WIDTH);
  AndLogic(s->instructionRegister, s->controlBus[3], s->addressBus, ADDRESS_WIDTH);
  AndLogic(s->accumulator, s->controlBus[4], s->readBus, DATA_WIDTH);
  AndLogic(s->accumulator, s->controlBus[5], s->dataBus, DATA_WIDTH);
  s->dataRead = s->controlBus[6];
  s->dataWrite = s->controlBus[7];
  MemoryUnit(s);
  XorLogic(s->dataBus, s->controlBus[8], s->operandBus);
  FullAdder(s->readBus, s->operandBus, s->controlBus[9], s->writeBus);
  DLatch(s->writeBus, s->controlBus[10], s->accumulator, DATA_WIDTH);
  DLatch(s->writeBus, s->controlBus[11], s->instructionRegister, DATA_WIDTH);
  DLatch(s->writeBus, s->controlBus[12], s->instructionPointer, ADDRESS_WIDTH);
  OrLogic(s->accumulator, &s->controlBus[13]);
  s->controlBus[14] = s->accumulator[DATA_WIDTH - 1];
  s->controlBus[15] = s->instructionRegister[DATA_WIDTH - 3];
  s->controlBus[16] = s->instructionRegister[DATA_WIDTH - 2];
  s->controlBus[17] = s->instructionRegister[DATA_WIDTH - 1];
}

void main() {
  char a[4] = {1, 0, 1, 0};
  char b[4] = {1, 0, 0, 0};
  char c[4] = {0, 0, 0, 0};
  char q[4] = {0, 0, 0, 0};
  XorLogic(a, b[0], q);
  for(int i  = 0; i < 4; i++) {
    printf(" %d,", !!q[i]);
  }
  printf("\n");
}





