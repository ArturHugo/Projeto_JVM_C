#ifndef __CLASS_FILE_H
#define __CLASS_FILE_H

#include "common.h"

#include "file.h"

#include "attributes.h"
#include "constant-pool.h"
#include "fields.h"
#include "map.h"
#include "methods.h"

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

typedef enum { loaded, initialized } ClassStatus;

typedef struct ClassFile {
  ClassStatus       _status;
  struct ClassFile* _super_class;
  u4                magic;
  u2                minor_version;
  u2                major_version;
  u2                constant_pool_count;
  ConstantPoolInfo* constant_pool;
  u2                access_flags;
  u2                this_class;
  u2                super_class;
  u2                interfaces_count;
  u2*               interfaces;
  u2                fields_count;
  FieldInfo*        fields;
  Map*              _field_map;
  u2                methods_count;
  MethodInfo*       methods;
  Map*              _method_map;
  u2                attributes_count;
  AttributeInfo*    attributes;
} ClassFile;

// Um alias pra ClassFile. Só pra ficar mais fácil de mudar depois
typedef ClassFile Class;

int isVersionValid(u2 major_version);
int isMagicValid(ClassFile* class_file);

u2* readInterfaces(u2 interfaces_count, File* fd);

ClassFile* readClassFile(File* fd);

void printClassFile(ClassFile* class_file);

char* getSourceFile(ClassFile* class_file);

void loadObjectClass();
Class* loadClass(char* file_path);

char* trimSuffix(char* file_path, char* suffix);

void resolveReferences(ClassFile *class_file);
void initializeClass(ClassFile* class_file);

#endif  // __CLASS_FILE_H
