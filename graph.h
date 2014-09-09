#ifndef GRAPH_H
#define GRAPH_H

#include "linkedlist.h"
#include "vertex.h"

typedef struct Graph graph_t;
struct Graph {
	linkedlist_t vertices;
};

void graph_init(graph_t *g);

void graph_delete(graph_t *g);

void graph_add_vertex(graph_t *g, vertex_t *v);

#endif