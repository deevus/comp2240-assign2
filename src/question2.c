/**
  Simon Hartcher
  C3185790

  COMP2240 Assignment 2
**/

#include "question2.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "common.h"
#include "semaphore_nostarve.h"

static semaphore_t semaphore;
static int total_crossed = 0;

void run(int north_farmers, int south_farmers) {

  //init vars
  sem_ns_init(&semaphore, 1);
  common_init(north_farmers, south_farmers, &do_work);

}

void do_work(farmer_t *farmer) {
  //allow thread to be cancelled
  common_pthread_setcancel();

  //loop forever
  while (1) {

    //wait for turn
    sem_ns_wait(&semaphore);

    //announce crossing
    printf("%s farmer %d now crossing\r\n", 
      (farmer->destination == NORTH ? "North" : "South"), 
      farmer->id);

    //sleep for step output
    msleep(1000);
    printf("10 steps\r\n");

    msleep(1000);
    printf("20 steps\r\n");

    msleep(1000);
    printf("30 steps\r\n");

    //update total
    total_crossed++;

    //announce crossed
    printf("%s farmer %d has crossed\r\n", 
      (farmer->destination == NORTH ? "North" : "South"), 
      farmer->id);

    //signal next farmer
    sem_ns_signal(&semaphore);

    //neon sign
    printf("Total Crossed: %d\r\n", total_crossed);

  }
}

void clean_up() {
  common_clean_up();

  printf("Destroying semaphore...\r\n");
  sem_ns_destroy(&semaphore);
}