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
  JavaType test_variable         = {.int_value = 42, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);
  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);
}

void test_pop2_cat1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x58};
  JavaType test_variable         = {.int_value = 42, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);
  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);
  test_variable.int_value = 192;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);
}

void test_pop2_cat2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x58};
  JavaType test_variable         = {.int_value = 42, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.long_value = 1;
  test_variable.cat_tag    = CAT2;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);
}

void test_dup(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x59};
  JavaType test_variable         = {.int_value = 42, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);
}

void test_dup_x1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x5a};

  JavaType test_variable = {.int_value = 42, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 42);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

void test_dup_x2_cat1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x5b};

  JavaType test_variable = {.int_value = 3, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 2;
  test_variable.cat_tag   = CAT1;
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  test_variable.cat_tag   = CAT1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 3);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

void test_dup_x2_cat2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x5b};

  JavaType test_variable = {.int_value = 2, .cat_tag = CAT2};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  test_variable.cat_tag   = CAT1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

void test_dup2_cat1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5c};
  JavaType test_variable         = {.int_value = 2, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);
}

void test_dup2_cat2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5c};
  JavaType test_variable         = {.long_value = 42, .cat_tag = CAT2};
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_long(test_variable.int_value, ==, 42);

  popValue(&(frame->operand_stack), &test_variable);
  assert_long(test_variable.int_value, ==, 42);
}

void test_dup2_x1_cat1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5d};
  JavaType test_variable         = {.int_value = 3, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 2;
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 3);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);
}
void test_dup2_x1_cat2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5d};
  JavaType test_variable         = {.int_value = 2, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  test_variable.cat_tag   = CAT2;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

void test_dup2_x2_form1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5e};
  JavaType test_variable         = {.int_value = 4, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 3;
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 2;
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 3);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 4);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);
}

void test_dup2_x2_form2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5e};
  JavaType test_variable         = {.int_value = 3, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 2;
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  test_variable.cat_tag   = CAT2;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 3);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

void test_dup2_x2_form3(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5e};
  JavaType test_variable         = {.int_value = 3, .cat_tag = CAT2};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.cat_tag   = CAT1;
  test_variable.int_value = 2;
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 3);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);
}

void test_dup2_x2_form4(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5e};
  JavaType test_variable         = {.int_value = 2, .cat_tag = CAT2};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

void test_swap(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0x5f};
  JavaType test_variable         = {.int_value = 2, .cat_tag = CAT1};
  pushValue(&(frame->operand_stack), test_variable);

  test_variable.int_value = 1;
  pushValue(&(frame->operand_stack), test_variable);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 2);

  popValue(&(frame->operand_stack), &test_variable);
  assert_int32(test_variable.int_value, ==, 1);
}

create_test_with_fixture(test_pop);
create_test_with_fixture(test_pop2_cat1);
create_test_with_fixture(test_pop2_cat2);
create_test_with_fixture(test_dup);
create_test_with_fixture(test_dup_x1);
create_test_with_fixture(test_dup_x2_cat1);
create_test_with_fixture(test_dup_x2_cat2);
create_test_with_fixture(test_dup2_cat1);
create_test_with_fixture(test_dup2_cat2);
create_test_with_fixture(test_dup2_x1_cat1);
create_test_with_fixture(test_dup2_x1_cat2);
create_test_with_fixture(test_dup2_x2_form1);
create_test_with_fixture(test_dup2_x2_form2);
create_test_with_fixture(test_dup2_x2_form3);
create_test_with_fixture(test_dup2_x2_form4);
create_test_with_fixture(test_swap);

MunitTest tests[] = {
    add_test_with_fixtures(test_pop),
    add_test_with_fixtures(test_pop2_cat1),
    add_test_with_fixtures(test_pop2_cat2),
    add_test_with_fixtures(test_dup),
    add_test_with_fixtures(test_dup_x1),
    add_test_with_fixtures(test_dup_x2_cat1),
    add_test_with_fixtures(test_dup_x2_cat2),
    add_test_with_fixtures(test_dup2_cat1),
    add_test_with_fixtures(test_dup2_cat2),
    add_test_with_fixtures(test_dup2_x1_cat1),
    add_test_with_fixtures(test_dup2_x1_cat2),
    add_test_with_fixtures(test_dup2_x2_form1),
    add_test_with_fixtures(test_dup2_x2_form2),
    add_test_with_fixtures(test_dup2_x2_form3),
    add_test_with_fixtures(test_dup2_x2_form4),
    add_test_with_fixtures(test_swap),
};

create_suite("stack", tests);