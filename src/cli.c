#include "sim.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


void main(int argc, char **argv) {
  const char *filepath = "examples/bin/hello_world.bin";
  struct timespec cycleTime = {0, 100000000};
  long cycleCount = 128;
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
  LoadSimulation(&s, file);
  fclose(file);
  while(cycleCount > 0) {
    SimulateCycle(&s);
    nanosleep(&cycleTime, 0);
    cycleCount--;
  }
}
