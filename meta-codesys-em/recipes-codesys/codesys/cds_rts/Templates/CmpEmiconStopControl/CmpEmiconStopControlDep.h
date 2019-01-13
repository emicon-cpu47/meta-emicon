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
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPEMICONSTOPCONTROLDEP_H_
#define _CMPEMICONSTOPCONTROLDEP_H_

#define COMPONENT_NAME "CmpEmiconStopControl" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpEmiconStopControl)
#define COMPONENT_NAME_UNQUOTED CmpEmiconStopControl






#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID       0x163f

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"				

#define CMPID_CmpEmiconStopControl		0x2003								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconStopControl	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconStopControl		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */


/*Obsolete include: CMUtilsItf.m4*/


#include "SysFileItf.h"


#include "CmpEmiconLCDItf.h"


#include "SysEventItf.h"


#include "CmpEventMgrItf.h"


/*Obsolete include: CmpLogItf.m4*/


#include "CmpAppItf.h"







#include "CmpEmiconStopControlItf.h"







    















     

















    



      



     


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
        if (pICmpApp == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpApp, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpApp = (ICmpApp *)pIBase->QueryInterface(pIBase, ITFID_ICmpApp, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          /*Obsolete include CmpLog*/ \
		  if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
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
          if (pICmpEmiconLCD == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEmiconLCD, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEmiconLCD = (ICmpEmiconLCD *)pIBase->QueryInterface(pIBase, ITFID_ICmpEmiconLCD, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysFile == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysFile, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysFile = (ISysFile *)pIBase->QueryInterface(pIBase, ITFID_ISysFile, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		   \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pICmpApp = NULL; \
          /*Obsolete include CmpLog*/ \
		  pICmpEventMgr = NULL; \
          pISysEvent = NULL; \
          pICmpEmiconLCD = NULL; \
          pISysFile = NULL; \
          /*Obsolete include CMUtils*/ \
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
          /*Obsolete include CmpLog*/ \
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
          if (pICmpEmiconLCD != NULL) \
        { \
            pIBase = (IBase *)pICmpEmiconLCD->QueryInterface(pICmpEmiconLCD, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpEmiconLCD = NULL; \
            } \
        } \
          if (pISysFile != NULL) \
        { \
            pIBase = (IBase *)pISysFile->QueryInterface(pISysFile, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysFile = NULL; \
            } \
        } \
          /*Obsolete include CMUtils*/ \
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
        if (ERR_OK == importResult ) TempResult = GET_SysFileWrite(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileRead(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileClose(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileOpen(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_AppStopApplications(0);\
          if (ERR_OK == importResult ) importResult = GET_AppStartApplications(0);\
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
          if (ERR_OK == importResult ) importResult = GET_CmpEmiconLCD_display_screen(0);\
          if (ERR_OK == importResult ) importResult = GET_CmpEmiconLCD_puts(0);\
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
	/*obsolete entry ITF_CMUtils*/      \
	ITF_SysFile     \
	ITF_SysEvent     \
	ITF_CmpEventMgr     \
	/*obsolete entry ITF_CmpLog*/      \
	ITF_CmpApp      \
    USE_CmpEmiconLCD_puts      \
    USE_CmpEmiconLCD_display_screen      \
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
    USE_AppStartApplications      \
    USE_AppStopApplications      \
    USE_CMUtlSafeStrCpy      \
    USE_SysFileOpen      \
    USE_SysFileClose      \
    USE_SysFileRead      \
    USE_SysFileWrite     
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
	/*obsolete entry ITF_CMUtils*/     \
	ITF_SysFile    \
	ITF_SysEvent    \
	ITF_CmpEventMgr    \
	/*obsolete entry ITF_CmpLog*/     \
	ITF_CmpApp     \
    USE_CmpEmiconLCD_puts      \
    USE_CmpEmiconLCD_display_screen      \
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
    USE_AppStartApplications      \
    USE_AppStopApplications      \
    USE_CMUtlSafeStrCpy      \
    USE_SysFileOpen      \
    USE_SysFileClose      \
    USE_SysFileRead      \
    USE_SysFileWrite     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	/*obsolete entry EXTITF_CMUtils*/     \
	EXTITF_SysFile    \
	EXTITF_SysEvent    \
	EXTITF_CmpEventMgr    \
	/*obsolete entry EXTITF_CmpLog*/     \
	EXTITF_CmpApp     \
    EXT_CmpEmiconLCD_puts  \
    EXT_CmpEmiconLCD_display_screen  \
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
    EXT_AppStartApplications  \
    EXT_AppStopApplications  \
    EXT_CMUtlSafeStrCpy  \
    EXT_SysFileOpen  \
    EXT_SysFileClose  \
    EXT_SysFileRead  \
    EXT_SysFileWrite 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpEmiconStopControl__Entry
#endif


#ifdef CPLUSPLUS

class CCmpEmiconStopControl : public ICmpEmiconStopControl 
{
    public:
        CCmpEmiconStopControl() : hCmpEmiconStopControl(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpEmiconStopControl()
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
                pItf = dynamic_cast<IBase *>((ICmpEmiconStopControl *)this);            
            else if (iid == ITFID_ICmpEmiconStopControl)
                pItf = dynamic_cast<ICmpEmiconStopControl *>(this); 
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
        RTS_HANDLE hCmpEmiconStopControl;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpEmiconStopControl Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpEmiconStopControl_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpEmiconStopControl_ExternalsTable[] = \
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
