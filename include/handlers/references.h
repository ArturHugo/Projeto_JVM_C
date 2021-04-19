#ifndef __REFERENCES_H
#define __REFERENCES_H

#include "common.h"
#include "frame.h"
#include "global.h"
#include "methods.h"
#include "stack.h"

//_insctruction appended to reserved names

void invokestatic(const u1* instruction);
void new(const u1* instruction);
void newarray(const u1* instruction);
void anewarray(const u1* instruction);
void arraylength(const u1* instruction);

#endif  // __REFERENCES_H
