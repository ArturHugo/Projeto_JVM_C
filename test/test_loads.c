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

void tload_pushes_int_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0x15, 0};
  JavaType int_variable          = {.int_value = 42};
  frame->local_variables[0]      = int_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, frame->local_variables[0].int_value);
}

void tload_pushes_long_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0x16, 0};
  JavaType long_variable         = {.long_value = (42L << 32) + 1};
  frame->local_variables[0]      = long_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int64(value->long_value, ==, frame->local_variables[0].long_value);
}

void tload_pushes_float_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0x17, 0};
  JavaType float_variable        = {.float_value = 420.69};
  frame->local_variables[0]      = float_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_float(value->float_value, ==, frame->local_variables[0].float_value);
}

void tload_pushes_double_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1       current_instruction[] = {0x18, 0};
  JavaType double_variable       = {.double_value = 520.69};
  frame->local_variables[0]      = double_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_double(value->double_value, ==, frame->local_variables[0].double_value);
}

void tload_pushes_reference_local_variable_into_stack(void* fixture) {
  Frame* frame = fixture;

  Object dummy_object;

  u1       current_instruction[] = {0x19, 0};
  JavaType reference_variable    = {.reference_value = &dummy_object};
  frame->local_variables[0]      = reference_variable;

  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_ptr(value->reference_value, ==, frame->local_variables[0].reference_value);
}

void iload_n_pushes_int_local_variables_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1  iload_0[]               = {0x1a};
  u1  iload_1[]               = {0x1b};
  u1  iload_2[]               = {0x1c};
  u1  iload_3[]               = {0x1d};
  u1* current_instructions[4] = {iload_0, iload_1, iload_2, iload_3};

  JavaType  int_variable;
  JavaType* value;

  for(int i = 0; i < 4; i++) {
    int_variable.int_value                 = i;
    frame->local_variables[i]              = int_variable;
    void (*instruction_handler)(const u1*) = instructions_handlers[*current_instructions[i]];
    instruction_handler(current_instructions[i]);
    value = (JavaType*) peekNode(frame->operand_stack);
    assert_int32(value->int_value, ==, frame->local_variables[i].int_value);
  }
}

void lload_n_pushes_long_local_variables_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1  lload_0[]               = {0x1e};
  u1  lload_1[]               = {0x1f};
  u1  lload_2[]               = {0x20};
  u1  lload_3[]               = {0x21};
  u1* current_instructions[4] = {lload_0, lload_1, lload_2, lload_3};

  JavaType  long_variable;
  JavaType* value;

  for(int i = 0; i < 4; i++) {
    long_variable.long_value               = (42L << 32) + i;
    frame->local_variables[i]              = long_variable;
    void (*instruction_handler)(const u1*) = instructions_handlers[*current_instructions[i]];
    instruction_handler(current_instructions[i]);
    value = (JavaType*) peekNode(frame->operand_stack);
    assert_int64(value->long_value, ==, frame->local_variables[i].long_value);
  }
}

void fload_n_pushes_float_local_variables_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1  fload_0[]               = {0x22};
  u1  fload_1[]               = {0x23};
  u1  fload_2[]               = {0x24};
  u1  fload_3[]               = {0x25};
  u1* current_instructions[4] = {fload_0, fload_1, fload_2, fload_3};

  JavaType  float_variable;
  JavaType* value;

  for(int i = 0; i < 4; i++) {
    float_variable.float_value             = i + 0.42;
    frame->local_variables[i]              = float_variable;
    void (*instruction_handler)(const u1*) = instructions_handlers[*current_instructions[i]];
    instruction_handler(current_instructions[i]);
    value = (JavaType*) peekNode(frame->operand_stack);
    assert_float(value->float_value, ==, frame->local_variables[i].float_value);
  }
}

