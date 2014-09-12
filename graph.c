#include "graph.h"
#include <stdlib.h>

void graph_init(graph_t *g) {
	linkedlist_init (&g->vertices);
}

void graph_delete(graph_t *g) {
	linkedlist_delete(&g->vertices);
}

void graph_add_vertex(graph_t *g, vertex_t *v) {
	linkedlist_insert(&g->vertices, v);
}