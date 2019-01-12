#ifndef _EMICONLOG_H_
#define _EMICONLOG_H_

/*
 * Маркировка первых двух байт (init_mark), означающее инициализацию буфера
 * из мусора LOG_INIT_MARK, либо буфер занят записью/чтенеием LOG_INIT_MARK_BUSY.
 */
#define LOG_INIT_MARK 0x55aa
#define LOG_INIT_MARK_BUSY 0x65aa

/* 
 * Используется для определения состояния буфера:
 * если указатели начала и конца одинаковы и указывают на NONE, то буфер пуст.
 * Считается, что тип фрейма на который указывает указатель начала не может быть
 * равен NONE. В данном случае 0. 
 */
#define NONE 0 

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

#define FRAME_TYPE_OWN_EVENT 1
#define FRAME_TYPE_TS 2
#define FRAME_TYPE_TI 3

/*
 * Маркировка первых двух байт (init_mark), означающее инициализацию буфера
 * из мусора LOG_INIT_MARK, либо буфер занят записью/чтенеием LOG_INIT_MARK_BUSY.
 */
#define LOG_INIT_MARK 0x55aa
#define LOG_INIT_MARK_BUSY 0x65aa

/*
 * Структуры кадров записи для каждого типа событий.
 * Внимание! Структуры обязатяельно должны быть объявлены между
 * #pragma pack(push, 1) и #pragma pack(pop). Ничего между структурами объявлять
 * не следует. Иначе выравнивание может испортить жизнь.
 */
#pragma pack(push, 1)
typedef struct own_event_frame {
	uint16_t event_id;
	CP56Time2a datetime;	
} own_event_frame;

typedef struct ts_frame {
	uint8_t class_id;
	uint8_t address[3];
	uint8_t value;
	CP56Time2a datetime;
} ts_frame;

typedef struct ti_frame {
	uint8_t class_id;
	uint8_t address[3];
	uint8_t value[4];
	uint8_t quality;
	CP56Time2a datetime;
} ti_frame;
#pragma pack(pop)

#define SIZE_OF_OWN_EVENT sizeof(own_event_frame)
#define SIZE_OF_TS sizeof(ts_frame)
#define SIZE_OF_TI sizeof(ti_frame)

/*
 * Фрейм в памяти теледанных отличается старшим битом равным 0.
 * Между собой (TI и TS фреймы) отличаются по значению.
 * CLASS_OF_TI содержит значения первого байта фрейма TI
 * по которым можно разделить TS от TI
 */  
uint8_t CLASS_OF_TI[] = {45, 58};
uint8_t CLASS_OF_TS[] = {1, 3, 30, 31};



void get_actual_time(date_and_time *data);

#endif /*_EMICONLOG_H_*/