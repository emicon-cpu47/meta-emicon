/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Loopback CAN Driver Component.
*	Version:
*	Description:	This component is intended to be a template for a
*                   CAN Minidriver component. It loops back all transmit messages
*                   to the receive queue.
******************************************************************************/
#ifdef CAALib
#include "CAADefines.h"
#ifdef CAA_CL2

#include "CmpStd.h"
#include "CmpErrors.h"
#include "CmpItf.h"
#include "CmpLoopbackCanDrvDep.h"

static void StartCommunicationThread(void);
static void StopCommunicationThread(void);
static CAA_ERROR CMD_Setup(CL2I_BYTE byNet);
static CAA_ERROR CMD_Init(CL2I_BYTE byNet, CL2I_WORD wBaudrate);
static CAA_BOOL  CMD_Send(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio, CAA_ERROR* peError);
static CAA_BOOL  CMD_Receive(CL2I_BYTE byNet, CAA_HANDLE hBlock, CAA_ERROR* peError);
static CAA_ERROR CMD_GetInfo(CL2I_BYTE byNet, CMD_INFO* pInfo);
static CAA_ERROR CMD_Dispose(CL2I_BYTE byNet);
static CAA_ERROR CMD_Identify(CL2I_BYTE byNet, CL2I_BYTE byCount);
static CAA_HANDLE CMD_SetBlock(CL2I_BYTE byNet, CL2I_BYTE byIndex, CAA_HANDLE hBlock, CAA_ERROR* peError);
static CAA_ERROR CMD_SetCycle(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwCycle);
static CAA_ERROR CMD_SetMask(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwValue, CL2I_DWORD dwMask);
static CAA_ERROR CMD_ResetAlarm(CL2I_BYTE byNet);
static CAA_ERROR CMD_SetStatus(CL2I_BYTE byNet, CL2I_BYTE byIndicator);

static CMD_CMDRV cmdInterface[] =
{
	{
		CMD_Setup,
		CMD_Init,
		CMD_Send,
		CMD_Receive,
		CMD_GetInfo,
		CMD_Dispose,
		CMD_Identify,
		CMD_SetBlock,
		CMD_SetCycle,
		CMD_SetMask,
		CMD_ResetAlarm,
		CMD_SetStatus
	}
};

#define Loopback_NNET ((unsigned char)1)
#define Loopback_NDRIVER  (sizeof(cmdInterface) / sizeof(CMD_CMDRV))

static CL2I_INFO* s_pInfo[Loopback_NNET] = {CAA_pNULL};

static CMD_INFO cmdInfo	= {
	CMD_SUPPORT_RTRFRAME | CMD_SUPPORT_EXTCOBID	/* support */,
	0		/* maxCycleIndex */,
	0		/* maxMaskIndex */,
	1		/* maxPrio  */,
	0		/* maxLed */
};

static RTS_HANDLE s_hTask;
static int s_bStart = 0;
static CL2I_BYTE s_byDriver[CL2_NNET];
static CL2I_BYTE s_byNet[Loopback_NDRIVER];

static CL2I_BYTE s_byDriverInitOk = 0;

/* Macro to define function pointers of import functions */
USE_STMT

#ifndef RTS_COMPACT_MICRO

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

#ifdef CPLUSPLUS
	if (pInitStruct->pfCMRegisterClass != NULL)
	{
		RTS_HANDLE hClass = pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpLoopbackCanDrv);
		if (hClass == RTS_INVALID_HANDLE)
			return ERR_FAILED;
	}
#endif
	return ERR_OK;
}

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpLoopbackCanDrv)
	{
		CCmpCAACanL2 *pCCmpLoopbackCanDrv = static_cast<CCmpCAACanL2 *>(new CCmpLoopbackCanDrv());
		return (IBase*)pCCmpLoopbackCanDrv->QueryInterface(pCCmpLoopbackCanDrv, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release();
	return ERR_OK;
#else
	return ERR_NOTIMPLEMENTED;
#endif
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT3:
			Loopback_CanMiniDriver_Setup();
			break;
		case CH_INIT_DONE:
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			StartCommunicationThread();
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			if (s_bStart && s_hTask == RTS_INVALID_HANDLE)
			{
				Loopback_CanMiniDriver_Handler();
			}
			break;

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			StopCommunicationThread();
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_PRE_EXIT:
			break;
		case CH_EXIT:
		{
			EXIT_STMT;
			break;
		}
		case CH_EXIT3:
			Loopback_CanMiniDriver_Dispose();
			break;
		case CH_EXIT_SYSTEM:
			break;
#endif

		default:
			break;
	}
	return ERR_OK;
}
	
