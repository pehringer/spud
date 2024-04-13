#include "backend.h"
#include "frontend.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include<unistd.h>


void main(int argc, char **argv) {
  struct winsize terminal;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminal);
  int lines = terminal.ws_row;
  int columns = terminal.ws_col;
  if(lines < MINIMUM_LINES || columns < MINIMUM_COLUMNS) {
    printf("Terminal window of (%dX%d) is too small.\n", lines, columns);
    printf("Minimum window size (%dX%d).\n", MINIMUM_LINES, MINIMUM_COLUMNS);
    exit(1);
  }
  const char *filepath = "sim_bin/echo.bin";
  struct timespec cycleTime = {0, 999999999};
  long cycleCount = 32;
  for(int argi = 1; argi < argc; argi++) {
    if(!strcmp(argv[argi], "-filepath")) {
      filepath = argv[++argi];
    } else if(!strcmp(argv[argi], "-cycle_time")) {
      cycleTime.tv_nsec = strtol(argv[++argi], NULL, 10) * 1000000;
    } else if(!strcmp(argv[argi], "-cycle_count")) {
      cycleCount = strtol(argv[++argi], NULL, 10);
    } else {
      printf("Invalid Option: %s\n", argv[argi]);
      printf("----------------------------\n");
      printf("-filepath [PATH_TO_BINARY]\n");
      printf("-cycle_time [NUMBER_MILLISECONDS]\n");
      printf("-cycle_count [NUMBER_OF_CYCLES]\n");
      exit(-1);
    }
  }
  FILE *file = fopen(filepath, "r");
  if(!file) {
    printf("Unable to load BIN file.\n");
    exit(2);
  }


  struct Simulation s;
  InitializeSimulation(&s, file);
  fclose(file);
  InitializeTerminal(lines);
  while(cycleCount > 0) {
    CycleSimulation(&s);
    DrawTerminal(&s);
    nanosleep(&cycleTime, 0);
    cycleCount--;
  }
}
