/*
 * Компонент осуществляет остановку/запуск МЭК приложения по длительному нажатию
 * кнопки «В» на панели ЦПУ.
 * Информация о состоянии МЭК приложения выводится на LCD экран через компонент
 * CmpEmiconLCD.
 *
 */

#include "CmpStd.h"
#include "CmpEmiconStopControlDep.h"

#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>


USE_STMT

#define LCD_STR_BLANK ""
#define LCD_STR_STOP "Stop"
#define LCD_STR_RUN "Run"
#define LCD_STR_LOCKED "Locked"
#define LCD_STR_UNLOCKED "Unlocked"
#define LOG_STR_STOP "App STOP"
#define LOG_STR_RUN "App RUN"


// GPIO имеет инверсную логику
#define NOT_PRESSED_BUTTON_CODE 49 // ascii 1
#define PRESSED_BUTTON_CODE 48 // ascii 0
#define START_STOP_PRESS_BUTTON_INTERVAL 2000// milliseconds

static RTS_RESULT CDECL InitRunStopSwitch(void);
static RTS_RESULT CDECL ExitRunStopSwitch(void);
static RTS_RESULT CDECL CyclicRunStopSwitch(void);
static void CDECL CBDenyStart(EventParam *pEventParam);
static RTS_I32 PollRunStopSwitch(void);
static void CDECL CBApp(EventParam *pEventParam);


static RTS_I32 s_bRun = 1;
static RTS_HANDLE s_hEventRSSDenyStart = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventLoadBootprojectDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventStopDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventStartDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventAppDownloadDone = RTS_INVALID_HANDLE;

bool _boot_prg_loaded = false;

#ifndef RTS_COMPACT_MICRO


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


static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}


static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}


static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif


static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook){
	
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		InitRunStopSwitch();
		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		CyclicRunStopSwitch();
		break;

	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		ExitRunStopSwitch();
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;

	default:
		break;
	}
	return ERR_OK;
}

static RTS_RESULT CDECL InitRunStopSwitch(void)
{
	RTS_RESULT Result;

	s_hEventRSSDenyStart = CAL_EventOpen(EVT_DenyStart, CMPID_CmpApp,
					     &Result);
	CAL_EventRegisterCallbackFunction(s_hEventRSSDenyStart, CBDenyStart, 0);

	s_hEventLoadBootprojectDone = CAL_EventOpen(EVT_LoadBootprojectDone,
						    CMPID_CmpApp, NULL);
	CAL_EventRegisterCallbackFunction(s_hEventLoadBootprojectDone, CBApp,
					  0);

	s_hEventStopDone = CAL_EventOpen(EVT_StopDone, CMPID_CmpApp, NULL);
	CAL_EventRegisterCallbackFunction(s_hEventStopDone, CBApp, 0);
	s_hEventStartDone = CAL_EventOpen(EVT_StartDone, CMPID_CmpApp, NULL);
	CAL_EventRegisterCallbackFunction(s_hEventStartDone, CBApp, 0);

	s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone, CMPID_CmpApp,
						NULL);
	CAL_EventRegisterCallbackFunction(s_hEventAppDownloadDone, CBApp, 0);

	return ERR_OK;
}

static RTS_RESULT CDECL ExitRunStopSwitch(void)
{
	CAL_EventUnregisterCallbackFunction(s_hEventRSSDenyStart, CBDenyStart);
	CAL_EventClose(s_hEventRSSDenyStart);
	CAL_EventUnregisterCallbackFunction(s_hEventLoadBootprojectDone, CBApp);
	CAL_EventClose(s_hEventLoadBootprojectDone);
	s_hEventRSSDenyStart = RTS_INVALID_HANDLE;

	CAL_EventUnregisterCallbackFunction(s_hEventStopDone, CBApp);
	CAL_EventUnregisterCallbackFunction(s_hEventStartDone, CBApp);
	CAL_EventClose(s_hEventStopDone);
	CAL_EventClose(s_hEventStartDone);

	CAL_EventUnregisterCallbackFunction(s_hEventAppDownloadDone, CBApp);
	CAL_EventClose(s_hEventAppDownloadDone);

	return ERR_OK;
}

static RTS_RESULT CDECL CyclicRunStopSwitch(void)
{
	RTS_I32 state = PollRunStopSwitch();
	if (state != s_bRun) {
		if (state)
			if (_boot_prg_loaded) {
				CAL_AppStartApplications();
			} else {
				CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_BLANK);
				CAL_CmpEmiconLCD_puts(0, 0, 0,
						      LCD_STR_UNLOCKED);
			}

		else
			if (_boot_prg_loaded) {
				CAL_AppStopApplications(RTS_TIMEOUT_DEFAULT,
						APP_STOP_REASON_RUNSTOP_SWITCH);
			} else {
				CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_BLANK);
				CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_LOCKED);
			}
	}
	s_bRun = state;

	return ERR_OK;
}

