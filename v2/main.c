#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define REGISTER_SIGN 0x8000
#define REGISTER_OPCODE 0xE000
#define REGISTER_ADDRESS 0x1FFF
#define CONTROL_OUT 0x07FF
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
#define CONTROL_IN 0xF800
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
  // Control Out
  s->addressBus = 0x0000;
  s->dataBus = 0x0000;
  s->readBus = 0x0000;
  s->writeBus = 0x0000;
  // 0
  s->readBus |= s->instructionPointer & (s->controlBus & CONTROL_OUT_0 ? 0xFFFF : 0x0000);
  // 1
  s->addressBus |= s->instructionPointer & (s->controlBus & CONTROL_OUT_1 ? REGISTER_ADDRESS : 0x0000);
  // 2
  s->readBus |= s->instructionRegister & (s->controlBus & CONTROL_OUT_2 ? 0xFFFF : 0x0000);
  // 3
  s->addressBus |= s->instructionRegister & (s->controlBus & CONTROL_OUT_3 ? REGISTER_ADDRESS : 0x0000);
  // 4
  s->readBus |= s->accumulator & (s->controlBus & CONTROL_OUT_4 ? 0xFFFF : 0x0000);
  // 5
  s->dataBus |= s->accumulator & (s->controlBus & CONTROL_OUT_5 ? 0xFFFF : 0x0000);
  s->dataWrite = s->controlBus & CONTROL_OUT_5;
  // 6
  s->dataBus ^= s->controlBus & CONTROL_OUT_6 ? 0xFFFF : 0x0000;
  // 7
  s->writeBus = s->readBus + s->databus + (s->controlBus & CONTROL_OUT_7 ? 0x0001 : 0x0000);
  // 8
  s->accumulator = s->controlBus & CONTROL_OUT_8 ? s->writeBus : s->accumulator;
  s->dataRead = s->controlBus & CONTROL_OUT_8;
  // 9
  s->instructionRegister = s->controlBus & CONTROL_OUT_9 ? s->writeBus : s->instructionRegister;
  // 10
  s->instructionPointer = s->controlBus & CONTROL_OUT_10 ? s->writeBus : s->instructionPointer;
  // Control In
  s->controlBus &= CONTROL_OUT;
  // 11
  s->controlBus |= s->accumulator & 0xFFFF ? CONTROL_IN_NON_ZERO : 0x0000;
  // 12
  s->controlBus |= s->accumulator & REGISTER_SIGN ? CONTROL_IN_SIGN_BIT : 0x0000;
  // 13-15
  s->controlBus |= s->instructionRegister & CONTROL_IN_OPCODE;
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





