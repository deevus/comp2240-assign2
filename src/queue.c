#include "queue.h"

void queue_init(queue_t *queue) {
	linkedlist_init(&queue->list);
}

void queue_enqueue(queue_t *queue, void *data) {
	linkedlist_insert(&queue->list, data);
}

void queue_dequeue(queue_t *queue) {
	void* data = linkedlist_gethead(&queue->list);
	linkedlist_remove(&queue->list, data);
}

void *queue_front(const queue_t *queue) {
	return linkedlist_gethead(&queue->list);
}

bool queue_isempty(const queue_t *queue) {
	return linkedlist_isempty(&queue->list);
}

void queue_destroy(queue_t *queue) {
	linkedlist_destroy(&queue->list);
}