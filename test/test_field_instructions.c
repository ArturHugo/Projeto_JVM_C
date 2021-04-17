#include "map.h"
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
#include "support/example_class.h"
#include "vector.h"

MethodArea method_area;
Stack      frame_stack;

// TODO: test edge cases for d2f?? 🤔🤔

static void* setup() {
  frame_stack                = NULL;
  method_area.loaded_classes = newMap();

  File* fd = malloc(sizeof(*fd));

  fd->buffer = Example_class;
  fd->size   = Example_class_len;
  fd->seek   = 0;

  ClassFile* class_file = readClassFile(fd);
  mapAdd(method_area.loaded_classes, "Example", class_file);
  resolveReferences(class_file);
  initializeClass(class_file);

  Frame* frame = newFrame(class_file, "main");

  pushNode(&frame_stack, frame);
  return frame;
}

static void teardown() {
  Frame* frame = popNode(&frame_stack);
  free(frame->local_variables);
  free(frame);
}

static void runInstruction(u1 opcode, u2 index) {
  u1 current_instruction[]               = {opcode, index >> 8, index};
  void (*instruction_handler)(const u1*) = instructions_handlers[*current_instruction];

  instruction_handler(current_instruction);
}

void test_static(void* fixture) {
  Frame*   frame = fixture;
  JavaType value = {.int_value = 42};
  pushValue(&frame->operand_stack, value);

  runInstruction(0xb3, 16);

  JavaType* top = peekNode(frame->operand_stack);
  assert_null(top);

  runInstruction(0xb2, 16);

  top = peekNode(frame->operand_stack);
  assert_int(42, ==, top->int_value);
}

void test_field(void* fixture) {
  Frame* frame = fixture;

  Object* object = malloc(sizeof(*object));
  object->fields_and_values = newMap();
  mapAdd(object->fields_and_values, "integer", malloc(sizeof(JavaType)));

  JavaType objectref = { .reference_value = object};
  pushValue(&frame->operand_stack, objectref);
  JavaType value = {.int_value = 42};
  pushValue(&frame->operand_stack, value);

  // no example, 26 é um fieldref para o field integer
  runInstruction(0xb5, 26);

  pushValue(&frame->operand_stack, objectref);

  runInstruction(0xb4, 26);

  JavaType* top = peekNode(frame->operand_stack);
  assert_int(42, ==, top->int_value);
}

create_test_with_fixture(test_static);
create_test_with_fixture(test_field);

MunitTest tests[] = {
    add_test_with_fixtures(test_static),
    add_test_with_fixtures(test_field),
};

create_suite("field_instructions", tests);
