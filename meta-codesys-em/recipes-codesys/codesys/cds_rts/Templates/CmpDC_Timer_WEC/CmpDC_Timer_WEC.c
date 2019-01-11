/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CEDistributedClocks component
*	Version:
*	Description:
******************************************************************************/

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "CmpItf.h"

#include "CmpDC_Timer_WECDep.h"

#ifndef CPLUSPLUS
	typedef struct
	{
		IBase Base;
		ICmpEventCallback EventCallback;
	} CCmpDC_Timer_WEC;

	DECLARE_ADDREF
	DECLARE_RELEASE
	DECLARE_QUERYINTERFACE

	static CCmpDC_Timer_WEC s_CCmpDC_Timer_WEC;
#else
	static CCmpDC_Timer_WEC *s_pCCmpDC_Timer_WEC = NULL;
#endif

#define IOC_SET_TIMER_INTERVAL 0x666

static void CDECL EventCallbackFunctionSchedule(EventParam *pEventParam);
static void CDECL EventCallbackFunctionSysTask(EventParam *pEventParam);

static RTS_RESULT SetupCustomerUsTimer(void);
static RTS_RESULT StopCustomerUsTimer(void);

static RTS_RESULT setTimerInterval(unsigned long ulIntervalUs);
RTS_HANDLE s_hDev = RTS_INVALID_HANDLE;
RTS_HANDLE s_hDrv = RTS_INVALID_HANDLE;
static RTS_HANDLE LoadTimerDriver(RTS_RESULT* pResult);
static RTS_HANDLE OpenTimerDriver(RTS_RESULT* pResult);
static RTS_RESULT CloseTimerDriver(RTS_HANDLE hDrv);
static RTS_RESULT UnloadTimerDriver(RTS_HANDLE hDev);

USE_STMT

/*********** external event triggered task stuff ********************************/

/* For external event tasks with interval, add to device description file, 
		section taskconfiguration :

		<ts:setting name="externaleventcycletime" type="boolean" access="visible"> 
			  <ts:value>1</ts:value> 
		</ts:setting>

		<ts:setting name="externalevents" type="cdata" access="hide">
			<ts:value><![CDATA[
				<externalevents>                                  
					<externalevent>
					   <name>EVENT_ECM_DC</name>
					</externalevent>           
                </externalevents>
			]]></ts:value>
		</ts:setting>
*/

/* event name must be the same as in the device description                     */
#define DC_EVENT_NAME				"EVENT_ECM_DC"
/* Ultra-high Windows CE priority for the thread waiting for the OEM-specific 
   event from the hardware timer handler in the CE kernel                       */
#define DC_PROC_PRIO_WINCE_PRIO		2

/* when a new external event triggered task with interval has been created, then 
   we want to know its (initial) interval (should be same as the DC interval)   */
static RTS_HANDLE s_hEventExternalEventTaskCreateDone;

/* we want to be informed when the task interval must be changed (i.e., when the 
  DC control loop wants to have a slightly smaller or larger interval)          */
static RTS_HANDLE	s_hEventSysTaskSetInterval = 0;

static DWORD		s_dwTaskInterval = 0;
static HANDLE		s_hCustomerUsEvent = 0;
static HANDLE		s_hThreadtimer = 0;
static BOOL			s_bStopThread = 0;

static BOOL			s_bSimulateExtEvts = 0;
static RTS_HANDLE	s_hExternalSchedEvent = RTS_INVALID_HANDLE;/* not really a handle */ 
static RTS_HANDLE	s_hEvent = RTS_INVALID_HANDLE;


DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
#ifndef RTS_COMPACT_MICRO
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
#endif

	s_hEventExternalEventTaskCreateDone = RTS_INVALID_HANDLE;
