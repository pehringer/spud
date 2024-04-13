#include "frontend.h"


void DrawBits(char *bits, int count) {
  while(count--) {
    printf("%d", bits[count]);
    if(count % 4 == 0) {
      printf(" ");
    }
  }
}


void DrawRegisters(struct Simulation *s) {
  printf("    \nAccumulator:         \n");
  DrawBits(s->ac, DATA_SIZE);
  printf("    \nInstruction Pointer: \n");
  DrawBits(s->ip, DATA_SIZE-3);
  printf("    \nInstruction Register:\n");
  DrawBits(s->ir, DATA_SIZE);
}


void DrawMemory(struct Simulation *s) {
  printf("\n                        \n");
  long ip = 0;
  for(int i = 0; i < DATA_SIZE-3; i++) {
    if(s->ip[i]) {
      ip |= 1 << i;
    }
  }
  for(long line = ip - 8; line < ip + 9; line++) {
    if(line < 0) {
      printf("                        \n");
      continue;
    }
    DrawBits(s->memory[line], DATA_SIZE);
    if(line == ip)
      printf(" <-\n");
    else
      printf("   \n");
  }
  printf("                        \n");
}


void DrawTerminal(struct Simulation *s) {
  printf("\033[s\033[H\033[2K");
  DrawRegisters(s);
  DrawMemory(s);
  printf("\033[u");
}


void InitializeTerminal(int lines) {
  for(int line = 0; line < lines; line++) {
    printf("\n");
  }
}
