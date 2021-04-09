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

void tload_pushes_int_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x15, 0};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[0]      = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);
}

void tload_pushes_long_local_variable_into_stack(void* fixture) {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  u1       operands[] = {22, 0};
  JavaType local_variable;
  local_variable.long_value = 42;
  frame->local_variables[0] = local_variable;

  tload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int64(value->long_value, ==, frame->local_variables[0].long_value);
}

void tload_pushes_float_local_variable_into_stack(void* fixture) {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  u1       operands[] = {24, 0};
  JavaType local_variable;
  local_variable.float_value = 420.69;
  frame->local_variables[0]  = local_variable;

  tload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_float(value->float_value, ==, frame->local_variables[0].float_value);
}

void tload_pushes_double_local_variable_into_stack(void* fixture) {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  u1       operands[] = {25, 0};
  JavaType local_variable;
  local_variable.double_value = 420.69;
  frame->local_variables[0]   = local_variable;

  tload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_double(value->double_value, ==, frame->local_variables[0].double_value);
}

void tload_pushes_reference_local_variable_into_stack(void* fixture) {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  Object dummy_object;

  u1       operands[] = {26, 0};
  JavaType local_variable;
  local_variable.reference_value = &dummy_object;
  frame->local_variables[0]      = local_variable;

  tload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_ptr(value->reference_value, ==, frame->local_variables[0].reference_value);
}

void iload_n_pushes_int_local_variables_into_stack(void* fixture) {
  frame_stack  = NULL;
  Frame* frame = _newFrame(1);
  pushNode(&frame_stack, frame);

  u1  iload_0[]   = {26};
  u1  iload_1[]   = {27};
  u1  iload_2[]   = {28};
  u1  iload_3[]   = {29};
  u1* operands[4] = {iload_0, iload_1, iload_2, iload_3};

  JavaType  int_variable;
  JavaType* value;

  for(int i = 0; i < 4; i++) {
    int_variable.int_value    = i;
    frame->local_variables[i] = int_variable;
    iload_n(operands[i]);
    value = (JavaType*) peekNode(frame->operand_stack);
    assert_int32(value->int_value, ==, frame->local_variables[i].int_value);
  }
}

create_test_with_fixture(tload_pushes_int_local_variable_into_stack);
create_test_with_fixture(tload_pushes_long_local_variable_into_stack);
create_test_with_fixture(tload_pushes_float_local_variable_into_stack);
create_test_with_fixture(tload_pushes_double_local_variable_into_stack);
create_test_with_fixture(tload_pushes_reference_local_variable_into_stack);
create_test_with_fixture(iload_n_pushes_int_local_variables_into_stack);

MunitTest tests[] = {
    add_test_with_fixtures(tload_pushes_int_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_long_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_float_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_double_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_reference_local_variable_into_stack),
    add_test_with_fixtures(iload_n_pushes_int_local_variables_into_stack),
};

create_suite("loads", tests);
