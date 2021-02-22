#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "common.h"

typedef struct {
    u1 bytecode;
    u1 size;        //number of 8-bit bytes contained in struction
    u2 pc;
} instruction;

instruction* instructionsRead(u1* code);
void instructionsPrint();

#endif