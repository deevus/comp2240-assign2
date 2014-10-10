/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#ifndef MONITOR_H
#define MONITOR_H 

#include "semaphore_nostarve.h"
#include "mutex.h"

typedef struct Condition condition_t;
struct Condition {
  volatile int queued;
  mutex_t queue_lock;
  semaphore_t sem;
};

/*
  Initialise condition variable

  Preconditions: cond is not null
  Postconditions: condition is intialised to default values
*/
void condition_init(condition_t *cond);

/*
	Wait on a given condition, blocking the thread until
	it is signaled using monitor_signal

	Preconditions: mutex and cond are not null
	Postconditions: none
*/
void monitor_wait(mutex_t *mutex, condition_t *cond);

/*
	Signal a given condition, releasing the next thread
	that was waiting on the condition

	Preconditions: cond is not null
	Postconditions: A thread that was waiting (if any)
		on the condition will be signaled.
*/
void monitor_signal(condition_t *cond);

/*
	Signal all threads waiting on a condition.

	Precondition: cond is not null
	Postcondition: All threads that were waiting on the 
		condition will be signaled.
*/
void monitor_signal_all(condition_t *cond);

#endif