#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>

#include "class-file.h"
#include "frame.h"
#include "global.h"
#include "handlers/loads.h"
#include "stack.h"

MethodArea method_area;
Stack      frame_stack;

void iload_pushes_int_local_variable_into_stack() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(1);
  pushNode(&frame_stack, frame);

  u1       operands[] = {21, 0};
  JavaType int_variable;
  int_variable.int_value    = 42;
  frame->local_variables[0] = int_variable;

  iload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);
}

void lload_pushes_long_local_variable_into_stack() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  u1       operands[] = {22, 0};
  JavaType local_variable;
  local_variable.long_value = 42;
  frame->local_variables[0] = local_variable;

  lload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int64(value->long_value, ==, frame->local_variables[0].long_value);
}

void fload_pushes_float_local_variable_into_stack() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  u1       operands[] = {24, 0};
  JavaType local_variable;
  local_variable.float_value = 420.69;
  frame->local_variables[0]  = local_variable;

  fload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_float(value->float_value, ==, frame->local_variables[0].float_value);
}

void dload_pushes_double_local_variable_into_stack() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  u1       operands[] = {25, 0};
  JavaType local_variable;
  local_variable.double_value = 420.69;
  frame->local_variables[0]   = local_variable;

  dload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_double(value->double_value, ==, frame->local_variables[0].double_value);
}

void aload_pushes_reference_local_variable_into_stack() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  Object dummy_object;

  u1       operands[] = {26, 0};
  JavaType local_variable;
  local_variable.reference_value = &dummy_object;
  frame->local_variables[0]      = local_variable;

  aload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_ptr(value->reference_value, ==, frame->local_variables[0].reference_value);
}

create_test(iload_pushes_int_local_variable_into_stack);
create_test(lload_pushes_long_local_variable_into_stack);
create_test(fload_pushes_float_local_variable_into_stack);
create_test(dload_pushes_double_local_variable_into_stack);
create_test(aload_pushes_reference_local_variable_into_stack);

MunitTest tests[] = {
    add_test(iload_pushes_int_local_variable_into_stack),
    add_test(lload_pushes_long_local_variable_into_stack),
    add_test(fload_pushes_float_local_variable_into_stack),
    add_test(dload_pushes_double_local_variable_into_stack),
    add_test(aload_pushes_reference_local_variable_into_stack),
};

create_suite("loads", tests);
