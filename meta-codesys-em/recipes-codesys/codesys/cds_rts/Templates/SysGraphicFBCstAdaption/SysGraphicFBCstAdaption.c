/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Template component
*	Version:
*	Description:
******************************************************************************/

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

#include "CmpStd.h"
#include "CmpItf.h"

#include <pmeFpga.h> 
#include <tsc2046Touch.h>
#include "SysGraphicFramebufferDrv.h"
#include "SysGraphicFBCstAdaptionDep.h"
#include "./Fonts/MyFontCourier10.h"
#if defined(WIN32) && !defined(STD_CALL)
	#include <windows.h>
#endif

#define SG_TEMP					0x0100
#define TEMP_GET_RTS_VERSION	0x12
#define TAG_TEMP_VERSION_TYPE	0x10

#define EVTPARAMID_SysGraphicFBCstAdaption		0x0001
#define EVTVERSION_SysGraphicFBCstAdaption		0x0001

#define EVT_Test				MAKE_EVENTID(EVTCLASS_INFO, 1)

#ifndef CPLUSPLUS
	typedef struct
	{
		IBase Base;
		ICmpEventCallback EventCallback;
	} CSysGraphicFBCstAdaption;

	DECLARE_ADDREF
	DECLARE_RELEASE
	DECLARE_QUERYINTERFACE

	static CSysGraphicFBCstAdaption s_CSysGraphicFBCstAdaption;
#else
	static CSysGraphicFBCstAdaption *s_pCSysGraphicFBCstAdaption = NULL;
#endif

USE_STMT

static char* s_pcFBAddress;
static int s_iWINDOW_SIZE_X, s_iWINDOW_SIZE_Y, s_i,	s_iBits_per_pixel,s_iBytes_per_pixel;
int g_uiTouchState = 0;
unsigned int g_uiTouchMinX = 0;
unsigned int g_uiTouchMaxX = 0;
unsigned int g_uiTouchMinY = 0;
unsigned int g_uiTouchMaxY = 0;

RTS_RESULT CDECL SysGraphicFBCstAdaptionSetPalette(void);

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

	return ERR_OK;
}

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CSysGraphicFBCstAdaption)
	{
		if (s_pCSysGraphicFBCstAdaption == NULL)
			s_pCSysGraphicFBCstAdaption = static_cast<CSysGraphicFBCstAdaption *>(new CSysGraphicFBCstAdaption());
		return (IBase*)s_pCSysGraphicFBCstAdaption->QueryInterface((ISysGraphicFBCstAdaption *)s_pCSysGraphicFBCstAdaption, ITFID_IBase, pResult);
	}
#else
	if (cid == CLASSID_CSysGraphicFBCstAdaption)
	{
		IBase *pI = &s_CSysGraphicFBCstAdaption.Base;
		pI->bIEC = 0;
		pI->AddRef = AddRef;
		pI->Release = Release;
		pI->QueryInterface = QueryInterface;
		pI->iRefCount++;
		return pI;
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	if (pIBase->Release() == 0)
		s_pCSysGraphicFBCstAdaption = NULL;
	return ERR_OK;
#else
	if (pIBase->iRefCount > 0)
		pIBase->iRefCount--;
	return ERR_OK;
#endif
}

#ifndef RTS_COMPACT_MICRO

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

