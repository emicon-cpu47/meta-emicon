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
static RTS_HANDLE s_hOperationWatchdog = RTS_INVALID_HANDLE;

#define SYSTASK_COMPONENT_AVAILABLE()		(CHK_SysTaskCreate && CHK_SysTaskResume && CHK_SysTaskWaitSleep && CHK_SysTaskEnd && CHK_SysTaskExit && CHK_SysTaskSetExit && CHK_SysTaskEnter && CHK_SysTaskLeave)


/**
* <category>OperationID</category>
* <description>Operation ID for the supervision</description>
* <param name="RTS_OPID_CmpTemplate_TestWatchdog" type="IN">The OperationID</param>
* <param name="RTS_OPID_CmpTemplate_TestWatchdog_Description" type="IN"></param>
*/
#define RTS_OPID_CmpTemplate_TestWatchdog				3
#define RTS_OPID_CmpTemplate_TestWatchdog_Description	"Test operation hardware watchdog"

/**
 * <description>Function to activate the hardware watchdog.
 *	USAGE:
 *	- Must be called in the watchdog task before the cyclic check of the supervisor operations.
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL HardwareWatchdogInit(void)
{
	RTS_RESULT Result = ERR_NOT_SUPPORTED;
	/* Register hardware watchdog as supervisor operation */
	if (CHK_SupervisorOperationRegister)
	{
		/* This is a operation which illustrates a consumer/watchdog operation! E.g. a hardware watchdog on a controller should registered at the supervisor that everyone
		can see, that there is an operating watchdog available at the target.
		*/
		s_hOperationWatchdog = CAL_SupervisorOperationRegister(RTS_OPID_CmpTemplate_TestWatchdog, COMPONENT_ID, RTS_OPID_CmpTemplate_TestWatchdog_Description, 0, &Result);
		if (Result != ERR_OK || s_hOperationWatchdog == RTS_INVALID_HANDLE)
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0, "HardwareWatchdog Template: SupervisorOperationRegister failed, watchdog not registered!");
		else
		{
			SupervisorEntry *pEntry = CAL_SupervisorOperationGetEntry(s_hOperationWatchdog, &Result);
			if (pEntry != NULL && Result == ERR_OK)
				pEntry->flags |= RTS_SUPERVISOR_FLAG_WATCHDOG;
			
			CAL_SupervisorOperationEnable(s_hOperationWatchdog);
		}
	}

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

	if (CHK_SupervisorOperationUnregister && s_hOperationWatchdog != RTS_INVALID_HANDLE)
		CAL_SupervisorOperationUnregister(s_hOperationWatchdog);
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
	int bFirstWatchdogTrigger = 1;
	int bWatchdogExpired = 0;
	int bWatchdogError = 0;
	RTS_UI32 tLastWatchdogTrigger = 0;

	CAL_SysTaskEnter(ptp->hTask);

	Result = HardwareWatchdogInit();

	while (!ptp->bExit && Result == ERR_OK)
	{
		if (CHK_SupervisorOperationGetState2)
		{
			SupervisorState state;

			Result = CAL_SupervisorOperationGetState2(&state);
			if (Result == ERR_OK)
			{
				SupervisorEntry *pEntry = CAL_SupervisorOperationGetEntry(s_hOperationWatchdog, &Result);
				RTS_IEC_UDINT nNumOfFailedOperations = state.nNumOfFailedOperations;

				/* Retrigger hardware watchdog if:
				- all operations are alive
				- hardware watchdog was disabled
				*/
				if (nNumOfFailedOperations == 0 || (pEntry != NULL && !pEntry->bEnable))
				{
					/* Retrigger hardware watchdog */
					Result = HardwareWatchdogTrigger();

					tLastWatchdogTrigger = CAL_SysTimeGetMs();
	
					if (bFirstWatchdogTrigger)
					{
						bFirstWatchdogTrigger = 0;
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, LOG_TEXT("HardwareWatchdog Template: Trigger active"));
					}
	
					if (!bWatchdogExpired)
						bWatchdogError = 0;
					
					if (pEntry != NULL && !pEntry->bEnable)
						nNumOfFailedOperations = 0;
				}

				if (!bWatchdogError && nNumOfFailedOperations > 0)
				{
					bWatchdogError = 1;
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, Result, 0, LOG_TEXT("HardwareWatchdog Template: %ld supervised operation(s) failed"), nNumOfFailedOperations);
				}
				if (!bWatchdogExpired && CAL_SysTimeGetMs() - tLastWatchdogTrigger > 2 * s_ulHardwareWatchdogCycleTime)
				{
					bWatchdogExpired = 1;
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_EXCEPTION, Result, 0, LOG_TEXT("HardwareWatchdog Template: Test watchdog expired, restart necessary"));
				}
			}
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
	if (SYSTASK_COMPONENT_AVAILABLE() && CHK_SupervisorOperationGetState2 && CHK_SysTimeGetMs)
	{
		s_hHardwareWatchdogTask = CAL_SysTaskCreate("HardwareWatchdogTask", HardwareWatchdogTask, NULL, TASKPRIO_REALTIME_BASE, 0, 0, 0, &Result);
		if (s_hHardwareWatchdogTask == RTS_INVALID_HANDLE || Result != ERR_OK)
		{
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, Result, 0, LOG_TEXT("HardwareWatchdog Template: error creating hardware watchdog task! Task not running!"));
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

