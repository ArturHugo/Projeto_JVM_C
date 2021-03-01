#include "attributes.h"
#include "constant-pool.h"

#include <stdio.h>
#include <stdlib.h>

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
}

int main() {
  test_print_constant_value_integer();
  test_print_constant_value_float();
  test_print_constant_value_double();

  return 0;
}
