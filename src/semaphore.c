#include "semaphore.h"
#include "atomic.h"
#include "time.h"

extern void semaphore_init(semaphore_t *sem, signed int count) {
	sem->lock = count;
}

extern void semaphore_wait(semaphore_t *sem) {
	while (atomic_compare_swap(&sem->lock, 1, 0) == 0);
}

extern void semaphore_signal(semaphore_t *sem) {
	atomic_inc(&sem->lock);
}