/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component IOMgr Sub</name>
 *  <description> 
 *  An empty implementation of the interface CmpIoMgrItf. This implementation can be
 *  used for example as a template for specially developed IOManagers or when an empty
 *  implemented IOMgr is necessary.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPIOMGRSTUBDEP_H_
#define _CMPIOMGRSTUBDEP_H_

#define COMPONENT_NAME "CmpIoMgrStub"COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpIoMgrStub)
#define COMPONENT_NAME_UNQUOTED CmpIoMgrStub






#define CMP_VERSION         UINT32_C(0x03050A00)
#define CMP_VERSION_STRING "3.5.10.0"
#define CMP_VERSION_RC      3,5,10,0
#define CMP_VENDORID       RTS_VENDORID_3S

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"

#define CMPID_CmpIoMgrStub		0x2000								/* To prevent conflicts with "real" components, we use this component id in the oem range */
#define CLASSID_CCmpIoMgrStub	ADDVENDORID(CMP_VENDORID, 0x2000)	/* To prevent conflicts with "real" components, we use this component id in the oem range */
#define ITFID_ICmpIoMgrStub		ADDVENDORID(CMP_VENDORID, 0x2000)	/* To prevent conflicts with "real" components, we use this component id in the oem range */






#include "CmpIoMgrItf.h"









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
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
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
    }
#else
    #define INIT_STMT
    #define INIT_LOCALS_STMT
    #define EXIT_STMT
#endif


#define IMPORT_STMT      INIT_STMT


