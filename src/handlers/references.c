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
  ClassFile* new_class = loadClass(new_class_name);

  if(new_class == NULL) {
    printf("\npc = %d: invokestatic failed\n", current_frame->local_pc);
    exit(1);
  }

  if(new_class->_status != initialized) {
    resolveReferences(new_class);
  }

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
  ClassFile* new_class = loadClass(new_class_name);

  if(new_class == NULL) {
    printf("\npc = %d: new failed\n", current_frame->local_pc);
    exit(1);
  }

  if(new_class->_status != initialized) {
    resolveReferences(new_class);
  }

  initializeClass(new_class);

  Object* new_object = malloc(sizeof(Object));

  JavaType object_reference;
  object_reference.cat_tag         = CAT1;
  object_reference.reference_value = new_object;

  new_object->class = new_class;

  new_object->fields_and_values = _newMap(new_class->fields_count * 1.5);

  FieldInfo* field;
  u2         field_name_index;
  char*      field_name;
  JavaType*  field_value;
  u2         field_type_index;
  char       field_type;
  for(u2 i = 0; i < new_class->fields_count; i++) {
    field = &(new_class->fields[i]);

    field_name_index = field->name_index;
    field_type_index = field->descriptor_index;

    field_name = (char*) new_class->constant_pool[field_name_index].utf8_info.bytes;
    field_type = (char) new_class->constant_pool[field_type_index].utf8_info.bytes[0];

    // calloc used to initialize values as zero
    field_value = calloc(1, sizeof(*field_value));

    if(field_type == 'D' || field_type == 'J')
      field_value->cat_tag = CAT2;
    else
      field_value->cat_tag = CAT1;

    mapAdd(&new_object->fields_and_values, field_name, field_value);
  }

  pushValue(&current_frame->operand_stack, object_reference);

  current_frame->local_pc += 3;
}

void newarray(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType count_javatype;

  popValue(&current_frame->operand_stack, &count_javatype);

  int32_t count = count_javatype.int_value;

  if(count < 0) {
    printf("\npc = %d: newarray NegativeArraySizeException\n", current_frame->local_pc);
    exit(1);
  }

  if(instruction[1] < 4 || instruction[1] > 11) {
    printf("\npc = %d: newarray invalid ntype\n", current_frame->local_pc);
    exit(1);
  }

  JavaType* elements = calloc(count, sizeof(JavaType));
  u1        cat      = CAT1;

  if(instruction[1] == 7 || instruction[1] == 11) {
    cat = CAT2;
  }

  for(int i = 0; i < count; i++) {
    elements[i].cat_tag = cat;
  }

  Array* new_array    = malloc(sizeof(Array));
  new_array->elements = elements;
  new_array->length   = count;
  new_array->type     = instruction[1];

  JavaType arrayref;
  arrayref.cat_tag         = CAT1;
  arrayref.reference_value = new_array;

  pushValue(&current_frame->operand_stack, arrayref);

  current_frame->local_pc += 2;
}

void anewarray(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType count_javatype;

  popValue(&current_frame->operand_stack, &count_javatype);

  int32_t count = count_javatype.int_value;

  if(count < 0) {
    printf("\npc = %d: newarray NegativeArraySizeException\n", current_frame->local_pc);
    exit(1);
  }

  JavaType* elements = calloc(count, sizeof(JavaType));

  for(int i = 0; i < count; i++) {
    elements[i].cat_tag = CAT1;
  }

  Array* new_array    = malloc(sizeof(Array));
  new_array->elements = elements;
  new_array->length   = count;
  new_array->type     = TYPE_REFERENCE;

  JavaType arrayref;
  arrayref.cat_tag         = CAT1;
  arrayref.reference_value = new_array;

  pushValue(&current_frame->operand_stack, arrayref);

  current_frame->local_pc += 3;
}

void arraylength(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType arrayref;

  popValue(&current_frame->operand_stack, &arrayref);

  if(arrayref.reference_value == NULL) {
    printf("\npc = %d: arraylength NullPointerException\n", current_frame->local_pc);
    exit(1);
  }

  Array* array = arrayref.reference_value;

  JavaType length;
  length.cat_tag   = CAT1;
  length.int_value = array->length;

  pushValue(&current_frame->operand_stack, length);

  current_frame->local_pc++;
}
