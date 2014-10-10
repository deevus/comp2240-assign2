/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#include "queue.h"
#include <string.h>

void queue_init(queue_t *queue) {
	linkedlist_init(&queue->list);
}

void queue_enqueue(queue_t *queue, const void *data) {
	linkedlist_insert(&queue->list, data);
}

void queue_dequeue(queue_t *queue) {
	const void *data = linkedlist_gethead(&queue->list);
	linkedlist_remove(&queue->list, data);
}

const void *queue_front(const queue_t *queue) {
	return linkedlist_gethead(&queue->list);
}

const bool queue_isempty(const queue_t *queue) {
	return linkedlist_isempty(&queue->list);
}

void queue_destroy(queue_t *queue) {
	linkedlist_destroy(&queue->list);
}

const int queue_getsize(const queue_t *queue) {
  return linkedlist_getsize(&queue->list);
}
