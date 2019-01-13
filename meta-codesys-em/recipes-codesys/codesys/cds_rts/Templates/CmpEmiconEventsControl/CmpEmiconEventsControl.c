/**
 */
#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconEventsControlDep.h"
#include <unistd.h>
#include <fcntl.h>

#define EVTPARAMID_CmpEmiconEventsControl	0x0001
#define EVTVERSION_CmpEmiconEventsControl	0x0001

static bool _is_emu = false;

#define EVT_B_BUTTON_PRESSED MAKE_EVENTID(EVTCLASS_INFO, 1)
#define EVT_GPIO_50 MAKE_EVENTID(EVTCLASS_INFO, 2)
#define EVT_GPIO_51 MAKE_EVENTID(EVTCLASS_INFO, 3)
#define EVT_GPIO_52 MAKE_EVENTID(EVTCLASS_INFO, 4)
#define EVT_GPIO_53 MAKE_EVENTID(EVTCLASS_INFO, 5)

static RTS_HANDLE _h_B_button = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_50 = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_51 = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_52 = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_53 = RTS_INVALID_HANDLE;

USE_STMT
// GPIO имеет инверсную логику
#define NOT_PRESSED_BUTTON_CODE 49 // ascii 1
#define PRESSED_BUTTON_CODE 48 // ascii 0

typedef struct gpio_control {
	uint8_t n;
	uint8_t old_satate;
	bool enabled;
} gpio_control;

gpio_control _B_button = {
	.n = 56, 		// кнопка B
	.old_satate = NOT_PRESSED_BUTTON_CODE,
	.enabled = false,
};

gpio_control _gpio_50 = {
	.n = 50,
	.old_satate = NOT_PRESSED_BUTTON_CODE,
	.enabled = false,
};

gpio_control _gpio_51 = {
	.n = 51,
	.old_satate = NOT_PRESSED_BUTTON_CODE,
	.enabled = false,
};

gpio_control _gpio_52 = {
	.n = 52,
	.old_satate = NOT_PRESSED_BUTTON_CODE,
	.enabled = false,
};
gpio_control _gpio_53 = {
	.n = 53,
	.old_satate = NOT_PRESSED_BUTTON_CODE,
	.enabled = false,
};

EventParam _tEventParam = {
	.pParameter = NULL,
	.usParamId = EVTPARAMID_CmpEmiconEventsControl,
	.usVersion = EVTVERSION_CmpEmiconEventsControl,
	.CmpIdProvider = CMPID_CmpEmiconEventsControl,
};
void enable_gpio(gpio_control *gpio);
bool r_trig_gpio(gpio_control *gpio); //детекция переднего фронта

static RTS_RESULT CDECL CreateEvents(void)
{

	_h_B_button = CAL_EventCreate2(EVT_B_BUTTON_PRESSED, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	printf("EVT_B_BUTTON_PRESSED, COMPONENT_ID: %lu, %lu\n",
		EVT_B_BUTTON_PRESSED, COMPONENT_ID);

	_h_gpio_50 = CAL_EventCreate2(EVT_GPIO_50, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	printf("EVT_GPIO_50, COMPONENT_ID: %lu, %lu\n",
		EVT_GPIO_50, COMPONENT_ID);

	_h_gpio_51 = CAL_EventCreate2(EVT_GPIO_51, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	printf("EVT_GPIO_51, COMPONENT_ID: %lu, %lu\n",
		EVT_GPIO_51, COMPONENT_ID);

	_h_gpio_52 = CAL_EventCreate2(EVT_GPIO_52, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	printf("EVT_GPIO_52, COMPONENT_ID: %lu, %lu\n",
		EVT_GPIO_52, COMPONENT_ID);

	_h_gpio_53 = CAL_EventCreate2(EVT_GPIO_53, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	printf("EVT_GPIO_53, COMPONENT_ID: %lu, %lu\n",
		EVT_GPIO_53, COMPONENT_ID);	

	return ERR_OK;
}


/**
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
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
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

/**
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	int res;

	switch (ulHook) {
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();
		CreateEvents();
		// _s_hEvent_my = CAL_EventOpen(0x01, CMPID_CmpEmiconEventsControl,
		// 				   NULL);
		// CAL_EventRegisterCallbackFunction(s_hEventTest, callback, 0);
		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		
		if (r_trig_gpio(&_B_button)) {
			_tEventParam.EventId = EVT_B_BUTTON_PRESSED;
			res = CAL_EventPost(_h_B_button, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_50)) {
			_tEventParam.EventId = EVT_GPIO_50;
			res = CAL_EventPost(_h_gpio_50, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_51)) {
			_tEventParam.EventId = EVT_GPIO_51;
			res = CAL_EventPost(_h_gpio_51, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_52)) {
			_tEventParam.EventId = EVT_GPIO_52;
			res = CAL_EventPost(_h_gpio_52, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_53)) {
			_tEventParam.EventId = EVT_GPIO_53;
			res = CAL_EventPost(_h_gpio_53, &_tEventParam);
		}

		break;


	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		CAL_EventClose(_h_B_button);
		CAL_EventClose(_h_gpio_50);
		CAL_EventClose(_h_gpio_51);
		CAL_EventClose(_h_gpio_52);
		CAL_EventClose(_h_gpio_53);

		CAL_EventDelete(_h_B_button);
		CAL_EventDelete(_h_gpio_50);
		CAL_EventDelete(_h_gpio_51);
		CAL_EventDelete(_h_gpio_52);
		CAL_EventDelete(_h_gpio_53);
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;

	}

	return ERR_OK;
}
void enable_gpio(gpio_control *gpio)
{
	char str[80];
	int fd;

	if (_is_emu)
		return;

	if (!gpio->enabled) {
		sprintf(str, "%d", gpio->n);
		fd = open("/sys/class/gpio/export", O_WRONLY);
		write(fd, str, strlen(str));
		close(fd);

		sprintf(str, "/sys/class/gpio/gpio%d/direction", gpio->n);
		fd = open(str, O_WRONLY);
		strcpy(str, "in");
		write(fd, str, strlen(str));
		close(fd);
		gpio->enabled = true;
		gpio->old_satate = NOT_PRESSED_BUTTON_CODE;
	}

	return;
}

bool r_trig_gpio(gpio_control *gpio)
{
	char str[80];
	int fd;
	bool ret = false;

	if (_is_emu)
		return ret;

	if (!gpio->enabled)
		enable_gpio(gpio);

	// считываем состояние gpio
	sprintf(str, "/sys/class/gpio/gpio%d/value", gpio->n);
	fd = open(str, O_RDONLY);
	read(fd, str, 1);
	close(fd);

	if (str[0] == PRESSED_BUTTON_CODE
	    && gpio->old_satate == NOT_PRESSED_BUTTON_CODE)
		ret = true;
	else
		ret = false;

	gpio->old_satate = str[0];

	return ret;
}

