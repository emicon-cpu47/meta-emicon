/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 * <name>Component IO-driver template</name>
 * <description> 
 *  An example on how to implement an IO-driver in C.
 * </description>
 *
 * <copyright>
 * Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 * </copyright>
 */
#ifndef _IODRVTEMPLATEDEP_H_
#define _IODRVTEMPLATEDEP_H_

#define COMPONENT_NAME "IoDrvTemplate" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_IoDrvTemplate)
#define COMPONENT_NAME_UNQUOTED IoDrvTemplate






#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID       0x0001

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"

#define CMPID_IoDrvTemplate		0x2001								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvTemplate	ADDVENDORID(CMP_VENDORID, 0x2001)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */


#include "SysMemItf.h"


#include "CmpSettingsItf.h"


#include "CMItf.h"


#include "CmpIoMgrItf.h"


#include "CmpEventMgrItf.h"


#include "CmpAppItf.h"


#include "CmpIecTaskItf.h"


/*Obsolete include: CMUtilsItf.m4*/


#include "SysCpuHandlingItf.h"


#include "SysTimeItf.h"







#include "CmpIoDrvItf.h"
#include "CmpIoDrvParameterItf.h"









    











































     














































#ifdef CPLUSPLUS
    #define INIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT initResult;\
        if (pICmpLog == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpLog, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpLog = (ICmpLog *)pIBase->QueryInterface(pIBase, ITFID_ICmpLog, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pICMUtils == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCMUtils, &initResult); \
            if (pIBase != NULL) \
            { \
                pICMUtils = (ICMUtils *)pIBase->QueryInterface(pIBase, ITFID_ICMUtils, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pISysTime == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysTime, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysTime = (ISysTime *)pIBase->QueryInterface(pIBase, ITFID_ISysTime, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysCpuHandling == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysCpuHandling, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysCpuHandling = (ISysCpuHandling *)pIBase->QueryInterface(pIBase, ITFID_ISysCpuHandling, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		  if (pICmpIecTask == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpIecTask, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpIecTask = (ICmpIecTask *)pIBase->QueryInterface(pIBase, ITFID_ICmpIecTask, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpApp == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpApp, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpApp = (ICmpApp *)pIBase->QueryInterface(pIBase, ITFID_ICmpApp, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpIoMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpIoMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpIoMgr = (ICmpIoMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpIoMgr, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICM == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCM, &initResult); \
            if (pIBase != NULL) \
            { \
                pICM = (ICM *)pIBase->QueryInterface(pIBase, ITFID_ICM, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpSettings == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSettings, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSettings = (ICmpSettings *)pIBase->QueryInterface(pIBase, ITFID_ICmpSettings, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysMem == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysMem, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysMem = (ISysMem *)pIBase->QueryInterface(pIBase, ITFID_ISysMem, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pISysTime = NULL; \
          pISysCpuHandling = NULL; \
          /*Obsolete include CMUtils*/ \
		  pICmpIecTask = NULL; \
          pICmpApp = NULL; \
          pICmpEventMgr = NULL; \
          pICmpIoMgr = NULL; \
          pICM = NULL; \
          pICmpSettings = NULL; \
          pISysMem = NULL; \
           \
    }
    #define EXIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT exitResult;\
        if (pICmpLog != NULL) \
        { \
            pIBase = (IBase *)pICmpLog->QueryInterface(pICmpLog, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpLog = NULL; \
            } \
        } \
        if (pICMUtils != NULL) \
        { \
            pIBase = (IBase *)pICMUtils->QueryInterface(pICMUtils, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICMUtils = NULL; \
            } \
        } \
        if (pISysTime != NULL) \
        { \
            pIBase = (IBase *)pISysTime->QueryInterface(pISysTime, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysTime = NULL; \
            } \
        } \
          if (pISysCpuHandling != NULL) \
        { \
            pIBase = (IBase *)pISysCpuHandling->QueryInterface(pISysCpuHandling, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysCpuHandling = NULL; \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		  if (pICmpIecTask != NULL) \
        { \
            pIBase = (IBase *)pICmpIecTask->QueryInterface(pICmpIecTask, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpIecTask = NULL; \
            } \
        } \
          if (pICmpApp != NULL) \
        { \
            pIBase = (IBase *)pICmpApp->QueryInterface(pICmpApp, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpApp = NULL; \
            } \
        } \
          if (pICmpEventMgr != NULL) \
        { \
            pIBase = (IBase *)pICmpEventMgr->QueryInterface(pICmpEventMgr, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpEventMgr = NULL; \
            } \
        } \
          if (pICmpIoMgr != NULL) \
        { \
            pIBase = (IBase *)pICmpIoMgr->QueryInterface(pICmpIoMgr, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpIoMgr = NULL; \
            } \
        } \
          if (pICM != NULL) \
        { \
            pIBase = (IBase *)pICM->QueryInterface(pICM, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICM = NULL; \
            } \
        } \
          if (pICmpSettings != NULL) \
        { \
            pIBase = (IBase *)pICmpSettings->QueryInterface(pICmpSettings, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSettings = NULL; \
            } \
        } \
          if (pISysMem != NULL) \
        { \
            pIBase = (IBase *)pISysMem->QueryInterface(pISysMem, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysMem = NULL; \
            } \
        } \
           \
    }
#else
    #define INIT_STMT
    #define INIT_LOCALS_STMT
    #define EXIT_STMT
#endif



#if defined(STATIC_LINK)
    #define IMPORT_STMT
#else
    #define IMPORT_STMT \
    {\
        RTS_RESULT importResult = ERR_OK;\
        RTS_RESULT TempResult = ERR_OK;\
        INIT_STMT   \
        TempResult = GET_LogAdd(CM_IMPORT_OPTIONAL_FUNCTION); \
        TempResult = GET_CMUtlMemCpy(CM_IMPORT_OPTIONAL_FUNCTION); \
        if (ERR_OK == importResult ) importResult = GET_SysTimeGetMs(0);\
          if (ERR_OK == importResult ) importResult = GET_SysCpuTestAndReset(0);\
          if (ERR_OK == importResult ) importResult = GET_SysCpuTestAndSet(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_IecTaskRegisterSlotCallbacks(0);\
          if (ERR_OK == importResult ) importResult = GET_IecTaskRegisterSlotCallback(0);\
          if (ERR_OK == importResult ) importResult = GET_EventPost(0);\
          if (ERR_OK == importResult ) importResult = GET_EventRegisteredCallbacks(0);\
          if (ERR_OK == importResult ) importResult = GET_EventUnregisterCallbackFunction(0);\
          if (ERR_OK == importResult ) importResult = GET_EventRegisterCallbackFunction(0);\
          if (ERR_OK == importResult ) importResult = GET_EventUnregisterCallback(0);\
          if (ERR_OK == importResult ) importResult = GET_EventRegisterCallback(0);\
          if (ERR_OK == importResult ) importResult = GET_EventClose(0);\
          if (ERR_OK == importResult ) importResult = GET_EventOpen(0);\
          if (ERR_OK == importResult ) importResult = GET_EventDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_EventCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_IoDrvDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_IoDrvCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrWatchdogTrigger(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrCopyOutputLE(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrCopyInputLE(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigResetDiagnosis(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigSetDiagnosis(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrUnregisterInstance(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrRegisterInstance(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrSetDriverProperties(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigResetDiagnosis(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigSetDiagnosis(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetParameterValuePointer(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetParameterValueDword(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetParameterValueWord(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetNextChild(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetFirstChild(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetNextConnector(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetFirstConnector(0);\
          if (ERR_OK == importResult ) importResult = GET_IoMgrConfigGetParameter(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetIntValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgSetIntValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgSetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeArea(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocArea(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeData(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocData(0);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef IODRVTEMPLATE_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
                                    
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef IODRVTEMPLATE_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
                                    
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
                                    \
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#else
#define EXPORT_CMPITF_STMT \
    {\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#endif
#define EXPORT_CPP_STMT


#if defined(STATIC_LINK)
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#else
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
        ExpResult = s_pfCMRegisterAPI(s_ItfTable, 0, 0, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#endif

#define USE_STMT \
    /*lint -save --e{528} --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    static const CMP_EXT_FUNCTION_REF s_ExternalsTable[] =\
    {\
        EXPORT_EXTREF_STMT\
        EXPORT_EXTREF2_STMT\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    };\
    static const CMP_EXT_FUNCTION_REF s_ItfTable[] = EXPORT_CMPITF_STMT; \
    /*lint -restore */  \
    static int CDECL ExportFunctions(void); \
    static int CDECL ImportFunctions(void); \
    static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult); \
    static RTS_RESULT CDECL DeleteInstance(IBase *pIBase); \
    static RTS_UI32 CDECL CmpGetVersion(void); \
    static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2); \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	ITF_SysMem     \
	ITF_CmpSettings     \
	ITF_CM     \
	ITF_CmpIoMgr     \
	ITF_CmpEventMgr     \
	ITF_CmpApp     \
	ITF_CmpIecTask     \
	/*obsolete entry ITF_CMUtils*/      \
	ITF_SysCpuHandling     \
	ITF_SysTime      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_SysMemAllocArea      \
    USE_SysMemFreeArea      \
    USE_SettgSetStringValue      \
    USE_SettgGetStringValue      \
    USE_SettgSetIntValue      \
    USE_SettgGetIntValue      \
    USE_IoMgrConfigGetParameter      \
    USE_IoMgrConfigGetFirstConnector      \
    USE_IoMgrConfigGetNextConnector      \
    USE_IoMgrConfigGetFirstChild      \
    USE_IoMgrConfigGetNextChild      \
    USE_IoMgrConfigGetParameterValueWord      \
    USE_IoMgrConfigGetParameterValueDword      \
    USE_IoMgrConfigGetParameterValuePointer      \
    USE_IoMgrConfigSetDiagnosis      \
    USE_IoMgrConfigResetDiagnosis      \
    USE_IoMgrSetDriverProperties      \
    USE_IoMgrRegisterInstance      \
    USE_IoMgrUnregisterInstance      \
    USE_IoMgrConfigSetDiagnosis      \
    USE_IoMgrConfigResetDiagnosis      \
    USE_IoMgrCopyInputLE      \
    USE_IoMgrCopyOutputLE      \
    USE_IoMgrWatchdogTrigger      \
    USE_IoDrvCreate      \
    USE_IoDrvDelete      \
    USE_EventCreate      \
    USE_EventDelete      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventRegisterCallback      \
    USE_EventUnregisterCallback      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_EventRegisteredCallbacks      \
    USE_EventPost      \
    USE_IecTaskRegisterSlotCallback      \
    USE_IecTaskRegisterSlotCallbacks      \
    USE_CMUtlSafeStrCpy      \
    USE_SysCpuTestAndSet      \
    USE_SysCpuTestAndReset      \
    USE_SysTimeGetMs     
#define USEIMPORT_STMT \
    /*lint -save --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    /*lint -restore */  \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	ITF_SysMem    \
	ITF_CmpSettings    \
	ITF_CM    \
	ITF_CmpIoMgr    \
	ITF_CmpEventMgr    \
	ITF_CmpApp    \
	ITF_CmpIecTask    \
	/*obsolete entry ITF_CMUtils*/     \
	ITF_SysCpuHandling    \
	ITF_SysTime     \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_SysMemAllocArea      \
    USE_SysMemFreeArea      \
    USE_SettgSetStringValue      \
    USE_SettgGetStringValue      \
    USE_SettgSetIntValue      \
    USE_SettgGetIntValue      \
    USE_IoMgrConfigGetParameter      \
    USE_IoMgrConfigGetFirstConnector      \
    USE_IoMgrConfigGetNextConnector      \
    USE_IoMgrConfigGetFirstChild      \
    USE_IoMgrConfigGetNextChild      \
    USE_IoMgrConfigGetParameterValueWord      \
    USE_IoMgrConfigGetParameterValueDword      \
    USE_IoMgrConfigGetParameterValuePointer      \
    USE_IoMgrConfigSetDiagnosis      \
    USE_IoMgrConfigResetDiagnosis      \
    USE_IoMgrSetDriverProperties      \
    USE_IoMgrRegisterInstance      \
    USE_IoMgrUnregisterInstance      \
    USE_IoMgrConfigSetDiagnosis      \
    USE_IoMgrConfigResetDiagnosis      \
    USE_IoMgrCopyInputLE      \
    USE_IoMgrCopyOutputLE      \
    USE_IoMgrWatchdogTrigger      \
    USE_IoDrvCreate      \
    USE_IoDrvDelete      \
    USE_EventCreate      \
    USE_EventDelete      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventRegisterCallback      \
    USE_EventUnregisterCallback      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_EventRegisteredCallbacks      \
    USE_EventPost      \
    USE_IecTaskRegisterSlotCallback      \
    USE_IecTaskRegisterSlotCallbacks      \
    USE_CMUtlSafeStrCpy      \
    USE_SysCpuTestAndSet      \
    USE_SysCpuTestAndReset      \
    USE_SysTimeGetMs     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_SysMem    \
	EXTITF_CmpSettings    \
	EXTITF_CM    \
	EXTITF_CmpIoMgr    \
	EXTITF_CmpEventMgr    \
	EXTITF_CmpApp    \
	EXTITF_CmpIecTask    \
	/*obsolete entry EXTITF_CMUtils*/     \
	EXTITF_SysCpuHandling    \
	EXTITF_SysTime     \
    EXT_SysMemAllocData  \
    EXT_SysMemFreeData  \
    EXT_SysMemAllocArea  \
    EXT_SysMemFreeArea  \
    EXT_SettgSetStringValue  \
    EXT_SettgGetStringValue  \
    EXT_SettgSetIntValue  \
    EXT_SettgGetIntValue  \
    EXT_IoMgrConfigGetParameter  \
    EXT_IoMgrConfigGetFirstConnector  \
    EXT_IoMgrConfigGetNextConnector  \
    EXT_IoMgrConfigGetFirstChild  \
    EXT_IoMgrConfigGetNextChild  \
    EXT_IoMgrConfigGetParameterValueWord  \
    EXT_IoMgrConfigGetParameterValueDword  \
    EXT_IoMgrConfigGetParameterValuePointer  \
    EXT_IoMgrConfigSetDiagnosis  \
    EXT_IoMgrConfigResetDiagnosis  \
    EXT_IoMgrSetDriverProperties  \
    EXT_IoMgrRegisterInstance  \
    EXT_IoMgrUnregisterInstance  \
    EXT_IoMgrConfigSetDiagnosis  \
    EXT_IoMgrConfigResetDiagnosis  \
    EXT_IoMgrCopyInputLE  \
    EXT_IoMgrCopyOutputLE  \
    EXT_IoMgrWatchdogTrigger  \
    EXT_IoDrvCreate  \
    EXT_IoDrvDelete  \
    EXT_EventCreate  \
    EXT_EventDelete  \
    EXT_EventOpen  \
    EXT_EventClose  \
    EXT_EventRegisterCallback  \
    EXT_EventUnregisterCallback  \
    EXT_EventRegisterCallbackFunction  \
    EXT_EventUnregisterCallbackFunction  \
    EXT_EventRegisteredCallbacks  \
    EXT_EventPost  \
    EXT_IecTaskRegisterSlotCallback  \
    EXT_IecTaskRegisterSlotCallbacks  \
    EXT_CMUtlSafeStrCpy  \
    EXT_SysCpuTestAndSet  \
    EXT_SysCpuTestAndReset  \
    EXT_SysTimeGetMs 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry IoDrvTemplate__Entry
#endif


#ifdef CPLUSPLUS

class CIoDrvTemplate : public ICmpIoDrv , public ICmpIoDrvParameter 
{
    public:
        CIoDrvTemplate() : hIoDrvTemplate(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CIoDrvTemplate()
        {
        }
        virtual unsigned long AddRef(IBase *pIBase = NULL)
        {
            iRefCount++;
            return iRefCount;
        }
        virtual unsigned long Release(IBase *pIBase = NULL)
        {
            iRefCount--;
            if (iRefCount == 0)
            {
                delete this;
                return 0;
            }
            return iRefCount;
        }

        
        virtual void* QueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult)
        {
            void *pItf;
            if (iid == ITFID_IBase)
                pItf = dynamic_cast<IBase *>((ICmpIoDrv *)this);            
            else if (iid == ITFID_ICmpIoDrv)
                pItf = dynamic_cast<ICmpIoDrv *>(this); 
            else if (iid == ITFID_ICmpIoDrvParameter)
                pItf = dynamic_cast<ICmpIoDrvParameter *>(this); 
            else
            {
                if (pResult != NULL)
                    *pResult = ERR_NOTIMPLEMENTED;
                return NULL;
            }
            if (pResult != (RTS_RESULT *)1)
                (reinterpret_cast<IBase *>(pItf))->AddRef();
            if (pResult != NULL && pResult != (RTS_RESULT *)1)
                *pResult = ERR_OK;
            return pItf;
        }
        virtual RTS_RESULT CDECL IIoDrvReadParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
        virtual RTS_RESULT CDECL IIoDrvWriteParameter(IoConfigConnector *pConnector, IoConfigParameter *pParameter, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
        virtual RTS_HANDLE CDECL IIoDrvCreate(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IIoDrvDelete(RTS_HANDLE hIIoDrv);
        virtual RTS_RESULT CDECL IIoDrvGetInfo(IoDrvInfo **ppIoDrv);
        virtual RTS_RESULT CDECL IIoDrvGetModuleDiagnosis(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoDrvIdentify(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoDrvReadInputs(IoConfigConnectorMap *pConnectorMapList, int nCount);
        virtual RTS_RESULT CDECL IIoDrvScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount);
        virtual RTS_RESULT CDECL IIoDrvStartBusCycle(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoDrvUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount);
        virtual RTS_RESULT CDECL IIoDrvUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount);
        virtual RTS_RESULT CDECL IIoDrvWatchdogTrigger(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoDrvWriteOutputs(IoConfigConnectorMap *pConnectorMapList, int nCount);

    public:
        RTS_HANDLE hIoDrvTemplate;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* IoDrvTemplate Declarations for uRTS */
/* This header is included only to have the CMP_EXT_FUNCTION_REF type definition. */
/* In final version this type could be moved to CmpItf.h, if we will use */
/* the same structure for representing an export entry. */
#include <_OptionalIncludes/Profiles/uRTS/CMMicro.h>

/* Undefine these macros if they were previously defined */

#ifdef USE_HOOK_FUNCTION
#undef USE_HOOK_FUNCTION
#endif

#ifdef USE_CMEXPORTFUNCTIONS
#undef USE_CMEXPORTFUNCTIONS
#endif

#ifdef USE_EXPORT_EXTREF
#undef USE_EXPORT_EXTREF
#endif

#ifdef USE_EXPORT_CMPITF
#undef USE_EXPORT_CMPITF
#endif

#ifdef USE_ENTRY_LINKAGE
#undef USE_ENTRY_LINKAGE
#endif

#ifdef IMPLEMENT_EXPORT_FUNCTIONS
#undef IMPLEMENT_EXPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_IMPORT_FUNCTIONS
#undef IMPLEMENT_IMPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_GETVERSION_FUNCTIONS
#undef IMPLEMENT_GETVERSION_FUNCTIONS
#endif

#ifdef EXPORT_STMT
#undef EXPORT_STMT
#endif

#ifdef USEEXTERN_STMT
#undef USEEXTERN_STMT
#endif

#ifdef USE_STMT
#undef USE_STMT
#endif

#ifdef USEIMPORT_STMT
#undef USEIMPORT_STMT
#endif

/* This wrapper is only required in uRTS */
#define USE_HOOK_FUNCTION	RTS_RESULT IoDrvTemplate_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF IoDrvTemplate_ExternalsTable[] = \
	{\
		EXPORT_EXTREF_STMT\
		EXPORT_EXTREF2_STMT\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0 }\
	};

/* No component interface exports in uRTS */
#define USE_EXPORT_CMPITF

/* No dynamic linkage in uRTS */
#define USE_ENTRY_LINKAGE

/* No ExportFunctions() routine in uRTS */
#define IMPLEMENT_EXPORT_FUNCTIONS

/* No ImportFunctions() routine in uRTS */
#define IMPLEMENT_IMPORT_FUNCTIONS

/* No CmpGetVersion() routine in uRTS */
#define IMPLEMENT_GETVERSION_FUNCTIONS

/* No usage of externals from the component secondary C-modules in uRTS */
#define USEEXTERN_STMT

/* No need for export calling to the Component Manager in uRTS */
#define EXPORT_STMT

/* No need for importing from secondary C-modules */
#define USEIMPORT_STMT

/* Instantiation macro for a root component C-module */
#define USE_STMT\
	static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);\
		USE_EXPORT_EXTREF;\
		USE_EXPORT_CMPITF;\
		USE_HOOK_FUNCTION;\
		USE_CMEXPORTFUNCTIONS;\


/******************************************************************************/
#endif

#endif /*WIN32_RESOURCES*/
#endif /*_DEP_H_*/
