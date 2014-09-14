#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <stdbool.h>

typedef struct ll_struct linkedlist_t;
struct ll_struct {
	node_t sentinel;
  int size;
};

extern void linkedlist_init(linkedlist_t *ll);

extern void linkedlist_insert(linkedlist_t *ll, void *data);

extern void linkedlist_remove(linkedlist_t *ll, void *data);

extern void *linkedlist_gethead(const linkedlist_t *ll);

extern void *linkedlist_gettail(const linkedlist_t *ll);

extern bool linkedlist_isempty(const linkedlist_t *ll);

extern const int linkedlist_getsize(const linkedlist_t *ll);

extern void linkedlist_destroy(linkedlist_t *ll);

#endif /* LINKEDLIST_H */