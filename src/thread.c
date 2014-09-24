#include "thread.h"
#include <time.h>

thread_t thread_create(void *start_routine, void *args) {
	thread_t t;

	os_create_thread(t.handle, start_routine, args, t.id);

	return t;
}

void thread_destroy(thread_t *thread) {
	os_delete_thread(thread);
}
