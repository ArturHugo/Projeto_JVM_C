#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "common.h"
#include "instructions.h"

// table with instructions that take opperandBytes. each entry [x][y]
// contains y=0 -> bytecode and y=1 -> number of opperandBytes. If
// number of opperandBytes == 10, opperandBytes are of variable
// ammount.

static u1 instruction_size_table[55][2] = {
    {16, 1},  {17, 1},   {18, 1},   {19, 2},  {20, 2},  {21, 1},  {22, 1},  {23, 1},
    {24, 1},  {25, 1},   {54, 1},   {55, 1},  {56, 1},  {57, 1},  {58, 1},  {132, 2},
    {153, 2}, {154, 2},  {155, 2},  {156, 2}, {157, 2}, {158, 2}, {159, 2}, {160, 2},
    {161, 2}, {162, 2},  {163, 2},  {164, 2}, {165, 2}, {166, 2}, {167, 2}, {168, 2},
    {169, 1}, {170, 10}, {171, 10}, {178, 2}, {179, 2}, {180, 2}, {181, 2}, {182, 2},
    {183, 2}, {184, 2},  {185, 4},  {186, 4}, {187, 2}, {188, 1}, {189, 2}, {192, 2},
    {193, 2}, {196, 10}, {197, 3},  {198, 2}, {199, 2}, {200, 4}, {201, 4}};

static char* instruction_mnemonic_table[206] = {"nop",
                                                "aconst_null",
                                                "iconst_m1",
                                                "iconst_0",
                                                "iconst_1",
                                                "iconst_2",
                                                "iconst_3",
                                                "iconst_4",
                                                "iconst_5",
                                                "lconst_0",
                                                "lconst_1",
                                                "fconst_0",
                                                "fconst_1",
                                                "fconst_2",
                                                "dconst_0",
                                                "dconst_1",
                                                "bipush",
                                                "Sipush",
                                                "ldc",
                                                "ldc_w",
                                                "ldc2_w",
                                                "iload",
                                                "lload",
                                                "fload",
                                                "dload",
                                                "aload",
                                                "iload_0",
                                                "iload_1",
                                                "iload_2",
                                                "iload_3",
                                                "lload_0",
                                                "lload_1",
                                                "lload_2",
                                                "lload_3",
                                                "fload_0",
                                                "fload_1",
                                                "fload_2",
                                                "fload_3",
                                                "dload_0",
                                                "dload_1",
                                                "dload_2",
                                                "dload_3",
                                                "aload_0",
                                                "aload_1",
                                                "aload_2",
                                                "aload_3",
                                                "iaload",
                                                "laload",
                                                "faload",
                                                "Daload",
                                                "aaload",
                                                "baload",
                                                "caload",
                                                "saload",
                                                "istore",
                                                "lstore",
                                                "fstore",
                                                "dstore",
                                                "astore",
                                                "istore_0",
                                                "istore_1",
                                                "istore_2",
                                                "istore_3",
                                                "lstore_0",
                                                "lstore_1",
                                                "lstore_2",
                                                "lstore_3",
                                                "fstore_0",
                                                "fstore_1",
                                                "fstore_2",
                                                "fstore_3",
                                                "dstore_0",
                                                "dstore_1",
                                                "dstore_2",
                                                "dstore_3",
                                                "astore_0",
                                                "astore_1",
                                                "astore_2",
                                                "astore_3",
                                                "iastore",
                                                "lastore",
                                                "Fastore",
                                                "dastore",
                                                "aastore",
                                                "bastore",
                                                "castore",
                                                "sastore",
                                                "pop",
                                                "pop2",
                                                "dup",
                                                "dup_x1",
                                                "dup_x2",
                                                "dup2",
                                                "dup2_x1",
                                                "dup2_x2",
                                                "swap",
                                                "iadd",
                                                "ladd",
                                                "fadd",
                                                "dadd",
                                                "isub",
                                                "lsub",
                                                "fsub",
                                                "dsub",
                                                "imul",
                                                "lmul",
                                                "fmul",
                                                "dmul",
                                                "idiv",
                                                "ldiv",
                                                "fdiv",
                                                "ddiv",
                                                "irem",
                                                "lrem",
                                                "frem",
                                                "drem",
                                                "ineg",
                                                "lneg",
                                                "fneg",
                                                "dneg",
                                                "ishl",
                                                "lshl",
                                                "ishr",
                                                "lshr",
                                                "iushr",
                                                "lushr",
                                                "iand",
                                                "land",
                                                "ior",
                                                "lor",
                                                "ixor",
                                                "lxor",
                                                "iinc",
                                                "i2l",
                                                "i2f",
                                                "i2d",
                                                "l2i",
                                                "l2f",
                                                "l2d",
                                                "f2i",
                                                "f2l",
                                                "f2d",
                                                "d2i",
                                                "d2l",
                                                "d2f",
                                                "l2b",
                                                "i2c",
                                                "i2s",
                                                "lcmp",
                                                "fcmpl",
                                                "fcmpg",
                                                "dcmpl",
                                                "dcmpg",
                                                "ifeq",
                                                "ifne",
                                                "iflt",
                                                "ifge",
                                                "ifgt",
                                                "ifle",
                                                "if_icmpeq",
                                                "if_icmpne",
                                                "if_icmplt",
                                                "if_icmpge",
                                                "if_icmpgt",
                                                "if_icmple",
                                                "if_acmpeg",
                                                "if_acmpne",
                                                "goto",
                                                "jsr",
                                                "ret",
                                                "tableswitch",
                                                "lookupswitch",
                                                "ireturn",
                                                "lreturn",
                                                "freturn",
                                                "dreturn",
                                                "areturn",
                                                "Return",
                                                "getstatic",
                                                "putstatic",
                                                "getfield",
                                                "putfield",
                                                "invokevirtual",
                                                "invokespecial",
                                                "invokestatic",
                                                "invokeinterface",
                                                "instruction not defined",
                                                "new",
                                                "newarray",
                                                "anewarray",
                                                "arraylengthgth",
                                                "athrow",
                                                "checkcast",
                                                "instanceof",
                                                "monitorenter",
                                                "monitorexit",
                                                "wide",
                                                "multianewarray",
                                                "ifnull",
                                                "ifnonnull",
                                                "goto_w",
                                                "jsr_w"};

