#include "map.h"
#include "methods.h"
#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit/munit.h"
#include "support/test_macros.h"

#include <stdio.h>
#include <stdlib.h>

#include "class-file.h"
#include "file.h"
#include "support/example_class.h"
#include "vector.h"
#include "method-area.h"
#include "stack.h"

MethodArea method_area;
Stack      frame_stack;


void it_initializes_a_class() {
  frame_stack = NULL;
  method_area.loaded_classes = newMap();
  loadObjectClass();

  File*      fd         = malloc(sizeof(*fd));

  fd->buffer = Example_class;
  fd->size   = Example_class_len;
  fd->seek   = 0;

  ClassFile* class_file = readClassFile(fd);
  resolveReferences(class_file);
  initializeClass(class_file);

  MethodInfo* main_method = mapGet(class_file->_method_map, "main");
  assert_ptr_not_null(main_method);

  MethodInfo* init_method = mapGet(class_file->_method_map, "<init>");
  assert_ptr_not_null(init_method);

  MethodInfo* random_method = mapGet(class_file->_method_map, "random");
  assert_null(random_method);

  FieldInfo* integer_field = mapGet(class_file->_field_map, "integer");
  assert_ptr_not_null(integer_field);

  FieldInfo* number_field = mapGet(class_file->_field_map, "number");
  assert_int16(number_field->access_flags, ==, 0x08);
}

create_test(it_initializes_a_class);

MunitTest tests[] = {
    add_test(it_initializes_a_class),
};

create_suite("jvm", tests);
