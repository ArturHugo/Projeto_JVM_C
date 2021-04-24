#ifndef __CONSTANT_POOL_H
#define __CONSTANT_POOL_H

#include "common.h"

#include "file.h"

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

ConstantPoolInfo* readConstantPool(u2 cp_count, File* fd);

void printConstantPool(u2 cp_count, ConstantPoolInfo* constant_pool);
void printConstantValue(ConstantPoolInfo* constant_pool, u2 index);

u1*  getUtf8String(ConstantPoolInfo* constant_pool, uint16_t index);
u1** getUtf8Strings(u1* num_of_strings, ConstantPoolInfo* constant_pool, uint16_t index);
u2   getArgumentCount(u1* descriptor);
#endif  // __CONSTANT_POOL_H
