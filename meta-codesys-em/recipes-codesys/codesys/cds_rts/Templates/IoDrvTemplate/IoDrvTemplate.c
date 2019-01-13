/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Template component
*	Version:
*	Description:
******************************************************************************/

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "IoDrvTemplateDep.h"

#define IODRV_TEMPLATE_MODULE_TYPE		CT_OEM_START

typedef struct
{
#ifndef CPLUSPLUS
	IBase_C Base;
	ICmpIoDrv_C IoDrv;
	ICmpIoDrvParameter_C IoDrvParameter;
#endif
	IBase *pIBase;
	ICmpIoDrv *pIoDrv;
	ICmpIoDrvParameter *pIoDrvParameter;
	IoDrvInfo Info;
	IoConfigConnector *pConnector;
} IoDrvTemplate;

#ifndef CPLUSPLUS

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

#endif

#ifndef CMPEVENTMGR_NOTIMPLEMENTED
static RTS_HANDLE s_hEventDownloadDone = RTS_INVALID_HANDLE;
#endif

static IBase *s_pIBase = NULL, *s_pIBase2 = NULL;

/* Our Fake I/O Area */
#define MAX_CHANNELS	128
#define MAX_DRIVERS		2
static RTS_UI32 s_abyIO[MAX_DRIVERS][MAX_CHANNELS];
static RTS_UI32 s_ulLastDiagnosis = 0;

#ifndef CMPEVENTMGR_NOTIMPLEMENTED
/* Example: Use of the Event Interface */
static void CDECL TemplateEventCallback(EventParam *pEventParam);
#endif

/* Macro to define function pointers of import functions */
USE_STMT

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

#ifdef CPLUSPLUS
	INIT_LOCALS_STMT;
	s_pIBase = NULL;
	s_pIBase2 = NULL;
#endif

	if (pInitStruct->pfCMRegisterClass != NULL)
	{
		RTS_HANDLE hClass = pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvTemplate);
		if (hClass == RTS_INVALID_HANDLE)
			return ERR_FAILED;
	}
	return ERR_OK;
}
#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CIoDrvTemplate)
	{
		CIoDrvTemplate *pCIoDrvTemplate = static_cast<CIoDrvTemplate *>(new CIoDrvTemplate());
		IBase *pIBase = (IBase *)pCIoDrvTemplate->QueryInterface((IBase *)(ICmpIoDrv*)pCIoDrvTemplate, ITFID_ICmpIoDrv, pResult);
		RTS_SETRESULT(pResult, ERR_OK);
		return pIBase;
	}
#else
	if (cid == CLASSID_CIoDrvTemplate)
	{
		IoDrvTemplate *pIoDrvTemplate = (IoDrvTemplate *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvTemplate), NULL);
		if (pIoDrvTemplate != NULL)
		{
			IBase *pI = &pIoDrvTemplate->Base;
			pIoDrvTemplate->pIBase = &pIoDrvTemplate->Base;
			pI->bIEC = 0;
			pI->AddRef = AddRef;
			pI->Release = Release;
			pI->QueryInterface = QueryInterface;
			pI->iRefCount++;
			RTS_SETRESULT(pResult, ERR_OK);
			return pI;
		}
		else
		{
			RTS_SETRESULT(pResult, ERR_NOMEMORY);
			return NULL;
		}
	}
#endif
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release(pIBase);
	return ERR_OK;
#else
	pIBase->iRefCount--;
	CAL_SysMemFreeData(COMPONENT_NAME, pIBase);
	return ERR_OK;
#endif
}

