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
#include "CmpCEDistributedClocksDep.h"
#if defined(WIN32) && !defined(STD_CALL)
	#include <windows.h>
#endif

#ifndef CPLUSPLUS
	typedef struct
	{
		IBase Base;
		ICmpEventCallback EventCallback;
	} CCmpCEDistributedClocks;

	DECLARE_ADDREF
	DECLARE_RELEASE
	DECLARE_QUERYINTERFACE

	static CCmpCEDistributedClocks s_CCmpCEDistributedClocks;
#else
	static CCmpCEDistributedClocks *s_pCCmpCEDistributedClocks = NULL;
#endif


static void CDECL EventCallbackFunction(EventParam *pEventParam);
static void CDECL EventCallbackFunctionSchedule(EventParam *pEventParam);

static RTS_RESULT SetupCustomerUsTimer(void);
static RTS_RESULT StopCustomerUsTimer(void);

static RTS_RESULT setTimerInterval(unsigned long ulIntervalUs);
static RTS_RESULT UnLoadDriver(void);

USE_STMT

#define DC_EVENT_NAME	"EVENT_ECM_DC"
#define DC_PROC_PRIO	2
static RTS_HANDLE s_hEventSourceDownload;
/* For external event triggered tasks */
static RTS_HANDLE s_hEventExternalEventTaskCreateDone;
static RTS_HANDLE s_hEventPrepareExternalEventTaskDelete;
static RTS_HANDLE s_hEventSysTaskSetInterval;

static DWORD s_dwTaskInterval;
static HANDLE	s_hCustomerUsEvent;
static HANDLE	s_hThreadtimer;
static BOOL		s_bStopThread;
static void (*s_pfTaskEntry)(void) = NULL;
// static RTS_HANDLE s_hEvent = RTS_INVALID_HANDLE;
Task_Desc *s_pDCTask;
/* For external event tasks with interval, add to device description file:

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

	/* For external event triggered tasks */
	s_hEventExternalEventTaskCreateDone = RTS_INVALID_HANDLE;
	s_hEventPrepareExternalEventTaskDelete = RTS_INVALID_HANDLE;
	s_hEventSysTaskSetInterval = RTS_INVALID_HANDLE;

	s_dwTaskInterval = 1000;
	s_pDCTask = 0;
	s_pfTaskEntry = 0;

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpCEDistributedClocks);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpCEDistributedClocks)
	{
		if (s_pCCmpCEDistributedClocks == NULL)
			s_pCCmpCEDistributedClocks = static_cast<CCmpCEDistributedClocks *>(new CCmpCEDistributedClocks());
		return (IBase*)s_pCCmpCEDistributedClocks->QueryInterface((ICmpCEDistributedClocks *)s_pCCmpCEDistributedClocks, ITFID_IBase, pResult);
	}
#else
	if (cid == CLASSID_CCmpCEDistributedClocks)
	{
		IBase *pI = &s_CCmpCEDistributedClocks.Base;
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
		s_pCCmpCEDistributedClocks = NULL;
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

			/* Register callback function */
			if (CHK_EventOpen)
			{
				/* For external event triggered tasks */
				s_hEventExternalEventTaskCreateDone = CAL_EventOpen(EVT_ExternalEventTaskCreateDone, CMPID_CmpSchedule, NULL);
				s_hEventPrepareExternalEventTaskDelete = CAL_EventOpen(EVT_PrepareExternalEventTaskDelete, CMPID_CmpSchedule, NULL);
				s_hEventSysTaskSetInterval = CAL_EventOpen(EVT_TaskSetInterval, CMPID_SysTask, NULL);
			}
			if (CHK_EventRegisterCallbackFunction)
			{
				/* For external event triggered tasks */
				CAL_EventRegisterCallbackFunction(s_hEventExternalEventTaskCreateDone, EventCallbackFunctionSchedule, 0);
				CAL_EventRegisterCallbackFunction(s_hEventPrepareExternalEventTaskDelete, EventCallbackFunctionSchedule, 0);

				/* ditributed clocks under CE are implemented through external event task */
				CAL_EventRegisterCallbackFunction(s_hEventSysTaskSetInterval, EventCallbackFunctionSchedule, 0);
			}
			/* Register callback Interface */
			pIBase = (IBase *)CreateInstance(CLASSID_CCmpCEDistributedClocks, NULL);
			pICallback = (ICmpEventCallback *) pIBase->QueryInterface(pIBase, ITFID_ICmpEventCallback, NULL);
			pIBase->Release(pIBase);

			break;
		}
		case CH_INIT_TASKS:
			SetupCustomerUsTimer();
			break;
		case CH_INIT_COMM:
			break;

		case CH_COMM_CYCLE:
 			break;
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
		{
			if (CHK_EventRegisterCallbackFunction)
			{
				/* For external event triggered tasks */
				CAL_EventUnregisterCallbackFunction(s_hEventExternalEventTaskCreateDone, EventCallbackFunction);
				CAL_EventUnregisterCallbackFunction(s_hEventPrepareExternalEventTaskDelete, EventCallbackFunction);
				CAL_EventUnregisterCallbackFunction(s_hEventSysTaskSetInterval, EventCallbackFunction);
			}
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
		CCmpCEDistributedClocks *pC = (CCmpCEDistributedClocks *)pBase;
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

static void CDECL EventCallbackFunction(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		default:
			break;
	}
}

