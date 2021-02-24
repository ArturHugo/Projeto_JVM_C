#include "unity.h"
#include <stdio.h>

#include "./support/attributes_class.h"
#include "./support/hello_world.h"
#include "attributes.h"
#include "class-file.h"

ClassFile* class_file;
File*      fd;

void setUp(void) {
  class_file = malloc(sizeof(ClassFile));
  fd         = malloc(sizeof(*fd));

  fd->buffer                 = examples_Attributes_class;
  fd->size                   = examples_Attributes_class_len;
  fd->seek                   = 8;
  short constant_pool_length = u2Read(fd);
  class_file->constant_pool  = readConstantPool(constant_pool_length, fd);
}

void tearDown(void) {
  free(fd);
  free(class_file);
}

void test_read_constant_value_attribute(void) {
  fd->seek                            = 0x1e8;  // offset till ConstantValue attribute
  AttributeInfo* attributes           = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  attribute            = attributes[0];
  short          constant_value_index = attribute.constant_value_info.constant_value_index;
  short constant_value = class_file->constant_pool[constant_value_index].integer_info.bytes;
  TEST_ASSERT_EQUAL(42, constant_value);
}

void test_read_code_attribute(void) {
  fd->seek                  = 0x225;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  code       = attributes[0];

  TEST_ASSERT_EQUAL(2, code.code_info.max_stack);
  TEST_ASSERT_EQUAL(3, code.code_info.max_locals);
  TEST_ASSERT_EQUAL(33, code.code_info.code_length);
  TEST_ASSERT_EQUAL(2, code.code_info.exception_table_length);
  TEST_ASSERT_EQUAL(2, code.code_info.attributes_count);

  unsigned char byte_code[] = {
      0xb2, 0x00, 0x02, 0x2a, 0xb6, 0x00, 0x03, 0xbb, 0x00, 0x04, 0x59,
      0xb7, 0x00, 0x05, 0xbf, 0x4c, 0xbb, 0x00, 0x04, 0x59, 0xb7, 0x00,
      0x05, 0xbf, 0x4d, 0xbb, 0x00, 0x04, 0x59, 0xb7, 0x00, 0x05, 0xbf,
  };

  TEST_ASSERT_EQUAL_UINT8_ARRAY(byte_code, code.code_info.code, code.code_info.code_length);
  // TODO: Read LINE_NUMBER_TABLE and STACK_MAP_TABLE
}

void test_read_exceptions_attribute(void) {
  fd->seek                  = 0x290;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool);
  AttributeInfo  exceptions = attributes[0];

  short number_of_exceptions = exceptions.exceptions_info.number_of_exceptions;
  u2* exceptions_index_table = exceptions.exceptions_info.exception_index_table;
  short exception_index = exceptions_index_table[0];

  short name_index = class_file->constant_pool[exception_index].class_info.name_index;
  unsigned char* exception_name = class_file->constant_pool[name_index].utf8_info.bytes;

  TEST_ASSERT_EQUAL(1, number_of_exceptions);
  TEST_ASSERT_EQUAL_STRING("java/lang/Exception", exception_name);
}

/* void test_read_source_file_attribute(void) {*/
  /* fd->seek = 418; */
  /* AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool); */
  /* short source_file_index = attributes[0].source_file_info.sourcefile_index; */
  /* char* source_file_name = (char *) class_file->constant_pool[source_file_index].utf8_info.bytes;
   */
  /* TEST_ASSERT_EQUAL_STRING("HelloWorld.java", source_file_name); */
/* } */
