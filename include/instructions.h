#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "common.h"

typedef struct {
  u1  bytecode;
  u1* mnemonic;
  u1  size;  // number of 8-bit bytes contained in struction
  u2  pc;
  // talvez indicadores de argumentos retorno
} instruction;

instruction* readInstructions(u1* code, u1 len);
void         printInstructions(instruction*, u1 len);

#endif