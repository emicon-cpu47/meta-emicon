/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component Socket Can Mini Driver</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  (c) 2008-2018 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPSOCKETCANDRVDEP_H_
#define _CMPSOCKETCANDRVDEP_H_

#define COMPONENT_NAME "CmpSocketCanDrv" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpSocketCanDrv)
#define COMPONENT_NAME_UNQUOTED CmpSocketCanDrv






#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0
#define CMP_VENDORID       RTS_VENDORID_3S

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"


#include "CmpItf.h"

#include "CAATypes.h"
#include "CAACanMiniDriver.h"
#include "SocketCanDrv.h"





#include "CmpSocketCanDrvItf.h"







/*Obsolete include: CmpLogItf.m4*/


#include "CmpCAACanL2Itf.h"


#include "CmpSettingsItf.h"


#include "SysTaskItf.h"


#include "SysTimeItf.h"


/*Obsolete include: CMUtilsItf.m4*/




/**
 * <category>Task</category>
 * <description>
 *	Socket CAN receive task.
 * </description>
 */
#ifndef RTS_TASKNAME_SOCKETRXTHREAD
    #define RTS_TASKNAME_SOCKETRXTHREAD           "SocketRXThread"
#endif
#ifndef RTS_TASKPRIO_SOCKETRXTHREAD
    #define RTS_TASKPRIO_SOCKETRXTHREAD           65
#endif



/**
 * <category>Task</category>
 * <description>
 *	Socket CAN transmit task.
 * </description>
 */
#ifndef RTS_TASKNAME_SOCKETTXTHREAD
    #define RTS_TASKNAME_SOCKETTXTHREAD           "SocketTXThread"
#endif
#ifndef RTS_TASKPRIO_SOCKETTXTHREAD
    #define RTS_TASKPRIO_SOCKETTXTHREAD           TASKPRIO_SYSTEM_END
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
        /*Obsolete include CMUtils*/ \
		  if (pISysTime == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysTime, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysTime = (ISysTime *)pIBase->QueryInterface(pIBase, ITFID_ISysTime, &initResult); \
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
          if (pICmpSettings == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSettings, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSettings = (ICmpSettings *)pIBase->QueryInterface(pIBase, ITFID_ICmpSettings, &initResult); \
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
          /*Obsolete include CmpLog*/ \
		   \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        /*Obsolete include CMUtils*/ \
		  pISysTime = NULL; \
          pISysTask = NULL; \
          pICmpSettings = NULL; \
          pICmpCAACanL2 = NULL; \
          /*Obsolete include CmpLog*/ \
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
        /*Obsolete include CMUtils*/ \
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
          /*Obsolete include CmpLog*/ \
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
        if (ERR_OK == importResult ) importResult = GET_CMUtlsnprintf(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTimeGetUs(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTimeGetMs(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskSetExit(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskEnter(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskLeave(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskEnd(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskExit(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskResume(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTaskCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgGetData(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgPutRQueue(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgSendAckn(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgFree(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_MsgAlloc(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_CmdUnRegister(0);\
          if (ERR_OK == importResult ) importResult = GET_CL2_CmdRegister(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetIntValue(0);\
          /*Obsolete required include LogAdd*/ \
		   \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#define EXPORT_EXTREF_STMT
#define EXPORT_EXTREF2_STMT
#define EXPORT_CMPITF_STMT {{ ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }}
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
	/*obsolete entry ITF_CmpLog*/      \
	ITF_CmpCAACanL2     \
	ITF_CmpSettings     \
	ITF_SysTask     \
	ITF_SysTime     \
	/*obsolete entry ITF_CMUtils*/       \
    /*obsolete USE_LogAdd*/      \
    USE_SettgGetIntValue      \
    USE_SettgGetStringValue      \
    USE_CL2_CmdRegister      \
    USE_CL2_CmdUnRegister      \
    USE_CL2_MsgAlloc      \
    USE_CL2_MsgFree      \
    USE_CL2_MsgSendAckn      \
    USE_CL2_MsgPutRQueue      \
    USE_CL2_MsgGetData      \
    USE_SysTaskCreate      \
    USE_SysTaskResume      \
    USE_SysTaskExit      \
    USE_SysTaskEnd      \
    USE_SysTaskLeave      \
    USE_SysTaskEnter      \
    USE_SysTaskSetExit      \
    USE_SysTimeGetMs      \
    USE_SysTimeGetUs      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlsnprintf     
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
	/*obsolete entry ITF_CmpLog*/     \
	ITF_CmpCAACanL2    \
	ITF_CmpSettings    \
	ITF_SysTask    \
	ITF_SysTime    \
	/*obsolete entry ITF_CMUtils*/      \
    /*obsolete USE_LogAdd*/      \
    USE_SettgGetIntValue      \
    USE_SettgGetStringValue      \
    USE_CL2_CmdRegister      \
    USE_CL2_CmdUnRegister      \
    USE_CL2_MsgAlloc      \
    USE_CL2_MsgFree      \
    USE_CL2_MsgSendAckn      \
    USE_CL2_MsgPutRQueue      \
    USE_CL2_MsgGetData      \
    USE_SysTaskCreate      \
    USE_SysTaskResume      \
    USE_SysTaskExit      \
    USE_SysTaskEnd      \
    USE_SysTaskLeave      \
    USE_SysTaskEnter      \
    USE_SysTaskSetExit      \
    USE_SysTimeGetMs      \
    USE_SysTimeGetUs      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlsnprintf     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	/*obsolete entry EXTITF_CmpLog*/     \
	EXTITF_CmpCAACanL2    \
	EXTITF_CmpSettings    \
	EXTITF_SysTask    \
	EXTITF_SysTime    \
	/*obsolete entry EXTITF_CMUtils*/      \
    /*obsolete EXT_LogAdd*/  \
    EXT_SettgGetIntValue  \
    EXT_SettgGetStringValue  \
    EXT_CL2_CmdRegister  \
    EXT_CL2_CmdUnRegister  \
    EXT_CL2_MsgAlloc  \
    EXT_CL2_MsgFree  \
    EXT_CL2_MsgSendAckn  \
    EXT_CL2_MsgPutRQueue  \
    EXT_CL2_MsgGetData  \
    EXT_SysTaskCreate  \
    EXT_SysTaskResume  \
    EXT_SysTaskExit  \
    EXT_SysTaskEnd  \
    EXT_SysTaskLeave  \
    EXT_SysTaskEnter  \
    EXT_SysTaskSetExit  \
    EXT_SysTimeGetMs  \
    EXT_SysTimeGetUs  \
    EXT_CMUtlSafeStrCpy  \
    EXT_CMUtlsnprintf 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpSocketCanDrv__Entry
#endif


#ifdef CPLUSPLUS

class CCmpSocketCanDrv : public ICmpSocketCanDrv 
{
    public:
        CCmpSocketCanDrv() : hCmpSocketCanDrv(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpSocketCanDrv()
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
                pItf = dynamic_cast<IBase *>((ICmpSocketCanDrv *)this);            
            else if (iid == ITFID_ICmpSocketCanDrv)
                pItf = dynamic_cast<ICmpSocketCanDrv *>(this); 
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

    public:
        RTS_HANDLE hCmpSocketCanDrv;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpSocketCanDrv Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpSocketCanDrv_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpSocketCanDrv_ExternalsTable[] = \
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
