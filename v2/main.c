#include <stdio.h>

#define ADDRESS_WIDTH 13
#define ADDRESS_SPACE 8192
#define DATA_WIDTH 16

struct simulationState {
  char accumulator[DATA_WIDTH];
  char addressBus[ADDRESS_WIDTH];
  char controlBus[16];
  char dataBus[DATA_WIDTH];
  char dataRead;
  char dataWrite;
  char instructionPointer[ADDRESS_WIDTH];
  char instructionRegister[DATA_WIDTH];
  char memory[ADDRESS_SPACE][DATA_WIDTH];
  char readBus[DATA_WIDTH];
  char writeBus[DATA_WIDTH];
};

void simulateAndIC(const char *a, const char *b, char *q, int width) {
  for(int i = 0; i < width; i++) {
    q[i] = !a[i] + !*b == 0;
  }
}

void simulateOrIC(const char *a, char *q, int width) {
  *q = 0;
  for(int i = 0; i < width; i++) {
    *q = !*q + !a[i] != 2;
  }
}

void simulateXorIC(const char *a, const char *b, char *q, int width) {
  for(int i = 0; i < width; i++) {
    q[i] = !a[i] + !*b == 1;
  }
}

void simulateFullAdderIC(const char *a, const char *b, const char *c, char *s, int width) {
  int carry = *c;
  for(int i = 0; i < width; i++) {
    s[i] = !a[i] + !b[i] + !carry;
    carry = s[i] <= 1;
    s[i] = s[i] % 2 == 0;
  }
}
void main() {
  char a[4] = {1, 1, 1, 0};
  char b[4] = {1, 1, 0, 0};
  char c = 1;
  char q[4] = {0, 0, 0, 0};
  simulateFullAdderIC(a, b, &c, q, 4);
  for(int i  = 0; i < 4; i++) {
    printf(" %d,", q[i]);
  }
  printf("\n");
}





