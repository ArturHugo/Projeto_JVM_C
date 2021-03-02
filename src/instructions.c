#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "common.h"
#include "instructions.h"

// local function declarations:
// obs.: opperand byte is used as a term for any byte other than the
// instruction.
// possible refactor: table/lookupswitch with more than 254
// opperandBytes?
u1 nInstructionOps(u1* code, u1 offset);
u1 nInstructions(u1* code, u1 len);
u1 calcTableswitchOps(u1* code, u1 offset);
u1 calcLookupswitchOps(u1* code, u1 offset);
u1 calcWideOps(u1* code);

// obs.: opperandBytes are being copied by reference. pass pointer
// to instruction* variable in "output";
void readInstructions(u1* code, u1 len, instruction** output) {
  u1           n      = nInstructions(code, len);
  instruction* instrs = (instruction*) calloc(n, sizeof(instruction));
  *output             = instrs;
  u1 currentByte      = 0;
  for(u1 i = 0; i < n; i++) {
    instrs[i].bytecode = code[currentByte];
    instrs[i].n_opperandBytes =
        nInstructionOps(code + currentByte, currentByte);
    instrs[i].opperandBytes = code + 1;
    instrs[i].pc            = i;
    currentByte += 1 + instrs[i].n_opperandBytes;
  }
}

void printInstructions(instruction* instructions, u1 len) {
  printf("\ninstructions read:\n\n");
  for(u1 i = 0; i < len; i++) {
    u1    instr = instructions[i].bytecode;
    char* mnem  = instructionMnemonicTable[instructions[i].bytecode];
    u1    nopperandBytes = instructions[i].n_opperandBytes;
    u2    pc             = instructions[i].pc;

    char* term = "operand";
    if(nopperandBytes == 1) {
      term = "operands";
    }

    printf("0x%x: %s, with %d %s on PC = %d\n",
           instr,
           mnem,
           nopperandBytes,
           term,
           pc);
  }
}

u1 nInstructionOps(u1* code, u1 offset) {
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
            return calcTableswitchOps(code, offset);
            break;
          case 171:
            return calcLookupswitchOps(code, offset);
            break;
          case 196:
            return calcWideOps(code);
            break;
        }
      }
      return currentInstrSize;
    }
  }
  return 0;
}

u1 calcTableswitchOps(u1* code, u1 offset) {
  u1 nOps = 0;
  while(offset % 4 != 3) {  // adding padding bytes
    nOps++;
    offset++;
  }
  // reading default, low and high

  // default is not yet used
  // u4 defaultValue = read32bFrom8b(code + nOps + 1);
  nOps += 4;

  u4 lowValue = read32bFrom8b(code + nOps + 1);
  nOps += 4;

  u4 highValue = read32bFrom8b(code + nOps + 1);
  nOps += 4;

  u4 offsets = highValue - lowValue + 1;
  nOps += 4 * offsets;  // adding 32 bit offset bytes
  // nOps -1 is returned beacause padding bytes loop adds an extra
  // byte
  return (u1) nOps;
}

u1 calcLookupswitchOps(u1* code, u1 offset) {
  u1 nOps = 0;
  while(offset % 4 != 3) {  // adding padding bytes
    nOps++;
    offset++;
  }
  // reading default, low and high

  // default is not yet used
  // u4 defaultValue = read32bFrom8b(code + nOps + 1);
  nOps += 4;

  u4 npairs = read32bFrom8b(code + nOps + 1);
  nOps += 4;

  nOps += 4 * npairs;  // adding 32 bit pair bytes
  return (u1) nOps;
}

u1 calcWideOps(u1* code) {
  // wide followed by iinc
  if(*(code + 1) == 132) {
    return 5;
  }
  // not checking if instruction is of accepted format, possible error
  // throw
  return 3;
}

u1 nInstructions(u1* code, u1 len) {
  u1 output = 0;
  u1 i      = 0;
  while(i < len) {
    i += 1 + nInstructionOps(code + i, i);
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