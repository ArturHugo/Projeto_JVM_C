#include "class-file.h"

int isVersionValid(u2 major_version) {
  if(major_version >= 46 && major_version <= 55)
    return 1;
  else
    return 0;
}

int isMagicValid(ClassFile* class_file) { return class_file->magic == 0xCAFEBABE ? 1 : 0; }

u2* readInterfaces(u2 interfaces_count, File* fd) {
  u2* interfaces = malloc(interfaces_count * sizeof(*interfaces));

  for(u2 i = 0; i < interfaces_count; i++) {
    interfaces[i] = u2Read(fd);
  }

  return interfaces;
}

ClassFile* readClassFile(File* fd) {
  ClassFile* class_file = (ClassFile*) malloc(sizeof(ClassFile));

  class_file->magic = u4Read(fd);
  if(isMagicValid(class_file) == 0) {
    printf("Class Format Error \n");
    exit(2);
  }

  class_file->minor_version = u2Read(fd);
  class_file->major_version = u2Read(fd);
  if(!isVersionValid(class_file->major_version)) {
    printf("Java version is invalid");
    exit(3);
  }
  class_file->constant_pool_count = u2Read(fd);
  ConstantPoolInfo* cp            = readConstantPool(class_file->constant_pool_count, fd);
  class_file->access_flags        = u2Read(fd);
  class_file->this_class          = u2Read(fd);
  class_file->super_class         = u2Read(fd);
  class_file->interfaces_count    = u2Read(fd);
  class_file->interfaces          = readInterfaces(class_file->interfaces_count, fd);
  class_file->fields_count        = u2Read(fd);
  class_file->fields              = readFields(class_file->fields_count, fd, cp);
  class_file->methods_count       = u2Read(fd);
  class_file->methods             = readMethods(class_file->methods_count, fd, cp);
  class_file->attributes_count    = u2Read(fd);
  class_file->attributes          = readAttributes(class_file->attributes_count, fd, cp);

  return class_file;
}