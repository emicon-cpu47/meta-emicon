/**
 * <name>RtsDisableOperations.c</name>
 * <description> 
 *	Template module to handle events
 *
 *	- CH_INIT2: call CreateEvents() from your component hook function
 *	- CH_INIT3: call RegisterEventHandler() from your component hook function
 *	- CH_EXIT3: call UnregisterEventHandler() from your component hook function
 *	- CH_EXIT2: call DeleteEvents() from your component hook function
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"
#include "CmpIecVarAccessItf.h"
#include "CmpIoMgrItf.h"
#include "CmpTemplateDep.h"
#include "CmpChannelServerItf.h"

#define EVTPARAMID_CmpTemplate		0x0001
#define EVTVERSION_CmpTemplate		0x0001
#define EVT_Test					MAKE_EVENTID(EVTCLASS_INFO, 1)

static RTS_HANDLE s_hEventAppPrepareDownload = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventAppDownloadDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventTest = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventAppPrepareDelete = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventCreateBootprojectDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventLoadBootprojectDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventDenyLoadBootproject = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventDenyStartBootproject = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventDenyStart = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventDenyStop = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventPrepareStop = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventStopDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventPrepareReset = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventResetDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventRegisterBootproject = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventCreateBootprojectFileFailed = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventOperatingStateChanged = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventSourceDownload = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventDenyDelete = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventAppException = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventOEMDownloadServiceTag = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventPrepareExit = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventExitDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventLogin = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventLogout = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventPrepareOnlineChange = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventOnlineChangeDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventOEMRegsiteredFunction = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventConfigStartDone = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventConfigPrepareStop = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventConfigStopDone = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventCodePatch = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventPrepareWriteVariable = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventPrepareForceVariable = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventIecVarAccPrepareWriteVariable = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventIecVarAccWriteVariableDone = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventSysExcept = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventSysFileOpen = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventSysFileClose = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventAllocArea = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventChSChannelOpened = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventChSChannelClosed = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventSupervisorStateChanged = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventUserMgrDatabaseChanged = RTS_INVALID_HANDLE;

static RTS_HANDLE s_hEventLogAdd = RTS_INVALID_HANDLE;

static void CDECL CBApp(EventParam *pEventParam);
static void CDECL CBBreakpoints(EventParam *pEventParam);
static void CDECL CBMonitoring(EventParam *pEventParam);
static void CDECL CBIecVarAccess(EventParam *pEventParam);
static void CDECL CBIoMgr(EventParam *pEventParam);
static void CDECL CBSysExcept(EventParam *pEventParam);
static void CDECL CBSysFile(EventParam *pEventParam);
static void CDECL CBChannelServer(EventParam *pEventParam);
static void CDECL CBSupervisor(EventParam *pEventParam);
static void CDECL CBUserMgr(EventParam *pEventParam);
static void CDECL CBLogger(EventParam *pEventParam);

static RTS_RESULT CDECL CreateEvents(void)
{
	/* Create new event */
	if (CHK_EventCreate)
	{
		s_hEventTest = CAL_EventCreate2(EVT_Test, COMPONENT_ID, 1, NULL);
	}
	return ERR_OK;
}

static RTS_RESULT CDECL DeleteEvents(void)
{
	if (CHK_EventDelete)
	{
		CAL_EventDelete(s_hEventTest);
	}
	return ERR_OK;
}

