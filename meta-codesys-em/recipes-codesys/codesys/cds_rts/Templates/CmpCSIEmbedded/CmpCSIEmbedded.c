/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CSIEmbedded component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpCSIEmbeddedDep.h"

USE_STMT

PF_COMPONENT_ENTRY g_pfComponentEntry;

static RTS_HANDLE s_hEventCDBlob = RTS_INVALID_HANDLE;
static void CDECL CB_CDBlob(EventParam *pEventParam);

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

	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
	return ERR_OK;
}

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
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
		case CH_INIT:
			break;
		case CH_INIT2:		
			break;		
		case CH_INIT3:
		{
			/* Register callback function */
			if (CHK_EventOpen)
			{
				s_hEventCDBlob = CAL_EventOpen(EVT_CDBlob, CMPID_CmpApp, NULL);
			}
			if (CHK_EventRegisterCallbackFunction)
			{
				CAL_EventRegisterCallbackFunction(s_hEventCDBlob, CB_CDBlob, 0);
			}
			break;		
		}
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


typedef void (*funcptr)(void);
typedef int (*funcptr2)(void*);
typedef struct __t_component_hdr
{
	unsigned long magic;
	funcptr init;
	funcptr2 entry;
} t_component_hdr;


static void CDECL CB_CDBlob(EventParam *pEventParam)
{
	switch(pEventParam->EventId)
	{
		case EVT_CDBlob:
		{
			EVTPARAM_CmpAppEmbedded_CDBlob *p = (EVTPARAM_CmpAppEmbedded_CDBlob *) pEventParam->pParameter;
			RTS_RESULT Result = ERR_OK;			
			RTS_HANDLE hComponent = RTS_INVALID_HANDLE;
			t_component_hdr* pBlobheader = (t_component_hdr*) p->pData;
			
			if(p->ulBlobID == 0xACDC0815 && pBlobheader->magic == 0xACDCACDC)
			{
				/* reserving space for data of c component */
				VirtualAlloc( (void*) 0x40000000, 0x1000, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);	
			
				/* calling init code */
				pBlobheader->init();
				g_pfComponentEntry = (PF_COMPONENT_ENTRY) pBlobheader->entry;
						
				hComponent = CAL_CMLoadComponent("CmpUserMod",&Result);
				if(hComponent != RTS_INVALID_HANDLE)
					CAL_CMInitComponent(hComponent);
			}

			break;
		}
		default:
			break;
	}

	
	

}
