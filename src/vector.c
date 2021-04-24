#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

// a mod b
static int mod(int a, int b) {
  int r = a % b;
  return r < 0 ? r + b : r;
}

Vector* newVector(int initial_size) {
  Vector* vec     = malloc(sizeof(*vec));
  vec->length     = 0;
  vec->array_size = initial_size;
  vec->array      = malloc(initial_size * sizeof(vec->array));
  return vec;
}

void resizeVector(Vector* vec) {
  vec->array_size *= VECTOR_RESIZE_RATIO;
  // realloc pode dar errado, mas a gente não liga 🤷
  vec->array = realloc(vec->array, vec->array_size);
}

void insert(Vector* vec, void* value) {
  if(vec->length >= vec->array_size)
    resizeVector(vec);

  vec->array[vec->length++] = value;
}

void* get(Vector* vec, int index) {
  index = mod(index, vec->length);

  return vec->array[index];
}

// Remove um item do vetor, reindexando o restante do array
// Aceita indices negativos
void* pop(Vector* vec, int index) {
  index = mod(index, vec->length);

  void* element = vec->array[index];

  for(int i = 0; i < vec->length - 1; i++)
    vec->array[i] = vec->array[i + 1];

  vec->length--;
  return element;
}

void freeVector(Vector* vec) {
  free(vec->array);
  free(vec);
}
