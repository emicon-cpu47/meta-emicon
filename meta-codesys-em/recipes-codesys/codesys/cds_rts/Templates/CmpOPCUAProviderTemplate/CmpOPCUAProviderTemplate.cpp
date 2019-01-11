/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpOPCUAProviderTemplate.c"










RTS_HANDLE CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderCreate(RTS_HANDLE hIOpcUaProvider, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	hCmpOPCUAProviderTemplate = OpcUaProviderCreate(hIOpcUaProvider,ClassId,iId,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ICmpOPCUAProvider *)this, ITFID_ICmpOPCUAProvider, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderDelete(void)
{
	RTS_RESULT Result = OpcUaProviderDelete(hCmpOPCUAProviderTemplate);
	DeleteInstance((IBase *)(ICmpOPCUAProvider *)this);
	return Result;
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderInitialize(void)
{
	return OpcUaProviderInitialize(hCmpOPCUAProviderTemplate);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderCleanup(void)
{
	return OpcUaProviderCleanup(hCmpOPCUAProviderTemplate);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderBrowse(OpcUaProvider_BrowseContext *pContext)
{
	return OpcUaProviderBrowse(hCmpOPCUAProviderTemplate,pContext);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderCreateMonitoredItem(OpcUaProvider_CreateMonitoredItemContext *pContext)
{
	return OpcUaProviderCreateMonitoredItem(hCmpOPCUAProviderTemplate,pContext);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderDeleteMonitoredItem(OpcUaProvider_DeleteMonitoredItemContext *pContext)
{
	return OpcUaProviderDeleteMonitoredItem(hCmpOPCUAProviderTemplate,pContext);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderSampleMonitoredItem(OpcUaProvider_SampleMonitoredItemContext *pContext)
{
	return OpcUaProviderSampleMonitoredItem(hCmpOPCUAProviderTemplate,pContext);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderRead(OpcUaProvider_ReadContext *pContext)
{
	return OpcUaProviderRead(hCmpOPCUAProviderTemplate,pContext);
}

OpcUa_StatusCode CDECL CCmpOPCUAProviderTemplate::IOpcUaProviderWrite(OpcUaProvider_WriteContext *pContext)
{
	return OpcUaProviderWrite(hCmpOPCUAProviderTemplate,pContext);
}





