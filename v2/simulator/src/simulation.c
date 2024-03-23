#include <stdio.h>

#define DATA_SIZE 16
#define ADDRESS_SPACE 8192

#define END_OF_INPUT '\n'
#define EMPTY 0
#define INPUT_ADDRESS 8190
#define OUTPUT_ADDRESS 8191

struct Simulation {
  char ac[DATA_SIZE];
  char ip[DATA_SIZE];
  char ir[DATA_SIZE];
  char memory[ADDRESS_SPACE][DATA_SIZE];
  char iu[DATA_SIZE];
  char ou[DATA_SIZE];
};


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
  for(int i = 0, v = 1; i < DATA_SIZE-3; i++, v += v) {
    if(src[i]) {
      idx += v;
    }
  }
  if(idx == INPUT_ADDRESS) {
	return &s->pi[0]
  }
  if(idx == OUTPUT_ADDRESS) {
	return &s->po[0]
  }
  return &s->memory[idx][0];
}


void ProcessorUnit(struct Simulation *s) {
  // Fetch.
  Datapath(s->ir, 0, Memory(s, s->ip), 0, 0);
  Datapath(s->ip, s->ip, 0, 0, 1);
  // Decode.
  int op = 0;
  if(s->ir[DATA_SIZE-1]) {
    op += 4;
  }
  if(s->ir[DATA_SIZE-2]) {
    op += 2;
  }
  if(s->ir[DATA_SIZE-3]) {
    op += 1;
  }
  int sb = 0;
  if(s->ac[DATA_SIZE-1]) {
    sb += 1;
  }
  // Execute.
  if(op == 0) {
    // Load Positive: ac <- +memory[address]
    Datapath(s->ac, 0, Memory(s, s->ir), 0, 0);
  } else if(op == 1) {
    // Load Negative: ac <- -memory[address]
    Datapath(s->ac, 0, Memory(s, s->ir), 1, 1);
  } else if(op == 2) {
    // Load Add: ac <- ac + memory[address]
    Datapath(s->ac, s->ac, Memory(s, s->ir), 0, 0);
  }  else if(op == 3) {
    // Load Subtract: ac <- ac - memory[address]
    Datapath(s->ac, s->ac, Memory(s, s->ir), 1, 1);
  } else if(op == 4) {
    // Save: memory[address] <- ac
    Datapath(Memory(s, s->ir), s->ac, 0, 0, 0);
  } else if(op == 5 && sb) {
    // Jump Negative: if(ac < 0) IP <- address
    Datapath(s->ip, s->ir, 0, 0, 0);
  } else if(op == 6) {
    // Jump Any: IP <- address
    Datapath(s->ip, s->ir, 0, 0, 0);
  } else if(op == 7) {
    // Halt: IP <- IP - 1
    Datapath(s->ip, s->ip, 0, 1, 0);
  }
}


void InputUnit() {
  // Get register.
  char val = 0
  for(int i = 0, v = 1; i < DATA_SIZE && i < sizeof(char); i++; v += v) {
    if(s->pi[i]) {
	val += v;
    }
  }
  // No character, get next character.
  if(!val) {
    val = getc(stdin);
  }
  // Set register.
  for(int i = 0; i < DATA_SIZE && i < sizeof(char); i++) {
    if(val >> i & 0x1) {
	s->pi[i]++;
    }
  }
}


void OutputUnit() {

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


void PrintProcessor(struct Simulation *s) {
  printf("Processor State:\n");
  printf("AC:\n");
  PrintArray(s->ac);
  printf("IP:\n");
  PrintArray(s->ip);
  printf("IR:\n");
  PrintArray(s->ir);
  printf("\n");
}


void main() {
  // LP 0x0000
  // LN 0x2000
  // LA 0x4000
  // LS 0x6000
  // S  0x8000
  // JN 0xA000
  // JA 0xC000
  // H  0xE000
  struct Simulation s;
  SetArray(0x0010, s.memory[0]);
  SetArray(0x4009, s.memory[1]);
  SetArray(0x8004, s.memory[2]);
  SetArray(0x000B, s.memory[3]);
  SetArray(0x0000, s.memory[4]); //save
  SetArray(0x0010, s.memory[5]);
  SetArray(0x600A, s.memory[6]);
  SetArray(0x8010, s.memory[7]);
  SetArray(0xE000, s.memory[8]);
  SetArray(0x8000, s.memory[9]); //opST
  SetArray(0x0001, s.memory[10]);//val1
  SetArray(0x002A, s.memory[11]);//varX
  SetArray(0x0000, s.memory[12]);
  SetArray(0x0000, s.memory[13]);
  SetArray(0x0000, s.memory[14]);//topS
  SetArray(0x0015, s.memory[15]);
  SetArray(0x000E, s.memory[16]);//ptrS
  SetArray(0x0000, s.memory[17]);

  for(int i = 0; i < 32; i++) {
    ProcessorUnit(&s);
  }

  PrintProcessor(&s);

  PrintArray(s.memory[0]);
  PrintArray(s.memory[1]);
  PrintArray(s.memory[2]);
  PrintArray(s.memory[3]);
  PrintArray(s.memory[4]);
  PrintArray(s.memory[5]);
  PrintArray(s.memory[6]);
  PrintArray(s.memory[7]);
  PrintArray(s.memory[8]);
  PrintArray(s.memory[9]);
  PrintArray(s.memory[10]);
  PrintArray(s.memory[11]);
  PrintArray(s.memory[12]);
  PrintArray(s.memory[13]);
  PrintArray(s.memory[14]);
  PrintArray(s.memory[15]);
  PrintArray(s.memory[16]);
  PrintArray(s.memory[17]);
}
