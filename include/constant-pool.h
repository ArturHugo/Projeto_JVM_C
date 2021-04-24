#ifndef __CONSTANT_POOL_H
#define __CONSTANT_POOL_H

#include "common.h"

#include "file.h"

/**
 * @file constant-pool.h
 * @brief Structures and functions concerning the constant pool.
 */

// ConstantPoolInfo tag values
#define CONSTANT_CLASS               7
#define CONSTANT_FIELDREF            9
#define CONSTANT_METHODREF           10
#define CONSTANT_INTERFACE_METHODREF 11
#define CONSTANT_STRING              8
#define CONSTANT_INTEGER             3
#define CONSTANT_FLOAT               4
#define CONSTANT_LONG                5
#define CONSTANT_DOUBLE              6
#define CONSTANT_NAME_AND_TYPE       12
#define CONSTANT_UTF8                1
#define CONSTANT_METHOD_HANDLE       15
#define CONSTANT_METHOD_TYPE         16
#define CONSTANT_INVOKE_DYNAMIC      18

// CONSTAT_item_info
typedef struct {
  /// Reference to a Utf8Info in the ClassFile's constant pool.
  u2 name_index;

  /// Points to the resolved reference to the class' name.
  u1* _name;
} ClassInfo;

typedef struct {
  /// Reference to a ClassInfo in the ClassFile's constant pool.
  u2 class_index;
  /// Reference to a NameAndTypeInfo in the ClassFile's constant pool.
  u2 name_and_type_index;

  /// Points to the resolved reference to the name of the field's class.
  u1* _class;
  /// Points to the resolved reference to the name of the field.
  u1* _name;
  /// Points to the resolved reference to the field's descriptor string.
  u1* _descriptor;
} FieldrefInfo;

typedef struct {
  /// Reference to a ClassInfo in the ClassFile's constant pool.
  u2 class_index;
  /// Reference to a NameAndTypeInfo in the ClassFile's constant pool.
  u2 name_and_type_index;

  /// Points to the resolved reference to the name of the method's class.
  u1* _class;
  /// Points to the resolved reference to the name of the method.
  u1* _name;
  /// Points to the resolved reference to the method's descriptor string.
  u1* _descriptor;
} MethodrefInfo;

typedef struct {
  /// Reference to a ClassInfo in the ClassFile's constant pool.
  u2 class_index;
  /// Reference to a NameAndTypeInfo in the ClassFile's constant pool.
  u2 name_and_type_index;

  /// Points to the resolved reference to the name of the method's interface.
  u1* _interface;
  /// Points to the resolved reference to the name of the method.
  u1* _name;
  /// Points to the resolved reference to the method's descriptor string.
  u1* _descriptor;
} InterfaceMethodrefInfo;

typedef struct {
  /// Reference to a StringInfo in the ClassFile's constant pool.
  u2 string_index;

  /// Points to the resolved reference to string's value.
  u1* _value;
} StringInfo;

typedef struct {
  /// Bytes of the integer value.
  u4 bytes;
} IntegerInfo;

typedef struct {
  /// Bytes of the float value encoded in IEEE 754.
  u4 bytes;

  /// Bytes value converted to float for ease of use.
  float _value;
} FloatInfo;

typedef struct {
  /// 4 most significant bytes of the float value.
  u4 high_bytes;
  /// 4 least significant bytes of the float value.
  u4 low_bytes;

  /// Bytes values converted to a single float value for ease of use.
  uint64_t _value;
} LongInfo;

typedef struct {
  /// 4 most significant bytes of the double value.
  u4 high_bytes;
  /// 4 least significant bytes of the double value.
  u4 low_bytes;

  /// Bytes values converted to a single double value for ease of use.
  double _value;
} DoubleInfo;

typedef struct {
  /// Reference to a Utf8Info in the ClassFile's constant pool.
  u2 name_index;
  /// Reference to a Utf8Info in the ClassFile's constant pool.
  u2 descriptor_index;
} NameAndTypeInfo;

typedef struct {
  /// Length of the UTF8 string.
  u2 length;
  /// Pointer to bytes of the UTF8 string.
  u1* bytes;
} Utf8Info;

typedef struct {
  u1 reference_kind;
  u2 reference_index;
} MethodHandleInfo;

