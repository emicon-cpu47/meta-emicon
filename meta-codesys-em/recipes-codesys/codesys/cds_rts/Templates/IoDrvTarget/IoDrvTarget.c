/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Target component
*	Version:
*	Description:
******************************************************************************/
#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "CmpItf.h"
#include "IoDrvTargetDep.h"

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
} IoDrvTarget;

#ifndef CPLUSPLUS

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

#endif

static IBase *s_pIBase;

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

	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvTarget);
	return ERR_OK;
}

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CIoDrvTarget)
	{
		CIoDrvTarget *pCIoDrvTarget = static_cast<CIoDrvTarget *>(new CIoDrvTarget());
		IBase *pIBase = (IBase *)pCIoDrvTarget->QueryInterface((IBase *)(ICmpIoDrv*)pCIoDrvTarget, ITFID_ICmpIoDrv, pResult);
		RTS_SETRESULT(pResult, ERR_OK);
		return pIBase;
	}
#else
	if (cid == CLASSID_CIoDrvTarget)
	{
		IoDrvTarget *pIoDrvTarget = (IoDrvTarget *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvTarget), NULL);
		if (pIoDrvTarget != NULL)
		{
			IBase *pI = &pIoDrvTarget->Base;
			pIoDrvTarget->pIBase = &pIoDrvTarget->Base;
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

#ifndef CPLUSPLUS
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
		IoDrvTarget *pC = (IoDrvTarget *)pBase;
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
		pC->Base.iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pC->IoDrv;
	}
	if (iid == ITFID_ICmpIoDrvParameter)
	{
		IoDrvTarget *pC = (IoDrvTarget *)pBase;
		pC->IoDrvParameter.pBase = pBase;
		pC->IoDrvParameter.IIoDrvReadParameter = IoDrvReadParameter;
		pC->IoDrvParameter.IIoDrvWriteParameter = IoDrvWriteParameter;
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
			RTS_RESULT Result;
			RTS_HANDLE hIoDrv = 0;
			RTS_HANDLE h = 0;

			s_pIBase = (IBase *)CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvTarget, 0, &Result);
			CAL_IoMgrRegisterInstance(s_pIBase, NULL);
			break;
		}
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			break;

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT2:
		{
			/* Delete instance */
			ICmpIoDrv *pI;
			
			CAL_IoMgrUnregisterInstance(s_pIBase);
			pI = (ICmpIoDrv *)s_pIBase->QueryInterface(s_pIBase, ITFID_ICmpIoDrv, NULL);
			s_pIBase->Release(s_pIBase);
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
	IoDrvTarget *pIoDrvTarget;

	RTS_SETRESULT(pResult, ERR_OK);

	/* Only two instances allowed */
	if (iId > 1)
	{
		RTS_SETRESULT(pResult, ERR_NOMEMORY);
		return RTS_INVALID_HANDLE;
	}

#ifdef CPLUSPLUS
	pIoDrvTarget = (IoDrvTemplate *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvTemplate), NULL);
	pIoDrvTarget->pIBase = (IBase *)hIIoDrv;	
	pIoDrvTarget->pIoDrv = (ICmpIoDrv *)pIoDrvTarget->pIBase->QueryInterface(pIoDrvTarget->pIBase, ITFID_ICmpIoDrv, NULL);
	pIoDrvTarget->pIoDrvParameter = (ICmpIoDrvParameter *)pIoDrvTarget->pIBase->QueryInterface(pIoDrvTarget->pIBase, ITFID_ICmpIoDrvParameter, NULL);
	pIoDrvTarget->pIBase->Release(pIoDrvTarget->pIBase);
	pIoDrvTarget->pIBase->Release(pIoDrvTarget->pIBase);
	pInfo = &pIoDrvTarget->Info;
#else
	pIoDrvTarget = (IoDrvTarget *)hIIoDrv;
	pIoDrvTarget->IoDrv.pBase = &pIoDrvTarget->Base;
	pIoDrvTarget->IoDrvParameter.pBase = &pIoDrvTarget->Base;
	pInfo = &pIoDrvTarget->Info;
#endif

	pInfo->wId = (RTS_IEC_WORD)iId;
	pInfo->wModuleType = 40100;
	pInfo->hSpecific = 0;
	pInfo->dwVersion = CMP_VERSION;

	strcpy(pInfo->szDriverName, "IoDrvTarget");
	strcpy(pInfo->szDeviceName, "MyCard");
	strcpy(pInfo->szVendorName, "MyCompany");
	strcpy(pInfo->szFirmwareVersion, "Rev. 1.0.0.0");
	return (RTS_HANDLE)pIoDrvTarget;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
	IoDrvTarget *pIoDrvTarget = (IoDrvTarget *)hIoDrv;
	CAL_SysMemFreeData(COMPONENT_NAME, pIoDrvTarget);
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)
{
	IoDrvTarget *pIoDrvTarget = (IoDrvTarget *)hIoDrv;

	if (ppInfo == NULL || hIoDrv == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	*ppInfo = (IoDrvInfo *)&pIoDrvTarget->Info;
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)
{
	IoConfigConnector *pConnector = pConnectorList;	
	IoDrvTarget *pIoDrvTarget = (IoDrvTarget *)hIoDrv;
	IBase *pIBase = pIoDrvTarget->pIBase;

#if 0
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

		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393218);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszVendorName = (char *)pParameter->dwValue;
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393219);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszDeviceName = (char *)pParameter->dwValue;

		if (pConnector->hIoDrv == 0 &&
			pszVendorName != NULL && strcmp(pszVendorName, pInfo->szVendorName) == 0 &&
			pszDeviceName != NULL && strcmp(pszDeviceName, pInfo->szDeviceName) == 0)
		{
		/* Always the pointer to IBase must be used as the handle to the driver! */
		pConnector->hIoDrv = (RTS_IEC_DWORD)pIBase;

		/* If the father is our input connector, you have to register the driver in this connector too
		to mark, that this connector is ours */
		if (pConnector->pFather != NULL && pConnector->pFather->wType == CT_PCI_MASTER)
			pConnector->pFather->hIoDrv = (RTS_IEC_DWORD)pIBase;
		
		/* Child access (slaves) if available:  */
		pChild = CAL_IoMgrConfigGetFirstChild(pConnector, &nCount, pConnector);
		if (pChild != NULL)
		{
		}
		
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393220);	/* test parameter */
		if (pParameter != NULL)
		{
			if (pParameter->dwFlags & PVF_VALUE)
				ulTestParameter = pParameter->dwValue;
			else if (pParameter->dwFlags & PVF_POINTER)
				pTestParameter = (unsigned char *)pParameter->dwValue;
		}

		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 1000);	/* inputs */
		if (pParameter != NULL)
			pParameter->dwDriverSpecific = 0;	/* Device offset 0 */
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 2000);	/* outputs */
		if (pParameter != NULL)
			pParameter->dwDriverSpecific = 0;	/* Device offset 0 */
		break;
	}
		pConnector = CAL_IoMgrConfigGetNextConnector(pConnector, &nCount, 40100);
	}
#endif

#ifdef CPLUSPLUS
	pIBase->Release(pIBase);
#endif
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateMapping(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadInputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvScanModules(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetModuleDiagnosis(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
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

STATICITF RTS_RESULT CDECL IoDrvReadParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;
	
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;

	return ERR_OK;
}

