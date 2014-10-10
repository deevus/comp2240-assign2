/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#ifndef COMMON_H
#define COMMON_H 

/*
	Initialises farmers and threads, then starts the threads
	with the given function fn

	Preconditions: fn is not null, north_farmers >= 0, south_farmers >= 0
	Postconditions: farmers are created and threads are running
*/
void common_init(int north_farmers, int south_farmers, void *fn);

/*
	Cancels threads and cleans up memory allocation

	Preconditions: none
	Postconditions: threads have been cancelled
*/
void common_clean_up();

/*
	Flags the running thread to be cancellable by SIGINT

	Preconditions: Call is made from running thread
	Postconditions: thread can be interrupted at program end
*/
void common_pthread_setcancel();

#endif