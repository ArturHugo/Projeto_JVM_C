#ifndef __ATTRIBUTES_H
#define __ATTRIBUTES_H

#include "common.h"
#include "constant-pool.h"
#include "instructions.h"

/**
 * @file attributes.h
 * @brief Structures and functions concerning class file attributes.
 */

/// Supported attribute types
typedef enum {
  CONSTANT_VALUE,
  CODE,
  EXCEPTIONS,
  INNER_CLASSES,
  SOURCE_FILE,
  LINE_NUMBER_TABLE,
  LOCAL_VARIABLE_TABLE,
  STACK_MAP_TABLE,
  UNKNOWN_ATTRIBUTE
} AttributeType;

typedef struct {
  u2 start_pc;
  u2 end_pc;
  u2 handler_pc;
  u2 catch_type;
} ExceptionTable;

typedef struct {
  u2 start_pc;
  u2 line_number;
} LineNumber;

typedef struct {
  u2 inner_class_info_index;
  u2 outer_class_info_index;
  u2 inner_name_index;
  u2 inner_class_access_flags;
} InnerClass;

/** @name Attribute Info structures */

///@{
typedef struct {
  /// Index in the constant pool to a Constant Value
  u2 constant_value_index;
} ConstantValueInfo;

typedef struct {
  /// Maximum stack size
  u2 max_stack;
  /// Maximum local variable array size
  u2 max_locals;
  /// Number of bytes in the code array
  u4 code_length;
  /// This method's bytecode stream
  u1* code;
  /// Size of the exception table
  u2 exception_table_length;
  /// Exception handlers for this code. See ExceptionTable
  ExceptionTable* exception_table;
  /// Number of inner attributes
  u2 attributes_count;
  /// Inner attributes
  struct AttributeInfo* atttributes;

  /// Number of actual instructions. Used for printing the class file
  u4 _instructions_count;
  /// Array of instructions. Used for printing the class file
  Instruction* _instructions;
} CodeInfo;

/** Table of exceptions a method may throw */
typedef struct {
  /// number of exceptions
  u2 number_of_exceptions;
  /// table of indexes in the constant pool to CONSTANT_Class_info
  u2* exception_index_table;
} ExceptionsInfo;

/** Array of inner classes */
typedef struct {
  /// number of classes
  u2 number_of_classes;
  /// array of classes. @see InnerClass
  InnerClass* classes;
} InnerClassesInfo;

/** The name of the source file for this class file */
typedef struct {
  /// index in the constant pool to a CONSTANT_Utf8_info
  u2 sourcefile_index;
} SourceFileInfo;

/** Table to associate line numbers in the source file with indexes in the code
 * array. Not used (debugging) */
typedef struct {
  /// size of the table
  u2 line_number_table_length;
  /// Table with line numbers and their corresponding start_pc in the code array
  LineNumber* line_number_table;
} LineNumberTableInfo;

/** NOT USED (debugging) */
typedef struct {
  u2 local_variable_table_length;
  struct {
    u2 start_pc;
    u2 length;
    u2 name_index;
    u2 descriptor_index;
    u2 index;
  } * local_variable_table;
} LocalVariableTableInfo;

///@}

// AttributeInfo struct
typedef struct AttributeInfo {
  u2 attribute_name_index;
  u4 attribute_length;

  AttributeType _attribute_type;
  char*         _attribute_name;

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

/**
 * @brief Reads an array of AttributeInfo from a file
 *
 * @param attributes_count - number of attributes to be read
 * @param fd - reference to a File structure that has the class file content
 * loaded into it. The File seek must be at the first attribute.
 * @param cp - reference to the current class file constant pool
 *
 * @return attributes - Array of AttributeInfo
 */
AttributeInfo* readAttributes(u2 attributes_count, File* fd, ConstantPoolInfo* cp);

/**
 * @brief Pretty prints the attribute array
 *
 * @param attributes_count - number of attributes in the array
 * @param attributes - an AttributeInfo array
 * @param cp - reference to the current class file constant pool
 */
void printAttributes(u2 attributes_count, AttributeInfo* attributes, ConstantPoolInfo* cp);

#endif  // __ATTRIBUTES_H
