#include "handlers/stores.h"
#include "frame.h"
#include "global.h"

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
void store(const u1* instruction) {
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
 * format: 	[lstore_n]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void dstore_n(const u1* instruction) { store_with_offset(0x47, 2); }
