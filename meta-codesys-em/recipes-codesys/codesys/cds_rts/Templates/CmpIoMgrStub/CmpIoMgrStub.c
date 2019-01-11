/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Stub component implementing the CmpIoMgr interface
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpIoMgrStubDep.h"

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

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpIoMgrStub);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpIoMgrStub)
	{
		CCmpIecVarTest *pCCmpIoMgrStub = static_cast<CCmpIoMgrStub *>(new CCmpIoMgrStub());
		return (IBase*)pCCmpIoMgrStub->QueryInterface(pCCmpIoMgrStub, ITFID_IBase, pResult);
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
	/* nothing to do in this stub component */
	return ERR_OK;
}

/* dummy implementation */

void CDECL CDECL_EXT iomgrregisterinstance(iomgrregisterinstance_struct *p)
{
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrregisterinstance2(iomgrregisterinstance2_struct *p)
{
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrunregisterinstance(iomgrunregisterinstance_struct *p)
{
	p->IoMgrUnregisterInstance = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrgetfirstdriverinstance(iomgrgetfirstdriverinstance_struct *p)
{
	p->IoMgrGetFirstDriverInstance = NULL;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrgetnextdriverinstance(iomgrgetnextdriverinstance_struct *p)
{
	p->IoMgrGetNextDriverInstance = NULL;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrsetdriverproperties(iomgrsetdriverproperties_struct *p)
{
	p->IoMgrSetDriverProperties = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrgetdriverproperties(iomgrgetdriverproperties_struct *p)
{
	p->IoMgrGetDriverProperties = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrsetdriverproperty(iomgrsetdriverproperty_struct *p)
{
	p->IoMgrSetDriverProperty = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrregisterconfigapplication(iomgrregisterconfigapplication_struct *p)
{
	p->IoMgrRegisterConfigApplication = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrunregisterconfigapplication(iomgrunregisterconfigapplication_struct *p)
{
	p->IoMgrUnregisterConfigApplication = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrgetconfigapplication(iomgrgetconfigapplication_struct *p)
{
	p->IoMgrGetConfigApplication = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrupdateconfiguration(iomgrupdateconfiguration_struct *p)
{
	p->IoMgrUpdateConfiguration = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrupdateconfiguration2(iomgrupdateconfiguration2_struct *p)
{
	p->IoMgrUpdateConfiguration2 = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrupdatemapping(iomgrupdatemapping_struct *p)
{
	p->IoMgrUpdateMapping = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrupdatemapping2(iomgrupdatemapping2_struct *p)
{
	p->IoMgrUpdateMapping2 = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrreconfigure(iomgrreconfigure_struct *p)
{
	p->IoMgrReconfigure = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrreadinputs(iomgrreadinputs_struct *p)
{
	p->IoMgrReadInputs = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrwriteoutputs(iomgrwriteoutputs_struct *p)
{
	p->IoMgrWriteOutputs = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrstartbuscycle(iomgrstartbuscycle_struct *p)
{
	p->IoMgrStartBusCycle = ERR_NOTIMPLEMENTED;
}
void CDECL CDECL_EXT iomgrstartbuscycle2(iomgrstartbuscycle2_struct *p)
{
	p->IoMgrStartBusCycle2 = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrgetbuscycletype(iomgrgetbuscycletype_struct *p)
{
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
	p->IoMgrGetBusCycleType = 0;
}

void CDECL CDECL_EXT iomgrscanmodules(iomgrscanmodules_struct *p)
{
	p->IoMgrScanModules = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrgetmodulediagnosis(iomgrgetmodulediagnosis_struct *p)
{
	p->IoMgrGetModuleDiagnosis = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgridentify(iomgridentify_struct *p)
{
	p->IoMgrIdentify = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrwatchdogtrigger(iomgrwatchdogtrigger_struct *p)
{
	p->IoMgrWatchdogTrigger = ERR_NOTIMPLEMENTED;
}

/* Io-Config access help routines */
void CDECL CDECL_EXT iomgrconfiggetparameter(iomgrconfiggetparameter_struct *p)
{
	p->IoMgrConfigGetParameter = NULL;
}

void CDECL CDECL_EXT iomgrconfiggetparametervaluedword(iomgrconfiggetparametervaluedword_struct *p)
{
	p->IoMgrConfigGetParameterValueDword = 0;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrconfiggetparametervalueword(iomgrconfiggetparametervalueword_struct *p)
{
	p->IoMgrConfigGetParameterValueWord = 0;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrconfiggetparametervaluebyte(iomgrconfiggetparametervaluebyte_struct *p)
{
	p->IoMgrConfigGetParameterValueByte = 0;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrconfiggetparametervaluepointer(iomgrconfiggetparametervaluepointer_struct *p)
{
	p->IoMgrConfigGetParameterValuePointer = NULL;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrconfiggetfirstconnector(iomgrconfiggetfirstconnector_struct *p)
{
	p->IoMgrConfigGetFirstConnector = NULL;
}

void CDECL CDECL_EXT iomgrconfiggetnextconnector(iomgrconfiggetnextconnector_struct *p)
{
	p->IoMgrConfigGetNextConnector = NULL;
}

void CDECL CDECL_EXT iomgrconfiggetfirstchild(iomgrconfiggetfirstchild_struct *p)
{
	p->IoMgrConfigGetFirstChild = NULL;
}

void CDECL CDECL_EXT iomgrconfiggetnextchild(iomgrconfiggetnextchild_struct *p)
{
	p->IoMgrConfigGetNextChild = NULL;
}

void CDECL CDECL_EXT iomgrconfiggetconnectorlist(iomgrconfiggetconnectorlist_struct *p)
{
	p->IoMgrConfigGetConnectorList = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrconfiggetconnector(iomgrconfiggetconnector_struct *p)
{
	p->IoMgrConfigGetConnector = NULL;
}

void CDECL CDECL_EXT iomgrconfiggetdriver(iomgrconfiggetdriver_struct *p)
{
	p->IoMgrConfigGetDriver = NULL;
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

void CDECL CDECL_EXT iomgrconfigsetdiagnosis(iomgrconfigsetdiagnosis_struct *p)
{
	p->IoMgrConfigSetDiagnosis = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrconfigresetdiagnosis(iomgrconfigresetdiagnosis_struct *p)
{
	p->IoMgrConfigResetDiagnosis = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrreadparameter(iomgrreadparameter_struct *p)
{
	p->IoMgrReadParameter = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrwriteparameter(iomgrwriteparameter_struct *p)
{
	p->IoMgrWriteParameter = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrconfiggetconnectorbydriver(iomgrconfiggetconnectorbydriver_struct *p)
{
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

/* Only for backward compatibility! */
void CDECL CDECL_EXT iomgrconfiggetiodriver(iomgrconfiggetiodriver_struct *p)
{
	RTS_SETRESULT(p->pResult, ERR_NOTIMPLEMENTED);
}

/**
 * IEC Interface: Copy Input/Output
 */
void CDECL CDECL_EXT iomgrcopyinputbe(iomgrcopyinputbe_struct *p)
{
	p->IoMgrCopyInputBE = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrcopyinputle(iomgrcopyinputle_struct *p)
{
	p->IoMgrCopyInputLE = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrcopyoutputbe(iomgrcopyoutputbe_struct *p)
{
	p->IoMgrCopyOutputBE = ERR_NOTIMPLEMENTED;
}

void CDECL CDECL_EXT iomgrcopyoutputle(iomgrcopyoutputle_struct *p)
{
	p->IoMgrCopyOutputLE = ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrExceptionHandler(char *pszApplication, RTS_UI32 ulException)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_HANDLE CDECL IoMgrRegisterInstance(IBase *pIBase, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return RTS_INVALID_HANDLE;
}

RTS_HANDLE CDECL IoMgrRegisterInstance2(IBase *pIBase, int bIecDriver, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return RTS_INVALID_HANDLE;
}

RTS_RESULT CDECL IoMgrUnregisterInstance(IBase *pIBase)
{
	return ERR_NOTIMPLEMENTED;	
}

IBase* CDECL IoMgrGetFirstDriverInstance(int *pbIecDriver, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return NULL;
}

IBase* CDECL IoMgrGetNextDriverInstance(IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return NULL;
}

RTS_RESULT CDECL IoMgrSetDriverProperties(IBase *pIBase, RTS_UI32 ulProperties)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrGetDriverProperties(IBase *pIBase, RTS_UI32 **ppulProperty)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrSetDriverProperty(IBase *pIBase, RTS_UI32 ulProperty, int bValue)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrRegisterConfigApplication(char *pszConfigApplication)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrUnregisterConfigApplication(char *pszConfigApplication)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrGetConfigApplication(char *pszConfigApplication, int *pnMaxLen)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrUpdateConfiguration2(IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_BOOL CDECL IoMgrHasTaskIOs(RTS_UI32 dwTaskId, RTS_UI16 taskMapType, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return FALSE;
}

RTS_RESULT CDECL IoMgrUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrUpdateMapping2(IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrReconfigure(IoConfigConnector *pConnector, RTS_UI32 *pui32State)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrReadInputs(IoConfigTaskMap *pTaskMap)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrWriteOutputs(IoConfigTaskMap *pTaskMap)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrStartBusCycle(IoConfigConnector *pConnector)
{
	return ERR_NOTIMPLEMENTED;
}


RTS_RESULT CDECL IoMgrStartBusCycle2(IoConfigConnector *pConnector, RTS_UI32 dwType)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_UI32 CDECL IoMgrGetBusCycleType(IoConfigConnector *pConnector, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}
RTS_RESULT CDECL IoMgrScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrIdentify(IoConfigConnector *pConnector)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrNominate(IoConfigConnector *pConnector)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrWatchdogTrigger(IoConfigConnector *pConnector)
{
	return ERR_NOTIMPLEMENTED;
}

/* Io-Config access help routines */
IoConfigParameter *CDECL IoMgrConfigGetParameter(IoConfigConnector *pConnector, RTS_UI32 dwParameterId)
{
	return NULL;
}

RTS_UI32 CDECL IoMgrConfigGetParameterValueDword(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

unsigned short CDECL IoMgrConfigGetParameterValueWord(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

unsigned char CDECL IoMgrConfigGetParameterValueByte(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

void* CDECL IoMgrConfigGetParameterValuePointer(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return NULL;
}

IoConfigConnector *CDECL IoMgrConfigGetFirstConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType)
{
	return NULL;
}

IoConfigConnector *CDECL IoMgrConfigGetNextConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType)
{
	return NULL;
}

IoConfigConnector *CDECL IoMgrConfigGetFirstChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather)
{
	return NULL;
}

IoConfigConnector *CDECL IoMgrConfigGetNextChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather)
{
	return NULL;
}

RTS_RESULT CDECL IoMgrConfigGetConnectorList(IoConfigConnector **ppConnectorList, int *pnCount)
{
	return ERR_NOTIMPLEMENTED;
}

IoConfigConnector* CDECL IoMgrConfigGetConnector(IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance)
{
	return NULL;
}

IBase* CDECL IoMgrConfigGetDriver(IoConfigConnector *pConnector, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return NULL;
}

RTS_RESULT CDECL IoMgrConfigSetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrConfigResetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrReadParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL IoMgrWriteParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return ERR_NOTIMPLEMENTED;
}

IoConfigConnector *CDECL IoMgrConfigGetConnectorByDriver(IBase *pIBase, int nIndex, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return NULL;
}

RTS_RESULT CDECL IoMgrCopyOutputLE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return ERR_OK;
}

RTS_RESULT CDECL IoMgrCopyOutputBE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return ERR_OK;
}

RTS_RESULT CDECL IoMgrCopyInputBE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return ERR_OK;
}

RTS_RESULT CDECL IoMgrCopyInputLE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return ERR_OK;
}
