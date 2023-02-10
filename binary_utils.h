#ifndef BIN_UTILS_H
#define BIN_UTILS_H




#include<stdio.h>
#include<stdlib.h>
#include"simulator.h"




struct binary {
  int size;
  int* data;
};

void create_binary(const char *filepath, const struct binary bin);

struct binary load_binary(const char *filepath);

void free_binary(struct binary bin);

void recreate_example_binaries();




#endif
