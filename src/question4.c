#include "question4.h"
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "time.h"
#include "monitor.h"
#include "semaphore_nostarve.h"
#include "common.h"

static int total_crossed_north_south;
static semaphore_t north_south_bridge;
static mutex_t lock;
static bool north_south_in_use;

void run(int north_farmers, int south_farmers) {

  sem_ns_init(&north_south_bridge, 1);
  mutex_init(&lock);
  common_init(north_farmers, south_farmers, &cross_bridge);

  north_south_in_use = false;
}

static void cross(farmer_t *farmer, direction from, direction to, bool has_load) {
	if ((to == NORTH || to == SOUTH) && (from == NORTH || from == SOUTH)) {

		printf("%s farmer %d now %s\r\n", 
	    (farmer->direction == NORTH ? "North" : "South"), 
	    farmer->id, 
	    (has_load ? "crossing" : "returning"));

		int sleep_base = 500;
		int step_base = 5;
		int multiplier = has_load ? 2 : 1;

	  msleep(sleep_base * multiplier);
	  printf("%d steps\r\n", step_base * multiplier);

	  msleep(sleep_base * multiplier);
	  printf("%d steps\r\n", step_base * multiplier * 2);

	  msleep(sleep_base * multiplier);
	  printf("%d steps\r\n", step_base * multiplier * 3);	

    printf("%s farmer %d has %s\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id,
      (has_load ? "crossed" : "returned"));

	}
}

void cross_bridge(farmer_t *farmer) {
//allow thread to be cancelled
  common_pthread_setcancel();
  
  //loop forever
  while (1) {

    sem_ns_wait(&north_south_bridge);

    //flag bridge as in use
    north_south_in_use = true;

    cross(farmer, NORTH & SOUTH, farmer->direction, true);

    total_crossed_north_south++;

    sem_ns_signal(&north_south_bridge);

    printf("Total Crossed: %d\r\n", total_crossed_north_south);

    sem_ns_wait(&north_south_bridge);

    cross(farmer, NORTH & SOUTH, farmer->direction, false);

    total_crossed_north_south++;

    sem_ns_signal(&north_south_bridge);

    printf("Total Crossed: %d\r\n", total_crossed_north_south);
  }
}

void clean_up() {
  common_clean_up();

  printf("Destroying semaphore...\r\n");
  sem_ns_destroy(&north_south_bridge);
}