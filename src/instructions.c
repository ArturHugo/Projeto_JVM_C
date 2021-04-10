#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "common.h"
#include "instructions.h"

// table with instructions that take opperandBytes. each entry [x][y]
// contains y=0 -> bytecode and y=1 -> number of opperandBytes. If
// number of opperandBytes == 10, opperandBytes are of variable
// ammount. y=2 -> 1 = constant pool, 2 = caso particular, 0 = não constant pool e normal

#define T_BOOLEAN 4
#define T_CHAR    5
#define T_FLOAT   6
#define T_DOUBLE  7
#define T_BYTE    8
#define T_SHORT   9
#define T_INT     10
#define T_LONG    11

#define _BYTECODE 0

#define _N_OPPERAND_BYTES 1
#define _VARIABLE_N_BYTES 10

#define _OP_FLAG               2
#define _OP_FLAG_NORMAL        0
#define _OP_FLAG_CONSTANT_POOL 1
#define _OP_FLAG_SPECIAL_CASE  2
#define _OP_FLAG_BRANCH        3

static u1 instruction_info_table[55][3] = {
    {16, 1, 2},   {17, 2, 2},  {18, 1, 1},  {19, 2, 1},  {20, 2, 1},  {21, 1, 0},   {22, 1, 0},
    {23, 1, 0},   {24, 1, 0},  {25, 1, 0},  {54, 1, 0},  {55, 1, 0},  {56, 1, 0},   {57, 1, 0},
    {58, 1, 0},   {132, 2, 2}, {153, 2, 3}, {154, 2, 3}, {155, 2, 3}, {156, 2, 3},  {157, 2, 3},
    {158, 2, 3},  {159, 2, 3}, {160, 2, 3}, {161, 2, 3}, {162, 2, 3}, {163, 2, 3},  {164, 2, 3},
    {165, 2, 3},  {166, 2, 3}, {167, 2, 3}, {168, 2, 3}, {169, 1, 0}, {170, 10, 2}, {171, 10, 2},
    {178, 2, 1},  {179, 2, 1}, {180, 2, 1}, {181, 2, 1}, {182, 2, 1}, {183, 2, 1},  {184, 2, 1},
    {185, 4, 1},  {186, 4, 1}, {187, 2, 1}, {188, 1, 2}, {189, 2, 1}, {192, 2, 1},  {193, 2, 1},
    {196, 10, 2}, {197, 3, 1}, {198, 2, 3}, {199, 2, 3}, {200, 4, 3}, {201, 4, 3}};

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

/* --------------------- local function declarations -----------------------------*/
u4   nInstructionOps(u1* code, u4 offset);
u1   instructionOpFlag(u1 bytecode);
u4   read32bFrom8b(u1* array);
void printMethodPath(ConstantPoolInfo* cp, u2 cp_index);

/* --------------------- printInstructions() helper functions -----------------------------*/
void printInstructionsConstantPool(u1                bytecode,
                                   u1                n_opperand_bytes,
                                   u1*               opperand_bytes,
                                   ConstantPoolInfo* cp);
void printInstructionsConstantPoolArg(ConstantPoolInfo* cp, u2 cp_index);

void printInstructionsSpecial(
    u1 bytecode, u1 n_opperand_bytes, u1* opperand_bytes, ConstantPoolInfo* cp, u2 pc);
void printInstructionsSpecialWide(u1* opperand_bytes, ConstantPoolInfo* cp);
void printInstructionsSpecialTableswitch(u1 n_opperand_bytes, u1* opperand_bytes, u2 pc);
void printInstructionsSpecialLookupswitch(u1 n_opperand_bytes, u1* opperand_bytes, u2 pc);

void printInstructionsNormal(u1 n_opperand_bytes, u1* opperand_bytes);

/*-----------------------------------Code-------------------------------------------------*/

u4 read32bFrom8b(u1* array) {
  u4 output = (array[0] << 24 | array[1] << 16 | array[2] << 8 | array[3]);
  return output;
}

// obs.: opperand_bytes are being copied by reference. pass pointer
// to Instruction* variable in "output";
Instruction* readInstructions(u1* code, u4 n_instruction) {
  Instruction* instructions = calloc(n_instruction, sizeof(Instruction));
  u4           current_byte = 0;
  for(u4 i = 0; i < n_instruction; i++) {
    instructions[i].bytecode         = code[current_byte];
    instructions[i].n_opperand_bytes = nInstructionOps(code + current_byte, current_byte);
    instructions[i].opperand_bytes   = code + current_byte + 1;
    instructions[i].pc               = current_byte;
    current_byte += 1 + instructions[i].n_opperand_bytes;
  }
  return instructions;
}

