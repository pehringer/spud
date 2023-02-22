#include"simulation.h"








//Control unit bitmasks.
#define LINE_READ_OPERAND_REGISTER_NOT 1       //Bit 0
#define LINE_WRITE_OPERAND_REGISTER 2          //Bit 1
#define LINE_READ_OPERAND_REGISTER 4           //Bit 2
#define LINE_WRITE_TEMPORARY_REGISTER 8        //Bit 3
#define LINE_READ_TEMPORARY_REGISTER 16        //Bit 4
#define LINE_WRITE_PROGRAM_COUNTER_REGISTER 32 //Bit 5
#define LINE_READ_PROGRAM_COUNTER_REGISTER 64  //Bit 6
#define LINE_WRITE_ACCUMULATOR_REGISTER 128    //Bit 7
#define LINE_WRITE_INSTRUCTION_REGISTER 256    //Bit 8
#define LINE_INPUT_RIGHT 512                   //Bit 9
#define LINE_INPUT_LEFT 1024                   //Bit 10
#define LINE_CARRY_IN 2048                     //Bit 11
#define LINE_WRITE_DATA_BUS 4096                 //Bit 12
#define LINE_READ_DATA_BUS 8192                  //Bit 13

//Sign unit bitmasks.
#define LINE_POSITIVE 1          //Bit 0
#define LINE_NEGATIVE 2          //Bit 1
#define POSITIVE_BITS 2147483647 //Bit 0-30
#define NEGATIVE_BITS 2147483648 //Bit 31








static int system_clock_cycle(struct simulation *sim) {
  /******* Simulate Control Unit *******/
  static const uint32_t CONTROL_UNIT_STATE[3][14][8] = {
    {//     Clock Count / Accumulator Register (0)
     //   0     1    2     3     4     5     6     7
      {8512, 2632, 560, 8258, 2632,  560,    0,    0}, //LOAD_I
      {8512, 2632, 560, 8204,  530,    0,    0,    0}, //LOAD
      {8512, 2632, 560, 8264, 8210, 2632,  560,    0}, //LOAD_A
      {8512, 2632, 560,  524, 1026,  656,    0,    0}, //SWAP
      {8512, 2632, 560, 1548,  656,    0,    0,    0}, //ADD
      {8512, 2632, 560, 3593,  656,    0,    0,    0}, //SUB
      {8512, 2632, 560, 5124,    0,    0,    0,    0}, //SAVE
      {8512, 2632, 560, 8264, 5136, 2632,  560,    0}, //SAVE_A
      {8512, 2632, 560,  524,  578,  560,    0,    0}, //JUMP
      {8512, 2632, 560, 8264,  560,    0,    0,    0}, //JUMP_A
      {8512, 2632, 560, 8264,  560,    0,    0,    0}, //JUMP_Z
      {8512, 2632, 560, 2632,  560,    0,    0,    0}, //JUMP_P
      {8512, 2632, 560, 2632,  560,    0,    0,    0}, //JUMP_N
      {8512, 2632, 560,    0,    0,    0,    0,    0}  //HALT
    },
    {//     Clock Count / Accumulator Register (+)
     //   0     1    2     3     4     5     6     7
      {8512, 2632, 560, 8258, 2632,  560,    0,    0}, //LOAD_I
      {8512, 2632, 560, 8204,  530,    0,    0,    0}, //LOAD
      {8512, 2632, 560, 8264, 8210, 2632,  560,    0}, //LOAD_A
      {8512, 2632, 560,  524, 1026,  656,    0,    0}, //SWAP
      {8512, 2632, 560, 1548,  656,    0,    0,    0}, //ADD
      {8512, 2632, 560, 3593,  656,    0,    0,    0}, //SUB
      {8512, 2632, 560, 5124,    0,    0,    0,    0}, //SAVE
      {8512, 2632, 560, 8264, 5136, 2632,  560,    0}, //SAVE_A
      {8512, 2632, 560,  524,  578,  560,    0,    0}, //JUMP
      {8512, 2632, 560, 8264,  560,    0,    0,    0}, //JUMP_A
      {8512, 2632, 560, 2632,  560,    0,    0,    0}, //JUMP_Z
      {8512, 2632, 560, 8264,  560,    0,    0,    0}, //JUMP_P
      {8512, 2632, 560, 2632,  560,    0,    0,    0}, //JUMP_N
      {8512, 2632, 560,    0,    0,    0,    0,    0}  //HALT
    },
    {//     Clock Count / Accumulator Register (-)
     //   0     1    2     3     4     5     6     7
      {8512, 2632, 560, 8258, 2632,  560,    0,    0}, //LOAD_I
      {8512, 2632, 560, 8204,  530,    0,    0,    0}, //LOAD
      {8512, 2632, 560, 8264, 8210, 2632,  560,    0}, //LOAD_A
      {8512, 2632, 560,  524, 1026,  656,    0,    0}, //SWAP
      {8512, 2632, 560, 1548,  656,    0,    0,    0}, //ADD
      {8512, 2632, 560, 3593,  656,    0,    0,    0}, //SUB
      {8512, 2632, 560, 5124,    0,    0,    0,    0}, //SAVE
      {8512, 2632, 560, 8264, 5136, 2632,  560,    0}, //SAVE_A
      {8512, 2632, 560,  524,  578,  560,    0,    0}, //JUMP
      {8512, 2632, 560, 8264,  560,    0,    0,    0}, //JUMP_A
      {8512, 2632, 560, 2632,  560,    0,    0,    0}, //JUMP_Z
      {8512, 2632, 560, 2632,  560,    0,    0,    0}, //JUMP_P
      {8512, 2632, 560, 8264,  560,    0,    0,    0}, //JUMP_N
      {8512, 2632, 560,    0,    0,    0,    0,    0}  //HALT
    }
  };
  int opcode = sim->instruction_register;
  if(opcode > HALT)
    return 0;
  int clock = sim->clock_count % 8;
  int sign = sim->sign_unit_lines;
  sim->control_unit_lines = CONTROL_UNIT_STATE[sign][opcode][clock];
  /******* Simulate Register Reads *******/
  sim->address_bus = 0;
  if(sim->control_unit_lines & LINE_READ_PROGRAM_COUNTER_REGISTER)
    sim->address_bus |= sim->program_counter_register;
  if(sim->control_unit_lines & LINE_READ_TEMPORARY_REGISTER)
    sim->address_bus |= sim->temporary_register;
  if(sim->control_unit_lines & LINE_READ_OPERAND_REGISTER)
    sim->address_bus |= sim->operand_register;
  if(sim->control_unit_lines & LINE_READ_OPERAND_REGISTER_NOT)
    sim->address_bus |= ~(sim->operand_register);
  /******* Simulate Adder Unit *******/
  sim->data_bus = 0;
  if(sim->control_unit_lines & LINE_INPUT_LEFT)
    sim->data_bus += sim->accumulator_register;
  if(sim->control_unit_lines & LINE_INPUT_RIGHT)
    sim->data_bus += sim->address_bus;
  if(sim->control_unit_lines & LINE_CARRY_IN)
    sim->data_bus += 1;
  /******* Simulate Memory Unit *******/
  if(sim->control_unit_lines & LINE_READ_DATA_BUS) {
    if(sim->address_bus < ADDRESS_INPUT_REGISTER)
      sim->data_bus |= sim->memory_unit[sim->address_bus];
    if(sim->address_bus == ADDRESS_INPUT_REGISTER)
      sim->data_bus |= sim->input_register;
    if(sim->address_bus == ADDRESS_OUTPUT_REGISTER)
      sim->data_bus |= sim->output_register;
    if(sim->address_bus > ADDRESS_OUTPUT_REGISTER)
      return 0;
  }
  if(sim->control_unit_lines & LINE_WRITE_DATA_BUS) {
    if(sim->address_bus < ADDRESS_INPUT_REGISTER)
      sim->memory_unit[sim->address_bus] = sim->data_bus;
    if(sim->address_bus == ADDRESS_INPUT_REGISTER)
      sim->input_register = sim->data_bus;
    if(sim->address_bus == ADDRESS_OUTPUT_REGISTER)
      sim->output_register = sim->data_bus;
    if(sim->address_bus > ADDRESS_OUTPUT_REGISTER)
      return 0;
  }
  /******* Simulate Register Writes *******/
  if(sim->control_unit_lines & LINE_WRITE_INSTRUCTION_REGISTER) {
    sim->instruction_register = sim->data_bus;
  }
  if(sim->control_unit_lines & LINE_WRITE_ACCUMULATOR_REGISTER) {
    sim->accumulator_register = sim->data_bus;
    sim->sign_unit_lines = 0;
    if(sim->accumulator_register & POSITIVE_BITS)
      sim->sign_unit_lines = LINE_POSITIVE;
    if(sim->accumulator_register & NEGATIVE_BITS)
      sim->sign_unit_lines = LINE_NEGATIVE;
  }
  if(sim->control_unit_lines & LINE_WRITE_PROGRAM_COUNTER_REGISTER)
    sim->program_counter_register = sim->data_bus;
  if(sim->control_unit_lines & LINE_WRITE_TEMPORARY_REGISTER)
    sim->temporary_register = sim->data_bus;
  if(sim->control_unit_lines & LINE_WRITE_OPERAND_REGISTER)
    sim->operand_register = sim->data_bus;
  return 1;
}

