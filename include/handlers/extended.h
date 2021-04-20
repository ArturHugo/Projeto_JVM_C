#ifndef __EXTENDED_HANDLERS_H
#define __EXTENDED_HANDLERS_H

#include "common.h"

void wide(const u1* instruction);
void multianewarray(const u1* instruction);
void ifnull(const u1* instruction);
void ifnonnull(const u1* instruction);
void goto_w(const u1* instruction);
void jsr_w(const u1* instruction);

#endif  //__EXTENDED_HANDLERS_H