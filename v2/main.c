#include <stdio.h>

#define ADDRESS_WIDTH 13
#define ADDRESS_SPACE 8192
#define DATA_WIDTH 16

struct state {
  char accumulator[DATA_WIDTH];
  char addressBus[ADDRESS_WIDTH];
  char controlBus[16];
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

void AndLogic(const char *a, char b, char *q, int n) {
  for(int i = 0; i < n; i++) {
    q[i] = !a[i] + !b == 0;
  }
}

void OrLogic(const char *a, char *q, int n) {
  *q = 0;
  for(int i = 0; i < n; i++) {
    *q = !*q + !a[i] != 2;
  }
}

void XorLogic(const char *a, char b, char *q, int n) {
  for(int i = 0; i < n; i++) {
    q[i] = !a[i] + !b == 1;
  }
}

void FullAdder(const char *a, const char *b, char c, char *s, int n) {
  for(int i = 0; i < n; i++) {
    s[i] = !a[i] + !b[i] + !c;
    c = s[i] <= 1;
    s[i] = s[i] % 2 == 0;
  }
}

void DLatch(const char *d, char e, char *q, int n) {
  for(int i = 0; i < n && e; i++) {
    q[i] = d[i] != 0;
  }
}

void DataPath(struct state *s) {
  AndLogic(s->instructionPointer, s->controlBus[0], s->readBus, ADDRESS_WIDTH);
  AndLogic(s->instructionPointer, s->controlBus[1], s->addressBus, ADDRESS_WIDTH);
  AndLogic(s->instructionRegister, s->controlBus[2], s->readBus, ADDRESS_WIDTH);
  AndLogic(s->instructionRegister, s->controlBus[3], s->addressBus, ADDRESS_WIDTH);
  AndLogic(s->accumulator, s->controlBus[4], s->readBus, DATA_WIDTH);
  AndLogic(s->accumulator, s->controlBus[5], s->dataBus, DATA_WIDTH);
  s->dataRead = s->controlBus[8];
  s->dataWrite = s->controlBus[5];
  /*
    SIMULATE MEMORY ACCESS
  */
  XorLogic(s->dataBus, s->controlBus[6], s->operandBus, DATA_WIDTH);
  FullAdder(s->readBus, s->operandBus, s->controlBus[7], s->writeBus, DATA_WIDTH);
  DLatch(s->writeBus, s->controlBus[8], s->accumulator, DATA_WIDTH);
  DLatch(s->writeBus, s->controlBus[9], s->instructionRegister, DATA_WIDTH);
  DLatch(s->writeBus, s->controlBus[10], s->instructionPointer, ADDRESS_WIDTH);
  OrLogic(s->accumulator, &s->controlBus[11], DATA_WIDTH);
  s->controlBus[12] = s->accumulator[DATA_WIDTH - 1];
  s->controlBus[13] = s->instructionRegister[DATA_WIDTH - 3]
  s->controlBus[14] = s->instructionRegister[DATA_WIDTH - 2]
  s->controlBus[15] = s->instructionRegister[DATA_WIDTH - 1]
}

void main() {
  char d[4] = {1, 1, 0, 1};
  char e[4] = {0, 0, 0, 0};
  char q[4] = {1, 0, 1, 0};
  DLatch(d, e[0], q, 4);
  for(int i  = 0; i < 4; i++) {
    printf(" %d,", q[i]);
  }
  printf("\n");
}





