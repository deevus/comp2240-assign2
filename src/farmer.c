#include "farmer.h"

void farmer_init(farmer_t *farmer, int id, location origin, location destination) {
	//get farmer id
	farmer->id = id;

	//set origin
	farmer->origin = origin;

	//set current location to origin
	farmer->location = origin;

	//set destination
	farmer->destination = destination;

	//new farmer has a load
	farmer->has_load = true;
}
