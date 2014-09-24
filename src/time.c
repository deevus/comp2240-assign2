#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#if _WIN32 
#include <windows.h>
#endif

int msleep(int millis) {
	#if _WIN32

	Sleep(millis);
	return 0;

	#else

	return usleep(millis * 1000L);

	#endif
}