#ifndef CMPIOMGRSTUB_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
                                                                                                    { (RTS_VOID_FCTPTR)iomgrregisterinstance, "iomgrregisterinstance", 0, 0 },\
              { (RTS_VOID_FCTPTR)iomgrconfiggetiodriver, "iomgrconfiggetiodriver", 0, 0x3010200 },\
          { (RTS_VOID_FCTPTR)iomgrwriteparameter, "iomgrwriteparameter", RTSITF_GET_SIGNATURE(0, 0xAD04F7E8), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrwriteoutputs, "iomgrwriteoutputs", RTSITF_GET_SIGNATURE(0, 0xDA3433B3), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrwatchdogtrigger, "iomgrwatchdogtrigger", RTSITF_GET_SIGNATURE(0, 0x986DFD93), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrupdatemapping2, "iomgrupdatemapping2", RTSITF_GET_SIGNATURE(0, 0x775F7CAD), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrupdatemapping, "iomgrupdatemapping", RTSITF_GET_SIGNATURE(0, 0x0A15126C), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrupdateconfiguration2, "iomgrupdateconfiguration2", RTSITF_GET_SIGNATURE(0, 0x44CD4528), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrupdateconfiguration, "iomgrupdateconfiguration", RTSITF_GET_SIGNATURE(0, 0xB1381773), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrunregisterinstance, "iomgrunregisterinstance", RTSITF_GET_SIGNATURE(0, 0x830B7CC7), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrunregisterconfigapplication, "iomgrunregisterconfigapplication", RTSITF_GET_SIGNATURE(0, 0xECB18F2E), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrstartbuscycle2, "iomgrstartbuscycle2", RTSITF_GET_SIGNATURE(0, 0x8AB99A18), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrstartbuscycle, "iomgrstartbuscycle", RTSITF_GET_SIGNATURE(0, 0x09EEEC27), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrsetdriverproperty, "iomgrsetdriverproperty", RTSITF_GET_SIGNATURE(0, 0x936FC5C4), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrsetdriverproperties, "iomgrsetdriverproperties", RTSITF_GET_SIGNATURE(0, 0x607A5D95), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrscanmodules, "iomgrscanmodules", RTSITF_GET_SIGNATURE(0, 0xF31DBCAE), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrregisterinstance2, "iomgrregisterinstance2", RTSITF_GET_SIGNATURE(0, 0x4219F9A3), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrregisterconfigapplication, "iomgrregisterconfigapplication", RTSITF_GET_SIGNATURE(0, 0xBEF7EAA8), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrreconfigure, "iomgrreconfigure", RTSITF_GET_SIGNATURE(0x7DDF91C4, 0x731E5390), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrreadparameter, "iomgrreadparameter", RTSITF_GET_SIGNATURE(0, 0xD37BF5DF), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrreadinputs, "iomgrreadinputs", RTSITF_GET_SIGNATURE(0, 0x3BCE0A42), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgridentify, "iomgridentify", RTSITF_GET_SIGNATURE(0, 0xC48724F5), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrgetnextdriverinstance, "iomgrgetnextdriverinstance", RTSITF_GET_SIGNATURE(0, 0x0B47742F), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrgetmodulediagnosis, "iomgrgetmodulediagnosis", RTSITF_GET_SIGNATURE(0, 0x5DA78ABA), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrgetfirstdriverinstance, "iomgrgetfirstdriverinstance", RTSITF_GET_SIGNATURE(0, 0x7823BC76), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrgetdriverproperties, "iomgrgetdriverproperties", RTSITF_GET_SIGNATURE(0, 0xEC0D662D), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrgetconfigapplication, "iomgrgetconfigapplication", RTSITF_GET_SIGNATURE(0, 0xF82C99F4), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrgetbuscycletype, "iomgrgetbuscycletype", RTSITF_GET_SIGNATURE(0, 0x8334DD20), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrcopyoutputle, "iomgrcopyoutputle", RTSITF_GET_SIGNATURE(0, 0x5FC818BC), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrcopyoutputbe, "iomgrcopyoutputbe", RTSITF_GET_SIGNATURE(0, 0xCDB7B2BE), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrcopyinputle, "iomgrcopyinputle", RTSITF_GET_SIGNATURE(0, 0xD4FB4CB6), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrcopyinputbe, "iomgrcopyinputbe", RTSITF_GET_SIGNATURE(0, 0x072C6C71), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfigsetdiagnosis, "iomgrconfigsetdiagnosis", RTSITF_GET_SIGNATURE(0, 0xE0CCC2C9), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfigresetdiagnosis, "iomgrconfigresetdiagnosis", RTSITF_GET_SIGNATURE(0, 0x6B60C0F6), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetparametervalueword, "iomgrconfiggetparametervalueword", RTSITF_GET_SIGNATURE(0, 0x522D5073), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetparametervaluepointer, "iomgrconfiggetparametervaluepointer", RTSITF_GET_SIGNATURE(0, 0x633BC6E3), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetparametervaluedword, "iomgrconfiggetparametervaluedword", RTSITF_GET_SIGNATURE(0, 0x6F885F72), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetparametervaluebyte, "iomgrconfiggetparametervaluebyte", RTSITF_GET_SIGNATURE(0, 0xDE4EF488), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetparameter, "iomgrconfiggetparameter", RTSITF_GET_SIGNATURE(0, 0xC7A23B05), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetnextconnector, "iomgrconfiggetnextconnector", RTSITF_GET_SIGNATURE(0, 0xA5BCF071), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetnextchild, "iomgrconfiggetnextchild", RTSITF_GET_SIGNATURE(0, 0x2F87EBF8), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetfirstconnector, "iomgrconfiggetfirstconnector", RTSITF_GET_SIGNATURE(0, 0x1AEDD2CA), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetfirstchild, "iomgrconfiggetfirstchild", RTSITF_GET_SIGNATURE(0, 0xB89B6273), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetdriver, "iomgrconfiggetdriver", RTSITF_GET_SIGNATURE(0, 0xA6C591A7), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetconnectorlist, "iomgrconfiggetconnectorlist", RTSITF_GET_SIGNATURE(0, 0x6E3F45DC), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetconnectorbydriver, "iomgrconfiggetconnectorbydriver", RTSITF_GET_SIGNATURE(0, 0x076B9D1E), 0x03050800 },\
          { (RTS_VOID_FCTPTR)iomgrconfiggetconnector, "iomgrconfiggetconnector", RTSITF_GET_SIGNATURE(0, 0xB093BAED), 0x03050800 },\
          
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPIOMGRSTUB_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
                                                                                                                                                                                                      
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
        { (RTS_VOID_FCTPTR)IoMgrCopyOutputBE, "IoMgrCopyOutputBE", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrCopyOutputLE, "IoMgrCopyOutputLE", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrCopyInputBE, "IoMgrCopyInputBE", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrCopyInputLE, "IoMgrCopyInputLE", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetConnectorByDriver, "IoMgrConfigGetConnectorByDriver", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetDriver, "IoMgrConfigGetDriver", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrWriteParameter, "IoMgrWriteParameter", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrReadParameter, "IoMgrReadParameter", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigResetDiagnosis, "IoMgrConfigResetDiagnosis", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigSetDiagnosis, "IoMgrConfigSetDiagnosis", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetConnector, "IoMgrConfigGetConnector", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetConnectorList, "IoMgrConfigGetConnectorList", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetNextChild, "IoMgrConfigGetNextChild", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetFirstChild, "IoMgrConfigGetFirstChild", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetNextConnector, "IoMgrConfigGetNextConnector", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetFirstConnector, "IoMgrConfigGetFirstConnector", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetParameterValuePointer, "IoMgrConfigGetParameterValuePointer", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetParameterValueByte, "IoMgrConfigGetParameterValueByte", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetParameterValueWord, "IoMgrConfigGetParameterValueWord", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetParameterValueDword, "IoMgrConfigGetParameterValueDword", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrConfigGetParameter, "IoMgrConfigGetParameter", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrWatchdogTrigger, "IoMgrWatchdogTrigger", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrNominate, "IoMgrNominate", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrIdentify, "IoMgrIdentify", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrGetModuleDiagnosis, "IoMgrGetModuleDiagnosis", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrScanModules, "IoMgrScanModules", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrGetBusCycleType, "IoMgrGetBusCycleType", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrStartBusCycle2, "IoMgrStartBusCycle2", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrStartBusCycle, "IoMgrStartBusCycle", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrWriteOutputs, "IoMgrWriteOutputs", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrReadInputs, "IoMgrReadInputs", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrReconfigure, "IoMgrReconfigure", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrUpdateMapping2, "IoMgrUpdateMapping2", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrUpdateMapping, "IoMgrUpdateMapping", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrUpdateConfiguration2, "IoMgrUpdateConfiguration2", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrUpdateConfiguration, "IoMgrUpdateConfiguration", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrGetConfigApplication, "IoMgrGetConfigApplication", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrUnregisterConfigApplication, "IoMgrUnregisterConfigApplication", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrRegisterConfigApplication, "IoMgrRegisterConfigApplication", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrSetDriverProperty, "IoMgrSetDriverProperty", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrGetDriverProperties, "IoMgrGetDriverProperties", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrSetDriverProperties, "IoMgrSetDriverProperties", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrGetNextDriverInstance, "IoMgrGetNextDriverInstance", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrGetFirstDriverInstance, "IoMgrGetFirstDriverInstance", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrUnregisterInstance, "IoMgrUnregisterInstance", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrRegisterInstance2, "IoMgrRegisterInstance2", 0, 0 },\
            { (RTS_VOID_FCTPTR)IoMgrRegisterInstance, "IoMgrRegisterInstance", 0, 0 },\
          { (RTS_VOID_FCTPTR)IoMgrExceptionHandler, "IoMgrExceptionHandler", 0, 0 },\
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
    USE_LogAdd 
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
    USE_LogAdd 
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpIoMgrStub__Entry
#endif