// algoritmo para print de operandos de instrução
/*
if tem bytes
  if constant pool
    imprime #
    if 1 byte
      imprime o byte e string
    else
      junta dois primeiros e imprime + string
      imprimir restantes separados
  else
    if caso particular -> 132, 170, 171, 188, 196.
      depende
    else
      if 1 byte
        imprime o byte
      else
        junto
*/

void printInstructionsConstantPoolArg(ConstantPoolInfo* cp, u2 cp_index) {
  if((cp[cp_index].tag != CONSTANT_STRING) && (cp[cp_index].tag != CONSTANT_INTEGER) &&
     (cp[cp_index].tag != CONSTANT_FLOAT) && (cp[cp_index].tag != CONSTANT_LONG) &&
     (cp[cp_index].tag != CONSTANT_DOUBLE)) {
    printMethodPath(cp, cp_index);
  } else {
    printConstantValue(cp, cp_index);
  }
}

void printInstructionsConstantPool(u1                bytecode,
                                   u1                n_opperand_bytes,
                                   u1*               opperand_bytes,
                                   ConstantPoolInfo* cp) {
  printf("#");
  u2 cp_index;
  if(n_opperand_bytes == 1) {
    cp_index = (u2) *opperand_bytes;
    printf("%d ", cp_index);
  } else {
    cp_index = (u2)((opperand_bytes[0] << 8) | opperand_bytes[1]);

    printf("%d ", cp_index);

    u1 printed_opperands = 2;
    while(printed_opperands < n_opperand_bytes) {
      printf("%d ", opperand_bytes[printed_opperands]);
      printed_opperands++;
    }
  }

  printInstructionsConstantPoolArg(cp, cp_index);

  // If multianewarray
  if(bytecode == 197) {
    printf(" dim %d", opperand_bytes[2]);
  }
}

void printInstructionsSpecialWide(u1* opperand_bytes, ConstantPoolInfo* cp) {
  char* widened_opcode = instruction_mnemonic_table[opperand_bytes[0]];
  printf("%s #", widened_opcode);

  u2 cp_index = (u2)((opperand_bytes[1] << 8) | opperand_bytes[2]);
  printf("%d ", cp_index);

  // If iinc
  if(opperand_bytes[0] == 132) {
    u2 const_byte = (u2)((opperand_bytes[3] << 8) | opperand_bytes[4]);
    printf("%d ", const_byte);
  } else {
    printMethodPath(cp, cp_index);  // TODO nao tem path pro iinc
  }
}

void printInstructionsSpecialTableswitch(u1 n_opperand_bytes, u1* opperand_bytes, u2 pc) {
  u1 padding       = n_opperand_bytes % 4;
  u4 default_value = read32bFrom8b(opperand_bytes + padding);
  u4 low, high, offset;
  low  = read32bFrom8b(opperand_bytes + padding + 4);
  high = read32bFrom8b(opperand_bytes + padding + 8);

  printf("%d to %d\n", low, high);

  for(u4 i = low; i <= high; i++) {
    offset = read32bFrom8b(opperand_bytes + padding + 12 + 4 * (i - low));
    printf("\t%d:\t\t%d\t(+%d)\n", i, pc + offset, offset);
  }
  printf("\tdefault:\t%d\t(+%d)\n", pc + default_value, default_value);
}

void printInstructionsSpecialLookupswitch(u1 n_opperand_bytes, u1* opperand_bytes, u2 pc) {
  u1 padding       = n_opperand_bytes % 4;
  u4 default_value = read32bFrom8b(opperand_bytes + padding);
  u4 n_pairs       = read32bFrom8b(opperand_bytes + padding + 4);

  printf("%d\n", n_pairs);

  u4 match, offset;

  for(u4 i = 0; i < n_pairs; i++) {
    match  = read32bFrom8b(opperand_bytes + padding + 8 * (i + 1));
    offset = read32bFrom8b(opperand_bytes + padding + 8 * (i + 1) + 4);

    printf("\t%d:\t%d\t(+%d)\n", match, pc + offset, offset);
  }
  printf("\tdefault:\t%d\t(+%d)\n", pc + default_value, default_value);
}

void printInstructionsSpecial(
    u1 bytecode, u1 n_opperand_bytes, u1* opperand_bytes, ConstantPoolInfo* cp, u2 pc) {
  switch(bytecode) {
    // Wide
    case 196: {
      printInstructionsSpecialWide(opperand_bytes, cp);
    } break;

    // Iinc
    case 132:
      printf("%d by %d", opperand_bytes[0], (int8_t) opperand_bytes[1]);
      break;

    // TableSwitch
    case 170: {
      printInstructionsSpecialTableswitch(n_opperand_bytes, opperand_bytes, pc);
    } break;

    // LookupSwitch
    case 171: {
      printInstructionsSpecialLookupswitch(n_opperand_bytes, opperand_bytes, pc);
    } break;

    // Bipush
    case 16:
      printf("%d ", (int8_t) opperand_bytes[0]);
      break;

    // Sipush
    case 17:
      printf("%d ", (int8_t)(opperand_bytes[0] << 8 | opperand_bytes[1]));
      break;

    // Newarray
    case 188:
      printf("%d ", opperand_bytes[0]);
      switch(opperand_bytes[0]) {
        case T_BOOLEAN:
          printf("(boolean) ");
          break;

        case T_CHAR:
          printf("(char) ");
          break;

        case T_FLOAT:
          printf("(float) ");
          break;

        case T_DOUBLE:
          printf("(double) ");
          break;

        case T_BYTE:
          printf("(byte) ");
          break;

        case T_SHORT:
          printf("(short) ");
          break;

        case T_INT:
          printf("(int) ");
          break;

        case T_LONG:
          printf("(long) ");
          break;
      }
      break;
  }
}