/*	
	s_hEventPrepareExternalEventTaskDelete = RTS_INVALID_HANDLE;
*/

	s_hEventSysTaskSetInterval = RTS_INVALID_HANDLE;

	s_dwTaskInterval = 1000; /* a reasonable initial interval */

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpDC_Timer_WEC);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpDC_Timer_WEC)
	{
		if (s_pCCmpDC_Timer_WEC == NULL)
			s_pCCmpDC_Timer_WEC = static_cast<CCmpDC_Timer_WEC *>(new CCmpDC_Timer_WEC());
		return (IBase*)s_pCCmpDC_Timer_WEC->QueryInterface((ICmpDC_Timer_WEC *)s_pCCmpDC_Timer_WEC, ITFID_IBase, pResult);
	}
#else
	if (cid == CLASSID_CCmpDC_Timer_WEC)
	{
		IBase *pI = &s_CCmpDC_Timer_WEC.Base;
		pI->bIEC = 0;
		pI->AddRef = AddRef;
		pI->Release = Release;
		pI->QueryInterface = QueryInterface;
		pI->iRefCount++;
		return pI;
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	if (pIBase->Release() == 0)
		s_pCCmpDC_Timer_WEC = NULL;
	return ERR_OK;
#else
	if (pIBase->iRefCount > 0)
		pIBase->iRefCount--;
	return ERR_OK;
#endif
}

#ifndef RTS_COMPACT_MICRO

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
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

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
#ifdef RTS_COMPACT_MICRO
			ComponentEntry(NULL);
#endif
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
		{	
			break;
		}
		case CH_INIT3:
		{
			IBase *pIBase;
			ICmpEventCallback *pICallback;

			if (CHK_EventOpen)
			{
				/* For external event triggered tasks */
				s_hEventSysTaskSetInterval = CAL_EventOpen(EVT_TaskSetInterval, CMPID_SysTask, NULL);
			}
			if (CHK_EventRegisterCallbackFunction)
			{
				/* distributed clocks under CE are implemented through external event task with interval
				The task itself changes its interval in every cycle, depending on the deviance between own 
				interval and the DC frame
				*/
				CAL_EventRegisterCallbackFunction(s_hEventSysTaskSetInterval, EventCallbackFunctionSysTask, 0);
			}
			if (CHK_SchedRegisterExternalEvent)
			{
				s_hExternalSchedEvent = CAL_SchedRegisterExternalEvent(DC_EVENT_NAME, NULL);
			}

			/* Register callback Interface */
			pIBase = (IBase *)CreateInstance(CLASSID_CCmpDC_Timer_WEC, NULL);
			pICallback = (ICmpEventCallback *) pIBase->QueryInterface(pIBase, ITFID_ICmpEventCallback, NULL);
			pIBase->Release(pIBase);

			break;
		}
		case CH_INIT_TASKS:
		{
			RTS_RESULT err = SetupCustomerUsTimer();
			s_bSimulateExtEvts = 1;/* TODO disable simulation */
			break;
		}
		case CH_INIT_COMM:
			break;

		case CH_COMM_CYCLE:
		{
			if (s_bSimulateExtEvts)
				CAL_SchedPostExternalEvent(s_hExternalSchedEvent);
			break;
		}
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			s_bSimulateExtEvts = 0;
			break;
		case CH_EXIT3:
		{
			if (CHK_SchedUnregisterExternalEvent)
				CAL_SchedUnregisterExternalEvent(s_hExternalSchedEvent);
			if (CHK_EventUnregisterCallbackFunction)
				CAL_EventUnregisterCallbackFunction(s_hEventSysTaskSetInterval, EventCallbackFunctionSysTask);

			break;
		}
		case CH_EXIT2:
			StopCustomerUsTimer();
			break;
		case CH_EXIT:			
		{
			EXIT_STMT;
			break;
		}
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

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer ro the IBase interface. So it doesn't matter, which interface
		   is used to get the IBase pointer */
		ICmpEventCallback *pI = (ICmpEventCallback *)pBase;
		pI->pBase->iRefCount++;
		return pI->pBase;
	}
	if (iid == ITFID_ICmpEventCallback)
	{
		CCmpDC_Timer_WEC *pC = (CCmpDC_Timer_WEC *)pBase;
		pC->EventCallback.pBase = pBase;
		pC->EventCallback.IEventCallback = EventCallback;
		pC->Base.iRefCount++;
		return &pC->EventCallback;
	}
	return NULL;
}
#endif

