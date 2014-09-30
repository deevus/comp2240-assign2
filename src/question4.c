#include "question4.h"
#include <stdio.h>
#include <pthread.h>
#include "time.h"
#include "monitor.h"
#include "semaphore_nostarve.h"
#include "common.h"

static int total_crossed_north_south;
static semaphore_t north_south_bridge;
static condition_t north_south_bridge_clear;
static mutex_t lock;

void run(int north_farmers, int south_farmers) {

  sem_ns_init(&north_south_bridge, 1);
  condition_init(&north_south_bridge_clear);
  mutex_init(&lock);
  common_init(north_farmers, south_farmers, &cross_bridge);

}

void cross_bridge(farmer_t *farmer) {
//allow thread to be cancelled
  common_pthread_setcancel();
  
  //loop forever
  while (1) {

  	monitor_wait(&lock, &north_south_bridge_clear);
    sem_ns_wait(&north_south_bridge);

    printf("%s farmer %d now crossing\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id);

    msleep(1000);
    printf("10 steps\r\n");

    msleep(1000);
    printf("20 steps\r\n");

    msleep(1000);
    printf("30 steps\r\n");

    total_crossed_north_south++;

    printf("%s farmer %d has crossed\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id);

    sem_ns_signal(&north_south_bridge);

    printf("Total Crossed: %d\r\n", total_crossed_north_south);

    sem_ns_wait(&north_south_bridge);
    monitor_signal(&north_south_bridge_clear);

    printf("%s farmer %d now returning\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id);

    msleep(500);
    printf("5 steps\r\n");

    msleep(500);
    printf("10 steps\r\n");

    msleep(500);
    printf("15 steps\r\n");

    total_crossed_north_south++;

    printf("%s farmer %d has returned\r\n", 
      (farmer->direction == NORTH ? "North" : "South"), 
      farmer->id);

    sem_ns_signal(&north_south_bridge);

    printf("Total Crossed: %d\r\n", total_crossed_north_south);
  }
}

void clean_up() {
  common_clean_up();

  printf("Destroying semaphore...\r\n");
  sem_ns_destroy(&north_south_bridge);
}