void dload_n_pushes_double_local_variables_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1  dload_0[]               = {0x26};
  u1  dload_1[]               = {0x27};
  u1  dload_2[]               = {0x28};
  u1  dload_3[]               = {0x29};
  u1* current_instructions[4] = {dload_0, dload_1, dload_2, dload_3};

  JavaType  double_variable;
  JavaType* value;

  for(int i = 0; i < 4; i++) {
    double_variable.double_value           = i + 0.42;
    frame->local_variables[i]              = double_variable;
    void (*instruction_handler)(const u1*) = instructions_handlers[*current_instructions[i]];
    instruction_handler(current_instructions[i]);
    value = (JavaType*) peekNode(frame->operand_stack);
    assert_double(value->double_value, ==, frame->local_variables[i].double_value);
  }
}

void aload_n_pushes_reference_local_variables_into_stack(void* fixture) {
  Frame* frame = fixture;

  u1  aload_0[]               = {0x2a};
  u1  aload_1[]               = {0x2b};
  u1  aload_2[]               = {0x2c};
  u1  aload_3[]               = {0x2d};
  u1* current_instructions[4] = {aload_0, aload_1, aload_2, aload_3};

  Object  obj1, obj2, obj3, obj4;
  Object* dummy_objects[4] = {&obj1, &obj2, &obj3, &obj4};

  JavaType  reference_variable;
  JavaType* value;

  for(int i = 0; i < 4; i++) {
    reference_variable.reference_value     = &dummy_objects[i];
    frame->local_variables[i]              = reference_variable;
    void (*instruction_handler)(const u1*) = instructions_handlers[*current_instructions[i]];
    instruction_handler(current_instructions[i]);
    value = (JavaType*) peekNode(frame->operand_stack);
    assert_ptr(value->reference_value, ==, frame->local_variables[i].reference_value);
  }
}

void taload_pushes_int_value_at_array_index_into_stack(void* fixture) {
  Frame* frame = fixture;

  JavaType* int_array    = malloc(2 * sizeof(int_array));
  int_array[0].int_value = 13;
  int_array[1].int_value = 42;
  Array array            = {.type = TYPE_INT, .length = 4, .elements = int_array};

  JavaType array_ref   = {.cat_tag = CAT1, .reference_value = &array};
  JavaType array_index = {.cat_tag = CAT1, .int_value = 1};

  pushValue(&frame->operand_stack, array_ref);
  pushValue(&frame->operand_stack, array_index);

  u1 current_instruction[]               = {0x2e};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];
  instruction_handler(current_instruction);

  JavaType* value = (JavaType*) peekNode(frame->operand_stack);
  assert_int32(value->int_value, ==, array.elements[array_index.int_value].int_value);
}

create_test_with_fixture(tload_pushes_int_local_variable_into_stack);
create_test_with_fixture(tload_pushes_long_local_variable_into_stack);
create_test_with_fixture(tload_pushes_float_local_variable_into_stack);
create_test_with_fixture(tload_pushes_double_local_variable_into_stack);
create_test_with_fixture(tload_pushes_reference_local_variable_into_stack);
create_test_with_fixture(iload_n_pushes_int_local_variables_into_stack);
create_test_with_fixture(lload_n_pushes_long_local_variables_into_stack);
create_test_with_fixture(fload_n_pushes_float_local_variables_into_stack);
create_test_with_fixture(dload_n_pushes_double_local_variables_into_stack);
create_test_with_fixture(aload_n_pushes_reference_local_variables_into_stack);

MunitTest tests[] = {
    add_test_with_fixtures(tload_pushes_int_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_long_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_float_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_double_local_variable_into_stack),
    add_test_with_fixtures(tload_pushes_reference_local_variable_into_stack),
    add_test_with_fixtures(iload_n_pushes_int_local_variables_into_stack),
    add_test_with_fixtures(lload_n_pushes_long_local_variables_into_stack),
    add_test_with_fixtures(fload_n_pushes_float_local_variables_into_stack),
    add_test_with_fixtures(dload_n_pushes_double_local_variables_into_stack),
    add_test_with_fixtures(aload_n_pushes_reference_local_variables_into_stack),
};

create_suite("loads", tests);
