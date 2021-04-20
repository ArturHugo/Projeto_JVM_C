#include "map.h"
#include "string.h"

Map* newMap() {
  Map* map  = malloc(sizeof(Map*));
  map->tail = NULL;
  map->head = NULL;
  return map;
}

// Adiciona uma entrada a tabela do Map. Não confere se a entrada é repetida.
void mapAdd(Map* map, char* key, void* value) {
  Pair* new_pair  = malloc(sizeof(Pair*));
  new_pair->key   = key;
  new_pair->value = value;
  new_pair->next  = NULL;

  if(map->head == NULL) {
    map->head = new_pair;
    map->tail = new_pair;
  } else {
    map->tail->next = new_pair;
    map->tail       = new_pair;
  }
}

// Obtém um valor da tabela do Map. Retorna NULL se não encontrado.
void* mapGet(Map* map, char* key) {
  Pair* current_pair = map->head;

  if(current_pair == NULL)
    return NULL;

  while(current_pair != NULL && strcmp(current_pair->key, key))
    current_pair = current_pair->next;

  if(current_pair == NULL)
    return NULL;

  return current_pair->value;
}

// Remove um valor do Map e retorna o valor removido.
void* mapRemove(Map* map, char* key) {
  Pair* current_pair  = map->head;
  Pair* previous_pair = NULL;

  if(current_pair == NULL)
    return NULL;

  while(current_pair != NULL && strcmp(current_pair->key, key)) {
    previous_pair = current_pair;
    current_pair  = current_pair->next;
  }

  if(current_pair == NULL)
    return NULL;

  if(previous_pair == NULL) {
    map->head = current_pair->next;
  } else {
    if(current_pair == map->tail) {
      map->tail = previous_pair;
    }
    previous_pair->next = current_pair->next;
  }

  void* value = current_pair->value;
  free(current_pair);
  return value;
}
