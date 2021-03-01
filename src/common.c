#include "common.h"
#include <stdio.h>

void pushNode(struct node** nd, void* data, size_t sz) {
  struct node* new_node = (struct node*) malloc(sizeof(struct node));

  new_node->data = malloc(sz);
  new_node->next = (*nd);

  int i;
  for(i = 0; i < sz; i++) {
    *(char*) (new_node->data + i) = *(char*) (data + i);
  }

  (*nd) = new_node;
}

void popNode(struct node** nd, void* data, size_t sz) {
  int i;
  for(i = 0; i < sz; i++) {
    *(char*) (data + i) = *(char*) ((*nd)->data + i);
  }

  free((*nd)->data);

  struct node* old_node;
  old_node = *nd;
  *nd      = (*nd)->next;
  free(old_node);
}

void testStack() {
  int testSuccesfull = 1;

  typedef struct {
    u1    bytecode;
    char* mnemonic;
    u1    pc;
    u1    n_args;
  } test;

  test i, i2;
  test teste;

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

  node* list = NULL;

  pushNode(&list, &i, sizeof(i));
  pushNode(&list, &i2, sizeof(i2));

  popNode(&list, &teste, sizeof(teste));
  if(teste.bytecode != i2.bytecode || teste.n_args != i2.n_args ||
     teste.pc != i2.pc) {
    testSuccesfull = 0;
  }
  popNode(&list, &teste, sizeof(teste));
  if(teste.bytecode != i.bytecode || teste.n_args != i.n_args ||
     teste.pc != i.pc) {
    testSuccesfull = 0;
  }

  if(testSuccesfull) {
    printf("Stack is working");
  } else {
    printf("Stack is broken");
  }
}

u4 read32bFrom8b(u1* array) {
  u4 output =
      (array[0] << 24 | array[1] << 16 | array[2] << 8 | array[3]);
  return output;
}