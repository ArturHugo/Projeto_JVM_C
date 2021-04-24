#ifndef __FRAME_H
#define __FRAME_H

#include "class-file.h"
#include "constant-pool.h"
#include "method-area.h"
#include "stack.h"

typedef struct Frame {
  Stack             operand_stack;
  u4                local_pc;
  JavaType*         local_variables;
  ConstantPoolInfo* constant_pool;
  MethodInfo*       current_method;
  char*             class_name;
} Frame;

Frame* newFrame(ClassFile* current_class, char* method_name, char* method_descriptor);

#endif  // __FRAME_H
