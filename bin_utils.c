#include"bin_utils.h"




void create_binary_file(const char *filepath, const struct machine_code program) {
  FILE *file = fopen(filepath, "wb");
  fwrite(&program.size, sizeof(int), 1, file);
  fwrite(program.data, sizeof(int), program.size, file);
  fclose(file);
}

struct machine_code load_binary_file(const char *filepath) {
  FILE *file = fopen(filepath, "rb");
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

int hello_world_machine_code[65] = {
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
LOAD_I,
0,
HALT
};

int echo_machine_code[37] = {
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


LOAD_A, //here
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
LOAD_I,
0,
HALT
};

void recreate_example_binary_files() {
  struct machine_code program;
  program.size = 65;
  program.data = hello_world_machine_code;
  create_binary_file("binary_examples/hello_world.BIN", program);
  program.size = 37;
  program.data = echo_machine_code;
  create_binary_file("binary_examples/echo.BIN", program);
}
