#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "node.h"
#include "graph.h"

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: [#North Farmers] [#South Farmers]\r\n");
  }
  else {
    /* normal execution */
    int south = atoi(argv[argc - 1]);
    int north = atoi(argv[argc - 2]);

    printf("North Farmers: %d\r\nSouth Farmers: %d\r\n", north, south);

    //create islands
    vertex_t north_v, south_v;
    vertex_init(&north_v, "North Island", NULL);
    vertex_init(&south_v, "South Island", NULL);

    //these are the bridges
    vertex_add_adjacent(&north_v, &south_v);
    vertex_add_adjacent(&south_v, &north_v);

    //create graph
    graph_t g;
    graph_init(&g);

    graph_add_vertex(&g, &north_v);
    graph_add_vertex(&g, &south_v);

    graph_delete(&g);
  }
}
