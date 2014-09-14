#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"
#include <stdbool.h>

typedef struct queue queue_t;
struct queue {
	linkedlist_t list;
};

extern void queue_init(queue_t *queue);

extern void queue_enqueue(queue_t *queue, void *data);

extern void queue_dequeue(queue_t *queue);

extern void *queue_front(const queue_t *queue);

extern bool queue_isempty(const queue_t *queue);

extern void queue_destroy(queue_t *queue);

#endif