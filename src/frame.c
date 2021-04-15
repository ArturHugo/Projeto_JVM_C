#include "frame.h"

#include "class-file.h"

Frame* newFrame(ClassFile* current_class, u2 method_index) {
  Frame* new_frame          = malloc(sizeof(*new_frame));
  new_frame->constant_pool  = current_class->constant_pool;
  new_frame->current_method = &(current_class->methods[method_index]);
  new_frame->operand_stack  = NULL;
  new_frame->local_pc       = 0;
  // TODO pode não ser attribute[0] que contém code info
  new_frame->local_variables =
      malloc((new_frame->current_method->attributes->code_info.max_locals) * sizeof(u4));

  return new_frame;
}
