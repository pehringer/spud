#ifndef BINARY_H
#define BINARY_H




#include<stdio.h>
#include<stdlib.h>
#include"simulation.h"




struct binary {
  int size;
  int* data;
};

int binary_write(const char *filepath, const struct binary *bin);

struct binary* binary_read(const char *filepath);

void binary_free(struct binary *bin);




#endif
