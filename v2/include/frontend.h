#ifndef FRONTEND_H
#define FRONTEND_H


#include "backend.h"
#include <stdio.h>


#define MINIMUM_LINES 32
#define MINIMUM_COLUMNS 32


void InitializeTerminal(int lines);
void DrawTerminal(struct Simulation *s);


#endif
