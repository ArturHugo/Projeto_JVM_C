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

void test_invokestatic(/*void* fixture*/) {
  /*Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1       current_instruction[] = {0xb8, 0};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[0]      = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);*/
}

void test_new(/*void* fixture*/) {}

void test_newarray(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  // creating long array
  u1 current_instruction[] = {0xbc, 0x0b};

  JavaType count = {.cat_tag = CAT1, .int_value = 6};
  pushValue(&frame->operand_stack, count);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_ptr(value->reference_value, !=, NULL);

  Array*  array     = value->reference_value;
  int64_t longValue = array->elements->long_value;

  assert_long(longValue, ==, 0);
}

void test_anewarray(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  // creating long array
  u1 current_instruction[] = {0xbd, 0x0b, 0x0b};

  JavaType count = {.cat_tag = CAT1, .int_value = 6};
  pushValue(&frame->operand_stack, count);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_ptr(value->reference_value, !=, NULL);

  Array* array    = value->reference_value;
  void*  refValue = array->elements->reference_value;

  assert_ptr(refValue, ==, NULL);
}
void test_arraylength(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  // creating long array
  u1 current_instruction[] = {0xbc, 0x0b};

  JavaType count = {.cat_tag = CAT1, .int_value = 6};
  pushValue(&frame->operand_stack, count);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  u1 current_instruction_2[] = {0xbe};

  void (*instruction_handler_2)(const u1*) = instructions_handlers[*current_instruction_2];

  instruction_handler_2(current_instruction_2);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);

  assert_int(value->int_value, ==, 6);
}

create_skip(test_invokestatic);
create_skip(test_new);
create_test_with_fixture(test_newarray);
create_test_with_fixture(test_anewarray);
create_test_with_fixture(test_arraylength);

MunitTest tests[] = {
    add_test(test_invokestatic),
    add_test(test_new),
    add_test_with_fixtures(test_newarray),
    add_test_with_fixtures(test_anewarray),
    add_test_with_fixtures(test_arraylength),
};

create_suite("stack", tests);