// local function declarations:
// obs.: opperand byte is used as a term for any byte other than the
// instruction.
// possible refactor: table/lookupswitch with more than 254
// opperandBytes?
u1 nInstructionOps(u1* code, u1 offset);
u1 nInstructions(u1* code, u1 length);
u1 calcTableswitchOps(u1* code, u1 offset);
u1 calcLookupswitchOps(u1* code, u1 offset);
u1 calcWideOps(u1* code);

// obs.: opperand_bytes are being copied by reference. pass pointer
// to Instruction* variable in "output";
void readInstructions(u1* code, u1 length, Instruction** output) {
  u1           n      = nInstructions(code, length);
  Instruction* instrs = calloc(n, sizeof(Instruction));
  *output             = instrs;
  u1 current_byte     = 0;
  for(u1 i = 0; i < n; i++) {
    instrs[i].bytecode         = code[current_byte];
    instrs[i].n_opperand_bytes = nInstructionOps(code + current_byte, current_byte);
    instrs[i].opperand_bytes   = code + 1;
    instrs[i].pc               = i;
    current_byte += 1 + instrs[i].n_opperand_bytes;
  }
}

////////TODO FUNCAO NOVA
/*
if constant pool
  imprime #
  if > 1 byte
    junta dois primeiros e imprime
  else
    imprime o byte
  imprimir restantes separados
else
  if caso particular
  else
    ???

*/

void printInstructions(Instruction* instructions, u1 length) {
  printf("\nInstructions read:\n\n");
  for(u1 i = 0; i < length; i++) {
    u1    instr            = instructions[i].bytecode;
    char* mnem             = instruction_mnemonic_table[instructions[i].bytecode];
    u1    n_opperand_bytes = instructions[i].n_opperand_bytes;
    u2    pc               = instructions[i].pc;

    char* term = "operands";
    if(n_opperand_bytes == 1) {
      term = "operand";
    }

    printf("%d\t%s", pc, mnem);
    // for
    printf(" #%d", n_opperand_bytes);
    printf("\t%s\n", "Stringzona");
  }
}

