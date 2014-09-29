#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include "common.h"
#include "farmer.h"

static int num_threads;
static pthread_t *thread_ptr;
static farmer_t **farmer_ptr;

void common_init(int north_farmers, int south_farmers, void *fn) {
  num_threads = north_farmers + south_farmers;
  int north_id, south_id;
  north_id = south_id = 0;

  pthread_t threads[num_threads];
  thread_ptr = threads;

  farmer_t *farmers[num_threads];
  farmer_ptr = farmers;

  for (int i = 0; i < num_threads; ++i) {

    farmers[i] = malloc(sizeof(farmer_t));
    if (north_farmers > 0) {
      farmers[i]->id = ++north_id;
      farmers[i]->direction = NORTH;
      north_farmers--;
    }
    else {
      farmers[i]->id = ++south_id;
      farmers[i]->direction = SOUTH;
      south_farmers--;
    }

    pthread_create(&threads[i], NULL, fn, farmers[i]);

  } 

  for (int i = 0; i < num_threads; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  pthread_exit(NULL); 
}

void common_clean_up() {
  printf("Cancelling threads and farmers...\r\n");
  for (int i = 0; i < num_threads; ++i)
  {
    //cancel the thread
    pthread_cancel(*(thread_ptr + i));

    //then free the associated farmer
    free((farmer_ptr + i));
  }
}

void common_pthread_setcancel() {
  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
}