static RTS_RESULT CDECL RegisterEventHandler(void)
{
	IBase *pIBase;
	ICmpEventCallback *pICallback;

	/* Register callback function */
	if (CHK_EventOpen)
	{
		s_hEventAppPrepareDownload = CAL_EventOpen(EVT_PrepareDownload, CMPID_CmpApp, NULL);
		s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone, CMPID_CmpApp, NULL);
		s_hEventAppPrepareDelete = CAL_EventOpen(EVT_PrepareDelete, CMPID_CmpApp, NULL);
		s_hEventCreateBootprojectDone = CAL_EventOpen(EVT_CreateBootprojectDone, CMPID_CmpApp, NULL);
		s_hEventLoadBootprojectDone = CAL_EventOpen(EVT_LoadBootprojectDone, CMPID_CmpApp, NULL);
		s_hEventDenyLoadBootproject = CAL_EventOpen(EVT_DenyLoadBootproject, CMPID_CmpApp, NULL);
		s_hEventDenyStartBootproject = CAL_EventOpen(EVT_DenyStartBootproject, CMPID_CmpApp, NULL);
		s_hEventDenyStart = CAL_EventOpen(EVT_DenyStart, CMPID_CmpApp, NULL);
		s_hEventDenyStop = CAL_EventOpen(EVT_DenyStop, CMPID_CmpApp, NULL);
		s_hEventPrepareStop = CAL_EventOpen(EVT_PrepareStop, CMPID_CmpApp, NULL);
		s_hEventStopDone = CAL_EventOpen(EVT_StopDone, CMPID_CmpApp, NULL);
		s_hEventPrepareReset = CAL_EventOpen(EVT_PrepareReset, CMPID_CmpApp, NULL);
		s_hEventResetDone = CAL_EventOpen(EVT_ResetDone, CMPID_CmpApp, NULL);
		s_hEventRegisterBootproject = CAL_EventOpen(EVT_RegisterBootproject, CMPID_CmpApp, NULL);
		s_hEventCreateBootprojectFileFailed = CAL_EventOpen(EVT_CreateBootprojectFileFailed, CMPID_CmpApp, NULL);
		s_hEventOperatingStateChanged = CAL_EventOpen(EVT_OperatingStateChanged, CMPID_CmpApp, NULL);
		s_hEventSourceDownload = CAL_EventOpen(EVT_SourceDownload, CMPID_CmpApp, NULL);
		s_hEventDenyDelete = CAL_EventOpen(EVT_DenyDelete, CMPID_CmpApp, NULL);
		s_hEventAppException = CAL_EventOpen(EVT_CmpApp_Exception, CMPID_CmpApp, NULL);
		s_hEventOEMDownloadServiceTag = CAL_EventOpen(EVT_OEMDownloadServiceTag, CMPID_CmpApp, NULL);
		s_hEventPrepareExit = CAL_EventOpen(EVT_PrepareExit, CMPID_CmpApp, NULL);
		s_hEventExitDone = CAL_EventOpen(EVT_ExitDone, CMPID_CmpApp, NULL);
		s_hEventLogin = CAL_EventOpen(EVT_Login, CMPID_CmpApp, NULL);
		s_hEventLogout = CAL_EventOpen(EVT_Logout, CMPID_CmpApp, NULL);
		s_hEventPrepareOnlineChange = CAL_EventOpen(EVT_PrepareOnlineChange, CMPID_CmpApp, NULL);
		s_hEventOnlineChangeDone = CAL_EventOpen(EVT_OnlineChangeDone, CMPID_CmpApp, NULL);
		s_hEventOEMRegsiteredFunction = CAL_EventOpen(EVT_OEMRegisteredIecFunction, CMPID_CmpApp, NULL);
	
		s_hEventCodePatch = CAL_EventOpen(EVT_CmpAppBP_CodePatch, CMPID_CmpAppBP, NULL);

		s_hEventPrepareWriteVariable = CAL_EventOpen(EVT_PrepareWriteVariable, CMPID_CmpMonitor, NULL);
		s_hEventPrepareForceVariable = CAL_EventOpen(EVT_PrepareForceVariable, CMPID_CmpMonitor, NULL);

		s_hEventIecVarAccPrepareWriteVariable = CAL_EventOpen(EVT_CmpIecVarAccess_PrepareWriteVariable, CMPID_CmpIecVarAccess, NULL);
		s_hEventIecVarAccWriteVariableDone = CAL_EventOpen(EVT_CmpIecVarAccess_WriteVariableDone, CMPID_CmpIecVarAccess, NULL);
			
		s_hEventConfigStartDone = CAL_EventOpen(EVT_ConfigAppStartedDone, CMPID_CmpIoMgr, NULL);
		s_hEventConfigPrepareStop = CAL_EventOpen(EVT_PrepareConfigAppStopped, CMPID_CmpIoMgr, NULL);
		s_hEventConfigStopDone = CAL_EventOpen(EVT_ConfigAppStoppedDone, CMPID_CmpIoMgr, NULL);

		s_hEventSysExcept = CAL_EventOpen(EVT_EXCPT_GenerateException2, CMPID_SysExcept, NULL);

		s_hEventSysFileOpen = CAL_EventOpen(EVT_SysFileOpen, CMPID_SysFile, NULL);
		s_hEventSysFileClose = CAL_EventOpen(EVT_SysFileClose, CMPID_SysFile, NULL);

		s_hEventAllocArea = CAL_EventOpen(EVT_AllocArea, CMPID_CmpApp, NULL);

		s_hEventChSChannelOpened = CAL_EventOpen(EVT_ChSChannelOpened, CMPID_CmpChannelServer, NULL);
		s_hEventChSChannelClosed = CAL_EventOpen(EVT_ChSChannelClosed, CMPID_CmpChannelServer, NULL);
		
		s_hEventSupervisorStateChanged = CAL_EventOpen(EVT_Supervisor_StateChanged, CMPID_CmpSupervisor, NULL);

		s_hEventUserMgrDatabaseChanged = CAL_EventOpen(EVT_UserMgrDatabaseChanged, CMPID_CmpUserMgr, NULL);

		s_hEventLogAdd = CAL_EventOpen(EVT_LogAdd, CMPID_CmpLog, NULL);
	}
	if (CHK_EventRegisterCallbackFunction)
	{
		/* CmpApp Events */
		CAL_EventRegisterCallbackFunction(s_hEventAppPrepareDownload, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventAppDownloadDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventAppPrepareDelete, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventCreateBootprojectDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventLoadBootprojectDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventDenyLoadBootproject, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventDenyStartBootproject, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventDenyStart, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventDenyStop, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventPrepareStop, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventStopDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventPrepareReset, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventResetDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventRegisterBootproject, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventCreateBootprojectFileFailed, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventOperatingStateChanged, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventSourceDownload, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventDenyDelete, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventAppException, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventOEMDownloadServiceTag, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventPrepareExit, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventExitDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventLogin, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventLogout, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventPrepareOnlineChange, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventOnlineChangeDone, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventAllocArea, CBApp, 0);
		CAL_EventRegisterCallbackFunction(s_hEventOEMRegsiteredFunction, CBApp, 0);
		
		CAL_EventRegisterCallbackFunction(s_hEventCodePatch, CBBreakpoints, 0);
		
		CAL_EventRegisterCallbackFunction(s_hEventPrepareWriteVariable, CBMonitoring, 0);
		CAL_EventRegisterCallbackFunction(s_hEventPrepareForceVariable, CBMonitoring, 0);

		CAL_EventRegisterCallbackFunction(s_hEventIecVarAccPrepareWriteVariable, CBIecVarAccess, 0);
		CAL_EventRegisterCallbackFunction(s_hEventIecVarAccWriteVariableDone, CBIecVarAccess, 0);

		/* Register on own event */
		CAL_EventRegisterCallbackFunction(s_hEventTest, CBApp, 0);

		/* IoMgr events */
		CAL_EventRegisterCallbackFunction(s_hEventConfigStartDone, CBIoMgr, 0);
		CAL_EventRegisterCallbackFunction(s_hEventConfigPrepareStop, CBIoMgr, 0);
		CAL_EventRegisterCallbackFunction(s_hEventConfigStopDone, CBIoMgr, 0);

		/* SysExcept events */
		CAL_EventRegisterCallbackFunction(s_hEventSysExcept, CBSysExcept, 0);

		/* SysFile events */
		CAL_EventRegisterCallbackFunction(s_hEventSysFileOpen, CBSysFile, 0);
		CAL_EventRegisterCallbackFunction(s_hEventSysFileClose, CBSysFile, 0);

		/* ChannelServer events */
		CAL_EventRegisterCallbackFunction(s_hEventChSChannelOpened, CBChannelServer, 0);
		CAL_EventRegisterCallbackFunction(s_hEventChSChannelClosed, CBChannelServer, 0);

		/* CmpSupervisor event */
		CAL_EventRegisterCallbackFunction(s_hEventSupervisorStateChanged, CBSupervisor, 0);

		/* CmpUserMgr event */
		CAL_EventRegisterCallbackFunction(s_hEventUserMgrDatabaseChanged, CBUserMgr, 0);

		/* CmpLog event */
		CAL_EventRegisterCallbackFunction(s_hEventLogAdd, CBLogger, 0);
	}
	/* Register callback Interface */
	pIBase = (IBase *)CreateInstance(CLASSID_CCmpTemplate, NULL);
	pICallback = (ICmpEventCallback *) pIBase->QueryInterface(pIBase, ITFID_ICmpEventCallback, NULL);
	if (CHK_EventRegisterCallback)
		CAL_EventRegisterCallback(s_hEventAppDownloadDone, pICallback);
	pIBase->Release(pIBase);
	return ERR_OK;
}

