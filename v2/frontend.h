#ifndef FRONTEND_H
#define FRONTEND_H


#include "backend.h"
#include <stdio.h>


#define MINIMUM_LINES 40
#define MINIMUM_COLUMNS 40


void InitializeTerminal(int lines);
void DrawTerminal(struct Simulation *s);


#endif
