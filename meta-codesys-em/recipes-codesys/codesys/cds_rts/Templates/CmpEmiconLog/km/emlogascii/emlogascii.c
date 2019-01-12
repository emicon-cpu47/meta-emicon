#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
// #include <asm/io.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include "../../CP56Time2a.c"
#include "emlogascii.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikhail Shvetsov <lameli67@gmail.com>");

static unsigned long _addr_base;
static unsigned long _addr_log_buff;
static unsigned long _addr_log_buff_end;
static size_t _sz_log_buff;
static size_t _sz_log_mem;


int in_array(uint8_t *array, size_t size, uint8_t look_for)
{
	int i;

	for (i = 0; i < size; i++)
		if (array[i] == look_for)
		return 1;
	return 0;
}

uint16_t reverse_uint16(uint16_t s)
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

int read_buffer(void *p_data, unsigned long addr_first_byte, size_t size)
{
	size_t bytes;

	if (size > _sz_log_buff)
		size = _sz_log_buff;

	if (addr_first_byte + size <= _addr_log_buff_end) {
		memcpy_from_nwram(p_data, addr_first_byte, size);
	} else {
		// считываем хвост и продолжаем от головы
		bytes = _addr_log_buff_end - addr_first_byte + 1;
		memcpy_from_nwram(p_data, addr_first_byte, bytes);
		memcpy_from_nwram(p_data + bytes, _addr_log_buff, size - bytes);
	}

	return 0;
}

/*
 * Считывает кадр собтвеных сообщений из памяти
 */
int read_sys_log(unsigned long addr_frame, char *str)
{

	uint16_t mask = 0x7FFF;
	own_event_frame frame;
	date_and_time dt;

	read_buffer((void *)&frame, addr_frame, sizeof(frame));
	frame.event_id = reverse_uint16(frame.event_id) & mask;
	CP56Time2a_to_time(frame.datetime, &dt);

	sprintf(str, "%d-%d-%d %d-%d-%d-%d E 0x%02X\n",
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		frame.event_id
	);

	return 0;
}

/*
 * Считывает кадр ts сообщений из памяти
 */
int read_ts_log(unsigned long addr_frame, char *str)
{

	ts_frame frame;
	date_and_time dt;

	read_buffer((void *)&frame, addr_frame, sizeof(frame));
	CP56Time2a_to_time(frame.datetime, &dt);

	sprintf(str,
		"%d-%d-%d %d-%d-%d-%d C: 0x%02X A: 0x%02X%02X%02X, V: 0x%02X\n",
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		frame.class_id,
		frame.address[0],
		frame.address[1],
		frame.address[2],
		frame.value
	);

	return 0;
}

/*
 * Считывает кадр ti сообщений из памяти
 */
int read_ti_log(unsigned long addr_frame, char *str)
{

	ti_frame frame;
	date_and_time dt;

	read_buffer((uint8_t *)&frame, addr_frame, sizeof(frame));
	CP56Time2a_to_time(frame.datetime, &dt);

	sprintf(str, "%d-%d-%d %d-%d-%d-%d C: 0x%02X A: 0x%02X%02X%02X, V: 0x%02X%02X%02X%02X, Q: 0x%02X\n",
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		frame.class_id,
		frame.address[0],
		frame.address[1],
		frame.address[2],
		frame.value[0],
		frame.value[1],
		frame.value[2],
		frame.value[3],
		frame.quality
	);

	return 0;
}


/*
 * возвращает указатель смещенный от p_begin на offset байт по буферу с учетом
 * цикличности.
 */

unsigned long shift_pointer_along_buffer(unsigned long addr_begin, size_t offset)
{
	unsigned long new_addr;

	new_addr = addr_begin + offset;
	if (new_addr > _addr_log_buff_end)
		new_addr = _addr_log_buff + (new_addr - _addr_log_buff_end - 1);

	return new_addr;
}

/*
 * Возвращает тип фрейма по первому байту
 */
