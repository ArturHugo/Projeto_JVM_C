#include "class-file.h"

#include <string.h>

static char* access_flag_table[16] = {"public",      // 0x1
                                      NULL,          // 0x2
                                      NULL,          // 0x4
                                      NULL,          // 0x8
                                      "final",       // 0x10
                                      "super",       // 0x20
                                      NULL,          // 0x40
                                      NULL,          // 0x80
                                      NULL,          // 0x100
                                      "interface",   // 0x200
                                      "abstract",    // 0x400
                                      NULL,          // 0x800
                                      "synthetic",   // 0x1000
                                      "annotation",  // 0x2000
                                      "enum",        // 0x4000
                                      NULL};         // 0x8000

void printAccessFlags(u2 access_flags) {
  for(int i = 0; i < 16; i++) {
    if((access_flags & 1) && (access_flag_table[i] != NULL)) {
      printf("%s ", access_flag_table[i]);
    }
    access_flags >>= 1;
  }
}

void printGeneralInfo(ClassFile* class_file) {
  printf("--------\nGeneral info:\n--------\n");
  printf("Minor version:       %d\n", class_file->minor_version);
  printf("Major version:       %d\n", class_file->major_version);
  printf("Constant pool count: %d\n", class_file->constant_pool_count);

  printf("Access flags:        0x%04x [", class_file->access_flags);
  printAccessFlags(class_file->access_flags);
  printf("]\n");

  u2 class_name_index = class_file->constant_pool[class_file->this_class].class_info.name_index;
  printf("This class:          cp_info #%d <%s>\n",
         class_file->this_class,
         class_file->constant_pool[class_name_index].utf8_info.bytes);

  class_name_index = class_file->constant_pool[class_file->super_class].class_info.name_index;
  printf("Super class:         cp_info #%d <%s>\n",
         class_file->this_class,
         class_file->constant_pool[class_name_index].utf8_info.bytes);

  printf("Interfaces count:    %d\n", class_file->interfaces_count);
  printf("Fields count:        %d\n", class_file->fields_count);
  printf("Methods count:       %d\n", class_file->methods_count);
  printf("Attrinbutes count:   %d\n", class_file->attributes_count);
}

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

void printInterfaces(u2 interfaces_count, u2* interfaces, ConstantPoolInfo* cp) {
  if(interfaces_count == 0)
    return;

  u1   num_of_strings = 0;
  u1** utf8_strings   = NULL;

  printf("-------\nInterfaces:\n-------\n");
  for(u2 i = 0; i < interfaces_count; i++) {
    printf("Interface %d: #%d ", i, interfaces[i]);
    utf8_strings = getUtf8Strings(&num_of_strings, cp, interfaces[i]);
    printf("<%s>\n", (char*) utf8_strings[0]);
  }
}

ClassFile* readClassFile(File* fd) {
  ClassFile* class_file = (ClassFile*) malloc(sizeof(ClassFile));

  class_file->magic = u4Read(fd);
  if(isMagicValid(class_file) == 0) {
    printf("Erro: nao tem cafebabe!\n");
    exit(2);
  }

  class_file->minor_version = u2Read(fd);
  class_file->major_version = u2Read(fd);
  if(!isVersionValid(class_file->major_version)) {
    printf("Erro: versao errada do Java!\n");
    exit(3);
  }
  class_file->constant_pool_count = u2Read(fd);
  class_file->constant_pool       = readConstantPool(class_file->constant_pool_count, fd);
  class_file->access_flags        = u2Read(fd);
  class_file->this_class          = u2Read(fd);
  class_file->super_class         = u2Read(fd);
  class_file->interfaces_count    = u2Read(fd);
  class_file->interfaces          = readInterfaces(class_file->interfaces_count, fd);
  class_file->fields_count        = u2Read(fd);
  class_file->fields        = readFields(class_file->fields_count, fd, class_file->constant_pool);
  class_file->methods_count = u2Read(fd);
  class_file->methods       = readMethods(class_file->methods_count, fd, class_file->constant_pool);
  class_file->attributes_count = u2Read(fd);
  class_file->attributes =
      readAttributes(class_file->attributes_count, fd, class_file->constant_pool);

  return class_file;
}

void printClassFile(ClassFile* class_file) {
  printGeneralInfo(class_file);
  printConstantPool(class_file->constant_pool_count, class_file->constant_pool);
  printInterfaces(class_file->interfaces_count, class_file->interfaces, class_file->constant_pool);
  printFields(class_file->fields_count, class_file->fields, class_file->constant_pool);
  printMethods(class_file->methods_count, class_file->methods, class_file->constant_pool);
  printAttributes(class_file->attributes_count, class_file->attributes, class_file->constant_pool);
}

char* getSourceFile(ClassFile* class_file) {
  for(int i = 0; i < class_file->attributes_count; i++) {
    if(!strcmp(class_file->attributes[i]._attribute_name, "SourceFile")) {
      u2 index = class_file->attributes[i].source_file_info.sourcefile_index;
      return (char*) class_file->constant_pool[index].utf8_info.bytes;
    }
  }
  return NULL;
}