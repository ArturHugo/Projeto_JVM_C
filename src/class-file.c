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