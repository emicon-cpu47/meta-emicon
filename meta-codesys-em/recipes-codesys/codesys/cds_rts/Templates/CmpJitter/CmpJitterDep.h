/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component Template</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
#ifndef _CMPJITTERDEP_H_
#define _CMPJITTERDEP_H_

#define COMPONENT_NAME "CmpJitter" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpJitter)
#define COMPONENT_NAME_UNQUOTED CmpJitter






#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID       0x0001

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"				

#define CMPID_CmpJitter		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpJitter	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpJitter		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */






#include "CmpEventCallbackItf.h"







#include "CmpSrvItf.h"


#include "CmpBinTagUtilItf.h"


#include "SysTaskItf.h"


#include "SysMemItf.h"


#include "CmpSettingsItf.h"


#include "CmpAppItf.h"


#include "CmpAppBPItf.h"


#include "CmpEventMgrItf.h"


#include "SysTimeItf.h"


#include "SysEventItf.h"


#include "CmpScheduleItf.h"


#include "SysCpuHandlingItf.h"


#include "CmpIecTaskItf.h"


#include "SysSocketItf.h"


#include "SysMsgQItf.h"



    




























































     






























































    
      
     


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
        if (pISysMsgQ == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysMsgQ, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysMsgQ = (ISysMsgQ *)pIBase->QueryInterface(pIBase, ITFID_ISysMsgQ, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysSocket == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysSocket, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysSocket = (ISysSocket *)pIBase->QueryInterface(pIBase, ITFID_ISysSocket, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpIecTask == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpIecTask, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpIecTask = (ICmpIecTask *)pIBase->QueryInterface(pIBase, ITFID_ICmpIecTask, &initResult); \
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
          if (pICmpSchedule == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSchedule, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSchedule = (ICmpSchedule *)pIBase->QueryInterface(pIBase, ITFID_ICmpSchedule, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysEvent == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysEvent, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysEvent = (ISysEvent *)pIBase->QueryInterface(pIBase, ITFID_ISysEvent, &initResult); \
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
          if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpAppBP == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpAppBP, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpAppBP = (ICmpAppBP *)pIBase->QueryInterface(pIBase, ITFID_ICmpAppBP, &initResult); \
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
          if (pISysTask == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysTask, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysTask = (ISysTask *)pIBase->QueryInterface(pIBase, ITFID_ISysTask, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpBinTagUtil == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpBinTagUtil, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpBinTagUtil = (ICmpBinTagUtil *)pIBase->QueryInterface(pIBase, ITFID_ICmpBinTagUtil, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpSrv == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSrv, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSrv = (ICmpSrv *)pIBase->QueryInterface(pIBase, ITFID_ICmpSrv, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pISysMsgQ = NULL; \
          pISysSocket = NULL; \
          pICmpIecTask = NULL; \
          pISysCpuHandling = NULL; \
          pICmpSchedule = NULL; \
          pISysEvent = NULL; \
          pISysTime = NULL; \
          pICmpEventMgr = NULL; \
          pICmpAppBP = NULL; \
          pICmpApp = NULL; \
          pICmpSettings = NULL; \
          pISysMem = NULL; \
          pISysTask = NULL; \
          pICmpBinTagUtil = NULL; \
          pICmpSrv = NULL; \
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
        if (pISysMsgQ != NULL) \
        { \
            pIBase = (IBase *)pISysMsgQ->QueryInterface(pISysMsgQ, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysMsgQ = NULL; \
            } \
        } \
          if (pISysSocket != NULL) \
        { \
            pIBase = (IBase *)pISysSocket->QueryInterface(pISysSocket, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysSocket = NULL; \
            } \
        } \
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
          if (pICmpSchedule != NULL) \
        { \
            pIBase = (IBase *)pICmpSchedule->QueryInterface(pICmpSchedule, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSchedule = NULL; \
            } \
        } \
          if (pISysEvent != NULL) \
        { \
            pIBase = (IBase *)pISysEvent->QueryInterface(pISysEvent, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysEvent = NULL; \
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
          if (pICmpAppBP != NULL) \
        { \
            pIBase = (IBase *)pICmpAppBP->QueryInterface(pICmpAppBP, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpAppBP = NULL; \
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
          if (pISysTask != NULL) \
        { \
            pIBase = (IBase *)pISysTask->QueryInterface(pISysTask, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysTask = NULL; \
            } \
        } \
          if (pICmpBinTagUtil != NULL) \
        { \
            pIBase = (IBase *)pICmpBinTagUtil->QueryInterface(pICmpBinTagUtil, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpBinTagUtil = NULL; \
            } \
        } \
          if (pICmpSrv != NULL) \
        { \
            pIBase = (IBase *)pICmpSrv->QueryInterface(pICmpSrv, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSrv = NULL; \
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
        if (ERR_OK == importResult ) TempResult = GET_SysMemIsValidPointer(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) importResult = GET_SysMsgQSend(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMsgQCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskExit(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskResume(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskEnd(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskLeave(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMsgQRecv(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskEnter(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTimeGetMs(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockPing(0);\
          if (ERR_OK == importResult ) importResult = GET_IecTaskCycle(0);\
          if (ERR_OK == importResult ) importResult = GET_SysEventSet(0);\
          if (ERR_OK == importResult ) importResult = GET_SysCpuCallIecFuncWithParams(0);\
          if (ERR_OK == importResult ) importResult = GET_EventPostByEvent(0);\
          if (ERR_OK == importResult ) importResult = GET_EventPost(0);\
          if (ERR_OK == importResult ) importResult = GET_EventUnregisterCallback(0);\
          if (ERR_OK == importResult ) importResult = GET_EventRegisterCallback(0);\
          if (ERR_OK == importResult ) importResult = GET_EventUnregisterCallbackFunction(0);\
          if (ERR_OK == importResult ) importResult = GET_EventRegisterCallbackFunction(0);\
          if (ERR_OK == importResult ) importResult = GET_EventClose(0);\
          if (ERR_OK == importResult ) importResult = GET_EventOpen(0);\
          if (ERR_OK == importResult ) importResult = GET_EventDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_EventCreate2(0);\
          if (ERR_OK == importResult ) importResult = GET_EventCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_IecTaskGetNext(0);\
          if (ERR_OK == importResult ) importResult = GET_IecTaskGetFirst(0);\
          if (ERR_OK == importResult ) importResult = GET_AppGetNextApp(0);\
          if (ERR_OK == importResult ) importResult = GET_AppGetFirstApp(0);\
          if (ERR_OK == importResult ) importResult = GET_AppGetAreaPointerByType(0);\
          if (ERR_OK == importResult ) importResult = GET_AppGetApplicationByIndex(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriteSingleTag(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderGetNextTag(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderGetFirstTag(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderPeekNext(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderGetString(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderSkipContent(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderGetContent(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderIsDataTag(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderGetTagLen(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderGetTagId(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderMoveNext(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagReaderInit(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterFinish(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterEndTag(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterAppendFillBytes(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterAppendBlob(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterAppendWString(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterStartTag(0);\
          if (ERR_OK == importResult ) importResult = GET_BTagWriterInit(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetIntValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgSetIntValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgSetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeArea(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocArea(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeData(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocData(0);\
          if (ERR_OK == importResult ) importResult = GET_ServerFinishRequest(0);\
          if (ERR_OK == importResult ) importResult = GET_ServerUnRegisterServiceHandler(0);\
          if (ERR_OK == importResult ) importResult = GET_ServerRegisterServiceHandler(0);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPJITTER_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
          
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPJITTER_DISABLE_EXTREF2
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
	ITF_CmpSrv     \
	ITF_CmpBinTagUtil     \
	ITF_SysTask     \
	ITF_SysMem     \
	ITF_CmpSettings     \
	ITF_CmpApp     \
	ITF_CmpAppBP     \
	ITF_CmpEventMgr     \
	ITF_SysTime     \
	ITF_SysEvent     \
	ITF_CmpSchedule     \
	ITF_SysCpuHandling     \
	ITF_CmpIecTask     \
	ITF_SysSocket     \
	ITF_SysMsgQ      \
    USE_ServerRegisterServiceHandler      \
    USE_ServerUnRegisterServiceHandler      \
    USE_ServerFinishRequest      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_SysMemAllocArea      \
    USE_SysMemFreeArea      \
    USE_SettgSetStringValue      \
    USE_SettgGetStringValue      \
    USE_SettgSetIntValue      \
    USE_SettgGetIntValue      \
    USE_BTagWriterInit      \
    USE_BTagWriterStartTag      \
    USE_BTagWriterAppendWString      \
    USE_BTagWriterAppendBlob      \
    USE_BTagWriterAppendFillBytes      \
    USE_BTagWriterEndTag      \
    USE_BTagWriterFinish      \
    USE_BTagReaderInit      \
    USE_BTagReaderMoveNext      \
    USE_BTagReaderGetTagId      \
    USE_BTagReaderGetTagLen      \
    USE_BTagReaderIsDataTag      \
    USE_BTagReaderGetContent      \
    USE_BTagReaderSkipContent      \
    USE_BTagReaderGetString      \
    USE_BTagReaderPeekNext      \
    USE_BTagReaderGetFirstTag      \
    USE_BTagReaderGetNextTag      \
    USE_BTagWriteSingleTag      \
    USE_AppGetApplicationByIndex      \
    USE_AppGetAreaPointerByType      \
    USE_AppGetFirstApp      \
    USE_AppGetNextApp      \
    USE_IecTaskGetFirst      \
    USE_IecTaskGetNext      \
    USE_EventCreate      \
    USE_EventCreate2      \
    USE_EventDelete      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_EventRegisterCallback      \
    USE_EventUnregisterCallback      \
    USE_EventPost      \
    USE_EventPostByEvent      \
    USE_SysCpuCallIecFuncWithParams      \
    USE_SysEventSet      \
    USE_IecTaskCycle      \
    USE_SysSockPing      \
    USE_SysTimeGetMs      \
    USE_SysTaskCreate      \
    USE_SysTaskEnter      \
    USE_SysMsgQRecv      \
    USE_SysTaskLeave      \
    USE_SysTaskEnd      \
    USE_SysTaskResume      \
    USE_SysTaskExit      \
    USE_SysMsgQCreate      \
    USE_SysMsgQSend      \
    USE_SysMemIsValidPointer     
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
	ITF_CmpSrv    \
	ITF_CmpBinTagUtil    \
	ITF_SysTask    \
	ITF_SysMem    \
	ITF_CmpSettings    \
	ITF_CmpApp    \
	ITF_CmpAppBP    \
	ITF_CmpEventMgr    \
	ITF_SysTime    \
	ITF_SysEvent    \
	ITF_CmpSchedule    \
	ITF_SysCpuHandling    \
	ITF_CmpIecTask    \
	ITF_SysSocket    \
	ITF_SysMsgQ     \
    USE_ServerRegisterServiceHandler      \
    USE_ServerUnRegisterServiceHandler      \
    USE_ServerFinishRequest      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_SysMemAllocArea      \
    USE_SysMemFreeArea      \
    USE_SettgSetStringValue      \
    USE_SettgGetStringValue      \
    USE_SettgSetIntValue      \
    USE_SettgGetIntValue      \
    USE_BTagWriterInit      \
    USE_BTagWriterStartTag      \
    USE_BTagWriterAppendWString      \
    USE_BTagWriterAppendBlob      \
    USE_BTagWriterAppendFillBytes      \
    USE_BTagWriterEndTag      \
    USE_BTagWriterFinish      \
    USE_BTagReaderInit      \
    USE_BTagReaderMoveNext      \
    USE_BTagReaderGetTagId      \
    USE_BTagReaderGetTagLen      \
    USE_BTagReaderIsDataTag      \
    USE_BTagReaderGetContent      \
    USE_BTagReaderSkipContent      \
    USE_BTagReaderGetString      \
    USE_BTagReaderPeekNext      \
    USE_BTagReaderGetFirstTag      \
    USE_BTagReaderGetNextTag      \
    USE_BTagWriteSingleTag      \
    USE_AppGetApplicationByIndex      \
    USE_AppGetAreaPointerByType      \
    USE_AppGetFirstApp      \
    USE_AppGetNextApp      \
    USE_IecTaskGetFirst      \
    USE_IecTaskGetNext      \
    USE_EventCreate      \
    USE_EventCreate2      \
    USE_EventDelete      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_EventRegisterCallback      \
    USE_EventUnregisterCallback      \
    USE_EventPost      \
    USE_EventPostByEvent      \
    USE_SysCpuCallIecFuncWithParams      \
    USE_SysEventSet      \
    USE_IecTaskCycle      \
    USE_SysSockPing      \
    USE_SysTimeGetMs      \
    USE_SysTaskCreate      \
    USE_SysTaskEnter      \
    USE_SysMsgQRecv      \
    USE_SysTaskLeave      \
    USE_SysTaskEnd      \
    USE_SysTaskResume      \
    USE_SysTaskExit      \
    USE_SysMsgQCreate      \
    USE_SysMsgQSend      \
    USE_SysMemIsValidPointer     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CmpSrv    \
	EXTITF_CmpBinTagUtil    \
	EXTITF_SysTask    \
	EXTITF_SysMem    \
	EXTITF_CmpSettings    \
	EXTITF_CmpApp    \
	EXTITF_CmpAppBP    \
	EXTITF_CmpEventMgr    \
	EXTITF_SysTime    \
	EXTITF_SysEvent    \
	EXTITF_CmpSchedule    \
	EXTITF_SysCpuHandling    \
	EXTITF_CmpIecTask    \
	EXTITF_SysSocket    \
	EXTITF_SysMsgQ     \
    EXT_ServerRegisterServiceHandler  \
    EXT_ServerUnRegisterServiceHandler  \
    EXT_ServerFinishRequest  \
    EXT_SysMemAllocData  \
    EXT_SysMemFreeData  \
    EXT_SysMemAllocArea  \
    EXT_SysMemFreeArea  \
    EXT_SettgSetStringValue  \
    EXT_SettgGetStringValue  \
    EXT_SettgSetIntValue  \
    EXT_SettgGetIntValue  \
    EXT_BTagWriterInit  \
    EXT_BTagWriterStartTag  \
    EXT_BTagWriterAppendWString  \
    EXT_BTagWriterAppendBlob  \
    EXT_BTagWriterAppendFillBytes  \
    EXT_BTagWriterEndTag  \
    EXT_BTagWriterFinish  \
    EXT_BTagReaderInit  \
    EXT_BTagReaderMoveNext  \
    EXT_BTagReaderGetTagId  \
    EXT_BTagReaderGetTagLen  \
    EXT_BTagReaderIsDataTag  \
    EXT_BTagReaderGetContent  \
    EXT_BTagReaderSkipContent  \
    EXT_BTagReaderGetString  \
    EXT_BTagReaderPeekNext  \
    EXT_BTagReaderGetFirstTag  \
    EXT_BTagReaderGetNextTag  \
    EXT_BTagWriteSingleTag  \
    EXT_AppGetApplicationByIndex  \
    EXT_AppGetAreaPointerByType  \
    EXT_AppGetFirstApp  \
    EXT_AppGetNextApp  \
    EXT_IecTaskGetFirst  \
    EXT_IecTaskGetNext  \
    EXT_EventCreate  \
    EXT_EventCreate2  \
    EXT_EventDelete  \
    EXT_EventOpen  \
    EXT_EventClose  \
    EXT_EventRegisterCallbackFunction  \
    EXT_EventUnregisterCallbackFunction  \
    EXT_EventRegisterCallback  \
    EXT_EventUnregisterCallback  \
    EXT_EventPost  \
    EXT_EventPostByEvent  \
    EXT_SysCpuCallIecFuncWithParams  \
    EXT_SysEventSet  \
    EXT_IecTaskCycle  \
    EXT_SysSockPing  \
    EXT_SysTimeGetMs  \
    EXT_SysTaskCreate  \
    EXT_SysTaskEnter  \
    EXT_SysMsgQRecv  \
    EXT_SysTaskLeave  \
    EXT_SysTaskEnd  \
    EXT_SysTaskResume  \
    EXT_SysTaskExit  \
    EXT_SysMsgQCreate  \
    EXT_SysMsgQSend  \
    EXT_SysMemIsValidPointer 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpJitter__Entry
#endif


#ifdef CPLUSPLUS

class CCmpJitter : public ICmpEventCallback 
{
    public:
        CCmpJitter() : hCmpJitter(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpJitter()
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
                pItf = dynamic_cast<IBase *>((ICmpEventCallback *)this);            
            else if (iid == ITFID_ICmpEventCallback)
                pItf = dynamic_cast<ICmpEventCallback *>(this); 
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
        virtual void CDECL IEventCallback(EventParam *pEventParam);

    public:
        RTS_HANDLE hCmpJitter;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpJitter Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpJitter_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpJitter_ExternalsTable[] = \
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
