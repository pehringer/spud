#ifndef SIMULATOR_H
#define SIMULATOR_H




#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include"bin_utils.h"



/***************
Pocessor Opcodes
***************/
#define LOAD_I 0
#define LOAD 1
#define LOAD_A 2
#define SWAP 3
#define ADD 4
#define SUB 5
#define SAVE 6
#define SAVE_A 7
#define JUMP 8
#define JUMP_A 9
#define JUMP_Z 10
#define JUMP_N 11
#define JUMP_P 12
#define HALT 13




/****************************
Peripheral Register Addresses
****************************/
#define FIRST_PERIPHERAL 65500
#define TERMINAL_INPUT 65500
#define TERMINAL_OUTPUT 65501




/****************************
Miscellaneous Register Values
*****************************/
#define EMPTY 0
#define END_OF_INPUT '\n'




#endif
