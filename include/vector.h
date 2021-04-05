#ifndef __VECTOR_H
#define __VECTOR_H

#define VECTOR_RESIZE_RATIO 2

typedef struct {
  int    length;
  int    array_size;
  void** array;
} Vector;

Vector* newVector(int initial_size);
void    insert(Vector* vec, void* value);
void*   get(Vector* vec, int index);
void*   pop(Vector* vec, int index);
void    freeVector(Vector* vec);

#endif  //__VECTOR_H
