#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "common.h"

typedef struct {
  u1  bytecode;
  u1  n_opperand_bytes;
  u1* opperand_bytes;
  u2  pc;
} Instruction;

u4 nInstructions(u1* code, u4 n_bytes);

Instruction* readInstructions(u1* code, u4 n_instruction);

void printInstructions(Instruction* instructions, u4 n_instrs, ConstantPoolInfo* cp);

/* --------------------- Helper functions -----------------------------*/
// funcões abaixo retornam o número de bytes de argumento para as instruções de tamanho
// variável. code deve ser o código da instrução inteira (incluindo bytecode). Offset
// deve ser o valor do pc local (número do byte atual no código).
u4 calcTableswitchOps(u1* code, u4 offset);
u4 calcLookupswitchOps(u1* code, u4 offset);
u1 calcWideOps(u1* code);

#endif