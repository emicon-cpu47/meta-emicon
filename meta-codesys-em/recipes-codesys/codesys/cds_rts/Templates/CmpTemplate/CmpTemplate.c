/**
 * <name>CmpTemplate.c</name>
 * <description> 
 *  Example for a runtime component frame that can be used as a starting point to develop own components.
 *
 *  MANDATORY FUNCTIONS:
 *  - ComponentEntry()
 *  - ExportFunctions()
 *  - ImportFunctions()
 *  - CmpGetVersion()
 *  - HookFunction()
 *
 *  OPTIONAL FUNCTIONS:
 *  - CreateInstance() + DeleteInstance() + QueryInterface():
 *    Only for C++ Runtimes or if you implement at least a multiple instantiable interface (like CmpIoDrvItf or CmpLogBackendItf)
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpTemplateDep.h"

#ifndef CPLUSPLUS
	typedef struct
	{
		IBase Base;
		ICmpEventCallback EventCallback;
	} CCmpTemplate;

	DECLARE_ADDREF
	DECLARE_RELEASE
	DECLARE_QUERYINTERFACE

	static CCmpTemplate s_CCmpTemplate;
#else
	static CCmpTemplate *s_pCCmpTemplate = NULL;
#endif

USE_STMT

#include "RtsDisableOperations.c"
#include "RtsRunStopSwitch.c"
#include "RtsPowerFail.c"
#include "RtsHandleEvents.c"
#include "RtsServiceHandler.c"
#include "RtsExternalLibs.c"
#include "RtsInteractiveLogin.c"
#include "RtsHardwareWatchdog.c"
#include "RtsSupervisorOperation.c"

static RTS_HANDLE s_hExternalEventTask = RTS_INVALID_HANDLE;

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
 * <result>ERR_OK if component could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
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

#ifdef CPLUSPLUS
	INIT_LOCALS_STMT;
	s_pCCmpTemplate = NULL;
	/* Register your class, if the component should be used in a C++ runtime: */
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpTemplate);
#else
	/* Register your class, if you implement at least a multiple instantiable interface like CmpIoDrvItf or CmpLogBackendItf:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpTemplate);
    */
 #endif
	return ERR_OK;
}

/**
 * <description>OPTIONAL FUNCTION:
 *  Function is used to instantiate an object of the specified class if your component is used in a C++ runtime or if you implement 
 *  at least a multiple instantiable interface like CmpIoDrvItf or CmpLogBackendItf.
 * </description>
 * <param name="cid" type="IN">Requested ClassID to instantiate</param> 
 * <param name="pResult" type="IN">Pointer to error code</param> 
 * <result>Return a pointer to IBase interface of the newly created class object</result>
 */
static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpTemplate)
	{
		if (s_pCCmpTemplate == NULL)
			s_pCCmpTemplate = static_cast<CCmpTemplate *>(new CCmpTemplate());
		return (IBase*)s_pCCmpTemplate->QueryInterface((ICmpTemplate *)s_pCCmpTemplate, ITFID_IBase, pResult);
	}
#else
	if (cid == CLASSID_CCmpTemplate)
	{
		IBase *pI = &s_CCmpTemplate.Base;
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

/**
 * <description>OPTIONAL FUNCTION:
 *  Function is called to delete the object created in CreateInstance().
 * </description>
 * <param name="pIBase" type="IN">Pointer to IBase interface to delete the object</param> 
 * <result>Error code</result>
 */
static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	if (pIBase->Release() == 0)
		s_pCCmpTemplate = NULL;
	return ERR_OK;
#else
	if (pIBase->iRefCount > 0)
		pIBase->iRefCount--;
	return ERR_OK;
#endif
}

#ifndef RTS_COMPACT_MICRO

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
#endif

/**
 * <description>Hook function to get all broadcast hooks of the component manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			/* First call at system startup to initialize all system components */
			/* Do not call other components here, use for internal init code only */
#ifdef RTS_COMPACT_MICRO
			ComponentEntry(NULL);
#endif
			break;
		case CH_INIT:
			/* First call at system startup. Compontents should initialize all local variables. */
			/* Do not call other components here, use for internal init code only */
			break;
		case CH_INIT2:
		{	
			/* Called after CH_INIT. All components are initialized. Other components can be used.
			/* NOTE: Events must be created by the provider in this init step! */
			CreateEvents();
			break;
		}
		case CH_INIT3:
		{
			/* All components are initialized. Other components can be used. */
			/* NOTE: Event callbacks must be registered by the consumer in this init step! Events are created in CH_INIT2. */
			InitPowerFail();
			InitDisableOperations();
			InitRunStopSwitch();
			RegisterEventHandler();
			InitServiceHandler();
			s_hExternalEventTask = CAL_SchedRegisterExternalEvent("MyEvent", NULL);
			InitLoginHandler();
			RegisterSupervisor();
			break;
		}
		case CH_INIT_TASKS:
		{
			/* Called after CH_INIT_SYSTEM_TASKS. All components should start their tasks. */
			/* NOTE: The IEC bootprojects are loaded here! */
			StartHardwareWatchdog();
			break;
		}
		case CH_INIT_COMM:
			/* Called after CH_INIT_TASKS. Communication can be started at this point, because all components are ready and running. */
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
		{
			CyclicRunStopSwitch();
			CAL_SchedPostExternalEvent(s_hExternalEventTask);
			if (CHK_EventPost)
			{
				EventParam ep;

				ep.CmpIdProvider = CMPID_CmpTemplate;
				ep.EventId = EVT_Test;
				ep.usParamId = EVTPARAMID_CmpTemplate;
				ep.usVersion = EVTVERSION_CmpTemplate;
				ep.pParameter = 0;

				CAL_EventPost(s_hEventTest, &ep);
			}
			CyclicSupervisorOperations();
 			break;
		}
		case CH_EXIT_COMM:
		{
			DisableSupervisor();
			break;
		}
		case CH_EXIT_TASKS:
		{
			StopHardwareWatchdog();
			break;
		}
		case CH_EXIT3:
		{
			ExitPowerFail();
			ExitRunStopSwitch();
			ExitDisableOperations();
			UnregisterEventHandler();
			ExitServiceHandler();
			CAL_SchedUnregisterExternalEvent(s_hExternalEventTask);
			ExitLoginHandler();
			UnregisterSupervisor();
			break;
		}
		case CH_EXIT2:
		{
			DeleteEvents();
			break;
		}
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

/**
 * <description>OPTIONAL FUNCTION:
 *  Function to query about all implemented interfaces of our class. Only for C-Runtimes! C++ QueryInterface() is automatically generated in the .cpp file of your component.
 * </description>
 * <param name="pBase" type="IN">Pointer to IBase of our object</param> 
 * <param name="iid" type="IN">Interface id of the requested interface</param> 
 * <param name="pResult" type="OUT">Pointer to error code</param>  
 * <result>Return a pointer to the implemented interface</result>
 */
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
		CCmpTemplate *pC = (CCmpTemplate *)pBase;
		pC->EventCallback.pBase = pBase;
		pC->EventCallback.IEventCallback = EventCallback;
		pC->Base.iRefCount++;
		return &pC->EventCallback;
	}
	return NULL;
}
#endif


