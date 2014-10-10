/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct semaphore semaphore_t;
struct semaphore {
	volatile int lock;
};

/*
	Initialise semaphore

	Preconditions: sem is not null
	Postconditions: semaphore is initialised to given count
*/
void semaphore_init(semaphore_t *sem, signed int count);

/*
	Wait on given semaphore

	Preconditions: sem is not null
	Postconditions: none
*/
void semaphore_wait(semaphore_t *sem);

/*
	Signal given semaphore

	Preconditions: sem is not null
	Postconditions: next thread will run
*/
void semaphore_signal(semaphore_t *sem);

#endif