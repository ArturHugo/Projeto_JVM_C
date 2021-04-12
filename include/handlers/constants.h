#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include "common.h"
#include "frame.h"
#include "global.h"

void nop(const u1* instruction);
void aconst_null(const u1* instruction);
void iconst_n(const u1* instruction);
void lconst_n(const u1* instruction);
void fconst_n(const u1* instruction);
void dconst_n(const u1* instruction);
void bipush(const u1* instruction);
void sipush(const u1* instruction);
void ldc(const u1* instruction);
void ldc_w(const u1* instruction);
void ldc_2_w(const u1* instruction);

#endif  // __CONSTANTS_H
