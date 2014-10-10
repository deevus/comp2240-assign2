/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#ifndef SEMAPHORE_NOSTARVE_H
#define SEMAPHORE_NOSTARVE_H

#include <pthread.h>
#include "queue.h"

typedef struct semaphore semaphore_t;
struct semaphore {
	volatile int critlock;
	volatile int queuelock;
	volatile int next_id;
	queue_t blocked;

	pthread_mutex_t lock;
	pthread_cond_t cond;
};

/*
	Initialise semaphore

	Preconditions: sem is not null
	Postconditions: semaphore is initialised to given count
*/
void sem_ns_init(semaphore_t *sem, signed int count);

/*
	Wait on given semaphore

	Preconditions: sem is not null
	Postconditions: none
*/
int sem_ns_wait(semaphore_t *sem);

/*
	Signal given semaphore

	Preconditions: sem is not null
	Postconditions: next thread will run
*/
int sem_ns_signal(semaphore_t *sem);

/*
	Clean up semaphore memory allocation

	Preconditions: sem is not null
	Postconditions: sem is no longer initialised
*/
void sem_ns_destroy(semaphore_t *sem);

#endif