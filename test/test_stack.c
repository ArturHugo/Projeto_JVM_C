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
/*
void example(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x00, 0};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[0]      = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);
}*/

void test_pop(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x57};
  JavaType test_variable         = {.int_value = 42};
  pushValue(&(frame->operand_stack), test_variable);
  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);
}

void test_pop2(/*void* fixture*/){};
void test_dup(/*void* fixture*/){};
void test_dup_x1(/*void* fixture*/){};
void test_dup_x2(/*void* fixture*/){};
void test_dup2(/*void* fixture*/){};
void test_dup2_x1(/*void* fixture*/){};
void test_dup2_x2(/*void* fixture*/){};
void test_swap(/*void* fixture*/){};

create_test_with_fixture(test_pop);
create_skip(test_pop2);
create_skip(test_dup);
create_skip(test_dup_x1);
create_skip(test_dup_x2);
create_skip(test_dup2);
create_skip(test_dup2_x1);
create_skip(test_dup2_x2);
create_skip(test_swap);

MunitTest tests[] = {
    add_test_with_fixtures(test_pop),
    add_test(test_pop2),
    add_test(test_dup),
    add_test(test_dup_x1),
    add_test(test_dup_x2),
    add_test(test_dup2),
    add_test(test_dup2_x1),
    add_test(test_dup2_x2),
    add_test(test_swap),
};

create_suite("stack", tests);