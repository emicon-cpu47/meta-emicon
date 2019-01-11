/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvBase.c"
#include "IoDrvTarget.c"








RTS_HANDLE CDECL CIoDrvTarget::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvTarget = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvTarget,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvTarget,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvTarget,pConnector);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvTarget,pConnector);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvTarget,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvTarget,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvTarget,pConnector);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvTarget,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvTarget,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvTarget,pConnector);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvTarget,pConnectorMapList,nCount);
}





RTS_RESULT CDECL CIoDrvTarget::IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvReadParameter(hIoDrvTarget,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvWriteParameter(hIoDrvTarget,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}





RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_M_Read(DPV1_C1_Read *pRead)
{
	return IoDrvDPV1_C1_M_Read(hIoDrvTarget,pRead);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_M_Write(DPV1_C1_Write *pWrite)
{
	return IoDrvDPV1_C1_M_Write(hIoDrvTarget,pWrite);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_M_Alarm(DPV1_C1_Alarm *pAlarm)
{
	return IoDrvDPV1_C1_M_Alarm(hIoDrvTarget,pAlarm);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_M_AlarmAck(DPV1_C1_AlarmAck *pAlarmAck)
{
	return IoDrvDPV1_C1_M_AlarmAck(hIoDrvTarget,pAlarmAck);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_M_Status(DPV1_C1_Status *pStatus)
{
	return IoDrvDPV1_C1_M_Status(hIoDrvTarget,pStatus);
}





RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_S_RegisterRecvCallback(ICmpEventCallback *pICallback)
{
	return IoDrvDPV1_C1_S_RegisterRecvCallback(hIoDrvTarget,pICallback);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_S_UnregisterRecvCallback(ICmpEventCallback *pICallback)
{
	return IoDrvDPV1_C1_S_UnregisterRecvCallback(hIoDrvTarget,pICallback);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_S_RegisterRecvCallbackFunction(PFEVENTCALLBACKFUNCTION pfCallbackFunction, int bIec)
{
	return IoDrvDPV1_C1_S_RegisterRecvCallbackFunction(hIoDrvTarget,pfCallbackFunction,bIec);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(PFEVENTCALLBACKFUNCTION pfCallbackFunction)
{
	return IoDrvDPV1_C1_S_UnregisterRecvCallbackFunction(hIoDrvTarget,pfCallbackFunction);
}

RTS_RESULT CDECL CIoDrvTarget::IIoDrvDPV1_C1_S_Write(DPV1_C1_Write *pWrite)
{
	return IoDrvDPV1_C1_S_Write(hIoDrvTarget,pWrite);
}





