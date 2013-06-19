#ifndef SLEEP_H
#define SLEEP_H
#include <time.h>

void msleep(int milliseconds)
{
	struct timespec time, time2;
	time.tv_sec = 0;
	time.tv_nsec = 17000000;

	nanosleep(&time, &time2);
}

#endif
