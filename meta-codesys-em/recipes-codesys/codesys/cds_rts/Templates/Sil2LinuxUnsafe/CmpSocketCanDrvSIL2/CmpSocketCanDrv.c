/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Socket Can Mini Driver component
*	Version:
*	Description:
******************************************************************************/

#ifdef CAALib
#include "CAADefines.h"
#ifdef CAA_CL2

#include "CmpSocketCanDrvDep.h"

/* External API's */
USE_STMT

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpSocketCanDrv)
	{
		CCmpSocketCanDrv *pCCmpSocketCanDrv = static_cast<CCmpSocketCanDrv *>(new CCmpSocketCanDrv());
		return (IBase*)pCCmpSocketCanDrv->QueryInterface(pCCmpSocketCanDrv, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase * hIBase)
{
#ifdef CPLUSPLUS
	IBase *pBase = (IBase *)hIBase;
	pBase->Release();
	return ERR_OK;
#else
	return ERR_NOTIMPLEMENTED;
#endif
}

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
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;

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

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:

			break;
		case CH_INIT3:
			{
				CAA_ERROR eError;
				/*Now register all the nets at CL2.*/
				eError = Socket_CanMiniDriver_Setup();
				if(eError != CL2_NO_ERROR)
				{
					return ERR_PENDING;
				}
				if(eError != CL2_NO_ERROR)
				{
					return ERR_PENDING;
				}
			}
			break;
		case CH_INIT_DONE:
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
            {
                int i;
                for (i=0; i<CL2_NNET; i++)
                {
                    CAL_CL2_MsgSendAckn(i, CAA_hINVALID);
                }
            }
			break;
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_PRE_EXIT:
			break;
		case CH_EXIT3:
			Socket_CanMiniDriver_Dispose();
			break;
		case CH_EXIT_SYSTEM:
			break;
		default:
			break;
	}
	return 0;
}
				
#endif /* CAA_CL2 */
#endif /* CAALib */
