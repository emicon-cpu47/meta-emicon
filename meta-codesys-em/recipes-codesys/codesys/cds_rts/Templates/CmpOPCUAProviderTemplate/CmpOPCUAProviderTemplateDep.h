/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component IecVarAccess OPC UA Provider</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
#ifndef _CMPOPCUAPROVIDERTEMPLATEDEP_H_
#define _CMPOPCUAPROVIDERTEMPLATEDEP_H_

#define COMPONENT_NAME "CmpOPCUAProviderTemplate" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpOPCUAProviderTemplate)
#define COMPONENT_NAME_UNQUOTED CmpOPCUAProviderTemplate







#define CMP_VERSION         UINT32_C(0x03050D00)
#define CMP_VERSION_STRING "3.5.13.0"
#define CMP_VERSION_RC      3,5,13,0
#define CMP_VENDORID       9999

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"


#include "CmpOPCUAStackItf.h"


#include "CmpOPCUAServerItf.h"


#include "SysMemItf.h"







#include "CmpOPCUAProviderItf.h"







    






















































     

























































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
        if (pISysMem == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysMem, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysMem = (ISysMem *)pIBase->QueryInterface(pIBase, ITFID_ISysMem, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpOPCUAServer == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpOPCUAServer, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpOPCUAServer = (ICmpOPCUAServer *)pIBase->QueryInterface(pIBase, ITFID_ICmpOPCUAServer, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpOPCUAStack == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpOPCUAStack, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpOPCUAStack = (ICmpOPCUAStack *)pIBase->QueryInterface(pIBase, ITFID_ICmpOPCUAStack, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
           \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pISysMem = NULL; \
          pICmpOPCUAServer = NULL; \
          pICmpOPCUAStack = NULL; \
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
          if (pICmpOPCUAServer != NULL) \
        { \
            pIBase = (IBase *)pICmpOPCUAServer->QueryInterface(pICmpOPCUAServer, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpOPCUAServer = NULL; \
            } \
        } \
          if (pICmpOPCUAStack != NULL) \
        { \
            pIBase = (IBase *)pICmpOPCUAStack->QueryInterface(pICmpOPCUAStack, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpOPCUAStack = NULL; \
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
        if (ERR_OK == importResult ) importResult = GET_OpcUaServerFireEvent(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerUnregisterEvent(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerRegisterEvent(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerUnregisterEventNotifier(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerRegisterEventNotifier(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerCheckReferenceRecursive(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerCheckIfReferenceIsValid(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerRegisterNamespace(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerGetNamespaceIndex(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerUnRegisterProvider(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerRegisterProvider(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaServerParseIndexRange(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaGetEncodableObjectType(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaVariantCopyTo(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaVariantCompare(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaVariantClear(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaVariantInitialize(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringStrnCmp(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringStrnCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringStrnCat(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringStrSize(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringStrLen(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringIsNull(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringIsEmpty(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringInitialize(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringGetRawString(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringClear(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringAttachToString(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringAttachReadOnly(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaStringAttachCopy(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaQualifiedNameCopyTo(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaQualifiedNameCompare(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaQualifiedNameClear(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaQualifiedNameInitialize(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaNodeIdIsNull(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaNodeIdCopyTo(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaNodeIdCompare(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaNodeIdClear(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaNodeIdInitialize(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaLocalizedTextCopyTo(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaLocalizedTextCompare(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaLocalizedTextClear(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaLocalizedTextInitialize(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaEncodeableObjectCreateExtension(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaEncodeableObjectDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaEncodeableObjectCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaDateTimeUtcNow(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaByteStringConcatenate(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaByteStringCopyTo(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaByteStringCompare(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaByteStringClear(0);\
          if (ERR_OK == importResult ) importResult = GET_OpcUaByteStringInitialize(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeData(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocData(0);\
          /*Obsolete required include LogAdd*/ \
		   \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPOPCUAPROVIDERTEMPLATE_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
                            
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPOPCUAPROVIDERTEMPLATE_DISABLE_EXTREF2
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
	ITF_CmpOPCUAStack     \
	ITF_CmpOPCUAServer     \
	ITF_SysMem      \
    /*obsolete USE_LogAdd*/      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_OpcUaByteStringInitialize      \
    USE_OpcUaByteStringClear      \
    USE_OpcUaByteStringCompare      \
    USE_OpcUaByteStringCopyTo      \
    USE_OpcUaByteStringConcatenate      \
    USE_OpcUaDateTimeUtcNow      \
    USE_OpcUaEncodeableObjectCreate      \
    USE_OpcUaEncodeableObjectDelete      \
    USE_OpcUaEncodeableObjectCreateExtension      \
    USE_OpcUaLocalizedTextInitialize      \
    USE_OpcUaLocalizedTextClear      \
    USE_OpcUaLocalizedTextCompare      \
    USE_OpcUaLocalizedTextCopyTo      \
    USE_OpcUaNodeIdInitialize      \
    USE_OpcUaNodeIdClear      \
    USE_OpcUaNodeIdCompare      \
    USE_OpcUaNodeIdCopyTo      \
    USE_OpcUaNodeIdIsNull      \
    USE_OpcUaQualifiedNameInitialize      \
    USE_OpcUaQualifiedNameClear      \
    USE_OpcUaQualifiedNameCompare      \
    USE_OpcUaQualifiedNameCopyTo      \
    USE_OpcUaStringAttachCopy      \
    USE_OpcUaStringAttachReadOnly      \
    USE_OpcUaStringAttachToString      \
    USE_OpcUaStringClear      \
    USE_OpcUaStringGetRawString      \
    USE_OpcUaStringInitialize      \
    USE_OpcUaStringIsEmpty      \
    USE_OpcUaStringIsNull      \
    USE_OpcUaStringStrLen      \
    USE_OpcUaStringStrSize      \
    USE_OpcUaStringStrnCat      \
    USE_OpcUaStringStrnCpy      \
    USE_OpcUaStringStrnCmp      \
    USE_OpcUaVariantInitialize      \
    USE_OpcUaVariantClear      \
    USE_OpcUaVariantCompare      \
    USE_OpcUaVariantCopyTo      \
    USE_OpcUaGetEncodableObjectType      \
    USE_OpcUaServerParseIndexRange      \
    USE_OpcUaServerRegisterProvider      \
    USE_OpcUaServerUnRegisterProvider      \
    USE_OpcUaServerGetNamespaceIndex      \
    USE_OpcUaServerRegisterNamespace      \
    USE_OpcUaServerCheckIfReferenceIsValid      \
    USE_OpcUaServerCheckReferenceRecursive      \
    USE_OpcUaServerRegisterEventNotifier      \
    USE_OpcUaServerUnregisterEventNotifier      \
    USE_OpcUaServerRegisterEvent      \
    USE_OpcUaServerUnregisterEvent      \
    USE_OpcUaServerFireEvent     
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
	ITF_CmpOPCUAStack    \
	ITF_CmpOPCUAServer    \
	ITF_SysMem     \
    /*obsolete USE_LogAdd*/      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_OpcUaByteStringInitialize      \
    USE_OpcUaByteStringClear      \
    USE_OpcUaByteStringCompare      \
    USE_OpcUaByteStringCopyTo      \
    USE_OpcUaByteStringConcatenate      \
    USE_OpcUaDateTimeUtcNow      \
    USE_OpcUaEncodeableObjectCreate      \
    USE_OpcUaEncodeableObjectDelete      \
    USE_OpcUaEncodeableObjectCreateExtension      \
    USE_OpcUaLocalizedTextInitialize      \
    USE_OpcUaLocalizedTextClear      \
    USE_OpcUaLocalizedTextCompare      \
    USE_OpcUaLocalizedTextCopyTo      \
    USE_OpcUaNodeIdInitialize      \
    USE_OpcUaNodeIdClear      \
    USE_OpcUaNodeIdCompare      \
    USE_OpcUaNodeIdCopyTo      \
    USE_OpcUaNodeIdIsNull      \
    USE_OpcUaQualifiedNameInitialize      \
    USE_OpcUaQualifiedNameClear      \
    USE_OpcUaQualifiedNameCompare      \
    USE_OpcUaQualifiedNameCopyTo      \
    USE_OpcUaStringAttachCopy      \
    USE_OpcUaStringAttachReadOnly      \
    USE_OpcUaStringAttachToString      \
    USE_OpcUaStringClear      \
    USE_OpcUaStringGetRawString      \
    USE_OpcUaStringInitialize      \
    USE_OpcUaStringIsEmpty      \
    USE_OpcUaStringIsNull      \
    USE_OpcUaStringStrLen      \
    USE_OpcUaStringStrSize      \
    USE_OpcUaStringStrnCat      \
    USE_OpcUaStringStrnCpy      \
    USE_OpcUaStringStrnCmp      \
    USE_OpcUaVariantInitialize      \
    USE_OpcUaVariantClear      \
    USE_OpcUaVariantCompare      \
    USE_OpcUaVariantCopyTo      \
    USE_OpcUaGetEncodableObjectType      \
    USE_OpcUaServerParseIndexRange      \
    USE_OpcUaServerRegisterProvider      \
    USE_OpcUaServerUnRegisterProvider      \
    USE_OpcUaServerGetNamespaceIndex      \
    USE_OpcUaServerRegisterNamespace      \
    USE_OpcUaServerCheckIfReferenceIsValid      \
    USE_OpcUaServerCheckReferenceRecursive      \
    USE_OpcUaServerRegisterEventNotifier      \
    USE_OpcUaServerUnregisterEventNotifier      \
    USE_OpcUaServerRegisterEvent      \
    USE_OpcUaServerUnregisterEvent      \
    USE_OpcUaServerFireEvent     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CmpOPCUAStack    \
	EXTITF_CmpOPCUAServer    \
	EXTITF_SysMem     \
    /*obsolete EXT_LogAdd*/  \
    EXT_SysMemAllocData  \
    EXT_SysMemFreeData  \
    EXT_OpcUaByteStringInitialize  \
    EXT_OpcUaByteStringClear  \
    EXT_OpcUaByteStringCompare  \
    EXT_OpcUaByteStringCopyTo  \
    EXT_OpcUaByteStringConcatenate  \
    EXT_OpcUaDateTimeUtcNow  \
    EXT_OpcUaEncodeableObjectCreate  \
    EXT_OpcUaEncodeableObjectDelete  \
    EXT_OpcUaEncodeableObjectCreateExtension  \
    EXT_OpcUaLocalizedTextInitialize  \
    EXT_OpcUaLocalizedTextClear  \
    EXT_OpcUaLocalizedTextCompare  \
    EXT_OpcUaLocalizedTextCopyTo  \
    EXT_OpcUaNodeIdInitialize  \
    EXT_OpcUaNodeIdClear  \
    EXT_OpcUaNodeIdCompare  \
    EXT_OpcUaNodeIdCopyTo  \
    EXT_OpcUaNodeIdIsNull  \
    EXT_OpcUaQualifiedNameInitialize  \
    EXT_OpcUaQualifiedNameClear  \
    EXT_OpcUaQualifiedNameCompare  \
    EXT_OpcUaQualifiedNameCopyTo  \
    EXT_OpcUaStringAttachCopy  \
    EXT_OpcUaStringAttachReadOnly  \
    EXT_OpcUaStringAttachToString  \
    EXT_OpcUaStringClear  \
    EXT_OpcUaStringGetRawString  \
    EXT_OpcUaStringInitialize  \
    EXT_OpcUaStringIsEmpty  \
    EXT_OpcUaStringIsNull  \
    EXT_OpcUaStringStrLen  \
    EXT_OpcUaStringStrSize  \
    EXT_OpcUaStringStrnCat  \
    EXT_OpcUaStringStrnCpy  \
    EXT_OpcUaStringStrnCmp  \
    EXT_OpcUaVariantInitialize  \
    EXT_OpcUaVariantClear  \
    EXT_OpcUaVariantCompare  \
    EXT_OpcUaVariantCopyTo  \
    EXT_OpcUaGetEncodableObjectType  \
    EXT_OpcUaServerParseIndexRange  \
    EXT_OpcUaServerRegisterProvider  \
    EXT_OpcUaServerUnRegisterProvider  \
    EXT_OpcUaServerGetNamespaceIndex  \
    EXT_OpcUaServerRegisterNamespace  \
    EXT_OpcUaServerCheckIfReferenceIsValid  \
    EXT_OpcUaServerCheckReferenceRecursive  \
    EXT_OpcUaServerRegisterEventNotifier  \
    EXT_OpcUaServerUnregisterEventNotifier  \
    EXT_OpcUaServerRegisterEvent  \
    EXT_OpcUaServerUnregisterEvent  \
    EXT_OpcUaServerFireEvent 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpOPCUAProviderTemplate__Entry
#endif


#ifdef CPLUSPLUS

class CCmpOPCUAProviderTemplate : public ICmpOPCUAProvider 
{
    public:
        CCmpOPCUAProviderTemplate() : hCmpOPCUAProviderTemplate(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpOPCUAProviderTemplate()
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
                pItf = dynamic_cast<IBase *>((ICmpOPCUAProvider *)this);            
            else if (iid == ITFID_ICmpOPCUAProvider)
                pItf = dynamic_cast<ICmpOPCUAProvider *>(this); 
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
        virtual RTS_HANDLE CDECL IOpcUaProviderCreate(RTS_HANDLE hIOpcUaProvider, CLASSID ClassId, int iId, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IOpcUaProviderDelete(void);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderInitialize(void);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderCleanup(void);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderBrowse(OpcUaProvider_BrowseContext *pContext);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderCreateMonitoredItem(OpcUaProvider_CreateMonitoredItemContext *pContext);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderDeleteMonitoredItem(OpcUaProvider_DeleteMonitoredItemContext *pContext);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderSampleMonitoredItem(OpcUaProvider_SampleMonitoredItemContext *pContext);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderRead(OpcUaProvider_ReadContext *pContext);
        virtual OpcUa_StatusCode CDECL IOpcUaProviderWrite(OpcUaProvider_WriteContext *pContext);

    public:
        RTS_HANDLE hCmpOPCUAProviderTemplate;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpOPCUAProviderTemplate Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpOPCUAProviderTemplate_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpOPCUAProviderTemplate_ExternalsTable[] = \
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