static RTS_RESULT CDECL UnregisterEventHandler(void)
{
	IBase *pIBase;
	ICmpEventCallback *pICallback;

	if (CHK_EventUnregisterCallbackFunction)
	{
		CAL_EventUnregisterCallbackFunction(s_hEventAppPrepareDownload, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventAppDownloadDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventAppPrepareDelete, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventCreateBootprojectDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventLoadBootprojectDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventDenyLoadBootproject, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventDenyStartBootproject, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventDenyStart, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventDenyStop, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventPrepareStop, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventStopDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventPrepareReset, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventResetDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventRegisterBootproject, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventCreateBootprojectFileFailed, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventOperatingStateChanged, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventSourceDownload, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventDenyDelete, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventAppException, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventOEMDownloadServiceTag, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventPrepareExit, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventExitDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventLogin, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventLogout, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventPrepareOnlineChange, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventOnlineChangeDone, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventAllocArea, CBApp);
		CAL_EventUnregisterCallbackFunction(s_hEventOEMRegsiteredFunction, CBApp);
		
		CAL_EventUnregisterCallbackFunction(s_hEventCodePatch, CBBreakpoints);
		
		CAL_EventUnregisterCallbackFunction(s_hEventPrepareWriteVariable, CBMonitoring);
		CAL_EventUnregisterCallbackFunction(s_hEventPrepareForceVariable, CBMonitoring);

		CAL_EventUnregisterCallbackFunction(s_hEventIecVarAccPrepareWriteVariable, CBIecVarAccess);
		CAL_EventUnregisterCallbackFunction(s_hEventIecVarAccWriteVariableDone, CBIecVarAccess);
		
		CAL_EventUnregisterCallbackFunction(s_hEventTest, CBApp);

		CAL_EventUnregisterCallbackFunction(s_hEventConfigStartDone, CBIoMgr);
		CAL_EventUnregisterCallbackFunction(s_hEventConfigPrepareStop, CBIoMgr);
		CAL_EventUnregisterCallbackFunction(s_hEventConfigStopDone, CBIoMgr);

		CAL_EventUnregisterCallbackFunction(s_hEventSysExcept, CBSysExcept);

		CAL_EventUnregisterCallbackFunction(s_hEventSysFileOpen, CBSysFile);
		CAL_EventUnregisterCallbackFunction(s_hEventSysFileClose, CBSysFile);

		CAL_EventUnregisterCallbackFunction(s_hEventChSChannelOpened, CBChannelServer);
		CAL_EventUnregisterCallbackFunction(s_hEventChSChannelClosed, CBChannelServer);

		CAL_EventUnregisterCallbackFunction(s_hEventSupervisorStateChanged, CBSupervisor);

		CAL_EventUnregisterCallbackFunction(s_hEventUserMgrDatabaseChanged, CBUserMgr);

		CAL_EventUnregisterCallbackFunction(s_hEventLogAdd, CBLogger);
	}
	/* Unregister callback Interface */
	pIBase = (IBase *)CreateInstance(CLASSID_CCmpTemplate, NULL);
	pICallback = (ICmpEventCallback *) pIBase->QueryInterface(pIBase, ITFID_ICmpEventCallback, NULL);
	if (CHK_EventUnregisterCallback)
		CAL_EventUnregisterCallback(s_hEventAppDownloadDone, pICallback);
	pIBase->Release(pIBase);
	pIBase->Release(pIBase);
	
	pIBase->Release(pIBase);	/* Here we have to release the object instance! */

	if (CHK_EventClose)
	{
		CAL_EventClose(s_hEventAppPrepareDownload);
		CAL_EventClose(s_hEventAppDownloadDone);
		CAL_EventClose(s_hEventAppPrepareDelete);
		CAL_EventClose(s_hEventCreateBootprojectDone);
		CAL_EventClose(s_hEventLoadBootprojectDone);
		CAL_EventClose(s_hEventDenyLoadBootproject);
		CAL_EventClose(s_hEventDenyStartBootproject);
		CAL_EventClose(s_hEventDenyStart);
		CAL_EventClose(s_hEventDenyStop);
		CAL_EventClose(s_hEventPrepareStop);
		CAL_EventClose(s_hEventStopDone);
		CAL_EventClose(s_hEventPrepareReset);
		CAL_EventClose(s_hEventResetDone);
		CAL_EventClose(s_hEventRegisterBootproject);
		CAL_EventClose(s_hEventCreateBootprojectFileFailed);
		CAL_EventClose(s_hEventOperatingStateChanged);
		CAL_EventClose(s_hEventSourceDownload);
		CAL_EventClose(s_hEventDenyDelete);
		CAL_EventClose(s_hEventAppException);
		CAL_EventClose(s_hEventOEMDownloadServiceTag);
		CAL_EventClose(s_hEventPrepareExit);
		CAL_EventClose(s_hEventExitDone);
		CAL_EventClose(s_hEventLogin);
		CAL_EventClose(s_hEventLogout);
		CAL_EventClose(s_hEventPrepareOnlineChange);
		CAL_EventClose(s_hEventOnlineChangeDone);
		CAL_EventClose(s_hEventOEMRegsiteredFunction);

		CAL_EventClose(s_hEventCodePatch);

		CAL_EventClose(s_hEventPrepareWriteVariable);
		CAL_EventClose(s_hEventPrepareForceVariable);

		CAL_EventClose(s_hEventIecVarAccPrepareWriteVariable);
		CAL_EventClose(s_hEventIecVarAccWriteVariableDone);

		CAL_EventClose(s_hEventConfigStartDone);
		CAL_EventClose(s_hEventConfigPrepareStop);
		CAL_EventClose(s_hEventConfigStopDone);

		CAL_EventClose(s_hEventSysExcept);

		CAL_EventClose(s_hEventSysFileOpen);
		CAL_EventClose(s_hEventSysFileClose);

		CAL_EventClose(s_hEventChSChannelOpened);
		CAL_EventClose(s_hEventChSChannelClosed);

		CAL_EventClose(s_hEventSupervisorStateChanged);

		CAL_EventClose(s_hEventUserMgrDatabaseChanged);
	}
	return ERR_OK;
}

