#include "handlers/references.h"
#include "class-file.h"
#include "constant-pool.h"
#include "exceptions.h"
#include "frame.h"
#include "global.h"
#include "methods.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>

/**
 * format:  [invokestatic, indexbyte1, indexbyte2]
 * stack:   (..., [arg1, [arg2...]]) -> (...)
 * description:  Invoke a class (static) method. args are the method arguments, indexbyte1 and 2 are
 * joined and used as a constant pool index to the static method.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
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

  ClassFile* new_class = loadClass(new_class_name);

  if(new_class == NULL) {
    printf("\npc = %d: invokestatic failed\n", current_frame->local_pc);
    exit(1);
  }

  if(new_class->_status != initialized) {
    resolveReferences(new_class);
  }

  initializeClass(new_class);

  Frame* new_frame = newFrame(new_class, new_method_name, new_method_descriptor);

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

/**
 * Invoke instance method; special handling for superclass, private,
 * and instance initialization method invocations
 *
 * opcode:	0xb7
 * format: 	[invokestatic, indexbyte1, indexbyte2]
 * stack: 	(..., objectref, [arg1, [arg2 ...]]) -> (...)
 * description: TODO
 * constaints:
 *  [ ]
 * observation: only implementation of 1 & 2. (JVM 8 spec, p482) is implemented
 */
void invokespecial(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  MethodrefInfo methodref_info = current_frame->constant_pool[index].methodref_info;

  if(!strcmp((char*) methodref_info._class, "java/lang/Object")) {
    current_frame->local_pc += 3;
    return;
  }

  u2 n_args = getArgumentCount((u1*) methodref_info._descriptor) + 1; /** + 1 para o objectref?? */
  JavaType* method_parameters = malloc(sizeof(*method_parameters) * n_args);

  for(u2 i = 1; i <= n_args; i++) {
    popValue(&current_frame->operand_stack, method_parameters + (n_args - i));
  }

  Class *method_class = loadClass((char*) methodref_info._class);

  Frame* new_frame = newFrame(method_class, (char*) methodref_info._name, (char*) methodref_info._descriptor);

  for(u2 i = 0; i < n_args; i++) {
    new_frame->local_variables[i] = method_parameters[i];
    if(method_parameters[i].cat_tag == CAT2)
      i++;
  }

  pushNode(&frame_stack, new_frame);

  current_frame->local_pc += 3;
}

/**
 * format:  [new, indexbyte1, indexbyte2]
 * stack:   (...) -> (..., objectref)
 * description:  Create new object.  indexbyte1 and 2 are joined and used as a constant pool index
 * to the object's class or interface.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void new(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  ConstantPoolInfo* current_cp_info =
      &(current_frame->constant_pool[instruction[1] << 8 | instruction[2]]);

  char* new_class_name = (char*) current_cp_info->class_info._name;

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

    mapAdd(new_object->fields_and_values, field_name, field_value);
  }

  pushValue(&current_frame->operand_stack, object_reference);

  current_frame->local_pc += 3;
}

/**
 * format:  [newarray, atype]
 * stack:   (..., count) -> (..., arrayref)
 * description:  The count must be of type int. It is popped off the operand stack.
 * The count represents the number of elements in the array to be
 * created.
 * The atype is a code that indicates the type of array to create. It must
 * take one of the following values:
 *
 * T_BOOLEAN 4
 * T_CHAR 5
 * T_FLOAT 6
 * T_DOUBLE 7
 * T_BYTE 8
 * T_SHORT 9
 * T_INT 10
 * T_LONG 11
 *
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
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

/**
 * format:  [new, indexbyte1, indexbyte2]
 * stack:   (...) -> (..., objectref)
 * description:  Create new array of reference. indexbyte1 and 2 are joined and used as a constant
 * pool index to the simbolic reference of a class, array or interface type. Count is of type int
 * and represents the number of components of the array to be created.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void anewarray() {
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

/**
 * format:  [arraylength]
 * stack:   (..., arrayref) -> (..., length)
 * description:  The arrayref must be of type reference and must refer to an array.
 * It is popped from the operand stack. The length of the array it
 * references is determined. That length is pushed onto the operand
 * stack as an int.
 * @param instruction uint8_t array containing instruction op_code on index 0 and argunments from
 * index 1 on, if any.
 */
void arraylength() {
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

void athrow() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* objectref     = peekNode(current_frame->operand_stack);

  if(objectref == NULL) {
    return throwException("java/lang/ArrayIndexOutOfBoundsException");
  }

  Object* object           = objectref->reference_value;
  u2      this_class_index = object->class->this_class;
  char*   class_name = (char*) current_frame->constant_pool[this_class_index].class_info._name;

  while(current_frame == NULL) {
    Exception* exception = findException(class_name);

    // if it was found, drop operand_stack, move to handler_pc and push object back
    if(exception != NULL) {
      while(current_frame->operand_stack)
        popNode(&current_frame->operand_stack);

      pushNode(&current_frame->operand_stack, objectref);

      current_frame->local_pc = exception->handler_pc;
    } else {
      Frame* old_frame = popNode(&frame_stack);
      free(old_frame);
    }
  }
}
