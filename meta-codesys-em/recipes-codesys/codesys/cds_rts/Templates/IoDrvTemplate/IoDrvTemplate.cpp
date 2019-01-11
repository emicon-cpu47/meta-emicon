/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvTemplate.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_IoDrvTemplate		0x2001								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvTemplate	ADDVENDORID(CMP_VENDORID, 0x2001)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */






RTS_HANDLE CDECL CIoDrvTemplate::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvTemplate = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvTemplate,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvTemplate,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvTemplate,pConnector);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvTemplate,pConnector);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvTemplate,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvTemplate,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvTemplate,pConnector);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvTemplate,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvTemplate,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvTemplate,pConnector);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvTemplate,pConnectorMapList,nCount);
}





RTS_RESULT CDECL CIoDrvTemplate::IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvReadParameter(hIoDrvTemplate,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}

RTS_RESULT CDECL CIoDrvTemplate::IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset)
{
	return IoDrvWriteParameter(hIoDrvTemplate,pConnector,pParameter,pData,ulBitSize,ulBitOffset);
}