static int peripherals_clock_cycle(struct simulation *sim) {
  /******* Simulate Input Unit *******/
  if(sim->input_register == EMPTY)
    sim->input_register = getc(stdin);
  /******* Simulate Register Writes *******/
  if(sim->output_register != EMPTY) {
    putc(sim->output_register, stdout);
    fflush(stdout);
    sim->output_register = EMPTY;
  }
  return 1;
}








int simulation_clock_cycle(struct simulation *sim) {
  if(!system_clock_cycle(sim))
    return 0;
  if(!peripherals_clock_cycle(sim))
    return 0;
  if(sim->instruction_register == HALT && (sim->clock_count % 8))
    return 0;
  sim->clock_count++;
  return 1;
}

struct simulation* simulation_new(const char *filepath) {
  struct simulation *sim = malloc(sizeof(struct simulation));
  /******* Init Clock *******/
  sim->clock_count = 0;
  /******* Init Buses and Lines *******/
  sim->sign_unit_lines = 0;
  sim->control_unit_lines = 0;
  sim->data_bus = 0;
  sim->address_bus = 0;
  /******* Init Registers *******/
  sim->instruction_register = 0;
  sim->accumulator_register = 0;
  sim->program_counter_register = 0;
  sim->temporary_register = 0;
  sim->operand_register = 0;
  /******* Init Memory *******/
  sim->input_register = END_OF_INPUT;
  sim->output_register = EMPTY;
  struct binary *bin = binary_read(filepath);
  if(!bin)
    return 0;
  for(int address = 0; address < bin->size; address++)
    sim->memory_unit[address] = bin->data[address];
  binary_free(bin);
  return sim;
}

void simulation_delete(struct simulation *sim) {
  free(sim);
}
