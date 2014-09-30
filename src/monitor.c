#include "monitor.h"
#include "atomic.h"
#include <stdio.h>

void condition_init(condition_t *cond) {
  cond->queued = 0;
  mutex_init(&cond->queue_lock);
  sem_ns_init(&cond->sem, 1);
}

void monitor_wait(mutex_t *mutex, condition_t *cond) {
  mutex_release(mutex);

  atomic_inc(&cond->queued);
  sem_ns_wait(&cond->sem);

  mutex_acquire(mutex);
}

void monitor_signal(condition_t *cond) {
  mutex_acquire(&cond->queue_lock);

  if (cond->queued > 0) {
    cond->queued--;
    sem_ns_signal(&cond->sem);
  }

  mutex_release(&cond->queue_lock);
}

void monitor_signal_all(condition_t *cond) {
  mutex_acquire(&cond->queue_lock);

  while (cond->queued > 0) {
    cond->queued--;
    sem_ns_signal(&cond->sem);
  }

  mutex_release(&cond->queue_lock);
}