void CDECL PCANCommunicationThread(SYS_TASK_PARAM *ptp)
{
	CAL_SysTaskEnter(ptp->hTask);

	while(!ptp->bExit)
	{
		Loopback_CanMiniDriver_Handler();
		CAL_SysTaskWaitSleep(ptp->hTask, 1);
	}
	CAL_SysTaskLeave(ptp->hTask);
	CAL_SysTaskEnd(ptp->hTask, 0);
}


RTS_RESULT PCANExceptionHandler(RTS_HANDLE hTaskHandle, RTS_UI32 ulException, RegContext Context)
{
	SYS_TASK_INFO *pTask = (SYS_TASK_INFO *)hTaskHandle;
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_EXCEPTION, ulException, 0, "*EXCEPTION* <Task>%s</Task> <IP>0x%x</IP> <BP>0x%x</BP> <SP>0x%x</SP>", CAL_SysTaskGetName((RTS_HANDLE)pTask, NULL), Context.IP, Context.BP, Context.SP);
	StartCommunicationThread();
	return ERR_OK;
}

static void StartCommunicationThread(void)
{
	s_bStart = 1;
	if (CHK_SysTaskCreate && CHK_SysTaskResume && CHK_SysTaskGetName)
	{
		RTS_RESULT Result;
		s_hTask = CAL_SysTaskCreate(RTS_TASKNAME_PCANCOMMTHREAD, PCANCommunicationThread, NULL, RTS_TASKPRIO_PCANCOMMTHREAD, 0, 0, PCANExceptionHandler, &Result);
		Result = CAL_SysTaskResume(s_hTask);
	}
}

static void StopCommunicationThread(void)
{
	s_bStart = 0;
	if (s_hTask != RTS_INVALID_HANDLE)
	{
		CAL_SysTaskSetExit(s_hTask);
		CAL_SysTaskExit(s_hTask, 100);
		s_hTask = RTS_INVALID_HANDLE;
	}
}

static CAA_ERROR CMD_Setup(CL2I_BYTE byNet)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_Init(CL2I_BYTE byNet, CL2I_WORD wBaudrate)
{
	if(!s_byDriverInitOk)
	{
		s_byDriverInitOk = 1;
		return CMD_NO_ERROR;
	}
	return CMD_SETUP_ERROR;
}

static CAA_BOOL CMD_Send(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio, CAA_ERROR* peError)
{
	CAA_HANDLE hReceiveBlock;
	CL2I_BLOCK* pSendBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(hBlock);
	CAA_SET_RESULT(peError, CMD_NO_ERROR);

	/* Loopback the sent message. Normally this code is part of the minidriver handler or Rx interrupt handler */
	hReceiveBlock = CAL_CL2_MsgAlloc(s_byDriver[0], CAA_pNULL); /* allocate a receive message */
	if(hReceiveBlock)
	{
		CL2I_BLOCK* pReceiveBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(hReceiveBlock);
		char buf1[256];
		char buf2[256];
		int i;

		pReceiveBlock->cobId.X.ID = pSendBlock->cobId.X.ID;;
		pReceiveBlock->cobId.X.RTR = pSendBlock->cobId.X.RTR;
		pReceiveBlock->cobId.X.EID = pSendBlock->cobId.X.EID;
		pReceiveBlock->byLen.X.DLC = pSendBlock->byLen.X.DLC;
		if(!pSendBlock->cobId.X.RTR)
			memcpy(&pReceiveBlock->byData[0], &pSendBlock->byData[0], (pSendBlock->byLen.X.DLC > 8) ? 8 : pSendBlock->byLen.X.DLC);
		
		memset(buf1, 0, sizeof(buf1));
		memset(buf2, 0, sizeof(buf2));
		sprintf(buf1,
			"ID:16#%08x EID:16#%01x RTR:16#%01x TX:16#%01x DLC:16#%01x",
			pReceiveBlock->cobId.X.ID,
			pReceiveBlock->cobId.X.EID,
			pReceiveBlock->cobId.X.RTR,
			pReceiveBlock->cobId.X.TX,
			pSendBlock->byLen.X.DLC);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 0, 0, "LoopbackCanDrv: CMD_Send(): %s", buf1);
		memset(buf1, 0, sizeof(buf1));
		for(i=0; i < pSendBlock->byLen.X.DLC; i++) {
			sprintf(buf2, " by[%u]:16#%02x", (unsigned int)i, pSendBlock->byData[i]);
			strcat(buf1, buf2);
		}
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 0, 0, "LoopbackCanDrv:           : %s", buf1);
		
		s_pInfo[s_byDriver[0]]->ctMessagesReceived++;
		CAL_CL2_MsgPutRQueue(s_byNet[0], hReceiveBlock); /* put message into receive queue */
	}
	else
	{
		s_pInfo[s_byDriver[0]]->ctDataOverruns++;
	}

	s_pInfo[s_byDriver[byNet]]->ctMessagesSend++;

	/*
	This function call signals that message hBlock has being sent now. Don't call it if sending wasn't successful!!!
	For drivers with IRQ use CAL_CL2_MsgSendAckIRQ and call it in the corresponding Tx IRQ handler.
	After calling this function don't use hBlock anymore!!!
	*/
	CAL_CL2_MsgSendAcknNoIRQ(byNet, hBlock);

	/*
	RETURN VALUE:
	case 1: Message was sent successfully
	==> Return value CMD_SND_OK
	If there are more messages in transmit queue CL2 calls this function again afterwards.

	case 2: Message can not be sent at the moment (e.g. CAN chip is not free)
	==> Return CMD_SND_NOT_OK and eError=CMD_NO_ERROR.
	The message will be queued by CL2. 
	For drivers with Tx IRQ: 
	  A retry is triggered when CAL_CL2_MsgSendAcknIRQ in Tx IRQ is called.
	For drivers without Tx IRQ: 
	  Drivers without Tx IRQ have to call CAL_CL2_MsgSendAcknNoIRQ with hBlock=CAA_hINVALID to signal that sending is possible now.

	case 3: An error occurred. Message should be dismissed.
	==> Return CMD_SND_NOT_OK and eError <> CMD_NO_ERROR.
	*/

	return CMD_SND_OK;
}