void printInstructionsNormal(u1 n_opperand_bytes, u1* opperand_bytes) {
  u4 opperand;
  switch(n_opperand_bytes) {
    case 1:
      opperand = (u4) opperand_bytes[0];
      break;

    case 2:
      opperand = (u4)((opperand_bytes[0] << 8) | opperand_bytes[1]);
      break;

    default:
      opperand = read32bFrom8b(opperand_bytes);
      break;
  }
  printf("%d", opperand);
}

void printInstructions(Instruction* instructions, u4 n_instrs, ConstantPoolInfo* cp) {
  printf("\nInstructions read:\n\n");
  for(u4 i = 0; i < n_instrs; i++) {

    u1    bytecode         = instructions[i].bytecode;
    char* mnem             = instruction_mnemonic_table[instructions[i].bytecode];
    u1    n_opperand_bytes = instructions[i].n_opperand_bytes;
    u2    pc               = instructions[i].pc;
    u1*   opperand_bytes   = instructions[i].opperand_bytes;

    printf("%d\t%s ", pc, mnem);

    // printing arguments:

    if(n_opperand_bytes) {
      u1 op_flag = instructionOpFlag(bytecode);
      if(op_flag == _OP_FLAG_CONSTANT_POOL) {
        printInstructionsConstantPool(bytecode, n_opperand_bytes, opperand_bytes, cp);
      } else {
        if(op_flag == _OP_FLAG_SPECIAL_CASE) {
          printInstructionsSpecial(bytecode, n_opperand_bytes, opperand_bytes, cp, pc);
        } else {
          if(op_flag == _OP_FLAG_BRANCH) {
            // If goto_w or jsr_w
            if(n_opperand_bytes == 4) {
              int32_t branch_offset = read32bFrom8b(opperand_bytes);
              printf("%d (%d)", pc + branch_offset, branch_offset);
            } else {
              int16_t branch_offset = (opperand_bytes[0] << 8) | opperand_bytes[1];
              printf("%d (%d)", pc + branch_offset, branch_offset);
            }
          } else {
            printInstructionsNormal(n_opperand_bytes, opperand_bytes);
          }
        }
      }
    }
    printf("\n");
  }
}

void printMethodPath(ConstantPoolInfo* cp, u2 cp_index) {
  u1   num_of_strings = 0;
  u1** utf8_strings   = getUtf8Strings(&num_of_strings, cp, cp_index);

  if(utf8_strings == NULL) {
    printf("No utf8 strings found!");
    return;
  }
  if(num_of_strings == 1) {
    printf("<%s>", utf8_strings[0]);
  } else {
    printf("<%s.%s>", utf8_strings[0], utf8_strings[1]);
  }
  free(utf8_strings);
}

u4 nInstructionOps(u1* code, u4 offset) {
  for(u1 i = 0; i < 55; i++) {
    u1 current_instruction_code = instruction_info_table[i][_BYTECODE];
    if(current_instruction_code > *code) {
      break;
    }
    if(current_instruction_code == *code) {
      u1 current_instruction_size = instruction_info_table[i][_N_OPPERAND_BYTES];
      if(current_instruction_size == _VARIABLE_N_BYTES) {
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

u1 instructionOpFlag(u1 bytecode) {
  for(u1 i = 0; i < 55; i++) {
    u1 current_instruction_code = instruction_info_table[i][_BYTECODE];
    if(current_instruction_code == bytecode) {
      return instruction_info_table[i][_OP_FLAG];
    }
  }
  return 0;
}

u4 calcTableswitchOps(u1* code, u4 offset) {
  u4 n_ops = 0;
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
  return n_ops;
}

u4 calcLookupswitchOps(u1* code, u4 offset) {
  u4 n_ops = 0;
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

  n_ops += 8 * n_pairs;  // adding 32 bit pair bytes
  return n_ops;
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

u4 nInstructions(u1* code, u4 n_bytes) {
  u4 output = 0;
  u4 i      = 0;
  while(i < n_bytes) {
    i += 1 + nInstructionOps(code + i, i);
    output++;
  }
  return output;
}
