#ifndef SEMAPHORE_H
#define SEMAPHORE_H

typedef struct semaphore semaphore_t;
struct semaphore {
	volatile int lock;
};

extern void semaphore_init(semaphore_t *sem);

extern void semaphore_wait(semaphore_t *sem);

extern void semaphore_signal(semaphore_t *sem);

#endif