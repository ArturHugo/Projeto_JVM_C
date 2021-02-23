#include "attributes.h"
#include "class-file.h"
#include <stdio.h>
#include <string.h>

// Attribute types for string comparisson
static const char CONSTANT_VALUE[]       = "ConstantValue";
static const char CODE[]                 = "Code";
static const char EXCEPTIONS[]           = "Exceptions";
static const char INNER_CLASSES[]        = "InnerClasses";
static const char SOURCE_FILE[]          = "SourceFile";
static const char LINE_NUMBER_TABLE[]    = "LineNumberTable";
static const char LOCAL_VARIABLE_TABLE[] = "LocalVariableTable";

AttributeInfo* readAttributes(u2 attributes_count, FILE* fd) {
  AttributeInfo* attributes = malloc((attributes_count) * sizeof(*attributes));

  AttributeInfo* attribute;
  for(attribute = attributes; attribute < attributes + attributes_count; attribute++) {
    attribute->attribute_name_index = u2Read(fd);
    attribute->attribute_length     = u4Read(fd);

    // TODO: Follow recursively
    ConstantPoolInfo attribute_name_reference = class_file.constant_pool[attribute->attribute_name_index];

    u1* attribute_name      = attribute_name_reference.utf8_info.bytes;
    u2  attribute_name_size = attribute_name_reference.utf8_info.length;

    // TODO: Substituir memcmp por strcmp e adicionar nullbyte ao
    // final dos bytes do CONSTANT_UTF8_info
    if(!memcmp(attribute_name, CONSTANT_VALUE, attribute_name_size)) {
      attribute->constant_value_info.constant_value_index = u2Read(fd);
    } else if(!memcmp(attribute_name, CODE, attribute_name_size)) {
      attribute->code_info.max_stack  = u2Read(fd);
      attribute->code_info.max_locals = u2Read(fd);

      // Read code
      attribute->code_info.code_length = u4Read(fd);
      u1* code                         = malloc(attribute->code_info.code_length * sizeof(u1));
      attribute->code_info.code        = code;

      for(; code < attribute->code_info.code_length + attribute->code_info.code; code++)
        *code = u1Read(fd);

      // Read exception_table
      attribute->code_info.exception_table_length = u2Read(fd);
      ExceptionTable* exception_table = malloc(attribute->code_info.exception_table_length * sizeof(ExceptionTable));
      attribute->code_info.exception_table = exception_table;
      for(; exception_table < attribute->code_info.exception_table_length + attribute->code_info.exception_table;
          exception_table++) {
        exception_table->start_pc   = u2Read(fd);
        exception_table->end_pc     = u2Read(fd);
        exception_table->handler_pc = u2Read(fd);
        exception_table->catch_type = u2Read(fd);
      }

      // Read code attributes (recusive)
      attribute->code_info.attributes_count = u2Read(fd);
      attribute->code_info.atttributes      = readAttributes(attribute->code_info.attributes_count, fd);

    } else if(!memcmp(attribute_name, EXCEPTIONS, attribute_name_size)) {
      attribute->exceptions_info.number_of_exceptions = u2Read(fd);
      u2* exception = malloc(attribute->exceptions_info.number_of_exceptions * sizeof(*exception));
      attribute->exceptions_info.exception_index_table = exception;

      for(; exception <
            attribute->exceptions_info.exception_index_table + attribute->exceptions_info.number_of_exceptions;
          exception++) {
        *exception = u2Read(fd);
      }

    } else if(!memcmp(attribute_name, INNER_CLASSES, attribute_name_size)) {
      // TODO: handle InnerClassesInfo
    } else if(!memcmp(attribute_name, SOURCE_FILE, attribute_name_size)) {
      // TODO: handle SourceFileInfo
    } else if(!memcmp(attribute_name, LINE_NUMBER_TABLE, attribute_name_size)) {
      // TODO: handle LineNumberTableInfo
    } else if(!memcmp(attribute_name, LOCAL_VARIABLE_TABLE, attribute_name_size)) {
      // TODO: handle LocalVariableTableInfo
    } else {
      exit(1);
    }
  }

  return attributes;
}
