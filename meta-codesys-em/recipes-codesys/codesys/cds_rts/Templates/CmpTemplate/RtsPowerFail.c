/**
 * <name>RtsDisableOperations.c</name>
 * <description> 
 *	Example to handle power fail conditions.
 *
 *	USAGE:
 *	- InitPowerFail() must be called out of CH_INIT3 hook	
 *	- ExitPowerFail() must be called out of CH_EXIT3 hook	
 *	- CBHandlePowerFail() is the callback function to handle power fail condition
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
#include "CmpStd.h"
#include "CMItf.h"
#include "CmpAppItf.h"

/**
 * <category>Static defines</category>
 * <description>Power fail options</description>
 */
#define SHUTDOWN_FAST			1
#define SHUTDOWN_STANDARD		2
#define SHUTDOWN_FULL			3


RTS_RESULT CBHandlePowerFail(RTS_UI32 shutdownOption);


/**
 * <description>Function to register the callback function CBHandlePowerFail() at the power fail handler.
 *	USAGE:
 *	- Must be called in CH_INIT3 out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL InitPowerFail(void)
{
	/*
	* TODO:
	* Add the handler CBHandlePowerFail() to PowerFail signal.
	*/
	return ERR_OK;
}

/**
 * <description>Function to unregister the callback function CBHandlePowerFail() from the power fail handler.
 *	USAGE:
 *	- Must be called in CH_EXIT3 out of component HookFunction()!
 * <result>error code</result>
 */
static RTS_RESULT CDECL ExitPowerFail(void)
{
	/*
	* TODO:
	* Remove the handler CBHandlePowerFail() from PowerFail signal.
	*/
	return ERR_OK;
}

/**
 * <description>Callback function to handle power fail signal</description>
 * <param name="shutdownOption" type="IN">Shutdown option. Depends on the hold time of the power supply
 *	SHUTDOWN_FAST: This should be used, if the power supply only holds less time.
 *	SHUTDOWN_STANDARD: This should be used, if the power supply holds enough time to stop application and save retains.
 *	SHUTDOWN_FULL: This should be used, if the power enough supply holds enough time to fully shutdown the runtime.
 * </param> 
 * <result>Error code</result>
 */
RTS_RESULT CDECL CBHandlePowerFail(RTS_UI32 shutdownOption)
{
	switch (shutdownOption)
	{
		case SHUTDOWN_FAST:
		{
			/* This is the hard way only to store the retains. Here no cycle consistency of the IEC data can be guaranteed!!! 
			 * This should be used, if the power supply only holds less time.
			 */
			return CAL_AppSaveAllRetainAreas();
		}
		case SHUTDOWN_STANDARD:
		{
			/* This is the standard way to store retains. All applications are stoppend and after this the retains are saved.
			 * This should be used, if the power supply only holds less time.
			 */
			RTS_RESULT result = CAL_AppStopApplications(RTS_TIMEOUT_DEFAULT, APP_STOP_REASON_SHUTDOWN);
			result = RTS_GETRESULT( CAL_AppSaveAllRetainAreas(), result);
			return result;
		}
		case SHUTDOWN_FULL:
		{
			/* If there is enough time to completeley shutdown the runtime (e.g. with a UPS), this is the correct sequence to fully shutdown the runtime system */
			return CAL_CMExit();
		}
		default:
			break;
	}
	return ERR_NOT_SUPPORTED;
}
