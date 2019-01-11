/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpIoMgrStub.c"




#define CMPID_CmpIoMgrStub		0x2000								/* To prevent conflicts with "real" components, we use this component id in the oem range */
#define CLASSID_CCmpIoMgrStub	ADDVENDORID(CMP_VENDORID, 0x2000)	/* To prevent conflicts with "real" components, we use this component id in the oem range */
#define ITFID_ICmpIoMgrStub		ADDVENDORID(CMP_VENDORID, 0x2000)	/* To prevent conflicts with "real" components, we use this component id in the oem range */



















































RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrExceptionHandler(char *pszApplication, RTS_UI32 ulException)
{
	return IoMgrExceptionHandler(pszApplication,ulException);
}

RTS_HANDLE CDECL CCmpIoMgrStub::IIoMgrRegisterInstance(IBase *pIBase, RTS_RESULT *pResult)
{
	return IoMgrRegisterInstance(pIBase,pResult);
}


RTS_HANDLE CDECL CCmpIoMgrStub::IIoMgrRegisterInstance2(IBase *pIBase, int bIecDriver, RTS_RESULT *pResult)
{
	return IoMgrRegisterInstance2(pIBase,bIecDriver,pResult);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrUnregisterInstance(IBase *pIBase)
{
	return IoMgrUnregisterInstance(pIBase);
}

IBase* CDECL CCmpIoMgrStub::IIoMgrGetFirstDriverInstance(int *pbIecDriver, RTS_RESULT *pResult)
{
	return IoMgrGetFirstDriverInstance(pbIecDriver,pResult);
}

IBase* CDECL CCmpIoMgrStub::IIoMgrGetNextDriverInstance(IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult)
{
	return IoMgrGetNextDriverInstance(pIBasePrev,pbIecDriver,pResult);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrSetDriverProperties(IBase *pIBase, RTS_UI32 ulProperties)
{
	return IoMgrSetDriverProperties(pIBase,ulProperties);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrGetDriverProperties(IBase *pIBase, RTS_UI32 **ppulProperty)
{
	return IoMgrGetDriverProperties(pIBase,ppulProperty);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrSetDriverProperty(IBase *pIBase, RTS_UI32 ulProperty, int bValue)
{
	return IoMgrSetDriverProperty(pIBase,ulProperty,bValue);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrRegisterConfigApplication(char *pszConfigApplication)
{
	return IoMgrRegisterConfigApplication(pszConfigApplication);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrUnregisterConfigApplication(char *pszConfigApplication)
{
	return IoMgrUnregisterConfigApplication(pszConfigApplication);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrGetConfigApplication(char *pszConfigApplication, int *pnMaxLen)
{
	return IoMgrGetConfigApplication(pszConfigApplication,pnMaxLen);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoMgrUpdateConfiguration(pConnectorList,nCount);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrUpdateConfiguration2(IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication)
{
	return IoMgrUpdateConfiguration2(pConnectorList,nCount,pszConfigApplication);
}

RTS_BOOL CDECL CCmpIoMgrStub::IIoMgrHasTaskIOs(RTS_UI32 dwTaskId, RTS_UI16 taskMapType, RTS_RESULT *pResult)
{
	return IoMgrHasTaskIOs(dwTaskId,taskMapType,pResult);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoMgrUpdateMapping(pTaskMapList,nCount);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrUpdateMapping2(IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication)
{
	return IoMgrUpdateMapping2(pTaskMapList,nCount,pszConfigApplication);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrReconfigure(IoConfigConnector *pConnector, RTS_UI32 *pui32State)
{
	return IoMgrReconfigure(pConnector,pui32State);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrReadInputs(IoConfigTaskMap *pTaskMap)
{
	return IoMgrReadInputs(pTaskMap);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrWriteOutputs(IoConfigTaskMap *pTaskMap)
{
	return IoMgrWriteOutputs(pTaskMap);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrStartBusCycle(IoConfigConnector *pConnector)
{
	return IoMgrStartBusCycle(pConnector);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrStartBusCycle2(IoConfigConnector *pConnector, RTS_UI32 dwType)
{
	return IoMgrStartBusCycle2(pConnector,dwType);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrGetBusCycleType(IoConfigConnector *pConnector, RTS_RESULT *pResult)
{
	return IoMgrGetBusCycleType(pConnector,pResult);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoMgrScanModules(pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoMgrGetModuleDiagnosis(pConnector);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrIdentify(IoConfigConnector *pConnector)
{
	return IoMgrIdentify(pConnector);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrNominate(IoConfigConnector *pConnector)
{
	return IoMgrNominate(pConnector);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoMgrWatchdogTrigger(pConnector);
}

IoConfigParameter* CDECL CCmpIoMgrStub::IIoMgrConfigGetParameter(IoConfigConnector *pConnector, RTS_UI32 dwParameterId)
{
	return IoMgrConfigGetParameter(pConnector,dwParameterId);
}

RTS_UI32 CDECL CCmpIoMgrStub::IIoMgrConfigGetParameterValueDword(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	return IoMgrConfigGetParameterValueDword(pParameter,pResult);
}

unsigned short CDECL CCmpIoMgrStub::IIoMgrConfigGetParameterValueWord(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	return IoMgrConfigGetParameterValueWord(pParameter,pResult);
}

unsigned char CDECL CCmpIoMgrStub::IIoMgrConfigGetParameterValueByte(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	return IoMgrConfigGetParameterValueByte(pParameter,pResult);
}

void * CDECL CCmpIoMgrStub::IIoMgrConfigGetParameterValuePointer(IoConfigParameter *pParameter, RTS_RESULT *pResult)
{
	return IoMgrConfigGetParameterValuePointer(pParameter,pResult);
}

IoConfigConnector* CDECL CCmpIoMgrStub::IIoMgrConfigGetFirstConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType)
{
	return IoMgrConfigGetFirstConnector(pConnectorList,pnCount,wType);
}

IoConfigConnector* CDECL CCmpIoMgrStub::IIoMgrConfigGetNextConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType)
{
	return IoMgrConfigGetNextConnector(pConnectorList,pnCount,wType);
}

IoConfigConnector* CDECL CCmpIoMgrStub::IIoMgrConfigGetFirstChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather)
{
	return IoMgrConfigGetFirstChild(pConnectorList,pnCount,pFather);
}

IoConfigConnector* CDECL CCmpIoMgrStub::IIoMgrConfigGetNextChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather)
{
	return IoMgrConfigGetNextChild(pConnectorList,pnCount,pFather);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrConfigGetConnectorList(IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoMgrConfigGetConnectorList(ppConnectorList,pnCount);
}

IoConfigConnector* CDECL CCmpIoMgrStub::IIoMgrConfigGetConnector(IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance)
{
	return IoMgrConfigGetConnector(pConnectorList,pnCount,ulModuleType,ulInstance);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrConfigSetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags)
{
	return IoMgrConfigSetDiagnosis(pConnector,ulFlags);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrConfigResetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags)
{
	return IoMgrConfigResetDiagnosis(pConnector,ulFlags);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrReadParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoMgrReadParameter(ulModuleType,ulInstance,ulParameterId,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrWriteParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoMgrWriteParameter(ulModuleType,ulInstance,ulParameterId,pData,ulBitSize,ulBitOffset);
}

IBase * CDECL CCmpIoMgrStub::IIoMgrConfigGetDriver(IoConfigConnector *pConnector, RTS_RESULT *pResult)
{
	return IoMgrConfigGetDriver(pConnector,pResult);
}

IoConfigConnector * CDECL CCmpIoMgrStub::IIoMgrConfigGetConnectorByDriver(IBase *pIBase, int nIndex, RTS_RESULT *pResult)
{
	return IoMgrConfigGetConnectorByDriver(pIBase,nIndex,pResult);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrCopyInputLE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return IoMgrCopyInputLE(pChannel,pAddress);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrCopyInputBE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return IoMgrCopyInputBE(pChannel,pAddress);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrCopyOutputLE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return IoMgrCopyOutputLE(pChannel,pAddress);
}

RTS_RESULT CDECL CCmpIoMgrStub::IIoMgrCopyOutputBE(IoConfigChannelMap *pChannel, char *pAddress)
{
	return IoMgrCopyOutputBE(pChannel,pAddress);
}






