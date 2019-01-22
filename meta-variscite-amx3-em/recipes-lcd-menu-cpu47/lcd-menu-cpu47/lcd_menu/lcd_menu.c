/* 
 * Системное Меню.
 * Независимое от рантайма кодесис меню. Запускается отдельным процессом и
 * вызывается длительным нажатием кнопки А на ЦПУ.
 * Каждый экран этого меню, явяется пунктом меню, которые перелистываются
 * короткими нажатиями кнопки А.
 * Выбор пункта меню на исполнение производится длительным нажатием кнопки А.
 * Длительность нажатия задается в MENU_MODE_BTN_PRESSED_INTERVAL.
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


#define NET_NAME "eth0"
#define LCD_START_SCREEN 0
#define LCD_RTS_MENU_SCREEN 1
#define MENU_EXIT_SCREEN 201
#define MENU_SYNC_SCREEN 202
#define MENU_NET_SHOW_SCREEN 203
#define SCREENS_INDEX_MAX 	200 	// количество экранов
#define MENU_SCREENS_INDEX_MAX 	250 	// максимальный индекс менюшек
#define SWITCH_TO_DEFAULT_SCREEN_INTERVAL 30000// milliseconds
#define MENU_MODE_BTN_PRESSED_INTERVAL 3000// milliseconds
#define LCD_MAX_LINE_INDEX	1 	// 0-1 строи экрана
#define LCD_MAX_POSITION_INDEX	249	// 0-249 позиции в линии
#define LCD_MAX_DATA_SIZE	250	// 250 данные
#define LCD_LINE_BUFFER_SIZE	253	// 250 данные + 3 разметочные байты
#define END_OF_LINE_MARK 	0xFF
#define LCD_BLANK_CODE		0x20	// пробел
#define ERR_PARAM 1
#define ERR_NO_SCREEN_IN_MEM 2
#define LCD_SERIAL_PORT "/dev/ttyS2"
#define BITRATE 57600
#define DEFAULT_SCREEN_INDEX 0

/*
 * Структура хранения экрана в памяти
 */
typedef struct lcd_screen {
	uint8_t n;				// номер экрана
	char line0[LCD_MAX_DATA_SIZE + 1];	// строка LCD
	char line1[LCD_MAX_DATA_SIZE + 1];	// вторая строка LCD
	bool hidden;	// показывает отображать или нет этот экран
	int (*p_function)(void); // функция меню
} lcd_screen;


/*
 * Хранилище динамически создаваемых экранов.
 */
struct {
	uint8_t number;		// количество экранов
	lcd_screen *p_area;	// область хранения экранов
} screens_storage;

/*
 * Отображаемый экран на LCD.
 */
struct {
	uint8_t index;	// индекс экрана в хранилище
	lcd_screen screen;
	bool init;
} shown_screen;

/*
 * Инициализация всего модуля. Сбарсывание буферов и указателей.
 * Установка начальных экранов.
 */
void lcd_init(void);

/*
 * Очищает одну линию на LCD.
 */
void clear_line_on_lcd(uint8_t line);

/*
 * Инициализирует экран.
 */
void screen_init(lcd_screen *screen, uint8_t n);

/*
 * Сменяет экран на LCD по индексу.
 * Возвращает 0 в случае успеха.
 */
int screen_to_LCD_by_index(uint8_t index);

/*
 * Сменяет экран на LCD на следующий.
 * Возвращает 0 в случае успеха.
 */
int next_screen_on_LCD(bool menu_mode);

/*
 * Находит по номеру в области хранения экранов (screens_storage) и возвращает
 * указатель на экран.
 */
lcd_screen *get_screen_by_number(uint8_t n);

/*
 * Находит по номеру в области хранения экранов (screens_storage) и возвращает
 * указатель на экран. Если экрана нет, то создает его.
 * Возвращает ошибку в случае невозможности создать экран - нехватка памяти.
 */