int get_type_of_frame(unsigned long addr)
{
	uint8_t msb = 0x80; // маска для определения собственного сообщения
	uint8_t byte_value;

	memcpy_from_nwram(&byte_value, addr, 1);

	if (byte_value & msb)
		return FRAME_TYPE_OWN_EVENT;

	else
		if (in_array((uint8_t *)CLASS_OF_TI, sizeof(CLASS_OF_TI),
			byte_value))
			return FRAME_TYPE_TI;
		else
			return FRAME_TYPE_TS;

	return -1; // тип не найден
}

/*
 * Проверка семафора.
 * Если буфер не занят, *init_mark должен быть LOG_INIT_MARK
 */
bool is_buffer_accessable(void)
{
	void *log_mem;
	int trial = 0;
	uint16_t init_mark;

	log_mem = ioremap_nocache(_addr_base, sizeof(init_mark));

	memcpy_fromio(&init_mark, log_mem, sizeof(init_mark));
	while (init_mark != LOG_INIT_MARK && trial < 3) {
		trial++;
		udelay(100);
		memcpy_fromio(&init_mark, log_mem, sizeof(init_mark));
	}
	iounmap(log_mem);
	if (trial >= 3)
		return false;

	return true;
}

/*
 * Блокировка/разблокировка доступа к буферу
 */

int set_lock_buffer(uint16_t init_mark)
{

	void *log_mem;

	log_mem = ioremap_nocache(_addr_base, sizeof(init_mark));
	memcpy_toio(log_mem, &init_mark, sizeof(init_mark));
	iounmap(log_mem);
	return 0;
}


void memcpy_from_nwram(void *dest, unsigned long source, size_t nbytes)
{
	void *mem;

	mem = ioremap_nocache(source, nbytes);
	memcpy_fromio(dest, mem, nbytes);
	iounmap(mem);
}

/*
 * Чтение памяти и вывод в hex.
 * Чтение производиться по PRINT_BYTES_IN_LINE байт.
 */
ssize_t md1_read(struct file *filp, char __user *buf, size_t count,
		loff_t *f_pos)
{
	unsigned long addr_first_record;
	unsigned long addr_end_of_frame;
	unsigned long addr_end_of_records;

	int type_of_frame;
	loff_t offset = 0;
	void *init_data;
	uint32_t offset_first_record;
	uint32_t offset_end_of_records;

	int error;
	char log_str[300];
	uint32_t nbytes;

	bool access;

	if (*f_pos == 1)
		return 0;

	if (!_addr_base) {
		pr_debug("emlog-ascii: Ошибка чтения - адрес не установлен!\n");
		return -EFAULT;
	}

	access = is_buffer_accessable();
	if (!access) {
		pr_debug("emlog-ascii: Ошибка чтения - буфер занят или не инициализирован!\n");
		return -EFAULT;
	}


	set_lock_buffer(LOG_INIT_MARK_BUSY);

	init_data = kmalloc(SZ_INIT_DATA_LOG, GFP_KERNEL);
	memcpy_from_nwram(init_data, _addr_base, SZ_INIT_DATA_LOG);
	offset_first_record = *(uint32_t *)(init_data + 2);
	offset_end_of_records = *(uint32_t *)(init_data + 6);
	kfree(init_data);

	// offset_first_record и offset_end_of_records смещение указателей от
	// головы области записи, а не от головы всей памяти лога

	if (offset_first_record == 0 && offset_end_of_records == 0) {
		sprintf(log_str, "Записи не найдены.\n");
		type_of_frame = FRAME_TYPE_NO;
	} else {
		addr_end_of_records = _addr_log_buff + offset_end_of_records;

		if (*f_pos == 0) {
			addr_first_record = _addr_log_buff + offset_first_record;
		} else {
			addr_first_record = *f_pos;
			if (addr_first_record < _addr_log_buff ||
				addr_first_record > _addr_log_buff_end){
				pr_debug("emlog-ascii: Некорректная позиция в файле!\n");
			}
		}

		type_of_frame = get_type_of_frame(addr_first_record);
		if (type_of_frame < 0) {
			sprintf(log_str, "Ошибка определения типа фрейма записи.\n");
			type_of_frame = FRAME_TYPE_NO;
		}
	}



	switch (type_of_frame) {
	case FRAME_TYPE_OWN_EVENT:
	{
		offset = SIZE_OF_OWN_EVENT;
		read_sys_log(addr_first_record, log_str);

		break;
	}

	case FRAME_TYPE_TS:
	{
		offset = SIZE_OF_TS;
		read_ts_log(addr_first_record, log_str);
		break;
	}

	case FRAME_TYPE_TI:
	{
		offset = SIZE_OF_TI;
		read_ti_log(addr_first_record, log_str);
		break;
	}

	case FRAME_TYPE_NO:
	{
		offset = 0;
		break;
	}
	}

	nbytes = strlen(log_str) + 1;
	error = copy_to_user(buf, log_str, nbytes);

	if (!offset) {
		*f_pos = 1;
	} else {
		addr_end_of_frame = shift_pointer_along_buffer(
						addr_first_record, offset - 1);
		if (addr_end_of_frame == addr_end_of_records) {
			*f_pos = 1; // достигнут конец файла
		} else {
			addr_first_record = shift_pointer_along_buffer(
						addr_first_record, offset);
			*f_pos = addr_first_record;
		}
	}
	// разблокируем доступ
	set_lock_buffer(LOG_INIT_MARK);

	return nbytes;
}

