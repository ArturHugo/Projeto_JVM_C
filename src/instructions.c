#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "common.h"
#include "instructions.h"

// obs.: args and mnemonic are being copied by reference. pass pointer
// to instruction* to be set;
void readInstructions(u1* code, u1 len, instruction** output) {
  u1           n      = nInstructions(code, len);
  instruction* instrs = (instruction*) calloc(n, sizeof(instruction));
  *output             = instrs;
  u1 currentByte      = 0;
  for(u1 i = 0; i < n; i++) {
    u1 currentCode     = code[currentByte];
    instrs[i].bytecode = currentCode;
    instrs[i].n_args   = nInstructionArgs(currentCode);
    instrs[i].args     = code + 1;
    instrs[i].pc       = i;
    currentByte += 1 + instrs[i].n_args;
  }
}

void printInstructions(instruction* instructions, u1 len) {
  printf("instructions read:\n\n\n");
  for(u1 i = 0; i < len; i++) {
    u1    instr = instructions[i].bytecode;
    char* mnem  = instructionMnemonicTable[instructions[i].bytecode];
    u1    nargs = instructions[i].n_args;
    u2    pc    = instructions[i].pc;

    char* term = "arguments";
    if(nargs == 1) {
      term = "argument";
    }

    printf("%x: %s, with %d %s on PC = %d\n",
           instr,
           mnem,
           nargs,
           term,
           pc);
  }
}

// implementar casos de numero de argumentos variável, quando
// instructionSizeTable[i][1] == 10
u1 nInstructionArgs(u1 code) {
  for(u1 i = 0; i < 55; i++) {
    if(instructionSizeTable[i][0] > code) {
      break;
    }
    if(instructionSizeTable[i][0] == code) {
      return instructionSizeTable[i][1];
    }
  }
  return 0;
}

u1 nInstructions(u1* code, u1 len) {
  u1 output = 0;
  u1 i      = 0;
  while(i < len) {
    i += 1 + nInstructionArgs(code[i]);
    output++;
  }
  return output;
}

void testInstructions() {
  u1           code[5] = {99, 75, 16, 8, 120};
  instruction* instructions;
  readInstructions(code, 5, &instructions);
  printInstructions(instructions, 4);
  free(instructions);
}