#include "handlers/stores.h"
#include "frame.h"
#include "global.h"

/*
 * format: 	[istore, index]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void u4_store(u1* operands) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + operands[1]);
  current_frame->local_pc += 2;
}

/*
 * Store long into local variable
 *
 * opcode:	0x37
 * format: 	[lstore, index]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void u8_store(u1* operands) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + operands[1] + 1); /* high bytes */
  popValue(&current_frame->operand_stack, current_frame->local_variables + operands[1]); /* low  bytes */
  current_frame->local_pc += 2;
}
