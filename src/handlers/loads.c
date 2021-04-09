#include "handlers/loads.h"
#include "frame.h"
#include "global.h"

/*
 * format:  [iload, index]
 * stack:   (...) -> (..., value)
 * description: takes int value from local_variables[index] and pushes into operand stack
 */
void iload(u1* instruction) {
  u1*    operands      = instruction + 1;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[*operands]);
}

void lload(u1* instruction){};
void fload(u1* instruction){};
void dload(u1* instruction){};
void aload(u1* instruction){};

/*
 * format:  [iload, index]
 * stack:   (...) -> (..., value)
 * description: takes int value from local_variables[index] and pushes into operand stack
 */
// void lload(u1* instruction) {
//   u1*    operands      = instruction + 1;
//   Frame* current_frame = peekNode(frame_stack);
//   pushValue(&current_frame->operand_stack, current_frame->local_variables[*operands]);
// }
