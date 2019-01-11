/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Loopback Can Mini Driver</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
#ifndef _CMPLOOPBACKCANDRVDEP_H_
#define _CMPLOOPBACKCANDRVDEP_H_

#define COMPONENT_NAME "CmpLoopbackCanDrv" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpLoopbackCanDrv)
#define COMPONENT_NAME_UNQUOTED CmpLoopbackCanDrv





#define CMPID_CmpLoopbackCanDrv 0x2000


#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0
#define CMP_VENDORID       RTS_VENDORID_3S

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"

#include "CmpStd.h"
#include "CmpItf.h"





#include "CmpLoopbackCanDrvItf.h"







#include "CmpCAACanL2Itf.h"


#include "SysTaskItf.h"



/**
 * <category>Task</category>
 * <description>
 *	CAN communication task.
 * </description>
 */
#ifndef RTS_TASKNAME_PCANCOMMTHREAD
    #define RTS_TASKNAME_PCANCOMMTHREAD           "PCANCommThread"
#endif
#ifndef RTS_TASKPRIO_PCANCOMMTHREAD
    #define RTS_TASKPRIO_PCANCOMMTHREAD           TASKPRIO_HIGH_END
#endif



    












      












     

    






     









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
        if (pISysTask == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysTask, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysTask = (ISysTask *)pIBase->QueryInterface(pIBase, ITFID_ISysTask, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpCAACanL2 == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpCAACanL2, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpCAACanL2 = (ICmpCAACanL2 *)pIBase->QueryInterface(pIBase, ITFID_ICmpCAACanL2, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pISysTask = NULL; \
          pICmpCAACanL2 = NULL; \
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
          if (pICmpCAACanL2 != NULL) \
        { \
            pIBase = (IBase *)pICmpCAACanL2->QueryInterface(pICmpCAACanL2, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpCAACanL2 = NULL; \
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
        if (ERR_OK == importResult ) importResult = GET_CL2_MsgGetData(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgPutRQueue(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgSendAcknNoIRQ(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgFree(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgAlloc(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_CmdUnRegister(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_CmdRegister(0);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskGetName(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskWaitSleep(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskSetExit(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskEnter(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskLeave(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskGetInfo(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskDestroy(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskGetCurrent(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskJoin(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskEnd(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskExit(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskResume(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysTaskCreate(CM_IMPORT_OPTIONAL_FUNCTION);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPLOOPBACKCANDRV_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
              
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPLOOPBACKCANDRV_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
              
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
        { (RTS_VOID_FCTPTR)Loopback_CanMiniDriver_Handler, "Loopback_CanMiniDriver_Handler", 0, 0 },\
          { (RTS_VOID_FCTPTR)Loopback_CanMiniDriver_Dispose, "Loopback_CanMiniDriver_Dispose", 0, 0 },\
          { (RTS_VOID_FCTPTR)Loopback_CanMiniDriver_Setup, "Loopback_CanMiniDriver_Setup", 0, 0 },\
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
	ITF_CmpCAACanL2     \
	ITF_SysTask      \
    USE_SysTaskCreate      \
    USE_SysTaskResume      \
    USE_SysTaskExit      \
    USE_SysTaskEnd      \
    USE_SysTaskJoin      \
    USE_SysTaskGetCurrent      \
    USE_SysTaskDestroy      \
    USE_SysTaskGetInfo      \
    USE_SysTaskLeave      \
    USE_SysTaskEnter      \
    USE_SysTaskSetExit      \
    USE_SysTaskWaitSleep      \
    USE_SysTaskGetName      \
    USE_CL2_CmdRegister      \
    USE_CL2_CmdUnRegister      \
    USE_CL2_MsgAlloc      \
    USE_CL2_MsgFree      \
    USE_CL2_MsgSendAcknNoIRQ      \
    USE_CL2_MsgPutRQueue      \
    USE_CL2_MsgGetData     
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
	ITF_CmpCAACanL2    \
	ITF_SysTask     \
    USE_SysTaskCreate      \
    USE_SysTaskResume      \
    USE_SysTaskExit      \
    USE_SysTaskEnd      \
    USE_SysTaskJoin      \
    USE_SysTaskGetCurrent      \
    USE_SysTaskDestroy      \
    USE_SysTaskGetInfo      \
    USE_SysTaskLeave      \
    USE_SysTaskEnter      \
    USE_SysTaskSetExit      \
    USE_SysTaskWaitSleep      \
    USE_SysTaskGetName      \
    USE_CL2_CmdRegister      \
    USE_CL2_CmdUnRegister      \
    USE_CL2_MsgAlloc      \
    USE_CL2_MsgFree      \
    USE_CL2_MsgSendAcknNoIRQ      \
    USE_CL2_MsgPutRQueue      \
    USE_CL2_MsgGetData     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CmpCAACanL2    \
	EXTITF_SysTask     \
    EXT_SysTaskCreate  \
    EXT_SysTaskResume  \
    EXT_SysTaskExit  \
    EXT_SysTaskEnd  \
    EXT_SysTaskJoin  \
    EXT_SysTaskGetCurrent  \
    EXT_SysTaskDestroy  \
    EXT_SysTaskGetInfo  \
    EXT_SysTaskLeave  \
    EXT_SysTaskEnter  \
    EXT_SysTaskSetExit  \
    EXT_SysTaskWaitSleep  \
    EXT_SysTaskGetName  \
    EXT_CL2_CmdRegister  \
    EXT_CL2_CmdUnRegister  \
    EXT_CL2_MsgAlloc  \
    EXT_CL2_MsgFree  \
    EXT_CL2_MsgSendAcknNoIRQ  \
    EXT_CL2_MsgPutRQueue  \
    EXT_CL2_MsgGetData 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpLoopbackCanDrv__Entry
#endif


#ifdef CPLUSPLUS

class CCmpLoopbackCanDrv : public ICmpLoopbackCanDrv 
{
    public:
        CCmpLoopbackCanDrv() : hCmpLoopbackCanDrv(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpLoopbackCanDrv()
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
                pItf = dynamic_cast<IBase *>((ICmpLoopbackCanDrv *)this);            
            else if (iid == ITFID_ICmpLoopbackCanDrv)
                pItf = dynamic_cast<ICmpLoopbackCanDrv *>(this); 
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
        virtual int CDECL ILoopback_CanMiniDriver_Setup(void);
        virtual int CDECL ILoopback_CanMiniDriver_Dispose(void);
        virtual void CDECL ILoopback_CanMiniDriver_Handler(void);

    public:
        RTS_HANDLE hCmpLoopbackCanDrv;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpLoopbackCanDrv Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpLoopbackCanDrv_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpLoopbackCanDrv_ExternalsTable[] = \
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
