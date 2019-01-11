/**
 * <name>CmpTemplateEventIEC.c</name>
 * <description> 
 *	Simple example about using runtime system events in IEC applications.
 *
 *	Runtime system events are posted by various runtime components, and can be catched by other components by registering a callback function.
 *	They can be used for communication between runtime system components, and between runtime system components and the IEC application.
 *	The communication using events is more flexible than function calls, because the component that posts the event needs not to know the components that register to the event,
 *	and because a function call from runtime component to IEC application is not possible otherwise.
 *	This example shows how to generate events, and how to catch event in an IEC application. This is done by registering a callback function to events.
 *	
 *	The example consists of this runtime component, a CODESYS library (CmpTemplateEventIEC.library), and a CODESYS test project (CmpTemplateEventIECTest.project).
 *	The runtime component creates the event at startup, and posts the event in the comm cycle.
 *	The CODESYS library defines event Ids and structures. This must correspond with the runtime component.
 *	The CODESYS test project is using the event by registering a callback function.
 *
 *	More examples about using events can be found in CmpTemplate and CmpTemplateEvent.
 *
 *	USAGE:
 *	- CAL_EventCreate2() must be called to register the callback function. IEC application can then call EventOpen and EventRegisterCallbackFunction.
 *	- CAL_EventClose() must be called to close the event	
 *	- CAL_EventPost() is called to post the event, and registered callback function will be called
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpTemplateEventIECDep.h"

#define EVTPARAMID_CmpTemplateEventIEC		0x0001
#define EVTVERSION_CmpTemplateEventIEC		0x0001
/* Event-Id. Must be same as 	EVT_Test: DWORD := EVTCLASS_INFO + 1; in CmpTemplateEventIEC.library */
#define EVT_Test							MAKE_EVENTID(EVTCLASS_INFO, 1)

/* Handle to the event defined by this component */
static RTS_HANDLE s_hEventTest = RTS_INVALID_HANDLE;

USE_STMT

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
/*	Return the version of our component */
{
	/* Our component version defined in our Dep file */
	return CMP_VERSION;
}

/* Example for a Hook function */
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
			/* Called after CH_INIT. All components are initialized. Other components can be used.
			/* NOTE: Events must be created by the provider in this init step! */
			/* Create new event here */
			if (CHK_EventCreate)
			{
				s_hEventTest = CAL_EventCreate2(EVT_Test, CMPID_CmpTemplateEventIEC, 1, NULL);
			}
			break;
		case CH_INIT3:
			/* All components are initialized. Other components can be used. */
			/* NOTE: Event callbacks must be registered by the consumer in this init step! Events are created in CH_INIT2. */
			break;
		case CH_INIT_TASKS:
			/* Called after CH_INIT_SYSTEM_TASKS. All components should start their tasks. */
			/* NOTE: The IEC bootprojects are loaded here! */
			break;
		case CH_INIT_COMM:
			/* Called after CH_INIT_TASKS. Communication can be started at this point, because all components are ready and running. */
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
		{
			/* Post our event in every comm cycle */
			if (CHK_EventPost)
			{
				// General event structure
				EventParam ep;
				// Specific event structure
				EVTPARAM_EvtTest evtParam;

				// Fill specific event structure
				evtParam.dwParam1 = 17;
				evtParam.xParam2 = 1;

				// Fill general event structure
				ep.CmpIdProvider = CMPID_CmpTemplateEventIEC;
				ep.EventId = EVT_Test;
				ep.usParamId = EVTPARAMID_CmpTemplateEventIEC;
				ep.usVersion = EVTVERSION_CmpTemplateEventIEC;
				ep.pParameter = &evtParam;

				// Post the event
				CAL_EventPost(s_hEventTest, &ep);
			}		
 			break;
		}

		/* Exit */
		case CH_EXIT_COMM:
			/*	Called at the beginning of the shutdown sequence to disable all communication channels. */
			break;
		case CH_EXIT_TASKS:
			/* Called before CH_EXIT_SYSTEM_TASKS to stop and remove all tasks that are not needed by the IEC application. */
			break;
		case CH_EXIT3:
			/* Called before CH_EXIT2 to store data (e.g. retain data). */
			break;
		case CH_EXIT2:
			/* Called before CH_EXIT to store data (e.g. retain data). */
			if (CHK_EventDelete)
			{
				// Delete our event
				CAL_EventDelete(s_hEventTest);
			}
			break;
		case CH_EXIT:
			/* Here all memory of the components should be released. */
			EXIT_STMT;
			break;
		case CH_EXIT_SYSTEM:
			/* Called at the end of the shutdown process for the system components to release memory. */
			break;
		default:
			break;
	}
	return ERR_OK;
}

