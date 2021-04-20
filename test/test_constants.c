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

  /*frame->operand_stack   = NULL;
  frame->local_pc        = 0;
  frame->local_variables = malloc(4 * sizeof(JavaType));*/

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

void test_nop(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x00};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_int32(frame->local_pc, ==, 1);
}

void test_aconst_null(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x01};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_ptr(value->reference_value, ==, NULL);
}

void test_iconst_ml(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x02};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, -1);
}

void test_iconst_0(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x03};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, 0);
}

void test_iconst_1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x04};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, 1);
}

void test_iconst_2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x05};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, 2);
}

void test_iconst_3(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x06};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, 3);
}

void test_iconst_4(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x07};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, 4);
}

void test_iconst_5(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x08};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, 5);
}

void test_lconst_0(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x09};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_long(value->long_value, ==, 0);
}

void test_lconst_1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x0a};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_long(value->long_value, ==, 1);
}

void test_fconst_0(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x0b};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_float(value->float_value, ==, 0.0);
}

void test_fconst_1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x0c};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_float(value->float_value, ==, 1.0);
}

void test_fconst_2(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x0d};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_float(value->float_value, ==, 2.0);
}

void test_dconst_0(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x0e};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_double(value->double_value, ==, 0.0);
}

void test_dconst_1(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x0f};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_double(value->double_value, ==, 1.0);
}

void test_bipush(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x10, -1};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);

  assert_int32(value->int_value, ==, -1);
}

void test_sipush(void* fixture) {
  Frame* frame = fixture;
  pushNode(&frame_stack, frame);

  u1 current_instruction[] = {0x11, 0xFF, 0xFE};

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);

  assert_int32(value->int_value, ==, -2);
}

void test_ldc(/*void* fixture*/){

};
void test_ldc_w(/*void* fixture*/){};
void test_ldc_2_w(/*void* fixture*/){};

create_test_with_fixture(test_nop);
create_test_with_fixture(test_aconst_null);
create_test_with_fixture(test_iconst_ml);
create_test_with_fixture(test_iconst_0);
create_test_with_fixture(test_iconst_1);
create_test_with_fixture(test_iconst_2);
create_test_with_fixture(test_iconst_3);
create_test_with_fixture(test_iconst_4);
create_test_with_fixture(test_iconst_5);
create_test_with_fixture(test_lconst_0);
create_test_with_fixture(test_lconst_1);
create_test_with_fixture(test_fconst_0);
create_test_with_fixture(test_fconst_1);
create_test_with_fixture(test_fconst_2);
create_test_with_fixture(test_dconst_0);
create_test_with_fixture(test_dconst_1);
create_test_with_fixture(test_bipush);
create_test_with_fixture(test_sipush);
create_skip(test_ldc);
create_skip(test_ldc_w);
create_skip(test_ldc_2_w);

MunitTest tests[] = {
    add_test_with_fixtures(test_nop),
    add_test_with_fixtures(test_aconst_null),
    add_test_with_fixtures(test_iconst_ml),
    add_test_with_fixtures(test_iconst_0),
    add_test_with_fixtures(test_iconst_1),
    add_test_with_fixtures(test_iconst_2),
    add_test_with_fixtures(test_iconst_3),
    add_test_with_fixtures(test_iconst_4),
    add_test_with_fixtures(test_iconst_5),
    add_test_with_fixtures(test_lconst_0),
    add_test_with_fixtures(test_lconst_1),
    add_test_with_fixtures(test_fconst_0),
    add_test_with_fixtures(test_fconst_1),
    add_test_with_fixtures(test_fconst_2),
    add_test_with_fixtures(test_dconst_0),
    add_test_with_fixtures(test_dconst_1),
    add_test_with_fixtures(test_bipush),
    add_test_with_fixtures(test_sipush),
    add_test(test_ldc),
    add_test(test_ldc_w),
    add_test(test_ldc_2_w),
};

create_suite("constants", tests);