/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#include "question4.h"
#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include "time.h"
#include "monitor.h"
#include "common.h"
#include "bridge.h"
#include "farmer.h"

static bridge_t north_south_bridge;
static bridge_t north_west_bridge;
static bridge_t south_west_bridge;

static mutex_t west_island;
static condition_t waiting_north_condition;
static condition_t waiting_south_condition;

static volatile bool waiting_north;
static volatile bool waiting_south;

static int total_crossed_north_south;
static int total_crossed_north_west;
static int total_crossed_south_west;

void run(int north_farmers, int south_farmers) {
	bridge_init(&north_south_bridge, NORTH, SOUTH);
	bridge_init(&north_west_bridge, NORTH, WEST);
	bridge_init(&south_west_bridge, SOUTH, WEST);

	mutex_init(&west_island);
	condition_init(&waiting_south_condition);
	condition_init(&waiting_north_condition);

	waiting_south = waiting_north = false;

	total_crossed_south_west 
		= total_crossed_north_west 
		= total_crossed_north_south 
		= 0;

  common_init(north_farmers, south_farmers, &do_work);
}

static void neon_sign(int *total) {
	if (total == &total_crossed_north_south) {
		printf("North South Total: %d\r\n", *total);
	}
	else if (total == &total_crossed_north_west) {
		printf("North West Total: %d\r\n", *total);
	}
	else if (total == &total_crossed_south_west) {
		printf("South West Total: %d\r\n", *total);
	}
}

void do_work(farmer_t *farmer) {
//allow thread to be cancelled
  common_pthread_setcancel();
  
  //loop forever
  while (1) {
  	bridge_t *bridge = &north_south_bridge;
  	int *bridge_total = &total_crossed_north_south;

  	//north-south bridge valid but in use
  	if (farmer_can_cross(farmer, &north_south_bridge) && bridge_in_use(&north_south_bridge)) {
  		//then go west
	  	bridge = farmer->location == NORTH ? &north_west_bridge : &south_west_bridge;
  		bridge_total = farmer->location == NORTH ? &total_crossed_north_west : &total_crossed_south_west;	
  	}
  	//north-south not valid
		//farmer is already at west
  	else if (!farmer_can_cross(farmer, &north_south_bridge)) {
  		//so they can cross when ready
	  	if (farmer->location == WEST) {
	  		//need to cross the island

	  		//determine what side of the island the farmer is on
	  		location came_from = farmer->has_load ? farmer->origin : farmer->destination;
	  		volatile bool *b_waiting = came_from == NORTH ? &waiting_north : &waiting_south;
	  		condition_t *wait_c = came_from == NORTH ? &waiting_north_condition : &waiting_south_condition;

	  		//announce arrival
	  		printf("%s farmer %d has arrived on the %s side of WEST island\r\n",
	  			farmer->origin == NORTH ? "NORTH" : "SOUTH",
	  			farmer->id,
	  			came_from == NORTH ? "NORTH" : "SOUTH");	

	  		//is someone waiting?
	  		if (*b_waiting) {
	  			//announce meeting another farmer
	  			printf("%s farmer %d has met another farmer on the %s side of WEST island\r\n",
		  			farmer->origin == NORTH ? "NORTH" : "SOUTH",
		  			farmer->id,
		  			came_from == NORTH ? "NORTH" : "SOUTH");	

	  			//signal waiting farmer to go
	  			monitor_signal(wait_c);
	  		}
	  		else {

	  			//atomically set b_waiting
		  		mutex_acquire(&west_island);
		  		*b_waiting = true;
		  		mutex_release(&west_island);

		  		printf("%s farmer %d is waiting for another farmer on the %s side of WEST island\r\n",
		  			farmer->origin == NORTH ? "NORTH" : "SOUTH",
		  			farmer->id,
		  			came_from == NORTH ? "NORTH" : "SOUTH");
		  		monitor_wait(&west_island, wait_c);

		  		//announce no longer waiting
					printf("%s farmer %d can now cross from %s side of WEST island\r\n",
		  			farmer->origin == NORTH ? "NORTH" : "SOUTH",
		  			farmer->id,
		  			came_from == NORTH ? "NORTH" : "SOUTH");	

	  			//atomically unset b_waiting
		  		mutex_acquire(&west_island);
		  		*b_waiting = false;
		  		mutex_release(&west_island);
		  	}

	  		//have load - go to dest
	  		if (farmer->has_load) {
		  		bridge = farmer->destination == NORTH ? &north_west_bridge : &south_west_bridge;
		  		bridge_total = farmer->destination == NORTH ? &total_crossed_north_west : &total_crossed_south_west;
	  		}

	  		//dont have load - go to origin
	  		else  {
	  			bridge = farmer->origin == NORTH ? &north_west_bridge : &south_west_bridge;
		  		bridge_total = farmer->origin == NORTH ? &total_crossed_north_west : &total_crossed_south_west;
	  		}
	  	}


	  }
  	else {
  		//which bridge to cross?
  		bridge_t *west_bridge = farmer->location == NORTH ? &north_west_bridge : &south_west_bridge; 

  		//compare queues of adjacent bridges
	  	bridge = bridge_num_waiting(west_bridge) < bridge_num_waiting(&north_south_bridge) ? west_bridge : &north_south_bridge;

	  	//get pointer to bridge total
  		bridge_total = bridge == &north_south_bridge 
	  		? &total_crossed_north_south 
	  		: bridge == &north_west_bridge 
		  		? &total_crossed_north_west 
		  		: &total_crossed_north_south;
  	}

  	bridge_cross(bridge, farmer);

  	(*bridge_total)++;
  	neon_sign(bridge_total);
  }
}

void clean_up() {
  common_clean_up();

  printf("Destroying bridges...\r\n");
  bridge_destroy(&north_south_bridge);
  bridge_destroy(&north_west_bridge);
  bridge_destroy(&south_west_bridge);
}