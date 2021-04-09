#include "handlers/loads.h"
#include "frame.h"
#include "global.h"

/*
 * format:  [iload, index]
 * stack:   (...) -> (..., value)
 * description: takes int value from local_variables[index] and pushes into operand stack
 */
void iload(u1* bytecode) {
  u1*    operands      = bytecode + 1;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[*operands]);
}

/*
 * format:  [iload, index]
 * stack:   (...) -> (..., value)
 * description: takes int value from local_variables[index] and pushes into operand stack
 */
// void lload(u1* bytecode) {
//   u1*    operands      = bytecode + 1;
//   Frame* current_frame = peekNode(frame_stack);
//   pushValue(&current_frame->operand_stack, current_frame->local_variables[*operands]);
// }
