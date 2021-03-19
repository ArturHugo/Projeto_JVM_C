#include <stdio.h>
#include <stdlib.h>

#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "instructions.h"

int main(int numargs, char* arg[]) {

  FILE* file = fopen(arg[1], "rb");

  File* fd = convertFile(file);

  fclose(file);

  ClassFile* class_file = readClassFile(fd);

  printConstantPool(class_file->constant_pool_count, class_file->constant_pool);
  printAttributes(class_file->attributes_count, class_file->attributes, class_file->constant_pool);
  printMethods(class_file->methods_count, class_file->methods, class_file->constant_pool);
  printFields(class_file->fields_count, class_file->fields, class_file->constant_pool);

  // u2                constant_pool_count = u2Read(fd);
  // ConstantPoolInfo* constant_pool       = readConstantPool(constant_pool_count, fd);

  // u2  acess_flags      = u2Read(fd);
  // u2  this_class       = u2Read(fd);
  // u2  super_class      = u2Read(fd);
  // u2  interfaces_count = u2Read(fd);
  // u2* interfaces       = (u2*) malloc(sizeof(u2) * interfaces_count);

  // for(u2 i = 0; i < interfaces_count; i++) {
  //   interfaces[i] = u2Read(fd);
  // }
  // u2         fields_count = u2Read(fd);
  // FieldInfo* fields       = malloc(fields_count * sizeof(*fields));
  // fields                  = readFields(fields_count, fd, constant_pool);
  // printFields(fields_count, fields, constant_pool);

  // u2          methods_count = u2Read(fd);
  // MethodInfo* methods       = malloc(methods_count * sizeof(*methods));
  // methods                   = readMethods(methods_count, fd, constant_pool);
  // printMethods(methods_count, methods, constant_pool);

  // u2             attributes_count = u2Read(fd);
  // AttributeInfo* attributes       = malloc(attributes_count * sizeof(*attributes));
  // attributes                      = readAttributes(attributes_count, fd, constant_pool);
  // printAttributes(attributes_count, attributes, constant_pool);

  // /* class_file->attributes_count = b2Read(fp);
  // //class_file->attributes = readAttributes(class_file->attributes_count, fp, cp);
  // */

  free(fd->buffer);
  free(fd);

  return (0);
}