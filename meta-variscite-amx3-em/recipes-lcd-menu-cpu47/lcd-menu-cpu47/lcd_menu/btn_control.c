/*
 * Функции контроля кнопки
 */
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>
#include <sys/ioctl.h>
#include <asm-generic/termbits.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>

// кнопка С gpio 55
// кнопка B gpio 56
// кнопка A gpio 57

#define PRESSED_BUTTON_CODE 48 // ascii 0
#define NOT_PRESSED_BUTTON_CODE 49 // ascii 1
#define BUTTON_GPIO "57" // A кнопка

void gpio_init(void);
char read_button(void);
static bool is_button_pressed(void);

static char _str_gpio_ctl[33];

void gpio_init(void)
{
	int fd;

	/*
	 * Активируетм кнопку.
	 */
	strcpy(_str_gpio_ctl, BUTTON_GPIO);
	fd = open("/sys/class/gpio/export", O_WRONLY);
	write(fd, _str_gpio_ctl, strlen(_str_gpio_ctl));
	close(fd);

	sprintf(_str_gpio_ctl, "/sys/class/gpio/gpio%s/direction", BUTTON_GPIO);
	fd = open(_str_gpio_ctl, O_WRONLY);
	strcpy(_str_gpio_ctl, "in");
	write(fd, _str_gpio_ctl, strlen(_str_gpio_ctl));
	close(fd);

	sprintf(_str_gpio_ctl, "/sys/class/gpio/gpio%s/value", BUTTON_GPIO);
	return;
}

char read_button(void)
{
	int fd;
	char ascii_code;
	fd = open(_str_gpio_ctl, O_RDONLY);
	read(fd, &ascii_code, 1);
	close(fd);
	return ascii_code;
}

/*
 * Выдает true если кнопка нажата в текущий момент
 */
static bool is_button_pressed(void)
{
	if (read_button() == PRESSED_BUTTON_CODE) 
		return true;
	else
		return false;
}

