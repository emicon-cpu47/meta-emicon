/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component Test</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
#ifndef _CMPIECVARTESTDEP_H_
#define _CMPIECVARTESTDEP_H_

#define COMPONENT_NAME "CmpIecVarTest" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpIecVarTest)
#define COMPONENT_NAME_UNQUOTED CmpIecVarTest






#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
#define CMP_VENDORID       0x5678

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"				

#define CMPID_CmpIecVarTest		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpIecVarTest	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpIecVarTest		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */


#include "SysTimeItf.h"


#include "SysOutItf.h"


#include "SysMemItf.h"


#include "CmpIecVarAccessItf.h"







#include "CmpIecVarTestItf.h"








    



















     























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
        if (pICmpIecVarAccess == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpIecVarAccess, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpIecVarAccess = (ICmpIecVarAccess *)pIBase->QueryInterface(pIBase, ITFID_ICmpIecVarAccess, &initResult); \
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
          if (pISysOut == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysOut, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysOut = (ISysOut *)pIBase->QueryInterface(pIBase, ITFID_ISysOut, &initResult); \
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
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pICmpIecVarAccess = NULL; \
          pISysMem = NULL; \
          pISysOut = NULL; \
          pISysTime = NULL; \
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
        if (pICmpIecVarAccess != NULL) \
        { \
            pIBase = (IBase *)pICmpIecVarAccess->QueryInterface(pICmpIecVarAccess, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpIecVarAccess = NULL; \
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
          if (pISysOut != NULL) \
        { \
            pIBase = (IBase *)pISysOut->QueryInterface(pISysOut, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysOut = NULL; \
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
        if (ERR_OK == importResult ) importResult = GET_IecVarAccBrowseGetRoot(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetTypeClass3(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetTypeDesc(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetNodeName(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetNodeType(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetTypeNode3(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccSetValue3(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetValue3(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetSize3(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetNode3(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccBrowseGetNext(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccBrowseDown(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetNodeFullPath(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetApplicationName(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetNextInterface(0);\
          if (ERR_OK == importResult ) importResult = GET_IecVarAccGetFirstInterface(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeData(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocData(0);\
          if (ERR_OK == importResult ) importResult = GET_SysOutPrintf(0);\
          if (ERR_OK == importResult ) importResult = GET_SysTimeGetMs(0);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPIECVARTEST_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
        { (RTS_VOID_FCTPTR)myexternalfunction, "myexternalfunction", 0xE1C6D757, 0x3040000 },\
          
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPIECVARTEST_DISABLE_EXTREF2
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
	ITF_SysTime     \
	ITF_SysOut     \
	ITF_SysMem     \
	ITF_CmpIecVarAccess      \
    USE_SysTimeGetMs      \
    USE_SysOutPrintf      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_IecVarAccGetFirstInterface      \
    USE_IecVarAccGetNextInterface      \
    USE_IecVarAccGetApplicationName      \
    USE_IecVarAccGetNodeFullPath      \
    USE_IecVarAccBrowseDown      \
    USE_IecVarAccBrowseGetNext      \
    USE_IecVarAccGetNode3      \
    USE_IecVarAccGetSize3      \
    USE_IecVarAccGetValue3      \
    USE_IecVarAccSetValue3      \
    USE_IecVarAccGetTypeNode3      \
    USE_IecVarAccGetNodeType      \
    USE_IecVarAccGetNodeName      \
    USE_IecVarAccGetTypeDesc      \
    USE_IecVarAccGetTypeClass3      \
    USE_IecVarAccBrowseGetRoot     
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
	ITF_SysTime    \
	ITF_SysOut    \
	ITF_SysMem    \
	ITF_CmpIecVarAccess     \
    USE_SysTimeGetMs      \
    USE_SysOutPrintf      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_IecVarAccGetFirstInterface      \
    USE_IecVarAccGetNextInterface      \
    USE_IecVarAccGetApplicationName      \
    USE_IecVarAccGetNodeFullPath      \
    USE_IecVarAccBrowseDown      \
    USE_IecVarAccBrowseGetNext      \
    USE_IecVarAccGetNode3      \
    USE_IecVarAccGetSize3      \
    USE_IecVarAccGetValue3      \
    USE_IecVarAccSetValue3      \
    USE_IecVarAccGetTypeNode3      \
    USE_IecVarAccGetNodeType      \
    USE_IecVarAccGetNodeName      \
    USE_IecVarAccGetTypeDesc      \
    USE_IecVarAccGetTypeClass3      \
    USE_IecVarAccBrowseGetRoot     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_SysTime    \
	EXTITF_SysOut    \
	EXTITF_SysMem    \
	EXTITF_CmpIecVarAccess     \
    EXT_SysTimeGetMs  \
    EXT_SysOutPrintf  \
    EXT_SysMemAllocData  \
    EXT_SysMemFreeData  \
    EXT_IecVarAccGetFirstInterface  \
    EXT_IecVarAccGetNextInterface  \
    EXT_IecVarAccGetApplicationName  \
    EXT_IecVarAccGetNodeFullPath  \
    EXT_IecVarAccBrowseDown  \
    EXT_IecVarAccBrowseGetNext  \
    EXT_IecVarAccGetNode3  \
    EXT_IecVarAccGetSize3  \
    EXT_IecVarAccGetValue3  \
    EXT_IecVarAccSetValue3  \
    EXT_IecVarAccGetTypeNode3  \
    EXT_IecVarAccGetNodeType  \
    EXT_IecVarAccGetNodeName  \
    EXT_IecVarAccGetTypeDesc  \
    EXT_IecVarAccGetTypeClass3  \
    EXT_IecVarAccBrowseGetRoot 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpIecVarTest__Entry
#endif


#ifdef CPLUSPLUS

class CCmpIecVarTest : public ICmpIecVarTest 
{
    public:
        CCmpIecVarTest() : hCmpIecVarTest(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpIecVarTest()
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
                pItf = dynamic_cast<IBase *>((ICmpIecVarTest *)this);            
            else if (iid == ITFID_ICmpIecVarTest)
                pItf = dynamic_cast<ICmpIecVarTest *>(this); 
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
        RTS_HANDLE hCmpIecVarTest;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpIecVarTest Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpIecVarTest_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpIecVarTest_ExternalsTable[] = \
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
