#include <stdlib.h>
#include <string.h>

#include "frame.h"
#include "global.h"
#include "handlers/comparison.h"

// TODO free nos frames popados da frame stack nas intrucoes de return

void go_to() {
  Frame* current_frame = peekNode(frame_stack);
  u1*    bytecode      = current_frame->current_method->attributes->code_info.code;

  u1      byte1        = bytecode[current_frame->local_pc + 1];
  u1      byte2        = bytecode[current_frame->local_pc + 2];
  int16_t branchOffset = (byte1 << 8) | byte2;

  current_frame->local_pc = current_frame->local_pc + branchOffset;
}

void jsr() {
  Frame* current_frame = peekNode(frame_stack);
  u1*    bytecode      = current_frame->current_method->attributes->code_info.code;

  int8_t   byte1        = bytecode[current_frame->local_pc + 1];
  int8_t   byte2        = bytecode[current_frame->local_pc + 2];
  uint16_t branchOffset = ((int16_t) byte1 << 8) | byte2;
  JavaType return_address;

  return_address.return_address_value = current_frame->local_pc + 3;
  pushValue(&current_frame->operand_stack, return_address);
  current_frame->local_pc = current_frame->local_pc + branchOffset;
}

void ret() {
  Frame* current_frame = peekNode(frame_stack);
  u1*    bytecode      = current_frame->current_method->attributes->code_info.code;
  int8_t index         = bytecode[current_frame->local_pc + 1];

  JavaType value;
  value                   = current_frame->local_variables[index];
  current_frame->local_pc = current_frame->local_pc + value.return_address_value;
}

void ireturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT1;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}
void lreturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT2;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}
void freturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT1;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}
void dreturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT2;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}
void areturn() {
  JavaType value;
  Frame*   current_frame = peekNode(frame_stack);
  popValue(&current_frame->operand_stack, &value);
  value.cat_tag = CAT1;

  popNode(&frame_stack);
  Frame* previous_frame = peekNode(frame_stack);
  pushValue(&previous_frame->operand_stack, value);
}

void return_op() {
  Frame* old_frame = popNode(&frame_stack);

  free(old_frame);
  // free(previous_node);
}