#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "attributes.h"
#include "class-file.h"
#include "common.h"
#include "instructions.h"

int main(int numargs, char* arg[]) {

  FILE* file = fopen(arg[1], "rb");

  File* fd = convertFile(file);

  fclose(file);

  ClassFile* class_file = readClassFile(fd);

  char* source_file_name = strtok(getSourceFile(class_file), ".");
  char* class_file_name  = strtok(arg[1], ".");

  if(strcmp(source_file_name, class_file_name)) {
    printf("%c[2K", 27);
    printf("\rError: source file name and class file name differ!\n");
    return 0;
  }

  printClassFile(class_file);

  free(fd->buffer);
  free(fd);

  return (0);
}

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