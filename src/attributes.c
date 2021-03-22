#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "constant-pool.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AttributeTypeTable {
  const char*   key;
  AttributeType value;
} attribute_type_table[] = {{"ConstantValue", CONSTANT_VALUE},
                            {"Code", CODE},
                            {"Exceptions", EXCEPTIONS},
                            {"InnerClasses", INNER_CLASSES},
                            {"SourceFile", SOURCE_FILE},
                            {"LineNumberTable", LINE_NUMBER_TABLE},
                            {"LocalVariableTable", LOCAL_VARIABLE_TABLE},
                            {"StackMapTable", STACK_MAP_TABLE},
                            {NULL, UNKNOWN_ATTRIBUTE}};

AttributeType getAttributeType(const char* type) {
  struct AttributeTypeTable* table = attribute_type_table;
  while(table->key != NULL && strcmp(table->key, type))
    ++table;
  return table->value;
}

AttributeInfo* readAttributes(u2 attributes_count, File* fd, ConstantPoolInfo* cp) {
  AttributeInfo* attributes = malloc((attributes_count) * sizeof(*attributes));

  AttributeInfo* attribute;
  for(attribute = attributes; attribute < attributes + attributes_count; attribute++) {
    attribute->attribute_name_index = u2Read(fd);
    attribute->attribute_length     = u4Read(fd);

    // TODO: check if index is on range
    ConstantPoolInfo attribute_name_reference = cp[attribute->attribute_name_index];
    attribute->_attribute_name                = (char*) attribute_name_reference.utf8_info.bytes;
    attribute->_attribute_type = getAttributeType((char*) attribute->_attribute_name);

    switch(attribute->_attribute_type) {
      case CONSTANT_VALUE:
        attribute->constant_value_info.constant_value_index = u2Read(fd);
        break;
      case CODE:
        attribute->code_info.max_stack  = u2Read(fd);
        attribute->code_info.max_locals = u2Read(fd);

        // Read code
        attribute->code_info.code_length = u4Read(fd);
        u1* code                         = malloc(attribute->code_info.code_length * sizeof(u1));
        attribute->code_info.code        = code;

        for(; code < attribute->code_info.code_length + attribute->code_info.code; code++)
          *code = u1Read(fd);

        attribute->code_info._instructions_count =
            nInstructions(attribute->code_info.code, attribute->code_info.code_length);

        attribute->code_info._instructions =
            readInstructions(attribute->code_info.code, attribute->code_info._instructions_count);

        // Read exception_table
        attribute->code_info.exception_table_length = u2Read(fd);
        ExceptionTable* exception_table =
            malloc(attribute->code_info.exception_table_length * sizeof(ExceptionTable));
        attribute->code_info.exception_table = exception_table;
        for(; exception_table <
              attribute->code_info.exception_table_length + attribute->code_info.exception_table;
            exception_table++) {
          exception_table->start_pc   = u2Read(fd);
          exception_table->end_pc     = u2Read(fd);
          exception_table->handler_pc = u2Read(fd);
          exception_table->catch_type = u2Read(fd);
        }

        // Read code attributes
        attribute->code_info.attributes_count = u2Read(fd);
        attribute->code_info.atttributes =
            readAttributes(attribute->code_info.attributes_count, fd, cp);

        break;
      case EXCEPTIONS:;
        attribute->exceptions_info.number_of_exceptions = u2Read(fd);
        u2* exception =
            malloc(attribute->exceptions_info.number_of_exceptions * sizeof(*exception));
        attribute->exceptions_info.exception_index_table = exception;

        for(; exception < attribute->exceptions_info.exception_index_table +
                              attribute->exceptions_info.number_of_exceptions;
            exception++) {
          *exception = u2Read(fd);
        }

        break;
      case INNER_CLASSES:;
        u2 number_of_classes                            = u2Read(fd);
        attribute->inner_classes_info.number_of_classes = number_of_classes;

        InnerClass* classes = malloc(number_of_classes * sizeof(*classes));

        InnerClass* current_class = classes;
        while(number_of_classes--) {
          current_class->inner_class_info_index   = u2Read(fd);
          current_class->outer_class_info_index   = u2Read(fd);
          current_class->inner_name_index         = u2Read(fd);
          current_class->inner_class_access_flags = u2Read(fd);
          current_class++;
        }

        attribute->inner_classes_info.classes = classes;

        break;
      case SOURCE_FILE:
        attribute->source_file_info.sourcefile_index = u2Read(fd);
        break;
      case LINE_NUMBER_TABLE:;
        u2 line_number_table_length                                = u2Read(fd);
        attribute->line_number_table_info.line_number_table_length = line_number_table_length;

        LineNumber* line_number_table =
            malloc(line_number_table_length * sizeof(*line_number_table));
        LineNumber* current_line_number = line_number_table;
        while(line_number_table_length--) {
          current_line_number->start_pc    = u2Read(fd);
          current_line_number->line_number = u2Read(fd);
          current_line_number++;
        }

        attribute->line_number_table_info.line_number_table = line_number_table;
        break;
      case LOCAL_VARIABLE_TABLE:
      case STACK_MAP_TABLE:
      case UNKNOWN_ATTRIBUTE:
        // Silently ignore unkown attributes
        fd->seek += attribute->attribute_length;
        break;
    }
  }

  return attributes;
}