/*
 * Записывает адрес буфера в физической памяти.
 * Значение должно передаваться 4мя байтами данных
 */

ssize_t md1_write(struct file *filp, const char __user *buf, size_t count,
	loff_t *f_pos)
{
	uint16_t init_mark;
	int err;

	if (count != sizeof(_addr_base)) {
		pr_debug("emlog-ascii: Ошибка записи - несоответствие параметра!\n");
		return -EFAULT;
	}

	_addr_base = 0;
	err = simple_write_to_buffer(&_addr_base, sizeof(_addr_base),
					f_pos, buf, count);
	if (!err) {
		pr_debug("emlog-ascii: FAULT simple_write_to_buffer - %d\n",
			 err);
		return err;
	}

	// считываем размер буфера, который дежит смещением 10 байт от головы
	// 14 байт вся структура инициализации

	memcpy_from_nwram(&init_mark, _addr_base, sizeof(init_mark));
	memcpy_from_nwram(&_sz_log_mem, _addr_base + 10, sizeof(_sz_log_mem));

	pr_debug("emlog-ascii: Установлен адрес 0x%p\n", (void *)_addr_base);

	if (init_mark != LOG_INIT_MARK) {
		_addr_base = 0;
		_sz_log_mem = 0;
		_sz_log_buff = 0;
		_addr_log_buff = 0;
		pr_debug("emlog-ascii: Ошибка записи - буфер не инициализирован!\n");
		return -EFAULT;
	}

	_addr_log_buff = _addr_base + SZ_INIT_DATA_LOG;
	_sz_log_buff = _sz_log_mem - SZ_INIT_DATA_LOG;
	_addr_log_buff_end = _addr_base + _sz_log_mem - 1;

	pr_debug("emlog-ascii: Размер буфера %zu байт\n", _sz_log_mem);

	return count;
}

const struct file_operations md1_fops = {
	.owner	= THIS_MODULE,
	.read	= md1_read,
	.write	= md1_write,
	.llseek = no_llseek,
};

struct miscdevice misc_dev = {
	.minor = MISC_DYNAMIC_MINOR,
	.name = MISC_DEV_NAME,
	.fops = &md1_fops,
};

static int __init md_init(void)
{
	int error;

	pr_debug("Emicon log-ascii module registred.\n");

	error = misc_register(&misc_dev);
	if (error) {
		pr_debug("Emicon log-ascii module registred - filed!\n");
		return error;
	}

	return 0;
}

static void __exit md_exit(void)
{
	pr_debug("Emicon log-ascii module disabled.\n");
	misc_deregister(&misc_dev);
}

module_init(md_init);
module_exit(md_exit);
