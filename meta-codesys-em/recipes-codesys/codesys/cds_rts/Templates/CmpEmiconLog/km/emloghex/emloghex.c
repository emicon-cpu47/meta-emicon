#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/miscdevice.h>
#include <asm/io.h>
#include <linux/slab.h>
# include <linux/delay.h> 


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mikhail Shvetsov <lameli67@gmail.com>");

#define MISC_DEV_NAME "emloghex"

/* 
 * Начало физического адреса в nvram устанавливается записью в файл.
 * Размер лога считывается из самой памяти.
 */
 
static unsigned long nvram_cs3_mem_address = 0x0; 
static size_t sz_log_mem = 0;

#define PRINT_BYTES_IN_LINE 16

/*
 * Маркировка первых двух байт (init_mark), означающее инициализацию буфера
 * из мусора LOG_INIT_MARK, либо буфер занят записью/чтенеием LOG_INIT_MARK_BUSY.
 */
#define LOG_INIT_MARK 0x55aa
#define LOG_INIT_MARK_BUSY 0x65aa


/* 
 * Проверка семафора. 
 * Если буфер не занят, *init_mark должен быть LOG_INIT_MARK
 */
bool is_buffer_accessable(uint16_t *init_mark)
{
	int trial = 0;
	while(*init_mark != LOG_INIT_MARK && trial < 3){
		trial++;
		udelay(100);
	}
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
	log_mem = ioremap_nocache(nvram_cs3_mem_address, sizeof(init_mark));
	memcpy_toio(log_mem, &init_mark, sizeof(init_mark));
	iounmap(log_mem);

	return 0;
}


/*
 * Чтение памяти и вывод в hex. 
 * Чтение производиться по PRINT_BYTES_IN_LINE байт.
 * 
 */

ssize_t md1_read(struct file *filp, char __user *buf, size_t count,
	loff_t *f_pos)
{
	int error;
	void *tmp_buf;
	void *tmp_buf_asci;
	size_t sz_tmp_buf_asci;
	void *log_mem;
	size_t bytes;
	char *str; 
	uint16_t init_mark;
	bool access;

	if (!nvram_cs3_mem_address) {
		pr_debug("emlog-hex: Ошибка чтения - адрес не установлен!\n");
		return -EFAULT;
	}

	if (*f_pos >= sz_log_mem)
		return 0;

	if (*f_pos + count > sz_log_mem)
		count = sz_log_mem - *f_pos;

	if (count > PRINT_BYTES_IN_LINE)
		count = PRINT_BYTES_IN_LINE;

	// проверяем разрешение на доступ к буферу
	log_mem = ioremap_nocache(nvram_cs3_mem_address, sizeof(init_mark));
	memcpy_fromio(&init_mark, log_mem, sizeof(init_mark));	
	access = is_buffer_accessable(&init_mark);
	iounmap(log_mem);
	if (!access){
		pr_debug("emlog-hex: Ошибка чтения - буфер занят или не инициализирован!\n");
		return -EFAULT;
	}

	set_lock_buffer(LOG_INIT_MARK_BUSY);

	// hex имеет 2 символа на байт + 1 пробел + 1 терминатор строки
	// + 1 на перевод каретки
	sz_tmp_buf_asci = count * 3 + 1 + 1;

	tmp_buf = kmalloc(count, GFP_KERNEL);
	tmp_buf_asci = kmalloc(sz_tmp_buf_asci, GFP_KERNEL);

	log_mem = ioremap_nocache(nvram_cs3_mem_address + *f_pos, count);
	memcpy_fromio(tmp_buf, log_mem, count);
	iounmap(log_mem);
	
	bytes = hex_dump_to_buffer(tmp_buf, count, 16, 1, tmp_buf_asci,
					sz_tmp_buf_asci, false);

	str = (char *)tmp_buf_asci;
	str[bytes] = '\n';
	str[bytes + 1] = '\0';

	error = copy_to_user(buf, str,  bytes + 1);

	kfree(tmp_buf);
	kfree(tmp_buf_asci);

	// разблокируем доступ
	set_lock_buffer(LOG_INIT_MARK);

	if (error)
		return -EFAULT;

	*f_pos += count;
	return bytes + 1;

}

/*
 * Записывает адрес буфера в физической памяти.
 * Значение должно передаваться 4мя байтами данных
 */

ssize_t md1_write(struct file *filp, const char __user *buf, size_t count,
	loff_t *f_pos)
{
	uint16_t init_mark;
	void *log_mem;
	int err;
	if (count != sizeof(nvram_cs3_mem_address)) {
		pr_debug("emlog-hex: Ошибка записи - несоответствие параметра!\n");
		return -EFAULT;
	}

	nvram_cs3_mem_address = 0;
	err = simple_write_to_buffer(
		&nvram_cs3_mem_address,
		sizeof(nvram_cs3_mem_address),
		f_pos, buf, count);
	if (!err){
		pr_debug("emlog-hex: FAULT simple_write_to_buffer - %d\n", err);
		return err;
	}

	// считываем размер буфера, который дежит смещением 10 байт от головы
	// 14 байт вся структура инициализации
	log_mem = ioremap_nocache(nvram_cs3_mem_address, 14);
	memcpy_fromio(&init_mark, log_mem, sizeof(init_mark));
	memcpy_fromio(&sz_log_mem, log_mem + 10, sizeof(sz_log_mem));
	iounmap(log_mem);

	pr_debug("emlog-hex: Установлен адрес 0x%p\n", (void *)nvram_cs3_mem_address);

	if (init_mark != LOG_INIT_MARK) {
		nvram_cs3_mem_address = 0;
		sz_log_mem = 0;
		pr_debug("emlog-hex: Ошибка записи - буфер не инициализирован!\n");
		return -EFAULT;
	}


	pr_debug("emlog-hex: Размер буфера %zu байт\n", sz_log_mem);

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

	pr_debug("Emicon log module registred.\n");

	error = misc_register(&misc_dev);
	if (error) {
		pr_debug("Emicon log module registred - filed!\n");
		return error;
	}

	return 0;
}

static void __exit md_exit(void)
{
	pr_debug("Emicon log module disabled.\n");
	misc_deregister(&misc_dev);
}

module_init(md_init);
module_exit(md_exit);
