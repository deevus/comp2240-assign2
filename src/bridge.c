#include "bridge.h"
#include "time.h"
#include <stdio.h>

void bridge_init(bridge_t *bridge, location island_1, location island_2) {
	mutex_init(&bridge->lock);

	bridge->island_1 = island_1;
	bridge->island_2 = island_2;
}

bool bridge_in_use(bridge_t *bridge) {
	return bridge->lock.critlock == 0;
}

static void farmer_cross(bridge_t *bridge, farmer_t *farmer) {

	location destination = farmer->location == bridge->island_1 ? bridge->island_2 : bridge->island_1;

	//generate strings for printing
	char *origin_str = farmer->origin == NORTH ? "NORTH" : "SOUTH";
	char *next_str = destination == NORTH ? "NORTH Island" : destination == SOUTH ? "SOUTH Island" : "WEST Island";
	char *location_str = farmer->location == NORTH ? "NORTH Island" : farmer->location == SOUTH ? "SOUTH Island" : "WEST Island";

	//print crossing information
	printf("%s farmer %d now %s from %s to %s\r\n", origin_str, farmer->id, (farmer->has_load ? "crossing" : "returning"), location_str, next_str);

	//init sleep variables
	int sleep_base = 500;
	int step_base = 5;
	int multiplier = farmer->has_load ? 2 : 1;

	//sleep farmer for 3 intervals
	for (int i = 1; i <= 3; i++) {
	  msleep(sleep_base * multiplier);
	  printf("%s farmer %d has progressed %d steps from %s to %s\r\n", origin_str, farmer->id, step_base * multiplier * i, location_str, next_str);
	}

  printf("%s farmer %d has %s to %s\r\n", 
    origin_str, 
    farmer->id,
    (farmer->has_load ? "crossed" : "returned"),
    next_str);

	//update new location
	farmer->location = farmer->location == bridge->island_1 ? bridge->island_2 : bridge->island_1;

	//has the farmer delivered its load?
	if (farmer->location == farmer->destination) {
	  printf("%s farmer %d has delivered its cargo to %s!!!\r\n", origin_str, farmer->id, next_str);
		farmer->has_load = false;
	}
	else if (farmer->location == farmer->origin) {
		farmer->has_load = true;
	}
}

void bridge_cross(bridge_t *bridge, farmer_t *farmer) {
	mutex_acquire(&bridge->lock);

	farmer_cross(bridge, farmer);

	mutex_release(&bridge->lock);
}

void bridge_destroy(bridge_t *bridge) {
	mutex_destroy(&bridge->lock);
}

bool farmer_can_cross(farmer_t *farmer, bridge_t *bridge) {
	//is the farmer adjacent to this bridge
	return farmer->location == bridge->island_1 || farmer->location == bridge->island_2;
}