STATICITF void CDECL EventCallback(RTS_HANDLE hTemplate, EventParam *pEventParam)
{

}

static void CDECL CBApp(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		case EVT_OEMRegisteredIecFunction:
		{
			EVTPARAM_CmpApp_OEMRegisteredIecFunction *pParam = (EVTPARAM_CmpApp_OEMRegisteredIecFunction *)pEventParam->pParameter;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_OEMRegisteredIecFunction received: App=%s, FctName=%s ***", pParam->pApp->szName, pParam->pszName);
			break;
		}
		case EVT_PrepareOnlineChange:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareOnlineChange received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_OnlineChangeDone:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_OnlineChangeDone received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_PrepareDownload:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareDownload received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_DownloadDone:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DownloadDone received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_CreateBootprojectFileFailed:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CreateBootprojectFileFailed received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_PrepareReset:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp_Reset)
			{
				char *pszName;
				EVTPARAM_CmpApp_Reset *pParam = (EVTPARAM_CmpApp_Reset *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareReset received: App=%s, ResetOption=%ld ***", pszName, pParam->usResetOption);
			}
			break;
		}
		case EVT_ResetDone:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp_Reset)
			{
				char *pszName;
				EVTPARAM_CmpApp_Reset *pParam = (EVTPARAM_CmpApp_Reset *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_ResetDone received: App=%s, ResetOption=%ld ***", pszName, pParam->usResetOption);
			}
			break;
		}
		case EVT_PrepareDelete:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareDelete received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_CreateBootprojectDone:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CreateBootprojectDone received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_LoadBootprojectDone:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpApp *pParam = (EVTPARAM_CmpApp *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_LoadBootprojectDone received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_RegisterBootproject:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpAppRegisterBootproject)
			{
				char *pszName;
				EVTPARAM_CmpAppRegisterBootproject *pParam = (EVTPARAM_CmpAppRegisterBootproject *)pEventParam->pParameter;
				pszName = pParam->pszAppName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_RegisterBootproject received: App=%s ***", pszName);
			}
			break;
		}
		case EVT_Test:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpTemplate && pEventParam->usVersion >= EVTVERSION_CmpTemplate)
			{
				pEventParam->usParamId = pEventParam->usParamId;
			}
			break;
		}
		case EVT_DenyLoadBootproject:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppDenyLoadBootproject)
			{
				char *pszName;			
				EVTPARAM_CmpAppDenyLoadBootproject *pParam = (EVTPARAM_CmpAppDenyLoadBootproject *)pEventParam->pParameter;
				
				/* To deny loading bootproject set:
				pParam->bDeny = 1; */

				pszName = pParam->pszAppName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DenyLoadBootproject received: App=%s, bDeny=%d ***", pszName, pParam->bDeny);
			}
			break;
		}
		case EVT_DenyStartBootproject:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppDenyStart)
			{
				char *pszName;			
				EVTPARAM_CmpAppDenyStart *pParam = (EVTPARAM_CmpAppDenyStart *)pEventParam->pParameter;
				
				/* To deny starting bootproject set:
				pParam->bDeny = 1; */

				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DenyStartBootproject received: App=%s, bDeny=%d ***", pszName, pParam->bDeny);
			}
			break;
		}
		case EVT_DenyStart:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppDenyStart)
			{
				char *pszName;			
				EVTPARAM_CmpAppDenyStart *pParam = (EVTPARAM_CmpAppDenyStart *)pEventParam->pParameter;
				
				/* To deny starting an application set:
				pParam->bDeny = 1; */

				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DenyStart received: App=%s, bDeny=%d ***", pszName, pParam->bDeny);
			}
			break;
		}
		case EVT_DenyStop:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppDenyStop)
			{
				char *pszName;			
				EVTPARAM_CmpAppDenyStop *pParam = (EVTPARAM_CmpAppDenyStop *)pEventParam->pParameter;
				
				/* To deny stopping an application set:
				pParam->bDeny = 1; */

				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DenyStop received: App=%s, Reason=%d, bDeny=%d ***", pszName, pParam->ulStopReason, pParam->bDeny);
			}
			break;
		}
		case EVT_PrepareStop:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppStop)
			{
				char *pszName;			
				EVTPARAM_CmpAppStop *pParam = (EVTPARAM_CmpAppStop *)pEventParam->pParameter;
				
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareStop received: App=%s, Reason=%d ***", pszName, pParam->ulStopReason);
			}
			break;
		}
		case EVT_StopDone:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppStop)
			{
				char *pszName;			
				EVTPARAM_CmpAppStop *pParam = (EVTPARAM_CmpAppStop *)pEventParam->pParameter;
				
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_StopDone received: App=%s, Reason=%d ***", pszName, pParam->ulStopReason);
			}
			break;
		}
		case EVT_OperatingStateChanged:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppOperatingStateChanged)
			{
				EVTPARAM_CmpAppOperatingStateChanged *pParam = (EVTPARAM_CmpAppOperatingStateChanged *)pEventParam->pParameter;
				if ((pParam->ulPrevOpState & OS_STORE_BOOTPROJECT) == 0 && (pParam->pApp->ulOpState & OS_STORE_BOOTPROJECT) != 0)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_OperatingStateChanged received: Start writing bootproject of App=%s", pParam->pApp->szName);
				else if ((pParam->ulPrevOpState & OS_STORE_BOOTPROJECT) != 0 && (pParam->pApp->ulOpState & OS_STORE_BOOTPROJECT) == 0)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_OperatingStateChanged received: End writing bootproject of App=%s", pParam->pApp->szName);
			}
			break;
		}
		case EVT_SourceDownload:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppSourceDownload)
			{
				EVTPARAM_CmpAppSourceDownload *pParam = (EVTPARAM_CmpAppSourceDownload *)pEventParam->pParameter;
				if (pParam->bBegin)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_SourceDownload received: Download started, Archive=%s", pParam->pszArchiveName);
				else
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_SourceDownload received: Download ended, Archive=%s", pParam->pszArchiveName);
			}
			break;
		}
		case EVT_DenyDelete:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppDenyDelete)
			{
				char *pszName;			
				EVTPARAM_CmpAppDenyDelete *pParam = (EVTPARAM_CmpAppDenyDelete*)pEventParam->pParameter;
				
				/* To deny deleting an application set: */
				/* pParam->bDeny = 1; */

				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_DenyDelete received: App=%s, bDeny=%d ***", pszName, pParam->bDeny);
			}
			break;
		}
		/**
		* Custom Download Service
		* =======================
		* a) Introduction
		* b) Codesnippet for a CODESYS plugin
		* c) Eventhandlig example of CmpTemplate
		* 
		* Introduction
		* ------------
		* With the Custom Download Service it is possible to transfer custom data to the PLC before the application download is finished. The data may be considered as part of the application, as the last POU so to say.
		* Unlike the application related external files in the device tree this transfer is much earlier, prior to any after-download events.
		* 
		* There are two requirements for this to achive: a CODESYS plugin which provides the data and an event-handler in the RTS which consumes the data.
		* 
		* NOTE: With V3.5 SP11 this Custom Download Service is now secured with a savepoint when the download context is passed via event to the custom event handler to make sure the download can be finished successfully.
		* 
		* Codesnippet for a CODESYS plugin
		* --------------------------------
		* This code example transfers 200k Bytes in total within ten 20k-blocks (chunks) to the PLC with subsequent tags, assuming the transfer buffer is about 95k in size (default). This code can be included in any plugin.
		* 
		* .. code-block:: csharp
		* 
		* 	[TypeGuid("{736290BC-8A9C-49fe-9BDB-2553263E9740}")]
		* 	public class CustomDownloadTagProvider : ICustomDownloadTagProvider
		* 	{
		* 		private const int ChunkSize = 20000;
		* 		private byte[] _bytes;
		* 		private int _index;
		* 		private int _tagId;
		* 
		* 		public CustomDownloadTagProvider()
		* 		{
		* 			_bytes = Enumerable.Range(0, 200000).Select(v => (byte)(v / ChunkSize + 1)).ToArray();
		* 		}
		* 
		* 		#region ICustomDownloadTagProvider Members
		* 
		* 		public ushort VendorSpecificTagID
		* 		{
		* 			get { return 0x074B; }
		* 		}
		* 
		* 		public bool ExistingDownloadTagsRequested
		* 		{
		* 			// Return TRUE if the OEM wants to double-check or record the written data
		* 			get { return false; }
		* 		}
		* 
		* 		public void GetCustomDownloadTag(IComplexNodeWriter complexNodeForAddingCustomTag, int nLastSuccessfulTagIndex, Guid ApplicationGuid, bool bIsOnlineChange, out bool bFinished)
		* 		{
		* 			Debug.Print("\t[TRY TO ADD TAG] Available Bytes:{0} Last successful tag index:{1}", complexNodeForAddingCustomTag.AvailableBytes, nLastSuccessfulTagIndex);
		* 
		* 			if (_index < _bytes.Length)
		* 			{
		* 				var remainBytes = this._bytes.Length - this._index;
		* 				var length = Math.Min(ChunkSize, remainBytes);
		* 				var dataTag = complexNodeForAddingCustomTag.AddDataTag(this._tagId, ContentAlignment.Align40);
		* 				dataTag.Write(this._bytes, this._index, length);
		* 				dataTag.AlignWithFillByte(0);
		* 				this._index += length;
		* 				Debug.Print("\t[SUCCESS ADD TAG] TAG ID:{0} SENT BYTES:{1} REMAINING BYTES:{2}", this._tagId, length, _bytes.Length - _index);
		* 
		* 				_tagId++;
		* 			}
		* 
		* 			bFinished = this._index >= this._bytes.Length;
		* 		}
		* 
		* 		public void SetExistingDownloadTags(BinaryWriter ExistingDownloadTags)
		* 		{
		* 			// Normally nothing to do here
		* 			
		* 			// Only of interest if the OEM wants to double-check or record the written data, e.g.
		* 			// Stream stream = new MemoryStream();
		* 			// stream = ExistingDownloadTags.BaseStream;
		* 		}
		* 
		* 		public void SetDownloadResult(ushort usResult)
		* 		{
		* 			_tagId = 0;
		* 			_index = 0;
		* 		}
		* 
		* 		#endregion
		* 	}
		* 
		* 
		* Eventhandlig example of CmpTemplate
		* -----------------------------------
		* This code consumes the vendor specific tags and its data in the download stream until either the transfer buffer ends or a next toplevel tag is found which is not for this vendor.
		* 
		* NOTE: The CMP_VENDORID must be correctly set. To correspond with the code snippet above it is 0x074B.
		* 
		*/
		case EVT_OEMDownloadServiceTag:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpApp_OEMServiceTag)
			{
				RTS_RESULT Result;
				short sResult = ERR_PARAMETER;
				RTS_UI32 ulTag, ulSize, ulToplevelTag;
				void *pContent;
				EVTPARAM_CmpApp_OEMServiceTag *pParam = (EVTPARAM_CmpApp_OEMServiceTag*)pEventParam->pParameter;
			
				/* Highword of a tag must always be the VendorID to have unique IDs! */ 
				if (((pParam->ulToplevelTag >> 16) & 0xFFFF) == CMP_VENDORID)
				{
					pContent = CAL_BTagReaderGetFirstTag(pParam->pReader, &ulToplevelTag, &ulTag, &ulSize, &Result);
					while (Result == ERR_OK)
					{
						if (ulToplevelTag == 0xFFFFFFFF)
							ulToplevelTag = pParam->ulToplevelTag;
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_OEMDownloadServiceTag received: bDownload=%d, ToplevelTag=0x%X, Tag=0x%X ***", 
							(pParam->pHeaderTag->usService == SRV_DOWNLOAD), ulToplevelTag, ulTag);
						pContent = CAL_BTagReaderGetNextTag(pParam->pReader, &ulToplevelTag, &ulTag, &ulSize, &Result);
						
						if (((ulToplevelTag >> 16) & 0xFFFF) != CMP_VENDORID)
							break;
					}
					sResult = ERR_OK;
				}

				/* For all reply tags, the toplevel tag must be reflected in the first tag of the reply! This contains the VendorID in the HighWord
				   to assign the reply to the correct OEM PlugIn in CoDeSys. */
				CAL_BTagWriterStartTag(pParam->pWriter, pParam->ulToplevelTag, align_40, 0);

					/* This is the OEM specific reply tag that can be used freely. */
					CAL_BTagWriterStartTag(pParam->pWriter, TAG_SERVICE_RESULT, align_42, 0);
						CAL_BTagWriterAppendBlob(pParam->pWriter, (unsigned char*)&sResult, sizeof(sResult));
					CAL_BTagWriterEndTag(pParam->pWriter, TAG_SERVICE_RESULT);

				CAL_BTagWriterEndTag(pParam->pWriter, pParam->ulToplevelTag);

				pParam->Result = ERR_OK;
			}
			break;
		}
		case EVT_PrepareExit:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpAppExit *pParam = (EVTPARAM_CmpAppExit *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareExit received: App=%s, Reason=%ld ***", pszName, pParam->ulExitReason);
			}
			break;
		}
		case EVT_ExitDone:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpApp)
			{
				char *pszName;
				EVTPARAM_CmpAppExit *pParam = (EVTPARAM_CmpAppExit *)pEventParam->pParameter;
				pszName = pParam->pApp->szName;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_ExitDone received: App=%s, Reason=%ld ***", pszName, pParam->ulExitReason);
			}
			break;
		}
		case EVT_CmpApp_Exception:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppException)
			{
				Task_Desc *pTaskDesc;
				EVTPARAM_CmpAppException *pParam = (EVTPARAM_CmpAppException *)pEventParam->pParameter;

				if (pParam->ulException == RTSEXCPT_RETAIN_IDENTITY_MISMATCH)
				{
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CmpApp_Exception received: App=%s, ulException=RTSEXCPT_RETAIN_IDENTITY_MISMATCH ***", pParam->pApp->szName);
				}
				else
				{
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CmpApp_Exception received: App=%s, ulException=0x%x ***", pParam->pApp->szName, pParam->ulException);
				}

				pTaskDesc = CAL_IecTaskGetDesc(pParam->hIecTask);
				if (pTaskDesc != NULL)
				{
					if (IsInIoUpdate(pTaskDesc))
					{
						/* An IEC-Task generates an exception in IO-Update! This is a serious error! */
					}
				}
			}
			break;
		}
		case EVT_Login:
		case EVT_Logout:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppComm)
			{
				EVTPARAM_CmpAppComm *pParam = (EVTPARAM_CmpAppComm *)pEventParam->pParameter;
				if (pEventParam->EventId == EVT_Login)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_Login received: App=%s, SessionId=%lx, AppSessionId=0x%lx ***", pParam->pApp->szName, pParam->ulSessionId, pParam->ulAppSessionId);
				else
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_Logout received: App=%s, SessionId=0x%lx, AppSessionId=0x%lx ***", pParam->pApp->szName, pParam->ulSessionId, pParam->ulAppSessionId);
			}
			break;
		}
		case EVT_AllocArea:
		{
			/* The following code is an example to handle the allocarea event. Can be used for testing too. */
			/*
			if (pEventParam->usParamId == EVTPARAMID_CmpAppArea)
			{
				RTS_RESULT Result;
				EVTPARAM_CmpAppArea *pParam = (EVTPARAM_CmpAppArea *)pEventParam->pParameter;
				if (pParam->bAlloc == 1)
				{
					if (IsArea(pParam->usType, DA_CODE) != 0)
					{
						pParam->pArea = (RTS_UI8*)CAL_SysMemAllocCode(COMPONENT_NAME, pParam->ulSize, &Result);
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_AllocArea received (alloc): App=%s, Type=0x%x, static [code] memory 0x%lx ***", pParam->pApp->szName, pParam->usType, pParam->pArea);
					}
					else if (IsArea(pParam->usType, DA_DATA) != 0)
					{
						pParam->pArea = (RTS_UI8*)CAL_SysMemAllocData(COMPONENT_NAME, pParam->ulSize, &Result);
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_AllocArea received (alloc): App=%s, Type=0x%x, static [data] memory 0x%lx ***", pParam->pApp->szName,  pParam->usType, pParam->pArea);
					}
				}
				else
				{
					if (IsArea(pParam->usType, DA_CODE) != 0)
					{
						Result = CAL_SysMemFreeCode(COMPONENT_NAME, pParam->pArea);
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_AllocArea received (free): App=%s, Type=0x%x, static [code] memory 0x%lx ***", pParam->pApp->szName, pParam->usType, pParam->pArea);
					}
					else if (IsArea(pParam->usType, DA_DATA) != 0)
					{
						Result = CAL_SysMemFreeData(COMPONENT_NAME, pParam->pArea);
						CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_AllocArea received (free): App=%s, Type=0x%x, static [data] memory 0x%lx ***", pParam->pApp->szName, pParam->usType, pParam->pArea);
					}
				}
			}
			*/
			break;
		}
		default:
			break;
	}
}

