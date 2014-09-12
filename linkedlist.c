#include "linkedlist.h"
#include <stdlib.h>

#include <stdio.h>

void linkedlist_init(linkedlist_t *ll) {
  //init struct vars
  ll->head = ll->tail = NULL;
  ll->size = 0;
}

void linkedlist_insert(linkedlist_t *ll, void *data) {
  node_t *temp = (node_t *)malloc(sizeof(node_t));
  node_init(temp, data);

  //empty list
  if (ll->size == 0) {
    ll->head = temp;
    ll->tail = temp;
  }
  //insert at end
  else {
    //set the tails next to new node
    ll->tail->nextptr = temp;

    //set tail to new node
    ll->tail = temp;
  }

  ll->size++;
}

void linkedlist_delete(linkedlist_t *ll) {
  node_t *next, *curr = ll->head;
  while (curr) {
    next = curr->nextptr;

    node_delete(curr);

    curr = next;
  }
}