#ifdef CPLUSPLUS

class CCmpIoMgrStub : public ICmpIoMgr 
{
    public:
        CCmpIoMgrStub() : hCmpIoMgrStub(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpIoMgrStub()
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
                pItf = dynamic_cast<IBase *>((ICmpIoMgr *)this);            
            else if (iid == ITFID_ICmpIoMgr)
                pItf = dynamic_cast<ICmpIoMgr *>(this); 
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
        virtual RTS_RESULT CDECL IIoMgrExceptionHandler(char *pszApplication, RTS_UI32 ulException);
        virtual RTS_HANDLE CDECL IIoMgrRegisterInstance(IBase *pIBase, RTS_RESULT *pResult);
        virtual RTS_HANDLE CDECL IIoMgrRegisterInstance2(IBase *pIBase, int bIecDriver, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IIoMgrUnregisterInstance(IBase *pIBase);
        virtual IBase* CDECL IIoMgrGetFirstDriverInstance(int *pbIecDriver, RTS_RESULT *pResult);
        virtual IBase* CDECL IIoMgrGetNextDriverInstance(IBase *pIBasePrev, int *pbIecDriver, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IIoMgrSetDriverProperties(IBase *pIBase, RTS_UI32 ulProperties);
        virtual RTS_RESULT CDECL IIoMgrGetDriverProperties(IBase *pIBase, RTS_UI32 **ppulProperty);
        virtual RTS_RESULT CDECL IIoMgrSetDriverProperty(IBase *pIBase, RTS_UI32 ulProperty, int bValue);
        virtual RTS_RESULT CDECL IIoMgrRegisterConfigApplication(char *pszConfigApplication);
        virtual RTS_RESULT CDECL IIoMgrUnregisterConfigApplication(char *pszConfigApplication);
        virtual RTS_RESULT CDECL IIoMgrGetConfigApplication(char *pszConfigApplication, int *pnMaxLen);
        virtual RTS_RESULT CDECL IIoMgrUpdateConfiguration(IoConfigConnector *pConnectorList, int nCount);
        virtual RTS_RESULT CDECL IIoMgrUpdateConfiguration2(IoConfigConnector *pConnectorList, int nCount, char *pszConfigApplication);
        virtual RTS_RESULT CDECL IIoMgrUpdateMapping(IoConfigTaskMap *pTaskMapList, int nCount);
        virtual RTS_RESULT CDECL IIoMgrUpdateMapping2(IoConfigTaskMap *pTaskMapList, int nCount, char *pszConfigApplication);
        virtual RTS_RESULT CDECL IIoMgrReconfigure(IoConfigConnector *pConnector, RTS_UI32 *pui32State);
        virtual RTS_RESULT CDECL IIoMgrReadInputs(IoConfigTaskMap *pTaskMap);
        virtual RTS_RESULT CDECL IIoMgrWriteOutputs(IoConfigTaskMap *pTaskMap);
        virtual RTS_RESULT CDECL IIoMgrStartBusCycle(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoMgrStartBusCycle2(IoConfigConnector *pConnector, RTS_UI32 dwType);
        virtual RTS_RESULT CDECL IIoMgrGetBusCycleType(IoConfigConnector *pConnector, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IIoMgrScanModules(IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount);
        virtual RTS_RESULT CDECL IIoMgrGetModuleDiagnosis(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoMgrIdentify(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoMgrNominate(IoConfigConnector *pConnector);
        virtual RTS_RESULT CDECL IIoMgrWatchdogTrigger(IoConfigConnector *pConnector);
        virtual IoConfigParameter* CDECL IIoMgrConfigGetParameter(IoConfigConnector *pConnector, RTS_UI32 dwParameterId);
        virtual RTS_UI32 CDECL IIoMgrConfigGetParameterValueDword(IoConfigParameter *pParameter, RTS_RESULT *pResult);
        virtual unsigned short CDECL IIoMgrConfigGetParameterValueWord(IoConfigParameter *pParameter, RTS_RESULT *pResult);
        virtual unsigned char CDECL IIoMgrConfigGetParameterValueByte(IoConfigParameter *pParameter, RTS_RESULT *pResult);
        virtual void * CDECL IIoMgrConfigGetParameterValuePointer(IoConfigParameter *pParameter, RTS_RESULT *pResult);
        virtual IoConfigConnector* CDECL IIoMgrConfigGetFirstConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType);
        virtual IoConfigConnector* CDECL IIoMgrConfigGetNextConnector(IoConfigConnector *pConnectorList, int *pnCount, unsigned short wType);
        virtual IoConfigConnector* CDECL IIoMgrConfigGetFirstChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather);
        virtual IoConfigConnector* CDECL IIoMgrConfigGetNextChild(IoConfigConnector *pConnectorList, int *pnCount, IoConfigConnector *pFather);
        virtual RTS_RESULT CDECL IIoMgrConfigGetConnectorList(IoConfigConnector **ppConnectorList, int *pnCount);
        virtual IoConfigConnector* CDECL IIoMgrConfigGetConnector(IoConfigConnector *pConnectorList, int *pnCount, RTS_UI32 ulModuleType, RTS_UI32 ulInstance);
        virtual RTS_RESULT CDECL IIoMgrConfigSetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags);
        virtual RTS_RESULT CDECL IIoMgrConfigResetDiagnosis(IoConfigConnector *pConnector, RTS_UI32 ulFlags);
        virtual RTS_RESULT CDECL IIoMgrReadParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
        virtual RTS_RESULT CDECL IIoMgrWriteParameter(RTS_UI32 ulModuleType, RTS_UI32 ulInstance, RTS_UI32 ulParameterId, void *pData, RTS_SIZE ulBitSize, RTS_SIZE ulBitOffset);
        virtual IBase * CDECL IIoMgrConfigGetDriver(IoConfigConnector *pConnector, RTS_RESULT *pResult);
        virtual IoConfigConnector * CDECL IIoMgrConfigGetConnectorByDriver(IBase *pIBase, int nIndex, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IIoMgrCopyInputLE(IoConfigChannelMap *pChannel, char *pAddress);
        virtual RTS_RESULT CDECL IIoMgrCopyInputBE(IoConfigChannelMap *pChannel, char *pAddress);
        virtual RTS_RESULT CDECL IIoMgrCopyOutputLE(IoConfigChannelMap *pChannel, char *pAddress);
        virtual RTS_RESULT CDECL IIoMgrCopyOutputBE(IoConfigChannelMap *pChannel, char *pAddress);

    public:
        RTS_HANDLE hCmpIoMgrStub;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpIoMgrStub Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpIoMgrStub_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpIoMgrStub_ExternalsTable[] = \
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
