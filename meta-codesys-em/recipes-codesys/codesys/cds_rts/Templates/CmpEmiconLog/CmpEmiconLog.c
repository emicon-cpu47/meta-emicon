/*
 * Модуль реализует кольцевой буфер записи лога.
 *
 * ВНИМАНИЕ!
 * Модуль строго зависим от модуля CmpEmiconMemManager. CmpEmiconMemManager
 * должен подключатся в конфигурации рантайма строго с большим порядковым
 * номером.
 *
 * Память для ведения записи модуль выделяет из области nvram. 
 * Начало памяти определяется двумя сценариями:
 *  1) Если NVRAM (задается в конфигурации рантайма [CmpEmiconMemManager]->
 *     NVRAMSize) до 256К, то буфер лога начинается строго со смещения 0x2F000 и
 *     имеет строгий размер в 4К (0x1000)
 *  2) Если NVRAM > 256К, то буфер располагается сразу за %M областью и имеет
 *     размер заданный в конфигурации рантайма [CmpEmiconLog]->BufferSize
 * 
 * Физическая память nvram отображается в виртуальное пространство размером
 * кратным размеру страницы. При этом используется только тот размер, который
 * указан в конфигурационном файле. Поэтому рекомендуется указывать размер
 * памяти кратным странице памяти (4Кб). 
 * Пример параметров конфигурационного файла:
 *
 *	[CmpEmiconLog]
 *	BufferSize=4096
 *
 * Первые 14 байт выделенной памяти используется для хранения технических
 * данных состояния буфера. Остальной размер отводится под записи лога.
 *
 * Принцип работы:
 * Модуль разработан для записи трех видов сообщений разной длины. Сообщения
 * могут быть записаны в любой последовательности в любом количестве.
 * При достижении конца буфера, сообщения записываются с начала буфера, затирая
 * наиболее старые записи. Данные записываются последовательно и без пропуска
 * байт в конце буфера. Другими словами, сообщение, которое полностью не влезает
 * в конец буфера, записывается до конца буфера и переноситься на начало буфера.
 * 
 */

#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconLogDep.h"

#include "stdint.h"
#include "errno.h"
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <CP56Time2a.c>

#define MEM_FILE_NAME "memnvram.txt"
static bool _is_emu = false;

#define MARK_SYS_LOG	0x80
#define MARK_TI_LOG	0x40
#define MASK_ALL_MARK	0x3F

// начало физического адреса nvram
#define NVRAM_CS3_MEM_ADDRESS 0x2000000; 

/* 
 * Используется для определения состояния буфера:
 * если указатели начала и конца одинаковы и указывают на NONE, то буфер пуст.
 * Считается, что тип фрейма на который указывает указатель начала не может быть
 * равен NONE. В данном случае 0. 
 */
#define NONE 0 

// зарезервированные собственные системные события
#define OWN_EVENT_ID_CLR 0 	// очистка буфера
#define OWN_EVENT_ID_STOP 1 	// останов МЭК приложения
#define OWN_EVENT_ID_START 2 	// старт МЭК приложения

/*
 * Определение пордка байт в системе нужно для правильного
 * переворота данных приходящих в параметрах функций записи
 * в последовательность записываемую в память. 
 * Последовательность в памяти строгая.
 */
const int _is_bigendian_i = 1;
#define is_bigendian() ( (*(uint8_t*)&_is_bigendian_i) == 0 )


/*
 * Структуры кадров записи для каждого типа событий.
 * Внимание! Структуры обязатяельно должны быть объявлены между
 * #pragma pack(push, 1) и #pragma pack(pop). Ничего между структурами объявлять
 * не следует. Иначе выравнивание может испортить жизнь.
 */
