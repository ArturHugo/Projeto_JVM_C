#include "methods.h"
#include "class-file.h"
#include "constant-pool.h"

static char* access_flag_table[16] = {"public",        // 0x1
                                      "private",       // 0x2
                                      "protected",     // 0x4
                                      "static",        // 0x8
                                      "final",         // 0x10
                                      "synchronized",  // 0x20
                                      "bridge",        // 0x40
                                      "varargs",       // 0x80
                                      "native",        // 0x100
                                      NULL,            // 0x200
                                      "abstract",      // 0x400
                                      "strict",        // 0x800
                                      "synthetic",     // 0x1000
                                      NULL,            // 0x2000
                                      NULL,            // 0x4000
                                      NULL};           // 0x8000

void printMethodAccessFlags(u2 access_flags) {
  for(int i = 0; i < 16; i++) {
    if((access_flags & 1) && (access_flag_table[i] != NULL)) {
      printf("%s ", access_flag_table[i]);
    }
    access_flags >>= 1;
  }
}

MethodInfo* readMethods(u2 methods_count, File* fd, ConstantPoolInfo* cp) {
  MethodInfo* methods = malloc(methods_count * sizeof(*methods));
  for(u2 i = 0; i < methods_count; i++) {
    MethodInfo method;

    method.access_flags     = u2Read(fd);
    method.name_index       = u2Read(fd);
    method.descriptor_index = u2Read(fd);
    method.attributes_count = u2Read(fd);

    method.attributes = readAttributes(method.attributes_count, fd, cp);

    methods[i] = method;
  }
  return methods;
}

void printMethods(u2 methods_count, MethodInfo* methods, ConstantPoolInfo* cp) {
  printf("----------\n  Methods  \n----------\n");
  printf("Methods count: %u\n", methods_count);
  for(u2 i = 0; i < methods_count; i++) {
    printf("Method number: [%d]\n", i);
    printf("\tName:             cp_info #%d\n", methods[i].name_index);
    printf("\tDescriptor_index: cp_info #%d\n", methods[i].descriptor_index);
    printf("\tAcess flag:       0x%04x ", methods[i].access_flags);
    printMethodAccessFlags(methods[i].access_flags);
    printf("\n");
    printf("\tAttributes_count: %d\n", methods[i].attributes_count);

    printAttributes(methods[i].attributes_count, methods[i].attributes, cp);
  }

  printf("\n");
}