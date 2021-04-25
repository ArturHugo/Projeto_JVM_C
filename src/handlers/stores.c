#include <stdlib.h>
#include <string.h>

#include "exceptions.h"
#include "frame.h"
#include "global.h"
#include "handlers/stores.h"

void tstore(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + instruction[1]);
  current_frame->local_pc += 2;
}

void istore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x3b));
  current_frame->local_pc += 1;
}

void lstore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x3f));
  current_frame->local_pc += 1;
}

void fstore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x43));
  current_frame->local_pc += 1;
}

void dstore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x47));
  current_frame->local_pc += 1;
}

void astore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x4b));
  current_frame->local_pc += 1;
}

void tastore() {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = popNode(&current_frame->operand_stack);
  JavaType* index         = popNode(&current_frame->operand_stack);
  JavaType* array_ref     = popNode(&current_frame->operand_stack);

  if(array_ref == NULL) {
    pushNode(&current_frame->operand_stack, array_ref);
    pushNode(&current_frame->operand_stack, index);
    pushNode(&current_frame->operand_stack, value);
    return throwException("java/lang/NullPointerException");
  }

  Array* array = array_ref->reference_value;

  if(index->int_value < 0 || index->int_value > array->length) {
    pushNode(&current_frame->operand_stack, array_ref);
    pushNode(&current_frame->operand_stack, index);
    pushNode(&current_frame->operand_stack, value);
    return throwException("java/lang/ArrayIndexOutOfBoundsException");
  }

  array->elements[index->int_value] = *value;

  current_frame->local_pc += 1;
  free(index);
  free(value);
}
