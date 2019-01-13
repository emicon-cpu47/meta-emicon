/*****************************************************************************
*
*	Copyright:		� 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Component: 		mainOS.c
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CMItf.h"
#include "CmpErrors.h"
#include "CmpItf.h"
#ifdef CODESYSCONTROL_COMPACT_TIMER
	#include "CoDeSysControl_Compact_Timer.h"	/* Adpapt to your platform name. This include file is generated by the RtsConfigurator tool */
#else
	#ifdef RTS_SIL2
		#include "CoDeSysControl_Compact_SIL2.h"			/* Adpapt to your platform name. This include file is generated by the RtsConfigurator tool */
	#elif defined (CODESYSCONTROL_COMPACT_CAN)
		#include "CoDeSysControl_Compact_CAN.h"
	#else
		#include "CoDeSysControl_Compact.h"			/* Adpapt to your platform name. This include file is generated by the RtsConfigurator tool */
	#endif
#endif

#include <_OptionalIncludes/Profiles/uRTS/CMMicro.h>

COMPO_INIT_DECLS

static StaticComponent s_ComponentList[] = {
	COMPO_INIT_LIST
};

static int s_bExitLoop;

int main(int argc, char *argv[])
{
	RTS_RESULT Result;

	printf("MainLoop entered\n");
	
	s_bExitLoop = 0;

	Result = CMInit(NULL, s_ComponentList);
	
	if (Result == ERR_OK || (Result != ERR_ID_MISMATCH && Result != ERR_LICENSE_MISSING))
	{
		while(
#ifdef WIN32
			!_kbhit() &&
#endif
			!s_bExitLoop)
		{
			CMCallHook( CH_COMM_CYCLE, 0, 0, FALSE);
#ifdef WIN32
			Sleep(10);
#endif
		}
	}

	printf("MainLoop exit received...\n");

	if (Result == ERR_OK)
		CMExit();

	printf("MainLoop exit done\n");
	return 0;
}

int PlcExit(void)
{
	s_bExitLoop = 1;
	return ERR_OK;
}

int MainExitLoop(RTS_UINTPTR ulPar)
{
	s_bExitLoop = 1;
	return ERR_OK;
}

RTS_RESULT CDECL MainLoadComponent(char *pszName, RTS_HANDLE *phModule, PF_COMPONENT_ENTRY* ppfComponentEntry)
{
	return ERR_FAILED;
}

RTS_RESULT CDECL MainUnloadComponent(char *pszName, RTS_HANDLE hModule)
{
	return ERR_FAILED;
}
