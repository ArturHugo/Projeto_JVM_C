#ifndef __CONSTANTS_H
#define __CONSTANTS_H

#include "common.h"
#include "frame.h"
#include "global.h"

void nop(u1* instruction);
void aconst_null(u1* instruction);
void iconst_n(u1* instruction);
void lconst_n(u1* instruction);
void fconst_n(u1* instruction);
void dconst_n(u1* instruction);
void bipush(u1* instruction);
void sipush(u1* instruction);
void ldc(u1* instruction);
void ldc_w(u1* instruction);
void ldc_2_w(u1* instruction);

#endif  // __CONSTANTS_H
