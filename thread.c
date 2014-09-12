#include "thread.h"

thread_t thread_create(void *start_routine, void *args) {
	thread_t t;

	os_create_thread(t.handle, start_routine, 0, t.id);

	return t;
}

void thread_destroy(thread_t *thread) {
	os_delete_thread(thread);
}

#if defined(_WIN32) 
	void sleep(int sec) {
	    HANDLE timer; 
	    LARGE_INTEGER ft; 

	    ft.QuadPart = -(10000000*sec); // convert to sec

	    timer = CreateWaitableTimer(NULL, TRUE, NULL); 
	    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
	    WaitForSingleObject(timer, INFINITE); 
	    CloseHandle(timer); 
	}
#endif

