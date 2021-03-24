#ifndef __METHODS_H
#define __METHODS_H

#include "attributes.h"
#include "common.h"

typedef struct Method {
  u2             access_flags;
  u2             name_index;
  u2             descriptor_index;
  u2             attributes_count;
  AttributeInfo* attributes;
} MethodInfo;

MethodInfo* readMethods(u2 methods_count, File* fd, ConstantPoolInfo* cp);
void        printMethods(u2 methods_count, MethodInfo* methods, ConstantPoolInfo* cp);

#endif  // __METHODS_H
