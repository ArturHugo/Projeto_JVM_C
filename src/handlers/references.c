#include "handlers/references.h"

void invokestatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  ConstantPoolInfo* current_cp_info =
      &(current_frame->constant_pool[instruction[1] << 8 | instruction[2]]);

  char* new_class_name;
  char* new_method_name;
  char* new_method_descriptor;

  // TODO does this even work?
  if(current_cp_info->tag == CONSTANT_METHODREF) {
    new_class_name        = (char*) (current_cp_info->methodref_info._class);
    new_method_name       = (char*) (current_cp_info->methodref_info._name);
    new_method_descriptor = (char*) (current_cp_info->methodref_info._descriptor);
  } else {
    new_class_name        = (char*) (current_cp_info->interface_methodref_info._interface);
    new_method_name       = (char*) (current_cp_info->interface_methodref_info._name);
    new_method_descriptor = (char*) (current_cp_info->interface_methodref_info._descriptor);
  }

  loadClass(new_class_name);

  ClassFile* new_class = mapGet(method_area.loaded_classes, new_class_name);

  if(new_class == NULL) {
    printf("\npc = %d: invokestatic failed\n");
    exit(1);
  }

  resolveReferences(new_class);
  initializeClass(new_class);

  Frame* new_frame = newFrame(new_class, new_method_name);

  MethodInfo* new_method = mapGet(new_class->_method_map, new_method_name);

  // TODO calcular n args a partir de new_method_descriptor
  u2 n_args = 0;

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