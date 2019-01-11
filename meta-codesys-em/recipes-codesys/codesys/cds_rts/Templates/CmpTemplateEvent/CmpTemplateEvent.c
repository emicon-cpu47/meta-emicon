/**
 * <name>CmpTemplateEvent.c</name>
 * <description> 
 *	Very simple example about using runtime system events.
 *	Runtime system events are posted by various runtime components, and can be catched by other components. by registering a callback function.
 *	They can be used for communication between runtime system components. The communication using events is more flexible than function calls,
 *	because the component that posts the event needs not to know the components that register to the event.
 *	This example shows how to catch existing events, by registering a callback function to events from two different other components.
 *
 *	More examples about using events can be found in CmpTemplate and CmpTemplateEventIEC.
 *
 *	USAGE:
 *	- CAL_EventOpen() and CAL_EventRegisterCallbackFunction() must be called to register the callback function	
 *	- CAL_EventUnregisterCallbackFunction() and CAL_EventClose() must be called to unregister	
 *	- CallbackFunction() is the callback function to catch the event
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpTemplateEventDep.h"

/* The callback function */
static void CDECL CallbackFunction(EventParam *pEventParam);

/* Handle to the event defined by CmpApp */
static RTS_HANDLE s_hEventAppDownloadDone = RTS_INVALID_HANDLE;
/* Handle to the event defined by CmpMonitor */
static RTS_HANDLE s_hEventPrepareWriteVariable = RTS_INVALID_HANDLE;

USE_STMT

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI			IN	Pointer to component mangager function to get a api function
 *		pfCallHook			IN	Pointer to component mangager function to call a hook function
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

/**
 * <description>Publish exported functions to the component manager, to make them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
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
	/* Our component version defined in our Dep file */
	return CMP_VERSION;
}

/**
 * <description>Example for a Hook function. Register and unregister callback functions here.</description>
 * <result></result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		/* Init */
		case CH_INIT_SYSTEM:
			/* First call at system startup to initialize all system components */
			/* Do not call other components here, use for internal init code only */
			break;
		case CH_INIT:
			/* First call at system startup. Compontents should initialize all local variables. */
			/* Do not call other components here, use for internal init code only */
			break;
		case CH_INIT2:
			/* Called after CH_INIT. All components are initialized. Other components can be used. */
			/* NOTE: Events must be created by the provider in this init step! */
			/* Other components create their events here */
			break;
		case CH_INIT3:
		{
			/* All components are initialized. Other components can be used. */
			/* NOTE: Event callbacks must be registered by the consumer in this init step! Events are created in CH_INIT2. */
			/* Now events from other components can be used. Open event and register callback function at startup */
			/* Open the events we want to use */
			if (CHK_EventOpen)
			{
				s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone, CMPID_CmpApp, NULL);
				s_hEventPrepareWriteVariable = CAL_EventOpen(EVT_PrepareWriteVariable, CMPID_CmpMonitor, NULL);
			}
			/* Register callback function */
			if (CHK_EventRegisterCallbackFunction)
			{
				CAL_EventRegisterCallbackFunction(s_hEventAppDownloadDone, CallbackFunction, 0);
				CAL_EventRegisterCallbackFunction(s_hEventPrepareWriteVariable, CallbackFunction, 0);
			}
			break;
		}
		case CH_INIT_TASKS:
			/* Called after CH_INIT_SYSTEM_TASKS. All components should start their tasks here. */
			/* NOTE: The IEC bootprojects are loaded here! */
			break;
		case CH_INIT_COMM:
			/* Called after CH_INIT_TASKS. Communication can be started at this point, because all components are ready and running. */
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
 			break;

		/* Exit */
		case CH_EXIT_COMM:
			/*	Called at the beginning of the shutdown sequence to disable all communication channels. */
			break;
		case CH_EXIT_TASKS:
			/* Called before CH_EXIT_SYSTEM_TASKS to stop and remove all tasks that are not needed by the IEC application. */
			break;
		case CH_EXIT3:
		{
			/* Called before CH_EXIT2 to store data (e.g. retain data). */
			/* Unregister from events at shutdown */
			if (CHK_EventUnregisterCallbackFunction)
			{
				CAL_EventUnregisterCallbackFunction(s_hEventAppDownloadDone, CallbackFunction);
				CAL_EventUnregisterCallbackFunction(s_hEventPrepareWriteVariable, CallbackFunction);
			}
			if (CHK_EventClose)
			{
				CAL_EventClose(s_hEventAppDownloadDone);
				CAL_EventClose(s_hEventPrepareWriteVariable);
			}
			break;
		}
		case CH_EXIT2:
			/* Called before CH_EXIT to store data (e.g. retain data). */
			break;
		case CH_EXIT:
		{
			/* Here all memory of the components should be released. */
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			/* Called at the end of the shutdown process for the system components to release memory. */
			break;
		default:
			break;
	}
	return ERR_OK;
}

/**
 * <description>Callback function to catch events.</description>
 * <param name="pEventParam" type="IN">Pointer to event parameter set.
 *	Use pEventParam->CmpIdProvider and pEventParam->EventId to identify the event.
 *	Every event has a parameter passed in pEventParam->pParameter. This is often a structure, defined in the components Itf file.
 * </param> 
 * <result></result>
 */
 static void CDECL CallbackFunction(EventParam *pEventParam)
{
	/* Use pEventParam->CmpIdProvider to identify the component that posts the event. Note that pEventParam->EventId is not unique in the system */
	switch (pEventParam->CmpIdProvider)
	{
		case CMPID_CmpApp:
			/* Use pEventParam->EventId to identify the event. */
			switch (pEventParam->EventId)
			{	
				case EVT_DownloadDone:
				{
					/* This event and its event parameter is defined in CmpMonitorItf.m4.
					   This is why USE_ITF(`CmpMonitorItf.m4') is need in the Dep file of our component */
					if (pEventParam->usVersion >= EVTVERSION_CmpApp)
					{
						char *pszName;
						EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
						pszName = pParam->pApp->szName;
						/* Just a logger output for test purposes */
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DownloadDone received: App=%s ***", pszName);
					}
					break;
				}
				default:
					break;
			}
			break;
		case CMPID_CmpMonitor:
			/* Use pEventParam->EventId to identify the event. */
			switch (pEventParam->EventId)
			{	
				case EVT_PrepareWriteVariable:
				{
					/* This event and its event parameter is defined in CmpAppItf.m4.
					   This is why USE_ITF(`CmpAppItf.m4') is need in the Dep file of our component */
					if (pEventParam->usVersion >= EVTVERSION_CmpMonitor2)
					{
						EVTPARAM_CmpMonitorWriteVar2 *pParam = (EVTPARAM_CmpMonitorWriteVar2*)pEventParam->pParameter;
						/* This event allows to deny the execution of this operation. To deny, set bDeny to 1 */
						/*TODO: pParam->bDeny = 1;*/
						/* ComponentID which denies this write operation */
						pParam->cmpId = COMPONENT_ID;
						/* Just a logger output for test purposes */
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareWriteVariable received: Size %d Address 0x%x, Value at 0x%x ***", pParam->usSize, pParam->pAddress, pParam->pValue);
					}
					break;
				}
				default:
					break;
			}
			break;
		default:
			break;
	}
}
