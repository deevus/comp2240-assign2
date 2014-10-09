#include "question2.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "common.h"
#include "semaphore_nostarve.h"

static semaphore_t semaphore;
static int total_crossed = 0;

void run(int north_farmers, int south_farmers) {

  sem_ns_init(&semaphore, 1);
  common_init(north_farmers, south_farmers, &do_work);

}

void do_work(farmer_t *farmer) {
  //allow thread to be cancelled
  common_pthread_setcancel();

  //loop forever
  while (1) {

    sem_ns_wait(&semaphore);

    printf("%s farmer %d now crossing\r\n", 
      (farmer->destination == NORTH ? "North" : "South"), 
      farmer->id);

    msleep(1000);
    printf("10 steps\r\n");

    msleep(1000);
    printf("20 steps\r\n");

    msleep(1000);
    printf("30 steps\r\n");

    total_crossed++;

    printf("%s farmer %d has crossed\r\n", 
      (farmer->destination == NORTH ? "North" : "South"), 
      farmer->id);

    sem_ns_signal(&semaphore);

    printf("Total Crossed: %d\r\n", total_crossed);

  }
}

void clean_up() {
  common_clean_up();

  printf("Destroying semaphore...\r\n");
  sem_ns_destroy(&semaphore);
}