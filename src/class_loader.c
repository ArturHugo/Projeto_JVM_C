#include "class-file.h"
#include "methods.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ClassFile* readClassFile(FILE* fd) {
  ClassFile* class_file = (ClassFile*) malloc(sizeof(ClassFile));

  magic = b4Read(fd);
  if(isMagicValid(class_file) == 0) {
    printf("Class Format Error \n");
    exit(2);
  }

  minor_version = b2Read(fd);
  major_version = b2Read(fd);
  if(!isVersionValid(major_version)) {
    printf("Java version is invalid");
    exit(3);
  }
  constant_pool_count = b2Read(fd);
  ConstantPoolInfo* cp            = readConstantPool(constant_pool_count, fd);
  access_flags        = b2Read(fd);
  this_class          = b2Read(fd);
  super_class         = b2Read(fd);
  interfaces_count    = b2Read(fd);
  set_interface(fd, class_file);
  fields_count = b2Read(fd);
  set_fields(fd, class_file, cp);
  methods_count = b2Read(fd);
  set_methods(fd, class_file, cp);
  attributes_count = b2Read(fd);
  // attributes =
  // readAttributes(attributes_count, fd, cp);

  return class_file;
}

int main() {

  FILE*      file       = fopen("HelloWorld.class", "rb");
  ClassFile* JAVA_CLASS = readClassFile(file);
  FILE*      out        = fopen("output.txt", "w+");
  printMethods(out, JAVA_CLASS);
  fclose(file);
  return (0);
}
