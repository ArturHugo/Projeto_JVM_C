#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

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

#define makeStoreTest(opcode, attribution, index)                                                  \
  Frame*   frame = fixture;                                                                        \
  JavaType value = attribution;                                                                    \
  pushValue(&frame->operand_stack, value);                                                         \
                                                                                                   \
  u1 current_instruction[]               = {opcode, index};                                        \
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];            \
                                                                                                   \
  instruction_handler(current_instruction);

void test_istore(void* fixture) {
  makeStoreTest(0x36, {.int_value = 42}, 0);
  assert_int(42, ==, frame->local_variables[0].int_value);
}

void test_lstore(void* fixture) {
  makeStoreTest(0x37, {.long_value = (42L << 32) + 1}, 0);
  assert_llong((42L << 32) + 1, ==, frame->local_variables[0].long_value);
}

void test_fstore(void* fixture) {
  makeStoreTest(0x38, {.float_value = 0.42f}, 0);
  assert_float(0.42f, ==, frame->local_variables[0].float_value);
}

void test_dstore(void* fixture) {
  makeStoreTest(0x39, {.double_value = 0.42}, 0);
  assert_double(0.42, ==, frame->local_variables[0].double_value);
}

void test_istore_0(void* fixture) {
  makeStoreTest(0x3b, {.int_value = 42}, 0);
  assert_double(42, ==, frame->local_variables[0].int_value);
}

void test_istore_1(void* fixture) {
  makeStoreTest(0x3c, {.int_value = 42}, 1);
  assert_double(42, ==, frame->local_variables[1].int_value);
}

void test_istore_2(void* fixture) {
  makeStoreTest(0x3d, {.int_value = 42}, 2);
  assert_double(42, ==, frame->local_variables[2].int_value);
}

void test_istore_3(void* fixture) {
  makeStoreTest(0x3e, {.int_value = 42}, 3);
  assert_double(42, ==, frame->local_variables[3].int_value);
}

void test_lstore_0(void* fixture) {
  makeStoreTest(0x3f, {.long_value = (42L << 32) + 1}, 0);
  assert_llong((42L << 32) + 1, ==, frame->local_variables[0].long_value);
}

void test_lstore_1(void* fixture) {
  makeStoreTest(0x40, {.long_value = (42L << 32) + 1}, 2);
  assert_llong((42L << 32) + 1, ==, frame->local_variables[2].long_value);
}

void test_lstore_2(void* fixture) {
  makeStoreTest(0x41, {.long_value = (42L << 32) + 1}, 4);
  assert_llong((42L << 32) + 1, ==, frame->local_variables[4].long_value);
}

void test_lstore_3(void* fixture) {
  makeStoreTest(0x42, {.long_value = (42L << 32) + 1}, 6);
  assert_llong((42L << 32) + 1, ==, frame->local_variables[6].long_value);
}

void test_fstore_0(void* fixture) {
  makeStoreTest(0x43, {.float_value = 0.42f}, 0);
  assert_float(0.42f, ==, frame->local_variables[0].float_value);
}

void test_fstore_1(void* fixture) {
  makeStoreTest(0x44, {.float_value = 0.42f}, 0);
  assert_float(0.42f, ==, frame->local_variables[1].float_value);
}

void test_fstore_2(void* fixture) {
  makeStoreTest(0x45, {.float_value = 0.42f}, 0);
  assert_float(0.42f, ==, frame->local_variables[2].float_value);
}

void test_fstore_3(void* fixture) {
  makeStoreTest(0x46, {.float_value = 0.42f}, 0);
  assert_float(0.42f, ==, frame->local_variables[3].float_value);
}

void test_dstore_0(void* fixture) {
  makeStoreTest(0x47, {.double_value = 0.42}, 0);
  assert_double(0.42, ==, frame->local_variables[0].double_value);
}

void test_dstore_1(void* fixture) {
  makeStoreTest(0x48, {.double_value = 0.42}, 0);
  assert_double(0.42, ==, frame->local_variables[2].double_value);
}

void test_dstore_2(void* fixture) {
  makeStoreTest(0x49, {.double_value = 0.42}, 0);
  assert_double(0.42, ==, frame->local_variables[4].double_value);
}

void test_dstore_3(void* fixture) {
  makeStoreTest(0x4a, {.double_value = 0.42}, 0);
  assert_double(0.42, ==, frame->local_variables[6].double_value);
}

void test_astore(void* fixture) {
  Vector* vec = newVector(2);
  makeStoreTest(0x3a, {.reference_value = vec}, 0);
  assert_ptr(vec, ==, frame->local_variables[0].reference_value);
  freeVector(vec);
}

void test_astore_0(void* fixture) {
  Vector* vec = newVector(2);
  makeStoreTest(0x4b, {.reference_value = vec}, 0);
  assert_ptr(vec, ==, frame->local_variables[0].reference_value);
  freeVector(vec);
}

void test_astore_1(void* fixture) {
  Vector* vec = newVector(2);
  makeStoreTest(0x4c, {.reference_value = vec}, 0);
  assert_ptr(vec, ==, frame->local_variables[1].reference_value);
  freeVector(vec);
}

void test_astore_2(void* fixture) {
  Vector* vec = newVector(2);
  makeStoreTest(0x4d, {.reference_value = vec}, 0);
  assert_ptr(vec, ==, frame->local_variables[2].reference_value);
  freeVector(vec);
}

void test_astore_3(void* fixture) {
  Vector* vec = newVector(2);
  makeStoreTest(0x4e, {.reference_value = vec}, 0);
  assert_ptr(vec, ==, frame->local_variables[3].reference_value);
  freeVector(vec);
}

