#ifndef THREAD_H
#define THREAD_H

#if defined(_WIN32)
  #include <Windows.h>
	typedef PDWORD thread_id;
	typedef HANDLE thread_type;
	#define os_create_thread(t, fn, arg, id) (t = CreateThread(NULL, 0, fn, arg, 0, id))
	#define os_delete_thread(t) (CloseHandle(t->handle))
#elif defined(__unix__)
	#include <pthread.h>
	typedef pthread_t thread_type;
	#define os_create_thread(t, fn, arg, id) \
		pthread_create(&t, NULL, &fn, (void *)id); 
#endif

typedef struct Thread thread_t;
struct Thread {
	thread_id id;
	thread_type handle;
};

extern thread_t thread_create(void *start_routine, void *args);

extern void thread_destroy(thread_t *t);

#endif