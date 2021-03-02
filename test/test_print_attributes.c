#include "attributes.h"
#include "class-file.h"
#include "constant-pool.h"

#include "support/attributes_class.h"

#include <stdio.h>
#include <stdlib.h>

ClassFile* class_file;
File*      fd;

void test_print_constant_value_integer() {
  printf("\n\ntest int\n\n");

  ConstantPoolInfo* cp   = malloc(sizeof(*cp));
  cp->tag                = CONSTANT_INTEGER;
  cp->integer_info.bytes = 42;

  AttributeInfo* attribute                            = malloc(sizeof(*attribute));
  attribute->_attribute_type                          = CONSTANT_VALUE;
  attribute->_attribute_name                          = NULL;
  attribute->constant_value_info.constant_value_index = 0;

  printAttributes(1, attribute, cp);
  free(cp);
  free(attribute);
}

void test_print_constant_value_float() {
  printf("\n\ntest float\n\n");

  ConstantPoolInfo* cp  = malloc(sizeof(*cp));
  cp->tag               = CONSTANT_FLOAT;
  cp->float_info._value = 42.0f;

  AttributeInfo* attribute                            = malloc(sizeof(*attribute));
  attribute->_attribute_type                          = CONSTANT_VALUE;
  attribute->_attribute_name                          = NULL;
  attribute->constant_value_info.constant_value_index = 0;

  printAttributes(1, attribute, cp);
  free(cp);
  free(attribute);
}

void test_print_constant_value_double() {
  printf("\n\ntest double\n\n");

  ConstantPoolInfo* cp   = malloc(sizeof(*cp));
  cp->tag                = CONSTANT_DOUBLE;
  cp->double_info._value = 42.0;

  AttributeInfo* attribute                            = malloc(sizeof(*attribute));
  attribute->_attribute_type                          = CONSTANT_VALUE;
  attribute->_attribute_name                          = NULL;
  attribute->constant_value_info.constant_value_index = 0;

  printAttributes(1, attribute, cp);
  free(cp);
  free(attribute);
}

void test_print_from_read(int start_position) {
  printf("\n\n");

  fd->seek                  = start_position;
  AttributeInfo* attributes = readAttributes(1, fd, class_file->constant_pool);
  printAttributes(1, attributes, class_file->constant_pool);

  free(attributes);
}

int main() {
  class_file = malloc(sizeof(*class_file));
  fd         = malloc(sizeof(*fd));

  fd->buffer                = examples_Attributes_class;
  fd->size                  = examples_Attributes_class_len;
  fd->seek                  = 8;
  u2 constant_pool_length   = u2Read(fd);
  class_file->constant_pool = readConstantPool(constant_pool_length, fd);

  test_print_constant_value_integer();
  test_print_constant_value_float();
  test_print_constant_value_double();

  test_print_from_read(0x290);
  test_print_from_read(0x2a4);
  test_print_from_read(0x268);

  return 0;
}
