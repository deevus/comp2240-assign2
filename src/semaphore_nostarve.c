/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#include "semaphore_nostarve.h"
#include "atomic.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

static volatile int wait_id = 1;

static void sem_queue(semaphore_t *sem, signed int *id);
static void sem_dequeue(semaphore_t *sem);

void sem_ns_init(semaphore_t *sem, signed int count) {
	queue_init(&sem->blocked);
	sem->critlock = count;
	sem->queuelock = 0;
	sem->next_id = 0;

	pthread_mutex_init(&sem->lock, NULL);
	pthread_cond_init(&sem->cond, NULL);
}

void sem_ns_destroy(semaphore_t *sem) {
	queue_destroy(&sem->blocked);
}

int sem_ns_wait(semaphore_t *sem) {

	//do we need to queue?
	if (atomic_dec(&sem->critlock) < 1) {
		//get id
		int *id = malloc(sizeof(int));
		*id = wait_id++;

		//queue thread
		sem_queue(sem, id);

		//wait until turn
		while (pthread_cond_wait(&sem->cond, &sem->lock) && sem->next_id != *id);
	}
	
	//run now
	return 0;
}

int sem_ns_signal(semaphore_t *sem) {
	sem_dequeue(sem);
	atomic_inc(&sem->critlock);
	return 0;
}

static void sem_queue(semaphore_t *sem, signed int *id) {
	//get lock
	while (atomic_compare_swap(&sem->queuelock, 0, 1) == 1);

	queue_enqueue(&sem->blocked, id);

	//release lock
	atomic_dec(&sem->queuelock);
}

static void sem_dequeue(semaphore_t *sem) {
	//get lock
	while (atomic_compare_swap(&sem->queuelock, 0, 1) == 1);

	//crit section
	if (!queue_isempty(&sem->blocked)) {
		int *id = (int *)queue_front(&sem->blocked);

		//set next id
		sem->next_id = *id;
		pthread_cond_signal(&sem->cond);

		//dequeue it
		queue_dequeue(&sem->blocked);
		free(id);
	}
	else {
		sem->next_id = 0;
	}

	//release lock
	atomic_dec(&sem->queuelock);
}