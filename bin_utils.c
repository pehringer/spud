#include"bin_utils.h"




/********************
Binary File Utilities
********************/

void create_binary_file(const char *filepath, const struct machine_code program) {
  FILE *file = fopen(filepath, "wb");
  fwrite(&program.size, sizeof(int), 1, file);
  fwrite(program.data, sizeof(int), program.size, file);
  fclose(file);
}

struct machine_code load_binary_file(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
  if(!file) {
    printf("Could not open: %s\n", filepath);
    exit(-1);
  }
  int size = 0;
  fread(&size, sizeof(int), 1, file);
  int *data = malloc(sizeof(int) * size);
  fread(data, sizeof(int), size, file);
  fclose(file);
  struct machine_code program = {size, data};
  return program;
}

void free_machine_code(struct machine_code program) {
  free(program.data);
}




/****************************
Example Machine Code Programs
****************************/

int hello_world_machine_code[63] = {
LOAD_I,
'H',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'e',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'l',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'o',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
' ',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'W',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'o',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'r',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'l',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'd',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'!',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'\n',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
HALT
};

int echo_machine_code[35] = {
LOAD_I,
'>',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
' ',
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
0,
SWAP,
SAVE_A,
TERMINAL_INPUT,
LOAD_A,
TERMINAL_INPUT,
SWAP,
SAVE_A,
TERMINAL_OUTPUT,
LOAD_I,
'\n',
SUB,
JUMP_Z,
34,
LOAD_I,
0,
SWAP,
SAVE_A,
TERMINAL_INPUT,
JUMP_A,
17,
HALT
};

void recreate_example_binary_files() {
  struct machine_code program;
  program.size = sizeof(hello_world_machine_code);
  program.data = hello_world_machine_code;
  create_binary_file("binary_examples/hello_world.BIN", program);
  program.size = sizeof(echo_machine_code);
  program.data = echo_machine_code;
  create_binary_file("binary_examples/echo.BIN", program);
}
