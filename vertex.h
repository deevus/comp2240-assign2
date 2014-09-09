#ifndef VERTEX_H
#define VERTEX_H
#include "linkedlist.h"

typedef struct Vertex vertex_t;
struct Vertex {
	char *name;
	void *data;
	linkedlist_t adjacent_vertices;
};

void vertex_init(vertex_t *v, char* name, void *data);

void vertex_add_adjacent(vertex_t *v, vertex_t *w);

void vertex_delete(vertex_t *v);

#endif