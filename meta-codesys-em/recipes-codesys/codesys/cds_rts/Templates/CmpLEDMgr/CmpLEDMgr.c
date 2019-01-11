/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Template component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpLEDMgrDep.h"

USE_STMT

/* LED STATES: Add your own states if wanted.*/
#define LED_NONE				0x00000000
#define LED_RUN					0x00000001
#define LED_STOP				0x00000002
#define	LED_ERROR				0x00000003
#define	LED_DIAG				0x00000004

/* Defines for LEDs, there are tree LEDs available: Add or remove our own defines.*/
#define LED_APP					0x00000001
#define LED_FB1					0x00000002
#define LED_FB2					0x00000003


static RTS_RESULT RefreshAppStateLED(unsigned long ulLED);
static RTS_RESULT RefreshBusStateLED(unsigned long ulLED,unsigned short wType);
static RTS_RESULT SetLEDState(unsigned long ulLED, unsigned long ulState);

#ifndef RTS_COMPACT_MICRO

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
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpLEDMgr);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpLEDMgr)
	{
		CCmpLEDMgr *pCCmpLEDMgr = static_cast<CCmpLEDMgr *>(new CCmpLEDMgr());
		return (IBase*)pCCmpLEDMgr->QueryInterface(pCCmpLEDMgr, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release();
	return ERR_OK;
#else
	return ERR_NOTIMPLEMENTED;
#endif
}

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
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
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
			break;
		case CH_INIT3:
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:

			/*Refresh the App State LEDs*/
			RefreshAppStateLED(LED_APP);

			/*Refresh you own fieldbuss LEDs*/
			RefreshBusStateLED(LED_FB1, CT_PROFIBUS_MASTER);
			RefreshBusStateLED(LED_FB2, CT_ETHERCAT_MASTER);

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
		{
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
#endif

		default:
			break;
	}
	return ERR_OK;
}

static RTS_RESULT RefreshAppStateLED(unsigned long ulLED)
{
	char szConfigApp[255];
	APPLICATION* pApp;
	unsigned long nMaxLen = 255;
	RTS_RESULT Result;
	
	/*Find Config Application*/
	Result = CAL_IoMgrGetConfigApplication(szConfigApp, &nMaxLen);
	if (Result != ERR_OK)
	{
		/* No Config Application, set Application NOT RUNNING */
		SetLEDState(ulLED, LED_NONE);
		return ERR_OK;
	}

	pApp = CAL_AppGetFirstApp(&Result);

	while (pApp != 0)
	{
		/*Look for Config App*/
		if (strcmp(pApp->szName, szConfigApp) == 0)
		{
			/*Config App found, set LED state*/
			if (pApp->ulState == AS_RUN)
				SetLEDState(ulLED, LED_RUN);
			else
				SetLEDState(ulLED, LED_STOP);

			return ERR_OK;
		}

		pApp = CAL_AppGetNextApp(pApp,&Result);
	}

	/*No config Application found, set Application NOT RUNNING*/
	SetLEDState(ulLED, LED_NONE);
	return ERR_OK;
}

static RTS_RESULT RefreshBusStateLED(unsigned long ulLED, unsigned short wType)
{
	RTS_RESULT Result;
	IoConfigConnector* pConnectorList;
	IoConfigConnector* pConnector;
	int nCount;

	Result = CAL_IoMgrConfigGetConnectorList(&pConnectorList, &nCount);
	if ((Result != ERR_OK) || (pConnectorList == 0))
	{
		/*No IoConfiguration available*/
		SetLEDState(ulLED, LED_NONE);
		return ERR_OK;
	}

	pConnector = CAL_IoMgrConfigGetFirstConnector(pConnectorList, &nCount, wType);
	if (pConnector)
	{
		/*Fieldbuss Master found, set LEDs*/
		if (((pConnector->dwFlags & CF_CONNECTOR_CONFIGURED) != CF_CONNECTOR_CONFIGURED) ||
			((pConnector->dwFlags & CF_CONNECTOR_ERROR) == CF_CONNECTOR_ERROR) ||
			((pConnector->dwFlags & CF_CONNECTOR_BUS_ERROR) == CF_CONNECTOR_BUS_ERROR))
			SetLEDState(ulLED, LED_ERROR);
		else if ((pConnector->dwFlags & CF_CONNECTOR_ACTIVE) != CF_CONNECTOR_ACTIVE)
			SetLEDState(ulLED, LED_STOP);
		else if ((pConnector->dwFlags & CF_CONNECTOR_DIAGNOSTIC_AVAILABLE) == CF_CONNECTOR_DIAGNOSTIC_AVAILABLE)
			SetLEDState(ulLED, LED_DIAG);
		else if ((pConnector->dwFlags & CF_CONNECTOR_ACTIVE) == CF_CONNECTOR_ACTIVE)
			SetLEDState(ulLED, LED_RUN);
		else
			SetLEDState(ulLED, LED_NONE);
	}

	/*No fieldbuss master found, set State NOT RUNNING*/
	SetLEDState(ulLED, LED_NONE);
	return ERR_OK;
}

static RTS_RESULT SetLEDState(unsigned long ulLED, unsigned long ulState)
{
	/*This must be implemented by the OEM*/
	switch (ulState)
	{		
		case LED_NONE:
		{
			/*Todo: Set ulLED LED to State NONE*/
			break;
		}
		case LED_RUN:
		{
			break;
		}
		case LED_STOP:
		{
			break;
		}
		case LED_ERROR:
		{
			break;
		}
		case LED_DIAG:
		{
			break;
		}
		default:
			break;
	}			
	
	return ERR_OK;
}
