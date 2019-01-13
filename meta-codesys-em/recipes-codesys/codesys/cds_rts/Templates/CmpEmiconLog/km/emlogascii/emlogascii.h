#ifndef _EMICONLOG_H_
#define _EMICONLOG_H_

#define MISC_DEV_NAME "emlogascii"

const int is_bigendian_i = 1;
#define is_bigendian() ((*(uint8_t*)&is_bigendian_i) == 0)

/*
 * Маркировка первых двух байт (init_mark), означающее инициализацию буфера
 * из мусора LOG_INIT_MARK, либо буфер занят записью/чтенеием LOG_INIT_MARK_BUSY.
 */
#define LOG_INIT_MARK 0x55aa
#define LOG_INIT_MARK_BUSY 0x65aa

#define FRAME_TYPE_NO 0
#define FRAME_TYPE_OWN_EVENT 1
#define FRAME_TYPE_TS 2
#define FRAME_TYPE_TI 3
#define SZ_INIT_DATA_LOG 14

uint8_t CLASS_OF_TI[] = {45, 58};

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

int get_type_of_frame(unsigned long  addr);
int read_sys_log(unsigned long addr_frame, char *str);
int read_ts_log(unsigned long addr_frame, char *str);
int read_ti_log(unsigned long addr_frame, char *str);
uint16_t reverse_uint16 (uint16_t s);
void memcpy_from_nwram(void *dest, unsigned long source, size_t nbytes);
int in_array(uint8_t *array, size_t size, uint8_t look_for);

unsigned long shift_pointer_along_buffer(unsigned long addr_begin,
	size_t offset);


#endif /*_EMICONLOG_H_*/