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
  frame->local_variables = malloc(257 * sizeof(JavaType));

  method_area.loaded_classes = newMap();
  loadObjectClass();
  loadClass("multi.class");

  ClassFile* test_class = mapGet(method_area.loaded_classes, "multi");
  frame->constant_pool  = test_class->constant_pool;

  pushNode(&frame_stack, frame);
  return frame;
}

static void teardown() {
  Frame* frame = popNode(&frame_stack);
  free(frame);
}

void wide_tload_pushes_int_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0xc4, 0x15, 1, 0};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[256]    = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[256].int_value);
}

void wide_tstore_pops_int_value_from_operand_stack_into_local_variables(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 42};
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0xc4, 0x36, 1, 0};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_int32(42, ==, frame->local_variables[256].int_value);
}

void wide_ret_updates_local_pc_value(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[]   = {0xc4, 0xa9, 1, 0};
  JavaType return_address_variable = {.return_address_value = 42};
  frame->local_variables[256]      = return_address_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint32(frame->local_pc, ==, frame->local_variables[256].return_address_value);
}

void wide_iinc_increments_int_local_variable(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0xc4, 0x84, 1, 0, 0xFF, 0xFF};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[256]    = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_int32(frame->local_variables[256].int_value, ==, 41);
}

void multianewarray_creates_instance_of_multiarray(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0xc5, 0, 2, 2};
  JavaType count1                = {.int_value = 3};
  JavaType count2                = {.int_value = 2};

  pushValue(&frame->operand_stack, count1);
  pushValue(&frame->operand_stack, count2);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* multiarray_ref = peekNode(frame->operand_stack);
  Array*    multiarray     = (Array*) (multiarray_ref->reference_value);
  Array*    subarray       = (Array*) (multiarray->elements[0].reference_value);

  assert_int32(multiarray->length, ==, 3);
  assert_int32(subarray->length, ==, 2);
}

void ifnull_branches_if_reference_is_null(void* fixture) {
  Frame* frame = fixture;

  u1 current_instruction[] = {0xc6, 1, 1};

  JavaType reference = {.reference_value = NULL};
  pushValue(&frame->operand_stack, reference);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint32(frame->local_pc, ==, (1 << 8) | 1);
}

void ifnull_does_not_branch_if_reference_is_not_null(void* fixture) {
  Frame* frame = fixture;

  u1 current_instruction[] = {0xc6, 1, 1};

  Object   obj;
  JavaType reference = {.reference_value = &obj};
  pushValue(&frame->operand_stack, reference);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint32(frame->local_pc, ==, 3);
}

void ifnonnull_branches_if_reference_is_not_null(void* fixture) {
  Frame* frame = fixture;

  u1 current_instruction[] = {0xc7, 1, 1};

  JavaType reference = {.reference_value = NULL};
  pushValue(&frame->operand_stack, reference);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint32(frame->local_pc, ==, 3);
}

void ifnonnull_does_not_branch_if_reference_is_null(void* fixture) {
  Frame* frame = fixture;

  u1 current_instruction[] = {0xc7, 1, 1};

  Object   obj;
  JavaType reference = {.reference_value = &obj};
  pushValue(&frame->operand_stack, reference);

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint32(frame->local_pc, ==, (1 << 8) | 1);
}

void goto_w_branches(void* fixture) {
  Frame* frame = fixture;

  u1 current_instruction[] = {0xc8, 1, 0, 0, 0};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint32(frame->local_pc, ==, (1 << 24));
}

void jsr_w_branches_and_pushes_return_address_into_operand_stack(void* fixture) {
  Frame* frame = fixture;

  u1 current_instruction[] = {0xc9, 1, 0, 0, 0};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* return_address = peekNode(frame->operand_stack);

  assert_uint32(return_address->return_address_value, ==, 1);
  assert_uint32(frame->local_pc, ==, (1 << 24));
}

create_test_with_fixture(wide_tload_pushes_int_local_variable_into_stack);
create_test_with_fixture(wide_tstore_pops_int_value_from_operand_stack_into_local_variables);
create_test_with_fixture(wide_ret_updates_local_pc_value);
create_test_with_fixture(wide_iinc_increments_int_local_variable);
create_test_with_fixture(multianewarray_creates_instance_of_multiarray);
create_test_with_fixture(ifnull_branches_if_reference_is_null);
create_test_with_fixture(ifnull_does_not_branch_if_reference_is_not_null);
create_test_with_fixture(ifnonnull_branches_if_reference_is_not_null);
create_test_with_fixture(ifnonnull_does_not_branch_if_reference_is_null);
create_test_with_fixture(goto_w_branches);
create_test_with_fixture(jsr_w_branches_and_pushes_return_address_into_operand_stack);

MunitTest tests[] = {
    add_test_with_fixtures(wide_tload_pushes_int_local_variable_into_stack),
    add_test_with_fixtures(wide_tstore_pops_int_value_from_operand_stack_into_local_variables),
    add_test_with_fixtures(wide_ret_updates_local_pc_value),
    add_test_with_fixtures(wide_iinc_increments_int_local_variable),
    add_test_with_fixtures(multianewarray_creates_instance_of_multiarray),
    add_test_with_fixtures(ifnull_branches_if_reference_is_null),
    add_test_with_fixtures(ifnull_does_not_branch_if_reference_is_not_null),
    add_test_with_fixtures(ifnonnull_branches_if_reference_is_not_null),
    add_test_with_fixtures(ifnonnull_does_not_branch_if_reference_is_null),
    add_test_with_fixtures(goto_w_branches),
    add_test_with_fixtures(jsr_w_branches_and_pushes_return_address_into_operand_stack),
};

create_suite("extended", tests);