void printAttributes(u2 attributes_count, AttributeInfo* attributes, ConstantPoolInfo* cp) {
  for(int i = 0; i < attributes_count; i++) {
    AttributeInfo attribute = attributes[i];

    printf("[%d] %s\n", i, attribute._attribute_name);
    println("Generic info -------------------------------------------------------------------");
    println();

    println("Attribute name index:\tcp_info #%d <%s>",
            attribute.attribute_name_index,
            attribute._attribute_name);
    printf("Attribute length:\t%d\n", attribute.attribute_length);
    println();

    println("Specific info ------------------------------------------------------------------");
    println();

    switch(attribute._attribute_type) {
      case CONSTANT_VALUE:
        printf("Constant value index: cp_info #%d ",
               attribute.constant_value_info.constant_value_index);
        printConstantValue(cp, attribute.constant_value_info.constant_value_index);
        println();
        break;

      case CODE:
        println("Misc ---------------------------------------------------------------------------");
        println();
        println("Maximum stack size:\t\t%d", attribute.code_info.max_stack);
        println("Maximum local variables:\t%d", attribute.code_info.max_locals);
        println("Code length:\t\t\t%d", attribute.code_info.code_length);
        printInstructions(attribute.code_info._instructions,
                          attribute.code_info._instructions_count,
                          cp);
        break;

      case EXCEPTIONS:
        println("Nr.\tException\tVerbose");
        for(int e = 0; e < attribute.exceptions_info.number_of_exceptions; e++) {
          u2 current_exception_index    = attribute.exceptions_info.exception_index_table[e];
          unsigned char* exception_name = getUtf8String(cp, current_exception_index);
          println("%d\tcp_info #%d\t%s", e, current_exception_index, exception_name);
        }
        break;

      case INNER_CLASSES:
        println("Nr.\tInner Class\t\tOuter Class\tInner Name\tAccess Flags");
        for(int index = 0; index < attribute.inner_classes_info.number_of_classes; index++) {
          InnerClass current_inner_class = attribute.inner_classes_info.classes[index];

          u1* inner_class_info = getUtf8String(cp, current_inner_class.inner_class_info_index);
          u1* outer_class_info = getUtf8String(cp, current_inner_class.outer_class_info_index);
          u1* inner_class_name = getUtf8String(cp, current_inner_class.inner_name_index);
          u2  access_flags     = current_inner_class.inner_class_access_flags;

          // TODO: add verbosity to access_flags
          println("%d\tcp_info #%d\t\tcp_info #%d\tcp_info#%d\t0x%04x []",
                  index,
                  current_inner_class.inner_class_info_index,
                  current_inner_class.outer_class_info_index,
                  current_inner_class.inner_name_index,
                  access_flags);

          println("\t%s\t%s\t%s\t", inner_class_info, outer_class_info, inner_class_name);
        }
        break;

      case SOURCE_FILE:;
        u2  index            = attribute.source_file_info.sourcefile_index;
        u1* source_file_name = getUtf8String(cp, index);
        println("Source File name index: cp_info #%d <%s>", index, source_file_name);
        break;

      case LINE_NUMBER_TABLE:
        println("Nr.\tStart PC\tLine Number");
        u2 line_number_table_length = attribute.line_number_table_info.line_number_table_length;
        for(int index = 0; index < line_number_table_length; index++) {
          LineNumber current_line = attribute.line_number_table_info.line_number_table[index];
          u2         start_pc     = current_line.start_pc;
          u2         line_number  = current_line.line_number;
          println("%d\t%d\t\t%d", index, start_pc, line_number);
        }
        break;

      default:
        printf("NOT IMPLEMENTED");
        break;
    }

    println();
  }
}
