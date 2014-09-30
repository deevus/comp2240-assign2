#ifndef MONITOR_H
#define MONITOR_H 

#include "semaphore_nostarve.h"
#include "mutex.h"

typedef struct Condition condition_t;
struct Condition {
  volatile int queued;
  mutex_t queue_lock;
  semaphore_t sem;
};

extern void condition_init(condition_t *cond);

extern void monitor_wait(mutex_t *mutex, condition_t *cond);

extern void monitor_signal(condition_t *cond);

extern void monitor_signal_all(condition_t *cond);

#endif