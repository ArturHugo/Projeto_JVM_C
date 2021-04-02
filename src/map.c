#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * djb2 goes brrr
 */
unsigned long hash(char* str) {
  unsigned long hash = 5381;
  int           c;

  while((c = *str++))
    hash = ((hash << 5) + hash) + c;

  return hash;
}

Entry* newEntry(char* key, void* value) {
  Entry* entry = malloc(sizeof(*entry));
  entry->value = value;
  entry->key   = key;
  return entry;
}

Map* _newMap(short table_size) {
  Map* map        = malloc(sizeof(*map));
  map->length     = 0;
  map->table_size = table_size;
  map->table      = calloc(map->table_size, sizeof(size_t));
  return map;
}

// Adiciona uma entrada a tabela do Map.
void mapAdd(Map* map, char* key, void* value) {
  int index = hash(key) % map->table_size;
  while(map->table[index] != NULL)
    index++;
  map->length++;
  map->table[index] = newEntry(key, value);
}

// Busca o index do elemento na tablea do Map.
// Retorna -1 se não encontrado
short mapFind(Map* map, char* key) {
  int index = hash(key) % map->table_size;

  while(map->table[index]) {
    if(!strcmp(map->table[index]->key, key))
      return index;
    index++;
  }

  return -1;
}

// Obtém um valor da tabela do Map. Retorna NULL se não encontrado.
void* mapGet(Map* map, char* key) {
  short index = mapFind(map, key);

  if(index == -1)
    return NULL;

  return map->table[index]->value;
}

// Remove um elemento da tabela do Map.
// Retorna o valor removido ou NULL se não encontrado.
void* mapRemove(Map* map, char* key) {
  short index = mapFind(map, key);

  if(index == -1)
    return NULL;

  void* value = map->table[index]->value;
  map->length--;
  free(map->table[index]);
  map->table[index] = NULL;
  return value;
}

// Altera um elemento do Map.
// Adiciona nova entrada caso não encontrado.
// Retorna o valor antigo para free()
void* mapSet(Map* map, char* key, void* value) {
  short index = mapFind(map, key);

  if(index == -1) {
    mapAdd(map, key, value);
    return NULL;
  }

  void* old_value          = map->table[index]->value;
  map->table[index]->value = value;
  return old_value;
}
