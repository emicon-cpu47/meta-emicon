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
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define EMLOG_ASCII_FILE "/dev/emlogascii"
#define READ_BUF_SIZE 300

USE_STMT

static void CDECL PlcCmdEmlogRead(EventParam *pEventParam);
static void CDECL PlcCmdEmlogMkfile(EventParam *pEventParam);
static void CDECL PlcCmdEmlogSync(EventParam *pEventParam);
static void CDECL PlcCmdEmlogClear(EventParam *pEventParam);
static void CDECL PlcCmdEmMemToFile(EventParam *pEventParam);
static void CDECL PlcCmdEmFileToMem(EventParam *pEventParam);

static void Init_PLCShellCommands(void);
static void Exit_PLCShellCommands(void);

/* Entry of the PLC Command Table */
typedef struct PlcShellCommand_s {
	char* pszName;
	char* pszHelp;
	PFEVENTCALLBACKFUNCTION pfCallback;
	int bIec;
} PlcShellCommand_t;


static PlcShellCommand_t s_shellCommands[] = {
	{"emlogclear", "emlogclear\r\n\tОчистка буфера лога.", PlcCmdEmlogClear,
									0},
	{"sync", "sync\r\n\tВызов системного sync.", PlcCmdEmlogSync, 0},
	{"emlogread", "emlogread\r\n\tЧтение лога.", PlcCmdEmlogRead, 0},
	{"emlogmkfile", "emlogmkfile\r\n\tСоздает файлы лога на ПЛК.",
							PlcCmdEmlogMkfile, 0},
	{"em_mem_to_file",
	 "PlcCmdEmMemToFile\r\n\tЗаписывает %M память в файл mem_dump.",
	 PlcCmdEmMemToFile, 0},

	{"em_file_to_mem",
	 "PlcCmdEmFileToMem\r\n\tСчитывает файл mem_dump в %M память.",
	 PlcCmdEmFileToMem, 0},

	{NULL, NULL, NULL, 0}
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
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT3:
			Init_PLCShellCommands();
			break;
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
			Exit_PLCShellCommands();
			break;
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

static const char* InfoTextForPlcCmdEmlogClear = {
	"Очищает буфер лога и вносит запись об очистке."
};

static void CDECL PlcCmdEmlogClear(EventParam *pEventParam) {

	EVTPARAM_PlcShellCommand *pCommand;
	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "emlogclear"))
		return;

	if (strstr(pCommand->pszArguments, "?") != NULL) {
		CAL_PlcShellAppend(InfoTextForPlcCmdEmlogClear,
				   pCommand->iBlockID);
		return;
	}

	clr_sys_log_struct p;
	CAL_clr_sys_log(&p);
	switch (p.clr_sys_log){
	case 1:
		CAL_PlcShellAppend("Error: The buffer is not initialized!",
				   pCommand->iBlockID);
		break;
	
	default:
		CAL_PlcShellAppend("clear done!", pCommand->iBlockID);
		break;

	}

	

	return;
}

static const char* InfoTextForPlcCmdEmlogSync =
{
	"Вызывает системную команду sync."
};

static void CDECL PlcCmdEmlogSync(EventParam *pEventParam) {

	EVTPARAM_PlcShellCommand *pCommand;
	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "sync"))
		return;

	if (strstr(pCommand->pszArguments, "?") != NULL) {
		CAL_PlcShellAppend(InfoTextForPlcCmdEmlogSync,
				   pCommand->iBlockID);
		return;
	}

	sync();
	
	CAL_PlcShellAppend("sync done!", pCommand->iBlockID);

	return;
}

static const char* InfoTextForPlcCmdEmlogRead = {
	"Команда выдает весь лог в текстовом виде, вызывается без параметров."
};

static void CDECL PlcCmdEmlogRead(EventParam *pEventParam) {
	int i;
	int fd;
	int flags;
	get_next_log_item_struct data;

	char buffer[READ_BUF_SIZE];

	data.log_str = buffer;

	EVTPARAM_PlcShellCommand *pCommand;
	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "emlogread"))
		return;

	if (strstr(pCommand->pszArguments, "?") != NULL) {
		CAL_PlcShellAppend(InfoTextForPlcCmdEmlogRead,
							pCommand->iBlockID);
		return;
	}


	data.get_first = 1;
	CAL_get_next_log_item(&data);
	CAL_PlcShellAppend(buffer, pCommand->iBlockID);
	data.get_first = 0;

	while (data.get_next_log_item == 1) {
		CAL_get_next_log_item(&data);
		CAL_PlcShellAppend(buffer, pCommand->iBlockID);
	}

}


