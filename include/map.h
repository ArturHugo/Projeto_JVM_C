#ifndef __MAP_H
#define __MAP_H

#define DEFAULT_MAP_LENGTH 13
#define MAX_LOAD_FACTOR    0.7
#define RESIZE_RATIO       1.6

#include <stddef.h>

typedef struct {
  char* key;
  void* value;
} Entry;

typedef struct {
  short   table_size;
  short   length;
  Entry** table;
} Map;

Map*  _newMap(short n_entries);
void  mapAdd(Map* map, char* key, void* value);
void* mapGet(Map* map, char* key);
void* mapRemove(Map* map, char* key);
void* mapSet(Map* map, char* key, void* value);
void  mapFree(Map* map);

#define newMap() _newMap(DEFAULT_MAP_LENGTH);

#endif  //__MAP_H
