#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"

typedef struct ll_struct linkedlist_t;
struct ll_struct {
  node_t *head;
  node_t *tail;
  int size;
};

void linkedlist_init(linkedlist_t *ll);

void linkedlist_insert(linkedlist_t *ll, void *data);

#endif /* LINKEDLIST_H */