static RTS_HANDLE s_hEvent = RTS_INVALID_HANDLE;
Task_Desc *s_pTask;

static void CDECL EventCallbackFunctionSchedule(EventParam *pEventParam)
{
	unsigned long ulErr;
	switch (pEventParam->EventId)
	{	
		/* For external event triggered tasks */
		case EVT_ExternalEventTaskCreateDone:
		/* !!!! case EVT_TaskSetInterval: this is the same EventID */
		{
			if (pEventParam->CmpIdProvider == CMPID_SysTask)
			{
				/* this means event is EVT_TaskSetInterval */
				EVTPARAM_SysTaskSetInterval* pParam = (EVTPARAM_SysTaskSetInterval*)pEventParam->pParameter;
				systasksetinterval_struct* pTaskSetInterval = pParam->pSysTaskSetInterval;
				s_dwTaskInterval = pTaskSetInterval->ulInterval;
				if(setTimerInterval(s_dwTaskInterval) != ERR_OK)
				{
					printf("SysTask DC event interval set failed  %d\r\n", s_dwTaskInterval);
				}
			}
			else if (pEventParam->usParamId >= EVTPARAMID_CmpSchedule)
			{
				EVTPARAM_CmpSchedule *pParam = (EVTPARAM_CmpSchedule *)pEventParam->pParameter;
				/* EVTPARAM_CmpSchedule has these 2 members */
				pParam->pTaskDesc;
				pParam->hEvent;

				/* Check if external event name matches */
				if (strcmp(pParam->pTaskDesc->pInfo->pszExternalEvent, DC_EVENT_NAME) == 0)
				{
					s_pDCTask = pParam->pTaskDesc;

					/* Method 1:Use pParam->hEvent to set the event that will run one cycle of the task that was created by the scheduler. */
					/* Add SysEvent interface to the dep.m4 file */
					s_hEvent = pParam->hEvent;

					/* Method 2:Use function pointer in pParam->pTaskDesc to call task function directly */
					/* Example: ; */
					memcpy(&s_pfTaskEntry, (unsigned long *)pParam->pTaskDesc->pInfo->dwTaskEntryFunctionPointer, sizeof(s_pfTaskEntry));

					s_dwTaskInterval = pParam->pTaskDesc->pInfo->dwInterval;
					ulErr = setTimerInterval(s_dwTaskInterval);
					if(ulErr != ERR_OK)
					{
						printf("SysTask DC event interval set failed  0x%x\r\n", ulErr);
					}
				}
			}
			break;
		}
		case EVT_PrepareExternalEventTaskDelete:
		{
			if (pEventParam->usParamId >= EVTPARAMID_CmpSchedule)
			{
				EVTPARAM_CmpSchedule *pParam = (EVTPARAM_CmpSchedule *)pEventParam->pParameter;

				/* Check if external event name matches */
				if (strcmp(pParam->pTaskDesc->pInfo->pszExternalEvent, DC_EVENT_NAME) == 0)
				{
					s_pDCTask = NULL;
					s_hEvent = RTS_INVALID_HANDLE;
					s_pfTaskEntry = NULL;
				}
			}
			break;
		}
		default:
			break;
	}
}

#if 0
/* Example for external task */
typedef struct
{
	RTS_IEC_DWORD dwTaskInfo;
	RTS_IEC_DWORD dwApplicationInfo;
	RTS_IEC_DWORD dwTaskHandle;
	RTS_IEC_BOOL bResult;
	RTS_IEC_BOOL bDummy1;
	RTS_IEC_BOOL bDummy2;
	RTS_IEC_BOOL bDummy3;
} IEC_CYCLE_STRUCT;

