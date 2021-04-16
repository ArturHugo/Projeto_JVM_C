#ifndef __STACK_H
#define __STACK_H

#include "common.h"
#include "frame.h"
#include "global.h"

//_insctruction appended to reserved names

void pop_instruction(const u1* instruction);
void pop2(const u1* instruction);
void dup_instruction(const u1* instruction);
void dup_x1(const u1* instruction);
void dup_x2(const u1* instruction);
void dup2_instruction(const u1* instruction);
void dup2_x1(const u1* instruction);
void dup2_x2(const u1* instruction);
void swap(const u1* instruction);

#endif  // __STACK_H