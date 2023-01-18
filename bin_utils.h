#ifndef BIN_UTILS_H
#define BIN_UTILS_H




#include<stdio.h>
#include<stdlib.h>
#include"simulator.h"



struct machine_code {
  int size;
  int* data;
};




void create_binary_file(const char *filepath, const struct machine_code program);
struct machine_code load_binary_file(const char *filepath);
void free_machine_code(struct machine_code program);
void recreate_example_binary_files();




#endif
