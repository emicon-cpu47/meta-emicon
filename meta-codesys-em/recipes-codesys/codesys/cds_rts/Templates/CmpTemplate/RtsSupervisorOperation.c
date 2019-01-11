/**
 * <name>RtsSupervisorOperation.c</name>
 * <description>
 *	Example for defining and registering supervisor operations.
 *
 *	This example registers two vital operations to the Supervisor:
 *	1) an operation that cyclically triggers the alive signal in the CH_COMM_CYCLE hook.
 *	2) an operation sets the dead signal after a configured time after the start of the supervision.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#define SUPERVISOR_OPERATION_TEST_ALIVE_TIMEOUT 500000  /* set the timeout in us for the TestAlive operation. */
#define SUPERVISOR_OPERATION_TEST_DEAD_TIMEOUT 30000  /* set the timeout for the dead signal in ms after the start of the supervision (0 to disable). */

static RTS_SYSTIME s_stTimeoutTestAliveUs = SUPERVISOR_OPERATION_TEST_ALIVE_TIMEOUT;
static RTS_HANDLE s_hOperationAlive = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hOperationDead = RTS_INVALID_HANDLE;

/**
 * <category>OperationID</category>
 * <description>Operation ID for the supervision</description>
 * <param name="RTS_OPID_CmpTemplate_TestAlive" type="IN">The OperationID</param>
 * <param name="RTS_OPID_CmpTemplate_TestAlive_Description" type="IN"></param>
 * <param name="RTS_OPID_CmpTemplate_TestDead" type="IN">The OperationID</param>
 * <param name="RTS_OPID_CmpTemplate_TestDead_Description" type="IN"></param>
 */
#define RTS_OPID_CmpTemplate_TestAlive					1
#define RTS_OPID_CmpTemplate_TestAlive_Description		"Test operation alive"

#define RTS_OPID_CmpTemplate_TestDead					2
#define RTS_OPID_CmpTemplate_TestDead_Description		"Test operation dead"

/**
 * <description>Function to register the above operations to the supervisor.
 *	USAGE:
 *	- Must be called in CH_INIT3 out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL RegisterSupervisor(void)
{
	RTS_RESULT Result = ERR_NOT_SUPPORTED;
	/* Register supervisor */
	if (CHK_SupervisorOperationRegister)
	{
		s_hOperationAlive = CAL_SupervisorOperationRegister(RTS_OPID_CmpTemplate_TestAlive, COMPONENT_ID, RTS_OPID_CmpTemplate_TestAlive_Description, s_stTimeoutTestAliveUs, &Result);
		if (Result != ERR_OK || s_hOperationAlive == RTS_INVALID_HANDLE)
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0, "SupervisorOperationRegister failed, Test operation alive not supervised!");

		s_hOperationDead = CAL_SupervisorOperationRegister(RTS_OPID_CmpTemplate_TestDead, COMPONENT_ID, RTS_OPID_CmpTemplate_TestDead_Description, 0, &Result);
		if (Result != ERR_OK || s_hOperationDead == RTS_INVALID_HANDLE)
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0, "SupervisorOperationRegister failed, Test operation dead not supervised!");

		if (s_hOperationAlive != RTS_INVALID_HANDLE && s_hOperationDead != RTS_INVALID_HANDLE)
			Result = ERR_OK;
		else
			Result = ERR_FAILED;
	}
	return Result;
}

/**
* <description>Function to disable the above operations at the supervisor.
*	USAGE:
*	- Should be called as soon as the runtime starts the shutdown, here in  CH_EXIT_COMM out of component HookFunction()!
* </description>
* <result>error code</result>
*/
static RTS_RESULT CDECL DisableSupervisor(void)
{
	RTS_RESULT Result = ERR_NOT_SUPPORTED;
	/* Disable the supervisor operations */
	if (CHK_SupervisorOperationDisable)
	{
		if (s_hOperationAlive != RTS_INVALID_HANDLE)
			CAL_SupervisorOperationDisable(s_hOperationAlive);

		if (s_hOperationDead != RTS_INVALID_HANDLE)
			CAL_SupervisorOperationDisable(s_hOperationDead);

		Result = ERR_OK;
	}
	return Result;
}

/**
* <description>Function to unregister the above operations from the supervisor.
*	USAGE:
*	- Must be called in CH_EXIT3 out of component HookFunction()!
* </description>
* <result>error code</result>
*/
static RTS_RESULT CDECL UnregisterSupervisor(void)
{
	RTS_RESULT Result = ERR_NOT_SUPPORTED;
	/* Unregister supervisor */
	if (CHK_SupervisorOperationUnregister)
	{
		if (s_hOperationAlive != RTS_INVALID_HANDLE)
			CAL_SupervisorOperationUnregister(s_hOperationAlive);

		if (s_hOperationDead != RTS_INVALID_HANDLE)
			CAL_SupervisorOperationUnregister(s_hOperationDead);
	
		Result = ERR_OK;
	}
	return Result;
}

/**
 * <description>Function for the cyclic handling of the registered supervisor operations.
 *	USAGE:
 *	- Must be called in CH_COMM_CYCLE out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL CyclicSupervisorOperations(void)
{
	RTS_RESULT Result = ERR_NOT_SUPPORTED;

	if (CHK_SupervisorOperationEnable && CHK_SupervisorOperationAlive && CHK_SysTimeGetMs && s_hOperationAlive != RTS_INVALID_HANDLE && s_hOperationDead != RTS_INVALID_HANDLE)
	{
		static int bSupervisorOperationEnabled = 0;
		static int bSupervisorOperationDead = 0;
		static RTS_UI32 tFirstCycle;

		if (!bSupervisorOperationEnabled)
		{
			/* enable the supervisor operations in the first cycle */
			if (CAL_SupervisorOperationEnable(s_hOperationAlive) == ERR_OK && CAL_SupervisorOperationEnable(s_hOperationDead) == ERR_OK)
			{
				bSupervisorOperationEnabled = 1;
				tFirstCycle = CAL_SysTimeGetMs();
				if (SUPERVISOR_OPERATION_TEST_DEAD_TIMEOUT != 0)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, LOG_TEXT("SupervisorOperation: test starvation in %d ms"), SUPERVISOR_OPERATION_TEST_DEAD_TIMEOUT);
			}
		}
		else
		{
			/* send alive signal to supervisor */
			CAL_SupervisorOperationAlive(s_hOperationAlive, 0);

			if (!bSupervisorOperationDead && SUPERVISOR_OPERATION_TEST_DEAD_TIMEOUT != 0 && (CAL_SysTimeGetMs() - tFirstCycle > SUPERVISOR_OPERATION_TEST_DEAD_TIMEOUT))
			{
				bSupervisorOperationDead = 1;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, LOG_TEXT("SupervisorOperation: test dead signal, hardware watchdog should expire soon"));
				/* send dead signal to supervisor */
				CAL_SupervisorOperationDead(s_hOperationDead);
			}
		}

		Result = ERR_OK;
	}
	return Result;
}

