#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "semaphore.h"
#include "thread.h"

#if defined(_WIN32)
  #define clear_screen() (system("cls"))
#else
  #define clear_screen() (system("clear"))
#endif

static semaphore_t semaphore;
static int north_threads, south_threads;
static int north_total, south_total;

static void cross_north(void *threadId);
static void cross_south(void *threadId);
static void cross_bridge();

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: [#North Farmers] [#South Farmers]\r\n");
  }
  else {
    /* normal execution */
    int south = atoi(argv[argc - 1]);
    int north = atoi(argv[argc - 2]);

    north_threads = south_threads = north_total = south_total = 0;

    semaphore_init(&semaphore);
    while (1 < 2) {
      if (north_threads < north) {
        thread_create(cross_north, NULL);
      }

      if (south_threads < south) {
        thread_create(cross_south, NULL);
      }

      clear_screen();
      printf("North: %d\r\nSouth: %d\r\n", north_total, south_total);

      sleep(1);
    } 

  }
}

typedef enum { NORTH, SOUTH } direction;

static void cross_north(void *threadId) {
  north_threads++;
  cross_bridge(NORTH);
  north_threads--;
}

static void cross_south(void *threadId) {
  south_threads++;
  cross_bridge(SOUTH);
  south_threads--;
}

static void cross_bridge(direction d) {
  semaphore_wait(&semaphore);

  sleep(3);

  if (d == NORTH)
    north_total++;
  else if (d == SOUTH) 
    south_total++;

  semaphore_signal(&semaphore);
}