#if !defined(CPLUSPLUS)
IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer ro the IBase interface. So it doesn't matter, which interface
		   is used to get the IBase pointer */
		ICmpIoDrv *pI = (ICmpIoDrv *)pBase;
		pI->pBase->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pI->pBase;
	}
	if (iid == ITFID_ICmpIoDrv)
	{
		IoDrvTemplate *pC = (IoDrvTemplate *)pBase;
		pC->IoDrv.pBase = pBase;
		pC->IoDrv.IIoDrvCreate = IoDrvCreate;
		pC->IoDrv.IIoDrvDelete = IoDrvDelete;
		pC->IoDrv.IIoDrvGetInfo = IoDrvGetInfo;
		pC->IoDrv.IIoDrvUpdateConfiguration = IoDrvUpdateConfiguration;
		pC->IoDrv.IIoDrvUpdateMapping = IoDrvUpdateMapping;
		pC->IoDrv.IIoDrvReadInputs = IoDrvReadInputs;
		pC->IoDrv.IIoDrvWriteOutputs = IoDrvWriteOutputs;
		pC->IoDrv.IIoDrvStartBusCycle = IoDrvStartBusCycle;
		pC->IoDrv.IIoDrvScanModules = IoDrvScanModules;
		pC->IoDrv.IIoDrvGetModuleDiagnosis = IoDrvGetModuleDiagnosis;
		pC->pIoDrv = &pC->IoDrv;
		pC->Base.iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pC->IoDrv;
	}
	if (iid == ITFID_ICmpIoDrvParameter)
	{
		IoDrvTemplate *pC = (IoDrvTemplate *)pBase;
		pC->IoDrvParameter.pBase = pBase;
		pC->IoDrvParameter.IIoDrvReadParameter = IoDrvReadParameter;
		pC->IoDrvParameter.IIoDrvWriteParameter = IoDrvWriteParameter;
		pC->pIoDrvParameter = &pC->IoDrvParameter;
		pC->Base.iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pC->IoDrvParameter;
	}
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}
#endif


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
			break;
		case CH_INIT2:
		{
			int iInstance = 0;
			RTS_RESULT Result;
			RTS_HANDLE hIoDrv = 0;
			void *pTmp;

			/* Example: Two cards found -> Create 2 instances */
			/* first instance */
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvTemplate, iInstance, &Result);
			s_pIBase = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase, NULL);
			
			iInstance++;

			/* second instance */
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvTemplate, iInstance, &Result);
			s_pIBase2 = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase2, NULL);
			break;
		}
		case CH_INIT3:
		{
#ifndef CMPEVENTMGR_NOTIMPLEMENTED
			/* Example: Use of the Event Interface */
			/* Register an event callback function */
			s_hEventDownloadDone = CAL_EventOpen(EVT_DownloadDone, CMPID_CmpApp, NULL);
			CAL_EventRegisterCallbackFunction(s_hEventDownloadDone , TemplateEventCallback, 0);
#endif
			break;
		}
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
#ifdef RTS_COMPACT_MICRO
			return ERR_NO_COMM_CYCLE;
#else
			break;
#endif

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
		{
#ifndef CMPEVENTMGR_NOTIMPLEMENTED
			CAL_EventUnregisterCallbackFunction(s_hEventDownloadDone, TemplateEventCallback);
			CAL_EventClose(s_hEventDownloadDone);
			s_hEventDownloadDone = RTS_INVALID_HANDLE;
#endif
			break;
		}
		case CH_EXIT2:
		{
			/* Delete both instances */
			ICmpIoDrv *pI;
			
			CAL_IoMgrUnregisterInstance(s_pIBase);
			pI = (ICmpIoDrv *)s_pIBase->QueryInterface(s_pIBase, ITFID_ICmpIoDrv, NULL);
			s_pIBase->Release(s_pIBase);
			CAL_IoDrvDelete((RTS_HANDLE)pI, (RTS_HANDLE)pI);
			
			CAL_IoMgrUnregisterInstance(s_pIBase2);
			pI = (ICmpIoDrv *)s_pIBase2->QueryInterface(s_pIBase2, ITFID_ICmpIoDrv, NULL);
			s_pIBase2->Release(s_pIBase2);
			CAL_IoDrvDelete((RTS_HANDLE)pI, (RTS_HANDLE)pI);
			break;
		}
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

STATICITF RTS_HANDLE CDECL IoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{

	IoDrvInfo *pInfo;
	IoDrvTemplate *pIoDrvTemplate;

	RTS_SETRESULT(pResult, ERR_OK);

	/* Only two instances allowed */
	if (iId >= MAX_DRIVERS)
	{
		RTS_SETRESULT(pResult, ERR_NOMEMORY);
		return RTS_INVALID_HANDLE;
	}

#ifdef CPLUSPLUS
	pIoDrvTemplate = (IoDrvTemplate *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvTemplate), NULL);
	pIoDrvTemplate->pIBase = (IBase *)hIIoDrv;	
	pIoDrvTemplate->pIoDrv = (ICmpIoDrv *)pIoDrvTemplate->pIBase->QueryInterface(pIoDrvTemplate->pIBase, ITFID_ICmpIoDrv, NULL);
	pIoDrvTemplate->pIoDrvParameter = (ICmpIoDrvParameter *)pIoDrvTemplate->pIBase->QueryInterface(pIoDrvTemplate->pIBase, ITFID_ICmpIoDrvParameter, NULL);
	pIoDrvTemplate->pIBase->Release(pIoDrvTemplate->pIBase);
	pIoDrvTemplate->pIBase->Release(pIoDrvTemplate->pIBase);
	pInfo = &pIoDrvTemplate->Info;
#else
	pIoDrvTemplate = (IoDrvTemplate *)hIIoDrv;
	pIoDrvTemplate->IoDrv.pBase = &pIoDrvTemplate->Base;
	pIoDrvTemplate->IoDrvParameter.pBase = &pIoDrvTemplate->Base;
	pInfo = &pIoDrvTemplate->Info;
