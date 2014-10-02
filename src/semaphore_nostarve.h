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

extern void sem_ns_init(semaphore_t *sem, signed int count);

extern int sem_ns_wait(semaphore_t *sem);

extern int sem_ns_signal(semaphore_t *sem);

extern void sem_ns_destroy(semaphore_t *sem);

#endif