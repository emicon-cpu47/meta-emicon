/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Template component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "IoDrvSoundDemoDep.h"
#include <mmsystem.h>

typedef struct
{
	IBase_C Base;
	ICmpIoDrv_C IoDrv;
	ICmpIoDrvParameter_C IoDrvParameter;
	IBase *pIBase;
	ICmpIoDrv *pIoDrv;
	ICmpIoDrvParameter *pIoDrvParameter;
	IoDrvInfo Info;
} IoDrvSoundDemo;

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

static IBase *s_pIBase, *s_pIBase2;
static unsigned char s_byIO[2][10];
static unsigned char *s_pSounds[40];

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
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvSoundDemo);
	return ERR_OK;
}

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
	if (cid == CLASSID_CIoDrvSoundDemo)
	{
		IoDrvSoundDemo *pIoDrvSoundDemo = (IoDrvSoundDemo *)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(IoDrvSoundDemo), NULL);
		if (pIoDrvSoundDemo != NULL)
		{
			IBase *pI = &pIoDrvSoundDemo->Base;
			pIoDrvSoundDemo->pIBase = &pIoDrvSoundDemo->Base;
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
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
	pIBase->iRefCount--;
	CAL_SysMemFreeData(COMPONENT_NAME, pIBase);
	return ERR_OK;
}

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
		IoDrvSoundDemo *pC = (IoDrvSoundDemo *)pBase;
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
		IoDrvSoundDemo *pC = (IoDrvSoundDemo *)pBase;
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
			RTS_HANDLE h = 0;
			void *pTmp;

			/* Example: Two cards found -> Create 2 instances */
			/* first instance */
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvSoundDemo, iInstance, &Result);
			s_pIBase = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase, NULL);

			iInstance++;

			/* second instance */
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvSoundDemo, iInstance, &Result);
			s_pIBase2 = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase2, NULL);
			break;
		}
		case CH_INIT3:
		{
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
		case CH_EXIT3:
		{
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
	IoDrvSoundDemo *pIoDrvSoundDemo;

	RTS_SETRESULT(pResult, ERR_OK);

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "IoDrvCreate ", 3);
	/* Only two instances allowed */
	if (iId > 1)
	{
		RTS_SETRESULT(pResult, ERR_NOMEMORY);
		return RTS_INVALID_HANDLE;
	}

	pIoDrvSoundDemo = (IoDrvSoundDemo *)hIIoDrv;
	pIoDrvSoundDemo->IoDrv.pBase = &pIoDrvSoundDemo->Base;
	pIoDrvSoundDemo->IoDrvParameter.pBase = &pIoDrvSoundDemo->Base;
	pInfo = &pIoDrvSoundDemo->Info;

	pInfo->wId = iId;
	pInfo->wModuleType = 40100;
	pInfo->hSpecific = (RTS_IEC_HANDLE)s_byIO[iId];
	pInfo->dwVersion = CMP_VERSION;

	strcpy(pInfo->szDriverName, "IoDrvSoundDemo");
	strcpy(pInfo->szDeviceName, "SoundCard");
	strcpy(pInfo->szVendorName, "Sound Company");
	strcpy(pInfo->szFirmwareVersion, "Rev. 1.0.0.0");
	return (RTS_HANDLE)pIoDrvSoundDemo;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
	IoDrvSoundDemo *pIoDrvSoundDemo = (IoDrvSoundDemo *)hIoDrv;
	CAL_SysMemFreeData(COMPONENT_NAME, pIoDrvSoundDemo);
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)
{
	IoDrvSoundDemo *pIoDrvSoundDemo = (IoDrvSoundDemo *)hIoDrv;

	if (ppInfo == NULL || hIoDrv == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	*ppInfo = (IoDrvInfo *)&pIoDrvSoundDemo->Info;
	return ERR_OK;
}



STATICITF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)
{
	IoConfigConnector *pConnector = CAL_IoMgrConfigGetFirstConnector(pConnectorList, &nCount, 40100);
	IoDrvSoundDemo *pIoDrvSoundDemo = (IoDrvSoundDemo *)hIoDrv;
	IBase *pIBase = pIoDrvSoundDemo->pIBase;
	ICmpIoDrv *pIIoDrv = pIoDrvSoundDemo->pIoDrv;
	int i;

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "UpdateConfiguration", 2);
	while (pConnector != NULL)
	{
		IoDrvInfo *pInfo;
		IoConfigParameter *pParameter;
		char *pszVendorName = NULL;
		char *pszDeviceName = NULL;
		char *pTestParameter = NULL;
		char *pszPathToSounds = NULL;
		char *pszSoundName = NULL;
		char pszTmpString[225];
		

		IoDrvGetInfo(hIoDrv, &pInfo);

		/* The connector type 40100 is not unique, so additional info must be investigated to detect our own device.
		   Here for example, two parameters with the vendorname and the devicename are used. */
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 10);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszVendorName = (char *)pParameter->dwValue;
		pParameter = CAL_IoMgrConfigGetParameter(pConnector, 20);
		if (pParameter != NULL && pParameter->dwFlags & PVF_POINTER)
			pszDeviceName = (char *)pParameter->dwValue;

		/* If the connector is still occupied by another driver instance, skip this connector */
		if (pConnector->hIoDrv == 0 &&
			pszVendorName != NULL && strcmp(pszVendorName, pInfo->szVendorName) == 0 &&
			pszDeviceName != NULL && strcmp(pszDeviceName, pInfo->szDeviceName) == 0)
		{
			/* Our driver instance must be registered at this connector to:
			- occupy this connector (that no other driver instance will use this connector)
			- to mark, that the conector is supported by a driver
			- for the IoMgr to be able to direct access the driver of this connector
			Always the pointer to the IBase interface must be written in the IO-driver handle of the connector! */
			pConnector->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* If the father is our input connector, you have to register the driver in this connector too
			to mark, that this connector is ours */
			if (pConnector->pFather != NULL && pConnector->pFather->wType == CT_PCI_MASTER)
				pConnector->pFather->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* Set the property, that bit consistency is provided by the driver! */
			CAL_IoMgrSetDriverProperties(pIBase, DRVPROP_CONSISTENCY);

			/* get the Parameter 50 that is the path to the sounds folder */
			pParameter = CAL_IoMgrConfigGetParameter(pConnector, 50);	
					if (pParameter != NULL)
						pszPathToSounds = (char*)pParameter->dwValue;

			/* get all the sound names from the paramter and add them to the s_pSound array */
				for(i = 0; i < 40; i++)
				{
					pParameter = CAL_IoMgrConfigGetParameter(pConnector, (10200 + i));	
					if (pParameter != NULL)
					{
						pszSoundName = (char*)pParameter->dwValue;
						strcpy(pszTmpString,pszPathToSounds);
						strcat(pszTmpString, pszSoundName);
						s_pSounds[i] = (unsigned char*) strdup(pszTmpString);
					}
				}

			pParameter = CAL_IoMgrConfigGetParameter(pConnector, 2000);	/* outputs */
			if (pParameter != NULL)
				pParameter->dwDriverSpecific = 0;	/* Device offset 0 */

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
		pConnector = CAL_IoMgrConfigGetNextConnector(pConnector, &nCount, 40100);
	}
	return ERR_OK;
}

			

