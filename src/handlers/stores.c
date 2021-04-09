#include "handlers/stores.h"
#include "frame.h"
#include "global.h"

/*
 * Store value into local variable
 *
 * opcode:	0x36, 0x37
 * format: 	[istore, index]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void store(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + instruction[1]);
  current_frame->local_pc += 2;
}
