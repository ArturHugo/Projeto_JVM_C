#ifndef __FIELDS_H
#define __FIELDS_H

#include "attributes.h"
#include "common.h"

typedef struct Field {
  u2         access_flag;
  u2         name_index;
  u2         descriptor_index;
  u2         attributes_count;
  Attribute* attributes;
} Field;

#endif  // __FIELDS_H
