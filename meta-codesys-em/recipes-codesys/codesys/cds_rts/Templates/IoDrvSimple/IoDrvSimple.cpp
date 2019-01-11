/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvSimple.c"




/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */

#define CMPID_IoDrvSimple		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvSimple	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IIoDrvSimple		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */










RTS_HANDLE CDECL CIoDrvSimple::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvSimple = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvSimple,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvSimple,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvSimple,pConnector);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvSimple,pConnector);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvSimple,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvSimple,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvSimple,pConnector);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvSimple,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvSimple,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvSimple,pConnector);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvSimple,pConnectorMapList,nCount);
}





RTS_RESULT CDECL CIoDrvSimple::IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvReadParameter(hIoDrvSimple,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CIoDrvSimple::IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvWriteParameter(hIoDrvSimple,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}







