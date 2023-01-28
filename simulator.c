#include"simulator.h"




/*******************
Computer Peripherals
*******************/

//Peripheral register inits.
static uint16_t input_register = END_OF_INPUT;
static uint16_t output_register = EMPTY;

static void simulate_input() {
  if(input_register == EMPTY) {
    input_register = getc(stdin);
  }
}

static void simulate_output() {
  if(output_register != EMPTY) {
    putc(output_register, stdout);
    fflush(stdout);
    output_register = EMPTY;
  }
}




/**************
Computer Memory
**************/

//Memory unit init.
static uint16_t memory[FIRST_PERIPHERAL];

static uint16_t memory_read(uint16_t address) {
  if(address < FIRST_PERIPHERAL) {
    return memory[address];
  }
  else if(address == TERMINAL_INPUT) {
    return input_register;
  }
  else if(address == TERMINAL_OUTPUT) {
    return output_register;
  }
  else {
    return 0;
  }
}

static void memory_write(uint16_t address, uint16_t value) {
  if(address < FIRST_PERIPHERAL) {
    memory[address] = value;
  }
  else if(address == TERMINAL_INPUT) {
    input_register = value;
  }
  else if(address == TERMINAL_OUTPUT) {
    output_register = value;
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




/*****************
Computer Processor
*****************/

//Processor register inits
static uint16_t accumulator_register = EMPTY;
static uint16_t instruction_register = EMPTY;
static uint16_t operand_register = EMPTY;
static uint16_t program_counter_register = 0;
static uint16_t temporary_register = EMPTY;

static int simulate_processor() {
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
      return 1;
    default:
      printf("Invalid Opcode %d At Address %d\n", instruction_register, program_counter_register - 1);
      return -1;
  }
  return 0;
}




/***************
Computer Runtime
***************/

//Simulation parameter inits.
static const char *program_filepath = "binary_examples/hello_world.BIN";
static int cycle_milliseconds = 0;
static int debug_output = 0;

static void simulate_runtime(const char *program_filepath) {
  struct machine_code program = load_binary_file(program_filepath);
  load_memory(program);
  free_machine_code(program);
  struct timespec now;
  unsigned long now_milliseconds;
  unsigned long last_cycle = 0;
  while(1) {
    clock_gettime(CLOCK_REALTIME, &now);
    now_milliseconds = (now.tv_sec * 1000) + (now.tv_nsec / 1000000);
    if(now_milliseconds - last_cycle < cycle_milliseconds) {
      continue;
    }
    last_cycle = now_milliseconds;
    simulate_input();
    if(debug_output && output_register != EMPTY) {
      printf("\n                                         |  ");
      fflush(stdout);
    }
    simulate_output();
    int stopped = simulate_processor();
    if(debug_output) {
      printf("\nPC: %5d IR: %5d AC: %5d OP: %5d  |  ", program_counter_register, instruction_register,
        accumulator_register, operand_register);
      fflush(stdout);
    }
    if(stopped) {
      if(debug_output) {
        printf("\n\n");
      }
      exit(0);
    }
  }
}

void main(int argc, char **argv) {
  recreate_example_binary_files();
  if(argc > 1) {
    for(int arg_number = 1; arg_number < argc; arg_number++) {
      if(!strcmp(argv[arg_number], "-program")) {
        program_filepath = argv[++arg_number];
      }
      else if(!strcmp(argv[arg_number], "-cycle")) {
        cycle_milliseconds = strtol(argv[++arg_number], NULL, 10);
      }
      else if(!strcmp(argv[arg_number], "-debug")) {
        debug_output = 1;
      }
      else {
        printf("Invalid Option: %s\n", argv[arg_number]);
        printf("----------------------------\n");
        printf("-program [FILEPATH]\n");
        printf("-cycle [NUMBER_MILLISECONDS]\n");
        printf("-debug\n");
        exit(-1);
      }
    }
  }
  simulate_runtime(program_filepath);
  exit(0);
}
