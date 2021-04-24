#include <stdlib.h>
#include <string.h>

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
void tastore(const u1* instruction) {
  Frame*    current_frame = peekNode(frame_stack);
  JavaType* value         = popNode(&current_frame->operand_stack);
  JavaType* index         = popNode(&current_frame->operand_stack);
  JavaType* array_ref     = popNode(&current_frame->operand_stack);

  if(array_ref == NULL) {
    printf("NullPointerException at %x", current_frame->local_pc);
    exit(1);
  }

  // TODO: check if its out of bounds (store in first index its length?? 🤔)
  ((Array*) array_ref->reference_value)->elements[index->int_value] = *value;

  current_frame->local_pc += 1;
  free(index);
  free(value);
}
