#include "stack.h"

// Apenas para testStack
#include <stdio.h>

/**
 * push a Node to stack. To use it for the first time, declare a Node*,
 * initialize it as NULL and pass it via reference in "nd". This will be your stack
 * variable.Then, pass a pointer to what is being stored in "data",
 * and its size (using sizeof()) in sz.
 *
 * @param node Pointer to Node* (stack) created.
 * @param data Pointer to dynamically allocated address to be kept in stack.
 */
void pushNode(Node** node, void* data) {
  Node* new_node = malloc(sizeof(Node));

  new_node->data = data;
  new_node->next = (*node);

  (*node) = new_node;
}

/**
 * pops stack passed in node and returns the data address stored in it.
 *
 * @param node Pointer to Node* (stack) created.
 * @return pointer stored in the popped node.
 */
void* popNode(Node** node) {
  void* data = (*node)->data;
  Node* old_node;
  old_node = *node;
  *node    = (*node)->next;
  free(old_node);
  return data;
}

/**
 * returns the data address stored in the stack's top node.
 *
 * @param stack Pointer to stack.
 * @return pointer stored in the in the stack's top node.
 */
void* peekNode(Stack stack) {
  if(stack) {
    return stack->data;
  }
  return NULL;
}

/**
 * Push a JavaType value without the need to allocate the value
 *
 * @param stack Stack into which to push the value
 * @param value JavaType value to be stored. It is copied by value, therefere doesn't need to have
 * been previoustly allocated.
 */
void pushValue(Stack* stack, JavaType value) {
  JavaType* data = malloc(sizeof(JavaType));
  *data          = value;
  pushNode(stack, data);
}

/**
 * Pop a JavaType value from the stack, puting it on reference and freeing the alloc
 *
 * @param stack Stack from which value is popped.
 * @param reference Reference to JavaType into which the popped node's information will be stored.
 */
void popValue(Stack* stack, JavaType* reference) {
  JavaType* temp = popNode(stack);
  *reference     = *temp;
  free(temp);
}
