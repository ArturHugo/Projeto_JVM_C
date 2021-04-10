#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "execution-engine.h"
#include "frame.h"
#include "global.h"
#include "method-area.h"
#include "stack.h"
#include "vector.h"

MethodArea method_area;
Stack      frame_stack;

static void* setup() {
  frame_stack  = NULL;
  Frame* frame = malloc(sizeof(*frame));

  frame->operand_stack   = NULL;
  frame->local_pc        = 0;
  frame->local_variables = malloc(8 * sizeof(JavaType));

  pushNode(&frame_stack, frame);
  return frame;
}

static void teardown() {
  Frame* frame = popNode(&frame_stack);
  free(frame);
}

static void runInstruction(u1 opcode) {
  u1 current_instruction[] = {
      opcode,
  };
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);
}

void i2l(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 42};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x85);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(42L, ==, newValue->long_value);
}

void i2f(void* fixture) {
  Frame* frame = fixture;
  // an integer value that will lose it's precision when converted
  JavaType value = {.int_value = 33554435};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x86);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_float(33554436.0f, ==, newValue->float_value);
}

void i2d(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 33554435};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x87);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_double(33554435.0, ==, newValue->double_value);
}

void l2i(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.long_value = (42L << 32) + 1};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x88);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(1, ==, newValue->int_value);
}

void l2f(void* fixture) {
  Frame* frame = fixture;
  // a long value that will lose it's precision when converted
  JavaType value = {.long_value = 33554435};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x89);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_float(33554436.0f, ==, newValue->float_value);
}

void l2d(void* fixture) {
  Frame* frame = fixture;
  // a long value that will lose it's precision when converted
  JavaType value = {.long_value = 9007199254740992L};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8a);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_double(9007199254740993.0, ==, newValue->double_value);
}

void f2i_round(void *fixture) {
  Frame* frame = fixture;
  JavaType value = {.float_value = 42.5};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(42, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void f2i_NaN(void *fixture) {
  Frame* frame = fixture;
  JavaType value = {.int_value = /* NaN */ 0x7FFFF3FF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(0, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void f2i_inf(void *fixture) {
  Frame* frame = fixture;
  JavaType value = {.int_value = 0x7F800000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(INT32_MAX, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void f2i_neg_inf(void *fixture) {
  Frame* frame = fixture;
  JavaType value = {.int_value = 0xFF800000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(INT32_MIN, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

create_test_with_fixture(i2l);
create_test_with_fixture(i2f);
create_test_with_fixture(i2d);
create_test_with_fixture(l2i);
create_test_with_fixture(l2f);
create_test_with_fixture(l2d);

create_test_with_fixture(f2i_round);
create_test_with_fixture(f2i_NaN);
create_test_with_fixture(f2i_inf);
create_test_with_fixture(f2i_neg_inf);

MunitTest tests[] = {
    add_test_with_fixtures(i2l),
    add_test_with_fixtures(i2f),
    add_test_with_fixtures(i2d),
    add_test_with_fixtures(l2i),
    add_test_with_fixtures(l2f),
    add_test_with_fixtures(l2d),

    add_test_with_fixtures(f2i_round),
    add_test_with_fixtures(f2i_NaN),
    add_test_with_fixtures(f2i_inf),
    add_test_with_fixtures(f2i_neg_inf),
};

create_suite("conversions", tests);
