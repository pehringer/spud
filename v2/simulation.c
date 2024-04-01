#include <stdio.h>

#define DATA_SIZE 16
#define ADDRESS_SPACE 8192 // 13 BIT
#define INPUT_ADDRESS 8190
#define OUTPUT_ADDRESS 8191


struct Simulation {
  char ac[DATA_SIZE];
  char ip[DATA_SIZE];
  char ir[DATA_SIZE];
  char memory[ADDRESS_SPACE][DATA_SIZE];
};


struct Simulation NewSimulation() {
  struct Simulation s;
  for(int i = 0; i < DATA_SIZE && i < 8; i++) {
    s.ac[i] = 0;
    s.ip[i] = 0;
    s.ir[i] = 0;
    s.memory[INPUT_ADDRESS][i] = 1 & '\n' >> i;
    s.memory[OUTPUT_ADDRESS][i] = 1 & '\0' >> i;
  }
}


void Datapath(char *des, char *src0, char *src1, char not1, char cin) {
  for(int i = 0; i < DATA_SIZE; i++) {
    char val = 0;
    if(src1 && src1[i]) {
      val++;
    }
    if(not1) {
      val++;
    }
    val %= 2;
    if(src0 && src0[i]) {
      val++;
    }
    if(cin) {
      val++;
    }
    cin = val > 1;
    des[i] = val % 2;
  }
}


char* Memory(struct Simulation *s, char *src) {
  int idx = 0;
  for(int i = 0; i < DATA_SIZE-3; i++) {
    if(src[i]) {
      idx |= 1 << i;
    }
  }
  return &s->memory[idx][0];
}


char Opcode(char *src) {
  char opc = 0;
  if(src[DATA_SIZE-1]) {
    opc |= 4;
  }
  if(src[DATA_SIZE-2]) {
    opc |= 2;
  }
  if(src[DATA_SIZE-3]) {
    opc |= 1;
  }
  return opc;
}


char Sign(char *src) {
  // Sign bit.
  if(src[DATA_SIZE-1]) {
    return -1;
  }
  // Non sign bits.
  for(int i = 0; i < DATA_SIZE-1; i++) {
    if(src[i]) {
      return 1;
    }
  }
  return 0;
}


void ProcessorUnit(struct Simulation *s) {
  // Fetch.
  Datapath(s->ir, 0, Memory(s, s->ip), 0, 0);
  Datapath(s->ip, s->ip, 0, 0, 1);
  // Decode.
  char opc = Opcode(s->ir);
  char sin = Sign(s->ac);
  // Execute.
  if(opc == 0) {
    // GET: ac = memory[address]
    Datapath(s->ac, 0, Memory(s, s->ir), 0, 0);
  }
  if(opc == 1) {
    // SET: memory[address] = ac
    Datapath(Memory(s, s->ir), s->ac, 0, 0, 0);
  }
  if(opc == 2) {
    // ADD: ac = ac + memory[address]
    Datapath(s->ac, s->ac, Memory(s, s->ir), 0, 0);
  }
  if(opc == 3) {
    // SUB: ac = ac - memory[address]
    Datapath(s->ac, s->ac, Memory(s, s->ir), 1, 1);
  }
  if(opc == 4) {
    // ANY: IP = address
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
  if(opc == 5 && sin < 0) {
    // NEG: if(ac < 0) IP = address
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
  if(opc == 6 && sin > 0) {
    // POS: if(ac > 0) IP = address
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
  if(opc == 7 && sin == 0) {
    // ZER: if(ac == 0) IP = address
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
}


void InputUnit(struct Simulation *s) {
  // Get register.
  char val = 0;
  for(int i = 0; i < DATA_SIZE && i < 8; i++) {
    if(s->memory[INPUT_ADDRESS][i]) {
	val |= 1 << i;
    }
  }
  // No character, read character.
  if(!val) {
    val = getc(stdin);
    // Set register.
    for(int i = 0; i < DATA_SIZE && i < 8; i++) {
      s->memory[INPUT_ADDRESS][i] = 1 & val >> i;
    }
  }
}


void OutputUnit(struct Simulation *s) {
  // Get register.
  char val = 0;
  for(int i = 0; i < DATA_SIZE && i < 8; i++) {
    if(s->memory[OUTPUT_ADDRESS][i]) {
      val |= 1 << i;
    }
  }
  // Has character, print character.
  if(val) {
    putc(val, stdout);
    fflush(stdout);
    // Clear character.
    for(int i = 0; i < DATA_SIZE && i < 8; i++) {
      s->memory[OUTPUT_ADDRESS][i] = 0;
    }
  }
}


void SimulateCycle(struct Simulation *s) {
  InputUnit(s);
  OutputUnit(s);
  ProcessorUnit(s);
}
















void SetArray(int d, char *q) {
   for(int i = 0; i < DATA_SIZE; i++) {
     q[i] = (d >> i) & 0x1;
   }
}


void PrintArray(char *q) {
  for(int i = DATA_SIZE - 1; i >= 0; i--) {
    printf("%d ", q[i]);
    if(i % 4 == 0) {
	printf("  ");
    }
  }
  printf("\n");
}


void main() {
  struct Simulation s;

  SetArray(0x1FFE, s.memory[0]);
  SetArray(0x3FFF, s.memory[1]);
  SetArray(0x0005, s.memory[2]);
  SetArray(0x3FFE, s.memory[3]);
  SetArray(0x8000, s.memory[4]);
  SetArray(0x0000, s.memory[5]);
  SetArray(0x0000, s.memory[6]);
  SetArray(0x0000, s.memory[7]);
  SetArray(0x0000, s.memory[8]);
  SetArray(0x0000, s.memory[9]);
  SetArray(0x0000, s.memory[10]);
  SetArray(0x0000, s.memory[11]);
  SetArray(0x0000, s.memory[12]);
  SetArray(0x0000, s.memory[13]);
  SetArray(0x0000, s.memory[14]);
  SetArray(0x0000, s.memory[15]);

  for(int i = 0; i < 32; i++) {
    SimulateCycle(&s);
  };
}