static void CDECL CBDenyStart(EventParam *pEventParam)
{
	EVTPARAM_CmpAppDenyStart *pParam;

	if (pEventParam->CmpIdProvider == CMPID_CmpApp) {
		switch (pEventParam->EventId) {
		case EVT_DenyStart:
			pParam = (EVTPARAM_CmpAppDenyStart *)\
				 pEventParam->pParameter;
			
			if (!PollRunStopSwitch())
				pParam->bDeny = 1;
			break;

		default:
			break;
		}
	}
}

static RTS_I32 PollRunStopSwitch(void)
{
	/*
	* return 1: switch is in run
	* return 0: switch is in stop
	*/	

	static char old_button_code = NOT_PRESSED_BUTTON_CODE; 
	static bool button_pressed = FALSE, state_switched = FALSE;
	static bool start_stop_button_is_pressed = FALSE;
	static RTS_I32 s_bRunStopSwitch = 1;
	static int fd;
	static int gpio_enabled = 0;
	struct timeval tv;
	static long int zerro_point_ms = 0;
	long int curent_point_ms;
	static bool init = FALSE;

	/* строка str для настройки и последующего считывания GPIO.  */
	char str[4];

	if (!gpio_enabled) {
		// Включаем gpio кнопки
		strcpy(str, "56");
		fd = open("/sys/class/gpio/export", O_WRONLY);
		write(fd, str, strlen(str));
		close(fd);

		strcpy(str, "in");
		fd = open("/sys/class/gpio/gpio56/direction", O_WRONLY);
		write(fd, str, strlen(str));
		close(fd);

		gpio_enabled = 1;

		printf("Run/Stop активирован\n");
	} 

	// считываем состояние gpio кнопки
	fd = open("/sys/class/gpio/gpio56/value", O_RDONLY);
	read(fd, str, 1);
	close(fd);

	if (str[0] == PRESSED_BUTTON_CODE
	    && old_button_code == NOT_PRESSED_BUTTON_CODE) 
		button_pressed = TRUE;

	if (str[0] == NOT_PRESSED_BUTTON_CODE
	    && old_button_code == PRESSED_BUTTON_CODE)
		button_pressed = FALSE;

	old_button_code = str[0];

	gettimeofday(&tv, NULL);

	// Convert microseconds to milliseconds
	curent_point_ms = tv.tv_sec * 1000 + round(tv.tv_usec / 1000.0f);

	/* Если кнопка нажата при старте, то нельзя ее переключать по времени.
	 * В этом случае блокируем переключение при первом цикле.
	 */
	if (!init){
		if (button_pressed) {
			state_switched = TRUE;
			s_bRunStopSwitch = 0;
			printf("Stop\n");
			CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_STOP);
		}
    		init = TRUE;
	}

	if (!button_pressed){
		zerro_point_ms = 0;
		state_switched = FALSE;
	} else {
		
		if (zerro_point_ms == 0) {
			zerro_point_ms = curent_point_ms;
		} else {
			if (curent_point_ms - zerro_point_ms > 
			    START_STOP_PRESS_BUTTON_INTERVAL &&
			    !state_switched){
				s_bRunStopSwitch =  s_bRunStopSwitch ? 0 : 1;
				zerro_point_ms = curent_point_ms;
				state_switched = TRUE;

				if (s_bRunStopSwitch)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID,
						   LOG_INFO, ERR_OK, 0,
						   LOG_STR_RUN);
				else
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID,
						   LOG_INFO, ERR_OK, 0,
						   LOG_STR_STOP);
			}			
		}
	}	
	 
	return s_bRunStopSwitch;
}

static void CDECL CBApp(EventParam *pEventParam)
{
	if (pEventParam->usVersion < EVTVERSION_CmpApp)
		return;

	switch (pEventParam->EventId) {
	case EVT_LoadBootprojectDone:
		_boot_prg_loaded = true;
		break;
	case EVT_DownloadDone:
		_boot_prg_loaded = true;
		break;
	case EVT_StopDone:
		CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_BLANK);
		CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_STOP);
		break;
	case EVT_StartDone:
		CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_BLANK);
		CAL_CmpEmiconLCD_puts(0, 0, 0, LCD_STR_RUN);
		break;

	}
}
