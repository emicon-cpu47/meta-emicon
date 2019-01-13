/*
 */

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif


#include <stdbool.h>
#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpEmiconMemManagerDep.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include "CmpIoMgrItf.h"

/*
 * MEM_FILE_NAME - файл в который будет работать вместо NVRAM в режиме эмуляции
 */

#define MEM_FILE_NAME "memnvram.txt"
static bool _is_emu = false;

#define SIZE_OF_SETS 32					// байт настроек
#define FIRST_BYTE_OF_SETS 197272		// %MW98636
/* NWRAM Memmory params */
const uint32_t CS3_MEM_ADDRESS = 0x2000000;

static uint32_t _cs3_mem_size = 0;
static void *_p_NWRAM_mem = NULL;

/* Buffer to store NWRAM before initial zerroing */
static void *_p_mem_buff = NULL;

/* буффер для сохранения настроек */
static void *_p_set_mem_buff = NULL;

static int _fd_cs3;

/* Handle to the event defined by CmpApp */
static RTS_HANDLE _s_hEventAllocArea = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventPrepareReset = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventResetDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventAppPrepareDownload = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventAppDownloadDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventConfigStopDone = RTS_INVALID_HANDLE;

static void callback_gateway(EventParam *pEventParam);
static void handler_evt_done_update_configuration(EventParam *pEventParam);
void CmpApp_callback_handler(EventParam *pEventParam);
void em_memory_manager(EVTPARAM_CmpAppArea *pParam);
void em_save_mem(void);
void em_restore_mem(void);

/*
 * Возвращает указатель на NVRAM память размером size.
 */
void *get_nvram_mem(uint32_t size, uint32_t page_mask);

/*
 * Возвращает указатель на память куда отображенен файл имитации NVRAM памяти
 * размером size.
 */
void *get_file_nvram_mem(uint32_t size);


USE_STMT

/**
 * <description>Entry function of the component. Called at startup for each
 * component. Used to exchange function pointers with the component
 * manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *	pfExportFunctions	OUT 	Pointer to function that exports
 					component functions
 *	pfImportFunctions	OUT 	Pointer to function that imports
 					functions from other components
 *	pfGetVersion		OUT 	Pointer to function to get component
 					version
 *	pfRegisterAPI		IN	Pointer to component mangager function
 					to register a api function
 *	pfGetAPI		IN	Pointer to component mangager function
 					to get a api function
 *	pfCallHook		IN	Pointer to component mangager function
 					to call a hook function
 * </param> 
 * <result>ERR_OK if library could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

	return ERR_OK;
}

/*
 * <description>Publish exported functions to the component manager, to make
 * them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	EXPORT_STMT;
	return ERR_OK;
}

/*
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

/*
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	/* Our component version defined in our Dep file */
	return CMP_VERSION;
}

/*
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
	switch (ulHook) {
	case CH_INIT_SYSTEM:

		break;
	case CH_INIT:
		break;
	case CH_INIT2:	

		break;

	case CH_INIT3:
		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();


		_s_hEventAllocArea = CAL_EventOpen(EVT_AllocArea, CMPID_CmpApp,
						   NULL);

		_s_hEventPrepareReset = CAL_EventOpen(EVT_PrepareReset,
						      CMPID_CmpApp, NULL);
		_s_hEventResetDone = CAL_EventOpen(EVT_ResetDone,
						   CMPID_CmpApp, NULL);

		_s_hEventAppPrepareDownload = CAL_EventOpen(EVT_PrepareDownload,
							    CMPID_CmpApp, NULL);
		_s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone,
							 CMPID_CmpApp, NULL);

		_s_hEventConfigStopDone = CAL_EventOpen(
			EVT_DoneUpdateConfiguration, CMPID_CmpIoMgr, NULL);


		CAL_EventRegisterCallbackFunction(_s_hEventAllocArea,
						  callback_gateway, 0);

		CAL_EventRegisterCallbackFunction(_s_hEventPrepareReset,
						  callback_gateway, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventResetDone,
						  callback_gateway, 0);

		CAL_EventRegisterCallbackFunction(_s_hEventAppPrepareDownload,
						  callback_gateway, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventAppDownloadDone,
						  callback_gateway, 0);

		CAL_EventRegisterCallbackFunction(_s_hEventConfigStopDone,
				handler_evt_done_update_configuration, 0);

		break;

	case CH_INIT_TASKS:
		/*
		 * Called after CH_INIT_SYSTEM_TASKS. All components should
		 * start their tasks.
		 * NOTE: The IEC bootprojects are loaded here!
		 */
		break;

	case CH_INIT_COMM:
		/*
		 * Called after CH_INIT_TASKS. Communication can be started at
		 * this point, because all components are ready and running.
		 */
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		break;
	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		/*
		 * Called before CH_EXIT2 to store data (e.g. retain data).
		 * Unregister from events at shutdown
		 */

		CAL_EventUnregisterCallbackFunction(_s_hEventAllocArea,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventPrepareReset,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventResetDone,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventAppPrepareDownload,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventAppDownloadDone,
						    callback_gateway);

		CAL_EventClose(_s_hEventAllocArea);
		CAL_EventClose(_s_hEventPrepareReset);
		CAL_EventClose(_s_hEventResetDone);
		CAL_EventClose(_s_hEventAppPrepareDownload);
		CAL_EventClose(_s_hEventAppDownloadDone);

		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;
	case CH_EXIT_SYSTEM:
		break;
	default:
		break;
	}
	return ERR_OK;
}

