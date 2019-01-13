/*
 * Модуль управления экраном.
 * Внимание:
 * 	Модуль не доработан до конца. Несовсем эвфективно работает фунцкционал
 * 	меню.
 *
 * Модуль реализует 256 буферов экрана. Каждый буфер содержит информацию
 * двух линий LCD. При нажатии клавиши С на внешней панели ЦПУ, модуль выводит
 * данные буферов на LCD поочередно. 
 * Каждый буфер в пределах модуля именнуется экраном (screen).
 * Каждому экрану может быть установлена в соответвие функция, которая будет
 * вызываться при выводе экрана на LCD. Это может быть полезным, если требуется
 * обновлять информацию экрана при его высвечивании. Например информация 
 * сетевых настроек.
 * Каждому экрану также может быть назначена функция меню. В этом случае экран
 * становится элементом меню, функция которого может быть вызвана длительным
 * нажатием кнопки С на передней панели ЦПУ. 
 * Экраны с номерами до 100 зарезервированы под системную информацию.
 * Экраны с номерами от 100 до 200 - пользовательские
 * Экраны от 200 по 255 - экраны меню.
 */

#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconLCDDep.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <asm-generic/termbits.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
// #include <pthread.h>


/* 
 * Количество экранов для отображения. Искуственное ограничение для
 * для предотвращения утечки памяти. Память для экранов выделяется динамически.
 * По сути количество экранов в этом компоненте ограничевается размерностью
 * переменной lcd_screen.n. Таким образом ошибка в МЭК программе может привести
 * к созданию экранов количеством соотвевенно размерности lcd_screen.n.
 * Для предотвращения утечки искуственно водится искуственное ограничение
 * SCREENS_INDEX_MAX.
 *
 * Следует учитывать:
 *	Зарезервированный индекс под системный экран - 0
 *	От SCREENS_INDEX_MAX + 1 до MENU_SCREENS_INDEX_MAX
 *	лежат экраны меню.
 */
#define SCREENS_INDEX_MAX 	200 	// количество экранов
#define MENU_SCREENS_INDEX_MAX 	254 	// Максимальный индекс меню

/*
 * Номер окна выхода из меню.
 * При создании меню из МЭК к номеру окна меню пердаваемого в функцию
 * будет прибавляться этот параметр. Например, при создании меню с параметром
 * screen == 1:
 * 	menu_item_create(1, 'test1', 'test2', adr(test_function))
 * будет создан экран 1 + MENU_ITEM_EXIT
 */
#define MENU_ITEM_EXIT 201

#define SWITCH_TO_DEFAULT_SCREEN_INTERVAL 30000// milliseconds
#define MENU_MODE_BTN_PRESSED_INTERVAL 3000// milliseconds

#define LCD_MAX_LINE_INDEX	1 	// 0-1 строи экрана
#define LCD_MAX_POSITION_INDEX	249	// 0-249 позиции в линии
#define LCD_MAX_DATA_SIZE	250	// 250 данные
#define LCD_LINE_BUFFER_SIZE	253	// 250 данные + 3 разметочные байты
#define END_OF_LINE_MARK 	0xFF
#define LCD_BLANK_CODE		0x20	// пробел

#define IP_MASK_SCREEN 1
#define VERSION_SCREEN 2

#define ERR_PARAM 1
#define ERR_NO_SCREEN_IN_MEM 2
#define SCREEN_BUSY 3

#define LCD_SERIAL_PORT "/dev/ttyS2"
#define BITRATE 57600

#define PRESSED_BUTTON_CODE 48 // ascii 0
#define NOT_PRESSED_BUTTON_CODE 49 // ascii 1


uint8_t _default_screen_index = 0;
static bool _is_emu = false;

/*
 * Структура хранения экрана в памяти
 */
typedef struct lcd_screen {
	uint8_t n;				// номер экрана
	char line0[LCD_MAX_DATA_SIZE + 1];// строка LCD
	char line1[LCD_MAX_DATA_SIZE + 1];// вторая строка LCD
	bool hidden;	// показывает отображать или нет этот экран
	// показывает является ли следующий указатель, указателем на МЭК функцию
	bool is_IEC_fn;
	void (*p_function)(void); // функция меню
	// функция вызываемая при открытии экрана
	void (*p_fn_open_screen)(void);

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
	/* 
	 * Независимое сохранение данных экрана нужно для дальнейшего
	 * сравнения при выводе. Требуется при ввызове lcd_puts на активный 
	 * экран. lcd_puts выводит сразу в буфер экрана. И при активном экране
	 * в дальнейшем несчем сравнивать. Для этого введен saved_screen.
	 */
	lcd_screen screen;
	bool init;
	bool lock;
} _shown_screen;


