#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "semaphore.h"
#include "farmer.h"
#include "time.h"

#define clear_screen() (system("clear"))

static semaphore_t semaphore;
static int total_crossed = 0;

static void cross_bridge(farmer_t *farmer);

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: [#North Farmers] [#South Farmers]\r\n");
  }
  else {
    /* normal execution */
    int south = atoi(argv[argc - 1]);
    int north = atoi(argv[argc - 2]);

    //init
    semaphore_init(&semaphore);
    int num_threads = north + south;
    int north_id, south_id;
    north_id = south_id = 0;
    pthread_t threads[num_threads];

    for (int i = 0; i < num_threads; ++i) {

      farmer_t *farmer = malloc(sizeof(farmer_t));
      if (north > 0) {
        farmer->id = ++north_id;
        farmer->direction = NORTH;
        north--;
      }
      else {
        farmer->id = ++south_id;
        farmer->direction = SOUTH;
        south--;
      }

      pthread_create(&threads[i], NULL, (void *)&cross_bridge, farmer);

    } 

    for (int i = 0; i < num_threads; ++i)
    {
      pthread_join(threads[i], NULL);
    }

  }

  pthread_exit(NULL);
}

static void cross_bridge(farmer_t *farmer) {
  while (1) {
    semaphore_wait(&semaphore);

    printf("%s farmer %d now crossing\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id);

    msleep(1000);
    printf("10 steps\r\n");

    msleep(1000);
    printf("20 steps\r\n");

    msleep(1000);
    printf("30 steps\r\n");

    total_crossed++;

    printf("%s farmer %d has crossed\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id);

    semaphore_signal(&semaphore);

    printf("Total Crossed: %d\r\n", total_crossed);
  }
}
