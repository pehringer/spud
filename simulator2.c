#include"simulator2.h"




//Control unit bitmasks.
#define LINE_READ_OPERAND_REGISTER_NOT 1
#define LINE_WRITE_OPERAND_REGISTER 2
#define LINE_READ_OPERAND_REGISTER 4
#define LINE_WRITE_TEMPORARY_REGISTER 8
#define LINE_READ_TEMPORARY_REGISTER 16
#define LINE_WRITE_PROGRAM_COUNTER_REGISTER 32
#define LINE_READ_PROGRAM_COUNTER_REGISTER 64
#define LINE_WRITE_ACCUMULATOR_REGISTER 128
#define LINE_WRITE_INSTRUCTION_REGISTER 256
#define LINE_INPUT_RIGHT 512
#define LINE_INPUT_LEFT 1024
#define LINE_CARRY_IN 2048
#define LINE_WRITE_MEMORY 4096
#define LINE_READ_MEMORY 8192

//Sign unit bitmasks.
#define LINE_POSITIVE 1
#define LINE_NEGATIVE 2
#define POSITIVE_BITS 2147483647
#define NEGATIVE_BITS 2147483648




static void simulate_system_clock_cycle(struct simulation_state *sim) {
  /******* Simulate Control Unit *******/
  //3 - sign unit lines.
  //14 - instruction register.
  //8 - clock pulse count.
  static const uint32_t CONTROL_UNIT_STATE[3][14][8] = {
    {
      {8512, 2632, 560, 8258, 2632,  560,    0,    0},
      {8512, 2632, 560, 8204,  530,    0,    0,    0},
      {8512, 2632, 560, 8264, 8210, 2632,  560,    0},
      {8512, 2632, 560,  524, 1026,  656,    0,    0},
      {8512, 2632, 560, 1548,  656,    0,    0,    0},
      {8512, 2632, 560, 3593,  656,    0,    0,    0},
      {8512, 2632, 560, 5124,    0,    0,    0,    0},
      {8512, 2632, 560, 8264, 5136, 2632,  560,    0},
      {8512, 2632, 560,  548,    0,    0,    0,    0},
      {8512, 2632, 560, 8264,  560,    0,    0,    0},
      {8512, 2632, 560, 8264,  560,    0,    0,    0},
      {8512, 2632, 560, 2632,  560,    0,    0,    0},
      {8512, 2632, 560, 2632,  560,    0,    0,    0},
      {8512, 2632, 560,    0,    0,    0,    0,    0}
    },
    {
      {8512, 2632, 560, 8258, 2632,  560,    0,    0},
      {8512, 2632, 560, 8204,  530,    0,    0,    0},
      {8512, 2632, 560, 8264, 8210, 2632,  560,    0},
      {8512, 2632, 560,  524, 1026,  656,    0,    0},
      {8512, 2632, 560, 1548,  656,    0,    0,    0},
      {8512, 2632, 560, 3593,  656,    0,    0,    0},
      {8512, 2632, 560, 5124,    0,    0,    0,    0},
      {8512, 2632, 560, 8264, 5136, 2632,  560,    0},
      {8512, 2632, 560,  548,    0,    0,    0,    0},
      {8512, 2632, 560, 8264,  560,    0,    0,    0},
      {8512, 2632, 560, 2632,  560,    0,    0,    0},
      {8512, 2632, 560, 2632,  560,    0,    0,    0},
      {8512, 2632, 560, 8264,  560,    0,    0,    0},
      {8512, 2632, 560,    0,    0,    0,    0,    0}
    },
    {
      {8512, 2632, 560, 8258, 2632,  560,    0,    0},
      {8512, 2632, 560, 8204,  530,    0,    0,    0},
      {8512, 2632, 560, 8264, 8210, 2632,  560,    0},
      {8512, 2632, 560,  524, 1026,  656,    0,    0},
      {8512, 2632, 560, 1548,  656,    0,    0,    0},
      {8512, 2632, 560, 3593,  656,    0,    0,    0},
      {8512, 2632, 560, 5124,    0,    0,    0,    0},
      {8512, 2632, 560, 8264, 5136, 2632,  560,    0},
      {8512, 2632, 560,  548,    0,    0,    0,    0},
      {8512, 2632, 560, 8264,  560,    0,    0,    0},
      {8512, 2632, 560, 2632,  560,    0,    0,    0},
      {8512, 2632, 560, 8264,  560,    0,    0,    0},
      {8512, 2632, 560, 2632,  560,    0,    0,    0},
      {8512, 2632, 560,    0,    0,    0,    0,    0}
    }
  };
  int opcode = sim->instruction_register;
  int clock = sim->clock_count % 8; //8 clock pulses (fetch/decode/execute).
  int sign = sim->sign_unit_lines;
  sim->control_unit_lines = CONTROL_UNIT_STATE[sign][opcode][clock];
  /******* Simulate Register Reads *******/
  sim->address_bus = 0;
  if(sim->control_unit_lines & LINE_READ_PROGRAM_COUNTER_REGISTER) {
    sim->address_bus |= sim->program_counter_register;
  }
  if(sim->control_unit_lines & LINE_READ_TEMPORARY_REGISTER) {
    sim->address_bus |= sim->temporary_register;
  }
  if(sim->control_unit_lines & LINE_READ_OPERAND_REGISTER) {
    sim->address_bus |= sim->operand_register;
  }
  if(sim->control_unit_lines & LINE_READ_OPERAND_REGISTER_NOT) {
    sim->address_bus |= ~(sim->operand_register);
  }
  /******* Simulate Adder Unit *******/
  sim->data_bus = 0;
  if(sim->control_unit_lines & LINE_INPUT_LEFT) {
    sim->data_bus += sim->accumulator_register;
  }
  if(sim->control_unit_lines & LINE_INPUT_RIGHT) {
    sim->data_bus += sim->address_bus;
  }
  if(sim->control_unit_lines & LINE_CARRY_IN) {
    sim->data_bus += 1;
  }
  /******* Simulate Memory Unit *******/
  if(sim->control_unit_lines & LINE_READ_MEMORY) {
    if(sim->address_bus < ADDRESS_INPUT_REGISTER) {
      sim->data_bus |= sim->memory[sim->address_bus];
    }
    if(sim->address_bus == ADDRESS_INPUT_REGISTER) {
      sim->data_bus |= sim->input_register;
    }
    if(sim->address_bus == ADDRESS_OUTPUT_REGISTER) {
      sim->data_bus |= sim->output_register;
    }
  }
  if(sim->control_unit_lines & LINE_WRITE_MEMORY) {
    if(sim->address_bus < ADDRESS_INPUT_REGISTER) {
      sim->memory[sim->address_bus] = sim->data_bus;
    }
    if(sim->address_bus == ADDRESS_INPUT_REGISTER) {
      sim->input_register = sim->data_bus;
    }
    if(sim->address_bus == ADDRESS_OUTPUT_REGISTER) {
      sim->output_register = sim->data_bus;
    }
  }
  /******* Simulate Register Writes *******/
  if(sim->control_unit_lines & LINE_WRITE_INSTRUCTION_REGISTER) {
    sim->instruction_register = sim->data_bus;
  }
  if(sim->control_unit_lines & LINE_WRITE_ACCUMULATOR_REGISTER) {
    sim->accumulator_register = sim->data_bus;
    sim->sign_unit_lines = 0;
    if(sim->accumulator_register & NEGATIVE_BITS) {
      sim->sign_unit_lines = LINE_NEGATIVE;
    }
    else if(sim->accumulator_register & POSITIVE_BITS) {
      sim->sign_unit_lines = LINE_POSITIVE;
    }
  }
  if(sim->control_unit_lines & LINE_WRITE_PROGRAM_COUNTER_REGISTER) {
    sim->program_counter_register = sim->data_bus;
  }
  if(sim->control_unit_lines & LINE_WRITE_TEMPORARY_REGISTER) {
    sim->temporary_register = sim->data_bus;
  }
  if(sim->control_unit_lines & LINE_WRITE_OPERAND_REGISTER) {
    sim->operand_register = sim->data_bus;
  }
}

