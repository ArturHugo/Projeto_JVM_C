#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "common.h"

typedef struct {
  u1  bytecode;
  u1  n_opperand_bytes;
  u1* opperand_bytes;
  u2  pc;
  // talvez adicionar indicadores de retorno
} Instruction;

void readInstructions(u1* code, u1 len, Instruction** instructions);
void printInstructions(Instruction*, u1 len);
void testInstructions();

#endif