STATICITF RTS_RESULT CDECL IoDrvUpdateMapping(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)
{
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "UpdateMapping ", 1);
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvReadInputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return ERR_OK;
}


/*
static RTS_RESULT HandleSoundAsync(IoConfigChannelMap *pChannelMap, char *pszSound)
{
	unsigned char *pbyIecAddress = pChannelMap->pbyIecAddress;
	unsigned short wSrcIndex = pChannelMap->wIecAddressBitOffset / 8;
	unsigned char bySrcValue;
	unsigned char bySrcMask = 1;
	unsigned char byDestMask = 1;

	byDestMask = (byDestMask << (pChannelMap->wParameterBitOffset % 8)); 
	bySrcMask = (bySrcMask << (pChannelMap->wIecAddressBitOffset % 8));
	bySrcValue = pbyIecAddress[wSrcIndex];

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Async soudn: %s", pszSound);

	if (bySrcValue & bySrcMask) 
	{
		if (((unsigned char)pChannelMap->dwDriverSpecific & byDestMask) == 0) 
		{
			(unsigned char)pChannelMap->dwDriverSpecific |= byDestMask;
			PlaySound(pszSound, NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
			return ERR_OK;
		}
	}
	else
	{
		if ((unsigned char)pChannelMap->dwDriverSpecific & byDestMask)
		{
			(unsigned char)pChannelMap->dwDriverSpecific &= ~byDestMask;
			PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
			return ERR_NOTINITIALIZED;
		}
	}
	return ERR_FAILED;
}

static RTS_RESULT HandleSoundSync(IoConfigChannelMap *pChannelMap, char *pszSound)
{
	unsigned char *pbyIecAddress = pChannelMap->pbyIecAddress;
	unsigned short wSrcIndex = pChannelMap->wIecAddressBitOffset / 8;
	unsigned char bySrcValue;
	unsigned char bySrcMask = 1;
	bySrcMask = (bySrcMask << (pChannelMap->wIecAddressBitOffset % 8));
	bySrcValue = pbyIecAddress[wSrcIndex];

	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Sync soudn: %s", pszSound);
	if (bySrcValue & bySrcMask)
	{
		PlaySound(pszSound, NULL, SND_SYNC);
		return ERR_OK;
	}
	return ERR_FAILED;
}

*/


