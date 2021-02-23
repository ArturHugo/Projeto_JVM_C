#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "instructions.h"

instruction* readInstructions(u1* code, u1 len) {
  // implementar estrutura de lista, ir iterando em code e
  // decrementando len
  instruction instr;
  instr.bytecode = 10;
  instr.pc       = 42;
  instr.size     = 1;
}

void printInstructions(instruction* instructions, u1 len) {
  // iterar na lista, imprimir coisas
  printf("teste");
}