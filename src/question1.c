#include "question1.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "time.h"
#include "common.h"
#include "semaphore.h"

static semaphore_t semaphore;
static int total_crossed = 0;

void run(int north_farmers, int south_farmers) {

  semaphore_init(&semaphore, 1);
  common_init(north_farmers, south_farmers, &cross_bridge);

}

void cross_bridge(farmer_t *farmer) {
  //allow thread to be cancelled in the case of clean up
  common_pthread_setcancel();

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

void clean_up() {
  common_clean_up();
}