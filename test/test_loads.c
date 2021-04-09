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
  int_variable.type         = INT_TYPE;
  int_variable.int_value    = 42;
  frame->local_variables[0] = int_variable;

  iload(operands);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);
}

// void lload_pushes_large_local_variable_into_stack() {
//   frame_stack  = NULL;
//   Frame* frame = _newFrame(2);
//   pushNode(&frame_stack, frame);

//   u1       operands[] = {21, 0};
//   JavaType local_variable;
//   local_variable.cat_tag = CAT1;

//   frame->local_variables[0] = 42;

//   iload(operands);

//   JavaType* value = (JavaType*) peekNode(frame->operand_stack);
//   assert_int((int32_t) value->low_bytes, ==, frame->local_variables[0]);
// }

create_test(iload_pushes_int_local_variable_into_stack);

MunitTest tests[] = {add_test(iload_pushes_int_local_variable_into_stack)};

create_suite("loads", tests);
