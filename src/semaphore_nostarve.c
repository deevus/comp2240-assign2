#include "semaphore_nostarve.h"
#include "atomic.h"
#include <stdio.h>
#include <stdlib.h>
#include "time.h"

static volatile int wait_id = 0;

static void sem_queue(semaphore_t *sem, signed int *id);
static void sem_dequeue(semaphore_t *sem);

void sem_ns_init(semaphore_t *sem, signed int count) {
	queue_init(&sem->blocked);
	sem->critlock = count;
	sem->queuelock = 0;
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
		while (atomic_compare_swap(&sem->next_id, *id, *id) != *id);
	}

	//run now
	return 0;
}

int sem_ns_signal(semaphore_t *sem) {
	sem_dequeue(sem);
	//atomic_inc(&sem->critlock);
	return 0;
}

static void sem_queue(semaphore_t *sem, signed int *id) {
	//get lock
	while (atomic_compare_swap(&sem->queuelock, 0, 1) == 1);

	//crit section
	//set this as next if queue is empty and not in crit section
	//if (queue_isempty(&sem->blocked) && atomic_compare_swap(&sem->critlock, 1 ,1) == 1) {
	if (queue_isempty(&sem->blocked)) {
		sem->next_id = *id;
	}
	//otherwise queue it
	else {
		queue_enqueue(&sem->blocked, id);
	}

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