#pragma pack(push, 1)
typedef struct own_event_frame {
	uint8_t class_id;
	uint32_t value;
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

#define FRAME_TYPE_OWN_EVENT 1
#define FRAME_TYPE_TS 2
#define FRAME_TYPE_TI 3

static bool _init_done = false;
/*
 * Указатели на параметры буфера (данные инициализации). Эти данные лежат в
 * голове бувера.
 * TODO: Оформить ее в структуру, но что-то не получилось с первого раза.
 */
uint16_t *_init_mark;
uint32_t *_offset_first_record;
uint32_t *_offset_end_of_records;
uint32_t *_log_mem_size;

/*
 * Дирикторя сохранения файлов лога. По умолчанию сохранит в папку с рантаймом.
 */
char _log_folder[] = "/home/plc/log/";

/*
 * Указатели на начало первой записи и последний байт последней записи.
 * При старте расчитываются смещением от головы (_offset_first_record,
 * _offset_end_of_records). При их изменении нужно соответсвенно править
 * смещение.
 */
uint8_t *_p_first_record;
uint8_t *_p_end_of_records;

/*
 * Маркировка первых двух байт (_init_mark), означающее инициализацию буфера
 * из мусора LOG_INIT_MARK, либо буфер занят записью/чтенеием LOG_INIT_MARK_BUSY.
 */
#define LOG_INIT_MARK 0x55aa
#define LOG_INIT_MARK_BUSY 0x65aa


// Указатели на начало и коенец буфера лог. Исключает данные инициализации.
uint8_t *_p_log_buff, *_p_log_buff_end;

// Размер буфера считывается из конфигурации. 
size_t _sz_log_buff;


// адрес системы лога - расчитывается автоматически
static uint32_t _nvram_log_mem_address; 

/*
 * Действительный размер выделенной памяти под весь Лог включая инициализацию.
 */ 
size_t _nvram_allocated_mem_size = 0;

// Указатель на мапированный блок памяти Лога
static void *_p_map_nvram_mem = NULL;

// Дескрипшин файла мапирования памяти
static int _fd_nvram;

static bool _debug_log;

// указатели для последовательного чтения буфера
static uint8_t *_p_first_record_read;
static uint8_t *_p_end_of_frame_read;

static RTS_HANDLE _s_hEventAppDownloadDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventStopDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventPrepareStart = RTS_INVALID_HANDLE;

/*
 * Создает запись в логе собественного системного события.
 */
void _create_own_sys_event(uint32_t evt);

int init_logger(void);
int set_init_offsets(void);
size_t size_of_free_space(void);
int write_buffer(uint8_t *p_data, size_t size);
int read_buffer(uint8_t *p_data, uint8_t *p_first_byte, size_t size);
int release_space(size_t size);
int in_array(uint8_t *array, size_t size, uint8_t look_for);
void get_actual_time(date_and_time *data);
void actual_time_to_CP56Time(uint8_t *data);

uint16_t reverse_uint16 (uint16_t s);

int read_sys_log(uint8_t *frame, char *str);
int read_ts_log(uint8_t *frame, char *str);
int read_ti_log(uint8_t *frame, char *str);

uint8_t* shift_pointer_along_buffer(uint8_t *p_begin, size_t offset);
int get_type_of_frame(uint8_t *frame);
int buffer_to_file(void);
bool is_buffer_accessable(void);

// функция для регистрации обработчиков событий
void register_events_handler(void);

static void handler_evt_download_done(EventParam *pEventParam);
static void handler_evt_stop_done(EventParam *pEventParam);
static void handler_evt_prepare_start(EventParam *pEventParam);


void CDECL CDECL_EXT get_next_log_item(get_next_log_item_struct *p)
{
	int type_of_frame;
	size_t offset = 0;

	if (!_init_done){
		sprintf(p->log_str, "Error: The buffer is not initialized!\n");
		p->get_next_log_item = 0;
		return;
	}

	if (_p_first_record == _p_end_of_records) {
		sprintf(p->log_str, "EOF");
		p->get_next_log_item = 0;
		return;
	}

	if (p->get_first)
		_p_first_record_read = _p_first_record;

	type_of_frame = get_type_of_frame(_p_first_record_read);

	if (type_of_frame < 0){
		p->get_next_log_item = type_of_frame;
		return;
	}

	switch (type_of_frame) {
	case FRAME_TYPE_OWN_EVENT:
		read_sys_log(_p_first_record_read, p->log_str);
		offset = SIZE_OF_OWN_EVENT;		
	break;

	case FRAME_TYPE_TS:
		if (0 == read_ts_log(_p_first_record_read, p->log_str))
			offset = SIZE_OF_TS;
	break;

	case FRAME_TYPE_TI:
		if (0 == read_ti_log(_p_first_record_read, p->log_str))
			offset = SIZE_OF_TI;
	break;
	}

	_p_end_of_frame_read = shift_pointer_along_buffer(
					_p_first_record_read, offset - 1);


	if (_p_end_of_frame_read == _p_end_of_records){
		p->get_next_log_item = 0;	// записей больше нет.
	} else {
		_p_first_record_read = shift_pointer_along_buffer(
						_p_first_record_read, offset);
		p->get_next_log_item = 1;	// означает - есть еще записи.
	}

	return;
}

void print_data()
{
	int i;

	printf("__________\n");
	for (i = 0; i < _sz_log_buff; i++)
		if (_p_log_buff + i == _p_first_record)
			printf("%p - %x B\n", _p_log_buff + i, _p_log_buff[i]);

		else if (_p_log_buff + i == _p_end_of_records)
			printf("%p - %x E\n", _p_log_buff + i, _p_log_buff[i]);

		else 
			printf("%p - %x\n", _p_log_buff + i, _p_log_buff[i]);

	printf("==========\n");
}

USE_STMT

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI		IN	Pointer to component mangager function to get a api function
 *		pfCallHook		IN	Pointer to component mangager function to call a hook function
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
 * <description>Publish exported functions to the component manager, to make them available for other components.
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
 * <description>Import function pointers from other components. Use generated macro IMPORT_STMT.</description>
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
 * <description>Hook function to get all broadcast hooks of the component manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See definitions in CmpItf.h for details.</param>  
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
		register_events_handler();
		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		break;

	case CH_EXIT3: 
		if (CHK_EventUnregisterCallbackFunction)
			CAL_EventUnregisterCallbackFunction(
				_s_hEventAppDownloadDone,
				handler_evt_download_done);
		if (CHK_EventClose)
			CAL_EventClose(_s_hEventAppDownloadDone);

		munmap(_p_map_nvram_mem, _nvram_allocated_mem_size);
		break;
	
	default:
		break;
	}
	return ERR_OK;
}

 static void handler_evt_download_done(EventParam *pEventParam)
{
	/* Use pEventParam->CmpIdProvider to identify the component that posts 
	the event. Note that pEventParam->EventId is not unique in the system */
	switch (pEventParam->CmpIdProvider){
	case CMPID_CmpApp:
		init_logger();
		break;

	default:
		break;
	}
}
static void handler_evt_stop_done(EventParam *pEventParam)
{
	if (pEventParam->CmpIdProvider != CMPID_CmpApp)
		return;

	_create_own_sys_event(OWN_EVENT_ID_STOP);

}
static void handler_evt_prepare_start(EventParam *pEventParam)
{
	if (pEventParam->CmpIdProvider != CMPID_CmpApp)
		return;

	_create_own_sys_event(OWN_EVENT_ID_START);
}

