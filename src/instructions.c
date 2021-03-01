#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "common.h"
#include "instructions.h"

// local function declarations:
// obs.: argument is used as a term for any byte other than the
// instruction, refactor to use "bytes" and "arguments" as different/
// possible refactor: table/lookupswitch with more than 254 args?
u1 nInstructionArgs(u1* code, u1 offset);
u1 nInstructions(u1* code, u1 len);
u1 calcTableswitchArgs(u1* code, u1 offset);
u1 calcLookupswitchArgs(u1* code, u1 offset);
u1 calcWideArgs(u1* code);

// obs.: args and mnemonic are being copied by reference. pass pointer
// to instruction* to be set;
void readInstructions(u1* code, u1 len, instruction** output) {
  u1           n      = nInstructions(code, len);
  instruction* instrs = (instruction*) calloc(n, sizeof(instruction));
  *output             = instrs;
  u1 currentByte      = 0;
  for(u1 i = 0; i < n; i++) {
    instrs[i].bytecode = code[currentByte];
    instrs[i].n_args =
        nInstructionArgs(code + currentByte, currentByte);
    instrs[i].args = code + 1;
    instrs[i].pc   = i;
    currentByte += 1 + instrs[i].n_args;
  }
}

void printInstructions(instruction* instructions, u1 len) {
  printf("\ninstructions read:\n\n");
  for(u1 i = 0; i < len; i++) {
    u1    instr = instructions[i].bytecode;
    char* mnem  = instructionMnemonicTable[instructions[i].bytecode];
    u1    nargs = instructions[i].n_args;
    u2    pc    = instructions[i].pc;

    char* term = "arguments";
    if(nargs == 1) {
      term = "argument";
    }

    printf("0x%x: %s, with %d %s on PC = %d\n",
           instr,
           mnem,
           nargs,
           term,
           pc);
  }
}

// implementar casos de numero de argumentos variável, quando
// instructionSizeTable[i][1] == 10
u1 nInstructionArgs(u1* code, u1 offset) {
  for(u1 i = 0; i < 55; i++) {
    u1 currentInstrCode = instructionSizeTable[i][0];
    if(currentInstrCode > *code) {
      break;
    }
    if(currentInstrCode == *code) {
      u1 currentInstrSize = instructionSizeTable[i][1];
      if(currentInstrSize == 10) {
        switch(*code) {
          case 170:
            return calcTableswitchArgs(code, offset);
            break;
          case 171:
            return calcLookupswitchArgs(code, offset);
            break;
          case 196:
            return calcWideArgs(code);
            break;
        }
      }
      return currentInstrSize;
    }
  }
  return 0;
}

u1 calcTableswitchArgs(u1* code, u1 offset) {
  u1 nArgs = 0;
  while(offset % 4 != 3) {  // adding padding bytes
    nArgs++;
    offset++;
  }
  // reading default, low and high

  // default is not yet used
  // u4 defaultValue = read32bFrom8b(code + nArgs + 1);
  nArgs += 4;

  u4 lowValue = read32bFrom8b(code + nArgs + 1);
  nArgs += 4;

  u4 highValue = read32bFrom8b(code + nArgs + 1);
  nArgs += 4;

  u4 offsets = highValue - lowValue + 1;
  nArgs += 4 * offsets;  // adding argument bytes
  // nArgs -1 is returned beacause padding bytes loop adds an extra
  // byte
  return (u1) nArgs;
}

u1 calcLookupswitchArgs(u1* code, u1 offset) {
  u1 nArgs = 0;
  while(offset % 4 != 3) {  // adding padding bytes
    nArgs++;
    offset++;
  }
  // reading default, low and high

  // default is not yet used
  // u4 defaultValue = read32bFrom8b(code + nArgs + 1);
  nArgs += 4;

  u4 npairs = read32bFrom8b(code + nArgs + 1);
  nArgs += 4;

  nArgs += 4 * npairs;  // adding argument bytes
  return (u1) nArgs;
}

u1 calcWideArgs(u1* code) {
  // wide followed by iinc
  if(*(code + 1) == 132) {
    return 5;
  }
  // instruction is not checked, possible error throw
  return 3;
}

u1 nInstructions(u1* code, u1 len) {
  u1 output = 0;
  u1 i      = 0;
  while(i < len) {
    i += 1 + nInstructionArgs(code + i, i);
    output++;
  }
  return output;
}

void testInstructions() {
  u1 code[43] = {99, 16, 8,  170, 10,  10, 10, 10, 0, 0,   0,
                 0,  0,  0,  0,   0,   1,  2,  3,  4, 171, 1,
                 2,  3,  10, 10,  10,  10, 0,  0,  0, 1,   1,
                 2,  3,  4,  196, 132, 1,  2,  3,  4, 5};
  instruction* instructions;
  readInstructions(code, 38, &instructions);
  printInstructions(instructions, 5);
  free(instructions);
}