lcd_screen *get_or_create_screen_by_number(uint8_t n);

/*
 * Выводит логические экраны на физический LCD.
 * При совпадении выведенной строки с выводимой, обновление строки не
 * происходит.
 */
void screen_to_lcd(lcd_screen *screen, uint8_t index);

/*
 * Посылает данные в LCD по 232му порту
 * 0 - успех
 */
int lcd_send(uint8_t const *tx, size_t len);

/*
 * Основная функция вывода на экран строки.
 */
int lcd_puts(uint8_t n, uint8_t line, uint8_t pos, char *str);

/*
 * Поиск индекса экрана по пользовательскому номеру.
 */
int16_t get_screen_index_by_n(uint8_t n);

/*
 * Выводит строку в экран.
 */
void line_to_lcd(uint8_t line, uint8_t pos, char *str);

/*
 * Создает пункт меню
 */
int create_menu(uint8_t n, char *str_line0, char *str_line1,
		int (*p_function)(void));

/*
 * возвращает текущий момент времени
 */
long int get_curent_time(void);

/*
 * Секция функций МЕНЮ.
 */
int menu_fn_sync_rts(void);
int menu_fn_exit(void);
int menu_fn_net_show(void);

static bool _start_fw = false;
static bool _sys_menu_mode = false;

#include "btn_control.c"
#include "flasher.c"

void main(void)
{
	bool init = false;
	long int zerro_time = 0;
	long int curent_time;
	long int btn_pressed_time;
	long int btn_un_pressed_time; 
	bool enable_switching_next_screen = false;;

	gpio_init();
	lcd_init();
	
	bool btn_pressed = false;
	bool btn_pressed_old = false;

	// блокировка реагирования если нажата кнопка А при старте
	while (!init) {
		if (!is_button_pressed())
			init = true;
		usleep(20000);
	}

	// основной цикл
	while (true) {
		curent_time = get_curent_time();
		btn_pressed = is_button_pressed();

		if (btn_pressed && !btn_pressed_old) {
			btn_pressed_time = curent_time;
			enable_switching_next_screen = true;
		}

		if (!btn_pressed && btn_pressed_old) {
			btn_un_pressed_time = curent_time;

			if (enable_switching_next_screen) {
				next_screen_on_LCD(_sys_menu_mode);
			}
		}

		if (btn_pressed){
			if (curent_time - btn_pressed_time
			    > MENU_MODE_BTN_PRESSED_INTERVAL){

				if (_sys_menu_mode) {
					(*shown_screen.screen.p_function)();
				} else {
					_sys_menu_mode = true;
					next_screen_on_LCD(_sys_menu_mode);
				}

				btn_pressed_time = curent_time;

				enable_switching_next_screen = false;
			}
		}


		if (!_sys_menu_mode
		    && curent_time - zerro_time > 
				    	      SWITCH_TO_DEFAULT_SCREEN_INTERVAL
		    && shown_screen.index != DEFAULT_SCREEN_INDEX) {
		    		zerro_time = curent_time;
				screen_to_LCD_by_index(DEFAULT_SCREEN_INDEX);
		}

		/*
		 * После приема прошивки ПЛК перезагрузится, следовательно
		 * нет надобности сбрасывать _start_fw.
		 */
		fw_manager(_start_fw);

		btn_pressed_old = btn_pressed;
		usleep(20000);
	}


	return;
}

void lcd_init(void)
{

	/*
	 * Инициализация области хранения экранов.
	 */
	screens_storage.p_area = NULL;
	screens_storage.number = 0;

	/*
	 * Инициализация отображаемого экрана. NULL - нет отображаемого экрана
	 */
	shown_screen.init = false;
	/*
	 * Вывод приглашения через образ МЭК функции
	 */

	lcd_puts(LCD_START_SCREEN, 0, 0, "");
	lcd_puts(LCD_START_SCREEN, 1, 0, "");

	create_menu(MENU_EXIT_SCREEN, "Sys Menu", "Exit    ", &menu_fn_exit);
	create_menu(MENU_SYNC_SCREEN, "Sys Menu", "App Sync", &menu_fn_sync_rts);
	// create_menu(MENU_NET_SHOW_SCREEN, "M:SYS   ", "NET SHOW",
	// 	    &menu_fn_net_show);
	return;
}

