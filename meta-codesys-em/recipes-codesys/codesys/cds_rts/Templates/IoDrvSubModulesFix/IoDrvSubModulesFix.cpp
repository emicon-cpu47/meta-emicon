/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvSubModulesFix.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_IoDrvSubModulesFix		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvSubModulesFix	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IIoDrvVErySimple		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





RTS_HANDLE CDECL CIoDrvSubModulesFix::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvSubModulesFix = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvSubModulesFix,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvSubModulesFix,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvSubModulesFix,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvSubModulesFix,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvSubModulesFix,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvSubModulesFix,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvSubModulesFix,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvSubModulesFix,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvSubModulesFix,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvSubModulesFix,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesFix::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvSubModulesFix,pConnectorMapList,nCount);
}