long int _zerro_time_point_ms = 0;
long int _curent_time_point_ms;
struct timeval _tv;
long int _btn_pressed_time_point_ms;
long int _btn_un_pressed_time_point_ms; 


bool menu_mode = false;
bool _enable_switching_next_screen;


/*
 * Определяет нажата ли кнопка по переднему фронту сигнала
 */
char read_button(void);
static bool rtrig_button(void);
static bool ftrig_button(void);
static bool is_button_pressed(void);
static bool is_button_un_pressed(void);

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
int next_screen_on_LCD(void);

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
 * Сложность алгоритма выходит из функции lcd_puts, которая пишет данные
 * напряумю в логический экран. При условии, что lcd_puts выводит строку на
 * активный экран получается что screen_to_lcd не видит изменения строки по 
 * сравеннию с выводимым. Таким образом требуется установить факт изменения
 * строки копированием выведенных данных в буфер (_shown_screen.saved_screen).
 * Возвращает -1 в случае сработки блокировки.
 */
int screen_to_lcd(lcd_screen *screen, uint8_t index);

/*
 * Посылает данные в LCD.
 * 0 - успех
 */
int lcd_send(uint8_t const *tx, size_t len);

/*
 * Обертка для МЭК функции lcd_puts.
 * Создана для блее удобного использования реализации lcd_puts внутри
 * компонента. Обычный lcd_puts имеет интерфейс МЭК функции, что требует
 * заполнять структуру входных данных. _lcd_puts заполняет эту структуру сам.
 */
void _lcd_puts(uint8_t n, uint8_t line, uint8_t pos, char *str);

/*
 * Добавляет к функционалу _lcd_puts привязку функции при открытии окна
 */
void _lcd_puts_fn(uint8_t n, uint8_t line, uint8_t pos, char *str,
		void (*p_fn_open_screen)(void));

/*
 * Основная функция формирования экранов. МЭК функция lcd_puts вызывает именно
 * lcd_puts2 после проверок границ предоставляемых МЭК пользователю. lcd_puts2
 * позволяет выйти за границы, к примеру ссистемным функциям, для вывода в
 * зарезервированные экраны.
 */
void lcd_puts2(lcd_puts_struct *p);

/*
 * Вызов lcd_puts2 с заполнением входной структуры. Для внутреннего
 * использования в компоненте.
 */
void _lcd_puts2(uint8_t n, uint8_t line, uint8_t pos, char *str);

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
		void (*p_function)(void), bool is_iec_fn);

void call_menu_function(void);

/*
 * Секция функций МЕНЮ.
 */

void menu_fn_exit(void);
void lcd_put_ip_and_mask(void);
void lcd_put_version(void);

USE_STMT

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each
 * component. Used to exchange function pointers with the component manager.
 * </description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports
 *					    component functions
 *		pfImportFunctions	OUT Pointer to function that imports
 *					    functions from other components
 *		pfGetVersion		OUT Pointer to function to get component
 *					    version
 *		pfRegisterAPI		IN  Pointer to component mangager
 *					    function to register a api function
 *		pfGetAPI		IN  Pointer to component mangager
 *					    function to get a api function
 *		pfCallHook		IN  Pointer to component mangager
 *					    function to call a hook function
 * </param> 
 * <result>ERR_OK if component could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = NULL;
	pInitStruct->pfDeleteInstance = NULL;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	return ERR_OK;
}

