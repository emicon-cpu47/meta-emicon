#include "CmpStd.h"

#ifdef PATHS_RELATIVE
	#include "SysTarget/SysTargetOEMDep.h"
#else
	#include "SysTargetOEMDep.h"
#endif

#define MY_SYSTARGET_NODE_NAME		"MyDevice"

USEIMPORT_STMT

RTS_RESULT CDECL SysTargetOSInit(INIT_STRUCT *pInit)
{
#ifndef RTS_COMPACT_MICRO
	s_pfCMRegisterAPI = pInit->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInit->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInit->pfCMGetAPI;
	s_pfCMGetAPI2 = pInit->pfCMGetAPI2;
	s_pfCMCallHook = pInit->pfCMCallHook;
	s_pfCMRegisterClass = pInit->pfCMRegisterClass;
	s_pfCMCreateInstance = pInit->pfCMCreateInstance;
#endif

	IMPORT_STMT;
	return ERR_OK;
}

RTS_RESULT CDECL SysTargetOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
#ifdef WIN32
#if 0
	/*If 0: In case this is used, an additional dependency to SysFileItf.m4 and SysFileCopy has to be added to the Dep.m4.*/
	/* If this is used with Control Win V3, in a SysTargetOEM.dll, remember to add 
		OverloadableFunctions=1 and the Component.xx=SysTargetOEM
		to both:
		- the configuration file of the runtime CodesysControl.cfg AND
		- the configuration file of the target-visualization targetvisuextern.cfg
		The following section where the 3s.dat (the OEM-specific one) is copied to the root path of the PLC, 
		is not necessarily required, as Codesys Control Win V3 will not write a 3s.dat if a SysTargetOEM.dll changes the vendor ID, 
		but it makes things easier on first start with SysTargetOEM.
		
	*/
	RTS_UI32 uiCopied = 0;
	switch (ulHook)
	{
		case CH_INIT2:
			CAL_SysFileCopy("3s.dat",".\\lic\\3s.dat",&uiCopied);
			break;
		default:
			break;
	}
#endif
#else
	switch (ulHook)
	{
		case CH_EXIT_SYSTEM:
		{
			EXIT_STMT;
			break;
		}	
		default:
			break;
	}
#endif
	return ERR_OK;
}

RTS_RESULT CDECL SysTargetGetNodeName(RTS_WCHAR * pwszName, RTS_SIZE *pnMaxLength)
{
	RTS_SIZE uiLen;

	if (pnMaxLength == NULL)
		return ERR_PARAMETER;

	uiLen = *pnMaxLength;
	if (CAL_SysTargetGetConfiguredNodeName(pwszName, &uiLen) != ERR_OK)
	{
		/* TODO: Set target name, that is displayed at online scan */
		if (pwszName != NULL)
			CAL_CMUtlStrToW(MY_SYSTARGET_NODE_NAME, pwszName, *pnMaxLength);
		*pnMaxLength = strlen(MY_SYSTARGET_NODE_NAME) + 1;
	}
	else
		*pnMaxLength = uiLen;
	return ERR_OK;
}

RTS_RESULT CDECL SysTargetGetSerialNumber(char **ppszSerialNumber, RTS_I32 *pnMaxLen)
{
	if (pnMaxLen == NULL)
		return ERR_PARAMETER;

	*pnMaxLen = 0;

	/*	
		EXAMPLE:
		static char s_szTargetSerialNumber[255] = {0};

		TODO: Retrieve the serial number

		if (ppszSerialNumber == NULL)
		{
			*pnMaxLen = (RTS_I32)strlen(s_szTargetSerialNumber) + 1;
			return ERR_OK;
		}
		*pnMaxLen = MIN((RTS_I32)strlen(s_szTargetSerialNumber) + 1, *pnMaxLen);

		if (*ppszSerialNumber == NULL)
		{
			*ppszSerialNumber = s_szTargetSerialNumber;
			return ERR_OK;
		}
		return CAL_CMUtlSafeStrCpy(*ppszSerialNumber, *pnMaxLen, s_szTargetSerialNumber);

	Alternatively, you can use the secure serial number here, if it is implemented:
		return SysTargetGetSerialNumber_Secure(ppszSerialNumber, pnMaxLen);
	*/
	return ERR_NOTIMPLEMENTED;
}