STATICITF void CDECL EventCallback(RTS_HANDLE hCEDistributedClocks, EventParam *pEventParam)
{

}

static void CDECL EventCallbackFunctionSysTask(EventParam *pEventParam)
{
	if (EVT_TaskSetInterval == pEventParam->EventId && CMPID_SysTask == pEventParam->CmpIdProvider)
	{	
		EVTPARAM_SysTaskSetInterval* pParam = (EVTPARAM_SysTaskSetInterval*)pEventParam->pParameter;
		systasksetinterval_struct* pTaskSetInterval = pParam->pSysTaskSetInterval;
		s_dwTaskInterval = pTaskSetInterval->ulInterval;
		if(setTimerInterval(s_dwTaskInterval) != ERR_OK)
		{
			printf("SysTask DC event interval set failed with error %d\r\n", s_dwTaskInterval);
		}
	}
}

static void CDECL EventCallbackFunctionSchedule(EventParam *pEventParam)
{
	unsigned long ulErr;
	switch (pEventParam->EventId)
	{	
		case EVT_ExternalEventTaskCreateDone:
		{
			if (pEventParam->usParamId >= EVTPARAMID_CmpSchedule)
			{
				EVTPARAM_CmpSchedule *pParam = (EVTPARAM_CmpSchedule *)pEventParam->pParameter;
				/* EVTPARAM_CmpSchedule has these 2 members */
				pParam->pTaskDesc;
				pParam->hEvent;

				/* Check if external event name matches */
				if (strcmp(pParam->pTaskDesc->pInfo->pszExternalEvent, DC_EVENT_NAME) == 0)
				{
					s_dwTaskInterval = pParam->pTaskDesc->pInfo->dwInterval;
					ulErr = setTimerInterval(s_dwTaskInterval);
					if(ulErr != ERR_OK)
					{
						printf("SysTask DC event interval set failed with error 0x%x\r\n", ulErr);
					}
				}
			}
			break;
		}
		default:
			break;
	}
}

DWORD WINAPI TimerProc(LPVOID lpParameter)
{
	DWORD dWait				= 0;
	DWORD dwHPETMainCounter = 0;
	DWORD dwCompareValue	= 0;
	RTS_RESULT Result		= ERR_OK;
	ULONG ulCount			= 0;

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "Us Timer proc entered");
	
	while(TRUE)
	{
		dWait = WaitForSingleObject(s_hCustomerUsEvent,INFINITE);
		if (s_bStopThread) 
			break;
		
		if (dWait == WAIT_OBJECT_0) 
		{
			/* trigger the EtherCAT IEC task to do its next cycle */
			CAL_SchedPostExternalEvent(s_hExternalSchedEvent);
			ResetEvent(s_hCustomerUsEvent); /* TODO. Do this only is the event has been created with ManualReset == TRUE */
		}
	}
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "Us Timer proc ended");
	return 0;
}


RTS_RESULT SetupCustomerUsTimer(void)
{
	RTS_RESULT Result = ERR_FAILED;
	unsigned long ulThreadId;

	s_hDev = LoadTimerDriver(&Result);
	s_hDrv = OpenTimerDriver(&Result);

	if (s_hDrv == INVALID_HANDLE_VALUE)
		printf("Could not load kernel driver! Hardware timer cannot be used");

	/* create an event, could be a named event 
	e.g. event with manual reset 
	we assume the event to be already created by the kernel driver for the hardware timer */
	s_hCustomerUsEvent = CreateEvent(NULL, TRUE /* manual reset */, FALSE /* initial value*/,L"TimerEvent");
	if (s_hCustomerUsEvent == NULL)
		return ERR_FAILED;
	if (GetLastError() != ERROR_ALREADY_EXISTS)
		return ERR_FAILED; /* the already existing object could not be created */

	/* Create Thread handling the timer event set by the OEM-specific timer driver in the kernel */
	s_bStopThread = FALSE;
	s_hThreadtimer = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TimerProc,/*pTimerInfo*/NULL,0,&ulThreadId);
	if (s_hThreadtimer == 0)
	{
		/* TODO clean up */
		printf("Could not initialize microsecond timer thread\r\n");
		return ERR_FAILED;
	}

	if (!CeSetThreadPriority((HANDLE)s_hThreadtimer, DC_PROC_PRIO_WINCE_PRIO))
	{
		printf("CeSetThreadPriority failed\r\n");
		return ERR_FAILED;
	}
	