int lcd_puts(uint8_t n, uint8_t line, uint8_t pos, char *str)
{
	lcd_screen *screen;
	char *tmp_line;
	size_t sz_data;
	uint8_t sz_data_in_line;
	uint8_t old_str_len;

	sz_data = strlen(str);

	screen = get_or_create_screen_by_number(n);
	if (screen == NULL) {
		return -ERR_NO_SCREEN_IN_MEM;
	} else {

		// формирование строки для  LCD
		if (line)
			tmp_line = screen->line1;
		else
			tmp_line = screen->line0;

		old_str_len = strlen(tmp_line);
		tmp_line[old_str_len] = LCD_BLANK_CODE; // убираем \0

		if (sz_data == 0){
			// sz_data == 0 пустая строка - команда обрезки строки
			// по заданной позиции.
			tmp_line[pos] = '\0';
		} else {
			if (sz_data + pos > LCD_MAX_DATA_SIZE)
				sz_data = LCD_MAX_DATA_SIZE - pos;

			memcpy(tmp_line + pos, str, sz_data);

			// избегаем обрезание длинной строки короткой
			if (old_str_len > pos + sz_data)
				tmp_line[old_str_len] = '\0';
			else
				tmp_line[pos + sz_data] = '\0';
		}

		/*
		 * Производим вывод на экран только если экран активный
		 * или небыло еще активных экранов.
		 */
		if (!shown_screen.init || screen->n == shown_screen.screen.n)
			screen_to_lcd(screen, get_screen_index_by_n(screen->n));

	}

	return 0;
}

lcd_screen *get_screen_by_number(uint8_t n)
{

	lcd_screen *screen = NULL;
	lcd_screen *tmp_screen = NULL;
	uint8_t i;

	if (screens_storage.number == 0)
		return NULL;

	// Ищем экран по номеру, перебирая все хранилище.
	
	for (i = 0; i < screens_storage.number; i++) {
		tmp_screen = screens_storage.p_area + i;
		if (tmp_screen->n == n){
			screen = tmp_screen;
			break;
		}
	}

	return screen;
}

lcd_screen *get_or_create_screen_by_number(uint8_t n)
{

	lcd_screen *screen = NULL;
	lcd_screen *tmp_screen = NULL;
	bool screen_found;
	uint8_t i;

	// Если экранов еще нет, создаем первый.
	if (screens_storage.number == 0) {
		screen = (lcd_screen *)malloc(sizeof(lcd_screen));
		if (screen != NULL) {
			screen_init(screen, n);
			++screens_storage.number;
			screens_storage.p_area = screen;
		}
		
		return screen;
	}

	// Ищем экран по номеру, перебирая все хранилище.

	screen_found = false;

	for (i = 0; i < screens_storage.number; i++) {
		screen = screens_storage.p_area + i;
		if (screen->n == n) {
			screen_found = true;
			break;
		}
	}

	// Если экран не найден, то пытаемся создать его.
	if (!screen_found) {
		++screens_storage.number;
		tmp_screen = (lcd_screen *)realloc(screens_storage.p_area,
				screens_storage.number * sizeof(lcd_screen));

		if (tmp_screen == NULL) {
			// экран не создан - нехватка памяти
			--screens_storage.number;
			return NULL;

		} else {
			screens_storage.p_area = tmp_screen;
			
			screen = screens_storage.p_area + 
						(screens_storage.number - 1);
			screen_init(screen, n);
			
		}
	} 

	// экран найден или создан
	return screen;
}

