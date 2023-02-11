#ifndef SIMULATOR_H
#define SIMULATOR_H








#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include"binary_utils.h"








//Peripheral Addresses
#define ADDRESS_INPUT_REGISTER 1048576
#define ADDRESS_OUTPUT_REGISTER 1048577

//Peripheral Values
#define END_OF_INPUT '\n'
#define EMPTY 0

//Instruction Opcodes
#define LOAD_I 0
#define LOAD 1
#define LOAD_A 2
#define SWAP 3
#define ADD 4
#define SUB 5
#define SAVE 6
#define SAVE_A 7
#define JUMP 8
#define JUMP_A 9
#define JUMP_Z 10
#define JUMP_P 11
#define JUMP_N 12
#define HALT 13








struct simulation {
  uint64_t clock_count;
  uint32_t sign_unit_lines;//LSB 2 bits used.
  uint32_t control_unit_lines;//LSB 14 bits used.
  uint32_t data_bus;
  uint32_t address_bus;
  uint32_t instruction_register;
  uint32_t accumulator_register;
  uint32_t program_counter_register;
  uint32_t temporary_register;
  uint32_t operand_register;
  uint32_t input_register;
  uint32_t output_register;
  uint32_t memory[ADDRESS_INPUT_REGISTER];
};

struct simulation* new_simulation();

void delete_simulation(struct simulation *sim);

int simulate_clock_cycle(struct simulation *sim);








#endif