/* This function has to be called from OEM */
void CyclicCallback()
{
	IEC_CYCLE_STRUCT ics;

	if (s_hEvent == RTS_INVALID_HANDLE)
		return;
	/* Method 1:Use pParam->hEvent to set the event that will run one cycle of the task that was created by the scheduler. */
	CAL_SysEventSet(s_hEvent);

	/* Method 2: Call IecTaskCycle with given task. This will inlcude IO update */
   if (s_pTask != 0 && s_pTask->pInfo->dwTaskEntryFunctionPointer != 0)
   {
       CAL_IecTaskCycle(s_pTask);
   }

	/* Method 3: Use function pointer in pParam->pTaskDesc to call task function directly. This will NOT inlcude IO update */
	if (s_pfTaskEntry == NULL)
		return;
	memset((char*) &ics, 0, sizeof(ics));
	ics.dwTaskInfo = (RTS_IEC_DWORD)s_pTask->pInfo;
	ics.dwApplicationInfo = (RTS_IEC_DWORD)s_pTask->pAppl;
	ics.dwTaskHandle = (RTS_IEC_DWORD)s_pTask;
	CAL_SysCpuCallIecFuncWithParams((RTS_VOID_FCTPTR)s_pfTaskEntry, (void*)&ics, sizeof(ics));	
}
#endif

DWORD WINAPI TimerProc( LPVOID lpParameter)
{
	DWORD						dWait = 0;
	DWORD						dwHPETMainCounter = 0;
	DWORD						dwCompareValue = 0;
	RTS_RESULT					Result = ERR_OK;
	ULONG ulCount = 0;

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "Us Timer proc entered");
	
	while(TRUE)
	{
		dWait = WaitForSingleObject(s_hCustomerUsEvent,INFINITE);
		if (s_bStopThread) 
			break;
		
		if (dWait == WAIT_OBJECT_0) 
		{
			if (s_pDCTask)
				CAL_IecTaskCycle(s_pDCTask);
		}
	}
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "Us Timer proc ended");
	return 0;
}


RTS_RESULT SetupCustomerUsTimer(void)
{
#if !defined (_WIN32_WCE)
	return ERR_NOTIMPLEMENTED;
#endif

	RTS_RESULT Result = ERR_FAILED;
	unsigned long ulThreadId;
	ULONG irq = 11;
	DWORD dwLastErr = 0;
	TCHAR wszDriverPath[256] = { 0 };
	LPTSTR psz;

	s_pDCTask = NULL;

	//load driver
	if (GetModuleFileName(NULL, (TCHAR*)&wszDriverPath, 256 * sizeof(TCHAR)) > 0)
	{
		psz = wcsrchr(wszDriverPath, '\\');
		if (psz != NULL)
			*psz = 0;
		else
			wszDriverPath[256-1] = 0;

		wcscat(wszDriverPath, L"\\");
		wcscat(wszDriverPath, L"xxx.dll");	
		
/*
		if(LoadDriver(wszDriverPath)!= _ERR_OK)
		{
			printf("Loading driver failed\r\n");
			return ERR_FAILED;
		}
*/
	}
	else
	{
/*		if(LoadDriver(L"xxxx.dll")!= ERR_OK)
		{
			printf("Loading driver failed\r\n");
			return ERR_FAILED;
		}
*/
	}
		
	//create an event  
	s_hCustomerUsEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
	if (s_hCustomerUsEvent == NULL)
	{
		return ERR_FAILED;
	}
/*
	if (openEvent(s_hCustomerUsEvent,irq,s_dwTaskInterval,DC_PROC_PRIO)!= ERR_OK)
	{
		// clean up
		return ERR_FAILED;
	}
*/

	//Create Thread
	s_bStopThread = FALSE;
	s_hThreadtimer = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)TimerProc,/*pTimerInfo*/NULL ,0,&ulThreadId);
	if (s_hThreadtimer == 0)
	{
		// clean up 
		printf("Could not initialize microsecond timer thread\r\n");
		return ERR_FAILED;
	}

	if (!CeSetThreadPriority((HANDLE)s_hThreadtimer, DC_PROC_PRIO))
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

	// cleanup
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
	UnLoadDriver();
	printf("customer microsecond timing stopped\r\n");
	return ERR_OK;
}

RTS_RESULT setTimerInterval(unsigned long ulIntervalUs)
{
	// TODO
	return ERR_OK;
}

RTS_RESULT UnLoadDriver(void)
{
	return ERR_OK;
}

