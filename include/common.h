#ifndef __COMMON_H
#define __COMMON_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Size specific data types
typedef uint8_t  u1;
typedef uint16_t u2;
typedef uint32_t u4;

typedef struct node {
  void*        data;
  struct node* next;
} node;

void pushNode(struct node** nd, void* data, size_t sz);

void popNode(struct node** nd, void* data, int sz);

#endif  // __COMMON_H