void _create_own_sys_event(uint32_t evt) {
	write_sys_log_struct param = {
		.byClassId = 0,
		.dwValue = evt
	};
	write_sys_log(&param);
}

int init_logger(void)
{
	int fd;
	char str[200];
	int nbytes;
	uint32_t sz_M;
	uint32_t sz_NVRAM = 0;
	uint32_t sz_log_mem = 0;

	RTS_I32 iValue;
	
	uint32_t page_mask, page_size;
	page_size = sysconf(_SC_PAGESIZE);

	
	// Считываем размер буфера лога
	if (CAL_SettgGetIntValue(COMPONENT_NAME, "BufferSize", &iValue, 0,
				 CMPSETTINGS_CACHED) == ERR_OK)
		sz_log_mem = iValue;
	
	if (sz_log_mem == 0) {
		sprintf(str, "Error: Нет размера буфера. (BufferSize в конфигурации rts)");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
		return ERR_FAILED;
	}

	// Считываем размер всей NVRAM
	if (CAL_SettgGetIntValue("CmpEmiconMemManager", "NVRAMSize", &iValue, 0,
				 CMPSETTINGS_CACHED) == ERR_OK)
		sz_NVRAM = iValue;

	if (sz_NVRAM == 0) {
		sprintf(str, "Error: Нет общего размера NVRAM. (NVRAMSize в конфигурации rts)");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
		return ERR_FAILED;
	}

	if (_is_emu) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   "Включен режим эмуляции! NVRAM пишется в файл %s.",
			   MEM_FILE_NAME);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   "Все адреса лога рассчитываются от начала файла.");
	}
	/*
	 * Если размер sz_NVRAM <= 0x40000 (256К) - это старая микросхема.
	 * В этом случае буффер лога привязывается жестко со смещением 188К -
	 * 0x2F000 и размером 4к 0x1000.
	 */

	if (sz_NVRAM <= 0x40000) {
		_nvram_log_mem_address = 0x2F000 + NVRAM_CS3_MEM_ADDRESS;
		sz_log_mem = 0x1000;
		sprintf(str, "Warning: Размер NVRAM 256К. Лог жестко смещен на %s размером %d!",
			"0x2F000", sz_log_mem);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
	} else {
		sprintf(str, "Расчет лога по смещению от M.");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);

		/* 
		 * Считываем у EmiconMemManager размер %M. Она уже выровнена по 
		 * 4к.
		 */
		sz_M = CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size();
		_nvram_log_mem_address = sz_M + NVRAM_CS3_MEM_ADDRESS;

		if (sz_M + sz_log_mem > sz_NVRAM){
			sprintf(str, "Error: Недостаточно места в NVRAM.");
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO,
				   ERR_FAILED, 0, str);
			return ERR_FAILED;
		}

		if (sz_log_mem < page_size){
			sprintf(str, "Error: Размер свободной памяти NVRAM (%d) меньше размера страницы (%d)",
				sz_log_mem, page_size);
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO,
				   ERR_FAILED, 0, str);
			return ERR_FAILED;
		}
	}

	page_mask = (page_size - 1);
	_nvram_allocated_mem_size = (((sz_log_mem / page_size)) * page_size);

	if (!_is_emu) {
		_fd_nvram = open("/dev/mem", O_RDWR | O_SYNC);

		_p_map_nvram_mem = mmap(NULL,
			_nvram_allocated_mem_size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			_fd_nvram,
			(_nvram_log_mem_address & ~page_mask)
		);
	} else {
		_nvram_log_mem_address = _nvram_log_mem_address 
							- NVRAM_CS3_MEM_ADDRESS;

		_fd_nvram = open(MEM_FILE_NAME, O_RDWR | O_CREAT, 
				 S_IRUSR | S_IRGRP | S_IROTH);

		_p_map_nvram_mem = mmap(0, _nvram_allocated_mem_size,
					PROT_READ | PROT_WRITE, MAP_SHARED,
					_fd_nvram,
					_nvram_log_mem_address & ~page_mask);

	}



	if(_p_map_nvram_mem == MAP_FAILED){
		sprintf(str, "Error: Ошибка отображения NVRAM памяти Лога.");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
		return ERR_FAILED;
	} else {
		sprintf(str, "Log: Выделено %d байт памяти.",
						_nvram_allocated_mem_size);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
		sprintf(str, "Log: Начало с физического адреса 0x%X .",
						_nvram_log_mem_address);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
	}

	/*
	 * Расчет указателей головной структуры лога.
	 * TODO: 
	 * Тут на до бы все сделать через структуру и избавиться от цифр в коде.
	 */
	_init_mark = (uint16_t*)_p_map_nvram_mem;
	_offset_first_record = (uint32_t *)((uint8_t *)_p_map_nvram_mem + 2); 
	_offset_end_of_records = (uint32_t *)((uint8_t *)_p_map_nvram_mem + 6);
	_log_mem_size = (uint32_t *)((uint8_t *)_p_map_nvram_mem + 10);

	// указатель на начало области записи расчитываем смещением на размер 
	// структуры инициализации от головы всей области, выделенной на Лог.
	_p_log_buff = (uint8_t *)_init_mark + 2+4+4+4;
	_sz_log_buff = sz_log_mem - 14;
	
	// указатель конца на последний байт буфера, а не байт за ним!
	_p_log_buff_end = (uint8_t *)_init_mark + sz_log_mem - 1;

	if (*_init_mark != LOG_INIT_MARK || *_log_mem_size != sz_log_mem) {
		// sprintf(str, "Log: _init_mark %hhX .", _init_mark);
		// CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
		// 	   str);

		// sprintf(str, "Log: _log_mem_size %zu sz_log_mem %zu.",
		// 	*_log_mem_size, sz_log_mem);
		// CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
		// 	   str);

		memset((uint8_t *)_init_mark, NONE, sz_log_mem);
		_p_first_record = _p_end_of_records = _p_log_buff;
		set_init_offsets();
		*_log_mem_size = sz_log_mem;
		*_init_mark = LOG_INIT_MARK;

		sprintf(str, "Log: Инициализация %d байт памяти.",
						_nvram_allocated_mem_size);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
	} else {
		_p_first_record = _p_log_buff + *_offset_first_record;
		_p_end_of_records = _p_log_buff + *_offset_end_of_records;

		sprintf(str, "Log: Буфер найден.");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
	}
		
	_p_first_record_read = _p_first_record;

	_init_done = true;
	return ERR_OK;
}