/**
 * <description>Publish exported functions to the component manager, to make
 * them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Import function pointers from other components. Use generated 
 * macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/**
 * <description>Hook function to get all broadcast hooks of the component
 * manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h
 * for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See
 * definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See
 * definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook){
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();
		lcd_init();
		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		gettimeofday(&_tv,NULL);
		_curent_time_point_ms = _tv.tv_sec * 1000 +
					round(_tv.tv_usec / 1000.0f);

		if (rtrig_button()) {
			_btn_pressed_time_point_ms = _curent_time_point_ms;
			_enable_switching_next_screen = true;
		}
		if (ftrig_button()) {
			_btn_un_pressed_time_point_ms = _curent_time_point_ms;

			if (_enable_switching_next_screen)
				next_screen_on_LCD();
		}

		if (is_button_pressed()){
			if (_curent_time_point_ms - _btn_pressed_time_point_ms
			    > MENU_MODE_BTN_PRESSED_INTERVAL){

				if (menu_mode) {
					// выполняем функцию меню
					call_menu_function();
				} else {
					menu_mode = true;
					next_screen_on_LCD();
				}

				_btn_pressed_time_point_ms =
							_curent_time_point_ms;

				_enable_switching_next_screen = false;
			}
		}

		if (!menu_mode) {
			if (_curent_time_point_ms - _zerro_time_point_ms > 
			    SWITCH_TO_DEFAULT_SCREEN_INTERVAL
			    && _shown_screen.index != _default_screen_index)
				screen_to_LCD_by_index(_default_screen_index);
		}

		break;

#ifndef RTS_COMPACT_MICRO
	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		// if (CHK_LogAdd)
		//	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
		//		   ERR_OK, 0, "CH_EXIT");
		EXIT_STMT;
		break;
#endif

	default:
		break;
	}
	return ERR_OK;
}

void lcd_init(void)
{
	
	char str[4];
	int fd;

	if (!_is_emu) {

		/*
		 * Активируетм кнопку.
		 */
		strcpy(str, "55");
		fd = open("/sys/class/gpio/export", O_WRONLY);
		write(fd, str, strlen(str));
		close(fd);

		strcpy(str, "in");
		fd = open("/sys/class/gpio/gpio55/direction", O_WRONLY);
		write(fd, str, strlen(str));
		close(fd);
	}

	/*
	 * Инициализация области хранения экранов.
	 */
	screens_storage.p_area = NULL;
	screens_storage.number = 0;

	/*
	 * Инициализация отображаемого экрана. NULL - нет отображаемого экрана
	 */
	_shown_screen.init = false;
	_shown_screen.lock = false;
	/*
	 * Вывод приглашения через образ МЭК функции
	 */

	_lcd_puts(0, 0, 0, "");
	_lcd_puts(0, 1, 0, "");

	_lcd_puts_fn(IP_MASK_SCREEN, 0, 0, "", &lcd_put_ip_and_mask);
	_lcd_puts_fn(VERSION_SCREEN, 0, 0, "", &lcd_put_version);


	create_menu(MENU_ITEM_EXIT, "RTS Menu", "Exit", &menu_fn_exit, false);

	return;
}

void CDECL CDECL_EXT lcd_puts(lcd_puts_struct *p)
{

/*
 * Вывод на экран осуществляется построчно. 
 * Входы по указател p:
 * 	RTS_IEC_USINT usiScreen;			
 *	RTS_IEC_USINT iLine;				
 *	RTS_IEC_USINT iPos;					
 *	RTS_IEC_STRING stData[252];	
 * Выход:		
 *	RTS_IEC_INT lcd_puts;	
 */

	if (p->usiScreen > SCREENS_INDEX_MAX ||
	    p->iLine > LCD_MAX_LINE_INDEX ||
	    p->iPos > LCD_MAX_POSITION_INDEX ||
	    strlen(p->stData) > LCD_MAX_DATA_SIZE) {

		p->lcd_puts = -ERR_PARAM;
		return;
	}

	lcd_puts2(p);

	return;
}