static void CDECL CBBreakpoints(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		case EVT_CmpAppBP_CodePatch:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpAppBP_CodePatch)
			{
				EVTPARAM_CmpAppBP_CodePatch *pParam = (EVTPARAM_CmpAppBP_CodePatch*)pEventParam->pParameter;
				if (pParam->bPatch)
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CmpAppBP_CodePatch: Begin received: pbyCodePos=%p, nCodeLen=%ld ***", pParam->pbyCodePosition, pParam->nCodeLen);
				else
					CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CmpAppBP_CodePatch: End received: pbyCodePos=%p, nCodeLen=%ld ***", pParam->pbyCodePosition, pParam->nCodeLen);
			}
			break;
		}
		default:
			break;
	}
}

static void CDECL CBMonitoring(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		case EVT_PrepareWriteVariable:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpMonitor2)
			{
				EVTPARAM_CmpMonitorWriteVar2 *pParam = (EVTPARAM_CmpMonitorWriteVar2*)pEventParam->pParameter;
				/*TODO: pParam->bDeny = 1;*/
				pParam->cmpId = COMPONENT_ID;
			}
			break;
		}
		case EVT_PrepareForceVariable:
		{
			if (pEventParam->usVersion >= EVTVERSION_CmpMonitorForce2)
			{
				EVTPARAM_CmpMonitorForceVar2 *pParam = (EVTPARAM_CmpMonitorForceVar2*)pEventParam->pParameter;
				/*TODO: pParam->bDeny = 1;*/
				pParam->cmpId = COMPONENT_ID;
			}
			break;
		}
		default:
			break;
	}
}

