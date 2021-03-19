#include "methods.h"
#include "class-file.h"
#include "constant-pool.h"
#include <inttypes.h>

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
    printf("	Name: cp_info #%" PRIu16 "\n", methods[i].name_index);
    printf("	Descriptor_index: cp_info #%" PRIu16 "\n", methods[i].descriptor_index);
    if(methods[i].access_flags < 10)
      printf("	Acess flag: 0x000%" PRIu16 "\n", methods[i].access_flags);
    else
      printf("	Acess flag: 0x00%" PRIu16 "\n", methods[i].access_flags);
    //printf("	Attributes_count: %" PRIu16 "\n", methods[i].attributes_count);
    if(methods[i].attributes_count > 0)
      for(int i = 0; i < methods[i].attributes_count; i++)
        printAttributes(methods[i].attributes_count, methods[i].attributes, cp);
  }

  printf("\n");
}