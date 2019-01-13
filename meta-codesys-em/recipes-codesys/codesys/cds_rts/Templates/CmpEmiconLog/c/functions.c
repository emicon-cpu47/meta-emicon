

#include "stdint.h"
#include "stddef.h"
#include "errno.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

/* 
 * Используется для определения состояния буфера:
 * если указатели начала и конца одинаковы и указывают на NONE, то буфер пуст.
 * Считается, что тип фрейма на который указывает указатель начала не может быть
 * равен NONE. В данном случае 0. 
 */
#define NONE 0 
#define ER_OK 0
#define ER_FAILURE -1
// зарезервированное id события очистки буфера 
#define OWN_EVENT_ID_CLR 0

const int is_bigendian_i = 1;
#define is_bigendian() ( (*(uint8_t*)&is_bigendian_i) == 0 )

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

#define FRAME_TYPE_OWN_EVENT 1
#define FRAME_TYPE_TS 2
#define FRAME_TYPE_TI 3

#define SIZE_OF_OWN_EVENT sizeof(own_event_frame)
#define SIZE_OF_TS sizeof(ts_frame)
#define SIZE_OF_TI sizeof(ti_frame)


uint8_t *p_log_buff, *p_log_buff_end;
size_t sz_log_buff = 30;

uint8_t CLASS_OF_TI[] = {45, 58};


/*
* 
* p_first_record - указатель на начало первой записи.
* p_end_of_records - указатель на последний байт последней записи.
*
*/

uint8_t *p_first_record;
uint8_t *p_end_of_records;
size_t size_of_free_space(void);
int write_buffer(uint8_t *p_data, size_t size);
int read_buffer(uint8_t *p_data, uint8_t *p_first_byte, size_t size);
int release_space(size_t size);
int in_array(int8_t *array, size_t size, int8_t look_for);
void get_actual_time(date_and_time *data);
void actual_time_to_CP56Time(uint8_t *data);
void CP56Time2a_to_time(uint8_t *cp56t, date_and_time *st);
void time_to_CP56Time2a(date_and_time *st, uint8_t *cp56t);
uint16_t reverse_uint16 (uint16_t s);

int write_sys_log(uint16_t wEventId);
int read_sys_log(uint8_t *frame, char *str);

int write_tsl_log(uint8_t class_id, uint8_t *p_data);
int read_ts_log(uint8_t *frame, char *str);

int write_ti_log(uint8_t class_id, uint8_t *p_data);
int read_ti_log(uint8_t *frame, char *str);

int clr_sys_log(void);
uint8_t* shift_pointer_along_buffer(uint8_t *p_begin, size_t offset);
int get_type_of_frame(int8_t *frame);
int buffer_to_file(void);

void print_data()
{
	int i;

	printf("_________\n");
	for (i = 0; i < sz_log_buff; i++)
		if (p_log_buff + i == p_first_record)
			printf("%p - %x B\n", p_log_buff + i, p_log_buff[i]);

		else if (p_log_buff + i == p_end_of_records)
			printf("%p - %x E\n", p_log_buff + i, p_log_buff[i]);

		else 
			printf("%p - %x\n", p_log_buff + i, p_log_buff[i]);

	printf("Указатели: %p, %p\n", p_first_record, p_end_of_records);

}

void pritn_time(date_and_time dt){
	fprintf(stdout, "%02d:%02d:%02d.%03d %02d-%02d-%04d\n",
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		dt.day,
		dt.month,
		dt.year
	);
}

int main(void)
{
	
	uint8_t test_ti_frame[2] = {0x82, 1};
	uint8_t frame_ti1[SIZE_OF_TI] = {0x0,0x0,0x0, 0x0,0x0,0x0,0x0, 0x80, 0xca,0x1b,0xa6,0x14,0x99,0x08,0x10};
	uint8_t frame_ti2[SIZE_OF_TI] = {0x01,0x0,0x0, 0x0,0x0,0x0,0x0, 0x80, 0xca,0x1b,0xa6,0x14,0x99,0x08,0x10};

	uint8_t frame_ts1[SIZE_OF_TS] = {0x58,0x0,0x0, 0x80, 0xca,0x1b,0xa6,0x14,0x99,0x08,0x10};
	uint8_t frame_ts2[SIZE_OF_TS] = {0x59,0x0,0x0, 0x80, 0xca,0x1b,0xa6,0x14,0x99,0x08,0x10};

	p_log_buff = malloc(sz_log_buff);
	if (p_log_buff == NULL) {
		printf("No memory\n");
		return -ENOMEM;
	}
	memset(p_log_buff, NONE, sz_log_buff);
	
	p_first_record = p_end_of_records = p_log_buff;
	p_log_buff_end = p_log_buff + sz_log_buff - 1;
	
	// ***********

	write_sys_log(0x0054);
	print_data();
	// write_sys_log(0x0052);
	// print_data();

	write_tsl_log(1, frame_ts1);
	print_data();
	write_ti_log(45, frame_ti1);
	print_data();
	// write_sys_log(0x0054);
	// print_data();
	

	int i;
	i = buffer_to_file();
	printf("записей: %d\n", i);

	free(p_log_buff);
}