static void CDECL CBIecVarAccess(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		/* For external event triggered tasks */
		case EVT_CmpIecVarAccess_PrepareWriteVariable:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpIecVarAccess_WriteVar)
			{
				RTS_RESULT Result;
				char szSymbol[255];
				EVTPARAM_CmpIecVarAccess_WriteVar *pParam = (EVTPARAM_CmpIecVarAccess_WriteVar *)pEventParam->pParameter;

				/* TODO: You can deny the write opration via IecVarAccess with this line:	pParam->bDeny = 1; */

				CAL_IecVarAccGetNodeFullPath3(pParam->hInterface, pParam->hNode, pParam->pVariableInformation, szSymbol, sizeof(szSymbol), &Result);
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CmpIecVarAccess_PrepareWriteVariable received: Symbol=%s ***", szSymbol);
			}
			break;
		}
		case EVT_CmpIecVarAccess_WriteVariableDone:
		{
			if (pEventParam->usParamId == EVTPARAMID_CmpIecVarAccess_WriteVar)
			{
				RTS_RESULT Result;
				char szSymbol[255];
				EVTPARAM_CmpIecVarAccess_WriteVar *pParam = (EVTPARAM_CmpIecVarAccess_WriteVar *)pEventParam->pParameter;

				CAL_IecVarAccGetNodeFullPath3(pParam->hInterface, pParam->hNode, pParam->pVariableInformation, szSymbol, sizeof(szSymbol), &Result);
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_CmpIecVarAccess_WriteVariableDone received: Symbol=%s ***", szSymbol);
			}
			break;
		}
		default:
			break;
	}
}

