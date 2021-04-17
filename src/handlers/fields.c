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
 *  [-] class must be loaded (load if not)
 *  [ ] field must be static (IncompattibleClassChangeError)
 */
void getstatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;
  // TODO: a classe pode ser java/lang/System. pq??

  Class* field_class = loadClass((char*) field_info._class);

  if(field_class == NULL) {
    panic("Class not found during getstatic: %s", field_info._class);
  }

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
 *  [-] class must be loaded (load if not)
 *  [ ] field must be static (IncompattibleClassChangeError)
 *  [ ] value must be type compatible with field descriptor
 *  [ ] if field is final, current method must be <clinit> (IllegalAccessError)
 */
void putstatic(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  u2     index         = (instruction[1] << 8 | instruction[2]);

  FieldrefInfo field_info = current_frame->constant_pool[index].fieldref_info;

  Class* field_class = loadClass((char*) field_info._class);

  if(field_class == NULL) {
    panic("Class not found during putstatic: %s", field_info._class);
  }

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