size_t size_of_free_space(void)
{
	/* 
	 * Ситуация когда указатель начала и конца совпадают может быть в одном
	 * случае:
	 * 	1) Буфер полностью чист, в этом случае значение по указателям 
		будет равным NONE.
	 */
	if (p_first_record == p_end_of_records)
		return sz_log_buff;

	/* 
	 * Если указатель начала меньше конца, то размер свободного пространства
	 * определяем вычитаением отрезка от начала до конца из общего размера
	 * буфера. 
	 *
	 * Иначе - указатель конца прошел по кругу и идет за указателем начала.
	 * В этом случае свободное пространство находится между указателями.
	 */

	if (p_first_record < p_end_of_records)
		return sz_log_buff - (p_end_of_records + 1 - p_first_record);
	else
		return p_first_record - p_end_of_records - 1;

}

int in_array(int8_t *array, size_t size, int8_t look_for)
{
    int i;

    for (i = 0; i < size; i++)
        if (array[i] == look_for)
            return 1;
    return 0;
}

/*
 * Освобождает место в буфере для size байт. 
 * Освобождение происходит путем переноса указателя первой записи на длину
 * фрейма. Указатель первой записи всегда указывает на первый байт фрейма, где
 * указан класс (тип) фрейма. Длина фрейма расчитывается исходя из типа фрейма:
 *	Фрейм собственного сигнала всегда имеет старший бит == 1,
 *	TI  имеет значения определенные в CLASS_OF_TI.
 * Таким образом, все значение со старшим битом == 0 и не входящие в CLASS_OF_TI
 * относим к TS типу.
 */
int release_space(size_t size)
{

	uint8_t msb = 0x80;
	size_t offset;
	int32_t rest_size;

	printf("Запрос: %zu\n", size);
	rest_size = size;
	do {
		if (*p_first_record & msb)
			offset = SIZE_OF_OWN_EVENT;
		else
			if (in_array(CLASS_OF_TI, sizeof(CLASS_OF_TI),\
							*p_first_record))
				offset = SIZE_OF_TI;
			else 
				offset = SIZE_OF_TS;
		printf("Выделяем: %zu\n", offset);

		// Смещаем указатель первой записи с учетом кольца
		// p_first_record += offset;
		// if (p_first_record > p_log_buff_end)
		// 	p_first_record = p_log_buff + (p_first_record - \
		// 		p_log_buff_end - 1);

		p_first_record = shift_pointer_along_buffer(p_first_record,
			offset);

		rest_size -= offset; 
	} while (rest_size > 0);

	return 0;
}

int write_buffer(uint8_t *p_data, size_t size)
{

	size_t sz_free_space;
	size_t sz_free_end;

	if (size > sz_log_buff)
		return -ENOMEM;

	sz_free_space = size_of_free_space();
	printf("свободный размер: %zu нужно: %zu  \n", sz_free_space, size);

	if (sz_free_space < size)
		release_space(size - sz_free_space);

	if (p_end_of_records + size <= p_log_buff_end) {
		if (p_first_record == p_end_of_records){
			memcpy(p_end_of_records, p_data, size);
			p_end_of_records += size - 1;

		}
		else {
			memcpy(p_end_of_records + 1, p_data, size);
			p_end_of_records += size;
		}

	} else {
		sz_free_end = p_log_buff_end - p_end_of_records;
		if (sz_free_end == 0) {
			// указатель конца последней записи в последнем байте
			// буфера - начинаем запись с головы буфера
			memcpy(p_log_buff, p_data, size);
			p_end_of_records = p_log_buff + size - 1;
		} else {
			// разбиваем запись на две части. Дозаполняем хвост
			// и продолжаем от головы
			memcpy(p_end_of_records + 1, p_data, sz_free_end);
			memcpy(p_log_buff, p_data + sz_free_end, size - \
				sz_free_end);
			p_end_of_records = p_log_buff + size - sz_free_end - 1;
		}

	}

	return ER_OK;
}

int read_buffer(uint8_t *p_data, uint8_t *p_first_byte, size_t size)
{
	size_t bytes;

	if (size > sz_log_buff)
		size = sz_log_buff;

	if (p_first_byte + size <= p_log_buff_end) {
		memcpy(p_data, p_first_byte, size);
	} else {
		// считываем хвост и продолжаем от головы
		bytes = p_log_buff_end - p_first_byte + 1;
		memcpy(p_data, p_first_byte, bytes);
		memcpy(p_data + bytes, p_log_buff, size - bytes);
	}

	return ER_OK;
}

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

