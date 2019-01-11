#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <sched.h>
#include <unistd.h>
#include "CmpStd.h"
#include "SysTimerDep.h"
#include "CmpScheduleItf.h"

USE_STMT
#define MAX_TIMERS	SYSTIMER_NUM_OF_STATIC_TIMER
#define NSEC_PER_SEC	1000000000


#define SIL2_LINUX_PRIO_WATCHDOG  sched_get_priority_max(SCHED_FIFO) - 4
#define SIL2_LINUX_MAX_PRIO_TIMER sched_get_priority_max(SCHED_FIFO) - 5
#define SIL2_LINUX_MIN_PRIO_TIMER sched_get_priority_min(SCHED_FIFO) + 1

#ifndef SIL2_LINUX_WATCHDOG_INTERVAL_NS
#define SIL2_LINUX_WATCHDOG_INTERVAL_NS 1000000
#endif

typedef struct tagSysLinuxTimerInfo
{
	SYS_TIMER_INFO *pti;
	int opened;
	int bRun;
	struct itimerspec timer;
	pthread_t thread;
} SysLinuxTimerInfo;


static SysLinuxTimerInfo timer[MAX_TIMERS];
static void *watchdogthread(void*);
static int s_bGlobalExit = 0;
static int s_bWatchdogRun = 0;

RTS_RESULT CDECL SysTimerOSInit(INIT_STRUCT *pInit)
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
 
RTS_RESULT CDECL SysTimerOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	static pthread_t wdg;
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
		{
			IMPORT_STMT;
			break;
		}
		case CH_INIT_SYSTEM2:
		{
			int res;
			cpu_set_t cpu_set;

			CPU_ZERO(&cpu_set);
			CPU_SET(0,&cpu_set);
			res = sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set);
			RTS_ASSERT(res == 0);

			break;
		}
		case CH_INIT3:
		{
			if (pthread_create(&wdg, NULL, watchdogthread,NULL) != 0)
			{
				DEBUGP("pthread_create:%s",strerror(errno));
			}
			while (s_bWatchdogRun == 0)
				usleep(1);
			break;
		}
		case CH_EXIT3:
		{
			s_bGlobalExit =1;
			pthread_join(wdg,NULL);
			break;
		}
		default:
			break;
	}
	return ERR_OK;
}

void SysTimerRestoreContextException(void)
{
	int i;
	for(i=0; i<MAX_TIMERS; i++)
	{
		if(timer[i].opened == 1)
		{
			pthread_cancel(timer[i].thread);
		}
	}
}

static void *watchdogthread(void *p)
{
	struct sched_param sched_param;
	struct itimerspec wdgtimer;

	memset (&sched_param, 0, sizeof (sched_param));
	sched_param.sched_priority = SIL2_LINUX_PRIO_WATCHDOG;

	DEBUGP("watchogthread is running (OSprio:%u, cycletime:%uns)", sched_param.sched_priority, SIL2_LINUX_WATCHDOG_INTERVAL_NS);

	if ((pthread_setschedparam (pthread_self(),SCHED_FIFO,&sched_param)))
	{
		DEBUGP("pthread_setschedparam:%s",strerror(errno));
	}
	s_bWatchdogRun = 1;
	wdgtimer.it_interval.tv_sec = 0;
	wdgtimer.it_interval.tv_nsec = SIL2_LINUX_WATCHDOG_INTERVAL_NS;
	if(clock_gettime(CLOCK_MONOTONIC,&wdgtimer.it_value) < 0)
	{
		DEBUGP("clock_gettime:%s",strerror(errno));
	}

	while(!s_bGlobalExit)
	{
		if ((wdgtimer.it_value.tv_nsec += wdgtimer.it_interval.tv_nsec) >= NSEC_PER_SEC)
		{
			wdgtimer.it_value.tv_nsec -= NSEC_PER_SEC;
			wdgtimer.it_value.tv_sec++;
		}
		if(clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &wdgtimer.it_value, NULL) < 0)
		{
			DEBUGP("clock_nanosleep:%s",strerror(errno));
		}
		
		//CAL_Schedule(RTS_INVALID_HANDLE, CMD_TICK);
	}
	DEBUGP("watchdogthread is exiting");
	pthread_exit(0);
}