void test_iastore(void* fixture) {
  JavaType* array = munit_newa(JavaType, 2);
  Frame*    frame = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.int_value = 42};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x4f};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_int(42, ==, array[1].int_value);
  free(array);
}

void test_lastore(void* fixture) {
  JavaType* array = munit_newa(JavaType, 2);
  Frame*    frame = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.long_value = (42L << 32)};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x50};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_long(42L << 32, ==, array[1].long_value);
  free(array);
}

void test_fastore(void* fixture) {
  JavaType* array = munit_newa(JavaType, 2);
  Frame*    frame = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.float_value = 0.42f};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x51};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_float(0.42f, ==, array[1].float_value);
  free(array);
}

void test_dastore(void* fixture) {
  JavaType* array = munit_newa(JavaType, 2);
  Frame*    frame = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.double_value = 0.42};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x52};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_double(0.42, ==, array[1].double_value);
  free(array);
}

void test_aastore(void* fixture) {
  JavaType* array  = munit_newa(JavaType, 2);
  Frame*    frame  = fixture;
  Object*   object = munit_new(Object);

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.reference_value = object};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x53};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_ptr(object, ==, array[1].reference_value);
  free(object);
  free(array);
}

void test_bastore(void* fixture) {
  JavaType* array  = munit_newa(JavaType, 2);
  Frame*    frame  = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.byte_value = 42};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x54};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_char(42, ==, array[1].byte_value);
  free(array);
}

void test_castore(void* fixture) {
  JavaType* array  = munit_newa(JavaType, 2);
  Frame*    frame  = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.char_value = 'a'};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x55};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_uint16('a', ==, array[1].char_value);
  free(array);
}

void test_sastore(void* fixture) {
  JavaType* array  = munit_newa(JavaType, 2);
  Frame*    frame  = fixture;

  JavaType arrayref = {.reference_value = array};
  JavaType index    = {.int_value = 1};
  JavaType value    = {.short_value = 42};

  pushValue(&frame->operand_stack, arrayref);
  pushValue(&frame->operand_stack, index);
  pushValue(&frame->operand_stack, value);

  u1 current_instruction[]               = {0x56};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  assert_short(42, ==, array[1].short_value);
  free(array);
}

create_test_with_fixture(test_istore);
create_test_with_fixture(test_lstore);
create_test_with_fixture(test_fstore);
create_test_with_fixture(test_dstore);
create_test_with_fixture(test_astore);
create_test_with_fixture(test_istore_0);
create_test_with_fixture(test_istore_1);
create_test_with_fixture(test_istore_2);
create_test_with_fixture(test_istore_3);
create_test_with_fixture(test_lstore_0);
create_test_with_fixture(test_lstore_1);
create_test_with_fixture(test_lstore_2);
create_test_with_fixture(test_lstore_3);
create_test_with_fixture(test_fstore_0);
create_test_with_fixture(test_fstore_1);
create_test_with_fixture(test_fstore_2);
create_test_with_fixture(test_fstore_3);
create_test_with_fixture(test_dstore_0);
create_test_with_fixture(test_dstore_1);
create_test_with_fixture(test_dstore_2);
create_test_with_fixture(test_dstore_3);
create_test_with_fixture(test_astore_0);
create_test_with_fixture(test_astore_1);
create_test_with_fixture(test_astore_2);
create_test_with_fixture(test_astore_3);
create_test_with_fixture(test_iastore);
create_test_with_fixture(test_lastore);
create_test_with_fixture(test_fastore);
create_test_with_fixture(test_dastore);
create_test_with_fixture(test_aastore);
create_test_with_fixture(test_bastore);
create_test_with_fixture(test_castore);
create_test_with_fixture(test_sastore);

MunitTest tests[] = {
    add_test_with_fixtures(test_istore),
    add_test_with_fixtures(test_lstore),
    add_test_with_fixtures(test_fstore),
    add_test_with_fixtures(test_dstore),
    add_test_with_fixtures(test_istore_0),
    add_test_with_fixtures(test_istore_1),
    add_test_with_fixtures(test_istore_2),
    add_test_with_fixtures(test_istore_3),
    add_test_with_fixtures(test_astore),
    add_test_with_fixtures(test_lstore_0),
    add_test_with_fixtures(test_lstore_1),
    add_test_with_fixtures(test_lstore_2),
    add_test_with_fixtures(test_lstore_3),
    add_test_with_fixtures(test_fstore_0),
    add_test_with_fixtures(test_fstore_1),
    add_test_with_fixtures(test_fstore_2),
    add_test_with_fixtures(test_fstore_3),
    add_test_with_fixtures(test_dstore_0),
    add_test_with_fixtures(test_dstore_1),
    add_test_with_fixtures(test_dstore_2),
    add_test_with_fixtures(test_dstore_3),
    add_test_with_fixtures(test_astore_0),
    add_test_with_fixtures(test_astore_1),
    add_test_with_fixtures(test_astore_2),
    add_test_with_fixtures(test_astore_3),
    add_test_with_fixtures(test_iastore),
    add_test_with_fixtures(test_lastore),
    add_test_with_fixtures(test_fastore),
    add_test_with_fixtures(test_dastore),
    add_test_with_fixtures(test_aastore),
    add_test_with_fixtures(test_bastore),
    add_test_with_fixtures(test_castore),
    add_test_with_fixtures(test_sastore),
};

create_suite("stores", tests);
