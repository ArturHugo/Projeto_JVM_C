#include "handlers/references.h"

void invokestatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  ConstantPoolInfo* current_cp_info =
      &(current_frame->constant_pool[instruction[1] << 8 | instruction[2]]);

  char* new_class_name;
  char* new_method_name;
  char* new_method_descriptor;

  if(current_cp_info->tag == CONSTANT_METHODREF) {
    new_class_name        = (char*) (current_cp_info->methodref_info._class);
    new_method_name       = (char*) (current_cp_info->methodref_info._name);
    new_method_descriptor = (char*) (current_cp_info->methodref_info._descriptor);
  } else {
    new_class_name        = (char*) (current_cp_info->interface_methodref_info._interface);
    new_method_name       = (char*) (current_cp_info->interface_methodref_info._name);
    new_method_descriptor = (char*) (current_cp_info->interface_methodref_info._descriptor);
  }

  // TODO does this even work?
  loadClass(new_class_name);

  ClassFile* new_class = mapGet(method_area.loaded_classes, new_class_name);

  if(new_class == NULL) {
    printf("\npc = %d: invokestatic failed\n", current_frame->local_pc);
    exit(1);
  }

  resolveReferences(new_class);
  initializeClass(new_class);

  Frame* new_frame = newFrame(new_class, new_method_name);

  // loading opperands from current stack to new local variables
  u2       n_args               = getArgumentCount((u1*) new_method_descriptor);
  u2       local_variable_index = 0;
  JavaType temp_value;
  for(u2 i = 0; i < n_args; i++) {
    popValue(&(current_frame->operand_stack), &temp_value);
    new_frame->local_variables[local_variable_index] = temp_value;
    local_variable_index++;
    if(temp_value.cat_tag == CAT2)
      local_variable_index++;
  }

  pushNode(&frame_stack, new_frame);

  current_frame->local_pc += 3;
}

void new(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  ConstantPoolInfo* current_cp_info =
      &(current_frame->constant_pool[instruction[1] << 8 | instruction[2]]);

  char* new_class_name = (char*) current_cp_info->class_info._name;

  // TODO does this even work?
  loadClass(new_class_name);

  ClassFile* new_class = mapGet(method_area.loaded_classes, new_class_name);

  if(new_class == NULL) {
    printf("\npc = %d: invokestatic failed\n", current_frame->local_pc);
    exit(1);
  }

  resolveReferences(new_class);
  initializeClass(new_class);

  Frame* new_frame = newFrame(new_class, new_method_name);

  // loading opperands from current stack to new local variables
  u2       n_args               = getArgumentCount((u1*) new_method_descriptor);
  u2       local_variable_index = 0;
  JavaType temp_value;
  for(u2 i = 0; i < n_args; i++) {
    popValue(&(current_frame->operand_stack), &temp_value);
    new_frame->local_variables[local_variable_index] = temp_value;
    local_variable_index++;
    if(temp_value.cat_tag == CAT2)
      local_variable_index++;
  }

  pushNode(&frame_stack, new_frame);

  current_frame->local_pc += 3;
}