STATICITF RTS_RESULT CDECL IoDrvWriteOutputs(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	int i;
	unsigned long j;
	int k;
	IoDrvSoundDemo *pIoDrvSoundDemo = (IoDrvSoundDemo *)hIoDrv;
	IoDrvInfo *pInfo = &pIoDrvSoundDemo->Info;
	unsigned short wBitOffset;

	if (pConnectorMapList == NULL)
		return ERR_PARAMETER;


	for (i=0; i<nCount; i++)
	{
		for (j=0; j<pConnectorMapList[i].dwNumOfChannels; j++)
		{
			
			if (pConnectorMapList[i].pChannelMapList[j].wSize == 1)
			{						
				unsigned char *pbyIecAddress = pConnectorMapList[i].pChannelMapList[j].pbyIecAddress;
				unsigned short wSrcIndex = pConnectorMapList[i].pChannelMapList[j].wIecAddressBitOffset / 8;
				unsigned char bySrcValue;
				unsigned char bySrcMask = 1;
				unsigned char byDestMask = 1;

				/* get the BitOffset from the Output channel */
				wBitOffset = pConnectorMapList[i].pChannelMapList[j].wParameterBitOffset;

				byDestMask = (byDestMask << (pConnectorMapList[i].pChannelMapList[j].wParameterBitOffset % 8)); // relativer offset
				bySrcMask = (bySrcMask << (pConnectorMapList[i].pChannelMapList[j].wIecAddressBitOffset % 8));
				bySrcValue = pbyIecAddress[wSrcIndex];


				if (bySrcValue & bySrcMask)
				{
					if (((unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific & byDestMask) == 0) // ein byte zum merken obs schon spielt
					{
						(unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific |= byDestMask;
						PlaySound((char*) s_pSounds[wBitOffset], NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
						return ERR_OK;
					}
				}
				else
				{
					if ((unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific & byDestMask)
					{
						(unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific &= ~byDestMask;
						PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
						return ERR_NOTINITIALIZED;
					}
				}
			}
					
			else if(pConnectorMapList[i].pChannelMapList[j].wSize == 8)
			{
				unsigned char *pbyIecAddress = pConnectorMapList[i].pChannelMapList[j].pbyIecAddress;
				unsigned short wSrcIndex = pConnectorMapList[i].pChannelMapList[j].wIecAddressBitOffset / 8;
				unsigned char bySrcValue;
				unsigned char bySrcMask = 1;
				unsigned char byDestMask = 1;

				bySrcValue = pbyIecAddress[wSrcIndex];

				for (k=0, wBitOffset = pConnectorMapList[i].pChannelMapList[j].wParameterBitOffset; k<pConnectorMapList[i].pChannelMapList[j].wSize; k++)
				{
					
					bySrcMask = (1 << k);
					if (bySrcValue & bySrcMask)
					{

						byDestMask = (1 << k);
						if (((unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific & byDestMask) == 0) // ein byte zum merken obs schon spielt
						{
							(unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific |= byDestMask;
							PlaySound((char*) s_pSounds[wBitOffset], NULL, SND_LOOP | SND_ASYNC | SND_FILENAME);
							return ERR_OK;
						}
					}
					else
					{
						byDestMask = (1 << k);
						if ((unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific & byDestMask)
						{
							(unsigned char)pConnectorMapList[i].pChannelMapList[j].dwDriverSpecific &= ~byDestMask;
							PlaySound(NULL, NULL, SND_LOOP | SND_ASYNC);
							return ERR_NOTINITIALIZED;
						}
					}
						wBitOffset++;
				}
			}
			else
			{
				
				unsigned short wIndex = (unsigned short)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific;
				unsigned short wSize = (pConnectorMapList[i].pChannelMapList[j].wSize / 8);
				unsigned char *pbyIecAddress = pConnectorMapList[i].pChannelMapList[j].pbyIecAddress;
				unsigned char *pbyDeviceAddress = (unsigned char *)pInfo->hSpecific;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "wIndex is: %d ", wIndex);
				memcpy(pbyDeviceAddress, pbyIecAddress, wSize);
				
				
			}
		}
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	if (pConnector->wType != 40100)
		return ERR_OK;
	return IoDrvGetModuleDiagnosis(hIoDrv, pConnector);
}

STATICITF RTS_RESULT CDECL IoDrvScanModules(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetModuleDiagnosis(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	/* Example for IO-error:
	IoDrvInfo *pInfo = (IoDrvInfo *)hIoDrv;
	if (IoError)
		IoMgrConfigSetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
	else
		IoMgrConfigResetDiagnosis(pConnector, CF_CONNECTOR_ERROR);
	*/
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

	switch (pParameter->dwParameterId)
	{
		case 4711:
		{
			if (pConnector->dwFlags & CF_CONNECTOR_DIAGNOSTIC_AVAILABLE)
			{
				RTS_RESULT Result;
				char *pszValue = (char *)CAL_IoMgrConfigGetParameterValuePointer(pParameter, &Result);
				if (pszValue != NULL && Result == ERR_OK)
					strcpy(pszValue, "**** Dies ist ein Diagnosetext! ****");
				if (pData != NULL)
					strncpy(pData, pszValue, MIN(strlen(pszValue) + 1, ulBitSize / 8));
				return ERR_OK;
			}
			break;
		}
		default:
			break;
	}
	return ERR_FAILED;
}

STATICITF RTS_RESULT CDECL IoDrvWriteParameter(RTS_HANDLE hDevice, IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	if (pParameter == NULL)
		return ERR_PARAMETER;

	switch (pParameter->dwParameterId)
	{
		case 4712:
		{
			IoConfigParameter *pParameterDiag;

			CAL_IoMgrConfigResetDiagnosis(pConnector, CF_CONNECTOR_DIAGNOSTIC_AVAILABLE);

			pParameterDiag = CAL_IoMgrConfigGetParameter(pConnector, 4711);
			if (pParameterDiag != NULL)
			{
				RTS_RESULT Result;
				char *pszValue = (char *)CAL_IoMgrConfigGetParameterValuePointer(pParameterDiag, &Result);
				if (pszValue != NULL && Result == ERR_OK)
					strcpy(pszValue, "");
			}
			return ERR_OK;
		}
		case 393220:
		{
			memcpy((void *)pParameter->dwValue, pData, ulBitSize / 8);
			return ERR_OK;
		}
		default:
			break;
	}
	return ERR_FAILED;
}
