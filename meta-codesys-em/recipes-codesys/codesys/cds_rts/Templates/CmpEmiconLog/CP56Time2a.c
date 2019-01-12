#include "CP56Time2a.h"

void time_to_CP56Time2a(date_and_time *st, uint8_t *cp56t)
{
	uint16_t m;
	m = st->msec + 1000 * st->seconds;
	cp56t[0] = m & 0xFF;
	cp56t[1] = (m & 0xFF00)>>8;
	cp56t[2] = st->minutes & 0x00FF;  // add valid flag and genuine flag
	cp56t[3] = st->hour & 0x00FF;    // add summer flag
	cp56t[4] = ((st->day_of_week%7)&0x03)<<5 | (st->day&0x1F);
	cp56t[5] = st->month & 0x0F;
	cp56t[6] = st->year - 2000;
}

void CP56Time2a_to_time(CP56Time2a cp56t, date_and_time *st)
{
	bool valid;
	bool genuine;
	bool summer;

	uint16_t mili = cp56t[0] | cp56t[1]<<8;
	st->seconds = mili / 1000;
	st->msec = mili - st->seconds*1000;

	if(cp56t[2] & 0x40)
		genuine = true;
	else
		genuine = false;

	if(cp56t[2] & 0x80)
		valid = true;
	else
		valid = false;

	st->minutes = cp56t[2] & 0x3F;
	st->hour = cp56t[3] & 0x1F;

	if(cp56t[3] & 0x80)
		summer = true;
	else
		summer = false;

	st->day = cp56t[4] & 0x1F;
	st->day_of_week = (cp56t[4] & 0xE0 ) >> 5;
	if(st->day_of_week)   // if zero day of week not used.   
		st->day_of_week = (st->day_of_week + 1)%7;
	st->month = cp56t[5] & 0x0F;
	st->year = 2000 + (cp56t[6] & 0x7F);
}