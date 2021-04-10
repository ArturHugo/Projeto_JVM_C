#ifndef __STORES_H
#define __STORES_H

#include "common.h"

void store(const u1* instruction);
void istore_n(const u1* instruction);
void lstore_n(const u1* instruction);
void fstore_n(const u1* instruction);
void dstore_n(const u1* instruction);

#endif  // __STORES_H