#ifndef CPLUSPLUS
	IMPLEMENT_ADDREF
	IMPLEMENT_RELEASE
#endif


 static void callback_gateway(EventParam *pEventParam)
{
	/* Use pEventParam->CmpIdProvider to identify the component that posts 
	the event. Note that pEventParam->EventId is not unique in the system */
	switch (pEventParam->CmpIdProvider){
	case CMPID_CmpApp:
		CmpApp_callback_handler(pEventParam);
		break;

	default:
		break;
	}
}

void CmpApp_callback_handler(EventParam *pEventParam){
	/* Use pEventParam->EventId to identify the event. */
	if (pEventParam->EventId == EVT_AllocArea &&
			pEventParam->usParamId == EVTPARAMID_CmpAppArea){
		//RTS_RESULT Result;
		EVTPARAM_CmpAppArea *pParam =
			(EVTPARAM_CmpAppArea *)pEventParam->pParameter;

		if (IsArea(pParam->usType, DA_MEMORY) != 0)
			em_memory_manager(pParam);
	}

	if (pEventParam->EventId == EVT_PrepareReset){
		EVTPARAM_CmpApp_Reset *pParam =
			(EVTPARAM_CmpApp_Reset *)pEventParam->pParameter;


		/*
		 * Делаем обнудение по холодному рессету, потому что он не 
		 * перегружает МЭК проект и не приводит к проблеме потери
		 * указателя. По исправлению ошибки переведем на
		 * RTS_RESET_ORIGIN
		 */
		if (pParam->usResetOption == RTS_RESET_COLD && _p_NWRAM_mem)
			memset(_p_NWRAM_mem, 0, _cs3_mem_size);
			
		em_save_mem();
	}

	if (pEventParam->EventId == EVT_ResetDone){
		EVTPARAM_CmpApp_Reset *pParam =
			(EVTPARAM_CmpApp_Reset *)pEventParam->pParameter;

		// аналогично переписать на RTS_RESET_ORIGIN
		if (pParam->usResetOption != RTS_RESET_COLD)
			em_restore_mem();
	}

	if (pEventParam->EventId == EVT_PrepareDownload)
		em_save_mem();

	if (pEventParam->EventId == EVT_DownloadDone){
		char *pszName;
		
		EVTPARAM_CmpApp *pParam =
				(EVTPARAM_CmpApp *)pEventParam->pParameter;
		pszName = pParam->pApp->szName;

		em_restore_mem();
	}

}

