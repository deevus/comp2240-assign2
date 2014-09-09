#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "node.h"

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: [North Farmers] [South Farmers]\r\n");
  }
  else {
    /* normal execution */
    int south = atoi(argv[argc - 1]);
    int north = atoi(argv[argc - 2]);

    printf("North: %d\r\nSouth: %d\r\n", north, south);

    linkedlist_t *list = (linkedlist_t *)malloc(sizeof(linkedlist_t));
    linkedlist_init(list);
    for (int i = 0; i < 10 ; ++i)
    {
      //init value
      int *x = (int *)malloc(sizeof(int));
      *x = i;

      linkedlist_insert(list, x);
    }

    linkedlist_delete(list);
  }
}
