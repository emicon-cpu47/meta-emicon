/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component Template</name>
 *  <description> 
 *  Simple example about using runtime system events in IEC applications.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPTEMPLATEEVENTIECDEP_H_
#define _CMPTEMPLATEEVENTIECDEP_H_

#define COMPONENT_NAME "CmpTemplateEventIEC"COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpTemplateEventIEC)
#define COMPONENT_NAME_UNQUOTED CmpTemplateEventIEC






#define CMP_VERSION         UINT32_C(0x03050A00)
#define CMP_VERSION_STRING "3.5.10.0"
#define CMP_VERSION_RC      3,5,10,0

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID       0x0001

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"				

#define CMPID_CmpTemplateEventIEC		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpTemplateEventIEC	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpTemplateEventIEC		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */






#include "CmpTemplateEventIECItf.h"







#include "CMItf.h"


#include "CmpEventMgrItf.h"



    





     









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
        if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
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
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pICmpEventMgr = NULL; \
          pICM = NULL; \
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
        if (ERR_OK == importResult ) importResult = GET_EventPost(0);\
          if (ERR_OK == importResult ) importResult = GET_EventClose(0);\
          if (ERR_OK == importResult ) importResult = GET_EventOpen(0);\
          if (ERR_OK == importResult ) importResult = GET_EventDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_EventCreate2(0);\
          if (ERR_OK == importResult ) importResult = GET_EventCreate(0);\
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
	ITF_CM     \
	ITF_CmpEventMgr      \
    USE_EventCreate      \
    USE_EventCreate2      \
    USE_EventDelete      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventPost     
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
	ITF_CM    \
	ITF_CmpEventMgr     \
    USE_EventCreate      \
    USE_EventCreate2      \
    USE_EventDelete      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventPost     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CM    \
	EXTITF_CmpEventMgr     \
    EXT_EventCreate  \
    EXT_EventCreate2  \
    EXT_EventDelete  \
    EXT_EventOpen  \
    EXT_EventClose  \
    EXT_EventPost 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpTemplateEventIEC__Entry
#endif


#ifdef CPLUSPLUS

class CCmpTemplateEventIEC : public ICmpTemplateEventIEC 
{
    public:
        CCmpTemplateEventIEC() : hCmpTemplateEventIEC(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpTemplateEventIEC()
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
                pItf = dynamic_cast<IBase *>((ICmpTemplateEventIEC *)this);            
            else if (iid == ITFID_ICmpTemplateEventIEC)
                pItf = dynamic_cast<ICmpTemplateEventIEC *>(this); 
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
        RTS_HANDLE hCmpTemplateEventIEC;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpTemplateEventIEC Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpTemplateEventIEC_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpTemplateEventIEC_ExternalsTable[] = \
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