#endif

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
		{
			dsFpgaDev_t tDevInfo;

			/* Initialize the Framebuffer interface */
			fpgaRuntimeInit();
			fpgaGetDeviceInfo(&tDevInfo);
			fpgaSetBrightness(255);
			if(tDevInfo.bIsRunning && tDevInfo.uiCountFb > 0)
			{
				s_pcFBAddress = tDevInfo.dfFpgaFb[0];
				fpgaSetActiveFramebuffer2(s_pcFBAddress);
			}
			else
			{
				printf("FB not initialized, yet.\n");
			}
			break;
		}
		case CH_INIT2:
		{
			/*Get a pointer to the FB-Visu-kernels font-array description. Then add one font as an example.*/
			FBMemoryFonts* pFBAllFonts = NULL;
			CAL_SysModuleGetFunctionPointer(NULL,"g_SysGraphicFramebuffer_FBAllFonts",&pFBAllFonts);
			
			if(pFBAllFonts)
			{
				unsigned char ucOldNumOfFonts = pFBAllFonts->ucFBNumberOfFonts;
				unsigned char ucNewNumOfFonts = ucOldNumOfFonts + 1;
				FBFont** pFontsOld = pFBAllFonts->FBFonts;
				FBFont** pFontsNew = CAL_SysMemAllocData(COMPONENT_NAME,ucNewNumOfFonts * sizeof(FBFont*),NULL);
				memcpy(pFontsNew,pFBAllFonts->FBFonts,ucOldNumOfFonts * sizeof(FBFont*));
				pFontsNew[ucOldNumOfFonts] = &MyCourierNew10;
				pFBAllFonts->FBFonts = pFontsNew;
				pFBAllFonts->ucFBNumberOfFonts = ucNewNumOfFonts;
				CAL_SysMemFreeData(COMPONENT_NAME,pFontsOld);
			}
			memset(s_pcFBAddress, 224, s_iWINDOW_SIZE_X * s_iWINDOW_SIZE_Y);			
			fpgaSetActiveFramebuffer2(s_pcFBAddress);
			
			/* Register Callback, which is called when the DMA transfer of the FB finished */
			/* fpgaSetNotification(FPGA_EVENT_END_OF_FRAME, FBReady); */
			
			/* Initialize the touchscreen driver */
			touchInit();

			/* Calibrate TS */
			int iColor = 220;
			RTS_RESULT hTask;
#if 0
			/* black */
			memset(g_pcFBAddress, 224, s_iWINDOW_SIZE_X * s_iWINDOW_SIZE_Y);
#endif
			while(g_uiTouchState < 4)
			{
				uint16_t uiX, uiY;
				bool_t bPressed;
				touchGetPosition(&uiX, &uiY, &bPressed);
				iColor = (iColor + 4) % 8;
				switch(g_uiTouchState)
				{
				case 0:
					memset(s_pcFBAddress + 0 + 0 * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + 0 + 1 * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + 0 + 2 * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + 0 + 3 * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + 0 + 4 * s_iWINDOW_SIZE_X, iColor, 15);
					if(bPressed)
					{
						g_uiTouchMinX = uiX;
						g_uiTouchMinY = uiY;
						g_uiTouchState++;
						printf("Min: %u x %u : %u\n", (unsigned int)uiX, (unsigned int)uiY, (unsigned int)bPressed);
					}
					break;
				case 1:
					if(!bPressed)
					{
						g_uiTouchState++;
						printf("Rel: %u x %u : %u\n", (unsigned int)uiX, (unsigned int)uiY, (unsigned int)bPressed);
					}
					break;
				case 2:
					memset(s_pcFBAddress + (s_iWINDOW_SIZE_X-15) + (s_iWINDOW_SIZE_Y-1) * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + (s_iWINDOW_SIZE_X-15) + (s_iWINDOW_SIZE_Y-2) * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + (s_iWINDOW_SIZE_X-15) + (s_iWINDOW_SIZE_Y-3) * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + (s_iWINDOW_SIZE_X-15) + (s_iWINDOW_SIZE_Y-4) * s_iWINDOW_SIZE_X, iColor, 15);
					memset(s_pcFBAddress + (s_iWINDOW_SIZE_X-15) + (s_iWINDOW_SIZE_Y-5) * s_iWINDOW_SIZE_X, iColor, 15);
					if(bPressed)
					{
						g_uiTouchMaxX = uiX;
						g_uiTouchMaxY = uiY;
						g_uiTouchState++;
						printf("Max: %u x %u : %u\n", (unsigned int)uiX, (unsigned int)uiY, (unsigned int)bPressed);
					}
					break;
				case 3:
					if(!bPressed)
					{
						g_uiTouchState++;
						printf("Rel: %u x %u : %u\n", (unsigned int)uiX, (unsigned int)uiY, (unsigned int)bPressed);
					}
					break;
				}
				fpgaSetActiveFramebuffer2(s_pcFBAddress);

				if(SysTaskGetCurrent(&hTask) == ERR_OK)
				{
					SysTaskWaitSleep(hTask, 500);
				}
			}
			break;
		}
		case CH_INIT3:
		{
			break;
		}
		case CH_INIT_TASKS:
			/* SysGraphicFBCstAdaptionSetPalette(); */
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
		{
 			break;
		}

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
		{
			break;
		}
		case CH_EXIT2:
		{
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

#ifndef CPLUSPLUS
IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void CDECL EventCallback(RTS_HANDLE hEventCallback, EventParam *pEventParam)
{
}

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer ro the IBase interface. So it doesn't matter, which interface
		   is used to get the IBase pointer */
		ICmpEventCallback *pI = (ICmpEventCallback *)pBase;
		pI->pBase->iRefCount++;
		return pI->pBase;
	}
	if (iid == ITFID_ICmpEventCallback)
	{
		CSysGraphicFBCstAdaption *pC = (CSysGraphicFBCstAdaption *)pBase;
		pC->EventCallback.pBase = pBase;
		pC->EventCallback.IEventCallback = EventCallback;
		pC->Base.iRefCount++;
		return &pC->EventCallback;
	}
	return NULL;
}
#endif