int set_init_offsets(void)
{
	*_offset_first_record = _p_first_record - _p_log_buff;
	*_offset_end_of_records = _p_end_of_records - _p_log_buff;
	return ERR_OK;
}
/*
 * Очищает буфер логера, и записывает сообщение об очитске первым сообщением.
 * Физически буфер не стирается. Переносятся указатели на начало.
 */
void CDECL CDECL_EXT clr_sys_log(clr_sys_log_struct *p)
{
	if (!_init_done){
		p->clr_sys_log = 1;
		return;
	}
	
	_p_first_record = _p_end_of_records = _p_log_buff;

	set_init_offsets();

	*_p_first_record = NONE;

	_create_own_sys_event(OWN_EVENT_ID_CLR);
	
	p->clr_sys_log = ERR_OK;
}

void CDECL CDECL_EXT create_log_files(create_log_files_struct *p)
{
	 if (!_init_done){
 		p->create_log_files = -1;
 		return;
 	}

	uint8_t *my_p_first_record;
	uint8_t *my_p_end_of_frame;
	int type_of_frame;
	int i;
	size_t offset;
	bool end_of_records;

	char date_str[100];
	char file_name_str[100];
	char log_str[300];

	int fd;
	int max_num_records;

	date_and_time dt_file_creation;
	get_actual_time(&dt_file_creation);

	sprintf(date_str, "%d-%02d-%02d_%02d-%02d-%02d-%03d",
		dt_file_creation.year,
		dt_file_creation.month,
		dt_file_creation.day,
		dt_file_creation.hour,
		dt_file_creation.minutes,
		dt_file_creation.seconds,
		dt_file_creation.msec);

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	my_p_first_record = _p_first_record;
	
	end_of_records = false;
	i = 0;
	max_num_records = *_log_mem_size / SIZE_OF_OWN_EVENT;

	do {
		type_of_frame = get_type_of_frame(my_p_first_record);

		// передаем ошибку определения типа вызывающему
		if (type_of_frame < 0){
			p->create_log_files = -2;
			return;
		}

		if (i > max_num_records){
			// считанных записей привышает лимит буфера
			// означает нарушение структуры буфера. Может быть если все байты
			// инициализировать с первым битом == 1
			p->create_log_files = -3;
			return;
		}

		i++;
		
		switch (type_of_frame) {
		case FRAME_TYPE_OWN_EVENT:
			if (EXIT_SUCCESS == 
				read_sys_log(my_p_first_record, log_str)){

				sprintf(file_name_str, "%sEVT/e_%s",
					_log_folder, date_str);
			
				fd = open(file_name_str, O_CREAT | O_WRONLY
					| O_APPEND, mode);
				write(fd, log_str, strlen(log_str));
				close(fd);
			}
			
			offset = SIZE_OF_OWN_EVENT;
			break;
		

		case FRAME_TYPE_TS:
			if (EXIT_SUCCESS == read_ts_log(my_p_first_record,
							log_str)){
				sprintf(file_name_str,
					"%sTD/t%d_%s",
					_log_folder,
					*my_p_first_record,
					date_str);
				fd = open(file_name_str, O_CREAT | O_WRONLY
					| O_APPEND, mode);

				write(fd, log_str, strlen(log_str));
				close(fd);
			}

			offset = SIZE_OF_TS;
			break;

		case FRAME_TYPE_TI:
			if (EXIT_SUCCESS == read_ti_log(my_p_first_record,
							log_str)) {
				sprintf(file_name_str,
					"%sTA/t%d_%s",
					_log_folder,
					*my_p_first_record & MASK_ALL_MARK,
					date_str);
				fd = open(file_name_str, O_CREAT | O_WRONLY
					| O_APPEND, mode);

				write(fd, log_str, strlen(log_str));
				close(fd);
			}

			offset = SIZE_OF_TI;
			break;
		}

		my_p_end_of_frame = shift_pointer_along_buffer(
			my_p_first_record, offset - 1);
		
		if (my_p_end_of_frame == _p_end_of_records)
			end_of_records = true;
		else
			my_p_first_record = shift_pointer_along_buffer(
				my_p_first_record, offset);
			
	} while (!end_of_records);


	p->create_log_files = i;
}

