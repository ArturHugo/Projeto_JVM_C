#ifndef __METHOD_AREA_H
#define __METHOD_AREA_H

#include "fields.h"
#include "map.h"
#include "methods.h"

typedef struct JavaType {
  u1 cat_tag;
  u4 high_bytes;
  u4 low_bytes;
} JavaType;

typedef struct Object {
  MethodInfo* methods;
  Map         fields_and_values;
} Object;

typedef struct MethodArea {
  Map     loaded_classes;
  Object* objects;
} MethodArea;

extern MethodArea method_area;

#endif  //__METHOD_AREA_H