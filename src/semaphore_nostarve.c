#include "semaphore_nostarve.h"
#include "atomic.h"
#include <stdio.h>

static void sem_queue(semaphore_t *sem, signed int id);
static void sem_dequeue(semaphore_t *sem);

void sem_ns_init(semaphore_t *sem) {
	queue_init(&sem->blocked);
	sem->critlock = 0;
	sem->queuelock = 0;
}

int sem_ns_wait(semaphore_t *sem, signed int id) {
	//queue thread
	sem_queue(sem, id);

	//wait until turn
	while (atomic_compare_swap(&sem->next_id, id, id) != id);
	//get lock
	while (atomic_compare_swap(&sem->critlock, 0, 1) == 1);
}

int sem_ns_signal(semaphore_t *sem) {
	sem_dequeue(sem);
	atomic_dec(&sem->critlock);
}

static void sem_queue(semaphore_t *sem, signed int id) {
	//get lock
	while (atomic_compare_swap(&sem->queuelock, 0, 1) == 1);

	//crit section
	//set this as next if queue is empty
	if (queue_isempty(&sem->blocked)) {
		sem->next_id = id;
	}
	//otherwise queue it
	else {
		printf("Queued %d\r\n", id);
		queue_enqueue(&sem->blocked, &id);
	}

	//release lock
	atomic_dec(&sem->queuelock);
}

static void sem_dequeue(semaphore_t *sem) {
	//get lock
	while (atomic_compare_swap(&sem->queuelock, 0, 1) == 1);

	//crit section
	if (!queue_isempty(&sem->blocked)) {
		//set next id
		sem->next_id = *(int *)queue_front(&sem->blocked);

		//dequeue it
		queue_dequeue(&sem->blocked);
	}
	else {
		sem->next_id = 0;
	}

	//release lock
	atomic_dec(&sem->queuelock);
}