int screen_to_LCD_by_index(uint8_t index)
{
	lcd_screen *screen;

	if (index >= screens_storage.number)
		return 1;

	screen = screens_storage.p_area + index;
	screen_to_lcd(screen, index);

	return 0;
}

int next_screen_on_LCD(bool menu_mode)
{
	uint8_t next_screen_index;
	static uint8_t old_index = LCD_START_SCREEN;
	static bool old_menu_mode = false; 
	int res;
	lcd_screen *screen;
	int i;

	if (screens_storage.number == 0)
		return 1;

	if (!menu_mode && !old_menu_mode)
		return 0;
	
	next_screen_index = shown_screen.index;
	i = 0;
	do {
		++next_screen_index;
		if (next_screen_index >= screens_storage.number)
			next_screen_index = 0;

		screen = screens_storage.p_area + next_screen_index;
		
		if (++i > screens_storage.number)
			return 0;



	} while (menu_mode ? screen->p_function == NULL :
			     (screen->hidden || screen->p_function != NULL));

	res = 0;
	if (next_screen_index != old_index)
		res = screen_to_LCD_by_index(next_screen_index);
	
	old_index = next_screen_index;

	old_menu_mode = menu_mode;
	return res;
}

void screen_to_lcd(lcd_screen *screen, uint8_t index)
{	/*
	 * Сложность алгоритма выходит из функции lcd_puts, которая пишет данные
	 * напряумю в логический экран. При условии, что lcd_puts выводит строку
	 * на активный экран получается что screen_to_lcd не видит изменения
	 * строки по сравеннию с выводимым. 
	 * Таким образом требуется установить факт изменения строки копированием
	 * выведенных данных в буфер.
	 */

	/*
	 * Если идет запрос на обновление уже отображенного экрана, то обновляем
	 * без проверки на совпадение.
	 */
	if (!shown_screen.init || shown_screen.index == index){
		line_to_lcd(0, 0, screen->line0);
		line_to_lcd(1, 0, screen->line1);
	} else {
		if (strcmp(screen->line0, shown_screen.screen.line0)
		    != 0)
			line_to_lcd(0, 0, screen->line0);

		if (strcmp(screen->line1, shown_screen.screen.line1)
		    != 0)
			line_to_lcd(1, 0, screen->line1);
	}

	shown_screen.init = true;
	shown_screen.index = index;
	memcpy(&shown_screen.screen, screen, sizeof(lcd_screen));
	return;
}

void line_to_lcd(uint8_t line, uint8_t pos, char *str)
{
	uint8_t lcd_command_line[LCD_LINE_BUFFER_SIZE];
	uint8_t sz_data_in_line;

	// todo надо бы перейти на массив линий в экране чтоб не было такого:
	if (line){
		if (strlen(str) < strlen(shown_screen.screen.line1))
			clear_line_on_lcd(1);
	} else {
		if (strlen(str) < strlen(shown_screen.screen.line0))
			clear_line_on_lcd(0);
	}

	sz_data_in_line = strlen(str);
	if (sz_data_in_line + pos > LCD_MAX_DATA_SIZE)
		sz_data_in_line = LCD_MAX_DATA_SIZE - pos;

	lcd_command_line[0] = pos;
	lcd_command_line[1] = line;
	memcpy(&lcd_command_line[2], str, sz_data_in_line);
	lcd_command_line[2 + sz_data_in_line] = END_OF_LINE_MARK;
	sz_data_in_line += 3;
	lcd_send(lcd_command_line, sz_data_in_line);
}

