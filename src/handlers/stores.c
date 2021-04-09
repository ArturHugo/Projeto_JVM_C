#include "handlers/stores.h"
#include "frame.h"
#include "global.h"

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
void istore_n(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + *instruction - 0x3b);
  current_frame->local_pc += 1;
}
