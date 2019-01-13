// #include <sys/time.h>
#include <time.h>
#include "emiconlog.h"

/*
 * Считывает текущее время с точностью до милисекунд
 */
void get_actual_time(date_and_time *dt)
{
	struct timeval tv;
	struct tm *tm;

	gettimeofday(&tv, NULL);
	tm = localtime(&tv.tv_sec);

	// Add 1900 to get the right year value
	// read the manual page for localtime()
	dt->year = tm->tm_year + 1900;
	// Months are 0 based in struct tm
	dt->month = tm->tm_mon + 1;
	dt->day_of_week = tm->tm_wday;
	dt->day = tm->tm_mday;
	dt->hour = tm->tm_hour;
	dt->minutes = tm->tm_min;
	dt->seconds = tm->tm_sec;
	dt->msec = (int) (tv.tv_usec / 1000);
}