void lcd_puts2(lcd_puts_struct *p)
{
	lcd_screen *screen;
	char *line;
	size_t sz_data;
	uint8_t sz_data_in_line;
	uint8_t old_str_len;
	int result;

	sz_data = strlen(p->stData);

	screen = get_or_create_screen_by_number(p->usiScreen);
	if (screen == NULL) {
		p->lcd_puts = -ERR_NO_SCREEN_IN_MEM;
	} else {

		// формирование строки для  LCD
		if (p->iLine)
			line = screen->line1;
		else
			line = screen->line0;

		old_str_len = strlen(line);
		line[old_str_len] = LCD_BLANK_CODE; // убираем \0

		if (sz_data == 0){
			// sz_data == 0 пустая строка - команда обрезки строки
			// по заданной позиции.
			line[p->iPos] = '\0';
		} else {
			if (sz_data + p->iPos > LCD_MAX_DATA_SIZE)
				sz_data = LCD_MAX_DATA_SIZE - p->iPos;

			memcpy(line + p->iPos, p->stData, sz_data);

			// избегаем обрезание длинной строки короткой
			if (old_str_len > p->iPos + sz_data)
				line[old_str_len] = '\0';
			else
				line[p->iPos + sz_data] = '\0';
		}

		/*
		 * Производим вывод на экран только если экран активный
		 * или небыло еще активных экранов.
		 */
		if (!_shown_screen.init || screen->n == _shown_screen.screen.n)
			result = screen_to_lcd(screen,
					get_screen_index_by_n(screen->n));

		if (result < 0)
			p->lcd_puts = -SCREEN_BUSY;
		else
			p->lcd_puts = sz_data + p->iPos;
	}

	return;
}

char read_button(void)
{
	int fd;
	char ascii_code;

	if (_is_emu)
		return NOT_PRESSED_BUTTON_CODE;

	fd = open("/sys/class/gpio/gpio55/value", O_RDONLY);
	read(fd, &ascii_code, 1);
	close(fd);

	return ascii_code;
}
/*
 * Ловит передний фронт нажатия кнопки.
 * По переднему фронту возвращает true.
 */
static bool rtrig_button(void)
{
	// GPIO имеет инверсную логику
	// #define NOT_PRESSED_BUTTON_CODE 49 // ascii 1
	// #define PRESSED_BUTTON_CODE 48 // ascii 0

	bool button_pressed;
	char ascii_code;
	static char old_state = 49; // ascii 1 соответвует НЕнажатой кнопке
	
	ascii_code = read_button();

	/* 
	 * Логика у кнопок инверсная, данные считываются в ascii кодах.
	 * 1 -> 49 кнопка отжата, 0 -> 48 кнопка нажата  
	 */
	if (ascii_code < old_state)
		button_pressed = true;
	else
		button_pressed = false;

	old_state = ascii_code;

	return button_pressed;
}

/*
 * Ловит передний фронт нажатия кнопки.
 * По заднему фронту возвращает true.
 */
