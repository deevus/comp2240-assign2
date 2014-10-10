/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#include "node.h"
#include <stdlib.h>

void node_init(node_t *node, const void *data) {
  node->data = data;
  node->nextptr = NULL;
  node->prevptr = NULL;
}
