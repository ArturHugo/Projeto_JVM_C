#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/stores.h"
#include "vector.h"

#define store_with_offset(offset, size)                                                            \
  Frame* current_frame = peekNode(frame_stack);                                                    \
  popValue(&current_frame->operand_stack,                                                          \
           current_frame->local_variables + (*instruction - offset) * size);                       \
  current_frame->local_pc += 1;

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
void istore_n(const u1* instruction) { store_with_offset(0x3b, 1); }

/*
 * Store long into local variable
 *
 * opcode:	0x3f, 0x40, 0x41, 0x42
 * format: 	[lstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void lstore_n(const u1* instruction) { store_with_offset(0x3f, 2); }

/*
 * Store float into local variable
 *
 * opcode:	0x43, 0x44, 0x45, 0x46
 * format: 	[fstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void fstore_n(const u1* instruction) { store_with_offset(0x43, 1); }

/*
 * Store double into local variable
 *
 * opcode:	0x47, 0x48, 0x49, 0x4a
 * format: 	[dstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void dstore_n(const u1* instruction) { store_with_offset(0x47, 2); }

/*
 * Store reference or (TODO) returnAddress into local variable
 *
 * opcode:	0x4b, 0x4c, 0x4d, 0x4e
 * format: 	[astore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void astore_n(const u1* instruction) { store_with_offset(0x4b, 1); }

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
  JavaType* array         = popNode(&current_frame->operand_stack);

  if(array == NULL) {
    printf("NullPointerException at %x", current_frame->local_pc);
    exit(1);
  }

  // TODO: fix this warning
  if(*instruction == 0x53) {
    println("Warning: aastore does not make runtime type checks yet.");
  }

  // TODO: check if its out of bounds (store in first index its length?? 🤔)
  ((JavaType*) array->reference_value)[index->int_value] = *value;

  free(index);
  free(value);
}
