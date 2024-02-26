#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define REGISTER_SIGN 0x8000
#define REGISTER_OPCODE 0xE000
#define REGISTER_ADDRESS 0x1FFF
#define CONTROL_OUT_0 0x0001
#define CONTROL_OUT_1 0x0002
#define CONTROL_OUT_2 0x0004
#define CONTROL_OUT_3 0x0008
#define CONTROL_OUT_4 0x0010
#define CONTROL_OUT_5 0x0020
#define CONTROL_OUT_6 0x0040
#define CONTROL_OUT_7 0x0080
#define CONTROL_OUT_8 0x0100
#define CONTROL_OUT_9 0x0200
#define CONTROL_OUT_10 0x0400
#define CONTROL_IN_NON_ZERO 0x0800
#define CONTROL_IN_SIGN_BIT 0x1000
#define CONTROL_IN_OPCODE 0xE000
#define CONTROL_LD 0x0000
#define CONTROL_AD 0x2000
#define CONTROL_SB 0x4000
#define CONTROL_ST 0x6000
#define CONTROL_JN 0x8000
#define CONTROL_JP 0xA000
#define CONTROL_JZ 0xC000
#define CONTROL_JA 0xE000

uint16_t simulateAndIc(uint16_t a, bool b) {
  return b ? a : 0x0000;
}

bool simulateOrIc(uint16_t a) {
  return a != 0x0000;
}

uint16_t simulateXorIc(uint16_t a, bool b) {
  return b ? ~a : a;
}

uint16_t simulateFullAdderIc(uint16_t a, uint16_t b, bool c) {
  return c ? a + b + 1 : a + b;
}

uint16_t simulateRegisterIC(uint16_t d, bool e, uint16_t q) {
  return e ? d : q
}

struct simulationState {
  uint16_t accumulator;
  uint16_t addressBus;
  uint16_t controlBus;
  uint16_t dataBus;
  bool dataRead;
  bool dataWrite;
  uint16_t instructionPointer;
  uint16_t instructionRegister;
  uint16_t memory[8192];
  uint16_t readBus;
  uint16_t writeBus;
};

void simulateDataPath(struct simulationState *s) {
}

void simulateControlUnitFetch(struct simulationState *s) {
}

void simulateControlUnitDecode(struct simulationState *s) {
}

void simulateControlUnitExecute(struct simulationState *s) {
}

void main() {
  printf("Hello, friend.\n");
}





