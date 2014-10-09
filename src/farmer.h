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

void farmer_init(farmer_t *farmer, int id, location origin, location destination);

#endif