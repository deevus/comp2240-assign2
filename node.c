#include "node.h"
#include <stdlib.h>

void node_init(node_t *node, void *data) {
  node->data = data;
  node->nextptr = NULL;
}

void node_delete(node_t *node) {
	free(node->data);
}