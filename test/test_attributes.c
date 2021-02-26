#define MUNIT_ENABLE_ASSERT_ALIASES
#include "munit.h"

#include <stdio.h>

#include "./support/attributes_class.h"
#include "./support/hello_world.h"
#include "attributes.h"
#include "class-file.h"

ClassFile* class_file;
File*      fd;

MunitResult test_read_constant_value_attribute() {
  fd->seek                            = 0x1e8;  // offset till ConstantValue attribute
  AttributeInfo* attributes           = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  attribute            = attributes[0];
  short          constant_value_index = attribute.constant_value_info.constant_value_index;
  short constant_value = class_file->constant_pool[constant_value_index].integer_info.bytes;
  assert_short(42, ==, constant_value);
  free(attributes);
  return MUNIT_OK;
}

MunitResult test_read_code_attribute() {
  unsigned char byte_code[] = {
      0xb2, 0x00, 0x02, 0x2a, 0xb6, 0x00, 0x03, 0xbb, 0x00, 0x04, 0x59,
      0xb7, 0x00, 0x05, 0xbf, 0x4c, 0xbb, 0x00, 0x04, 0x59, 0xb7, 0x00,
      0x05, 0xbf, 0x4d, 0xbb, 0x00, 0x04, 0x59, 0xb7, 0x00, 0x05, 0xbf,
  };

  fd->seek                  = 0x225;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  code       = attributes[0];

  assert_short(2, ==, code.code_info.max_stack);
  assert_short(3, ==, code.code_info.max_locals);
  assert_short(33, ==, code.code_info.code_length);
  assert_short(2, ==, code.code_info.exception_table_length);
  assert_short(2, ==, code.code_info.attributes_count);
  assert_memory_equal(code.code_info.code_length, byte_code, code.code_info.code);
  // TODO: Read LINE_NUMBER_TABLE and STACK_MAP_TABLE
  // TODO: Test exception table

  free(attributes->code_info.code);
  free(attributes->code_info.exception_table);
  free(attributes);

  return MUNIT_OK;
}

MunitResult test_read_exceptions_attribute() {
  fd->seek                  = 0x290;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  exceptions = attributes[0];

  short number_of_exceptions   = exceptions.exceptions_info.number_of_exceptions;
  u2*   exceptions_index_table = exceptions.exceptions_info.exception_index_table;
  short exception_index        = exceptions_index_table[0];

  short name_index     = class_file->constant_pool[exception_index].class_info.name_index;
  char* exception_name = (char*) class_file->constant_pool[name_index].utf8_info.bytes;

  assert_short(1, ==, number_of_exceptions);
  assert_string_equal(exception_name, "java/lang/Exception");

  free(attributes->exceptions_info.exception_index_table);
  free(attributes);

  return MUNIT_OK;
}

MunitResult test_read_inner_classes_attributes() {
  fd->seek                     = 0x2a4;
  AttributeInfo* attributes    = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  inner_classes = attributes[0];

  u2         number_of_classes = inner_classes.inner_classes_info.number_of_classes;
  InnerClass inner_class       = *inner_classes.inner_classes_info.classes;

  short inner_class_index      = inner_class.inner_class_info_index;
  short inner_class_name_index = class_file->constant_pool[inner_class_index].class_info.name_index;
  char* inner_class_name =
      (char*) class_file->constant_pool[inner_class_name_index].utf8_info.bytes;

  assert_short(1, ==, number_of_classes);
  assert_string_equal(inner_class_name, "Attributes$InnerClass");

  free(attributes->inner_classes_info.classes);
  free(attributes);

  return MUNIT_OK;
}

MunitResult test_read_source_file_attribute() {
  fd->seek                         = 418;
  AttributeInfo* attributes        = readAttributes(1, fd, class_file->constant_pool);
  short          source_file_index = attributes[0].source_file_info.sourcefile_index;
  char* source_file_name = (char*) class_file->constant_pool[source_file_index].utf8_info.bytes;
  assert_string_equal(source_file_name, "HelloWorld.java");
  return MUNIT_OK;
}

MunitTest tests[] = {
    {"/constant_value",
     test_read_constant_value_attribute,
     NULL,
     NULL,
     MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/code", test_read_code_attribute, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/exceptions", test_read_exceptions_attribute, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL},
    {"/inner_classes",
     test_read_inner_classes_attributes,
     NULL,
     NULL,
     MUNIT_TEST_OPTION_NONE,
     NULL},
    {"/source_file",
     test_read_source_file_attribute,
     NULL,
     NULL,
     MUNIT_TEST_OPTION_NONE,
     NULL},
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

static const MunitSuite suite = {
    "/attributes",          /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};

int main(int argc, char* argv[]) {
  class_file = malloc(sizeof(*class_file));
  fd         = malloc(sizeof(*fd));

  fd->buffer                = examples_Attributes_class;
  fd->size                  = examples_Attributes_class_len;
  fd->seek                  = 8;
  u2 constant_pool_length   = u2Read(fd);
  class_file->constant_pool = readConstantPool(constant_pool_length, fd);

  return munit_suite_main(&suite, NULL, argc, argv);
}
