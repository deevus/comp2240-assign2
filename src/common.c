/**
  Simon Hartcher
  C3185790

  COMP2240 Assignment 2
**/

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "common.h"
#include "farmer.h"

static int num_threads;
static pthread_t *thread_ptr;
static farmer_t **farmer_ptr;

void common_init(int north_farmers, int south_farmers, void *fn) {
  //calc the number of threads to spawn
  num_threads = north_farmers + south_farmers;

  //init id counters
  int north_id, south_id;
  north_id = south_id = 0;

  //create thread array
  pthread_t threads[num_threads];
  thread_ptr = threads;

  //create farmer array
  farmer_t *farmers[num_threads];
  farmer_ptr = farmers;

  //spawn farmers and threads
  for (int i = 0; i < num_threads; ++i) {

    //allocate memory for farmer
    farmers[i] = malloc(sizeof(farmer_t));

    //spawn north then south farmers in that order
    if (north_farmers > 0) {
      //spawn north farmer
      farmer_init(farmers[i], ++north_id, NORTH, SOUTH);
      north_farmers--;
    }
    else {
      //spawn south farmer
      farmer_init(farmers[i], ++south_id, SOUTH, NORTH);
      south_farmers--;
    }

    //spawn the thread
    pthread_create(&threads[i], NULL, fn, farmers[i]);

  } 

  //join threads into main thread to stop
  //main thread from terminating
  for (int i = 0; i < num_threads; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  //exit when done
  pthread_exit(NULL); 
}

void common_clean_up() {
  //free farmers and threads
  printf("Cancelling threads...\r\n");
  for (int i = 0; i < num_threads; ++i)
  {
    //cancel the thread
    pthread_cancel(*(thread_ptr + i));
  }
}

void common_pthread_setcancel() {
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
}
