#include "methods.h"
#include "class-file.h"

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
  printf("**********\n* Methods *\n**********\n");
  printf("methods_count: %u\n", methods_count);
  for(u2 i = 0; i < methods_count; i++) {
    printf("Method Number %d\n", i);
    printf("--->acess flag %" PRIu16 "\n", methods[i].access_flags);
    printf("--->name_index %" PRIu16 "\n", methods[i].name_index);
    printf("--->descriptor_index %" PRIu16 "\n", methods[i].descriptor_index);
    printf("--->attributes_count %" PRIu16 "\n", methods[i].attributes_count);
  }
  printf("\n");
}