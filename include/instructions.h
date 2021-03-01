#ifndef __INSTRUCTIONS_H
#define __INSTRUCTIONS_H

#include "common.h"

// table with instructions that take args. each entry [x][y]
// contains y=0 -> bytecode and y=1 -> number of args. If number of
// args == 10, args are of variable ammount.

static u1 instructionSizeTable[55][2] = {
    {16, 1},  {17, 1},   {18, 1},  {19, 2},   {20, 2},   {21, 1},
    {22, 1},  {23, 1},   {24, 1},  {25, 1},   {54, 1},   {55, 1},
    {56, 1},  {57, 1},   {58, 1},  {132, 2},  {153, 2},  {154, 2},
    {155, 2}, {156, 2},  {157, 2}, {158, 2},  {159, 2},  {160, 2},
    {161, 2}, {162, 2},  {163, 2}, {164, 2},  {165, 2},  {166, 2},
    {167, 2}, {168, 2},  {169, 1}, {170, 10}, {171, 10}, {178, 2},
    {179, 2}, {180, 2},  {181, 2}, {182, 2},  {183, 2},  {184, 2},
    {185, 4}, {186, 4},  {187, 2}, {188, 1},  {189, 2},  {192, 2},
    {193, 2}, {196, 10}, {197, 3}, {198, 2},  {199, 2},  {200, 4},
    {201, 4}};

static char* instructionMnemonicTable[206] = {
    "nop","aconst_null","iconst_m1","iconst_0","iconst_1","iconst_2","iconst_3",
    "iconst_4","iconst_5","lconst_0","lconst_1","fconst_0","fconst_1","fconst_2",
    "dconst_0","dconst_1","bipush","Sipush","ldc","ldc_w","ldc2_w",
    "iload","lload","fload","dload","aload","iload_0","iload_1",
    "iload_2","iload_3","lload_0","lload_1","lload_2","lload_3","fload_0",
    "fload_1","fload_2","fload_3","dload_0","dload_1","dload_2","dload_3",
    "aload_0","aload_1","aload_2","aload_3","iaload","laload","faload",
    "Daload","aaload","baload","caload","saload","istore","lstore",
    "fstore","dstore","astore","istore_0","istore_1","istore_2","istore_3",
    "lstore_0","lstore_1","lstore_2","lstore_3","fstore_0","fstore_1","fstore_2",
    "fstore_3","dstore_0","dstore_1","dstore_2","dstore_3","astore_0","astore_1",
    "astore_2","astore_3","iastore","lastore","Fastore","dastore","aastore",
    "bastore","castore","sastore","pop","pop2","dup","dup_x1",
    "dup_x2","dup2","dup2_x1","dup2_x2","swap","iadd","ladd",
    "fadd","dadd","isub","lsub","fsub","dsub","imul",
    "lmul","fmul","dmul","idiv","ldiv","fdiv","ddiv",
    "irem","lrem","frem","drem","ineg","lneg","fneg",
    "dneg","ishl","lshl","ishr","lshr","iushr","lushr",
    "iand","land","ior","lor","ixor","lxor","iinc",
    "i2l","i2f","i2d","l2i","l2f","l2d","f2i",
    "f2l","f2d","d2i","d2l","d2f","l2b","i2c",
    "i2s","lcmp","fcmpl","fcmpg","dcmpl","dcmpg","ifeq",
    "ifne","iflt","ifge","ifgt","ifle","if_icmpeq","if_icmpne",
    "if_icmplt","if_icmpge","if_icmpgt","if_icmple","if_acmpeg","if_acmpne","goto",
    "jsr","ret","tableswitch","lookupswitch","ireturn","lreturn","freturn",
    "dreturn","areturn","Return","getstatic","putstatic","getfield","putfield",
    "invokevirtual","invokespecial","invokestatic","invokeinterface",
    "instruction not defined","new","newarray","anewarray","arraylength","athrow",
    "checkcast","instanceof","monitorenter","monitorexit","wide","multianewarray",
    "ifnull","ifnonnull","goto_w","jsr_w"};

typedef struct {
  u1  bytecode;
  u1  n_args;
  u1* args;
  u2  pc;
  // talvez adicionar indicadores de retorno
} instruction;

void readInstructions(u1* code, u1 len, instruction** instructions);
void printInstructions(instruction*, u1 len);
void testInstructions();

#endif