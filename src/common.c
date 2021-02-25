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