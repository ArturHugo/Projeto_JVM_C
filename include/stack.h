#ifndef __JVM_STACK_H
#define __JVM_STACK_H

#include "common.h"

/** Node struct for stack*/
typedef struct Node {
  void*        data;
  struct Node* next;
} Node;

typedef Node* Stack;

// push a Node to stack. To use it for the first time, declare a Node*
// and pass it via reference in "nd". This will be your stack
// variable.Then, pass a pointer to what is being stored in "data",
// and its size (using sizeof()) in sz.
void pushNode(Node** node, void* data);

// pops stack passed in node and returns the data address stored in it.
void* popNode(Node** node);

void* peekNode(Stack stack);

/*
 * Push a JavaType value without the need to allocate the value
 */
void pushValue(Stack* stack, JavaType value);

/*
 * Pop a JavaType value from the stack, puting it on reference and freeing the alloc
 */
void popValue(Stack* stack, JavaType* reference);

#endif  //__JVM_STACK_H
