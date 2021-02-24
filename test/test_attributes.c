#include <stdio.h>
#include "unity.h"

#include "./support/hello_world.h"
#include "attributes.h"
#include "class-file.h"

ClassFile* class_file;
File* fd;

void setUp(void) {
  class_file = malloc(sizeof(ClassFile));
  fd = malloc(sizeof(*fd));

  fd->buffer = examples_HelloWorld_class;
  fd->size = examples_HelloWorld_class_len;

  class_file->magic = u4Read(fd);
  fd->seek = 10;

  class_file->constant_pool = readConstantPool(29, fd);
}

void tearDown(void) {
  free(fd);
  free(class_file);
}

void test_read_constant_value_attribute(void) {
  // TODO: testar constant value
}

void test_read_source_file_attribute(void) {
  fd->seek = 418;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool); 
  short source_file_index = attributes[0].source_file_info.sourcefile_index;
  char* source_file_name = (char *) class_file->constant_pool[source_file_index].utf8_info.bytes;
  TEST_ASSERT_EQUAL_STRING("HelloWorld.java", source_file_name);
}

void test_read_code_attribute(void) {
  fd->seek = 0x175;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool); 
  AttributeInfo code = attributes[0];
  
  TEST_ASSERT_EQUAL(2, code.code_info.max_stack);
  TEST_ASSERT_EQUAL(1, code.code_info.max_locals);
  TEST_ASSERT_EQUAL(9, code.code_info.code_length);
  TEST_ASSERT_EQUAL(0, code.code_info.exception_table_length);
  TEST_ASSERT_EQUAL(1, code.code_info.attributes_count);

  unsigned char byte_code[] = { 0xb2, 0x00, 0x02, 0x12, 0x03, 0xb6, 0x00, 0x04, 0xb1};
  TEST_ASSERT_EQUAL_UINT8_ARRAY(byte_code, code.code_info.code, code.code_info.code_length);
}
