#include"binary.h"








int binary_write(const char *filepath, const struct binary *bin) {
  FILE *file = fopen(filepath, "wb");
  if(!file)
    return 0;
  fwrite(&(bin->size), sizeof(int), 1, file);
  fwrite(bin->data, sizeof(int), bin->size, file);
  fclose(file);
  return 1;
}

struct binary* binary_new(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if(!file)
    return 0;
  int size = 0;
  fread(&size, sizeof(int), 1, file);
  int *data = malloc(sizeof(int) * size);
  fread(data, sizeof(int), size, file);
  fclose(file);
  struct binary *bin = malloc(sizeof(struct binary));
  bin->size = size;
  bin->data = data;
  return bin;
}

void binary_delete(struct binary *bin) {
  free(bin->data);
  free(bin);
}








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

#define _W 19 //final val 3
#define _X 20 //final val 6
#define _Y 21 //final val -3
#define _H 130
int test_machine_code[131] = {
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


int binary_recreate_examples() {
  struct binary bin;
  bin.size = 63;
  bin.data = hello_world_machine_code;
  if(!binary_write("machine_code/hello_world.BIN", &bin))
    return 0;
  bin.size = 35;
  bin.data = echo_machine_code;
  if(!binary_write("machine_code/echo.BIN", &bin))
    return 0;
  bin.size = 131;
  bin.data = test_machine_code;
  if(!binary_write("machine_code/test.BIN", &bin))
    return 0;
  return 1;
}