static void CDECL CBIoMgr(EventParam *pEventParam)
{
	if (pEventParam->usParamId == EVTPARAMID_CmpIoMgr)
	{
		/*EVTPARAM_CmpIoMgr *pParam = (EVTPARAM_CmpIoMgr *)pEventParam->pParameter;*/

		switch (pEventParam->EventId)
		{	
			case EVT_ConfigAppStartedDone:
			{
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_ConfigAppStartedDone received ***");
				break;
			}
			case EVT_PrepareConfigAppStopped:
			{
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_PrepareConfigAppStopped received ***");
				break;
			}
			case EVT_ConfigAppStoppedDone:
			{
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_ConfigAppStoppedDone received ***");
				break;
			}
			default:
				break;
		}
	}
}

static void CDECL CBSysExcept(EventParam *pEventParam)
{
	if (pEventParam->usParamId == EVTPARAMID_SysExcept)
	{
		switch (pEventParam->EventId)
		{	
			case EVT_EXCPT_GenerateException2:
			{
				RTS_RESULT result;
				APPLICATION *pApp;
				RTS_HANDLE  hSysTask;
				RTS_HANDLE hIecTask;
				EVTPARAM_SysExcept *pParam = (EVTPARAM_SysExcept *)pEventParam->pParameter;
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_EXCPT_GenerateException2 received ***");

				if (CHK_SysTaskGetHandleByOSHandle)
				{
					hSysTask = CAL_SysTaskGetHandleByOSHandle(pParam->uiTaskOSHandle, &result);
					if (hSysTask != RTS_INVALID_HANDLE && result == ERR_OK)
					{
						pApp = CAL_AppGetFirstApp(NULL);
						while (pApp != NULL)
						{
							hIecTask = CAL_IecTaskGetFirst2(pApp, NULL);
							while (hIecTask != RTS_INVALID_HANDLE)
							{
								Task_Desc *pTaskDesc = CAL_IecTaskGetDesc(hIecTask);
								if (pTaskDesc != NULL)
								{
									if (strcmp(pTaskDesc->pInfo->pszName, CAL_SysTaskGetName(hSysTask, NULL)) == 0 && IsInIoUpdate(pTaskDesc))
									{
										/* An IEC-Task generates an exception in IO-Update! This is a serious error! */
									}
								}
								hIecTask = CAL_IecTaskGetNext2(pApp, hIecTask, NULL);
							}
							pApp = CAL_AppGetNextApp(pApp, NULL);
						}
					}
				}
				break;
			}
			default:
				break;
		}
	}
}

