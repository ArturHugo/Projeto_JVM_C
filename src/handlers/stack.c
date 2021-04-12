#include "handlers/stack.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

//  TODO consertar nome
void pop_instruction(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  popValue(&(current_frame->operand_stack), &value);
  current_frame->local_pc++;
}

void pop2(const u1* instruction) {}
void dup(const u1* instruction) {}
void dup_x1(const u1* instruction) {}
void dup_x2(const u1* instruction) {}
void dup2(const u1* instruction) {}
void dup2_x1(const u1* instruction) {}
void dup2_x2(const u1* instruction) {}
void swap(const u1* instruction) {}