#include "vertex.h"
#include <stdlib.h>

void vertex_init (vertex_t *v, char* name, void *data) {
	v->name = name;
	v->data = data;

	//init the linked list
	linkedlist_init( &v->adjacent_vertices );
}

void vertex_delete (vertex_t *v) {
	free(v->name);
	free(v->data);
	linkedlist_delete( &v->adjacent_vertices );
}

void vertex_add_adjacent (vertex_t *v, vertex_t *w) {
	linkedlist_t *ll = &v->adjacent_vertices;
	linkedlist_insert(ll, w);
}