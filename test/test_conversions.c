#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "execution-engine.h"
#include "frame.h"
#include "global.h"
#include "method-area.h"
#include "stack.h"
#include "vector.h"

MethodArea method_area;
Stack      frame_stack;

// TODO: test edge cases for d2f?? 🤔🤔

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

void test_i2l(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 42};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x85);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(42L, ==, newValue->long_value);
}

void test_i2f(void* fixture) {
  Frame* frame = fixture;
  // an integer value that will lose it's precision when converted
  JavaType value = {.int_value = 33554435};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x86);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_float(33554436.0f, ==, newValue->float_value);
}

void test_i2d(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 33554435};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x87);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_double(33554435.0, ==, newValue->double_value);
}

void test_l2i(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.long_value = (42L << 32) + 1};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x88);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(1, ==, newValue->int_value);
}

void test_l2f(void* fixture) {
  Frame* frame = fixture;
  // a long value that will lose it's precision when converted
  JavaType value = {.long_value = 33554435};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x89);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_float(33554436.0f, ==, newValue->float_value);
}

void test_l2d(void* fixture) {
  Frame* frame = fixture;
  // a long value that will lose it's precision when converted
  JavaType value = {.long_value = 9007199254740992L};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8a);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_double(9007199254740993.0, ==, newValue->double_value);
}

void test_f2i_round(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.float_value = 42.5};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(42, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_f2i_NaN(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = /* NaN */ 0x7FFFF3FF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(0, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_f2i_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 0x7F800000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(INT32_MAX, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_f2i_neg_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 0xFF800000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8b);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(INT32_MIN, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_f2l_round(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.float_value = 42.5};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8c);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(42L, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_f2l_NaN(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = /* NaN */ 0x7FFFF3FF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8c);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(0L, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_f2l_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 0x7F800000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8c);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(INT64_MAX, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_f2l_neg_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 0xFF800000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8c);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(INT64_MIN, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_f2d(void* fixture) {
  Frame* frame = fixture;
  JavaType value = {.float_value = 42.5f};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8d);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_double(42.5, ==, newValue->double_value);
}

void test_d2i_round(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.double_value = 42.5};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8e);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(42, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_d2i_NaN(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = /* NaN */ 0x7FFFF3FF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8e);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(0, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_d2i_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.long_value = 0x7FF0000000000000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8e);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(INT32_MAX, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_d2i_neg_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.long_value = 0xFFF0000000000000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8e);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(INT32_MIN, ==, newValue->int_value);
  free(popNode(&frame->operand_stack));
}

void test_d2l_round(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.double_value = 42.5};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8f);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(42L, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_d2l_NaN(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = /* NaN */ 0x7FFFF3FF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8f);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(0L, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_d2l_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.long_value = 0x7FF0000000000000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8f);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(INT64_MAX, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_d2l_neg_inf(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.long_value = 0xFFF0000000000000};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x8f);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_llong(INT64_MIN, ==, newValue->long_value);
  free(popNode(&frame->operand_stack));
}

void test_d2f(void* fixture) {
  Frame* frame = fixture;
  JavaType value = {.double_value = 42.5};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x90);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_float(42.5f, ==, newValue->float_value);
}

void test_i2b(void* fixture) {
  Frame* frame = fixture;
  JavaType value = {.int_value = 0x0FF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x91);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(-1, ==, newValue->int_value);
}

void test_i2c(void* fixture) {
  Frame* frame = fixture;
  JavaType value = {.int_value = 0xF000000F};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x92);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(0x0000000F, ==, newValue->int_value);
}

void test_i2s(void* fixture) {
  Frame* frame = fixture;
  JavaType value = {.int_value = 0x0FFFF};
  pushValue(&frame->operand_stack, value);

  runInstruction(0x93);

  JavaType* newValue = peekNode(frame->operand_stack);
  assert_int(-1, ==, newValue->int_value);
}

create_test_with_fixture(test_i2l);
create_test_with_fixture(test_i2f);
create_test_with_fixture(test_i2d);
create_test_with_fixture(test_l2i);
create_test_with_fixture(test_l2f);
create_test_with_fixture(test_l2d);

create_test_with_fixture(test_f2i_round);
create_test_with_fixture(test_f2i_NaN);
create_test_with_fixture(test_f2i_inf);
create_test_with_fixture(test_f2i_neg_inf);

create_test_with_fixture(test_f2l_round);
create_test_with_fixture(test_f2l_NaN);
create_test_with_fixture(test_f2l_inf);
create_test_with_fixture(test_f2l_neg_inf);

create_test_with_fixture(test_f2d);

create_test_with_fixture(test_d2i_round);
create_test_with_fixture(test_d2i_NaN);
create_test_with_fixture(test_d2i_inf);
create_test_with_fixture(test_d2i_neg_inf);

create_test_with_fixture(test_d2l_round);
create_test_with_fixture(test_d2l_NaN);
create_test_with_fixture(test_d2l_inf);
create_test_with_fixture(test_d2l_neg_inf);

create_test_with_fixture(test_d2f);
create_test_with_fixture(test_i2b);
create_test_with_fixture(test_i2c);
create_test_with_fixture(test_i2s);

MunitTest tests[] = {
    add_test_with_fixtures(test_i2l),
    add_test_with_fixtures(test_i2f),
    add_test_with_fixtures(test_i2d),
    add_test_with_fixtures(test_l2i),
    add_test_with_fixtures(test_l2f),
    add_test_with_fixtures(test_l2d),

    add_test_with_fixtures(test_f2i_round),
    add_test_with_fixtures(test_f2i_NaN),
    add_test_with_fixtures(test_f2i_inf),
    add_test_with_fixtures(test_f2i_neg_inf),

    add_test_with_fixtures(test_f2l_round),
    add_test_with_fixtures(test_f2l_NaN),
    add_test_with_fixtures(test_f2l_inf),
    add_test_with_fixtures(test_f2l_neg_inf),

    add_test_with_fixtures(test_f2d),

    add_test_with_fixtures(test_d2i_round),
    add_test_with_fixtures(test_d2i_NaN),
    add_test_with_fixtures(test_d2i_inf),
    add_test_with_fixtures(test_d2i_neg_inf),

    add_test_with_fixtures(test_d2l_round),
    add_test_with_fixtures(test_d2l_NaN),
    add_test_with_fixtures(test_d2l_inf),
    add_test_with_fixtures(test_d2l_neg_inf),

    add_test_with_fixtures(test_d2f),
    add_test_with_fixtures(test_i2b),
    add_test_with_fixtures(test_i2c),
    add_test_with_fixtures(test_i2s),
};

create_suite("conversions", tests);
