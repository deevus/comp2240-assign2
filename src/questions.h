/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

/*
	Defines the prototype functions that are used
	in every question
*/
#ifndef QUESTIONS_H
#define QUESTIONS_H

#include "farmer.h"

/*
	Runs the program according to
	question specifications

	Preconditions: Parameter values must be >= 0
	Postconditions: None
*/
extern void run(int north_farmers, int south_farmers);

/*
	Is called for each running thread determined by
	the parameters passed to run

	Preconditions: Parameter farmer must not be NULL
	Postconditions: None
*/
extern void do_work(farmer_t *farmer);

/*
	Cleans up any memory

	Preconditions: Method run has been called
	Postconditions: Memory allocation for the program has been cleared
*/
extern void clean_up();

#endif