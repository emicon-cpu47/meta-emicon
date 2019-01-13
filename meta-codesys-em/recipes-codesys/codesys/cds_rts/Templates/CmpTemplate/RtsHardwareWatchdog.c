/**
 * <name>RtsHardwareWatchdog.c</name>
 * <description>
 *	Example to handle hardware watchdog trigger.
 *
 *	USAGE:
 *		- adjust the cycle time HARDWARE_WATCHTDOGTASK_CYCLE_TIME of the hardware watchdog trigger
 *		- Implement the activation of the hardware watchdog in HardwareWatchdogInit()
 *		- Implement the deactivation of the hardware watchdog in HardwareWatchdogExit()
 *		- Implement the trigger of the hardware watchdog in HardwareWatchdogTrigger()
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#define HARDWARE_WATCHTDOGTASK_CYCLE_TIME		500 /* set the cycle time in ms of the hardware watchdog trigger, typically half of desired expiration time */

static RTS_UI32 s_ulHardwareWatchdogCycleTime = HARDWARE_WATCHTDOGTASK_CYCLE_TIME;
static RTS_HANDLE s_hHardwareWatchdogTask = RTS_INVALID_HANDLE;

#define SYSTASK_COMPONENT_AVAILABLE()		(CHK_SysTaskCreate && CHK_SysTaskResume && CHK_SysTaskWaitSleep && CHK_SysTaskEnd && CHK_SysTaskExit && CHK_SysTaskSetExit && CHK_SysTaskEnter && CHK_SysTaskLeave)

/**
 * <description>Function to activate the hardware watchdog.
 *	USAGE:
 *	- Must be called in the watchdog task before the cyclic check of the supervisor operations.
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL HardwareWatchdogInit(void)
{
	/*
	 * TODO: Start the hardware watchdog here.
	 */
	return ERR_OK;
}

/**
 * <description>Function to deactivate the hardware watchdog.
 *	USAGE:
 *	- Must be called before terminating the watchdog trigger task.
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL HardwareWatchdogExit(void)
{
	/*
	 * TODO: Stop the hardware watchdog here.
	 */
	return ERR_OK;
}

/**
 * <description>Function to trigger cyclically the hardware watchdog.
 *	USAGE:
 *	- Must be cyclically. Is called from a high priority task that polls the status of the supervisor operations.
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL	HardwareWatchdogTrigger(void)
{
	/*
	 * TODO: Trigger the hardware watchdog here.
	 */
	return ERR_OK;
}

/**
 * <description>Function that is called in a seperate task. 
 * Here the supervision and the trigger of the hardware watchdog is called cyclically.
 * </description>
 * <param name="ptp" type="IN">Pointer to task parameter set.</param>  
 * <result></result>
 */
static void CDECL HardwareWatchdogTask(SYS_TASK_PARAM *ptp)
{
	RTS_RESULT Result = ERR_FAILED;
	static int bFirstWatchdogTrigger = 1;
	static int bWatchdogExpired = 0;
	static int bWatchdogError = 0;
	RTS_UI32 tLastWatchdogTrigger = 0;

	CAL_SysTaskEnter(ptp->hTask);

	Result = HardwareWatchdogInit();

	while (!ptp->bExit && Result == ERR_OK)
	{
		SupervisorState *pState = CAL_SupervisorOperationGetState(&Result);
		if (pState != NULL && Result == ERR_OK && pState->nNumOfFailedOperations == 0)
		{
			/* Retrigger hardware watchdog */
			Result = HardwareWatchdogTrigger();

			tLastWatchdogTrigger = CAL_SysTimeGetMs();

			if (bFirstWatchdogTrigger)
			{
				bFirstWatchdogTrigger = 0;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, LOG_TEXT("HardwareWatchdog trigger active"));
			}

			if (!bWatchdogExpired)
				bWatchdogError = 0;
		}

		if (!bWatchdogError && pState != NULL && Result == ERR_OK && pState->nNumOfFailedOperations > 0)
		{
			bWatchdogError = 1;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, Result, 0, LOG_TEXT("HardwareWatchdog: at least one supervised operation failed"));
		}

		if (!bWatchdogExpired && CAL_SysTimeGetMs() - tLastWatchdogTrigger > 2 * s_ulHardwareWatchdogCycleTime)
		{
			bWatchdogExpired = 1;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, Result, 0, LOG_TEXT("HardwareWatchdog expired, restart necessary"));
		}

		CAL_SysTaskWaitSleep(ptp->hTask, s_ulHardwareWatchdogCycleTime);
	}

	CAL_SysTaskLeave(ptp->hTask);
	CAL_SysTaskEnd(ptp->hTask, 0);
}

/**
 * <description>Function to create and start the hardware watchdog task.
 *	USAGE:
 *	- Must be called in CH_INIT_TASKS out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL StartHardwareWatchdog(void)
{
	RTS_RESULT Result = ERR_FAILED;
	if (SYSTASK_COMPONENT_AVAILABLE() && CHK_SupervisorOperationGetState && CHK_SysTimeGetMs)
	{
		s_hHardwareWatchdogTask = CAL_SysTaskCreate("HardwareWatchdogTask", HardwareWatchdogTask, NULL, TASKPRIO_REALTIME_BASE, 0, 0, 0, &Result);
		if (s_hHardwareWatchdogTask == RTS_INVALID_HANDLE || Result != ERR_OK)
		{
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, Result, 0, LOG_TEXT("HardwareWatchdog: error creating hardware watchdog task! Task not running!"));
		}
		else
			Result = CAL_SysTaskResume(s_hHardwareWatchdogTask);
	}
	return Result;
}

/**
 * <description>Function to stop and terminate the hardware watchdog task.
 *	USAGE:
 *	- Must be called in CH_EXIT_TASKS out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL StopHardwareWatchdog(void)
{
	RTS_RESULT Result = HardwareWatchdogExit();

	if (s_hHardwareWatchdogTask != RTS_INVALID_HANDLE && SYSTASK_COMPONENT_AVAILABLE())
	{
		CAL_SysTaskSetExit(s_hHardwareWatchdogTask);
		CAL_SysTaskExit(s_hHardwareWatchdogTask, 1000);
		s_hHardwareWatchdogTask = RTS_INVALID_HANDLE;
	}
	return Result;
}

