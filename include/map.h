#ifndef __MAP_H
#define __MAP_H

/**
 * @file map.h
 * \~english @brief An open addressing hash map structure
 * \~portuguese @brief Uma estrutura de hash-map usando endereçamento aberto
 */

#define DEFAULT_MAP_LENGTH 13   /// tamanho inicial de um map com newMap
#define MAX_LOAD_FACTOR    0.7  /// fator de carga pra iniciar um resize
#define RESIZE_RATIO       1.6  /// razão de resize

/** @brief entry in the hashmap table */
typedef struct {
  char* key;
  void* value;
} Entry;

/** @brief map strucure, created with _newMap or newMap */
typedef struct {
  short   table_size;  /// allocated space for the map table
  short   length;      /// number of items in the map
  Entry** table;       /// table of entries, with length of table_size
} Map;

/**
 * @brief Map constructor
 *
 * @param n_entries - initial map size
 *
 * @return Initialized Map structure
 *
 * Creates a Map structure, and allocates space for it's internals
 */
Map* _newMap(short n_entries);

/**
 * @brief Add item to the map
 *
 * @param map - Pointer to the initialized Map structure
 * @param key - String representing the key
 * @param value - Pointer to the value to be saved
 *
 * Add value to the hashmap using open addressing. Will not check for
 * duplicates. Value & key will be assigned by reference, not copy, which
 * means that they should live long enough to be retrieved.
 *
 */
void mapAdd(Map* map, char* key, void* value);

/**
 * @brief Retrieve value in item from map. Returns NULL if not found
 *
 * @param map - Pointer to the initialized Map structure
 * @param key - String to search for
 *
 * @return Pointer to the value of the entry matching key. NULL if not found
 *
 * Search the map for a item with the specified key. Return a pointer to
 * the value if found, else returns NULL.
 *
 */
void* mapGet(Map* map, char* key);

/**
 * @brief Remove item from map
 *
 * @param map - Pointer to the initialized Map structure
 * @param key - String to search for
 *
 * @return Pointer to the value of the entry matching key. NULL if not found
 *
 * Search the map for a item with the specified key. If found, deallocate entry
 * from the table, and return a pointer to the *value* removed. Returns NULL
 * otherwise.
 *
 */
void* mapRemove(Map* map, char* key);

/**
 * @brief Updates the value of entry
 *
 * @param map - Pointer to the initialized Map structure
 * @param key - String to search for
 * @param value - The new value to be set
 *
 * @return Pointer to the value before update. NULL if new entry
 *
 * Search the map for a item with the specified key. If found, updates the
 * value and returns a pointer to the old value. Otherwise, act like mapAdd.
 *
 */
void* mapSet(Map* map, char* key, void* value);

/**
 * @brief Frees Map structure and it's internals
 *
 * @param map - Pointer to the initialized Map structure
 *
 */
void  mapFree(Map* map);

/**
 * @brief Default map constructor
 *
 * @return Initialized Map structure
 *
 * Creates a Map structure, and allocates space for it's internals. See _newMap
 * for initial size options.
 *
 */
#define newMap() _newMap(DEFAULT_MAP_LENGTH);

#endif  //__MAP_H
