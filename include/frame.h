#ifndef __FRAME_H
#define __FRAME_H

#include "constant-pool.h"
#include "stack.h"

typedef struct Frame {
  Stack             operand_stack;
  u4*               local_variables;
  ConstantPoolInfo* constant_pool;
} Frame;

#endif  // __FRAME_H