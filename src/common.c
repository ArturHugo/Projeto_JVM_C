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

void popNode(struct node** nd, void* data, int sz) {
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
  typedef struct {
    u1    bytecode;
    char* mnemonic;
    u1    pc;
    u1    n_args;
  } test;
  test  i, i2;
  test  teste;
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
  printf("\n%d\n%s\n%d\n%d",
         teste.bytecode,
         teste.mnemonic,
         teste.pc,
         teste.n_args);

  popNode(&list, &teste, sizeof(teste));
  printf("\n%d\n%s\n%d\n%d",
         teste.bytecode,
         teste.mnemonic,
         teste.pc,
         teste.n_args);
}