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

u1 nInstructions(u1* code, u1 n_bytes);

Instruction* readInstructions(u1* code, u1 n_bytes, u4 n_instruction);

void printInstructions(Instruction* instructions, u1 length, ConstantPoolInfo* cp);

#endif