static void timerfunction(int i)
{
	struct sched_param sched_param;

	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

	memset (&sched_param, 0, sizeof (sched_param));

	if(timer[i].pti->ulPriority < SIL2_LINUX_MAX_PRIO_TIMER)
		sched_param.sched_priority = SIL2_LINUX_MAX_PRIO_TIMER - timer[i].pti->ulPriority;
	else
		sched_param.sched_priority = SIL2_LINUX_MIN_PRIO_TIMER;
 
	if ((pthread_setschedparam (pthread_self(),SCHED_FIFO,&sched_param)))
	{
		DEBUGP("pthread_setschedparam:%s",strerror(errno));
	}

	timer[i].bRun = 1;
	DEBUGP("timerthread %i is running (CDS prio:%lu, OS prio:%u, cycletime %llums)",i ,timer[i].pti->ulPriority, sched_param.sched_priority, timer[i].pti->tIntervalNs/1000000);

	if(clock_gettime(CLOCK_MONOTONIC,&timer[i].timer.it_value) < 0)
	{
		DEBUGP("clock_gettime:%s",strerror(errno));
	}

	timer[i].timer.it_interval.tv_sec = timer[i].pti->tIntervalNs/NSEC_PER_SEC;
	timer[i].timer.it_interval.tv_nsec = timer[i].pti->tIntervalNs%NSEC_PER_SEC;

	while(timer[i].bRun)
	{
		timer[i].timer.it_value.tv_nsec += timer[i].timer.it_interval.tv_nsec;
		timer[i].timer.it_value.tv_sec += timer[i].timer.it_interval.tv_sec;

		if (timer[i].timer.it_value.tv_nsec >= NSEC_PER_SEC)
		{
			timer[i].timer.it_value.tv_nsec -= NSEC_PER_SEC;
			timer[i].timer.it_value.tv_sec++;
		}
		if(clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &timer[i].timer.it_value, NULL) < 0)
		{
			DEBUGP("clock_nanosleep:%s",strerror(errno));
		}
		SysTimerCallCallback(timer[i].pti);
	}
	DEBUGP("timerthread %d is exiting",i);
	pthread_exit(0);
}

RTS_HANDLE CDECL SysTimerOpen(SYS_TIMER_INFO *pTimerInfo, RTS_RESULT *pResult)
{
	int i;
	RTS_RESULT res = ERR_FAILED;
	RTS_HANDLE hTimer = RTS_INVALID_HANDLE;

	if (pTimerInfo == NULL)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	for(i=0;i<MAX_TIMERS;i++)
		if(timer[i].opened == 0)
			break;
	if(i< MAX_TIMERS)
	{
		memset(&(timer[i].timer),0,sizeof(timer[i].timer));
		timer[i].pti = pTimerInfo;
		timer[i].opened = 1;
		timer[i].pti->ulIRQ = i;
		res = ERR_OK;
		hTimer = pTimerInfo;
		DEBUGP("timer %d opened",i);
	}
	else
	{
		DEBUGP("Could not open timer! Too many timers opened!");
		exit(0);
	}

	RTS_SETRESULT(pResult, res);
	return hTimer;
}

RTS_RESULT CDECL SysTimerClose(RTS_HANDLE hTimer)
{
	SYS_TIMER_INFO* pTimerInfo = (SYS_TIMER_INFO*) hTimer;

	if(hTimer==RTS_INVALID_HANDLE || pTimerInfo==0)
		return ERR_PARAMETER;

	pthread_join(timer[pTimerInfo->ulIRQ].thread,NULL);
	DEBUGP("timer %lu closed",pTimerInfo->ulIRQ);
	memset(&(timer[pTimerInfo->ulIRQ]),0,sizeof(SysLinuxTimerInfo));
	return ERR_OK;
}

RTS_RESULT CDECL SysTimerStart(RTS_HANDLE hTimer, unsigned long ulType)
{
	RTS_RESULT res = ERR_FAILED;
	SYS_TIMER_INFO* pTimerInfo = (SYS_TIMER_INFO*) hTimer;

	if(hTimer==RTS_INVALID_HANDLE || pTimerInfo==0)
		return ERR_PARAMETER;

	if(ulType != RTS_TIMER_PERIODIC)
	{
		DEBUGP("Timer type %ld not supported!", ulType);
		return ERR_PARAMETER;
	}

	if (pthread_create(&timer[pTimerInfo->ulIRQ].thread, NULL, (void*(*)(void*))timerfunction,(void*)pTimerInfo->ulIRQ) != 0)
	{
		DEBUGP("pthread_create:%s",strerror(errno));
	}
	else
	{
		pTimerInfo->hSysTimer=(RTS_HANDLE)timer[pTimerInfo->ulIRQ].thread;
		/* Wait until the timer is running (sleep, because the
		 * initial thread is running at a lower priority.
		 */
		while (timer[pTimerInfo->ulIRQ].bRun == 0)
			usleep(1);
		res = ERR_OK;
		DEBUGP("timer %lu started",pTimerInfo->ulIRQ);
	}

	return res;
}

