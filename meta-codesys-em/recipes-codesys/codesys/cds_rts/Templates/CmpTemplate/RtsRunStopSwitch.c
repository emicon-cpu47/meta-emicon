/**
 * <name>RtsRunStopSwitch.c</name>
 * <description> 
 *	Example to handle a run/stop switch on the controller.
 *
 *	USAGE:
 *		- CH_INIT3: call InitRunStopSwitch() from your component hook function
 *		- CH_EXIT3: call ExitRunStopSwitch from your component hook	function
 *		- CH_COMM_CYCLE: call CyclicRunStopSwitch() from your component hook function
 *		- PollRunStopSwitch(): Implement the polling routines for the RunStop Switch state here
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"
#include "CmpAppItf.h"

static RTS_HANDLE s_hEventRSSDenyStart = RTS_INVALID_HANDLE;
static RTS_I32 s_bRun = 1;

static void CDECL CBDenyStart(EventParam *pEventParam);
static RTS_I32 PollRunStopSwitch(void);

/**
 * <description>Function to init example at startup of the runtime system.
 *	USAGE:
 *	- Must be called in CH_INIT3 out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL InitRunStopSwitch(void)
{
	if (CHK_EventOpen && CHK_EventRegisterCallbackFunction)
	{
		RTS_RESULT Result;

		s_hEventRSSDenyStart = CAL_EventOpen(EVT_DenyStart, CMPID_CmpApp, &Result);
		CAL_EventRegisterCallbackFunction(s_hEventRSSDenyStart, CBDenyStart, 0);
	}
	return ERR_OK;
}

/**
 * <description>Function to exit example code at shutdown of the runtime system.
 *	USAGE:
 *	- Must be called in CH_EXIT3 out of component HookFunction()!
 * </description> 
 * <result>error code</result>
 */
static RTS_RESULT CDECL ExitRunStopSwitch(void)
{
	if (CHK_EventClose && CHK_EventUnregisterCallbackFunction)
	{
		CAL_EventUnregisterCallbackFunction(s_hEventRSSDenyStart, CBDenyStart);
		CAL_EventClose(s_hEventRSSDenyStart);
		s_hEventRSSDenyStart = RTS_INVALID_HANDLE;
	}
	return ERR_OK;
}

/**
 * <description>Function to poll cyclically the state of the run/stop switch and to react correctly.
 *	USAGE:
 *	- Must be cyclically. Can be called e.g. from CH_COMM_CYCLE.
 * </description> 
 * <result>error code</result>
 */
static RTS_RESULT CDECL CyclicRunStopSwitch(void)
{
	RTS_I32 state = PollRunStopSwitch();
	if (state != s_bRun)
	{
		if (state)
		{
			CAL_AppStartApplications();
		}
		else
		{
			CAL_AppStopApplications(RTS_TIMEOUT_DEFAULT, APP_STOP_REASON_RUNSTOP_SWITCH);
		}
	}
	s_bRun = state;
	return ERR_OK;
}

/**
 * <description>Callback function to prevent from starting applications, if switch is in STOP position!
 * <param name="pEventParam" type="IN">Pointer to event parameter set.</param>  
 * <result></result>
 */
static void CDECL CBDenyStart(EventParam *pEventParam)
{
	if (pEventParam->CmpIdProvider == CMPID_CmpApp)
	{
		switch (pEventParam->EventId)
		{
			case EVT_DenyStart:
			{
				EVTPARAM_CmpAppDenyStart *pParam = (EVTPARAM_CmpAppDenyStart *)pEventParam->pParameter;
				
				if (!PollRunStopSwitch())
					pParam->bDeny = 1;
			}
			default:
				break;
		}
	}
}

/**
 * <description>Function to get the actual state of the run/stop switch. Is called cyclically from CyclicRunStopSwitch().</description> 
 * <result>
 *  0 = switch is in stop state
 *  1 = switch is in run state
 * </result>
 */
static RTS_I32 PollRunStopSwitch(void)
{
	/*
	* TODO:
	* Poll the state of the run stop switch:
	* return 1: switch is in run
	* return 0: switch is in stop
	*/	
	
	static RTS_I32 s_bRunStopSwitch = 1;
	/* Here you can simulate the state of the RunStop switch by writing the value of s_bRunStopSwitch in debugger. */
	return s_bRunStopSwitch;
}
