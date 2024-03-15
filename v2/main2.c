#include <stdio.h>


#define DATA_SIZE 16
#define ADDRESS_SIZE 13
#define ADDRESS_SPACE 8192


struct Simulation {
  char ac[DATA_SIZE];
  char ip[DATA_SIZE];
  char ir[DATA_SIZE];
  char memory[ADDRESS_SPACE][DATA_SIZE];
};


void Datapath(char *des, char *src0, char *src1, char not1, char cin) {
  for(int i = 0; i < DATA_SIZE; i++) {
    int val = cin != 0;
    val += (src0 ? src0[i] != 0 : 0);
    val += (src1 ? src1[i] != 0 : 0) + (not1 != 0) == 1;
    cin = val > 1;
    des[i] = val % 2 != 0;
  }
}


char NonZero(char *src) {
  char res = 0;
  for(int i = 0; i < DATA_SIZE; i++) {
    res = res + (src[i] != 0) != 0;
  }
}


char* Memory(struct Simulation *s, char *src) {
  int idx = 0;
  for(int i = 0, v = 1; i < ADDRESS_SIZE; i++, v += v) {
    idx += (src[i] != 0) * v;
  }
  return &s->memory[idx][0];
}


void ProcessorUnit(struct Simulation *s) {
  Datapath(s->ir, 0, Memory(s, s->ip), 0, 0);
  Datapath(s->ip, s->ip, 0, 0, 1);
  char sb = s->ac[DATA_SIZE-1];
  char nz = NonZero(s->ac);
  char op = (s->ir[DATA_SIZE-1] != 0) * 4 +
            (s->ir[DATA_SIZE-2] != 0) * 2 +
            (s->ir[DATA_SIZE-3] != 0) * 1;
  if(op == 0) {
    Datapath(s->ac, 0, Memory(s, s->ir), 0, 0);
  } else if(op == 1) {
    Datapath(s->ac, s->ac, Memory(s, s->ir), 0, 0);
  } else if(op == 2) {
    Datapath(s->ac, s->ac, Memory(s, s->ir), 1, 1);
  } else if(op == 3) {
    Datapath(Memory(s, s->ir), s->ac, 0, 0, 0);
  } else if(op == 4 && sb) {
    Datapath(s->ip, s->ir, 0, 0, 0);
  } else if(op == 5 && !sb && nz) {
    Datapath(s->ip, s->ir, 0, 0, 0);
  } else if(op == 6 && !nz) {
    Datapath(s->ip, s->ir, 0, 0, 0);
  } else if(op == 7) {
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
    printf(" %d,", q[i]);
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
  SetArray(0x0002, s.ip);

  SetArray(0x0000, s.memory[0]); //VAL 0
  SetArray(0x0003, s.memory[1]); //VAL 3

  SetArray(0x0000, s.memory[2]); //LOAD [1]
  SetArray(0x4001, s.memory[3]); //SUB  [1]
  SetArray(0x6000, s.memory[4]); //SAVE [1]
  SetArray(0x8005, s.memory[5]); //HALT NEG
  SetArray(0xA006, s.memory[6]); //HALT POS
  SetArray(0xC007, s.memory[7]); //HALT ZER
  SetArray(0xE008, s.memory[8]); //HALT ANY

  PrintProcessor(&s);
  ProcessorUnit(&s);
  PrintProcessor(&s);
  ProcessorUnit(&s);
  PrintProcessor(&s);
  PrintArray(s.memory[0]);
  ProcessorUnit(&s);
  PrintProcessor(&s);
  PrintArray(s.memory[0]);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
  ProcessorUnit(&s);
/*
  PrintArray(s.memory[0]);
  PrintArray(s.memory[1]);
  PrintArray(s.memory[2]);
  PrintArray(s.memory[3]);
  PrintArray(s.memory[4]);
  PrintArray(s.memory[5]);
  PrintArray(s.memory[6]);
  PrintArray(s.memory[7]);
  PrintArray(s.memory[8]);
*/
}