static void simulate_peripherals_clock_cycle(struct simulation_state *sim) {
  /******* Simulate Input Unit *******/
  if(sim->input_register == EMPTY) {
    sim->input_register = getc(stdin);
  }
  /******* Simulate Register Writes *******/
  if(sim->output_register != EMPTY) {
    putc(sim->output_register, stdout);
    fflush(stdout);
    sim->output_register = EMPTY;
  }
}



/*
int hello_world_machine_code[63] = {
LOAD_I,
'H',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'e',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'l',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'o',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
' ',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'W',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'o',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'r',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'l',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'd',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'!',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'\n',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
HALT
};
*/

/*
int echo_machine_code[35] = {
LOAD_I,
'>',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
' ',
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
0,
SWAP,
SAVE_A,
ADDRESS_INPUT_REGISTER,
LOAD_A,
ADDRESS_INPUT_REGISTER,
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER,
LOAD_I,
'\n',
SUB,
JUMP_Z,
34,
LOAD_I,
0,
SWAP,
SAVE_A,
ADDRESS_INPUT_REGISTER,
JUMP_A,
17,
HALT
};
*/

#define _W 19 //final val 3
#define _X 20 //final val 6
#define _Y 21 //final val -3
#define _H 130
int test_all[131] = {
LOAD_I, //0
3,
SWAP,
LOAD_I,
_W,
SAVE,
LOAD,
ADD,
SAVE_A,
_X,
LOAD_A, //10
_W,
SWAP,
SUB,
SAVE_A,
_Y,
LOAD_I,
22,
JUMP,
0,
0,     //20
0,
LOAD_A,
_W,
SWAP,
LOAD_I,
48,
ADD,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print '3'.
LOAD_A, //30
_X,
SWAP,
LOAD_I,
48,
ADD,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print '6'.
LOAD_A,
_Y,
SWAP,   //40
LOAD_I,
51,
ADD,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print '0'.
LOAD_I,
0,
SWAP,
JUMP_Z,
55,     //50
JUMP_P,
_H,
JUMP_N,
_H,
LOAD_I,
95,
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print '_'.
LOAD_I, //60
0,
SWAP,
JUMP_P,
_H,
JUMP_N,
_H,
LOAD_I,
32,
SWAP,
SAVE_A, //70
ADDRESS_OUTPUT_REGISTER, //Should print ' '.
LOAD_I,
1,
SWAP,
JUMP_P,
81,
JUMP_Z,
_H,
JUMP_N,
_H,     //80
LOAD_I,
43,
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print '+'.
LOAD_I,
1,
SWAP,
JUMP_Z,
_H,     //90
JUMP_N,
_H,
LOAD_I,
32,
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print ' '.
LOAD_I,
-1,
SWAP,   //100
JUMP_N,
107,
JUMP_Z,
_H,
JUMP_P,
_H,
LOAD_I,
45,
SWAP,
SAVE_A, //110
ADDRESS_OUTPUT_REGISTER, //Should print '-'.
LOAD_I,
-1,
SWAP,
JUMP_Z,
_H,
JUMP_P,
_H,
LOAD_I,
32,    //120
SWAP,
SAVE_A,
ADDRESS_OUTPUT_REGISTER, //Should print ' '.
JUMP_A,
_H,
JUMP_A,
0,
0,
0,
HALT //130
};

struct simulation_state* new_simulation() {
  struct simulation_state *sim = malloc(sizeof(struct simulation_state));
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
  for(int i = 0; i < sizeof(test_all)/sizeof(test_all[0]); i++) {
    sim->memory[i] = test_all[i];
  }
  return sim;
}

void delete_simulation(struct simulation_state *sim) {
  free(sim);
}


int simulate_clock_cycle(struct simulation_state *sim) {
  if(sim->instruction_register == HALT) {
    return 0;
  }
  simulate_system_clock_cycle(sim);
  simulate_peripherals_clock_cycle(sim);
  sim->clock_count++;
  return 1;
}



//#include<unistd.h>
int main() {
  printf("Running\n");
  struct simulation_state *sim = new_simulation();
  while(simulate_clock_cycle(sim)) {
    //sleep(1);
  }
  delete_simulation(sim);
  printf("Halted\n");
  return 0;
}















