#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#include "common.h"
#include "constant-pool.h"
#include <stdio.h>

// Attribute info structs
typedef struct {
  u2 constant_value_index;
} ConstantValueInfo;

typedef struct {
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} ExceptionTable;

typedef struct {
  u2                    max_stack;
  u2                    max_locals;
  u4                    code_length;
  u1*                   code;
  u2                    exception_table_length;
  ExceptionTable*       exception_table;
  u2                    attributes_count;
  struct AttributeInfo* atttributes;
} CodeInfo;

typedef struct {
  u2  number_of_exceptions;
  u2* exception_index_table;
} ExceptionsInfo;

typedef struct {
  u2 inner_class_info_index;
  u2 outer_class_info_index;
  u2 inner_name_index;
  u2 inner_class_access_flags;
} InnerClass;

typedef struct {
  u2          number_of_classes;
  InnerClass* classes;
} InnerClassesInfo;

typedef struct {
  u2 sourcefile_index;
} SourceFileInfo;

typedef struct {
  u2 start_pc;
  u2 line_number;
} LineNumber;

typedef struct {
  u2          line_number_table_length;
  LineNumber* line_number_table;
} LineNumberTableInfo;

typedef struct {
  u2 local_variable_table_length;
  struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
  } * local_variable_table;  // FIXME? noem ficou meio estranho2
} LocalVariableTableInfo;

// AttributeInfo struct
typedef struct AttributeInfo {
  u2 attribute_name_index;
  u4 attribute_length;
  union {
    ConstantValueInfo      constant_value_info;
    CodeInfo               code_info;
    ExceptionsInfo         exceptions_info;
    InnerClassesInfo       inner_classes_info;
    SourceFileInfo         source_file_info;
    LineNumberTableInfo    line_number_table_info;
    LocalVariableTableInfo local_variable_table_info;
  };
} AttributeInfo;

AttributeInfo* readAttributes(u2 attributes_count, File* fd, ConstantPoolInfo* cp);

#endif  // __ATTRIBUTES_H
