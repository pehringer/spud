#include"simulation.h"
#include<sys/ioctl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>







#define MINIMUM_LINES 40
#define MINIMUM_COLUMNS 40








void draw_state(struct simulation *sim) {
  printf("                                    \n");
  printf("State_______________________________\n");
  printf("                                    \n");
  printf("%11d Data Bus                \n", sim->data_bus);
  printf("%11d Address Bus             \n", sim->address_bus);
  printf("%11d Instruction Register    \n", sim->instruction_register);
  printf("%11d Accumulator Register    \n", sim->accumulator_register);
  printf("%11d Program Counter Register\n", sim->program_counter_register);
  printf("%11d Temporary Register      \n", sim->temporary_register);
  printf("%11d Operand Register        \n", sim->operand_register);
}

void draw_program(struct simulation *sim) {
  printf("                                    \n");
  printf("Program_____________________________\n");
  printf("                                    \n");
  long pc = sim->program_counter_register;
  for(long line = pc - 8; line < pc + 9; line++) {
    if(line < 0) {
      printf("        |                            \n");
      continue;
    }
    printf("%7ld | %d", line, sim->memory_unit[line]);
    if(line == pc)
      printf(" <<<<<<<<        \n");
    else
      printf("                 \n");
  }
}

void draw_output() {
  printf("                                    \n");
  printf("Output______________________________\n");
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

void main() {
  initialize_terminal();
  struct simulation *sim = simulation_new("machine_code/test.BIN");
  if(!sim) {
    printf("Unable to load BIN file.\n");
    exit(2);
  }
  while(simulation_clock_cycle(sim)) {
    redraw_terminal(sim);
    usleep(15000);
  }
  simulation_delete(sim);
}