/*
 * Считывает текущее время с точностью до милисекунд и укладывает в формате
 * CP56Time2a по указателю, переданному в праметре.
 */
void actual_time_to_CP56Time(uint8_t *data)
{
	date_and_time dt;
	get_actual_time(&dt);
	time_to_CP56Time2a(&dt, data);
}

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

uint16_t reverse_uint16 (uint16_t s)
{
	uint8_t c1, c2;

	if (is_bigendian()) {
		return s;
	} else {
		c1 = s & 255;
		c2 = (s >> 8) & 255;

		return (c1 << 8) + c2;
	}
}

/*
 * Очищает буфер логера, и записывает сообщение об очитске первым сообщением.
 * Физически буфер не стирается. Переносятся указатели на начало.
 */
int clr_sys_log(void)
{
	p_first_record = p_end_of_records = p_log_buff;
	*p_first_record = NONE;
	write_sys_log(OWN_EVENT_ID_CLR);
}

/*
 * Записывает собственное сообщение, переданное в параметре.
 * Функция вормирует own_event_frame кадр записи, где 
 * первые 2 байта - полученный параметр старший бит которого 
 * устанавливается в 1,
 * последние 7 байт - текущее время в формате CP56Time2a.
 */
int write_sys_log(uint16_t wEventId)
{
	int res;

	uint16_t mask = 0x8000;

	own_event_frame frame;

	// старший бит в 1
	uint16_t my_wEventId = reverse_uint16(wEventId) | reverse_uint16(mask);

	frame.event_id = my_wEventId;
	// memcpy(data, &my_wEventId, 2);
	actual_time_to_CP56Time(frame.datetime);

	res = write_buffer((uint8_t *)&frame, sizeof(frame));
	if (res < 0)
		return res;

	return 0;
}

/*
 * Считывает кадр собтвеных сообщений из памяти
 */
int read_sys_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_OWN_EVENT)
		return ER_FAILURE;

	uint16_t mask = 0x7FFF;
	own_event_frame my_frame;

	read_buffer((int8_t*)&my_frame, frame, sizeof(my_frame));

	my_frame.event_id = reverse_uint16(my_frame.event_id) & mask;

	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	sprintf(str, "%d-%d-%d %d-%d-%d-%d E %X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		my_frame.event_id
	);

	return ER_OK;
}

/*
 * Считывает кадр ts сообщений из памяти
 */
int read_ts_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_TS)
		return ER_FAILURE;

	ts_frame my_frame;
	read_buffer((int8_t*)&my_frame, frame, sizeof(my_frame));
	
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	sprintf(str, "%d-%d-%d %d-%d-%d-%d C: %X address: %X%X%X, value: %X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		my_frame.class_id,
		my_frame.address[0],
		my_frame.address[1],
		my_frame.address[2],
		my_frame.value
		
	);

	return ER_OK;
}

/*
 * Считывает кадр ti сообщений из памяти
 */
int read_ti_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_TI)
		return ER_FAILURE;

	ti_frame my_frame;
	read_buffer((int8_t*)&my_frame, frame, sizeof(my_frame));
	
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	sprintf(str, "%d-%d-%d %d-%d-%d-%d C: %X address: %X%X%X, value: %X%X%X%X, quality: %X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		my_frame.class_id,
		my_frame.address[0],
		my_frame.address[1],
		my_frame.address[2],
		my_frame.value[0],
		my_frame.value[1],
		my_frame.value[2],
		my_frame.value[3],
		my_frame.quality
	);

	return ER_OK;
}

/*
 * Записывает TS данные.
 */
int write_tsl_log(uint8_t class_id, uint8_t *p_data)
{

	int8_t data[SIZE_OF_TS];
	int res;

	if (in_array(CLASS_OF_TI, sizeof(CLASS_OF_TI), class_id))
				return ER_FAILURE;

	data[0] = class_id;
	memcpy(&data[1], p_data, SIZE_OF_TS - 1);	
	res = write_buffer(data, SIZE_OF_TS);
	if (res < 0)
		return res;

	return ER_OK;
}


/*
 * Записывает TI данные.
 */
int write_ti_log(uint8_t class_id, uint8_t *p_data)
{
	int8_t data[SIZE_OF_TI];
	int res;

	if (!in_array(CLASS_OF_TI, sizeof(CLASS_OF_TI), class_id))
				return ER_FAILURE;

	data[0] = class_id;
	memcpy(&data[1], p_data, SIZE_OF_TI - 1);	
	res = write_buffer(data, SIZE_OF_TI);
	if (res < 0)
		return res;

	return ER_OK;
}


