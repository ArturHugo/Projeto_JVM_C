#include "handlers/loads.h"
#include "frame.h"
#include "global.h"

/*
 * format:  [tload, index]
 * stack:   (...) -> (..., value)
 * description: takes value of type t from local_variables[index] and pushes into operand stack
 */
void tload(const u1* instruction) {
  const u1* operands      = instruction + 1;
  Frame*    current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[*operands]);
  current_frame->local_pc += 2;
}

/*
 * format:  [iload_n]
 * stack:   (...) -> (..., value)
 * description: takes int value from local_variables[n] and pushes into operand stack
 */
void iload_n(const u1* instruction) {
  u1     n             = *instruction - 26;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[n]);
  current_frame->local_pc += 1;
}

/*
 * format:  [lload_n]
 * stack:   (...) -> (..., value)
 * description: takes long value from local_variables[n] and pushes into operand stack
 */
void lload_n(const u1* instruction) {
  u1     n             = *instruction - 30;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[n]);
  current_frame->local_pc += 1;
}

/*
 * format:  [fload_n]
 * stack:   (...) -> (..., value)
 * description: takes float value from local_variables[n] and pushes into operand stack
 */
void fload_n(const u1* instruction) {
  u1     n             = *instruction - 34;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[n]);
  current_frame->local_pc += 1;
}

/*
 * format:  [dload_n]
 * stack:   (...) -> (..., value)
 * description: takes double value from local_variables[n] and pushes into operand stack
 */
void dload_n(const u1* instruction) {
  u1     n             = *instruction - 38;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[n]);
  current_frame->local_pc += 1;
}

/*
 * format:  [aload_n]
 * stack:   (...) -> (..., value)
 * description: takes reference value from local_variables[n] and pushes into operand stack
 */
void aload_n(const u1* instruction) {
  u1     n             = *instruction - 42;
  Frame* current_frame = peekNode(frame_stack);
  pushValue(&current_frame->operand_stack, current_frame->local_variables[n]);
  current_frame->local_pc += 1;
}