static void CDECL CBSysFile(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{
		case EVT_SysFileOpen:
		{
			char szPath[RTS_MAXSTR];
			EVTPARAM_SysFileOpen *pParam = (EVTPARAM_SysFileOpen *)pEventParam->pParameter;

			if (strlen(pParam->pszPath) + 1 >= RTS_MAXSTR)
				strcpy(szPath, pParam->pszPath + strlen(pParam->pszPath) + 1 - RTS_MAXSTR);
			else
				strcpy(szPath, pParam->pszPath);

			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_FileOpen received. Mode %d Handle %x ***", pParam->am, pParam->hFile);
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** File %s ***", szPath);

			break;
		}
		case EVT_SysFileClose:
		{
			EVTPARAM_SysFileClose *pParam = (EVTPARAM_SysFileClose *)pEventParam->pParameter;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_FileClose received. Handle %x ***", pParam->hFile);

			break;
		}
	default:
		break;
	}
}

static void CDECL CBChannelServer(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{
		case EVT_ChSChannelOpened:
		{
			EVTPARAM_CmpChS_ChannelOpened *pParam = (EVTPARAM_CmpChS_ChannelOpened *)pEventParam->pParameter;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_ChSChannelOpened received. ulChannelHandle=0x%08x", pParam->ulChannelHandle);
			break;
		}
		case EVT_ChSChannelClosed:
		{
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_ChSChannelClosed received.");
			break;
		}
		default:
			break;
	}
}

static void CDECL CBSupervisor(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{
		case EVT_Supervisor_StateChanged:
		{
			EVTPARAM_CmpSupervisor_StateChanged *pParam = (EVTPARAM_CmpSupervisor_StateChanged *)pEventParam->pParameter;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_Supervisor_StateChanged received: RegOperations=%ld, Operations=%ld, FailedOperations=%ld", pParam->nNumOfRegisteredOperations, pParam->nNumOfOperations, pParam->nNumOfFailedOperations);
			break;
		}
		default:
			break;
	}
}

static void CDECL CBUserMgr(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{
		case EVT_UserMgrDatabaseChanged:
		{
			EVTPARAM_CmpUserMgrDatabaseChanged *pParam = (EVTPARAM_CmpUserMgrDatabaseChanged *)pEventParam->pParameter;
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "*** EVT_UserMgrDatabaseChanged received: UserManagementChanged=%d, RightsManagementChanged=%d", pParam->bUserManagementChanged, pParam->bRightsManagementChanged);
			break;
		}
		default:
			break;
	}
}

static void CDECL CBLogger(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{
		case EVT_LogAdd:
		{
			/* In this event you get all log messages which are created after CH_INIT2!
			   This implementation is only for testing.
			   Don't use the logger here to avoid endless recursions!
			 */
#if 0
			char szInfo[255];
			EVTPARAM_CmpLogAdd *pParam = (EVTPARAM_CmpLogAdd *)pEventParam->pParameter;
			CAL_CMUtlvsnprintf(szInfo, sizeof(szInfo), pParam->pszInfo, pParam->pargList);
			printf("*** EVT_LogAdd received: CmpId=%ld, iClassID=%ld, iErrorID=%ld, iInfoID=%ld, pszInfo=%s\n", pParam->CmpId, pParam->iClassID, pParam->iErrorID, pParam->iInfoID, szInfo);
#endif
			break;
		}
		default:
			break;
	}
}