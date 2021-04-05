#include "stack.h"

// Apenas para testStack
#include <stdio.h>

void pushNode(Node** node, void* data, size_t size) {
  Node* new_node = malloc(sizeof(Node));

  new_node->data = malloc(size);
  new_node->next = (*node);

  size_t i;
  for(i = 0; i < size; i++) {
    *((u1*) (new_node->data) + i) = *((u1*) data + i);
  }

  (*node) = new_node;
}

void popNode(Node** node, void* data, size_t size) {
  size_t i;
  for(i = 0; i < size; i++) {
    *((u1*) data + i) = *((u1*) ((*node)->data) + i);
  }

  free((*node)->data);

  Node* old_node;
  old_node = *node;
  *node    = (*node)->next;
  free(old_node);
}

void* peekNode(Stack stack) { return (*stack).data; }

void testStack() {
  int testSuccesfull = 1;

  typedef struct {
    u1    bytecode;
    char* mnemonic;
    u1    pc;
    u1    n_args;
  } test;

  test  i, i2;
  test  teste;
  test* peekTest;

  char* mn   = "teste";
  i.bytecode = 42;
  i.mnemonic = mn;
  i.pc       = 42;
  i.n_args   = 4;

  char* mn2   = "teste2";
  i2.bytecode = 43;
  i2.mnemonic = mn2;
  i2.pc       = 43;
  i2.n_args   = 5;

  Node* list = NULL;

  pushNode(&list, &i, sizeof(i));
  pushNode(&list, &i2, sizeof(i2));

  peekTest = peekNode(list);
  if(peekTest->bytecode != i2.bytecode || peekTest->n_args != i2.n_args || peekTest->pc != i2.pc) {
    testSuccesfull = 0;
  }

  popNode(&list, &teste, sizeof(teste));
  if(teste.bytecode != i2.bytecode || teste.n_args != i2.n_args || teste.pc != i2.pc) {
    testSuccesfull = 0;
  }
  popNode(&list, &teste, sizeof(teste));
  if(teste.bytecode != i.bytecode || teste.n_args != i.n_args || teste.pc != i.pc) {
    testSuccesfull = 0;
  }

  if(testSuccesfull) {
    printf("Stack is working");
  } else {
    printf("Stack is broken");
  }
}