typedef struct {
  /// Reference to a Utf8Info in the ClassFile's constant pool.
  u2 descriptor_index;
} MethodTypeInfo;

typedef struct {
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;
} InvokeDynamicInfo;

// Constant structure
typedef struct ConstantPoolInfo {
  u1 tag;
  union {
    ClassInfo              class_info;
    FieldrefInfo           fieldref_info;
    MethodrefInfo          methodref_info;
    InterfaceMethodrefInfo interface_methodref_info;
    StringInfo             string_info;
    IntegerInfo            integer_info;
    FloatInfo              float_info;
    LongInfo               long_info;
    DoubleInfo             double_info;
    NameAndTypeInfo        name_and_type_info;
    Utf8Info               utf8_info;
    MethodHandleInfo       method_handle_info;
    MethodTypeInfo         method_type_info;
    InvokeDynamicInfo      invoke_dynamic_info;
  };
} ConstantPoolInfo;

/**
 * @fn ConstantPoolInfo* readConstantPool(u2 cp_count, File* fd)
 * @brief Reads constant pool from a class file and stores it into memory.
 *
 * @param cp_count - number of elements in the constant pool +1.
 * @param fd - reference to a File structure that has the class file content
 * loaded into it.
 *
 * @return constant_pool - reference to constant pool represented by pointer to ConstantPoolInfo.
 */
ConstantPoolInfo* readConstantPool(u2 cp_count, File* fd);

/**
 * @fn void printConstantPool(u2 cp_count, ConstantPoolInfo* constant_pool)
 * @brief Prints all the values in the constant pool.
 *
 * @param cp_count - number of elements in the constant pool +1.
 * @param constant_pool - reference to a constant pool.
 */
void printConstantPool(u2 cp_count, ConstantPoolInfo* constant_pool);

/**
 * @fn void printConstantValue(ConstantPoolInfo* constant_pool, u2 index)
 * @brief Prints a constant value from the constant pool at the given index.
 *
 * @param constant_pool - reference to a constant pool.
 * @param index - must be a valid index to the constant pool (not 0).
 */
void printConstantValue(ConstantPoolInfo* constant_pool, u2 index);

/**
 * @fn u1* getUtf8String(ConstantPoolInfo* constant_pool, uint16_t index)
 * @brief Finds UTF8 string associated with ClassInfo's name_index or StringInfo's
 * string_index.
 *
 * @param constant_pool - reference to a constant pool.
 * @param index - must be a valid index to the constant pool (not 0).
 *
 * @return utf8_string - pointer to first byte of UTF8 string.
 */
u1* getUtf8String(ConstantPoolInfo* constant_pool, uint16_t index);

/**
 * @fn u1** getUtf8Strings(u1* num_of_strings, ConstantPoolInfo* constant_pool, uint16_t index)
 * @brief Finds all UTF8 strings associated with a constant pool value
 *
 * @param num_of_strings - used to return by reference the number of strings returned by the
 * function.
 * @param constant_pool - reference to a constant pool.
 * @param index - must be a valid index to the constant pool (not 0).
 *
 * @return utf8_strings - list of pointers UTF8 strings associated with a constant pool value.
 *
 * Formats of utf8_strings:
 * - ClassInfo:
 *   * utf8_strings[0] = class name string.
 * - FieldrefInfo/MethodrefInfo/InterfaceMethodrefInfo:
 *   * utf8_strings[0] = name string of the field/method's class/interface.
 *   * utf8_strings[1] = name string of the field/method.
 *   * utf8_strings[2] = name string of the field/emthod's descriptor.
 * - StringInfo:
 *   * utf8_strings[0] = string's value.
 * - NameAndTypeInfo:
 *   * utf8_strings[0] = name string of the field/method.
 *   * utf8_strings[1] = name string of the field/emthod's descriptor.
 * - Utf8Info:
 *   * utf8_strings = NULL.
 */
u1** getUtf8Strings(u1* num_of_strings, ConstantPoolInfo* constant_pool, uint16_t index);

/**
 * @fn u2 getArgumentCount(u1* descriptor)
 * @brief analyses a method descriptor and return it's number of arguments.
 *
 * @param descriptor - pointer to method descriptor's string.
 *
 * @return n_args - number of arguments of method by analysing it's descriptor.
 */
u2 getArgumentCount(u1* descriptor);
#endif  // __CONSTANT_POOL_H
