#include "stack.h"

// Apenas para testStack
#include <stdio.h>

void pushNode(Node** node, void* data) {
  Node* new_node = malloc(sizeof(Node));

  new_node->data = data;
  new_node->next = (*node);

  (*node) = new_node;
}

void* popNode(Node** node) {
  void* data = (*node)->data;
  Node* old_node;
  old_node = *node;
  *node    = (*node)->next;
  free(old_node);
  return data;
}

void* peekNode(Stack stack) {
  if(stack) {
    return stack->data;
  }
  return NULL;
}

void pushValue(Stack* stack, u4 value) {
  u4* data = malloc(sizeof(u4));
  *data = value;
  pushNode(stack, data);
}

void popValue(Stack* stack, u4* reference) {
  u4* temp = popNode(stack);
  *reference = *temp;
  free(temp);
}
