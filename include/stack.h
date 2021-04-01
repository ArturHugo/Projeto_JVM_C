#ifndef __STACK_H
#define __STACK_H

#include "common.h"

// Node struct for stack
typedef struct Node {
  void*        data;
  struct Node* next;
} Node;

typedef Node* Stack;

// push a Node to stack. To use it for the first time, declare a Node*
// and pass it via reference in "nd". This will be your stack
// variable.Then, pass a pointer to what is being stored in "data",
// and its size (using sizeof()) in sz.
void pushNode(Node** node, void* data, size_t size);

// pass reference to stack in nd. declare a variable of the expected
// type, and pass its reference in "data" and size in "sz".
void popNode(Node** node, void* data, size_t size);

#endif  //__STACK_H