#ifndef MUTEX_H
#define MUTEX_H 

#include "semaphore_nostarve.h"

typedef semaphore_t mutex_t;

#define mutex_init(m) sem_ns_init(m, 1)
#define mutex_acquire(m) sem_ns_wait(m)
#define mutex_release(m) sem_ns_signal(m)
#define mutex_destroy(m) sem_ns_destroy(m)

#endif