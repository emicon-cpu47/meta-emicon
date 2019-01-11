/**
 * <name>IoDrvSubModulesFix.c</name>
 * <description> 
 *	Very simple example of an IO driver.
 *	This example consists of an device description and a corresponding IO driver component.
 *	The device of the device description can be added to a Control Win V3 soft plc device. It has a connector with one parameter, 2 input channels and 2 output channels.
 *	The corresponding IO driver component performs the basic functions of an IO driver:
 *  - At startup, creating an instance of the driver and registering the instance at the IO manager
 *  - At download, registering the instance at the connector and adding driver specific information to the channels
 *  - At task start, updating the inputs
 *  - At task end, updaing the outputs
 *
 *	More examples about IO drivers can be found in IoDrvSimple and IoDrvTemplate.
 *
 *	Implements the IO driver interface	
 *	- IoDrvCreate
 *	- IoDrvDelete
 *	- IoDrvGetInfo
 *	- IoDrvGetModuleDiagnosis
 *	- IoDrvIdentify
 *	- IoDrvReadInputs
 *	- IoDrvScanModules
 *	- IoDrvStartBusCycle	
 *	- IoDrvUpdateConfiguration
 *	- IoDrvUpdateMapping
 *	- IoDrvWatchdogTrigger
 *	- IoDrvWriteOutputs
 *
 *	USAGE:
 * 
 *	Install the device description to the CODESYS device repository and use "Add Device" command to add the device "IoDrvSubModulesFix" to your top level device (PLC).
 *	Add some channel mappings and use them in your IEC program.
 *	Compile the driver component and add to your runtime configuration. Download the application to test the driver.
 *
 *	This example driver uses static memory (s_ulyInputs and s_ulyOutputs) to simulate a physical input and output area.
 *	In IoDrvStartBusCycle, the example driver copies outputs to inputs, simulating outputs connected to inputs with a cable.
 *	In your real driver, adapt the code for reading inputs and writing outputs, and remove the copy-code in IoDrvStartBusCycle.
 *
 *	</description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright> 
 */
#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "IoDrvSubModulesFixDep.h"

USE_STMT

typedef struct
{
	IBase_C Base;
	ICmpIoDrv_C IoDrv;
	IBase *pIBase;
	ICmpIoDrv *pIoDrv;
	IoDrvInfo Info;
} IoDrvSubModulesFix;

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

static IBase *s_pIBase;

/* Our one and only instance of the driver */
static IoDrvSubModulesFix s_IoDrvSubModulesFix;

#ifndef RTS_COMPACT_MICRO

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
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CIoDrvSubModulesFix);

	return ERR_OK;
}

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
	if (cid == CLASSID_CIoDrvSubModulesFix)
	{
		IoDrvSubModulesFix *pIoDrvSubModulesFix = &s_IoDrvSubModulesFix;
		IBase *pI = &pIoDrvSubModulesFix->Base;
		pIoDrvSubModulesFix->pIBase = &pIoDrvSubModulesFix->Base;
		pI->bIEC = 0;
		pI->AddRef = AddRef;
		pI->Release = Release;
		pI->QueryInterface = QueryInterface;
		pI->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pI;
	}
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
	pIBase->iRefCount--;
	return ERR_OK;
}

IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer to the IBase interface. So it doesn't matter, which interface
		   is used to get the IBase pointer */
		ICmpIoDrv *pI = (ICmpIoDrv *)pBase;
		pI->pBase->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pI->pBase;
	}
	if (iid == ITFID_ICmpIoDrv)
	{
		IoDrvSubModulesFix *pC = (IoDrvSubModulesFix *)pBase;
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
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Publish exported functions to the component manager, to make them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Import function pointers from other components. Use generated macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
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
 * <description>Example for a Hook function. Register and unregister driver instance here.</description>
 * <result></result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
		{
			RTS_HANDLE hIoDrv = 0;
			void *pTmp;

			/* first instance */
			pTmp = CAL_IoDrvCreate(hIoDrv, CLASSID_CIoDrvSubModulesFix, 0, NULL);
			s_pIBase = (IBase *)pTmp;
			CAL_IoMgrRegisterInstance(s_pIBase, NULL);

			break;
		}		
		case CH_INIT3:
			break;
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
			break;
		case CH_EXIT2:
		{
			/* Delete instance */
			ICmpIoDrv *pI;
			
			CAL_IoMgrUnregisterInstance(s_pIBase);
			pI = (ICmpIoDrv *)s_pIBase->QueryInterface(s_pIBase, ITFID_ICmpIoDrv, NULL);
			s_pIBase->Release(s_pIBase);
			CAL_IoDrvDelete((RTS_HANDLE)pI, (RTS_HANDLE)pI);
			DeleteInstance(s_pIBase);
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

/**
 * Implementation of the IoDrv Interface
 */
/* Our dummy I/O area. */
#define MAX_CHANNELS 2
static unsigned long s_ulyInputs[MAX_CHANNELS];
static unsigned long s_ulyOutputs[MAX_CHANNELS];

STATICITF RTS_HANDLE CDECL IoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	IoDrvInfo *pInfo;
	IoDrvSubModulesFix *pIoDrvSubModulesFix;

	RTS_SETRESULT(pResult, ERR_OK);

	/* Only one instance allowed */
	if (iId > 0) {
		RTS_SETRESULT(pResult, ERR_NOMEMORY);
		return RTS_INVALID_HANDLE;
	}

	pIoDrvSubModulesFix = (IoDrvSubModulesFix *)hIIoDrv;
	pIoDrvSubModulesFix->IoDrv.pBase = &pIoDrvSubModulesFix->Base;
	pInfo = &pIoDrvSubModulesFix->Info;

	pInfo->wId = (RTS_IEC_WORD)iId;
	pInfo->wModuleType = 40100;
	pInfo->hSpecific = (RTS_IEC_HANDLE)s_ulyInputs[iId];
	pInfo->dwVersion = CMP_VERSION;

	strcpy(pInfo->szDriverName, "IoDrvSubModulesFix");
	strcpy(pInfo->szDeviceName, "ModuleIoDrvSubModulesFix");
	strcpy(pInfo->szVendorName, "MyCompany");
	strcpy(pInfo->szFirmwareVersion, "Rev. 3.5.9.0");

	/* Return value will be stored in CmpIoManager, and used in calls to IoDrvUpdateConfiguration, IoDrvUpdateMapping, IoDrvReadInputs, IoDrvWriteOutputs */
	return (RTS_HANDLE)pIoDrvSubModulesFix;
}

STATICITF RTS_RESULT CDECL IoDrvDelete(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)
{
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvGetInfo(RTS_HANDLE hIoDrv, IoDrvInfo **ppInfo)
{
	if (ppInfo == NULL || hIoDrv == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	*ppInfo = (IoDrvInfo *)hIoDrv;
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvUpdateConfiguration(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)
{
/* Find connector with moduleType="40100" as defined in device desciption file:
 * <Connector moduleType="40100" interface="MyCompany:FixConnectorInterface" role="parent" explicit="false" connectorId="2" hostpath="1">
 *
 * This is the connector structure as defined in the device desciption file:
 * (child 257) Module IoDrvSubModulesFix (parent 40100)
 *	                (child 40105) Module SubModuleAsLocalModule (parent 40102)
 *	                (child 40107) Module SubModuleAsDeviceIdentification (parent 33025)
 *
*/
	int nCountBase = nCount;
	int nCountWork = 0;

	IoConfigConnector *pConnector = CAL_IoMgrConfigGetFirstConnector(pConnectorList, &nCount, 40100);
	IoDrvSubModulesFix *pIoDrvSubModulesFix = (IoDrvSubModulesFix *)(hIoDrv); /* hIoDrv as returned from IoDrvCreate */
	IBase *pIBase = pIoDrvSubModulesFix->pIBase;
	/*ICmpIoDrv *pIIoDrv = pIoDrvSubModulesFix->pIoDrv;*/

	if (pConnectorList == NULL)
	{
		/* Called with this parameter before download if another application is already running, and on shutdown */
		/* Free Resources */
		return ERR_OK;
	}

	if (pConnector != NULL)
	{
		IoDrvInfo *pInfo;
		IoConfigParameter *pParameter;
		IoConfigConnector *pChild;
		IoConfigConnector *pChildChild;
		unsigned char *pTestParameter;

		IoDrvGetInfo(hIoDrv, &pInfo);

		/* If the connector is still occupied by another driver instance, skip this connector */
		if (pConnector->hIoDrv == 0)
		{
			int i;

			/* Our driver instance must be registered at this connector to:
			- occupy this connector (that no other driver instance will use this connector)
			- to mark, that the conector is supported by a driver
			- for the IoMgr to be able to direct access the driver of this connector
			Always the pointer to the IBase interface must be written in the IO-driver handle of the connector! */
			pConnector->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* If the father is our input connector, you have to register the driver in this connector too
			to mark, that this connector is ours */
			if (pConnector->pFather != NULL && pConnector->pFather->wType == CT_PCI_SLAVE)
				/* pConnector->pFather has module type 257 */
				pConnector->pFather->hIoDrv = (RTS_IEC_HANDLE)pIBase;

			/* Set the property, that bit consistency is provided by the driver! */
			CAL_IoMgrSetDriverProperties(pIBase, DRVPROP_CONSISTENCY);

			/* If the connector has childs, they can be handled here */
			/* pChild has connector type 40105 for first child, 40107 for second child */
			pChild = CAL_IoMgrConfigGetFirstChild(pConnector, &nCount, pConnector);
			while (pChild != NULL)
			{
				/* With this code you can go through all child connectors of the father pConnector */

				/* Example: This is the access to a parameter of the child connector */
				/* Will be NULL because in the devdesc, no parameter is defined for this connector */
				pParameter = CAL_IoMgrConfigGetParameter(pChild, 4711);

				nCountWork = nCountBase;
				/* pChildChild has connector type 40102, resp 33025 */
				pChildChild = CAL_IoMgrConfigGetFirstChild(pConnectorList, &nCountWork, pChild);

				/* This is the first fixed submodule */
				if (pChildChild->wType == 40102)
				{
					/* Input channels */
					for(i=0; i < MAX_CHANNELS; i++)
					{
						pParameter = CAL_IoMgrConfigGetParameter(pChildChild, 1000 + i);
						if (pParameter != NULL) {
							pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyInputs[i];
						}
						else
							break;
					}

					/* Our driver instance must be registered at this connector */
					pChild->hIoDrv = (RTS_IEC_HANDLE)pIBase;
					pChildChild->hIoDrv = (RTS_IEC_HANDLE)pIBase;
					/* The diagnosis bits are set here to mark, that everything is OK
					   or an error occurred on this connector (in this case set the corresponding error flags
					   or remove some valid flags).
					   */
					CAL_IoMgrConfigSetDiagnosis(pChild, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
					CAL_IoMgrConfigSetDiagnosis(pChildChild, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
				}
			
				/* This is the second fixed submodule */
				if (pChildChild->wType == 33025)
				{
					/* Output channels */
					for(i=0; i < MAX_CHANNELS; i++)
					{
						pParameter = CAL_IoMgrConfigGetParameter(pChildChild, 1000 + i);
						if (pParameter != NULL)
							pParameter->dwDriverSpecific = (RTS_IEC_BYTE *)&s_ulyOutputs[i];
						else
							break;
					}

					/* Our driver instance must be registered at this connector */
					pChild->hIoDrv = (RTS_IEC_HANDLE)pIBase;
					pChildChild->hIoDrv = (RTS_IEC_HANDLE)pIBase;
					/* The diagnosis bits are set here to mark, that everything is OK
					   or an error occurred on this connector (in this case set the corresponding error flags
					   or remove some valid flags).
					   */
					CAL_IoMgrConfigSetDiagnosis(pChild, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
					CAL_IoMgrConfigSetDiagnosis(pChildChild, CF_DRIVER_AVAILABLE | CF_CONNECTOR_FOUND | CF_CONNECTOR_CONFIGURED | CF_CONNECTOR_ACTIVE);
				}
								
				pChild = CAL_IoMgrConfigGetNextChild(pChild, &nCount, pConnector);
			}
			
			/* Example how to read a parameter value */
			pParameter = CAL_IoMgrConfigGetParameter(pConnector, 393220);	/* test parameter */
			if (pParameter != NULL)
			{
				if (pParameter->dwFlags & PVF_POINTER)
					pTestParameter = (unsigned char *)pParameter->dwValue;
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
		}
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
			/* For demonstation, example for manual read of channel map list, using memcpy */
			/* Note: In Dep.m4 file, add USE_ITF(`SysCpuHandlingItf.m4'), and SysCpuTestAndSetBit to REQUIRED_IMPORTS */
			/* Note: Does not handle byte swapping. Use IoMgrCopyInput functions instead. */ /*
			RTS_IEC_BYTE *pbyIecAddress;
			char *pAddress;
			IoConfigChannelMap *pChannel = &(pConnectorMapList[i].pChannelMapList[j]);

			if (pChannel == NULL)
				return ERR_PARAMETER;

			pbyIecAddress = &pChannel->pbyIecAddress[pChannel->wIecAddressBitOffset/8];
			pAddress = (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific;

			if (pbyIecAddress == NULL || pAddress == NULL)
				return ERR_PARAMETER;

			if(pChannel->wSize == 1)
			{
				// Bit Access
				int bSet = (pAddress[pChannel->wParameterBitOffset/8] >> (pChannel->wParameterBitOffset%8)) & 0x1;
				CAL_SysCpuTestAndSetBit(pbyIecAddress, 1, pChannel->wIecAddressBitOffset % 8, bSet);
			}
			else
			{
				// Standard Data Types and Arrays
				int iOffset = pChannel->wParameterBitOffset/8;
				memcpy(pbyIecAddress, pAddress + iOffset, pChannel->wSize/8);
			}
			*/

			/* Instead of manual example using memcpy, better use IoMgrCopyInput functions */
			/* Use BE functions if physical process image is big endian */
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
			/* For demonstration, example for manual read of channel map list, using memcpy */
			/* Note: In Dep.m4 file, add USE_ITF(`SysCpuHandlingItf.m4'), and SysCpuTestAndSetBit to REQUIRED_IMPORTS */
			/* Note: Does not handle byte swapping. Use IoMgrCopyOutput functions instead. */ /*
			RTS_IEC_BYTE *pbyIecAddress;
			char *pAddress;
			IoConfigChannelMap *pChannel = &(pConnectorMapList[i].pChannelMapList[j]);

			if (pChannel == NULL)
				return ERR_PARAMETER;

			pbyIecAddress = &pChannel->pbyIecAddress[pChannel->wIecAddressBitOffset/8];
			pAddress = (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific;

			if (pbyIecAddress == NULL || pAddress == NULL)
				return ERR_PARAMETER;

			if(pChannel->wSize == 1)
			{
				// Bit Access
				int i = pChannel->wParameterBitOffset/8;
				int bSet = (pbyIecAddress[0] >> (pChannel->wIecAddressBitOffset%8)) & 0x1;
				CAL_SysCpuTestAndSetBit(&pAddress[i], 1, pChannel->wParameterBitOffset % 8, bSet);
			}
			else
			{
				// Standard Data Types and Arrays
				int iOffset = pChannel->wParameterBitOffset/8;
				memcpy(pAddress + iOffset, pbyIecAddress, pChannel->wSize/8);
			}

			/* Instead of manual example using memcpy, better use IoMgrCopyOutput functions */
			/* Use BE functions if physical process image is big endian */
			CAL_IoMgrCopyOutputLE(&(pConnectorMapList[i].pChannelMapList[j]), (char *)pConnectorMapList[i].pChannelMapList[j].pParameter->dwDriverSpecific);
		}
	}
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL IoDrvStartBusCycle(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)
{
	int i;

	if (pConnector->wType != 40100)
		return ERR_OK;

	/* Our dummy driver: Copy outputs to inputs. Remove this code in your real driver */
	for (i=0; i< MAX_CHANNELS; i++)
		s_ulyInputs[i] = s_ulyOutputs[i];

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

