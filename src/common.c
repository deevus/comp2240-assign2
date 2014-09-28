#include <stdlib.h>
#include <pthread.h>
#include "common.h"
#include "farmer.h"

void common_init(int north_farmers, int south_farmers, void *fn) {
  int num_threads = north_farmers + south_farmers;
  int north_id, south_id;
  north_id = south_id = 0;
  pthread_t threads[num_threads];

  for (int i = 0; i < num_threads; ++i) {

    farmer_t *farmer = malloc(sizeof(farmer_t));
    if (north_farmers > 0) {
      farmer->id = ++north_id;
      farmer->direction = NORTH;
      north_farmers--;
    }
    else {
      farmer->id = ++south_id;
      farmer->direction = SOUTH;
      south_farmers--;
    }

    pthread_create(&threads[i], NULL, fn, farmer);

  } 

  for (int i = 0; i < num_threads; ++i)
  {
    pthread_join(threads[i], NULL);
  }

  pthread_exit(NULL); 
}
