#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread.h"
#include "semaphore_nostarve.h"
#include "node.h"
#include "linkedlist.h"
#include "queue.h"

#if defined(_WIN32)
  #define clear_screen() (system("cls"))
#elif defined(__unix__)
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
    printf("main: Start\r\n");

    int south = atoi(argv[argc - 1]);
    int north = atoi(argv[argc - 2]);

    north_threads = south_threads = north_total = south_total = 0;

    int next_thread_id = 1;
    sem_ns_init(&semaphore);
    while (1 < 2) {
      if (north_threads < north) {
      	int *n_id = malloc(sizeof(int));
        *n_id = next_thread_id++;
        thread_create(cross_north, n_id);
      }

      if (south_threads < south) {
      	int *s_id = malloc(sizeof(int));
        *s_id = next_thread_id++;
        thread_create(cross_south, s_id);
      }

      //clear_screen();
      //printf("North: %d\r\nSouth: %d\r\n", north_total, south_total);

      sleep(1);
    } 

    sem_ns_destroy(&semaphore);
  }
}

typedef enum { NORTH, SOUTH } direction;

static void cross_north(void *threadId) {
  north_threads++;
  cross_bridge(NORTH, threadId);
  north_threads--;
}

static void cross_south(void *threadId) {
  south_threads++;
  cross_bridge(SOUTH, threadId);
  south_threads--;
}

static void cross_bridge(direction d, int id) {
  sem_ns_wait(&semaphore, id);

  printf("%d now crossing\r\n", id);
  sleep(3);

  if (d == NORTH)
    north_total++;
  else if (d == SOUTH) 
    south_total++;

  printf("%d has crossed\r\n", id);
  sem_ns_signal(&semaphore);
}
