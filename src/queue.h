/**
	Simon Hartcher
	C3185790

	COMP2240 Assignment 2
**/

#ifndef QUEUE_H
#define QUEUE_H

#include "linkedlist.h"
#include <stdbool.h>

typedef struct queue queue_t;
struct queue {
	linkedlist_t list;
};

void queue_init(queue_t *queue);

void queue_enqueue(queue_t *queue, const void *data);

void queue_dequeue(queue_t *queue);

const void *queue_front(const queue_t *queue);

const bool queue_isempty(const queue_t *queue);

void queue_destroy(queue_t *queue);

const int queue_getsize(const queue_t *queue);

#endif