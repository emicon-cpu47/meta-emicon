/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Component: 		Main.c
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CMItf.h"
#include "CmpErrors.h"
#include "CmpItf.h"
#include "CmpLogItf.h"
#include "SysTaskItf.h"
#include "ParamDevice.h"

static PFSYSTASKCREATE pfSysTaskCreate = NULL;
static PFSYSTASKENTER pfSysTaskEnter = NULL;
static PFSYSTASKLEAVE pfSysTaskLeave = NULL;
static PFSYSTASKEND pfSysTaskEnd = NULL;
static PFSYSTASKRESUME pfSysTaskResume = NULL;
static PFSYSTASKGETNAME pfSysTaskGetName = NULL;
static PFSYSTASKWAITSLEEP pfSysTaskWaitSleep = NULL;
static PFSYSTASKEXIT pfSysTaskExit = NULL;
static PFLOGADD pfLogAdd = NULL;

COMPO_INIT_DECLS

static StaticComponent s_ComponentList[] = {COMPO_INIT_LIST};

RTS_RESULT CDECL MainLoopExceptionHandler(RTS_HANDLE hTask, RTS_UI32 ulException, RegContext Context)
{
	SYS_TASK_INFO *pTask = (SYS_TASK_INFO *)hTask;
	CAL_LogAdd(STD_LOGGER, 1, LOG_EXCEPTION, ulException, 0, "*EXCEPTION* <Task>%s</Task> <IP>0x%x</IP> <BP>0x%x</BP> <SP>0x%x</SP>", CAL_SysTaskGetName((RTS_HANDLE)pTask, NULL), Context.IP, Context.BP, Context.SP);
	return ERR_OK;
}

static void MainLoop(SYS_TASK_PARAM *pParam)
{
	CAL_SysTaskEnter(pParam->hTask);

	while(!_kbhit() && !CMGetExit())
	{
		CMCallHook( CH_COMM_CYCLE, 0, 0, FALSE);
		CAL_SysTaskWaitSleep(pParam->hTask, 1);
	}

	CAL_SysTaskLeave(pParam->hTask);
	CAL_SysTaskEnd(pParam->hTask, 0);
}

static char* TStr2Str(char* pszOut, TCHAR* ptszIn)
{
	char* pszReturn = pszOut;
	while (*ptszIn != '\0')
		*pszOut++ = (char)*ptszIn++;
	*pszOut = '\0';
	return pszReturn;
}

int main(int argc, char *argv[])
{
	/* Set actual working directory to execution path */
	char sz[MAX_PATH];
	TCHAR wsz[MAX_PATH];
	char drive[3];
    char dir[MAX_PATH];
    GetModuleFileName(NULL, wsz, MAX_PATH);
    TStr2Str(sz, wsz);
	_splitpath(sz, drive, dir, NULL, NULL);
	strcpy((LPSTR)sz, (LPSTR)drive);
	strcat((LPSTR)sz, (LPSTR)dir);
	SetCurrentDirectory(dir);

	__try
	{
		CMInit(NULL, s_ComponentList);
	}
	__except(printf("Exception occurred in CMInit: ExceptionCode=0x%08x\n", (unsigned long)GetExceptionCode()))
	{
		getchar();
		return -1;
	}

	CMGetAPI( "SysTaskCreate", (RTS_VOID_FCTPTR *)&pfSysTaskCreate, 0);
	CMGetAPI( "SysTaskEnter", (RTS_VOID_FCTPTR *)&pfSysTaskEnter, 0);
	CMGetAPI( "SysTaskLeave", (RTS_VOID_FCTPTR *)&pfSysTaskLeave, 0);
	CMGetAPI( "SysTaskEnd", (RTS_VOID_FCTPTR *)&pfSysTaskEnd, 0);
	CMGetAPI( "SysTaskWaitSleep", (RTS_VOID_FCTPTR *)&pfSysTaskWaitSleep, 0);
	CMGetAPI( "SysTaskExit", (RTS_VOID_FCTPTR *)&pfSysTaskExit, 0);
	CMGetAPI( "SysTaskResume", (RTS_VOID_FCTPTR *)&pfSysTaskResume, 0);
	CMGetAPI( "SysTaskGetName", (RTS_VOID_FCTPTR *)&pfSysTaskGetName, 0);
	CMGetAPI( "LogAdd", (RTS_VOID_FCTPTR *)&pfLogAdd, 0);

	if (CHK_SysTaskCreate)
	{
		RTS_RESULT Result;
		RTS_HANDLE hMain = CAL_SysTaskCreate("MainLoop", MainLoop, NULL, 254, 0, 0, MainLoopExceptionHandler, &Result);
		CAL_SysTaskResume(hMain);
		while(!_kbhit() && !CMGetExit())
			Sleep(200);
		if (Result == ERR_OK)
			CAL_SysTaskExit(hMain, 1000);
		getchar();
	}
	else
	{
		while(!_kbhit() && !CMGetExit())
		{
			__try
			{
				CMCallHook( CH_COMM_CYCLE, 0, 0, FALSE);
				Sleep(1);
			}
			__except(printf("Exception occurred in CMCallHook: ExceptionCode=0x%08x\n", (unsigned long)GetExceptionCode()))
			{
			}
		}
		getchar();
	}

	__try
	{
		CMExit();
	}
	__except(printf("Exception occurred in CMExit: ExceptionCode=0x%08x\n", (unsigned long)GetExceptionCode()))
	{
	}

	getchar();
	return 0;
}

RTS_RESULT CDECL MainLoadComponent(char *pszName, char *pszPath, RTS_HANDLE *phModule, PF_COMPONENT_ENTRY* ppfComponentEntry)
{
	return ERR_OK;
}

RTS_RESULT CDECL MainUnloadComponent(char *pszName, RTS_HANDLE hModule)
{
	return ERR_OK;
}

int CDECL MainExitLoop(RTS_UINTPTR ulPar)
{
	CMSetExit();
	return ERR_OK;
}
