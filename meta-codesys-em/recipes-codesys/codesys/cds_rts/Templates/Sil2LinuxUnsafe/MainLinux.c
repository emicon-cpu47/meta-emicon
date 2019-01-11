/*****************************************************************************
*
*	Copyright:		(c) 3s - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Component: 		Main.c
*	Version:
*	Description:
******************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include "CmpStd.h"
#include "CMItf.h"
#include "CmpErrors.h"
#include "SysTaskItf.h"
#include "CmpLogItf.h"
#include "CmpSIL2Itf.h"
#include "sysinclude.h"

COMPO_INIT_DECLS

/* locals */
static int s_bExitLoop;
static struct sigaction main_act,act_ign;
static StaticComponent SysMainComponentList[] = {
	COMPO_INIT_LIST
};

void syscpudebughandler(void)
{

}

void main_signalhandler(int sig)
{
	switch(sig)
	{
		case SIGTERM:
		case SIGINT:
			MainExitLoop(0);
			break;
		default:
		{
			DEBUGP("received unexpected signal %d",sig);
		}
	}
}

int main(int argc, char *argv[])
{
	RTS_RESULT Result;

	main_act.sa_handler = main_signalhandler;
	sigemptyset(&main_act.sa_mask);
	main_act.sa_flags = 0;
	act_ign.sa_handler = SIG_IGN;
	sigemptyset(&act_ign.sa_mask);
	act_ign.sa_flags = 0;

	if (sigaction(SIGTERM, &main_act, 0) != 0)
	{
		DEBUGP("Setting sigaction(SIGTERM) failed");
	}
	if (sigaction(SIGINT, &main_act, 0) != 0)
	{
		DEBUGP("Setting sigaction(SIGINT) failed");
	}
	if (sigaction(SIGPIPE, &act_ign, 0) != 0)		/* don't give up due to network problems */
	{
		DEBUGP("Setting sigaction(SIGPIPE) failed");
	}
	if (sigaction(SIGABRT, &act_ign, 0) != 0)		/* don't give up due to QT signal handler*/
	{
		DEBUGP("Setting sigaction(SIGABRT) failed");
	}


	CMInit(NULL, SysMainComponentList);

	s_bExitLoop = 0;

	while(!s_bExitLoop && !CMGetExit()) 
	{

	  CMCallHook(CH_COMM_CYCLE, 0, 0, FALSE);
		usleep(10000);
	}

	return 0;
}

int MainExitLoop(RTS_UINTPTR ulPar)
{
	s_bExitLoop = 1;
	return ERR_OK;
}

int PlcExit(void)
{
	return MainExitLoop(0);
}

RTS_RESULT CDECL MainLoadComponent(char *pszName, char *pszPath, RTS_HANDLE *phModule, PF_COMPONENT_ENTRY* ppfComponentEntry)
{
		printf("module %s not builtin\n",pszName);
		return ERR_FAILED;
}

RTS_RESULT CDECL MainUnloadComponent(char *pszName, RTS_HANDLE hModule)
{
	return ERR_OK;
}

