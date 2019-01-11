/*lint -save --e{*} */
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

/*lint -restore */

#include "CmpStd.h"
#ifdef PATHS_RELATIVE
	#include "SysInt/SysIntDep.h"
#else
	#include "SysIntDep.h"
#endif

USE_STMT

static pthread_mutex_t intlockMutex = PTHREAD_MUTEX_INITIALIZER;
static int s_nestcount;
static struct sched_param old_sched_param;
static int old_policy;

RTS_RESULT CDECL SysIntOSInit(INIT_STRUCT *pInit)
{
	s_pfCMRegisterAPI = pInit->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInit->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInit->pfCMGetAPI;
	s_pfCMGetAPI2 = pInit->pfCMGetAPI2;
	s_pfCMCallHook = pInit->pfCMCallHook;
	s_pfCMRegisterClass = pInit->pfCMRegisterClass;
	s_pfCMCreateInstance = pInit->pfCMCreateInstance;

	return ERR_OK;
}

RTS_RESULT CDECL SysIntOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
		{
			IMPORT_STMT;
			if(geteuid()!=0)
			{
				printf("You have to be root to start this program ! ...bye...\n");
				exit(-1);
			}
			break;
		}
		default:
			break;
	}
	return ERR_OK;
}

RTS_HANDLE CDECL SysIntOpen(unsigned long ulInterrupt, SYS_INT_DESCRIPTION *pIntDescription, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return RTS_INVALID_HANDLE;
}

RTS_HANDLE CDECL SysIntOpenByName(char* pszIntName, RTS_RESULT* pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return RTS_INVALID_HANDLE;
}

RTS_RESULT CDECL SysIntClose(RTS_HANDLE hInt)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL SysIntEnable(RTS_HANDLE hInt)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL SysIntDisable(RTS_HANDLE hInt)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL SysIntRegister(RTS_HANDLE hInt, unsigned long ulType, SYS_INT_INTHANDLER pHandler, RTS_UINTPTR ulAdditionalInfo)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL SysIntUnregister(RTS_HANDLE hInt, SYS_INT_INTHANDLER pHandler)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL SysIntEnableAll(RTS_UI32 *pulParam)
{
	struct sched_param sched_param;
	int res,policy;
	RTS_RESULT retval = ERR_FAILED;

	if(pulParam == NULL)
		return ERR_PARAMETER;
    
	pthread_getschedparam(pthread_self(), &policy, &sched_param);
	RTS_ASSERT(sched_param.sched_priority == sched_get_priority_max(SCHED_FIFO) - 1);
	RTS_ASSERT(policy == SCHED_FIFO);
	RTS_ASSERT(s_nestcount > 0);

	pthread_mutex_lock(&intlockMutex);
	if(--s_nestcount > 0)
	{
		retval = ERR_OK;
	}
	else
	{
		if ((res=pthread_setschedparam(pthread_self(), old_policy, &old_sched_param)))
		{
			DEBUGP("pthread_setschedparam:%s",strerror(res));
		}
		else
			retval = ERR_OK;
	}
	pthread_mutex_unlock(&intlockMutex);

	sched_yield();
	return retval;
}

RTS_RESULT CDECL SysIntDisableAll(RTS_UI32 *pulParam)
{
	struct sched_param sched_param;
	int res,policy;
	RTS_RESULT retval = ERR_FAILED;

	if(pulParam == NULL)
		return ERR_PARAMETER;
    
	RTS_ASSERT(s_nestcount >= 0);
	memset (&sched_param, 0, sizeof (sched_param));
	sched_param.sched_priority = sched_get_priority_max(SCHED_FIFO) - 1;


	pthread_mutex_lock(&intlockMutex);


	if(s_nestcount)
	{
		pthread_getschedparam(pthread_self(), &policy, &sched_param);
		RTS_ASSERT(sched_param.sched_priority == sched_get_priority_max(SCHED_FIFO) - 1);
		RTS_ASSERT(policy == SCHED_FIFO);

		s_nestcount++;
	}
	else
	{
		pthread_getschedparam(pthread_self(), &old_policy, &old_sched_param);

		res=pthread_setschedparam(pthread_self(), SCHED_FIFO, &sched_param);
		if (res)
		{
			DEBUGP("pthread_setschedparam:%s",strerror(res));
		}
		else
		{
			s_nestcount=1;
			retval = ERR_OK;
		}
	}
	pthread_mutex_unlock(&intlockMutex);
	return retval;
}

RTS_RESULT CDECL SysIntLevel(void)
{
	return ERR_NOTIMPLEMENTED;
}

