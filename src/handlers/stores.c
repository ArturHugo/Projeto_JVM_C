#include "handlers/stores.h"
#include "frame.h"
#include "global.h"

/*
 * format: 	[istore, index]
 * stack: 	(..., value) -> (...)
 * description:	put value into operand_stack at index
 */
void istore(u1* operands) {
  Frame* current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, current_frame->local_variables + *operands);
}
