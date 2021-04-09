#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>
#include "handlers/stores.h"
#include "frame.h"
#include "class-file.h"
#include "stack.h"
#include "global.h"

MethodArea method_area;
Stack      frame_stack;

void istore_stores_a_value() {
  frame_stack = NULL;
  Frame* frame= _newFrame(1);
  pushNode(&frame_stack, frame);

  pushValue(&frame->operand_stack, 42);

  u1 operands[] = { 0 };
  istore(operands);

  assert_int(42, ==, frame->local_variables[0]);
}

create_test(istore_stores_a_value);


MunitTest tests[] = {
  add_test(istore_stores_a_value),
};

create_suite("stores", tests);
