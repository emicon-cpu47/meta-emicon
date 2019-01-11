/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvSoundDemo.c"




#define CMPID_IoDrvSoundDemo		0x0000FF02
#define CLASSID_CIoDrvSoundDemo		0x0000FF02






RTS_HANDLE CDECL CIoDrvSoundDemo::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvSoundDemo = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvSoundDemo,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvSoundDemo,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvSoundDemo,pConnector);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvSoundDemo,pConnector);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvSoundDemo,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvSoundDemo,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvSoundDemo,pConnector);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvSoundDemo,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvSoundDemo,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvSoundDemo,pConnector);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvSoundDemo,pConnectorMapList,nCount);
}





RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvReadParameter(hIoDrvSoundDemo,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CIoDrvSoundDemo::IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvWriteParameter(hIoDrvSoundDemo,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}