static CAA_BOOL CMD_Receive(CL2I_BYTE byNet, CAA_HANDLE hBlock, CAA_ERROR* peError)
{
	CAA_SET_RESULT(peError, CMD_NO_ERROR);
	return CMD_NO_MORE_DATA;
}

static CAA_ERROR CMD_GetInfo(CL2I_BYTE byNet, CMD_INFO* pInfo)
{
	if(pInfo)
	{
		memcpy((void*)pInfo, (void*)&cmdInfo, sizeof(CMD_INFO));
	}
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_Dispose(CL2I_BYTE byNet)
{
	s_byDriverInitOk = 0;
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_Identify(CL2I_BYTE byNet, CL2I_BYTE byCount)
{
	return CMD_NO_ERROR;
}

static CAA_HANDLE CMD_SetBlock(CL2I_BYTE byNet, CL2I_BYTE byIndex, CAA_HANDLE hBlock, CAA_ERROR* peError)
{
	CAA_SET_RESULT(peError, CMD_NO_ERROR);
	return CAA_pNULL;
}

static CAA_ERROR CMD_SetCycle(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwCycle)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_SetMask(CL2I_BYTE byNet, CL2I_BYTE byIndex, CL2I_DWORD dwValue, CL2I_DWORD dwMask)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_ResetAlarm(CL2I_BYTE byNet)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_SetStatus(CL2I_BYTE byNet, CL2I_BYTE byIndicator)
{
  return CMD_NOT_IMPLEMENTED;
}

int CAAFKT Loopback_CanMiniDriver_Setup(void)
{
	CL2I_BYTE byDriver;
	CL2I_BYTE byNet;
	CL2I_BYTE byLastNet = 0;
	CAA_ERROR eError;

	for(byDriver=0; byDriver < Loopback_NDRIVER; byDriver++)
	{
		for(byNet=byLastNet; byNet < CL2_NNET; byNet++)
		{
			s_byDriver[byNet] = byDriver;
			s_byNet[byDriver] = byNet;
			eError = CAL_CL2_CmdRegister(byNet, &cmdInterface[byDriver], CL2_NRXMSG, &s_pInfo[s_byDriver[byNet]]);
			if(eError == CL2_NO_ERROR)
			{
				byLastNet = (CL2I_BYTE)(byNet + 1);
				break;
			}
			else
			{
				s_byDriver[byNet] = Loopback_NDRIVER;
				s_byNet[byDriver] = Loopback_NNET;
			}
		}
	}
	return 0;
}

int CAAFKT Loopback_CanMiniDriver_Dispose(void)
{
	CL2I_BYTE byDriver;

	for(byDriver=0; byDriver < Loopback_NDRIVER; byDriver++)
	{
		CAL_CL2_CmdUnRegister(s_byNet[byDriver]);
		s_byDriver[s_byNet[byDriver]] = Loopback_NDRIVER;
		s_byNet[byDriver] = Loopback_NNET;

	}
	return 0;
}

void CAAFKT Loopback_CanMiniDriver_Handler(void)
{
	if(s_byDriverInitOk)
	{
		/*The following call is used to check the Tx Queue if there are any messages to send.
		Note: It is only needed in case CMD_Send returns an error (e.g. if CAN chip is not free)
		*/
		CAL_CL2_MsgSendAcknNoIRQ(s_byNet[0], CAA_hINVALID);
	}
}
			
#endif /* CAA_CL2 */
#endif /* CAALib */
