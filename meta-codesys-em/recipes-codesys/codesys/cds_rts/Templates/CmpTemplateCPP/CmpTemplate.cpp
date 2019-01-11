#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpErrors.h"
#include "SysFileItf.h"
#include "SysDirItf.h"
#include "CmpLogItf.h"
#include "CmpEventMgrItf.h"
#include "CmpAppItf.h"

#include "CmpTemplate.h"

#define CMP_VERSION		RTS_VERSION
#define CMP_VENDORID	RTS_VENDORID_3S

static PF_REGISTER_API s_pfRegisterAPI;
static PF_GET_API s_pfGetAPI;
static PF_CALL_HOOK s_pfCallHook;
static PF_CREATEINSTANCE s_pfCreateInstance;

static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);
static int CDECL ExportFunctions(void);
static int CDECL ImportFunctions(void);
static RTS_UI32 CDECL CmpGetVersion(void);

static ICmpLog *_pICmpLog;
static ISysDir *_pISysDir;

class CMyCallbackHandler : public ICmpEventCallback 
{
	public:
		CMyCallbackHandler()
		{
		}
		virtual ~CMyCallbackHandler()
		{
		}
		IMPLEMENT_ADDREF();
		IMPLEMENT_RELEASE();
		
		virtual	void* QueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult)
		{
			void *pItf;
			if (iid == ITFID_IBase)
				pItf = dynamic_cast<IBase *>((IBase *)this);			
			else if (iid == ITFID_ICmpEventCallback)
				pItf = dynamic_cast<ICmpEventCallback *>(this); 
			else
			{
				if (pResult != NULL)
					*pResult = ERR_NOTIMPLEMENTED;
				return NULL;
			}
			(reinterpret_cast<IBase *>(pItf))->AddRef();
			if (pResult != NULL)
				*pResult = ERR_OK;
			return pItf;
		}

		virtual void CDECL IEventCallback(EventParam *pEventParam)
		{
			 iCBCounter += 1;
			_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** Stop event received ***", 0);
		}

		private:
			int iRefCount;
			int iCBCounter;
};

static CMyCallbackHandler *s_pCMyCallbackHandler = NULL;

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
    if (cid == CLASSID_CCmpTemplateCPP)
    {
        if (s_pCMyCallbackHandler == NULL)
            s_pCMyCallbackHandler = static_cast<CMyCallbackHandler *>(new CMyCallbackHandler());
        return (IBase*)s_pCMyCallbackHandler->QueryInterface(s_pCMyCallbackHandler, ITFID_IBase, pResult);
    }
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
    if (pIBase->Release() == 0)
        s_pCMyCallbackHandler = NULL;
    return ERR_OK;
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

	s_pfRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCallHook = pInitStruct->pfCMCallHook;
	s_pfCreateInstance = pInitStruct->pfCMCreateInstance;

	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpTemplateCPP);
	return ERR_OK;
}

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
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
		case CH_INIT:
			// Get instance pointers to singleton classes
			IBase *pIBase;
			if (_pICmpLog == NULL && s_pfCreateInstance != NULL)
			{
				pIBase = s_pfCreateInstance(CLASSID_CCmpLog, NULL);
				_pICmpLog = (ICmpLog *)pIBase->QueryInterface(pIBase, ITFID_ICmpLog, NULL);
			}
			if (_pISysDir == NULL && s_pfCreateInstance != NULL)
			{
				pIBase = s_pfCreateInstance(CLASSID_CSysDir, NULL);
				_pISysDir = (ISysDir *)pIBase->QueryInterface(pIBase, ITFID_ISysDir, NULL);
			}
			break;
		case CH_INIT3:
		{
			RTS_RESULT Result;
			char szOldDir[255];

			/* Use of static functions */
			if (_pISysDir->ISysDirGetCurrent(szOldDir, sizeof(szOldDir)) != ERR_OK)
				_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, "Directory could not read", 0);

			if (_pISysDir->ISysDirSetCurrent("d:\\temp") != ERR_OK)
				_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, "Directory could not be changed", 0);

			/* Use of an typical C++ object via its interface */
			IBase *pIBase = (ISysFile *)s_pfCreateInstance(CLASSID_CSysFile, NULL);
			ISysFile *pIsysFile = (ISysFile *)pIBase->QueryInterface(pIBase, ITFID_ISysFile, NULL);

			pIsysFile->ISysFileOpen("test.dat", AM_WRITE, &Result);
			if (Result != ERR_OK)
				_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "File %s could not be opened", "test.dat");
			pIsysFile->ISysFileWrite((unsigned char*)"Hallo", strlen("Hallo")+1, &Result);
			if (Result != ERR_OK)
				_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "File %s could not be written", "test.dat");
			if (pIsysFile->ISysFileClose() != ERR_OK)
				_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, Result, 0, "File %s could not be written", "test.dat");

			// Release and delete object if refcount = 0
			pIsysFile->Release();

			if (_pISysDir->ISysDirSetCurrent(szOldDir) != ERR_OK)
				_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, "Directory could not be changed", 0);

			// Register on an event
			pIBase = s_pfCreateInstance(CLASSID_CCmpEventMgr, NULL);
			ICmpEventMgr *pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, NULL);
			if (pICmpEventMgr != NULL)
			{
				IBase *pIBase = s_pfCreateInstance(CLASSID_CCmpTemplateCPP, NULL);
				if (pIBase != NULL)
				{
					ICmpEventCallback *pCallback = (ICmpEventCallback *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventCallback, NULL);
					// Check if interface is implemented
					if (pCallback != NULL)
					{
						RTS_HANDLE hEvent = pICmpEventMgr->IEventOpen(EVT_StopDone, CMPID_CmpApp, NULL);
						if (pICmpEventMgr->IEventRegisterCallback(hEvent, pCallback) != ERR_OK)
							_pICmpLog->ILogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0, "Event could not be registered", 0);
					}
				}
			}
			pICmpEventMgr->Release();
			break;

		}
		default:
			break;
	}
	return ERR_OK;
}
