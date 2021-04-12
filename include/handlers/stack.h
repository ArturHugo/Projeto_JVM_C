#ifndef __STACK_H
#define __STACK_H

#include "common.h"
#include "frame.h"
#include "global.h"

void pop(const u1* instruction);
void pop2(const u1* instruction);
void dup(const u1* instruction);
void dup_x1(const u1* instruction);
void dup_x2(const u1* instruction);
void dup2(const u1* instruction);
void dup2_x1(const u1* instruction);
void dup2_x2(const u1* instruction);
void swap(const u1* instruction);

#endif  // __STACK_H
