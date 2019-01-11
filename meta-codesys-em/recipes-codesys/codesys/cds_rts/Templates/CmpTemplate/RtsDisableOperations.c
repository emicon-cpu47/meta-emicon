/**
 * <name>RtsDisableOperations.c</name>
 * <description> 
 *	Example to disable single/all operations in a critical machine state, that can disturb the operating of the machine like setting a breakpoint or do an OnlineChange.
 *
 *	USAGE:
 *	- InitDisableOperations() must be called out of CH_INIT3 hook	
 *	- ExitDisableOperations() must be called out of CH_EXIT3 hook	
 *	- CBDisableOperations() is the callback function to disable single operations
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
#include "CmpStd.h"
#include "CMItf.h"
#include "CmpAppItf.h"

/* Handle to the operation event */
static RTS_HANDLE s_hEventDisableOperations = RTS_INVALID_HANDLE;

static void CDECL CBDisableOperations(EventParam *pEventParam);

/**
 * <description>Function to init example at startup of the runtime system.
 *	USAGE:
 *	- Must be called in CH_INIT3 out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CDECL InitDisableOperations(void)
{
	if (CHK_EventOpen && CHK_EventRegisterCallbackFunction)
	{
		RTS_RESULT Result;

		s_hEventDisableOperations = CAL_EventOpen(EVT_CmpMgr_DisableOperation, CMPID_CM, &Result);
		CAL_EventRegisterCallbackFunction(s_hEventDisableOperations, CBDisableOperations, 0);
	}
	return ERR_OK;
}

/**
 * <description>Function to exit example code at shutdown of the runtime system.
 *	USAGE:
 *	- Must be called in CH_EXIT3 out of component HookFunction()!
 * <result>error code</result>
 */
static RTS_RESULT CDECL ExitDisableOperations(void)
{
	if (CHK_EventClose && CHK_EventUnregisterCallbackFunction)
	{
		CAL_EventUnregisterCallbackFunction(s_hEventDisableOperations, CBDisableOperations);
		CAL_EventClose(s_hEventDisableOperations);
		s_hEventDisableOperations = RTS_INVALID_HANDLE;
	}
	return ERR_OK;
}

/**
 * <description>Callback function to disable single operations</description>
 * <param name="pEventParam" type="IN">Pointer to event parameter set.
 *	pEventParam->pParameter is a pointer to EVTPARAM_CmpMgr_DisableOperation. And with the member bDisable = 1 you can disable this operation! 
 * </param> 
 * <result></result>
 */
static void CDECL CBDisableOperations(EventParam *pEventParam)
{
	if (pEventParam->CmpIdProvider == CMPID_CM)
	{
		switch (pEventParam->EventId)
		{
			case EVT_CmpMgr_DisableOperation:
			{
				EVTPARAM_CmpMgr_DisableOperation *pParam = (EVTPARAM_CmpMgr_DisableOperation *)pEventParam->pParameter;
				if (pParam->cmpId == CMPID_CmpApp)
				{
					switch (pParam->ulOperation)
					{
						case OP_APP_STOP:
						case OP_APP_DOWNLOAD:
						case OP_APP_ONLINECHANGE:
						case OP_APP_WRITE_VARIABLES:
						case OP_APP_FORCE_VARIABLES:
						case OP_APP_SET_BREAKPOINT:
						case OP_APP_RESET:
						case OP_APP_DELETE_APPLICATION:
						{
							/*
							* TODO:
							* With the following line, the corresponding application operations can be disabled during a critical state:
							* pParam->bDisable = 1;
							*/
							break;
						}
					}
					break;
				}
				else if (pParam->cmpId == CMPID_CmpFileTransfer)
				{
					switch (pParam->ulOperation)
					{
						case OP_FILE_TRANSFER_DOWNLOAD:
						case OP_FILE_TRANSFER_UPLOAD:
						{
							/*
							* TODO:
							* With the following line, the filetransfer can be disabled during a critical state:
							* pParam->bDisable = 1;
							*/
							break;
						}
					}
					break;
				}
				break;
			}
			default:
				break;
		}
	}
}