/*
 * Записывает собственное сообщение, переданное в параметре.
 * Функция вормирует own_event_frame кадр записи, где 
 * первый 1 байт определяет подкласс собственного события. Старший бит этого
 * этого байта всегда устанавливается в 1 - признак собственного сообщения.
 * Последующие 4 байта содержат код сообщения (поле value).
 * Последние 7 байт - текущее время в формате CP56Time2a.
 */
void CDECL CDECL_EXT write_sys_log(write_sys_log_struct *p)
{
	int res;
	own_event_frame frame;

	// принудительно устанавливаем старший бит в 1
	uint8_t class_id = p->byClassId | MARK_SYS_LOG;
	frame.class_id = class_id;
	frame.value = p->dwValue;

	actual_time_to_CP56Time(frame.datetime);
	res = write_buffer((uint8_t *)&frame, SIZE_OF_OWN_EVENT);
	if (res < 0)
		p->write_sys_log = res;
	p->write_sys_log = ERR_OK;
	
}

void CDECL CDECL_EXT write_ti_log(write_ti_log_struct *p)
{
	uint8_t data[SIZE_OF_TI];
	int res;
	uint8_t class_id;

	class_id = p->byClassId;

	class_id &= ~MARK_SYS_LOG;
	class_id |= MARK_TI_LOG; 

	data[0] = class_id;
	memcpy(&data[1], p->pbyData, SIZE_OF_TI - 1);	

	res = write_buffer((uint8_t *)data, SIZE_OF_TI);
	if (res < 0)
		p->write_ti_log = res;

	p->write_ti_log = ERR_OK;
	
}

