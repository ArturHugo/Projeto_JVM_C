#ifndef __MATH_H
#define __MATH_H

#include "common.h"

void iadd();
void ladd();
void fadd();
void dadd();

void isub();
void lsub();
void fsub();
void dsub();

void imul();
void lmul();
void fmul();
void dmul();

void idiv();
void ldiv_instruction();
void fdiv();
void ddiv();

void irem();
void lrem();
void frem();
void drem();

void ineg();
void lneg();
void fneg();
void dneg();

void ishl();
void lshl();

void ishr();
void lshr();

void iushr();
void lushr();

void iand();
void land();

void ior();
void lor();

void ixor();
void lxor();

void iinc(const u1* instruction);

#endif  // __MATH_H