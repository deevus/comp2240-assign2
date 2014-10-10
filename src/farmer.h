/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/
	
#ifndef FARMER_H
#define FARMER_H
#include <stdbool.h>

typedef enum { NORTH, SOUTH, WEST } location;
typedef struct Farmer farmer_t;
struct Farmer {
	int id;
	bool has_load;
  location origin;
  location location;
  location destination;
  location next_stop;
};

#define NORTH_STR "NORTH"
#define SOUTH_STR "SOUTH"
#define WEST_STR "WEST"

/*
	Initialises the given farmer instance

	Preconditions: farmer is not null
	Postconditions: farmer is initialised with given values
*/
void farmer_init(farmer_t *farmer, int id, location origin, location destination);

#endif