static const char* InfoTextForPlcCmdEmlogMkfile = {
	"Option to extend the help text."
};

static void CDECL PlcCmdEmlogMkfile(EventParam *pEventParam) {
	create_log_files_struct p;
	char buffer[100];
	

	EVTPARAM_PlcShellCommand *pCommand;

	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "emlogmkfile"))
		return;
	
	if (strstr(pCommand->pszArguments, "?") != NULL) {
		CAL_PlcShellAppend(InfoTextForPlcCmdEmlogMkfile,
				   pCommand->iBlockID);
		return;
	}

	CAL_create_log_files(&p);
	
	switch (p.create_log_files){
	case -1:
		sprintf(buffer, "Error: The buffer is not initialized!\n");
		break;
	case -2:
		sprintf(buffer, "Error: Type of record is not correct!\n");
		break;
	case -3:
		sprintf(buffer, "Error: The buffer's structue is damaged!\n");
		break;
	default:
		sprintf(buffer, "files created\n");
		break;

	}


	CAL_PlcShellAppend(buffer, pCommand->iBlockID);
}


static void Init_PLCShellCommands(void)
{
	/* Register all static command handlers */
	int i;

	if (!CHK_PlcShellRegister)
		return;

	for (i = 0; s_shellCommands[i].pszName != NULL; i++) {
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

	for (i = 0; s_shellCommands[i].pszName != NULL; i++) {
		CAL_PlcShellUnregister(s_shellCommands[i].pfCallback);
	}
}

static const char* InfoTextForPlcCmdMemToFile =
{
	"\tWrites %M are to file mem_dump. \n\
	Example: em_mem_to_file [from_byte] [to_byte]\n\
	If parameters from_byte and to_byte are absent or equal zero then all %M area is written.",
};

static void CDECL PlcCmdEmMemToFile(EventParam *pEventParam) {
	int res;
	char *p;
	long int i = 0;
	long int param[2] = {0, 0};
	char *end;
	int j = 0;


	EVTPARAM_PlcShellCommand *pCommand;
	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "em_mem_to_file"))
		return;

	if (strstr(pCommand->pszArguments, "?") != NULL) {
		CAL_PlcShellAppend(InfoTextForPlcCmdMemToFile,
				   pCommand->iBlockID);
		return;
	}

	p = strdup(pCommand->pszArguments);

	for (i = strtol(p, &end, 10); p != end && j < 2;
						i = strtol(p, &end, 10)) {
		p = end;
		if (errno == ERANGE) {
			printf("range error, got ");
			errno = 0;
		} else {
			param[j] = i;
		}
		j++;
	}

	if (param[0] > param[1] || param[0] < 0) {
		CAL_PlcShellAppend("parameters error", pCommand->iBlockID);
		return;
	}

	res = CAL_CmpEmiconMemManager_mem_to_file(param[0], param[1]);

	switch (res) {
	case -1:
		CAL_PlcShellAppend("Open file failed!", pCommand->iBlockID);
	break;

	case -2:
		CAL_PlcShellAppend("Writing file failed!", pCommand->iBlockID);

	case -3:
		CAL_PlcShellAppend("Fail - Violation of memory boundaries!",
							pCommand->iBlockID);
	break;
	}

	
	CAL_PlcShellAppend("Done!", pCommand->iBlockID);

	return;
}

static const char* InfoTextForPlcCmdFileToMem =
{
	"Reads file mem_dump to %M memory."
};

static void CDECL PlcCmdEmFileToMem(EventParam *pEventParam){
	int res;

	EVTPARAM_PlcShellCommand *pCommand;
	pCommand = (EVTPARAM_PlcShellCommand*) pEventParam->pParameter;
	if(strcmp(pCommand->pszCommand, "em_file_to_mem"))
		return;

	if (strstr(pCommand->pszArguments, "?") != NULL) {
		CAL_PlcShellAppend(InfoTextForPlcCmdFileToMem,
				   pCommand->iBlockID);
		return;
	}

	res = CAL_CmpEmiconMemManager_file_to_mem();

	switch (res) {
	case -1:
		CAL_PlcShellAppend("Open file failed!", pCommand->iBlockID);
	break;

	case -2:
		CAL_PlcShellAppend("File size is bigger then the memory area!",
				   pCommand->iBlockID);
	break;

	case -3:
		CAL_PlcShellAppend("Reading file failed!", pCommand->iBlockID);
	break;
	
	default:
		CAL_PlcShellAppend("Done!", pCommand->iBlockID);
	break;
	}
	
	return;
}
