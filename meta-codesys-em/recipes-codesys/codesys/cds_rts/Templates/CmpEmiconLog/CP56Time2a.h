#ifndef _CP56Time2a_h_
#define _CP56Time2a_h_

typedef uint8_t CP56Time2a[7];

typedef struct date_and_time {
	uint16_t year;
	uint16_t month;
	uint16_t day_of_week;
	uint16_t day;
	uint16_t hour;
	uint16_t minutes;
	uint16_t seconds;
	uint16_t msec;
} date_and_time;

void CP56Time2a_to_time(uint8_t *cp56t, date_and_time *st);
void time_to_CP56Time2a(date_and_time *st, uint8_t *cp56t);

#endif /*_CP56Time2a_h_*/