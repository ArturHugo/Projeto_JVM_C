#ifndef __FIELDS_H
#define __FIELDS_H

#include "attributes.h"
#include "common.h"

typedef struct Field {
  u2             access_flags;
  u2             name_index;
  u2             descriptor_index;
  u2             attributes_count;
  AttributeInfo* attributes;
} FieldInfo;

FieldInfo* readFields(u2 fields_count, File* fd, ConstantPoolInfo* cp);
void printFields(u2 fields_count, FieldInfo* fields, ConstantPoolInfo* cp);

#endif  // __FIELDS_H
