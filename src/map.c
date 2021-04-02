#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long hash(char* str);
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

Map* _newMap(short length) {
  Map* map    = malloc(sizeof(*map));
  map->length = length;
  map->table  = calloc(map->length, sizeof(size_t));
  return map;
}

// Adiciona uma entrada a tabela do Map.
void mapAdd(Map* map, char* key, void* value) {
  int index = hash(key) % map->length;
  while(map->table[index] != NULL)
    index++;
  map->table[index] = newEntry(key, value);
}

// Obtém um valor da tabela do Map. Retorna NULL se não encontrado.
void* mapGet(Map* map, char* key) {
  int index = hash(key) % map->length;

  if(map->table[index] == NULL) {
    return NULL;
  }

  while(strcmp(map->table[index]->key, key))
    index++;

  return map->table[index]->value;
}