/*
 * Возвращает тип фрейма по первому байту
 */
int get_type_of_frame(int8_t *frame)
{
	uint8_t msb = 0x80; // маска для определения собственного сообщения

	if (*frame & msb)
			return FRAME_TYPE_OWN_EVENT;
	else
		if (in_array(CLASS_OF_TI, sizeof(CLASS_OF_TI), *frame))
			return FRAME_TYPE_TI;
		else 
			return FRAME_TYPE_TS;

	return -1; // тип не найден
}

/*
 * возвращает указатель смещенный от p_begin на offset байт по буферу с учетом 
 * цикличности.
 */

uint8_t* shift_pointer_along_buffer(uint8_t *p_begin, size_t offset)
{
	uint8_t *my_p;
	
	my_p = p_begin + offset;
	if (my_p > p_log_buff_end)
		my_p = p_log_buff + (my_p - p_log_buff_end - 1);

	return my_p;
}

/*
 * Выгружает буфер в файлы
 * Все собственные события записываются в один файл именованный по формату 
 * E_yyy-mm-dd_hh-mm-ss, где время – это вермя выгрузки файлов. 
 * Теледанные выгружаются в файлы разделенные по ClassId в формате 
 * Ttt_yyy-mm-dd_hh-mm-ss где tt- значение ClassID, дата - время выгрузки фалов.

 1) Считываем байт под p_first_record и определяем тип сообщения
 2) записываем в соответвующий файл
 3) По типу сообщения определяем размер
 4) по размеру нахродим указатель на последний байт текущей записи
 5) если указатель 4) совпал с p_end_of_records, то мы считали последнюю запись
    если нет, то:
 6) передвигаем p_first_record на следующую запись и повторяем с 1)

 */
int buffer_to_file(void){
	uint8_t *my_p_first_record;
	uint8_t *my_p_end_of_frame;
	int type_of_frame;
	int i;
	size_t offset;
	bool end_of_records;

	date_and_time dt;
	get_actual_time(&dt);

	char date_str[100];
	char file_name_str[100];
	char log_str[300];

	time_t t;
	struct tm *tmp;

	t = time(NULL);
	tmp = localtime(&t);

	if (tmp == NULL) {
		perror("localtime");
		return ER_FAILURE;
	}

	if (strftime(date_str, sizeof(date_str), "%Y-%m-%d_%H_%M_%S", tmp) == 0) {
		fprintf(stderr, "strftime returned 0");
		return ER_FAILURE;
	}

	printf("Result string is \"%s\"\n", date_str);

	int fd;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	my_p_first_record = p_first_record;
	
	end_of_records = false;
	i = 0;
	do {
		type_of_frame = get_type_of_frame(my_p_first_record);

		// передаем ошибку определения типа вызывающему
		if (type_of_frame < 0)
			return type_of_frame;

		i++;
		
		switch (type_of_frame) {
			case FRAME_TYPE_OWN_EVENT:
			{
				if (EXIT_SUCCESS == read_sys_log(my_p_first_record, log_str)) {
					sprintf(file_name_str, "E_%s", date_str);
					fd = open(file_name_str, O_CREAT | O_WRONLY
						| O_APPEND, mode);

					write(fd, log_str,strlen(log_str));
					close(fd);
				}
				
				offset = SIZE_OF_OWN_EVENT;
				break;
			}

			case FRAME_TYPE_TS:
			{
				
				if (EXIT_SUCCESS == read_ts_log(my_p_first_record, log_str)) {
					sprintf(file_name_str, "T%d_%s", *my_p_first_record,
						date_str);
					fd = open(file_name_str, O_CREAT | O_WRONLY
						| O_APPEND, mode);

					write(fd, log_str, strlen(log_str));
					close(fd);
				}

				offset = SIZE_OF_TS;
				break;
			}

			case FRAME_TYPE_TI:
			{
				if (EXIT_SUCCESS == read_ti_log(my_p_first_record, log_str)) {
					sprintf(file_name_str, "T%d_%s", *my_p_first_record,
						date_str);
					fd = open(file_name_str, O_CREAT | O_WRONLY
						| O_APPEND, mode);

					write(fd, log_str, strlen(log_str));
					close(fd);
				}

				offset = SIZE_OF_TI;
				break;
			}
		}

		my_p_end_of_frame = shift_pointer_along_buffer(
			my_p_first_record, offset - 1);
		
		if (my_p_end_of_frame == p_end_of_records)
			end_of_records = true;
		else
			my_p_first_record = shift_pointer_along_buffer(
				my_p_first_record, offset);
			
	} while (!end_of_records);


	return i;
}
































