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

/**
 * get static field from class
 *
 * opcode:	0xb2
 * format: 	[getstatic, indexbyte1, indexbyte2]
 * stack: 	(...) -> (..., value)
 * description:	get the value from a field on a class, may initialize class if not already
 * constaints:
 *  [x] class must be loaded (load if not)
 *  [ ] field must be static (IncompattibleClassChangeError)
 */
void getstatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;
  // TODO: a classe pode ser java/lang/System. pq??

  Class* field_class = loadClass((char*) field_info._class);

  if(field_class->_status != initialized)
    initializeClass(field_class);

  FieldInfo* field = mapGet(field_class->_field_map, (char*) field_info._name);

  if(field == NULL) {
    panic("NoSuchFieldError: %s", field_info._name);
  }

  // TODO: checar se é estático

  pushValue(&current_frame->operand_stack, field->value);

  current_frame->local_pc += 3;
}

/**
 * set static field in class
 *
 * opcode:	0xb3
 * format: 	[putstatic, indexbyte1, indexbyte2]
 * stack: 	(..., value) -> (...)
 * description:
 * constaints:
 *  [x] class must be loaded (load if not)
 *  [ ] field must be static (IncompattibleClassChangeError)
 *  [ ] value must be type compatible with field descriptor (???)
 *  [ ] field must not be final if current method is not <clinit> (IllegalAccessError)
 */
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

/**
 * get field from object
 *
 * opcode:	0xb4
 * format: 	[getfield, indexbyte1, indexbyte2]
 * stack: 	(..., objectref) -> (..., value)
 * description: get field from object e push into the operand_stack
 * constaints:
 *  [x] object must not be null
 *  [ ] field must not be static (IncompattibleClassChangeError)
 */
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

/**
 * put value into field in objectref
 *
 * opcode:	0xb4
 * format: 	[putfield, indexbyte1, indexbyte2]
 * stack: 	(..., objectref, value) -> (...)
 * description: set field from object to value
 * constaints:
 *  [x] object must not be null (NullPointerException)
 *  [ ] value must be type compatible with field descriptor (???)
 *  [ ] field must not be static (IncompattibleClassChangeError)
 *  [ ] field must not be final outside <init> (IllegalAccessError)
 */
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
  *current_value = value;

  current_frame->local_pc += 3;
}
