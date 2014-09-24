#include <stdlib.h>
#include <time.h>

#if _WIN32 
#include <windows.h>
#endif

int sleep(int millis) {
	#if _WIN32

	Sleep(millis);
	return 0;


	#else

	struct timespec t;
	t.tv_nsec = 1000000 * millis;

	return nanosleep(t, NULL);

	#endif
}
