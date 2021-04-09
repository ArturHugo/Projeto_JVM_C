#include "handlers/stores.h"
#include "frame.h"
#include "global.h"

/*
 * Store int into local variable
 *
 * opcode:	0x36
 * format: 	[istore, index]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void istore(const u1* operands) {
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
void lstore(const u1* operands);
