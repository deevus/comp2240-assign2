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

/*
	Initialises a bridge_t structure

	Preconditions: bridge is not null. 
	Postconditions: bridge object is initialised to default values
*/
void bridge_init(bridge_t *bridge, location island_1, location island_2);

/*
	Returns a boolean value determining whether the bridge is 
	currently in use

	Preconditions: bridge is not null
	Postconditions: none.
*/
bool bridge_in_use(bridge_t *bridge);

/*
	Farmer crosses the given bridge. The farmer will enter a queue
	and will be blocked until their turn.

	Preconditions: bridge and farmer are not null.
	Postconditions: farmer will be updated with a new location
		and load status if the load was delivered.
*/
void bridge_cross(bridge_t *bridge, farmer_t *farmer);

/*
	Frees allocated memory for bridge

	Preconditions: bridge is not null
	Postconditions: memory allocated to bridge is freed
*/
void bridge_destroy(bridge_t *bridge);

/*
	Returns boolean determining whether farmer can cross
	given bridge. If the farmer is not in a location able
	to cross it will return false, otherwise true.

	Preconditions: farmer and bridge are not null
	Postconditions: none
*/
bool farmer_can_cross(farmer_t *farmer, bridge_t *bridge);

#endif