void CDECL CDECL_EXT write_ts_log(write_ts_log_struct *p)
{
	uint8_t data[SIZE_OF_TS];
	int res;
	uint8_t class_id;

	class_id = p->byClassId;

	class_id &= ~MARK_SYS_LOG;
	class_id &= ~MARK_TI_LOG;
	
	data[0] = p->byClassId;
	memcpy(&data[1], p->pbyData, SIZE_OF_TS - 1);	
	res = write_buffer((uint8_t *)data, SIZE_OF_TS);
	if (res < 0)
		p->write_ts_log = res;

	p->write_ts_log = ERR_OK;
	
}


size_t size_of_free_space(void)
{
	/* 
	 * Ситуация когда указатель начала и конца совпадают может быть в одном
	 * случае:
	 * 	1) Буфер полностью чист, в этом случае значение по указателям 
		будет равным NONE.
	 */
	if (_p_first_record == _p_end_of_records)
		return _sz_log_buff;

	/* 
	 * Если указатель начала меньше конца, то размер свободного пространства
	 * определяем вычитаением отрезка от начала до конца из общего размера
	 * буфера. 
	 *
	 * Иначе - указатель конца прошел по кругу и идет за указателем начала.
	 * В этом случае свободное пространство находится между указателями.
	 */

	if (_p_first_record < _p_end_of_records)
		return _sz_log_buff - (_p_end_of_records + 1 - _p_first_record);
	else
		return _p_first_record - _p_end_of_records - 1;

}

