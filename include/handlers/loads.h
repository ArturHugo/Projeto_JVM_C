#ifndef __LOAD_HANDLERS_H
#define __LOAD_HANDLERS_H

#include "common.h"

void iload(u1* instruction);
void lload(u1* instruction);
void fload(u1* instruction);
void dload(u1* instruction);
void aload(u1* instruction);

void iload_n(u1* instruction);
void lload_n(u1* instruction);
void fload_n(u1* instruction);
void dload_n(u1* instruction);
void aload_n(u1* instruction);

void iaload(u1* instruction);
void laload(u1* instruction);
void faload(u1* instruction);
void daload(u1* instruction);
void aaload(u1* instruction);
void baload(u1* instruction);
void caload(u1* instruction);
void saload(u1* instruction);

#endif  // __LOAD_HANDLERS_H