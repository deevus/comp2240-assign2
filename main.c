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

    //print adjacencies
    linkedlist_t vertices = g.vertices;
    node_t inode = *vertices.head;
    for (int i = 0; i < vertices.size; ++i)
    {
      vertex_t v = *(vertex_t *)inode.data;
      printf("%s:\r\n", v.name);

      node_t jnode = *v.adjacent_vertices.head;
      for (int j = 0; j < v.adjacent_vertices.size; ++j)
      {
        vertex_t w = *(vertex_t *)jnode.data;
        printf("Is connected to %s\r\n", w.name);

        if (jnode.nextptr)
          jnode = *jnode.nextptr;
      }

      if (inode.nextptr)
        inode = *inode.nextptr;
    }

    graph_delete(&g);
  }
}