/* 
 * Проверка семафора. 
 * Если буфер не занят, *_init_mark должен быть LOG_INIT_MARK
 */
bool is_buffer_accessable(void)
{
	int trial = 0;
	
	while(*_init_mark != LOG_INIT_MARK && trial < 3){
		trial++;
		usleep (100);
	}
	if (trial >= 3)
		return false;
	
	return true; 
}

int write_buffer(uint8_t *p_data, size_t size)
{

	size_t sz_free_space;
	size_t sz_free_end;
	char str[200];
	
	if (!_init_done)
		return ERR_FAILED;

	if (!is_buffer_accessable()){
		sprintf(str, "Test:  %d!", *_init_mark);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			   str);
		return ERR_FAILED;
	}


	*_init_mark = LOG_INIT_MARK_BUSY;

	if (size > _sz_log_buff)
		return -ENOMEM;

	sz_free_space = size_of_free_space();

	if (sz_free_space < size)
		release_space(size - sz_free_space);

	if (_p_end_of_records + size <= _p_log_buff_end) {
		if (_p_first_record == _p_end_of_records){
			memcpy(_p_end_of_records, p_data, size);
			_p_end_of_records += size - 1;
			set_init_offsets();
		}
		else {
			memcpy(_p_end_of_records + 1, p_data, size);
			_p_end_of_records += size;
			set_init_offsets();
		}

	} else {
		sz_free_end = _p_log_buff_end - _p_end_of_records;
		if (sz_free_end == 0) {
			// указатель конца последней записи в последнем байте
			// буфера - начинаем запись с головы буфера
			memcpy(_p_log_buff, p_data, size);
			_p_end_of_records = _p_log_buff + size - 1;
			set_init_offsets();
		} else {
			// разбиваем запись на две части. Дозаполняем хвост
			// и продолжаем от головы
			memcpy(_p_end_of_records + 1, p_data, sz_free_end);
			memcpy(_p_log_buff, p_data + sz_free_end, size -
				sz_free_end);
			_p_end_of_records = _p_log_buff + size - sz_free_end - 1;
			set_init_offsets();
		}

	}

	*_init_mark = LOG_INIT_MARK;

	if (_debug_log)
		print_data();

	return ERR_OK;
}

int read_buffer(uint8_t *p_data, uint8_t *p_first_byte, size_t size)
{
	size_t bytes;

	if (!_init_done)
		return ERR_FAILED;

	if (!is_buffer_accessable())
		return ERR_FAILED;
	*_init_mark = LOG_INIT_MARK_BUSY;

	if (size > _sz_log_buff)
		size = _sz_log_buff;

	if (p_first_byte + size <= _p_log_buff_end) {
		memcpy(p_data, p_first_byte, size);
	} else {
		// считываем хвост и продолжаем от головы
		bytes = _p_log_buff_end - p_first_byte + 1;
		memcpy(p_data, p_first_byte, bytes);
		memcpy(p_data + bytes, _p_log_buff, size - bytes);
	}
	
	*_init_mark = LOG_INIT_MARK;
	return ERR_OK;
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

	size_t offset;
	int32_t rest_size;

	rest_size = size;
	do {
		if (*_p_first_record & MARK_SYS_LOG)
			offset = SIZE_OF_OWN_EVENT;
		else
			if (*_p_first_record & MARK_TI_LOG)
				offset = SIZE_OF_TI;
			else 
				offset = SIZE_OF_TS;

		_p_first_record = shift_pointer_along_buffer(_p_first_record,
							     offset);
		set_init_offsets();

		rest_size -= offset; 
	} while (rest_size > 0);

	return 0;
}

