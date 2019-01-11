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
#include <pthread.h>
#include <errno.h>


#include "CmpStd.h"
#include "CMItf.h"
#include "CmpErrors.h"
#include "SysTaskItf.h"
#include "CmpLogItf.h"
#include "CmpSIL2Itf.h"
#include "CmpScheduleItf.h"
#include "IoDrvBridgeItf.h"


COMPO_INIT_DECLS

/* locals */
static int s_bExitLoop;
static struct sigaction main_act,act_ign;
static StaticComponent SysMainComponentList[] = {
	COMPO_INIT_LIST
};

/* safe memory handling */
extern void SIL2OEMSwitchToPreviousCtx(void);
extern void SIL2OEMSwitchToUnsafeCtx(void);
extern void SIL2OEMSwitchToSafeCtx(void);


#ifdef RTS_MODULETEST
   RTS_RESULT CDECL CDSTestFrameworkException(RTS_UI32 uiExceptionCode)
   {
   	return ERR_OK;
   }
#endif /* RTS_MODULETEST */

#ifndef CMPAPPBP_NOTIMPLEMENTED
#include "CmpEventMgrItf.h"
#include "CmpAppBPItf.h"

RTS_HANDLE s_hEventCodePatch;

void SysFlashLinuxEnableWProt();
void SysFlashLinuxRemoveWProt();

static void CDECL CBCodePatch(EventParam* pEventParam)
{
	switch(pEventParam->EventId)
	{
		case EVT_CmpAppBP_CodePatch:
		{
			EVTPARAM_CmpAppBP_SavePatch *pParam = (EVTPARAM_CmpAppBP_SavePatch*) pEventParam->pParameter;
			if(pParam->flags & APPBP_FLAG_BEFORE_CODE_PATCH)
			{
				SysFlashLinuxRemoveWProt();
			}
			else if(pParam->flags & APPBP_FLAG_AFTER_CODE_PATCH)
			{
				SysFlashLinuxEnableWProt();
			}
		}
	}
}

void RegisterCodePatchEvent()
{
	RTS_RESULT Result = ERR_OK;
	s_hEventCodePatch = CAL_EventOpen(EVT_CmpAppBP_CodePatch, CMPID_CmpAppBP, &Result);
	CAL_EventRegisterCallbackFunction(s_hEventCodePatch, CBCodePatch,0);
}


#endif


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
	struct sched_param sched_param;

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


	sched_param.sched_priority = 0;
	if(pthread_setschedparam(pthread_self(),SCHED_OTHER,&sched_param))
	{
		DEBUGP("pthread_setschedparam:%s",strerror(errno));
	}


	SIL2OEMSwitchToSafeCtx();

	if(CMInit(NULL, SysMainComponentList) != ERR_OK)
	{
		SIL2OEMException(RTS_SIL2_EXCEPTION_RUNTIME_INIT);
	}

	/* Load boot application */
	Result = SIL2AppBoot();

	if(Result != ERR_OK && Result != ERR_NO_OBJECT)
	{
		SIL2OEMException(RTS_SIL2_EXCEPTION_LOADBOOTPROJECT);
	}

#ifndef CMPAPPBP_NOTIMPLEMENTED
	RegisterCodePatchEvent();

#endif

	s_bExitLoop = 0;

	while(!s_bExitLoop) 
	{
		/* Set comm cycle hook counter of safety components to 0. They should be 1 after comm cycle hook. */
		g_RTS_SIL2_Cycle_LifeCounter_CmpSIL2 = 0;
		g_RTS_SIL2_Cycle_LifeCounter_CmpScheduleTimer = 0;
		g_RTS_SIL2_Cycle_LifeCounter_IoDrvUnsafeBridge = 0;

		/* Call safe comm cycle hook */
		CMCallHook2(CMPTYPE_SAFETY, CH_COMM_CYCLE, 0, 0);

		if(g_RTS_SIL2_Cycle_LifeCounter_CmpSIL2 != 1 ||
		   g_RTS_SIL2_Cycle_LifeCounter_CmpScheduleTimer != 1 ||
		   g_RTS_SIL2_Cycle_LifeCounter_IoDrvUnsafeBridge != 1)
		{
			SIL2OEMException(RTS_SIL2_EXCEPTION_LIFE_COUNTER);
		}

		/* Switch to unsafe mode */
		if(SIL2OEMGetOperationMode() == RTS_SIL2_OPMODE_SAFE)
			SIL2OEMSwitchToUnsafeCtx();

		CMCallHook2(CMPTYPE_STANDARD, CH_COMM_CYCLE, 0, 0);

		/* Switch to safe mode */
		if(SIL2OEMGetOperationMode() == RTS_SIL2_OPMODE_SAFE)
			SIL2OEMSwitchToPreviousCtx();		

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

int rts_system(const char *command)
{
  pid_t return_pid;
  pid_t child_pid;
  int child_status = -1;

  child_pid = vfork();

  if (child_pid == -1)
  {
    return -1;
  }
  else if (child_pid == 0)
  {
    execl("/bin/sh", "sh", "-c", command, (char*)NULL);
    _exit(127);
  }
  else
  {
    return_pid = waitpid(child_pid, &child_status, 0);
    if (return_pid != child_pid)
    {
      return -1;
    }
    else
    {
      return child_status;
    }
  }
}
