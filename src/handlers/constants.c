#include "handlers/constants.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

void nop(u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);
  current_frame->local_pc++;
}

void aconst_null(u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.reference_value = NULL;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void iconst_n(u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (*instruction) - 3;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void lconst_n(u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.long_value = (*instruction) - 9;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void fconst_n(u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.float_value = (*instruction) - 11.0;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void dconst_n(u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.double_value = (*instruction) - 14.0;
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void bipush(u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  value.int_value = (int32_t) instruction[1];
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc += 2;
}

void sipush(u1* instruction) {}
void ldc(u1* instruction) {}
void ldc_w(u1* instruction) {}
void ldc_2_w(u1* instruction) {}