void em_memory_manager(EVTPARAM_CmpAppArea *pParam){
	
	if (pParam->bAlloc == 1){
		/* Memmory allocation */

		uint32_t page_mask, page_size;
		
		page_size = sysconf(_SC_PAGESIZE);
		page_mask = (page_size - 1);
		_cs3_mem_size = ((pParam->ulSize / page_size) * page_size);

		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			   "em_memory_manager: Запрошенный размер %M %zu, выделено %zu",
			   pParam->ulSize, _cs3_mem_size);

		if (_is_emu) {
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
				   ERR_FAILED, 0, 
				   "Эмуляция NVRAM в файл: %s", MEM_FILE_NAME);

			_p_NWRAM_mem = get_file_nvram_mem(_cs3_mem_size);
		} else {
			// Выделение в NVRAM
			_p_NWRAM_mem = get_nvram_mem(_cs3_mem_size, page_mask);
		}

		if(_p_NWRAM_mem == MAP_FAILED) {
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
				ERR_FAILED, 0, 
				"Error: Мапирование NWRAM для %M не удалось! Ошибка: %s",
				strerror(errno)
			);

			_p_NWRAM_mem = 0;
		} else {
			// settings RTS pointer of %M:
			pParam->pArea = (RTS_UI8*)_p_NWRAM_mem;
			em_save_mem();
		}
	} else {
		/* Memmory dealocation: */
		int res;

		res = munmap(pParam->pArea, _cs3_mem_size);
		if (res < 0)
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
				ERR_FAILED, 0, 
				"Error: Освобождение NWRAM не выполнено. Ошибка: %s",
				strerror(errno)
			);
		
		close(_fd_cs3);
	}
}

void em_save_mem(void)
{
	if (!_p_NWRAM_mem)
		return;

	if (_p_mem_buff){
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Error: Буфер для сохранения обнуляемой при старте %M памяти занят!");
		free(_p_mem_buff);
		_p_mem_buff = NULL;
	}

	_p_mem_buff = malloc(_cs3_mem_size);
	if(!_p_mem_buff)
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Error: Ошибка выделения памяти для сохранения %M от обнуления!");
	else
		memcpy(_p_mem_buff, _p_NWRAM_mem, _cs3_mem_size);

}

void em_restore_mem(void)
{
	if(!_p_mem_buff && !_p_NWRAM_mem){
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Error: указатели на востанавливаемые участки памяти не верные!");
	} else{

		RTS_UI32 state;
		
		/*
		 * Если FIRST_BYTE_OF_SETS второй бит (десятичная двойка)
		 * установлен, то востановление памяти не нужно.
		 * Внимание! Реализованная битовая операция не учитывает разницу
		 * в порядках байт, поэтому работает корректно только на 
		 * intel-byteorder.
		 */
		
		// uint32_t mask_fZeroMappedOnDownload = 2;
		// uint32_t *p_sets;
		// p_sets = _p_NWRAM_mem + FIRST_BYTE_OF_SETS;

		// if (~ *p_sets & mask_fZeroMappedOnDownload)
		memcpy(_p_NWRAM_mem, _p_mem_buff,
				_cs3_mem_size);
		// else
		// 	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO,
		// 		ERR_FAILED, 0, 
		// 		"WARNING: Установлен флаг fZeroMappedOnDownload! %M не востановлена!");

		free(_p_mem_buff);
		_p_mem_buff = NULL;
		
		// восстанавливаем настройки производимые со вкладки 
		// EmiconSettings
		if(_p_set_mem_buff){
			memcpy(_p_NWRAM_mem + FIRST_BYTE_OF_SETS,
				_p_set_mem_buff, SIZE_OF_SETS);
			free(_p_set_mem_buff);
			_p_set_mem_buff = NULL;
		}
	}
}


static void handler_evt_done_update_configuration(EventParam *pEventParam)
{
	if (pEventParam->usParamId == EVTPARAMID_CmpIoMgr
	    && pEventParam->EventId == EVT_DoneUpdateConfiguration){
		// Сохраняем параметры
		_p_set_mem_buff = malloc(SIZE_OF_SETS);
		if(_p_set_mem_buff)
			memcpy(_p_set_mem_buff,
				_p_NWRAM_mem + FIRST_BYTE_OF_SETS,
				SIZE_OF_SETS);

		// For debug only
		// CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0,
			// "*** EVT_DoneUpdateConfiguration received ***");
	}
}


uint32_t CDECL CmpEmiconMemManager_get_cs3_allocated_mem_size(void)
{
	return _cs3_mem_size;
}

