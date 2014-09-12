#include "semaphore.h"

extern void semaphore_init(semaphore_t *sem, unsigned int value) {
	*sem = (semaphore_t)value;
}

extern void semaphore_wait(semaphore_t *sem) {
	while (*sem <= 0);

	atomic_dec(sem);
}

extern void semaphore_signal(semaphore_t *sem) {
	atomic_inc(sem);
}