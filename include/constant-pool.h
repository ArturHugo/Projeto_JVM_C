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

// Constant structure
typedef struct Constant {
  u1 tag;
  union {
    struct {
      u2 name_index;
    } Class;

    struct {
      u2 class_index;
      u2 name_and_type_index;
    } Fieldref;

    struct {
      u2 class_index;
      u2 name_and_type_index;
    } Methodref;

    struct {
      u2 class_index;
      u2 name_and_type_index;
    } InterfaceMethodref;

    struct {
      u2 string_index;
    } String;

    struct {
      u4 bytes;
    } Integer;

    struct {
      u4 bytes;
    } Float;

    struct {
      u4 high_bytes;
      u4 low_bytes;
    } Long;

    struct {
      u4 high_bytes;
      u4 low_bytes;
    } Double;

    struct {
      u2 name_index;
      u2 descriptor_index;
    } NameAndType;

    struct {
      u2  length;
      u1* bytes;
    } Utf8;

    struct {
      u1 reference_kind;
      u2 reference_index;
    } MethodHandle;

    struct {
      u2 descriptor_index;
    } MethodType;

    struct {
      u2 bootstrap_method_attr_index;
      u2 name_and_type_index;
    } InvokeDynamic;
  } info;
} Constant;

// TODO: apagar isso aqui
// Constant *constant_pool = (Constant *) malloc(...);
// Constant *cp = constant_pool;
// cp->info.Utf8.length = ...
// cp->info.Utf8.bytes = (u1 *) malloc(cp->info.Utf8.length);
//

#endif  // __CONSTANT_POOL_H