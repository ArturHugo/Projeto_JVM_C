#ifndef __LOAD_HANDLERS_H
#define __LOAD_HANDLERS_H

#include "common.h"

void tload(u1* instruction);

void iload_n(u1* instruction);
void lload_n(u1* instruction);
void fload_n(u1* instruction);
void dload_n(u1* instruction);
void aload_n(u1* instruction);

void taload(u1* instruction);

#endif  // __LOAD_HANDLERS_H