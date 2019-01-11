/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "IoDrvSubModulesSlot.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_IoDrvSubModulesSlot		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvSubModulesSlot	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IIoDrvVErySimple		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





RTS_HANDLE CDECL CIoDrvSubModulesSlot::IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hIoDrvSubModulesSlot = IoDrvCreate(hIIoDrv,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpIoDrv *)this, ITFID_ICmpIoDrv, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvDelete(RTS_HANDLE hIIoDrv)
{
	RTS_RESULT Result = IoDrvDelete(hIoDrvSubModulesSlot,hIIoDrv);
	DeleteInstance((IBase *)(ICmpIoDrv *)this);
	return Result;
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvGetInfo(IoDrvInfo **ppIoDrv)
{
	return IoDrvGetInfo(hIoDrvSubModulesSlot,ppIoDrv);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector)
{
	return IoDrvGetModuleDiagnosis(hIoDrvSubModulesSlot,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvIdentify(IoConfigConnector *pConnector)
{
	return IoDrvIdentify(hIoDrvSubModulesSlot,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvReadInputs(hIoDrvSubModulesSlot,pConnectorMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)
{
	return IoDrvScanModules(hIoDrvSubModulesSlot,pConnector,ppConnectorList,pnCount);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvStartBusCycle(IoConfigConnector *pConnector)
{
	return IoDrvStartBusCycle(hIoDrvSubModulesSlot,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount)
{
	return IoDrvUpdateConfiguration(hIoDrvSubModulesSlot,pConnectorList,nCount);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount)
{
	return IoDrvUpdateMapping(hIoDrvSubModulesSlot,pTaskMapList,nCount);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvWatchdogTrigger(IoConfigConnector *pConnector)
{
	return IoDrvWatchdogTrigger(hIoDrvSubModulesSlot,pConnector);
}

RTS_RESULT CDECL CIoDrvSubModulesSlot::IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount)
{
	return IoDrvWriteOutputs(hIoDrvSubModulesSlot,pConnectorMapList,nCount);
}