int in_array(uint8_t *array, size_t size, uint8_t look_for)
{
	int i;

	for (i = 0; i < size; i++)
		if (array[i] == look_for)
		return 1;
	return 0;
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
 * Считывает кадр собтвеных сообщений из памяти
 */
int read_sys_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_OWN_EVENT)
		return ERR_FAILED;

	own_event_frame my_frame;

	read_buffer((uint8_t*)&my_frame, frame, SIZE_OF_OWN_EVENT);

	my_frame.class_id &=  ~MARK_SYS_LOG;

	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%d\tType: 0x%02X\tValue: 0x%02X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		my_frame.class_id,
		my_frame.value
	);

	return ERR_OK;
}

/*
 * Считывает кадр ts сообщений из памяти
 */
int read_ts_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_TS)
		return ERR_FAILED;

	ts_frame my_frame;
	read_buffer((uint8_t*)&my_frame, frame, sizeof(my_frame));
	
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	// убираем разметочные два старших бита
	my_frame.class_id &= MASK_ALL_MARK;

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%d  Type: 0x%02X  Address: 0x%02X%02X%02X  Value: 0x%02X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		my_frame.class_id,
		my_frame.address[2],
		my_frame.address[1],
		my_frame.address[0],
		my_frame.value
		
	);

	return ERR_OK;
}

/*
 * Считывает кадр ti сообщений из памяти
 */
int read_ti_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_TI)
		return ERR_FAILED;

	ti_frame my_frame;
	read_buffer((uint8_t*)&my_frame, frame, sizeof(my_frame));
	
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	// убираем разметочные два старших бита
	my_frame.class_id &= MASK_ALL_MARK;

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%d  Type: 0x%02X  Address: 0x%02X%02X%02X  Value: 0x%02X%02X%02X%02X  Quality: 0x%02X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,

		// по ТЗ требуется при выводе подменять значение 0 на 64.
		my_frame.class_id ? my_frame.class_id : 64,

		my_frame.address[2],
		my_frame.address[1],
		my_frame.address[0],

		my_frame.value[3],
		my_frame.value[2],
		my_frame.value[1],
		my_frame.value[0],
		
		my_frame.quality
	);

	return ERR_OK;
}

/*
 * возвращает указатель смещенный от p_begin на offset байт по буферу с учетом 
 * цикличности.
 */

uint8_t* shift_pointer_along_buffer(uint8_t *p_begin, size_t offset)
{
	uint8_t *my_p;
	
	my_p = p_begin + offset;
	if (my_p > _p_log_buff_end)
		my_p = _p_log_buff + (my_p - _p_log_buff_end - 1);

	return my_p;
}

/*
 * Возвращает тип фрейма по первому байту
 */
int get_type_of_frame(uint8_t *frame)
{

	if (*frame & MARK_SYS_LOG)
			return FRAME_TYPE_OWN_EVENT;
	
	if (*frame & MARK_TI_LOG)
		return FRAME_TYPE_TI;
	else
		return FRAME_TYPE_TS;

	return -1; // тип не найден
}

/*
 * Регистрация обработчиков событий
 */
void register_events_handler(void)
{
	if (CHK_EventOpen) {
		_s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone,
							 CMPID_CmpApp, NULL);
		_s_hEventStopDone = CAL_EventOpen(EVT_StopDone,
						  CMPID_CmpApp, NULL);
		_s_hEventPrepareStart = CAL_EventOpen(EVT_PrepareStart,
						  CMPID_CmpApp, NULL);

	}

	if (CHK_EventRegisterCallbackFunction) {
		CAL_EventRegisterCallbackFunction(_s_hEventAppDownloadDone,
						  handler_evt_download_done, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventStopDone,
						  handler_evt_stop_done, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventPrepareStart,
						  handler_evt_prepare_start, 0);
	}
}