#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include "class-file.h"
#include "frame.h"
#include "global.h"
#include "handlers/stores.h"
#include "stack.h"
#include <stdio.h>

MethodArea method_area;
Stack      frame_stack;

void istore_stores_a_value() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(1);
  pushNode(&frame_stack, frame);

  pushValue(&frame->operand_stack, 42);

  u1 operands[] = {0x36, 0};
  istore(operands);

  assert_int(42, ==, frame->local_variables[0]);
}

union pun {
    u4 in [2];
    uint64_t out;
};

void lstore_stores_a_value() {
  frame_stack  = NULL;
  Frame* frame = _newFrame(2);
  pushNode(&frame_stack, frame);

  pushValue(&frame->operand_stack, 0);  /* low bytes */
  pushValue(&frame->operand_stack, 1); /* high bytes */

  u1 operands[] = {0x37, 0};
  istore(operands);

  assert_int(0, ==, frame->local_variables[1]);
  assert_int(1, ==, frame->local_variables[0]);
}

create_test(istore_stores_a_value);
create_test(lstore_stores_a_value);

MunitTest tests[] = {
    add_test(istore_stores_a_value),
    add_test(lstore_stores_a_value),
};

create_suite("stores", tests);
