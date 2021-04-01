#ifndef __MAP_H
#define __MAP_H

#include "common.h"

typedef struct Pair {
  char*        key;
  void*        value;
  struct Pair* next;
} Pair;

typedef struct Map {
  Pair* head;
  Pair* tail;
} Map;

Map*  newMap();
void  mapAdd(Map* map, char* key, void* value);
void* mapGet(Map* map, char* key);
void* mapRemove(Map* map, char* key);

#endif  //__MAP_H
