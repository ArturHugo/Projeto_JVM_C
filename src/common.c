#include "common.h"

void pushList(struct node** nd, void* data, size_t sz) {
  struct node* new_node = (struct node*) malloc(sizeof(struct node));

  new_node->data = malloc(sz);
  new_node->next = (*nd);

  int i;
  for(i = 0; i < sz; i++)
    *(char*) (new_node->data + i) = *(char*) (data + i);

  (*nd) = new_node;
}