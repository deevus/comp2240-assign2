#ifndef BRIDGE_H
#define BRIDGE_H 
#include "mutex.h"
#include "farmer.h"
#include <stdbool.h>

typedef struct Bridge bridge_t;
struct Bridge {
	mutex_t lock;
	location island_1;
	location island_2;
};

void bridge_init(bridge_t *bridge, location island_1, location island_2);

bool bridge_in_use(bridge_t *bridge);

void bridge_cross(bridge_t *bridge, farmer_t *farmer);

void bridge_destroy(bridge_t *bridge);

bool farmer_can_cross(farmer_t *farmer, bridge_t *bridge);

#endif