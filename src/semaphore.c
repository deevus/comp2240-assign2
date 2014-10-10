/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#include "semaphore.h"
#include "atomic.h"
#include "time.h"

void semaphore_init(semaphore_t *sem, signed int count) {
	sem->lock = count;
}

void semaphore_wait(semaphore_t *sem) {
	while (atomic_compare_swap(&sem->lock, 1, 0) == 0);
}

void semaphore_signal(semaphore_t *sem) {
	atomic_inc(&sem->lock);
}