int lcd_send(uint8_t const *tx, size_t len)
{

	int fd;
	struct termios2 tio;

	memset(&tio, 0, sizeof(struct termios2));
	fd = open(LCD_SERIAL_PORT, O_RDWR|O_NOCTTY);
	if (fd < 0) {
		perror ("LCD Open device failure"); 
		return -1;
	}

	tio.c_cflag = 0;
	tio.c_cflag	= BOTHER | PARENB | CS8 | CLOCAL;
	tio.c_cflag &= ~PARODD;
	tio.c_iflag 	= 0;
	tio.c_oflag 	= 0;
	tio.c_lflag 	= 0;
	tio.c_ispeed 	= BITRATE;
	tio.c_ospeed	= BITRATE;
	ioctl(fd, TCSETS2, &tio);

	write(fd, tx, len);
	close (fd);

	return 0;
}

void screen_init(lcd_screen *screen, uint8_t n)
{
	screen->n = n;
	memset(screen->line0, LCD_BLANK_CODE, LCD_MAX_DATA_SIZE);
	memset(screen->line1, LCD_BLANK_CODE, LCD_MAX_DATA_SIZE);
	screen->line0[0] = '\0';
	screen->line1[0] = '\0';
	screen->hidden = false;
	screen->p_function = NULL;
}

int16_t get_screen_index_by_n(uint8_t n){

	bool screen_found = false;
	lcd_screen *tmp_screen = NULL;
	uint8_t i;

	if (screens_storage.number == 0)
		return -1;

	// Ищем экран по номеру, перебирая все хранилище.
	for (i = 0; i < screens_storage.number; i++) {
		tmp_screen = screens_storage.p_area + i;
		if (tmp_screen->n == n){
			screen_found = true;
			break;
		}
	}

	if (screen_found)
		return (int16_t)i;
	else
		return -1;
}

void clear_line_on_lcd(uint8_t line) {
	uint8_t blank_line[3];
	blank_line[0] = 0;
	blank_line[1] = line;
	blank_line[2] = END_OF_LINE_MARK;
	lcd_send(blank_line, 3);
}

int create_menu(uint8_t n, char *str_line0, char *str_line1,
		int (*p_function)(void))
{
	lcd_screen *screen;
	size_t len_str_line0, len_str_line1;

	len_str_line0 = strlen(str_line0);
	len_str_line1 = strlen(str_line1);

	if (n <= SCREENS_INDEX_MAX
	    || n > MENU_SCREENS_INDEX_MAX
	    || len_str_line0 > LCD_MAX_DATA_SIZE
	    || len_str_line1 > LCD_MAX_DATA_SIZE)
		return -1;

	/* 
	 * Cоздаем экран тут, и заполняем параметры,что бы он не участвовал в
	 * пролистывании пока идет заполнение параметров.
	 */
	screen = get_or_create_screen_by_number(n);
	screen->p_function = p_function;

	lcd_puts(n, 0, 0, str_line0);
	lcd_puts(n, 1, 0, str_line1);

	return 0;
}

long int get_curent_time(void)
{
	struct timeval tv;

	gettimeofday(&tv,NULL);
	return tv.tv_sec * 1000 + round(tv.tv_usec / 1000.0f);
}

int menu_fn_sync_rts(void)
{
	_start_fw = true;
	return 0;
}

int menu_fn_exit(void)
{
	_sys_menu_mode = false;
	next_screen_on_LCD(_sys_menu_mode);

	return 0;
}

int menu_fn_net_show(void)
{
	struct ifaddrs *ifaddr, *ifa;
	int res;
	char host[NI_MAXHOST];
	char mask[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		return -1;
	}
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;  

		res = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
				  host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		res = getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in),
				  mask, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, NET_NAME) == 0)
		     &&(ifa->ifa_addr->sa_family == AF_INET)) {
			if (res != 0) {
				printf("getnameinfo() failed: %s\n",
					gai_strerror(res));
				return -1;
			}

			lcd_puts(MENU_NET_SHOW_SCREEN, 0, 0, host);
			lcd_puts(MENU_NET_SHOW_SCREEN, 1, 0, mask);

		}
	}

	freeifaddrs(ifaddr);
	return 0;
}