RTS_RESULT CDECL SysTimerStop(RTS_HANDLE hTimer)
{
	SYS_TIMER_INFO* pTimerInfo = (SYS_TIMER_INFO*) hTimer;

	if(hTimer==RTS_INVALID_HANDLE || pTimerInfo==0)
		return ERR_PARAMETER;
	DEBUGP("timer %lu stopped",pTimerInfo->ulIRQ);
	timer[pTimerInfo->ulIRQ].bRun = 0;

	return ERR_OK;
}

RTS_RESULT CDECL SysTimerGetInterval(RTS_HANDLE hTimer, RTS_SYSTIME *ptIntervalNs)
{
	SYS_TIMER_INFO* pTimerInfo = (SYS_TIMER_INFO*) hTimer;

	if(hTimer==RTS_INVALID_HANDLE || pTimerInfo==0)
		return ERR_PARAMETER;

	if(ptIntervalNs == NULL)
		return ERR_PARAMETER;

	*ptIntervalNs = timer[pTimerInfo->ulIRQ].timer.it_interval.tv_sec * NSEC_PER_SEC;
	*ptIntervalNs += timer[pTimerInfo->ulIRQ].timer.it_interval.tv_nsec;
	return ERR_OK;
}

RTS_RESULT CDECL SysTimerSetInterval(RTS_HANDLE hTimer, RTS_SYSTIME tIntervalNs)
{
	SYS_TIMER_INFO* pTimerInfo = (SYS_TIMER_INFO*) hTimer;

	if(hTimer==RTS_INVALID_HANDLE || pTimerInfo==0)
		return ERR_PARAMETER;

	timer[pTimerInfo->ulIRQ].timer.it_interval.tv_sec = tIntervalNs/NSEC_PER_SEC;
	timer[pTimerInfo->ulIRQ].timer.it_interval.tv_nsec = tIntervalNs%NSEC_PER_SEC;
	return ERR_OK;
}

RTS_RESULT CDECL SysTimerMaxTimer(RTS_UI32 *pulMaxTimers)
{
	if(pulMaxTimers == NULL)
		return ERR_PARAMETER;
	*pulMaxTimers = MAX_TIMERS;
	return ERR_OK;
}

RTS_RESULT CDECL SysTimerGetMinResolution(RTS_HANDLE hTimer, RTS_SYSTIME *ptMinResolutionNs)
{
	struct timespec time;
	
	if(ptMinResolutionNs == NULL)
		return ERR_PARAMETER;
	if(clock_getres(CLOCK_MONOTONIC,&time))
		return ERR_FAILED;
	*ptMinResolutionNs = time.tv_sec * NSEC_PER_SEC;
	*ptMinResolutionNs += time.tv_nsec;
	return ERR_OK;
}

RTS_RESULT CDECL SysTimerGetContext(RTS_HANDLE hTimer, RegContext *pContext)
{
	DEBUGP("returning not implemented");
	return ERR_NOTIMPLEMENTED;
}

unsigned int CDECL SysTimerFitTimer(RTS_HANDLE hTimer, unsigned long ulPriority, RTS_SYSTIME tInterval, RTS_RESULT *pResult)
{
	DEBUGP("returning not implemented");
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

RTS_RESULT CDECL SysTimerGetTimeStamp(RTS_HANDLE hTimer, RTS_SYSTIME *ptTimestampNs)
{
	DEBUGP("returning not implemented");
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL SysTimerRegisterBasePointer(RTS_UINTPTR ulBP)
{
	DEBUGP("returning not implemented");
	return ERR_NOTIMPLEMENTED;
}


RTS_HANDLE CDECL SysTimerGetCurrent(RTS_RESULT *pResult)
{
	/* Determining the current timer is not supported.
	 * It is actually only used in combination with CmpScheduleTimer.
	 */
	RTS_SETRESULT(pResult, ERR_NOT_SUPPORTED);
	return RTS_INVALID_HANDLE;
}
