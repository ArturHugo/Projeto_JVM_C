#include "handlers/references.h"

void invokestatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  // JavaType value;
  // popValue(&(current_frame->operand_stack), &value);

  ConstantPoolInfo* current_cp_info =
      &(current_frame->constant_pool[instruction[1] << 8 | instruction[2]]);

  ClassFile*  current_class;
  MethodInfo* current_method;

  if(current_cp_info->tag == CONSTANT_METHODREF)
    current_class = current_cp_info
                         ->methodref_info

                             current_frame->local_pc += 3;
}