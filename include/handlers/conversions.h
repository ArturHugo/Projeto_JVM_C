#ifndef __CONVERSIONS_H
#define __CONVERSIONS_H

#include "common.h"

void i2l();
void i2f();
void i2d();
void l2i();
void l2f();
void l2d();
void f2l(const u1* instruction); /* f2i */
void f2d();
void d2l(const u1* instruction); /* d2i */
void d2f();
void i2b();
void i2c();
void i2s();

#endif  // __CONVERSIONS_H