u1 nInstructionOps(u1* code, u1 offset) {
  for(u1 i = 0; i < 55; i++) {
    u1 current_instruction_code = instruction_size_table[i][0];
    if(current_instruction_code > *code) {
      break;
    }
    if(current_instruction_code == *code) {
      u1 current_instruction_size = instruction_size_table[i][1];
      if(current_instruction_size == 10) {
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
      return current_instruction_size;
    }
  }
  return 0;
}

u1 calcTableswitchOps(u1* code, u1 offset) {
  u1 n_ops = 0;
  while(offset % 4 != 3) {  // adding padding bytes
    n_ops++;
    offset++;
  }
  // reading default, low and high

  // default is not yet used
  // u4 defaultValue = read32bFrom8b(code + n_ops + 1);
  n_ops += 4;

  u4 lowValue = read32bFrom8b(code + n_ops + 1);
  n_ops += 4;

  u4 highValue = read32bFrom8b(code + n_ops + 1);
  n_ops += 4;

  u4 offsets = highValue - lowValue + 1;
  n_ops += 4 * offsets;  // adding 32 bit offset bytes
  // n_ops -1 is returned beacause padding bytes loop adds an extra
  // byte
  return (u1) n_ops;
}

u1 calcLookupswitchOps(u1* code, u1 offset) {
  u1 n_ops = 0;
  while(offset % 4 != 3) {  // adding padding bytes
    n_ops++;
    offset++;
  }
  // reading default, low and high

  // default is not yet used
  // u4 defaultValue = read32bFrom8b(code + n_ops + 1);
  n_ops += 4;

  u4 n_pairs = read32bFrom8b(code + n_ops + 1);
  n_ops += 4;

  n_ops += 4 * n_pairs;  // adding 32 bit pair bytes
  return (u1) n_ops;
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

u1 nInstructions(u1* code, u1 length) {
  u1 output = 0;
  u1 i      = 0;
  while(i < length) {
    i += 1 + nInstructionOps(code + i, i);
    output++;
  }
  return output;
}

void testInstructions() {
  u1 testSuccessfull = 1;
  u1 code[42]        = {99, 16, 8, 170, 10, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0,   1,   2, 3, 4, 171,
                 1,  2,  3, 10,  10, 10, 10, 0,  0, 0, 1, 1, 2, 3, 4, 196, 132, 1, 2, 3, 4};
  Instruction* instructions;
  readInstructions(code, 38, &instructions);
  printf("printInstructions() test:\n");
  printInstructions(instructions, 5);
  // instruction 0 test:
  if(instructions[0].bytecode != 99 || instructions[0].n_opperand_bytes != 0 ||
     instructions[0].pc != 0) {
    testSuccessfull = 0;
  }
  // instruction 1 test:
  if(instructions[1].bytecode != 16 || instructions[1].n_opperand_bytes != 1 ||
     instructions[1].pc != 1) {
    testSuccessfull = 0;
  }
  // instruction 2 test:
  if(instructions[2].bytecode != 170 || instructions[2].n_opperand_bytes != 16 ||
     instructions[2].pc != 2) {
    testSuccessfull = 0;
  }
  // instruction 3 test:
  if(instructions[3].bytecode != 171 || instructions[3].n_opperand_bytes != 15 ||
     instructions[3].pc != 3) {
    testSuccessfull = 0;
  }
  // instruction 4 test:
  if(instructions[4].bytecode != 196 || instructions[4].n_opperand_bytes != 5 ||
     instructions[4].pc != 4) {
    testSuccessfull = 0;
  }
  free(instructions);

  if(testSuccessfull) {
    printf("\nTest successfull!\n");
  } else {
    printf("\nInstructions are broken\n");
  }
}