int16_t CDECL CmpEmiconMemManager_mem_to_file(long int l_byte, long int b_byte)
{
	int fd;
	int64_t res;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	if (l_byte > b_byte || l_byte < 0 || b_byte > _cs3_mem_size) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
				"Fail - Violation of memory boundaries!");
		return -3;
	}
	

	fd = open("/home/plc/mem_dump", O_CREAT | O_WRONLY | O_TRUNC, mode);
	if (fd < 0)
		return -1;

	res = write(fd, &l_byte, sizeof(l_byte));
	if (res < 0)
		return -2;

	res = write(fd, &b_byte, sizeof(b_byte));
	if (res < 0)
		return -2;

	if (l_byte == 0 && b_byte == 0) {
		res = write(fd, _p_NWRAM_mem, _cs3_mem_size);
		if (res < 0)
			return -2;
	} else {
		res = write(fd, _p_NWRAM_mem + l_byte, b_byte - l_byte + 1);
		if (res < 0)
			return -2;

	}
	close(fd);

	return 0;
}

int16_t CDECL CmpEmiconMemManager_file_to_mem(void)
{
	int fd;
	struct stat st;
	char *file_name = "/home/plc/mem_dump";
	int64_t res;
	long int l_byte;
	long int b_byte;

	stat(file_name, &st);
	if (st.st_size - sizeof(long int) * 2 > _cs3_mem_size)
		return -2;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return -1;

	res = read(fd, &l_byte, sizeof(l_byte));
	if (res < 0)
		return -3;

	res = read(fd, &b_byte, sizeof(b_byte));
	if (res < 0)
		return -3;

	if (l_byte == 0 && b_byte == 0) {
		res = read(fd, _p_NWRAM_mem, _cs3_mem_size);
		if (res < 0)
			return -3;
	} else {
		res = read(fd, _p_NWRAM_mem + l_byte, b_byte - l_byte + 1);
	}

	close(fd);
	return 0;
}

void *get_nvram_mem(uint32_t size, uint32_t page_mask)
{
	void *p_mem;

	_fd_cs3 = open("/dev/mem", O_RDWR | O_SYNC);
	p_mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, _fd_cs3,
		     (CS3_MEM_ADDRESS & ~page_mask));

	return p_mem;
}

void *get_file_nvram_mem(uint32_t size)
{
	void *p_mem;
	struct stat sb;
	RTS_I32 nvram_sz = 0;
	char buffer[1024] = {0};

	/*
	 * Считываем из настроек rts размер всей NVRAM для дальнейшего
	 * создания файла имитации NVRAM.
	 */
	if (CAL_SettgGetIntValue(COMPONENT_NAME, "NVRAMSize", &nvram_sz, 0,
				 CMPSETTINGS_CACHED) != ERR_OK)
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			   "Ошибка чтения параметра NVRAMSize из конфигурационного файла");


	_fd_cs3 = open(MEM_FILE_NAME, O_RDWR | O_CREAT, 
		       S_IRUSR | S_IRGRP | S_IROTH);

	/*
	 * Определяем размер файла симуляции, и при меньшем размере чем 
	 * _cs3_mem_size дополняем его нулями. При большем размере
	 * обрезать не следует - это позволит экспериментировать с меньшим
	 * выделением памяти NVRAM из МЭК без потерь данных предыдущего
	 * большего размера.
	 */
	if (fstat(_fd_cs3, &sb) == -1){
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
			ERR_FAILED, 0, 
			"Ошибка определения размера файла симуляции NVRAM: %s",
			strerror(errno));
		return MAP_FAILED;
	}

	if (sb.st_size < nvram_sz) {
		for (int i = 0; i < nvram_sz / sizeof(buffer); i++)
			write(_fd_cs3, &buffer, sizeof(buffer));

		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Файл симуляции NVRAM дополнен до: %d", nvram_sz);

	} else {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Размер файла симуляции NVRAM: %ld, запрашиваемый объем памяти: %d",
			sb.st_size, _cs3_mem_size);
	}

	p_mem = mmap(0, _cs3_mem_size, PROT_READ | PROT_WRITE,
		     MAP_SHARED, _fd_cs3, 0);

	return p_mem;
}
