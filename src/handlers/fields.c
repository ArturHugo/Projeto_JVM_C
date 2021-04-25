#include "handlers/fields.h"
#include "class-file.h"
#include "common.h"
#include "constant-pool.h"
#include "fields.h"
#include "frame.h"
#include "global.h"
#include "map.h"
#include "method-area.h"
#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getstatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;

  /* System.out.print(ln) tenta pegar o field out de System
   * nós temos o próprio handler para print (ver invokevirtual)
   * então pulamos esse caso */
  if(strcmp((char*) field_info._class, "java/lang/System")) {
    Class* field_class = loadClass((char*) field_info._class);

    if(field_class->_status != initialized)
      initializeClass(field_class);

    FieldInfo* field = mapGet(field_class->_field_map, (char*) field_info._name);

    if(field == NULL) {
      panic("NoSuchFieldError: %s", field_info._name);
    }

    pushValue(&current_frame->operand_stack, field->value);
    // TODO: checar se é estático
  } else {
    JavaType dummy_value = {.cat_tag = 0, .int_value = 0};
    pushValue(&current_frame->operand_stack, dummy_value);
  }

  current_frame->local_pc += 3;
}

void putstatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;

  Class* field_class = loadClass((char*) field_info._class);

  if(field_class->_status != initialized) {
    initializeClass(field_class);
  }

  FieldInfo* field = mapGet(field_class->_field_map, (char*) field_info._name);

  if(field == NULL) {
    panic("NoSuchFieldError: %s", field_info._name);
  }

  // TODO: checar se é estático

  popValue(&current_frame->operand_stack, &field->value);

  current_frame->local_pc += 3;
}

void getfield(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  /** get object from operand_stack */
  JavaType objectref;
  popValue(&current_frame->operand_stack, &objectref);
  Object* object = objectref.reference_value;

  if(object == NULL) {
    panic("NullPointerException at getfield");
  }

  /** get field */
  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;

  JavaType* value = mapGet(object->fields_and_values, (char*) field_info._name);

  pushValue(&current_frame->operand_stack, *value);

  current_frame->local_pc += 3;
}

void putfield(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  JavaType value;
  popValue(&current_frame->operand_stack, &value);

  /** get object from operand_stack */
  JavaType objectref;
  popValue(&current_frame->operand_stack, &objectref);
  Object* object = objectref.reference_value;

  if(object == NULL) {
    panic("NullPointerException at getfield");
  }

  /** get field */
  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;

  JavaType* current_value = mapGet(object->fields_and_values, (char*) field_info._name);
  *current_value          = value;

  current_frame->local_pc += 3;
}