static bool ftrig_button(void)
{

	bool button_un_pressed;
	char ascii_code;
	static char old_state = 49; // ascii 1 соответвует НЕнажатой кнопке

	ascii_code = read_button();

	/* 
	 * Логика у кнопок инверсная, данные считываются в ascii кодах.
	 * 1 -> 49 кнопка отжата, 0 -> 48 кнопка нажата  
	 */
	if (ascii_code > old_state)
		button_un_pressed = true;		
	else
		button_un_pressed = false;

	old_state = ascii_code;

	return button_un_pressed;
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

/*
 * Выдает true если кнопка отжата в текущий момент
 */
static bool is_button_un_pressed(void)
{
	if (read_button() == NOT_PRESSED_BUTTON_CODE) 
		return true;
	else
		return false;
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

	uint8_t test;

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

	if (screen->p_fn_open_screen != NULL)
		(*screen->p_fn_open_screen)();


	_zerro_time_point_ms = _curent_time_point_ms;
	screen_to_lcd(screen, index);

	return 0;
}

int next_screen_on_LCD(void)
{

	uint8_t next_screen_index;
	lcd_screen *screen;
	int i;

	if (screens_storage.number == 0)
		return 1;

	next_screen_index = _shown_screen.index;

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

	return screen_to_LCD_by_index(next_screen_index);
}

int screen_to_lcd(lcd_screen *screen, uint8_t index)
{	

	/*
	 * Переменная i ведет осчет количества запросов обновления активного
	 * экрана. Если количество обновлений более 3 раз, то к активному
	 * экрану применяются общие правила сравнения строк, иначе просто
	 * обновляем.
	 */
	static int i = 0;
	/*
	 * _shown_screen - глобальный разделяемый ресурс. Вызов screen_to_lcd
	 * может осуществляться с разных процессов, следовательно _screen_to_lcd
	 * должен быть защищен светофором - взаимной блокировкой.
	 * Но просто ожидать освобождения ресурас нельзя, потому что зависание
	 * одного процесса установившего блокировку приведет к зависанию всех
	 * остальных процессов, пытающихся вывести что-либо. Поэтому просто
	 * пропускаем действие.  
	 */
	if (_shown_screen.lock)
		return -1;
	_shown_screen.lock = true;

	/*
	 * Если идет запрос на обновление уже отображенного экрана, то обновляем
	 * без проверки на совпадение.
	 */
	if ((!_shown_screen.init || _shown_screen.index == index)&& i < 3){
		line_to_lcd(0, 0, screen->line0);
		line_to_lcd(1, 0, screen->line1);
		i++;
	} else {
		if (strcmp(screen->line0, _shown_screen.screen.line0)
		    != 0){
			line_to_lcd(0, 0, screen->line0);
			i = 0;
		}

		if (strcmp(screen->line1, _shown_screen.screen.line1)
		    != 0) {
			line_to_lcd(1, 0, screen->line1);
			i = 0;
		}

	}


	_shown_screen.init = true;
	_shown_screen.index = index;
	memcpy(&_shown_screen.screen, screen, sizeof(lcd_screen));
	_shown_screen.lock = false;

	return 0;
}

void line_to_lcd(uint8_t line, uint8_t pos, char *str)
{
	uint8_t lcd_command_line[LCD_LINE_BUFFER_SIZE];
	uint8_t sz_data_in_line;

	// todo надо бы перейти на массив линий в экране чтоб не было такого:
	if (line){
		if (strlen(str) < strlen(_shown_screen.screen.line1))
			clear_line_on_lcd(1);
	} else {
		if (strlen(str) < strlen(_shown_screen.screen.line0))
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

	if (_is_emu)
		return 0;

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
	screen->is_IEC_fn = false;
	screen->p_function = NULL;
	screen->p_fn_open_screen = NULL;
}

void _lcd_puts(uint8_t n, uint8_t line, uint8_t pos, char *str)
{
	lcd_puts_struct p = {
		.usiScreen = n,
		.iLine = line,
		.iPos = pos
	};
	strcpy(p.stData, str);
	lcd_puts(&p);
}

void _lcd_puts_fn(uint8_t n, uint8_t line, uint8_t pos, char *str,
		void (*p_fn_open_screen)(void))
{

	lcd_screen *screen;
	screen = get_or_create_screen_by_number(n);
	screen->p_fn_open_screen = p_fn_open_screen;
	_lcd_puts(n, line, pos, str);

}

void _lcd_puts2(uint8_t n, uint8_t line, uint8_t pos, char *str)
{
	lcd_puts_struct p = {
		.usiScreen = n,
		.iLine = line,
		.iPos = pos
	};
	strcpy(p.stData, str);
	lcd_puts2(&p);
}

uint32_t CDECL CmpEmiconLCD_puts(uint8_t n, uint8_t line, uint8_t pos,
				 char *str)
{
	_lcd_puts(n, line, pos, str);
	return 0;
}

void CDECL CDECL_EXT display_screen(display_screen_struct *p)
{

	lcd_screen *screen = NULL;
	lcd_screen *tmp_screen = NULL;
	uint8_t i;

	if (_shown_screen.screen.n == p->n)
		return;

	p->display_screen = -1;
	if (screens_storage.number == 0)
		return;

	// Ищем экран по номеру, перебирая все хранилище.
	for (i = 0; i < screens_storage.number; i++) {
		tmp_screen = screens_storage.p_area + i;
		if (tmp_screen->n == p->n){
			screen = tmp_screen;
			break;
		}
	}

	if (screen != NULL){
		screen_to_LCD_by_index(i);
		p->display_screen = 0;
	}

	return;
}

uint32_t CDECL CmpEmiconLCD_display_screen(uint8_t n){

	display_screen_struct p;
	p.n = n;
	display_screen(&p);
	return 0;
}

void CDECL CDECL_EXT get_current_screen(get_current_screen_struct *p)
{

	p->get_current_screen = _shown_screen.screen.n;
}

void CDECL CDECL_EXT get_default_screen(get_default_screen_struct *p)
{

	lcd_screen *screen;
	screen = screens_storage.p_area + _default_screen_index;
	p->get_default_screen = screen->n;
}


void CDECL CDECL_EXT set_default_screen(set_default_screen_struct *p)
{	

	int16_t i;

	p->set_default_screen = -1;
	i = get_screen_index_by_n(p->n);
	
	if (i >= 0){
		_default_screen_index = (uint8_t)i;
		p->set_default_screen = 0;
		screen_to_LCD_by_index(_default_screen_index);
	}

	return;
}

void CDECL CDECL_EXT set_visibility(set_visibility_struct *p)
{

	lcd_screen *screen;

	p->set_visibility = -1;
	screen = get_screen_by_number(p->n);
	if (screen != NULL) {
		screen->hidden = p->visibility;
		p->set_visibility = 0;
	}

	return;
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

/*
 * Очищает одну линию на LCD, но не в буфере.
 */

void clear_line_on_lcd(uint8_t line) {
	uint8_t blank_line[3];
	blank_line[0] = 0;
	blank_line[1] = line;
	blank_line[2] = END_OF_LINE_MARK;
	lcd_send(blank_line, 3);
}

int create_menu(uint8_t n, char *str_line0, char *str_line1,
		void (*p_function)(void), bool is_iec_fn)
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
	screen->is_IEC_fn = is_iec_fn;

	_lcd_puts2(n, 0, 0, str_line0);
	_lcd_puts2(n, 1, 0, str_line1);

	return 0;
}


void menu_fn_exit(void)
{
	menu_mode = false;
	screen_to_LCD_by_index(_default_screen_index);
	return;
}

void lcd_put_ip_and_mask(void)
{
	struct ifaddrs *ifaddr, *ifa;
	int res;
	char host[NI_MAXHOST];
	char mask[NI_MAXHOST];

	if (getifaddrs(&ifaddr) == -1) {
		perror("getifaddrs");
		return;
	}

	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		if (ifa->ifa_addr == NULL)
			continue;  

		res = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
				  host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
		res = getnameinfo(ifa->ifa_netmask, sizeof(struct sockaddr_in),
				  mask, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);

		if ((strcmp(ifa->ifa_name, "eth0") == 0)
		    &&(ifa->ifa_addr->sa_family == AF_INET)) {
			if (res != 0) {
				printf("getnameinfo() failed: %s\n",
					gai_strerror(res));
				return;
			}

			_lcd_puts(IP_MASK_SCREEN, 0, 0, host);
			_lcd_puts(IP_MASK_SCREEN, 1, 0, mask);

		}
	}

	freeifaddrs(ifaddr);
	return;
}

void lcd_put_version(void){
	#define BUF_SIZE 8
	#define VERSION_FILE "version.txt"
	int fd;
	int ret_in;
	char buff[BUF_SIZE + 1];
	static bool init = false;

	if (!init)
		init = true;
	else
		return;

	fd = open(VERSION_FILE, O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Файл версий НЕ открылся!\n");
		strcpy(buff, "Not found");
	} else {
		ret_in = read(fd, &buff, BUF_SIZE);
		buff[ret_in] = '\0';
		close(fd);
	}

	_lcd_puts(VERSION_SCREEN, 0, 0, "FW  Ver.");
	_lcd_puts(VERSION_SCREEN, 1, 0, buff);

	return;
}

void CDECL CDECL_EXT menu_item_create(menu_item_create_struct *p)
{

	if (p->screen > 9)
		p->screen = 9;
	if (p->screen < 1)
		p->screen = 1;

	p->screen += MENU_ITEM_EXIT;
	create_menu(p->screen, p->st_line1, p->st_line2,
		    (void (*)(void))p->p_menu_function, true);

}

void call_menu_function(void)
{
	PFEVENTCALLBACKFUNCTION *ppfCallbackFunction;
	if (_shown_screen.screen.is_IEC_fn) {
		ppfCallbackFunction =
		      (PFEVENTCALLBACKFUNCTION *)_shown_screen.screen.p_function;

		CAL_SysCpuCallIecFuncWithParams(
					(RTS_VOID_FCTPTR)(*ppfCallbackFunction),
					0, 0);
	} else {
		(*_shown_screen.screen.p_function)();
	}
	menu_fn_exit();
}
