#include "handlers/stack.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

void pop_instruction(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;
  popValue(&(current_frame->operand_stack), &value);

  if(value.cat_tag == CAT2) {
    printf("\npc = %d: pop called with cat2 value in stack\n", current_frame->local_pc);
    exit(1);
  }

  current_frame->local_pc++;
}

void pop2(const u1* instruction) {
  Frame*   current_frame = peekNode(frame_stack);
  JavaType value;

  popValue(&(current_frame->operand_stack), &value);

  if(value.cat_tag == CAT1) {
    popValue(&(current_frame->operand_stack), &value);
    if(value.cat_tag == CAT2) {
      printf("\npc = %d: Inconsistency detected on opperand stack, read jvms8.pdf page 549\n pop2 "
             "called "
             "with stack = ...,cat2,cat1\n");
      exit(1);
    }
  }
  current_frame->local_pc++;
}

void dup_instruction(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType value;
  popValue(&(current_frame->operand_stack), &value);

  if(value.cat_tag == CAT2) {
    printf("\npc = %d: dup called with cat2 value in stack\n", current_frame->local_pc);
    exit(1);
  }
  pushValue(&(current_frame->operand_stack), value);
  pushValue(&(current_frame->operand_stack), value);
  current_frame->local_pc++;
}

void dup_x1(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType value1, value2;
  popValue(&(current_frame->operand_stack), &value1);
  popValue(&(current_frame->operand_stack), &value2);

  if(value1.cat_tag == CAT2 || value2.cat_tag == CAT2) {
    printf("\npc = %d: dup_x1 called with cat2 value in stack\n", current_frame->local_pc);
    exit(1);
  }

  pushValue(&(current_frame->operand_stack), value1);
  pushValue(&(current_frame->operand_stack), value2);
  pushValue(&(current_frame->operand_stack), value1);
  current_frame->local_pc++;
}

void dup_x2(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType value1, value2, value3;

  popValue(&(current_frame->operand_stack), &value1);
  if(value1.cat_tag == CAT2) {
    printf("\npc = %d: dup_x2 called with invalid cat2 value in stack\n", current_frame->local_pc);
    exit(1);
  }

  popValue(&(current_frame->operand_stack), &value2);

  if(value2.cat_tag == CAT1) {
    popValue(&(current_frame->operand_stack), &value3);
    if(value3.cat_tag == CAT2) {
      printf("\npc = %d: dup_x2 called with invalid cat2 value in stack\n",
             current_frame->local_pc);
      exit(1);
    }
  }

  pushValue(&(current_frame->operand_stack), value1);
  if(value2.cat_tag == CAT1)
    pushValue(&(current_frame->operand_stack), value3);
  pushValue(&(current_frame->operand_stack), value2);
  pushValue(&(current_frame->operand_stack), value1);

  current_frame->local_pc++;
}

void dup2_instruction(const u1* instruction) {
  Frame* current_frame = peekNode(frame_stack);

  JavaType value1, value2;

  popValue(&(current_frame->operand_stack), &value1);

  if(value1.cat_tag == CAT1) {
    popValue(&(current_frame->operand_stack), &value2);
    if(value2.cat_tag == CAT2) {
      printf("\npc = %d: dup2 called with invalid cat2 value in stack\n", current_frame->local_pc);
      exit(1);
    }
  }

  if(value1.cat_tag == CAT1)
    pushValue(&(current_frame->operand_stack), value2);
  pushValue(&(current_frame->operand_stack), value1);
  if(value1.cat_tag == CAT1)
    pushValue(&(current_frame->operand_stack), value2);
  pushValue(&(current_frame->operand_stack), value1);

  current_frame->local_pc++;
}

void dup2_x1(const u1* instruction) {}
void dup2_x2(const u1* instruction) {}
void swap(const u1* instruction) {}