#include <stdio.h>


#define DATA_SIZE 16
#define ADDRESS_SPACE 8192


struct Simulation {
  char ac[DATA_SIZE];
  char ip[DATA_SIZE];
  char ir[DATA_SIZE];
  char memory[ADDRESS_SPACE][DATA_SIZE];
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
    // LOAD: ac <- memory[address]
    Datapath(s->ac, 0, Memory(s, s->ir), 0, 0);
  } else if(op == 1) {
    // Add: ac <- ac + memory[address]
    Datapath(s->ac, s->ac, Memory(s, s->ir), 0, 0);
  } else if(op == 2) {
    // Negate: ac <- -memory[address]
    Datapath(s->ac, 0, Memory(s, s->ir), 1, 1);
  } else if(op == 3) {
    // Subtract: ac <- ac - memory[address]
    Datapath(s->ac, s->ac, Memory(s, s->ir), 1, 1);
  } else if(op == 4) {
    // Store: memory[address] <- ac
    Datapath(Memory(s, s->ir), s->ac, 0, 0, 0);
  } else if(op == 5 && sb) {
    // Jump Negative: if(ac < 0) IP <- address
    Datapath(s->ip, s->ir, 0, 0, 0);
  } else if(op == 6) {
    // Jump Any: IP <- address
    Datapath(s->ip, s->ir, 0, 0, 0);
  }
}


void SetArray(int d, char *q) {
   for(int i = 0; i < DATA_SIZE; i++) {
     q[i] = (d >> i) & 0x0001;
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
  struct Simulation s;
  SetArray(0x0008, s.ip);
  SetArray(0x0001, s.memory[0]);  // DATA val
  SetArray(0x0001, s.memory[1]);  // DATA 1
  SetArray(0x0004, s.memory[2]);  // DATA pow
  SetArray(0x4001, s.memory[3]);  // SU 1
  SetArray(0x6002, s.memory[4]);  // ST pow
  SetArray(0x0000, s.memory[5]);  // LO val
  SetArray(0x2000, s.memory[6]);  // AD val
  SetArray(0x6000, s.memory[7]);  // ST val
  SetArray(0x0002, s.memory[8]);  // LO pow
  SetArray(0xA003, s.memory[9]);  // JP pos
  SetArray(0xE00A, s.memory[10]); // JA hlt

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
}

/*
  SetArray(0x0002, s.ip);
  SetArray(0x0000, s.memory[0]); // DATA 0
  SetArray(0x0003, s.memory[1]); // DATA 3
  SetArray(0x0000, s.memory[2]); // LD 3
  SetArray(0x4001, s.memory[3]); // SU 3 MOD-TO-TEST
  SetArray(0x6000, s.memory[4]); // ST 3
  SetArray(0x8005, s.memory[5]); // JN hlt
  SetArray(0xA006, s.memory[6]); // JP hlt
  SetArray(0xC007, s.memory[7]); // JZ hlt
  SetArray(0xE008, s.memory[8]); // JA hlt
*/
