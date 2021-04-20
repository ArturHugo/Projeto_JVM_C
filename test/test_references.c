#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>
#include <stdlib.h>

#include "execution-engine.h"
#include "frame.h"
#include "global.h"
#include "stack.h"

MethodArea method_area;
Stack      frame_stack;

static void* setup() {
  frame_stack  = NULL;
  Frame* frame = malloc(sizeof(*frame));

  frame->operand_stack   = NULL;
  frame->local_pc        = 0;
  frame->local_variables = malloc(4 * sizeof(JavaType));

  pushNode(&frame_stack, frame);
  return frame;
}

static void teardown() {
  Frame* frame = popNode(&frame_stack);
  free(frame);
}

void test_invokestatic(/*void* fixture*/) {
  /*Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0xb8, 0};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[0]      = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);*/
}

void test_new(/*void* fixture*/) {}
void test_newarray(/*void* fixture*/) {}
void test_anewarray(/*void* fixture*/) {}
void test_arraylength(/*void* fixture*/) {}

create_skip(test_invokestatic);
create_skip(test_new);
create_skip(test_newarray);
create_skip(test_anewarray);
create_skip(test_arraylength);

MunitTest tests[] = {
    add_test(test_invokestatic),
    add_test(test_new),
    add_test(test_newarray),
    add_test(test_anewarray),
    add_test(test_arraylength),
};

create_suite("stack", tests);