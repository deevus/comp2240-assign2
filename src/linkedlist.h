/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <stdbool.h>

typedef struct ll_struct linkedlist_t;
struct ll_struct {
	node_t sentinel;
  int size;
};

/*
	Initialises linked list instance

	Preconditions: ll is not null
	Postconditions: linked list is initialised to default values
*/
void linkedlist_init(linkedlist_t *ll);

/*
	Insert the given data into the linked list

	Preconditions: ll is not null
	Postconditions: data is inserted into the end of the list
*/
void linkedlist_insert(linkedlist_t *ll, const void *data);

/*
	Removed the given data item from the linked list

	Preconditions: ll and data is not null
	Postconditions: data is removed from the list
*/
void linkedlist_remove(linkedlist_t *ll, const void *data);

/*
	Returns the head of the list

	Preconditions: none
	Postconditions: none
*/
const void *linkedlist_gethead(const linkedlist_t *ll);

/*
	Returns the tail of the list

	Preconditions: none
	Postconditions: none
*/
const void *linkedlist_gettail(const linkedlist_t *ll);

/*
	Determines whether the linked list is empty

	Preconditions: ll is not null
	Postconditions: none
*/
bool linkedlist_isempty(const linkedlist_t *ll);

/*
	Returns the size of the list

	Preconditions: ll is not null
	Postconditions: none
*/
const int linkedlist_getsize(const linkedlist_t *ll);

/*
	Cleans up any memory allocation for the list

	Preconditions: ll is not null
	Postconditions: ll is no longer initialised
*/
void linkedlist_destroy(linkedlist_t *ll);

#endif /* LINKEDLIST_H */