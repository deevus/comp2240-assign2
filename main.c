#include <stdio.h>
#include <stdlib.h>
#include "vertex.h"
#include "graph.h"
#include "semaphore.h"
#include "thread.h"

static void hello_world(void *threadId);

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

    thread_t thread = thread_create(hello_world, NULL);
    printf("Thread Id: %d\r\n", thread.id);

    int count = 1000000;
    while (count > 500000) count--;
    thread_destroy(&thread);
    while (count > 0) count--;
  }
}

static void hello_world(void *threadId) {
  int count = 100;
  while (count > 0) {
    printf("Hello, world! \r\n");
    count--;
  }
}
