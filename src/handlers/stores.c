#include <stdlib.h>
#include <string.h>

#include "execution-engine.h"
#include "frame.h"
#include "global.h"
#include "handlers/stores.h"

/*
 * Store value into local variable
 *
 * opcode:	0x36, 0x37, 0x38, 0x39
 * format: 	[store, index]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void tstore(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + instruction[1]);
  current_frame->local_pc += 2;
}

/*
 * Store int into local variable
 *
 * opcode:	0x3b, 0x3c, 0x3d, 0x3e
 * format: 	[istore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void istore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x3b));
  current_frame->local_pc += 1;
}

/*
 * Store long into local variable
 *
 * opcode:	0x3f, 0x40, 0x41, 0x42
 * format: 	[lstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void lstore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x3f));
  current_frame->local_pc += 1;
}

/*
 * Store float into local variable
 *
 * opcode:	0x43, 0x44, 0x45, 0x46
 * format: 	[fstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void fstore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x43));
  current_frame->local_pc += 1;
}

/*
 * Store double into local variable
 *
 * opcode:	0x47, 0x48, 0x49, 0x4a
 * format: 	[dstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void dstore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x47));
  current_frame->local_pc += 1;
}

/*
 * Store reference or (TODO) returnAddress into local variable
 *
 * opcode:	0x4b, 0x4c, 0x4d, 0x4e
 * format: 	[astore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void astore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + (*instruction - 0x4b));
  current_frame->local_pc += 1;
}

/*
 * Store value into array
 *
 * opcode:	0x4f
 * format: 	[tstore]
 * stack: 	(..., arrayref, index, value) -> (...)
 * description:	put value into array at index
 */
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
