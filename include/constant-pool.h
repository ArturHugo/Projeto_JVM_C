#ifndef __CONSTANT_POOL_H
#define __CONSTANT_POOL_H

#include "common.h"

// Constant tag values
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
  u2 name_index;
} ClassInfo;

typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} FieldrefInfo;

typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} MethodrefInfo;

typedef struct {
  u2 class_index;
  u2 name_and_type_index;
} InterfaceMethodrefInfo;

typedef struct {
  u2 string_index;
} StringInfo;

typedef struct {
  u4 bytes;
} IntegerInfo;

typedef struct {
  u4 bytes;
} FloatInfo;

typedef struct {
  u4 high_bytes;
  u4 low_bytes;
} LongInfo;

typedef struct {
  u4 high_bytes;
  u4 low_bytes;
} DoubleInfo;

typedef struct {
  u2 name_index;
  u2 descriptor_index;
} NameAndTypeInfo;

typedef struct {
  u2  length;
  u1* bytes;
} Utf8Info;

typedef struct {
  u1 reference_kind;
  u2 reference_index;
} MethodHandleInfo;

typedef struct {
  u2 descriptor_index;
} MethodTypeInfo;

typedef struct {
  u2 bootstrap_method_attr_index;
  u2 name_and_type_index;
} InvokeDynamicInfo;

// Constant structure
typedef struct Constant {
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
  } info;
} ConstantPoolInfo;

// TODO: apagar isso aqui
// Constant *constant_pool = (Constant *) malloc(...);
// Constant *cp = constant_pool;
// cp->utf8_info.length = ...
// cp->utf8_info.bytes = (u1 *) malloc(cp->utf8_info.length);
//

#endif  // __CONSTANT_POOL_H