#endif

	pInfo->wId = (RTS_IEC_WORD)iId;
	pInfo->wModuleType = IODRV_TEMPLATE_MODULE_TYPE;
	pInfo->hSpecific = (RTS_IEC_HANDLE)s_abyIO[iId];
	pInfo->dwVersion = CMP_VERSION;

	strcpy(pInfo->szDriverName, "IoDrvTemplate");
	strcpy(pInfo->szDeviceName, "MyCard");
	strcpy(pInfo->szVendorName, "MyCompany");
	strcpy(pInfo->szFirmwareVersion, "Rev. 1.0.0.0");
	return (RTS_HANDLE)pIoDrvTemplate;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
#ifdef CPLUSPLUS
	IoDrvTemplate *pIoDrvTemplate = (IoDrvTemplate *)hIoDrv;
	CAL_SysMemFreeData(COMPONENT_NAME, pIoDrvTemplate);
#endif
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)
{
	IoDrvTemplate *pIoDrvTemplate = (IoDrvTemplate *)hIoDrv;

	if (ppInfo == NULL || hIoDrv == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	*ppInfo = (IoDrvInfo *)&pIoDrvTemplate->Info;
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)
{
	IoConfigConnector *pConnector = CAL_IoMgrConfigGetFirstConnector(pConnectorList, &nCount, IODRV_TEMPLATE_MODULE_TYPE);
	IoDrvTemplate *pIoDrvTemplate = (IoDrvTemplate *)hIoDrv;
	IBase *pIBase = pIoDrvTemplate->pIBase;

	if (pConnectorList == NULL)
		pIoDrvTemplate->pConnector = NULL;

	while (pConnector != NULL)
	{
		IoDrvInfo *pInfo;
		IoConfigParameter *pParameter;
		IoConfigConnector *pChild;
		char *pszVendorName = NULL;
		char *pszDeviceName = NULL;
		unsigned char *pTestParameter;
		unsigned long ulTestParameter;

		IoDrvGetInfo(hIoDrv, &pInfo);

		/* The connector type IODRV_TEMPLATE_MODULE_TYPE is not unique, so additional info must be investigated to detect our own device.
		   Here for example, two parameters with the vendorname and the devicename are used. */
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393218);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszVendorName = (char *)pParameter->dwValue;
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393219);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszDeviceName = (char *)pParameter->dwValue;

		/* If the connector is still occupied by another driver instance, skip this connector */
		if (pConnector->hIoDrv == 0 &&
			pszVendorName != NULL && strcmp(pszVendorName, pInfo->szVendorName) == 0 &&
			pszDeviceName != NULL && strcmp(pszDeviceName, pInfo->szDeviceName) == 0)
		{
			int i;

			/* Our driver instance must be registered at this connector to:
			- occupy this connector (that no other driver instance will use this connector)
			- to mark, that the conector is supported by a driver
			- for the IoMgr to be able to direct access the driver of this connector
			Always the pointer to the IBase interface must be written in the IO-driver handle of the connector! */
			pConnector->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* This is our main connector. Store it for later usage in driver instance. */
			pIoDrvTemplate->pConnector = pConnector;

			/* If the father is our input connector, you have to register the driver in this connector too
			to mark, that this connector is ours */
			if (pConnector->pFather != NULL && pConnector->pFather->wType == CT_PCI_MASTER)
				pConnector->pFather->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* Set the property, that bit consistency is provided by the driver! */
			s_ulLastDiagnosis = CAL_SysTimeGetMs();
			CAL_IoMgrSetDriverProperties(pIBase, DRVPROP_CONSISTENCY | DRVPROP_BACKGROUND_GETDIAG);
			
			/* If the connector has childs, they can be handled here */
			pChild = CAL_IoMgrConfigGetFirstChild(pConnector, &nCount, pConnector);
			while (pChild != NULL)
			{
				/* With this code you can go through all child connectors of the father pConnector */

				/* Example: This is the access to a parameter of the child connector */
				pParameter = CAL_IoMgrConfigGetParameter(pChild, 4711);
				
				pChild = CAL_IoMgrConfigGetNextChild(pChild, &nCount, pConnector);
			}
			
			pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393220);	/* test parameter */
			if (pParameter != NULL)
			{
				if (pParameter->dwFlags & PVF_VALUE)
					ulTestParameter = CAL_IoMgrConfigGetParameterValueDword(pParameter, NULL);
				else if (pParameter->dwFlags & PVF_POINTER)
					pTestParameter = (unsigned char*)CAL_IoMgrConfigGetParameterValuePointer(pParameter, NULL);
			}

			
			/* Inputs and outputs are mapped to the same region */
			for(i=0; i < MAX_CHANNELS; i++)
			{
				pParameter = CAL_IoMgrConfigGetParameter(pConnector, 1000 + i);

				if (pParameter != NULL)
				{
					pParameter->dwDriverSpecific = (RTS_IEC_BYTE *) &s_abyIO[pIoDrvTemplate->Info.wId][i];
				}
				else
					break;
			}		
			/* Outputs */
			for(i=0; i < MAX_CHANNELS; i++)
			{
				pParameter = CAL_IoMgrConfigGetParameter(pConnector, 2000 + i);

				if (pParameter != NULL)
				{
					pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_abyIO[pIoDrvTemplate->Info.wId][i];
				}
				else
					break;
			}

			/* The diagnosis bits are set here to mark, that everything is OK
			   or an error occurred on this connector (in this case set the corresponding error flags
			   or remove some valid flags).
			   */
			CAL_IoMgrConfigSetDiagnosis(pConnector, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
			if (pConnector->pFather != NULL)
				CAL_IoMgrConfigSetDiagnosis(pConnector->pFather, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);

			/* If a very serious error occurred during IoDrvUpdateConfiguration, the driver can return ERR_EXCEPTION
			   to generate an exception on the corresponding IO-application:
			   return ERR_EXCEPTION; */

			/* If an error occurred during IoDrvUpdateConfiguration, the driver can return ERR_FAILED
			   to generate a logger entry on the corresponding IO-application with the error code.
			   But this has no further consequence:
			   return ERR_FAILED; */
			break;
		}
		pConnector = CAL_IoMgrConfigGetNextConnector(pConnector, &nCount, IODRV_TEMPLATE_MODULE_TYPE);
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateMapping(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadInputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	int i;
	unsigned long j;

	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;

	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{
			CAL_IoMgrCopyInputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
		}
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	int i;
	unsigned long j;

	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;

	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{
			CAL_IoMgrCopyOutputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
		}
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	if (pConnector->wType != IODRV_TEMPLATE_MODULE_TYPE)
		return ERR_OK;

	/* Update diagnostic information at least every 4 seconds, if it is not supported by the backgground diagnostic task */
	if ((CAL_SysTimeGetMs() - s_ulLastDiagnosis) > 4000)
		return IoDrvGetModuleDiagnosis(hIoDrv, pConnector);
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvScanModules(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetModuleDiagnosis(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	IoConfigParameter *pParameter;

	if (pConnector == NULL)
	{
		IoDrvTemplate *pIoDrvTemplate = (IoDrvTemplate *)hIoDrv;
		pConnector = pIoDrvTemplate->pConnector;
	}

	if (pConnector == NULL)
		return ERR_PARAMETER;

	pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393221);
	if (pParameter != NULL)
	{
		RTS_I16 sChangeStatus = *(RTS_I16 *)pParameter->dwValue;

		if (sChangeStatus)
		{
			/* Example for IO-error: */
			CAL_IoMgrConfigSetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
		}
		else
			CAL_IoMgrConfigResetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
	}
	s_ulLastDiagnosis = CAL_SysTimeGetMs();
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvIdentify(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWatchdogTrigger(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadParameter(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;
	
	memcpy(pData, (unsigned char *)pParameter->dwValue, ulBitSize / 8);
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;

	memcpy((unsigned char *)pParameter->dwValue, pData, ulBitSize / 8);
	return ERR_OK;
}

/* Callback function for slot */
static void CDECL BeforeTaskCycle(struct tagTask_Desc *pTask) 
{ 
        static unsigned long cycle_count; 

        cycle_count++; 
} 

#ifndef CMPEVENTMGR_NOTIMPLEMENTED

/* Callback function for event */
void CDECL TemplateEventCallback(EventParam *pEventParam)
{
	switch(pEventParam->EventId)
	{
		case EVT_DownloadDone:
		{
			/* Called when an application was downloaded or a bootproject was loaded */
			if (pEventParam->usParamId == EVTPARAMID_CmpApp &&
				pEventParam->usVersion == EVTVERSION_CmpApp)
			{
				EVTPARAM_CmpApp *p = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				APPLICATION* pAppl = (APPLICATION*)p->pApp;

				if (pAppl)
				{
					/* Register a slot callback function to all tasks of the application.
					Note that some slots are used by the system (see CmpIecTaskItf.m4):
						#define SLOT_READ_INPUTS			15000
						#define SLOT_AFTER_READ_INPUTS		22500
						#define SLOT_IEC_CODE				30000
						#define SLOT_BEFORE_WRITE_INPUTS	37500
						#define SLOT_WRITE_OUTPUTS			45000
					*/
			        CAL_IecTaskRegisterSlotCallbacks(pAppl, 10000, BeforeTaskCycle, FALSE); 
					/* Test of a log output */
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Event received: Application <%s> loaded\n", pAppl->szName);
				}
			}
			break;
		}
		default:
			break;
	}
}

#endif

