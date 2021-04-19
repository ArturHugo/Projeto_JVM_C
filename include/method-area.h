#ifndef __METHOD_AREA_H
#define __METHOD_AREA_H

#include "fields.h"
#include "map.h"
#include "methods.h"

#define TYPE_INT       0
#define TYPE_LONG      1
#define TYPE_FLOAT     2
#define TYPE_DOUBLE    3
#define TYPE_REFERENCE 4
#define TYPE_BYTE      5
#define TYPE_CHAR      6
#define TYPE_SHORT     7

typedef struct Object {
  Class* class;
  Map* fields_and_values; /** Map<char*, JavaType*> */
} Object;

typedef struct Array {
  u1        type;
  int32_t   length;
  JavaType* elements;
} Array;

typedef struct MethodArea {
  Map*    loaded_classes;
  Object* objects;
} MethodArea;

#endif  //__METHOD_AREA_H
