/*
 * Компонент определяет режим эмуляции ПЛК и предоставляет интерфейс для
 * определения режима другим компонентам.
 * Режим эмуляции определяется по наличию переменной окружения EMU.
 */

#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconEmuDep.h"

/*
 * EMU_ENV_VAR - параметр окружения по наличию которого определяется режим
 * эмуляции. 
 */

#define EMU_ENV_VAR "EMU"

USE_STMT

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = NULL;
	pInitStruct->pfDeleteInstance = NULL;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	return ERR_OK;
}

static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}


static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook) {
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		break;

	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;
	default:
		break;
	}
	return ERR_OK;
}

bool CDECL CmpEmiconEmu_is_emu(void)
{
	char *env_emu = NULL;
	env_emu = getenv(EMU_ENV_VAR);
	return true;
}