#if 0
	CAL_SysTaskResume(s_hThreadtimer);
#endif

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Started customer microsecond timing");
	return ERR_OK;
}

static RTS_RESULT StopCustomerUsTimer(void)
{
	DWORD dWait = 0;

	/* clean up */
	if(s_hThreadtimer)
	{
		s_bStopThread = TRUE;
		SetEvent(s_hCustomerUsEvent);
		
		dWait = WaitForSingleObject(s_hThreadtimer,INFINITE);
		if (dWait == WAIT_OBJECT_0) 
		{
			if(s_hThreadtimer)
				CloseHandle(s_hThreadtimer);
			if(s_hCustomerUsEvent)
				CloseHandle(s_hCustomerUsEvent);
			s_hThreadtimer = NULL;
			s_hCustomerUsEvent = NULL;	
		}
	}
	CloseTimerDriver(s_hDrv);
	UnloadTimerDriver(s_hDev);
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "OEM microsecond timing stopped");
	return ERR_OK;
}

static RTS_RESULT setTimerInterval(unsigned long ulIntervalUs)
{
	/* TODO: 
	here we have to pass the new interval to the OEM-specific 
	kernel driver handling the hardware timer 
	*/
	RTS_RESULT Result = ERR_FAILED;
	unsigned long ulParam = ulIntervalUs;

	if (INVALID_HANDLE_VALUE != s_hDrv)
		DeviceIoControl(s_hDrv, IOC_SET_TIMER_INTERVAL, &ulParam, sizeof(ulParam), &Result, sizeof(Result), 0, 0);
	return Result;
}


static RTS_HANDLE OpenTimerDriver(RTS_RESULT* pResult)
{
	/* TODO adapt the driver name here */
	RTS_HANDLE hDrv = (RTS_HANDLE)CreateFile((LPCWSTR)_T("xxx"), GENERIC_READ | GENERIC_WRITE, 0, NULL, (DWORD)OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hDrv == INVALID_HANDLE_VALUE)
	{
		RTS_SETRESULT(pResult, ERR_FAILED);
		return RTS_INVALID_HANDLE;
	}
	RTS_SETRESULT(pResult, ERR_OK);
	return hDrv;
}


static RTS_RESULT CloseTimerDriver(RTS_HANDLE hDrv)
{
	if (hDrv == INVALID_HANDLE_VALUE)
		return ERR_PARAMETER;

	CloseHandle(hDrv);
	hDrv = INVALID_HANDLE_VALUE;
	return ERR_OK;
}

static RTS_HANDLE LoadTimerDriver(RTS_RESULT* pResult)
{
	RTS_HANDLE hDev	= RTS_INVALID_HANDLE;
	HANDLE hFind = 0;
	DEVMGR_DEVICE_INFORMATION devInfo = {0};

	/* deactivate the driver if already loaded */
	devInfo.dwSize = sizeof(devInfo);
	/* TODO adapt driver instance name here*/
	hFind = FindFirstDevice(DeviceSearchByLegacyName, "XXX0:", &devInfo);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		FindClose(hFind);
		DeactivateDevice(devInfo.hDevice);
	}

/*	AddDriverToRegistry();
	hDev = ActivateDeviceEx(DRIVER_REG_KEY, NULL, 0, NULL);
*/
	if (hDev == NULL) 
	{
		RTS_SETRESULT(pResult, ERR_FAILED);
		return RTS_INVALID_HANDLE;
	}
	RTS_SETRESULT(pResult, ERR_OK);
	return hDev;
}


static RTS_RESULT UnloadTimerDriver(RTS_HANDLE hDev)
{
	if (hDev == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	
	DeactivateDevice((HANDLE)hDev);
	return ERR_OK;
}



