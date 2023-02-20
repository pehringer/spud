#include"simulation.h"
#include<sys/ioctl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>







#define MINIMUM_LINES 40
#define MINIMUM_COLUMNS 40








void draw_state(struct simulation *sim) {
  printf("                                    \n");
  printf("Processor___________________________\n");
  printf("                                    \n");
  printf("%11ld Data Bus                \n", sim->data_bus);
  printf("%11ld Address Bus             \n", sim->address_bus);
  printf("%11ld Instruction Register    \n", sim->instruction_register);
  printf("%11ld Accumulator Register    \n", sim->accumulator_register);
  printf("%11ld Program Counter Register\n", sim->program_counter_register);
  printf("%11ld Temporary Register      \n", sim->temporary_register);
  printf("%11ld Operand Register        \n", sim->operand_register);
}

void draw_program(struct simulation *sim) {
  printf("                                    \n");
  printf("Memory______________________________\n");
  printf("                                    \n");
  long pc = sim->program_counter_register;
  for(long line = pc - 8; line < pc + 9; line++) {
    if(line < 0) {
      printf("            |                       \n");
      continue;
    }
    printf("%11ld | %11ld", line, sim->memory_unit[line]);
    if(line == pc)
      printf(" <- PC\n");
    else
      printf("      \n");
  }
}

void draw_output() {
  printf("                                    \n");
  printf("Input/Output________________________\n");
  printf("                                    \n");
}

void redraw_terminal(struct simulation *sim) {
  //Save cursor postion and goto first line.
  printf("\033[s\033[H\033[2K");
  /******** Draw Elements ********/
  draw_state(sim);
  draw_program(sim);
  draw_output();
  //Restore cursor position.
  printf("\033[u");
}

void initialize_terminal() {
  /******** Get and Check Window Size ********/
  struct winsize terminal;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);
  int lines = terminal.ws_row;
  int columns = terminal.ws_col;
  if(lines < MINIMUM_LINES || columns < MINIMUM_COLUMNS) {
    printf("Terminal window of (%dX%d) is too small.\n", lines, columns);
    printf("Minimum window size (%dX%d).\n", MINIMUM_LINES, MINIMUM_COLUMNS);
    exit(1);
  }
  /******** Create Display Area ********/
  for(int line = 0; line < lines; line++)
    printf("\n");
}

void main(int argc, char **argv) {
  /******** Default Visualizer Settings ********/
  const char *program_filepath = "machine_code/hello_world.BIN";
  struct timespec cycle_time = {0, 25000000};
  long halt_line = -1;
  int use_ui = 0;
  /******** Command Line Options ********/
  if(argc > 1) {
    for(int arg_number = 1; arg_number < argc; arg_number++) {
      if(!strcmp(argv[arg_number], "-program"))
        program_filepath = argv[++arg_number];
      else if(!strcmp(argv[arg_number], "-cycle"))
        cycle_time.tv_nsec = (strtol(argv[++arg_number], NULL, 10)*1000000)/8;
      else if(!strcmp(argv[arg_number], "-halt"))
	halt_line = strtol(argv[++arg_number], NULL, 10);
      else if(!strcmp(argv[arg_number], "-ui"))
        use_ui = 1;
      else {
        printf("Invalid Option: %s\n", argv[arg_number]);
        printf("----------------------------\n");
        printf("-program [FILEPATH]\n");
        printf("-cycle [NUMBER_MILLISECONDS]\n");
        printf("-halt [PROGRAM_COUNTER_NUMBER]\n");
        exit(-1);
      }
    }
  }
  /******** Init Simulation ********/
  struct simulation *sim = simulation_new(program_filepath);
  if(!sim) {
    printf("Unable to load BIN file.\n");
    exit(2);
  }
  /******** Run and Visualize Simulation ********/
  if(use_ui)
    initialize_terminal();
  while(simulation_clock_cycle(sim)) {
    if(use_ui)
      redraw_terminal(sim);
    nanosleep(&cycle_time, 0);
    if((sim->program_counter_register) == halt_line)
      break;
  }
  simulation_delete(sim);
}
