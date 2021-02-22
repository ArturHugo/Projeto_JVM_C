#ifndef __CLASS_FILE_H
#define __CLASS_FILE_H

#include "common.h"

#include "attributes.h"
#include "constant-pool.h"
#include "fields.h"
#include "methods.h"
#include <stdio.h>
#include <stdlib.h>

// Access flag values
#define ACC_PUBLIC    0x0001
#define ACC_PRIVATE   0x0002
#define ACC_PROTECTED 0x0004
#define ACC_STATIC    0x0008
#define ACC_FINAL     0x0010
#define ACC_SYNTHETIC 0x1000

// Field specific access flag values
#define ACC_VOLATILE  0x0040
#define ACC_TRANSIENT 0x0080
#define ACC_ENUM      0x4000

// Method specific access flag values
#define ACC_SYNCHRONIZED 0x0020
#define ACC_BRIDGE       0x0040
#define ACC_VARARGS      0x0080
#define ACC_NATIVE       0x0100
#define ACC_ABSTRACT     0x0400
#define ACC_STRICT       0x0800

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

typedef struct ClassFile {
  u4             magic;
  u2             minor_version;
  u2             major_version;
  u2             constant_pool_count;
  Constant*      constant_pool;
  u2             access_flags;
  u2             this_class;
  u2             super_class;
  u2             interfaces_count;
  u2*            interfaces;
  u2             fields_count;
  Field*         fields;
  u2             methods_count;
  Method*        methods;
  u2             attributes_count;
  AttributeInfo* attributes;
} ClassFile;

// Functions to read .class file
u2        u2Read(FILE* fd);
u4        u4Read(FILE* fd);
Constant* readConstantPool(u2 cp_count, FILE* fd);
AttributeInfo* readAttributes(u2 attributes_count, FILE *fd, Constant* constant_pool);

#endif  // __CLASS_FILE_H
