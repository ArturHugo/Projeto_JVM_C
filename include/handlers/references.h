#ifndef __REFERENCES_H
#define __REFERENCES_H

#include "common.h"
#include "frame.h"
#include "global.h"
#include "methods.h"
#include "stack.h"

//_insctruction appended to reserved names

void invokestatic(const u1* instruction);
void invokespecial(const u1* instruction);
void new(const u1* instruction);
void newarray(const u1* instruction);
void anewarray();
void arraylength();

#endif  // __REFERENCES_H
