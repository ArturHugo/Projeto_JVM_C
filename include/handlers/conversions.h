#ifndef __CONVERSIONS_H
#define __CONVERSIONS_H

#include "common.h"

void l2f();                      /* i2f */
void l2d();                      /* i2f */
void f2l(const u1* instruction); /* f2i */
void f2d();
void d2l(const u1* instruction); /* d2i */
void d2f();
void i2b();
void i2c();
void i2s();

#endif  // __CONVERSIONS_H
