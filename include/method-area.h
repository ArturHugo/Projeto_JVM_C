#ifndef __METHOD_AREA_H
#define __METHOD_AREA_H

#include "class-file.h"
#include "fields.h"
#include "map.h"
#include "methods.h"

#define TYPE_INT       10
#define TYPE_LONG      11
#define TYPE_FLOAT     6
#define TYPE_DOUBLE    7
#define TYPE_REFERENCE 3
#define TYPE_BOOLEAN   4
#define TYPE_BYTE      8
#define TYPE_CHAR      5
#define TYPE_SHORT     9

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
