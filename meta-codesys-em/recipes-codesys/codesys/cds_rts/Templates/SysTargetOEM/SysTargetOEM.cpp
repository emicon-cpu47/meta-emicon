/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/






#include "SysTargetOEM.c"
























RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetNodeName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetConfiguredNodeName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetConfiguredNodeName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetType(RTS_UI32 *pulType)
{
	return SysTargetGetType(pulType);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetId(RTS_UI32 *pulTargetId)
{
	return SysTargetGetId(pulTargetId);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetVersion(RTS_UI32 *pulVersion)
{
	return SysTargetGetVersion(pulVersion);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetDeviceName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetDeviceName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetVendorName(RTS_WCHAR *pwszName, RTS_SIZE *pnMaxLength)
{
	return SysTargetGetVendorName(pwszName,pnMaxLength);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetOperatingSystemId(RTS_UI32 *pulOperatingSystemId)
{
	return SysTargetGetOperatingSystemId(pulOperatingSystemId);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetProcessorId(RTS_UI32 *pulProcessorId)
{
	return SysTargetGetProcessorId(pulProcessorId);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetSerialNumber(char **ppszSerialNumber, RTS_I32 *pnMaxLen)
{
	return SysTargetGetSerialNumber(ppszSerialNumber,pnMaxLen);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetSerialNumber_Secure(char **ppszSerialNumber, RTS_I32 *pnMaxLen)
{
	return SysTargetGetSerialNumber_Secure(ppszSerialNumber,pnMaxLen);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetSignature(RTS_UI32 ulChallenge, RTS_UI32 *pulSignature)
{
	return SysTargetGetSignature(ulChallenge,pulSignature);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetGetDeviceMask(RTS_UI16 *pusDeviceMask)
{
	return SysTargetGetDeviceMask(pusDeviceMask);
}

RTS_RESULT CDECL CSysTargetOEM::ISysTargetCheckIdent(SysTargetIdent *pTargetIdentReq, SysTargetIdent *pTargetIdent)
{
	return SysTargetCheckIdent(pTargetIdentReq,pTargetIdent);
}





