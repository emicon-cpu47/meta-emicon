/**
* <name>RtsInteractive.c</name>
* <description>
*   This example shows the implementation of the interactive login and the wink feature.
*
*   The interactive login is used that a user has to identify this target at login, e.g. with a unique token or the serial number of the target.
*   This is a security level 1 feature to prevent someone to login to a wrong target.
*
*   The wink feature is used to identify a controller e.g. blinking a LED or similar.
*
*   The implementation of both features based on the EVT_CmpDevice_InteractiveLogin event (see CmpDeviceItf.h for details). Following login commands 
*   are specified here in the event parameter (EVTPARAM_CmpDevice_InteractiveLogin.ui32LoginCommand):
*   <ul>
*      <li>DEV_ILC_IDENTIFY: Identify the controller by a wink signal (e.g. blinking a LED)</li>
*      <li>DEV_ILC_LOGIN_REQUEST: Command to initiate the interactive login feature (Login modes: 
*           DEV_ILMF_BLINK = User can use this wink at login to check, if he/she is connected with the correct controller, 
*           DEV_ILMF_ID = User must specify a unique token of the controller, e.g. the serial number. This must be descibed in the corresponding target setting "interactivelogin_id_string", 
*           DEV_ILMF_KEY_PRESS = User must press a key or button on the controller to identify this target)
*      </li>
*      <li>DEV_ILC_LOGIN_POLL_RESULT: Is called cyclically if we return in the DEV_ILC_LOGIN_REQUEST command rLoginResult = ERR_PENDING. An this command is therefore 
*           called cyclically, until the user does the correct identification method (e.g. enter the correct serial number of the controller or pressed the login button on the controller).
*      </li>
*      <li>DEV_ILC_LOGIN_CANCEL: Cancel the interactive login operation</li>
*   </ul>
*
*	USAGE:
*	- InitLoginHandler() must be called out of CH_INIT3 hook
*	- ExitLoginHandler() must be called out of CH_EXIT3 hook
*	- CBDeviceLogin() is the callback function to login to the device
* </description>
*
* <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
*/

#include "CmpStd.h"
#include "CmpDeviceItf.h"

static RTS_HANDLE s_hEventInteractiveLogin = RTS_INVALID_HANDLE;
static void CDECL CBDeviceLogin(EventParam *pEventParam);

/**
* <description>Function to init example at startup of the runtime system.
*	USAGE:
*	- Must be called in CH_INIT3 out of component HookFunction()!
* </description>
* <result>error code</result>
*/
static RTS_RESULT CDECL InitLoginHandler(void)
{
	if (CHK_EventOpen)
	{
		s_hEventInteractiveLogin = CAL_EventOpen(EVT_CmpDevice_InteractiveLogin, CMPID_CmpDevice, NULL);
	}
	if (CHK_EventRegisterCallbackFunction)
	{
		CAL_EventRegisterCallbackFunction(s_hEventInteractiveLogin, CBDeviceLogin, 0);
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
static RTS_RESULT CDECL ExitLoginHandler(void)
{
	if (CHK_EventUnregisterCallbackFunction)
	{
		CAL_EventUnregisterCallbackFunction(s_hEventInteractiveLogin, CBDeviceLogin);
	}
	if (CHK_EventClose)
	{
		CAL_EventClose(s_hEventInteractiveLogin);
	}

	return ERR_OK;
}

/* Variable iWaitCount needed only for simulation a key press. */
static int iWaitCount = 0;

/**
* <description>Callback function that is called at login to the device or if someone pressed the "Wink" button in the communication dialog in CODESYS.</description>
* <param name="pEventParam" type="IN">Pointer to event parameter set.
*   pEventParam->pParameter is a pointer to EVTPARAM_CmpDevice_InteractiveLogin.
* </param>
* <result></result>
*/
static void CDECL CBDeviceLogin(EventParam *pEventParam)
{
	if (pEventParam->EventId == EVT_CmpDevice_InteractiveLogin && pEventParam->usVersion >= EVTVERSION_CmpDevice_InteractiveLogin)
	{
		EVTPARAM_CmpDevice_InteractiveLogin *pParam = (EVTPARAM_CmpDevice_InteractiveLogin *)pEventParam->pParameter;

		switch(pParam->ui32LoginCommand)
		{
			case DEV_ILC_IDENTIFY:
				/* Only used for device identification - triggered by the "wink" command in the CODESYS communication page.
				   For example let a LED blink for a few seconds. 
				*/
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: Identify: blink blink blink ***");
				pParam->rLoginResult = ERR_OK;
				break;
			case DEV_ILC_LOGIN_REQUEST:
				/* A secure login is requested by the client. */
				if (pParam->ui32LoginMode & DEV_ILMF_BLINK)
				{
					/* For example let a LED blink for a few seconds. Callback should return immediatly. */
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: LoginRequest: blink blink blink ***");
					pParam->rLoginResult = ERR_OK;
				}
				if (pParam->ui32LoginMode & DEV_ILMF_ID)
				{
					/* Check the provided data and return the result synchronously.
					   The example code is very simple: A login is successful, if the data start with 'A'. */ 
					if (pParam->pui8LoginData != NULL && pParam->pui8LoginData[0] == 'A')
					{
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: LoginRequest: Login OK ***");
						pParam->rLoginResult = ERR_OK;
					}
					else
					{
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: LoginRequest: ID mismatch ***");
						pParam->rLoginResult = ERR_ID_MISMATCH;
					}
				}
				if (pParam->ui32LoginMode & DEV_ILMF_KEY_PRESS)
				{
					/* Interactive login should be confirmed by a key press on the PLC. Callback should return immediatly with the result.
					   ERR_PENDING. It is again called wit the command DEV_ILC_LOGIN_POLL_RESULT until the runtime system returns anotehr result. */
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: LoginRequest: Waiting for key press ***");
					iWaitCount = 0;
					pParam->rLoginResult = ERR_PENDING;
				}
				break;
			case DEV_ILC_LOGIN_POLL_RESULT:
				/* Polls the result of an asynchronous interactive login operation. Typically this is used for the the login mode DEV_ILMF_KEY_PRESS.
 				   The example implementation simulates a pressed key after 20 poll calls. */
				iWaitCount++;
				if (iWaitCount == 20)
				{
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: poll result: key pressed ***");
					pParam->rLoginResult = ERR_OK;
				}
				else
				{
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: poll result: still wait for key press ***");
					pParam->rLoginResult = ERR_PENDING;
				}
				break;
			case DEV_ILC_LOGIN_CANCEL:
				/* Called if the user or the client cancels the interactive login, to inform the runtime system about that.	*/
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Interactive Login: canceled ***");
				pParam->rLoginResult = ERR_OK;
				break;
			default:
				break;
		}
	}
}
