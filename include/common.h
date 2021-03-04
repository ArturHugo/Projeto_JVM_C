#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size specific data types
typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;

// Node struct for stack
typedef struct Node {
  void*        data;
  struct Node* next;
} Node;

// push a Node to stack. To use it for the first time, declare a Node*
// and pass it via reference in "nd". This will be your stack
// variable.Then, pass a pointer to what is being stored in "data",
// and its size (using sizeof()) in sz.
void pushNode(Node** nd, void* data, size_t sz);

// pass reference to stack in nd. declare a variable of the expected
// type, and pass its reference in "data" and size in "sz".
void popNode(Node** nd, void* data, size_t sz);

// pass array pointer, first 4 elements will be read and concatenated
// in 32bit result. pointer is not incremented.
u4 read32bFrom8b(u1* array);

#endif  // __COMMON_H