#ifndef __FRAME_H
#define __FRAME_H

#include "class-file.h"
#include "constant-pool.h"
#include "stack.h"

typedef struct Frame {
  Stack             operand_stack;
  u4                local_pc;
  u4*               local_variables;
  ConstantPoolInfo* constant_pool;
  MethodInfo*       current_method;
} Frame;

Frame* newFrame(ClassFile* current_class, u2 method_index);
Frame* _newFrame(u2 max_locals);

#endif  // __FRAME_H
