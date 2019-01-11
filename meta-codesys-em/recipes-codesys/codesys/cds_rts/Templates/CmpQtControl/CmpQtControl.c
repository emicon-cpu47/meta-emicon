/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Template component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpQtControlDep.h"

USE_STMT

extern int qt_show_Message(void *handle);
extern void *qt_create_dialog(void *handle, int tx, int ty, int bx, int by);
extern void qt_move_dialog(void *handle, int x, int y);
extern void qt_show_dialog(void *handle);
extern void qt_hide_dialog(void *handle);
  
static RTS_HANDLE s_hEventNativeControlCreate;
static RTS_HANDLE s_hEventNativeControlDestroy;
static RTS_HANDLE s_hEventNativeControlCallMethod;
static RTS_HANDLE s_hEventNativeControlMove;
static RTS_HANDLE s_hEventNativeControlShow;

static void CDECL EventCallbackFunction(EventParam *pEventParam);

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

	s_hEventNativeControlCreate = RTS_INVALID_HANDLE;
  s_hEventNativeControlDestroy = RTS_INVALID_HANDLE;
  s_hEventNativeControlCallMethod = RTS_INVALID_HANDLE;
  s_hEventNativeControlMove = RTS_INVALID_HANDLE;
  s_hEventNativeControlShow = RTS_INVALID_HANDLE;
  
	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpQtControl);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
	return ERR_NOTIMPLEMENTED;
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
static RTS_RESULT CDECL  HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
			break;
		case CH_INIT3:
			if (CHK_EventOpen)
			{
				s_hEventNativeControlCreate = CAL_EventOpen(EVT_SysNativeControlCreate, CMPID_SysNativeControl, NULL);
        s_hEventNativeControlDestroy = CAL_EventOpen(EVT_SysNativeControlDestroy, CMPID_SysNativeControl, NULL);
        s_hEventNativeControlCallMethod = CAL_EventOpen(EVT_SysNativeControlCallMethod, CMPID_SysNativeControl, NULL);
        s_hEventNativeControlMove = CAL_EventOpen(EVT_SysNativeControlMove, CMPID_SysNativeControl, NULL);
        s_hEventNativeControlShow = CAL_EventOpen(EVT_SysNativeControlShow, CMPID_SysNativeControl, NULL);
        
      }
			if (CHK_EventRegisterCallbackFunction)
			{
				CAL_EventRegisterCallbackFunction(s_hEventNativeControlCreate, EventCallbackFunction, 0);
				CAL_EventRegisterCallbackFunction(s_hEventNativeControlDestroy, EventCallbackFunction, 0);
        CAL_EventRegisterCallbackFunction(s_hEventNativeControlCallMethod, EventCallbackFunction, 0);
        CAL_EventRegisterCallbackFunction(s_hEventNativeControlMove, EventCallbackFunction, 0);
        CAL_EventRegisterCallbackFunction(s_hEventNativeControlShow, EventCallbackFunction, 0);
      }
      //qt_show_PushButton();
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
			break;

		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
			if (CHK_EventUnregisterCallbackFunction)
			{
				CAL_EventUnregisterCallbackFunction(s_hEventNativeControlCreate, EventCallbackFunction);
        CAL_EventUnregisterCallbackFunction(s_hEventNativeControlDestroy, EventCallbackFunction);
        CAL_EventUnregisterCallbackFunction(s_hEventNativeControlCallMethod, EventCallbackFunction);
        CAL_EventUnregisterCallbackFunction(s_hEventNativeControlMove, EventCallbackFunction);
        CAL_EventUnregisterCallbackFunction(s_hEventNativeControlShow, EventCallbackFunction);
      }
			break;
		case CH_EXIT2:
			break;
		case CH_EXIT:
		{
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
		default:
			break;
	}
	return ERR_OK;
}

static void CDECL EventCallbackFunction(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		case EVT_SysNativeControlCreate:
		{
			if (pEventParam->usVersion >= EVTVERSION_SysNativeControlCreate)
			{
				EVTPARAM_SysNativeControlCreate *pParam = (EVTPARAM_SysNativeControlCreate *)pEventParam->pParameter;
        printf("SysNativeControlCreate: Windowhandle: %x\n", (unsigned int)pParam->pCreateInfo->hParentWindow);
        pParam->bHandled = 1;

        RTS_Rectangle rect;
        rect = *pParam->pCreateInfo->prWindow;

        qt_show_Message(pParam->pCreateInfo->hParentWindow);
        pParam->hControl = qt_create_dialog(pParam->pCreateInfo->hParentWindow, rect.ptTopLeft.sX, rect.ptTopLeft.sY, rect.ptBottomRight.sX, rect.ptBottomRight.sY);
			}
			break;
		}
		case EVT_SysNativeControlDestroy:
		{
			if (pEventParam->usVersion >= EVTVERSION_SysNativeControlCreate)
			{
				EVTPARAM_SysNativeControlDestroy *pParam = (EVTPARAM_SysNativeControlDestroy *)pEventParam->pParameter;
        pParam->bHandled = 1;
        printf("SysNativeControlDestroy\n");
			}
			break;
		}
		case EVT_SysNativeControlCallMethod:
		{
			if (pEventParam->usVersion >= EVTVERSION_SysNativeControlCreate)
			{
				EVTPARAM_SysNativeControlCallMethod *pParam = (EVTPARAM_SysNativeControlCallMethod *)pEventParam->pParameter;
        pParam->bHandled = 1;
        printf("SysNativeControlCallMethod\n");
			}
			break;
		}
		case EVT_SysNativeControlMove:
		{
			if (pEventParam->usVersion >= EVTVERSION_SysNativeControlCreate)
			{
				EVTPARAM_SysNativeControlMove *pParam = (EVTPARAM_SysNativeControlMove *)pEventParam->pParameter;
        printf("SysNativeControlMove\n");
        int x, y;
        RTS_Rectangle rect;
        rect = *pParam->prRect;
        pParam->bHandled = 1;
        qt_move_dialog(pParam->hControl, rect.ptTopLeft.sX, rect.ptTopLeft.sY);
			}
			break;
		}
		case EVT_SysNativeControlShow:
		{
			if (pEventParam->usVersion >= EVTVERSION_SysNativeControlCreate)
			{
				EVTPARAM_SysNativeControlShow *pParam = (EVTPARAM_SysNativeControlShow *)pEventParam->pParameter;

        pParam->bHandled = 1;
        switch (pParam->ulFlags)
        {
          case NATIVE_CONTROL_SNCF_SHOW:
            printf("SysNativeControlShow\n");
            qt_show_dialog(pParam->hControl);
            break;
          case NATIVE_CONTROL_SNCF_HIDE:
            printf("SysNativeControlHide\n");
            qt_hide_dialog(pParam->hControl);
            break;
        }
			}
			break;
		}
  }
}
