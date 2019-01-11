/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Test component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpPlcShellHandlerDep.h"

USE_STMT

static void CDECL PlcCmdSimple(EventParam *pEventParam);
static void CDECL PlcCmdAdvanced(EventParam *pEventParam);

static void Init_PLCShellCommands(void);
static void Exit_PLCShellCommands(void);
static void Init_EventHandler(void);
static void Exit_EventHandler(void);
static void CDECL CBPlcShellCommandRegister(EventParam *pEventParam);

static RTS_HANDLE s_hCommandRegisterEvent = RTS_INVALID_HANDLE;

/* Entry of the PLC Command Table */
typedef struct PlcShellCommand_s {
	char* pszName;
	char* pszHelp;
	PFEVENTCALLBACKFUNCTION pfCallback;
	int bIec;
} PlcShellCommand_t;


static PlcShellCommand_t s_shellCommands[] =
{
	{ "simple", "simple\r\n\tAn example of a simple and inperformant PlcShell Handler.", PlcCmdSimple, 0 },
	{ "advanced", "advanced\r\n\tSame example as 'simple', but with intelligent buffer handling.", PlcCmdAdvanced, 0 },
	{ NULL, NULL, NULL, 0 }
};

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

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpPlcShellHandler);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpPlcShellHandler)
	{
		CCmpPlcShellHandler *pCCmpPlcShellHandler = static_cast<CCmpPlcShellHandler *>(new CCmpPlcShellHandler());
		return (IBase*)pCCmpPlcShellHandler->QueryInterface(pCCmpPlcShellHandler, ITFID_IBase, pResult);
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
		{
			Init_PLCShellCommands();
			Init_EventHandler();
			break;
		}
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			break;

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
		{
			Exit_PLCShellCommands();
			Exit_EventHandler();
			break;
		}
		case CH_EXIT:
		{
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
#endif

		default:
			break;
	}
	return ERR_OK;
}


static const char* InfoTextForPlcCmdSimple =
{
	"Option to extend the help text."
};

/*****************************************************************************
 * This is a simple (stupid) command, which dumps more than one communication
 * buffer, but doesn't care about that. The buffer handling is done by the
 * PlcShell.
 */
static void CDECL PlcCmdSimple(EventParam *pEventParam) {
	int i;
	EVTPARAM_PlcShellCommand *pCommand;

	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "simple"))
	   return;

	if (strstr(pCommand->pszArguments, "?") != NULL)
	{
		CAL_PlcShellAppend(InfoTextForPlcCmdSimple, pCommand->iBlockID);
		return;
	}

	for(i=0; i < 10000; i++) {
		char buffer[64];
		sprintf(buffer, "line #%05u\r\n", i);
		CAL_PlcShellAppend(buffer, pCommand->iBlockID);
	}
}


static const char* InfoTextForPlcCmdAdvanced =
{
	"Option to extend the help text."
};
/*****************************************************************************
 * This is an advanced command handler, with intelligent buffer handling.
 */
static void CDECL PlcCmdAdvanced(EventParam *pEventParam) {
	int i, i1, i2;
	EVTPARAM_PlcShellCommand *pCommand;

	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "advanced"))
	   return;
	
	if (strstr(pCommand->pszArguments, "?") != NULL)
	{
		CAL_PlcShellAppend(InfoTextForPlcCmdAdvanced, pCommand->iBlockID);
		return;
	}

	i1 = (pCommand->uiBlockSize * pCommand->iBlockID) / 16;
	i2 = (pCommand->uiBlockSize * (pCommand->iBlockID + 1)) / 16;
	
	i2 = (i2 > 10000) ? 10000 : i2;
	
	CAL_PlcShellSkip(pCommand->iBlockID);
	for(i=i1; i < i2; i++) {
		char buffer[64];
		sprintf(buffer, "line #%05u   \r\n", i);
		CAL_PlcShellAppend(buffer, pCommand->iBlockID);
	}
	CAL_PlcShellSetEof(10000 * 16);
}


static void Init_PLCShellCommands(void)
{
	/* Register all static command handlers */
	int i;

	if (!CHK_PlcShellRegister)
		return;

	for (i = 0; s_shellCommands[i].pszName != NULL; i++)
	{
		CAL_PlcShellRegister(
			s_shellCommands[i].pszName,
			s_shellCommands[i].pszHelp,
			s_shellCommands[i].pfCallback,
			s_shellCommands[i].bIec);
	}
}


static void Exit_PLCShellCommands(void)
{
	/* Unregister all static command handlers*/
	int i;

	if (!CHK_PlcShellUnregister)
		return;

	for (i = 0; s_shellCommands[i].pszName != NULL; i++)
	{
		CAL_PlcShellUnregister(s_shellCommands[i].pfCallback);
	}
}

static void Init_EventHandler(void)
{
	RTS_RESULT Result;

	if (CHK_EventOpen && CHK_EventRegisterCallbackFunction)
	{
		s_hCommandRegisterEvent = CAL_EventOpen(EVT_PlcShellCommandRegister, CMPID_CmpPlcShell, &Result);
		CAL_EventRegisterCallbackFunction(s_hCommandRegisterEvent, CBPlcShellCommandRegister, 0);
	}
}
static void Exit_EventHandler(void)
{
	if (CHK_EventUnregisterCallbackFunction)
		CAL_EventUnregisterCallbackFunction(s_hCommandRegisterEvent, CBPlcShellCommandRegister);
}

static void CDECL CBPlcShellCommandRegister(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{
	case EVT_PlcShellCommandRegister:
		{
			EVTPARAM_PlcShellCommandRegister *pParam = (EVTPARAM_PlcShellCommandRegister *)pEventParam->pParameter;

			/* disable the command "mem" in the PlcShell */
			if (strcmp(pParam->pszCommand, "mem") == 0)
				pParam->bDisable = 1;

			break;
		}
	default:
		break;
	}
}