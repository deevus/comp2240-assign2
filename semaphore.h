#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#if defined(_WIN32)
	#include <Windows.h>
	#define atomic_inc(ptr) (InterlockedIncrement(ptr))
	#define atomic_dec(ptr) (InterlockedDecrement(ptr))
#elif defined(__unix__)
	#define atomic_inc(ptr) (__sync_fetch_and_add(ptr, 1))
	#define atomic_dec(ptr) (__sync_fetch_and_sub(ptr, 1))
#endif

typedef volatile long semaphore_t;

extern void semaphore_init(semaphore_t *sem, unsigned int value);

extern void semaphore_wait(semaphore_t *sem);

extern void semaphore_signal(semaphore_t *sem);

#endif