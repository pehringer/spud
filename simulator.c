#include"simulator.h"




/**************
Computer Memory
**************/

//Processor register inits
static uint16_t accumulator_register = EMPTY;
static uint16_t instruction_register = EMPTY;
static uint16_t operand_register = EMPTY;
static uint16_t program_counter_register = 0;
static uint16_t temporary_register = EMPTY;

//Memory unit init.
static uint16_t memory[FIRST_PERIPHERAL];

//Memory mapped peripheral register inits.
static uint16_t character_input_register = END_OF_INPUT;
static uint16_t character_output_register = EMPTY;

static uint16_t memory_read(uint16_t address) {
  if(address < FIRST_PERIPHERAL) {
    return memory[address];
  }
  if(address == TERMINAL_INPUT) {
    return character_input_register;
  }
  if(address == TERMINAL_OUTPUT) {
    return character_output_register;
  }
  return 0;
}

static void memory_write(uint16_t address, uint16_t value) {
  if(address < FIRST_PERIPHERAL) {
    memory[address] = value;
  }
  if(address == TERMINAL_INPUT) {
    character_input_register = value;
  }
  if(address == TERMINAL_OUTPUT) {
    character_output_register = value;
  }
}

static void load_memory(struct machine_code program) {
  if(program.size > FIRST_PERIPHERAL) {
    printf("Insufficient Memory For Machine Code\n");
    exit(1);
  }
  for(int address = 0; address < program.size; address++) {
    memory[address] = program.data[address];
  }
}




/*******************
Computer Peripherals
*******************/

static void simulate_terminal_input() {
  if(character_input_register == EMPTY) {
    character_input_register = getc(stdin);
  }
}

static void simulate_terminal_output() {
  if(character_output_register != EMPTY) {
    putc(character_output_register, stdout);
    fflush(stdout);
    character_output_register = EMPTY;
  }
}




/*****************
Computer Processor
*****************/

static void simulate_processor() {
  //Fetch instruction.
  instruction_register = memory_read(program_counter_register);
  temporary_register = program_counter_register + 1;
  program_counter_register = temporary_register;
  //Decode instruction.
  switch(instruction_register) {
    //Execute instruction.
    case LOAD_I:
      operand_register = memory_read(program_counter_register);
      temporary_register = program_counter_register + 1;
      program_counter_register = temporary_register;
      break;
    case LOAD:
      temporary_register = memory_read(operand_register);
      operand_register = temporary_register;
      break;
    case LOAD_A:
      temporary_register = memory_read(program_counter_register);
      operand_register = memory_read(temporary_register);
      temporary_register = program_counter_register + 1;
      program_counter_register = temporary_register;
      break;
    case SWAP:
      temporary_register = operand_register;
      operand_register = accumulator_register;
      accumulator_register = temporary_register;
      break;
    case ADD:
      temporary_register = accumulator_register + operand_register;
      accumulator_register = temporary_register;
      break;
    case SUB:
      temporary_register = accumulator_register + (~operand_register) + 1;
      accumulator_register = temporary_register;
      break;
    case SAVE:
      memory_write(operand_register, accumulator_register);
      break;
    case SAVE_A:
      temporary_register = memory_read(program_counter_register);
      memory_write(temporary_register, accumulator_register);
      temporary_register = program_counter_register + 1;
      program_counter_register = temporary_register;
      break;
    case JUMP:
      program_counter_register = operand_register;
      break;
    case JUMP_A:
      temporary_register = memory_read(program_counter_register);
      program_counter_register = temporary_register;
      break;
    case JUMP_Z:
      if(((int16_t) accumulator_register) == 0) {
        temporary_register = memory_read(program_counter_register);
        program_counter_register = temporary_register;
      }
      else {
        temporary_register = program_counter_register + 1;
        program_counter_register = temporary_register;
      }
      break;
    case JUMP_N:
      if(((int16_t) accumulator_register) < 0) {
        temporary_register = memory_read(program_counter_register);
        program_counter_register = temporary_register;
      }
      else {
        temporary_register = program_counter_register + 1;
        program_counter_register = temporary_register;
      }
      break;
    case JUMP_P:
      if(((int16_t) accumulator_register) > 0) {
        temporary_register = memory_read(program_counter_register);
        program_counter_register = temporary_register;
      }
      else {
        temporary_register = program_counter_register + 1;
        program_counter_register = temporary_register;
      }
      break;
    case HALT:
      printf("Halting %d\n", operand_register);
      exit(0);
    default:
      printf("Unknown Opcode %d At Address %d\n", instruction_register, program_counter_register - 1);
      exit(1);
  }
}




/***************
Computer Runtime
***************/

static void simulate_runtime(const char *program_filepath) {
  struct machine_code program = load_binary_file(program_filepath);
  load_memory(program);
  free_machine_code(program);
  while(1) {
    simulate_terminal_input();
    simulate_terminal_output();
    simulate_processor();
  }
}

void main(int argc, char **argv) {
  const char *program_filepath;
  switch(argc) {
    case 1:
      recreate_example_binary_files();
      program_filepath = "binary_examples/hello_world.BIN";
      break;
    case 2:
      program_filepath = argv[1];
      break;
    default:
      printf("Too Many Arguments\n");
      exit(1);
  }
  simulate_runtime(program_filepath);
  exit(0);
}

