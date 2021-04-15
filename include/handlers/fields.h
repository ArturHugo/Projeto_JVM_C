#ifndef __FIELD_INSTRUCTIONS_H
#define __FIELD_INSTRUCTIONS_H

#include "common.h"

void getstatic(const u1* instruction);
void putstatic(const u1* instruction);
void getfield(const u1* instruction);
void putfield(const u1* instruction);

#endif  // __FIELD_INSTRUCTIONS_H
