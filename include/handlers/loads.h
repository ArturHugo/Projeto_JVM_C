#ifndef __LOAD_HANDLERS_H
#define __LOAD_HANDLERS_H

#include "common.h"

void tload(const u1* instruction);

void iload_n(const u1* instruction);
void lload_n(const u1* instruction);
void fload_n(const u1* instruction);
void dload_n(const u1* instruction);
void aload_n(const u1* instruction);

void taload(const u1* instruction);

#endif  // __LOAD_HANDLERS_H