RTS_RESULT CDECL SysGraphicFBCstAdaptionBufferWasUpdated(char* pcFBAddress)
{
	/* switch FB */
	fpgaSetActiveFramebuffer2(pcFBAddress);
}

char* CDECL SysGraphicFBCstAdaptionGetFBAddress(char* pcFBAddress)
{
	return s_pcFBAddress;
}

RTS_RESULT CDECL SysGraphicFBCstAdaptionGetGlobalParameters(SysGraphicGlobalParameters* pParameters)
{
	s_iWINDOW_SIZE_X = pParameters->iWindow_size_x;
	s_iWINDOW_SIZE_Y = pParameters->iWindow_size_y;
	s_iBits_per_pixel = pParameters->iBits_per_pixel;
	s_iBytes_per_pixel = pParameters->iBytes_per_pixel;
	
	/*Here the function takes the parameters from the parameter, it could set the parameters, too. If required to change them.*/
	
	return ERR_OK;
}

RTS_RESULT CDECL SysGraphicFBCstAdaptionGetTouchPosition(int* piX, int* piY, int* pbPressed)
{
	uint16_t uiX, uiY;
	bool_t bPressed = 0;
	
	/* Poll TS */
	touchGetPosition(&uiX, &uiY, &bPressed);
	*pbPressed = bPressed != 0;
	*piX = MAX(g_uiTouchMinX, uiX - g_uiTouchMinX) * s_iWINDOW_SIZE_X / (g_uiTouchMaxX - g_uiTouchMinX);
	*piY = MAX(g_uiTouchMinY, uiY - g_uiTouchMinY) * s_iWINDOW_SIZE_Y/ (g_uiTouchMaxY - g_uiTouchMinY);

	return ERR_OK;
}

RTS_RESULT CDECL SysGraphicFBCstAdaptionSetPalette(void)
{
	FBPalette *pPalette;
	RTS_RESULT Result;
	FBDC* pdc;
	int nEntriesCount = 256;
	
	pdc = SysGraphicNativeGetDisplayDeviceContext(&Result);
	
	pPalette = FBAllocPalette(nEntriesCount);
	if (pPalette != NULL)
	{
		int i;
		pdc->deviceInfo.pPalette = pPalette;
		
		pPalette->usNumberOfEntrys = (RTS_UI16) nEntriesCount;
		for (i = 0; i < nEntriesCount; ++i)
		{
			pdc->deviceInfo.pPalette->acRed[i] = (i%2 == 0) ? 255 : 0;
			pdc->deviceInfo.pPalette->acGreen[i] = (i%2 == 0) ? 255 : 0;
			pdc->deviceInfo.pPalette->acBlue[i] = (i%2 == 0) ? 255 : 0;
		}
	}
}

