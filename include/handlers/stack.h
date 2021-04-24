#ifndef __STACK_H
#define __STACK_H

#include "common.h"
#include "frame.h"
#include "global.h"

//_insctruction appended to reserved names

void pop_instruction();
void pop2();
void dup_instruction();
void dup_x1();
void dup_x2();
void dup2_instruction();
void dup2_x1();
void dup2_x2();
void swap();

#endif  // __STACK_H
