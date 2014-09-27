#include "semaphore.h"
#include "atomic.h"
#include "time.h"

extern void semaphore_init(semaphore_t *sem) {
	sem->lock = 0;
}

extern void semaphore_wait(semaphore_t *sem) {
	while (atomic_compare_swap(&sem->lock, 0, 1) == 1);
}

extern void semaphore_signal(semaphore_t *sem) {
	atomic_dec(&sem->lock);
}