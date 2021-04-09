#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>
#include <stdlib.h>

#include "frame.h"
#include "global.h"
#include "stack.h"
#include "execution-engine.h"

MethodArea method_area;
Stack      frame_stack;

static void* setup() {
  frame_stack  = NULL;
  Frame* frame = malloc(sizeof(*frame));

  frame->operand_stack  = NULL;
  frame->local_pc       = 0;
  frame->local_variables = malloc(2 * sizeof(u4));

  pushNode(&frame_stack, frame);
  return frame;
}

static void teardown() {
  Frame* frame = popNode(&frame_stack);
  free(frame);
}

void test_istore(void *fixture) {
  Frame* frame = fixture;
  pushValue(&frame->operand_stack, 42);

  u1 current_instruction[] = {0x36, 0};
  void (*instruction_handler)(const u1*)        = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_int(42, ==, frame->local_variables[0]);
}

void test_lstore() {}
void test_fstore() {}
void test_dstore() {}
void test_astore() {}
void test_istore_0() {}
void test_istore_1() {}
void test_istore_2() {}
void test_istore_3() {}
void test_lstore_0() {}
void test_lstore_1() {}
void test_lstore_2() {}
void test_lstore_3() {}
void test_fstore_0() {}
void test_fstore_1() {}
void test_fstore_2() {}
void test_fstore_3() {}
void test_dstore_0() {}
void test_dstore_1() {}
void test_dstore_2() {}
void test_dstore_3() {}
void test_astore_0() {}
void test_astore_1() {}
void test_astore_2() {}
void test_astore_3() {}
void test_iastore() {}
void test_lastore() {}
void test_fastore() {}
void test_dastore() {}
void test_aastore() {}
void test_bastore() {}
void test_castore() {}
void test_sastore() {}

create_test_with_fixture(test_istore);
create_skip(test_lstore);
create_skip(test_fstore);
create_skip(test_istore_0);
create_skip(test_istore_1);
create_skip(test_istore_2);
create_skip(test_istore_3);
create_skip(test_lstore_0);
create_skip(test_lstore_1);
create_skip(test_lstore_2);
create_skip(test_lstore_3);
create_skip(test_fstore_0);
create_skip(test_fstore_1);
create_skip(test_fstore_2);
create_skip(test_fstore_3);
create_skip(test_dstore_0);
create_skip(test_dstore_1);
create_skip(test_dstore_2);
create_skip(test_dstore_3);
create_skip(test_astore_0);
create_skip(test_astore_1);
create_skip(test_astore_2);
create_skip(test_astore_3);
create_skip(test_iastore);
create_skip(test_lastore);
create_skip(test_fastore);
create_skip(test_dastore);
create_skip(test_aastore);
create_skip(test_bastore);
create_skip(test_castore);
create_skip(test_sastore);

MunitTest tests[] = {
    add_test_with_fixtures(test_istore),
    add_test(test_lstore),
    add_test(test_fstore),
    add_test(test_istore_0),
    add_test(test_istore_1),
    add_test(test_istore_2),
    add_test(test_istore_3),
    add_test(test_lstore_0),
    add_test(test_lstore_1),
    add_test(test_lstore_2),
    add_test(test_lstore_3),
    add_test(test_fstore_0),
    add_test(test_fstore_1),
    add_test(test_fstore_2),
    add_test(test_fstore_3),
    add_test(test_dstore_0),
    add_test(test_dstore_1),
    add_test(test_dstore_2),
    add_test(test_dstore_3),
    add_test(test_astore_0),
    add_test(test_astore_1),
    add_test(test_astore_2),
    add_test(test_astore_3),
    add_test(test_iastore),
    add_test(test_lastore),
    add_test(test_fastore),
    add_test(test_dastore),
    add_test(test_aastore),
    add_test(test_bastore),
    add_test(test_castore),
    add_test(test_sastore),
};

create_suite("stores", tests);
