/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 * <name>OpenSSL</name>
 * <description> 
 * A component implementing all interfaces for security issues (replaces the existing CmpOpenSSL component).
 * </description>
 * <copyright>
 * (c) 2003-2016 3S-Smart Software Solutions
 * </copyright>
 */
#ifndef _CMPOPENSSLOEMDEP_H_
#define _CMPOPENSSLOEMDEP_H_

#define COMPONENT_NAME "CmpOpenSSLOEM"COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpOpenSSLOEM)
#define COMPONENT_NAME_UNQUOTED CmpOpenSSLOEM





#define CMP_VERSION         UINT32_C(0x03050A00)
#define CMP_VERSION_STRING "3.5.10.0"
#define CMP_VERSION_RC      3,5,10,0

/* TODO: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID       0x0001

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"				

/* TODO: Start defining your ComponentIDs with 0x2000 */
#define CMPID_CmpOpenSSLOEM		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */

#define CLASSID_COpenSSLOEM		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IOpenSSLOEM		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */


#if defined(CPLUSPLUS) && !defined(CPP_IMPLEMENTATION_SysSockAccept2)
	#define CPP_IMPLEMENTATION_SysSockAccept2\
			CCmpOpenSSLOEM *pCOpenSSLOEM = (COpenSSLOEM *)(ISysSocket2 *)hSocket;\
			hSocket = pCOpenSSLOEM->hOpenSSLOEM;\
			hOpenSSLOEM = SysSockAccept2(hISysSocket,ClassId,hSocket,pSockAddr,piSockAddrSize,pResult);\
			return (RTS_HANDLE)QueryInterface((IBase *)(ISysSocket2 *)this, ITFID_ISysSocket2, NULL);
#endif

#include "CMItf.h"


#include "CmpSettingsItf.h"


#include "CmpEventMgrItf.h"


#include "SysSocketItf.h"


#include "SysSocket2Itf.h"


#include "CmpMemPoolItf.h"


/*Obsolete include: CMUtilsItf.m4*/


#include "SysFileItf.h"


#include "SysMemItf.h"







#include "CmpTlsItf.h"
#include "SysSocket2Itf.h"
#include "CmpCryptoItf.h"
#include "CmpX509CertItf.h"













    















































     

















































    







      







     


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
		  if (pICmpMemPool == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpMemPool, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpMemPool = (ICmpMemPool *)pIBase->QueryInterface(pIBase, ITFID_ICmpMemPool, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysSocket2 == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysSocket2, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysSocket2 = (ISysSocket2 *)pIBase->QueryInterface(pIBase, ITFID_ISysSocket2, &initResult); \
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
          if (pICmpEventMgr == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEventMgr, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEventMgr = (ICmpEventMgr *)pIBase->QueryInterface(pIBase, ITFID_ICmpEventMgr, &initResult); \
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
        pISysMem = NULL; \
          pISysFile = NULL; \
          /*Obsolete include CMUtils*/ \
		  pICmpMemPool = NULL; \
          pISysSocket2 = NULL; \
          pISysSocket = NULL; \
          pICmpEventMgr = NULL; \
          pICmpSettings = NULL; \
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
		  if (pICmpMemPool != NULL) \
        { \
            pIBase = (IBase *)pICmpMemPool->QueryInterface(pICmpMemPool, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpMemPool = NULL; \
            } \
        } \
          if (pISysSocket2 != NULL) \
        { \
            pIBase = (IBase *)pISysSocket2->QueryInterface(pISysSocket2, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysSocket2 = NULL; \
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
        if (ERR_OK == importResult ) TempResult = GET_SysFileRead(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileGetSize(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileClose(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileOpen(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventUnregisterCallbackFunction(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventRegisterCallbackFunction(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventClose(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_EventOpen(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) importResult = GET_SysMemFreeData(0);\
          if (ERR_OK == importResult ) importResult = GET_SysMemAllocData(0);\
          if (ERR_OK == importResult ) importResult = GET_CMGetCmpName(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlsnprintf(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlStrICmp(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlStrNICmp(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCat(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlStrLen(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolIsValidBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolUnlockBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolLockBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolUnlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolLock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolRemoveUsedBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolCleanup(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolAppendUsedBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolAddUsedBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolPutBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolGetBlock2(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolGetBlock(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolDelete(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolCreateDynamic(0);\
          if (ERR_OK == importResult ) importResult = GET_MemPoolCreateStatic(0);\
          if (ERR_OK == importResult ) importResult = GET_CMExit(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockGetPeerName(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockGetSockName(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockInetNtoa(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockHtons(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockInetAddr(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockFdZero(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockFdInit(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockFdIsset(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockSend(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockRecv(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockIoctl(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockShutdown(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockSelect(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockConnect(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockAccept(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockListen(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockBind(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockGetOption(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockSetOption(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockClose(0);\
          if (ERR_OK == importResult ) importResult = GET_SysSockCreate(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetIntValue(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPOPENSSLOEM_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
        { (RTS_VOID_FCTPTR)cmptlswrite, "cmptlswrite", RTSITF_GET_SIGNATURE(0xA1D9E8A7, 0xF01B2E0C), 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsshutdown, "cmptlsshutdown", 0x2AA5307D, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsread, "cmptlsread", RTSITF_GET_SIGNATURE(0x7869515D, 0xC50DA073), 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsfreecontext, "cmptlsfreecontext", 0x4FCCCE44, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlscreatecontext, "cmptlscreatecontext", 0x9BD4354C, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsconnect, "cmptlsconnect", 0xE8789C31, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsclose, "cmptlsclose", 0xBD50D496, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsbufferopen, "cmptlsbufferopen", 0x205777BB, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsbufferdatatosendavailable, "cmptlsbufferdatatosendavailable", 0xFC0521B2, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsbufferdatasent, "cmptlsbufferdatasent", 0xA15919C8, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsbufferdatareceived, "cmptlsbufferdatareceived", 0x613BC278, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cmptlsaccept, "cmptlsaccept", 0xE5016190, 0x03050A00 },\
                                                                                                                          { (RTS_VOID_FCTPTR)cryptosymmetricencrypt, "cryptosymmetricencrypt", 0x8D659084, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptosymmetricdecrypt, "cryptosymmetricdecrypt", 0xF3963545, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptosignatureverify, "cryptosignatureverify", 0x3F425BB9, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptosignaturegenerate, "cryptosignaturegenerate", 0x0C2FBF80, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptortsbytestringinit, "cryptortsbytestringinit", 0xC1B4C2F9, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptortsbytestringexit, "cryptortsbytestringexit", 0x16B297C5, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptokeyinit, "cryptokeyinit", 0xE8E228B3, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptokeyexit, "cryptokeyexit", 0xD71ED5F3, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptohmacverify, "cryptohmacverify", 0x49EEB4A9, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptohmacsign, "cryptohmacsign", 0x931A9470, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptogetnextalgorithm, "cryptogetnextalgorithm", 0x79EC29C8, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptogetfirstalgorithm, "cryptogetfirstalgorithm", 0xC8A4A345, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptogetasymmetrickeylength, "cryptogetasymmetrickeylength", 0x0F3B29BE, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptogetalgorithmbyid, "cryptogetalgorithmbyid", 0x3D0776D3, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptogeneraterandomnumber, "cryptogeneraterandomnumber", 0xF9FC5437, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptogeneratehash, "cryptogeneratehash", 0x34E1A812, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptoasymmetricencrypt, "cryptoasymmetricencrypt", 0xC14613D0, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)cryptoasymmetricdecrypt, "cryptoasymmetricdecrypt", 0x126B86CC, 0x03050A00 },\
                                                                                          { (RTS_VOID_FCTPTR)x509parsecertificate, "x509parsecertificate", 0x01B27207, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certverify, "x509certverify", 0x9822EB29, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoreunregister, "x509certstoreunregister", 0xE41C13F3, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoresearchgetnext, "x509certstoresearchgetnext", 0xB7F16B08, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoresearchgetfirst, "x509certstoresearchgetfirst", 0x6C956088, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoreremovecert, "x509certstoreremovecert", 0x0E795BC4, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoreregister, "x509certstoreregister", 0x35F7F607, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoreopen, "x509certstoreopen", 0xFE7CCE6C, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoregetnextcert, "x509certstoregetnextcert", 0x894377FA, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoregetfirstcert, "x509certstoregetfirstcert", 0x9165907D, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoreclose, "x509certstoreclose", 0x048C3968, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certstoreaddcert, "x509certstoreaddcert", 0x690E5D79, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certkeyclose, "x509certkeyclose", 0x6A598D05, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certinfoinit, "x509certinfoinit", 0xD52F28DD, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certinfoexit, "x509certinfoexit", 0x4F4B0310, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certgetthumbprint, "x509certgetthumbprint", 0x5B1EA1C5, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certgetpublickey, "x509certgetpublickey", 0x35142E48, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certgetprivatekey, "x509certgetprivatekey", 0x279C9A63, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certgetcontent, "x509certgetcontent", 0xDA69570E, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certgetbinary, "x509certgetbinary", 0x6F7D6C42, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certcreateselfsigned, "x509certcreateselfsigned", 0x6765E8BD, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certcreatecsr, "x509certcreatecsr", 0xF64C1D04, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certcmsverify, "x509certcmsverify", 0x73653424, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certcmsdecrypt, "x509certcmsdecrypt", 0xCCAD85D1, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)x509certclose, "x509certclose", 0x150A5E6B, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)rtsoidgetname, "rtsoidgetname", 0xBEA6E204, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)rtsoidgetid, "rtsoidgetid", 0xB69D55FF, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)rtsoidcreate, "rtsoidcreate", 0xE11A70BD, 0x03050A00 },\
          { (RTS_VOID_FCTPTR)rtsoidclear, "rtsoidclear", 0xB53A1CAF, 0x03050A00 },\
          
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPOPENSSLOEM_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
                                                                                                                                                                                                                                                                                                                              
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
                                { (RTS_VOID_FCTPTR)TlsRandCheckStatus, "TlsRandCheckStatus", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsRandAdd, "TlsRandAdd", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsClose, "TlsClose", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsShutdown, "TlsShutdown", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsWrite, "TlsWrite", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsRead, "TlsRead", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsConnect, "TlsConnect", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsAccept, "TlsAccept", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsBufferNumOfWrittenBlocks, "TlsBufferNumOfWrittenBlocks", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsBufferDataToSendAvailable, "TlsBufferDataToSendAvailable", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsBufferDataSent, "TlsBufferDataSent", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsBufferDataReveived, "TlsBufferDataReveived", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsBufferOpen, "TlsBufferOpen", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsFreeContext, "TlsFreeContext", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsCreateContext2, "TlsCreateContext2", 0, 0 },\
          { (RTS_VOID_FCTPTR)TlsCreateContext, "TlsCreateContext", 0, 0 },\
                                                  { (RTS_VOID_FCTPTR)CryptoRtsByteStringExit, "CryptoRtsByteStringExit", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoRtsByteStringInit2, "CryptoRtsByteStringInit2", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoRtsByteStringInit, "CryptoRtsByteStringInit", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoKeyExit, "CryptoKeyExit", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoKeyInit, "CryptoKeyInit", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGenerateRandomNumber, "CryptoGenerateRandomNumber", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoSignatureVerify, "CryptoSignatureVerify", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoSignatureGenerate, "CryptoSignatureGenerate", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoHMACVerify, "CryptoHMACVerify", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoHMACSign, "CryptoHMACSign", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGenerateHash, "CryptoGenerateHash", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGetAsymmetricKeyLength, "CryptoGetAsymmetricKeyLength", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoAsymmetricDecrypt, "CryptoAsymmetricDecrypt", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoAsymmetricEncrypt, "CryptoAsymmetricEncrypt", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoSymmetricDecrypt, "CryptoSymmetricDecrypt", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoSymmetricEncrypt, "CryptoSymmetricEncrypt", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGetAlgorithmInfo, "CryptoGetAlgorithmInfo", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGetNextAlgorithm, "CryptoGetNextAlgorithm", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGetFirstAlgorithm, "CryptoGetFirstAlgorithm", 0, 0 },\
          { (RTS_VOID_FCTPTR)CryptoGetAlgorithmById, "CryptoGetAlgorithmById", 0, 0 },\
                                              { (RTS_VOID_FCTPTR)X509CertStoreUnregister, "X509CertStoreUnregister", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreRegister, "X509CertStoreRegister", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreGetNextCert, "X509CertStoreGetNextCert", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreGetFirstCert, "X509CertStoreGetFirstCert", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreRemoveCert, "X509CertStoreRemoveCert", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreAddCert, "X509CertStoreAddCert", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCreateCSRAsync, "X509CertCreateCSRAsync", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCreateCSR, "X509CertCreateCSR", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCreateSelfSignedAsync, "X509CertCreateSelfSignedAsync", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCreateSelfSigned, "X509CertCreateSelfSigned", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStorGetBackendInfo, "X509CertStorGetBackendInfo", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreGetNextBackend, "X509CertStoreGetNextBackend", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreGetFirstBackend, "X509CertStoreGetFirstBackend", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertInfoExit, "X509CertInfoExit", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertInfoInit, "X509CertInfoInit", 0, 0 },\
          { (RTS_VOID_FCTPTR)RtsOIDClear, "RtsOIDClear", 0, 0 },\
          { (RTS_VOID_FCTPTR)RtsOIDGetName, "RtsOIDGetName", 0, 0 },\
          { (RTS_VOID_FCTPTR)RtsOIDGetID, "RtsOIDGetID", 0, 0 },\
          { (RTS_VOID_FCTPTR)RtsOIDCreate, "RtsOIDCreate", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509SplitCertificateChain, "X509SplitCertificateChain", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCmsDecrypt, "X509CertCmsDecrypt", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCmsVerify2, "X509CertCmsVerify2", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCmsVerify, "X509CertCmsVerify", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertClose, "X509CertClose", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertKeyClose, "X509CertKeyClose", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertCompare, "X509CertCompare", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertHasExtendedKeyUsage, "X509CertHasExtendedKeyUsage", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertIsSelfSigned, "X509CertIsSelfSigned", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertIsDateValid, "X509CertIsDateValid", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertGetThumbprint, "X509CertGetThumbprint", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertGetPrivateKey, "X509CertGetPrivateKey", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertGetPublicKey, "X509CertGetPublicKey", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertGetBinary, "X509CertGetBinary", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertGetContent, "X509CertGetContent", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509ParseCertificate, "X509ParseCertificate", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreSearchGetNext, "X509CertStoreSearchGetNext", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreSearchGetFirst, "X509CertStoreSearchGetFirst", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertVerify, "X509CertVerify", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreClose, "X509CertStoreClose", 0, 0 },\
          { (RTS_VOID_FCTPTR)X509CertStoreOpen, "X509CertStoreOpen", 0, 0 },\
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
	ITF_CM     \
	ITF_CmpSettings     \
	ITF_CmpEventMgr     \
	ITF_SysSocket     \
	ITF_SysSocket2     \
	ITF_CmpMemPool     \
	/*obsolete entry ITF_CMUtils*/      \
	ITF_SysFile     \
	ITF_SysMem      \
    USE_SettgGetStringValue      \
    USE_SettgGetIntValue      \
    USE_SysSockCreate      \
    USE_SysSockClose      \
    USE_SysSockSetOption      \
    USE_SysSockGetOption      \
    USE_SysSockBind      \
    USE_SysSockListen      \
    USE_SysSockAccept      \
    USE_SysSockConnect      \
    USE_SysSockSelect      \
    USE_SysSockShutdown      \
    USE_SysSockIoctl      \
    USE_SysSockRecv      \
    USE_SysSockSend      \
    USE_SysSockFdIsset      \
    USE_SysSockFdInit      \
    USE_SysSockFdZero      \
    USE_SysSockInetAddr      \
    USE_SysSockHtons      \
    USE_SysSockInetNtoa      \
    USE_SysSockGetSockName      \
    USE_SysSockGetPeerName      \
    USE_CMExit      \
    USE_MemPoolCreateStatic      \
    USE_MemPoolCreateDynamic      \
    USE_MemPoolDelete      \
    USE_MemPoolGetBlock      \
    USE_MemPoolGetBlock2      \
    USE_MemPoolPutBlock      \
    USE_MemPoolAddUsedBlock      \
    USE_MemPoolAppendUsedBlock      \
    USE_MemPoolCleanup      \
    USE_MemPoolRemoveUsedBlock      \
    USE_MemPoolLock      \
    USE_MemPoolUnlock      \
    USE_MemPoolLockBlock      \
    USE_MemPoolUnlockBlock      \
    USE_MemPoolIsValidBlock      \
    USE_CMUtlStrLen      \
    USE_CMUtlSafeStrCat      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlStrNICmp      \
    USE_CMUtlStrICmp      \
    USE_CMUtlsnprintf      \
    USE_CMGetCmpName      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_SysFileOpen      \
    USE_SysFileClose      \
    USE_SysFileGetSize      \
    USE_SysFileRead     
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
	ITF_CmpSettings    \
	ITF_CmpEventMgr    \
	ITF_SysSocket    \
	ITF_SysSocket2    \
	ITF_CmpMemPool    \
	/*obsolete entry ITF_CMUtils*/     \
	ITF_SysFile    \
	ITF_SysMem     \
    USE_SettgGetStringValue      \
    USE_SettgGetIntValue      \
    USE_SysSockCreate      \
    USE_SysSockClose      \
    USE_SysSockSetOption      \
    USE_SysSockGetOption      \
    USE_SysSockBind      \
    USE_SysSockListen      \
    USE_SysSockAccept      \
    USE_SysSockConnect      \
    USE_SysSockSelect      \
    USE_SysSockShutdown      \
    USE_SysSockIoctl      \
    USE_SysSockRecv      \
    USE_SysSockSend      \
    USE_SysSockFdIsset      \
    USE_SysSockFdInit      \
    USE_SysSockFdZero      \
    USE_SysSockInetAddr      \
    USE_SysSockHtons      \
    USE_SysSockInetNtoa      \
    USE_SysSockGetSockName      \
    USE_SysSockGetPeerName      \
    USE_CMExit      \
    USE_MemPoolCreateStatic      \
    USE_MemPoolCreateDynamic      \
    USE_MemPoolDelete      \
    USE_MemPoolGetBlock      \
    USE_MemPoolGetBlock2      \
    USE_MemPoolPutBlock      \
    USE_MemPoolAddUsedBlock      \
    USE_MemPoolAppendUsedBlock      \
    USE_MemPoolCleanup      \
    USE_MemPoolRemoveUsedBlock      \
    USE_MemPoolLock      \
    USE_MemPoolUnlock      \
    USE_MemPoolLockBlock      \
    USE_MemPoolUnlockBlock      \
    USE_MemPoolIsValidBlock      \
    USE_CMUtlStrLen      \
    USE_CMUtlSafeStrCat      \
    USE_CMUtlSafeStrCpy      \
    USE_CMUtlStrNICmp      \
    USE_CMUtlStrICmp      \
    USE_CMUtlsnprintf      \
    USE_CMGetCmpName      \
    USE_SysMemAllocData      \
    USE_SysMemFreeData      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_SysFileOpen      \
    USE_SysFileClose      \
    USE_SysFileGetSize      \
    USE_SysFileRead     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	EXTITF_CM    \
	EXTITF_CmpSettings    \
	EXTITF_CmpEventMgr    \
	EXTITF_SysSocket    \
	EXTITF_SysSocket2    \
	EXTITF_CmpMemPool    \
	/*obsolete entry EXTITF_CMUtils*/     \
	EXTITF_SysFile    \
	EXTITF_SysMem     \
    EXT_SettgGetStringValue  \
    EXT_SettgGetIntValue  \
    EXT_SysSockCreate  \
    EXT_SysSockClose  \
    EXT_SysSockSetOption  \
    EXT_SysSockGetOption  \
    EXT_SysSockBind  \
    EXT_SysSockListen  \
    EXT_SysSockAccept  \
    EXT_SysSockConnect  \
    EXT_SysSockSelect  \
    EXT_SysSockShutdown  \
    EXT_SysSockIoctl  \
    EXT_SysSockRecv  \
    EXT_SysSockSend  \
    EXT_SysSockFdIsset  \
    EXT_SysSockFdInit  \
    EXT_SysSockFdZero  \
    EXT_SysSockInetAddr  \
    EXT_SysSockHtons  \
    EXT_SysSockInetNtoa  \
    EXT_SysSockGetSockName  \
    EXT_SysSockGetPeerName  \
    EXT_CMExit  \
    EXT_MemPoolCreateStatic  \
    EXT_MemPoolCreateDynamic  \
    EXT_MemPoolDelete  \
    EXT_MemPoolGetBlock  \
    EXT_MemPoolGetBlock2  \
    EXT_MemPoolPutBlock  \
    EXT_MemPoolAddUsedBlock  \
    EXT_MemPoolAppendUsedBlock  \
    EXT_MemPoolCleanup  \
    EXT_MemPoolRemoveUsedBlock  \
    EXT_MemPoolLock  \
    EXT_MemPoolUnlock  \
    EXT_MemPoolLockBlock  \
    EXT_MemPoolUnlockBlock  \
    EXT_MemPoolIsValidBlock  \
    EXT_CMUtlStrLen  \
    EXT_CMUtlSafeStrCat  \
    EXT_CMUtlSafeStrCpy  \
    EXT_CMUtlStrNICmp  \
    EXT_CMUtlStrICmp  \
    EXT_CMUtlsnprintf  \
    EXT_CMGetCmpName  \
    EXT_SysMemAllocData  \
    EXT_SysMemFreeData  \
    EXT_EventOpen  \
    EXT_EventClose  \
    EXT_EventRegisterCallbackFunction  \
    EXT_EventUnregisterCallbackFunction  \
    EXT_SysFileOpen  \
    EXT_SysFileClose  \
    EXT_SysFileGetSize  \
    EXT_SysFileRead 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpOpenSSLOEM__Entry
#endif


#ifdef CPLUSPLUS

class CCmpOpenSSLOEM : public ICmpTls , public ISysSocket2 , public ICmpCrypto , public ICmpX509Cert 
{
    public:
        CCmpOpenSSLOEM() : hCmpOpenSSLOEM(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpOpenSSLOEM()
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
                pItf = dynamic_cast<IBase *>((ICmpTls *)this);            
            else if (iid == ITFID_ICmpTls)
                pItf = dynamic_cast<ICmpTls *>(this); 
            else if (iid == ITFID_ISysSocket2)
                pItf = dynamic_cast<ISysSocket2 *>(this); 
            else if (iid == ITFID_ICmpCrypto)
                pItf = dynamic_cast<ICmpCrypto *>(this); 
            else if (iid == ITFID_ICmpX509Cert)
                pItf = dynamic_cast<ICmpX509Cert *>(this); 
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
        virtual RTS_HANDLE CDECL IX509CertStoreOpen(CMPID componentID, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL IX509CertStoreClose(RTS_HANDLE hCertStore);
        virtual RTS_RESULT CDECL IX509CertVerify(RTS_HANDLE hCertStore, RTS_HANDLE hCert);
        virtual RTS_HANDLE CDECL IX509CertStoreSearchGetFirst(RTS_HANDLE hCertStore, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult);
        virtual RTS_HANDLE CDECL IX509CertStoreSearchGetNext(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult);
        virtual RTS_HANDLE CDECL IX509ParseCertificate(RtsByteString* pCert, RTSCERTENCODING encoding, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL IX509CertGetContent(RTS_HANDLE hCert, RtsX509CertInfo* pCertContent);
        virtual RTS_RESULT CDECL IX509CertGetBinary(RTS_HANDLE hCert, RTSCERTENCODING encoding, RtsByteString* pCert);
        virtual RTS_RESULT CDECL IX509CertGetPublicKey(RTS_HANDLE hCert, RtsCryptoKey* pPublicKey);
        virtual RTS_RESULT CDECL IX509CertGetPrivateKey(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsCryptoKey* pPrivateKey);
        virtual RTS_RESULT CDECL IX509CertGetThumbprint(RTS_HANDLE hCert, RTSCRYPTOID* hashAlgorithm, RtsByteString* pThumbprint);
        virtual RTS_BOOL CDECL IX509CertIsDateValid(RTS_HANDLE hCert, RTS_RESULT *pResult);
        virtual RTS_BOOL CDECL IX509CertIsSelfSigned(RTS_HANDLE hCert, RTS_RESULT *pResult);
        virtual RTS_BOOL CDECL IX509CertHasExtendedKeyUsage(RTS_HANDLE hCert, RTS_UI32 numOfExKeyUsages, RtsOID *pExKeyUsages, RTS_RESULT *pResult);
        virtual RTS_BOOL CDECL IX509CertCompare(RTS_HANDLE hCert1, RTS_HANDLE hCert2);
        virtual RTS_RESULT CDECL IX509CertKeyClose(RtsCryptoKey* pKey);
        virtual RTS_RESULT CDECL IX509CertClose(RTS_HANDLE hCert);
        virtual RTS_RESULT CDECL IX509CertCmsVerify(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData);
        virtual RTS_RESULT CDECL IX509CertCmsVerify2(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData, RTS_HANDLE* phSignerCert);
        virtual RTS_RESULT CDECL IX509CertCmsDecrypt(RTS_HANDLE hCertStore, RTS_HANDLE hRecipientCert, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pOutData);
        virtual RTS_RESULT CDECL IX509SplitCertificateChain(RtsByteString* pCertificateChain, RtsByteString* pCertificates, RTS_UI32* pui32NumOfCertificates);
        virtual RTS_RESULT CDECL IRtsOIDCreate(char* id, RtsOID* oid);
        virtual RTS_RESULT CDECL IRtsOIDGetID(RtsOID* oid, RtsByteString* pBuffer);
        virtual RTS_RESULT CDECL IRtsOIDGetName(RtsOID* oid, RtsByteString* pBuffer);
        virtual RTS_RESULT CDECL IRtsOIDClear(RtsOID* oid);
        virtual RTS_RESULT CDECL IX509CertInfoInit(RtsX509CertInfo* pCertInfo, RTS_UI32 structSize);
        virtual RTS_RESULT CDECL IX509CertInfoExit(RtsX509CertInfo* pCertInfo);
        virtual RTS_HANDLE CDECL IX509CertStoreGetFirstBackend(RTS_HANDLE hCertStore, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult);
        virtual RTS_HANDLE CDECL IX509CertStoreGetNextBackend(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL IX509CertStorGetBackendInfo(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo);
        virtual RTS_HANDLE CDECL IX509CertCreateSelfSigned(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL IX509CertCreateSelfSignedAsync(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTS_UI32 nIndex, PFX509ASYNCCALLBACK pfCallback);
        virtual RTS_RESULT CDECL IX509CertCreateCSR(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR);
        virtual RTS_RESULT CDECL IX509CertCreateCSRAsync(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, CMPID cmpID, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR, RTS_UI32 nIndex, PFX509ASYNCCALLBACK pfCallback);
        virtual RTS_RESULT CDECL IX509CertStoreAddCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTSCERTTRUSTLEVEL trustLevel);
        virtual RTS_RESULT CDECL IX509CertStoreRemoveCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_BOOL bRemovePrivateKey);
        virtual RTS_HANDLE CDECL IX509CertStoreGetFirstCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTSCERTTRUSTLEVEL trustLevel, RTS_RESULT* pResult);
        virtual RTS_HANDLE CDECL IX509CertStoreGetNextCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_RESULT* pResult);
        virtual RTS_HANDLE CDECL IX509CertStoreRegister(RTS_HANDLE hCertStore, CMPID cmpID, RtsX509CertInfo* pCertInfo, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL IX509CertStoreUnregister(RTS_HANDLE hCertStore, RTS_HANDLE hRegisteredComponent);
        virtual RTS_HANDLE CDECL ICryptoGetAlgorithmById(RTS_UI32 ui32CryptoID, RTS_RESULT* pResult);
        virtual RTS_HANDLE CDECL ICryptoGetFirstAlgorithm(RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult);
        virtual RTS_HANDLE CDECL ICryptoGetNextAlgorithm(RTS_HANDLE hCrypto, RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult);
        virtual RtsCryptoInfo* CDECL ICryptoGetAlgorithmInfo(RTS_HANDLE hCrypto, RTS_RESULT* pCryptoInfo);
        virtual RTS_RESULT CDECL ICryptoSymmetricEncrypt(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pCipherText);
        virtual RTS_RESULT CDECL ICryptoSymmetricDecrypt(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pPlainText);
        virtual RTS_RESULT CDECL ICryptoAsymmetricEncrypt(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey publicKey, RtsByteString* pCipherText);
        virtual RTS_RESULT CDECL ICryptoAsymmetricDecrypt(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey privateKey, RtsByteString* pPlainText);
        virtual RTS_UI32 CDECL ICryptoGetAsymmetricKeyLength(RtsCryptoKey privateKey, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL ICryptoGenerateHash(RTS_HANDLE hAlgo, RtsByteString* pData, RtsByteString* pHash);
        virtual RTS_RESULT CDECL ICryptoHMACSign(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature);
        virtual RTS_RESULT CDECL ICryptoHMACVerify(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature);
        virtual RTS_RESULT CDECL ICryptoSignatureGenerate(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey privateKey, RtsByteString* pSignature);
        virtual RTS_RESULT CDECL ICryptoSignatureVerify(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey publicKey, RtsByteString* pSignature);
        virtual RTS_RESULT CDECL ICryptoGenerateRandomNumber(RTS_UI32 ui32NumOfRandomBytes, RtsByteString* pRandom);
        virtual RTS_RESULT CDECL ICryptoKeyInit(RtsCryptoKey* pKey, RtsCryptoKeyStorage key, RTSCRYPTOKEYTYPE keyType);
        virtual RTS_RESULT CDECL ICryptoKeyExit(RtsCryptoKey* pKey);
        virtual RTS_RESULT CDECL ICryptoRtsByteStringInit(RtsByteString* pByteString);
        virtual RTS_RESULT CDECL ICryptoRtsByteStringInit2(RtsByteString* pByteString, RTS_UI32 ui32BufferSize, RTS_UI8* pBuffer);
        virtual RTS_RESULT CDECL ICryptoRtsByteStringExit(RtsByteString* pByteString);
        virtual RTS_HANDLE CDECL ISysSock2Create(RTS_HANDLE hISysSocket, CLASSID ClassId, SysSock_Parameter *pParameter, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL ISysSock2Close(void);
        virtual RTS_RESULT CDECL ISysSock2SetOption(RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 iOptionLen);
        virtual RTS_RESULT CDECL ISysSock2GetOption(RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 *piOptionLen);
        virtual RTS_RESULT CDECL ISysSock2Bind(SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize);
        virtual RTS_RESULT CDECL ISysSock2Listen(RTS_I32 iMaxConnections);
        virtual RTS_HANDLE CDECL ISysSock2Accept(RTS_HANDLE hISysSocket, CLASSID ClassId, RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL ISysSock2Connect(SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize);
        virtual RTS_RESULT CDECL ISysSock2Select(RTS_I32 iWidth, SOCKET_FD_SET *fdRead, SOCKET_FD_SET *fdWrite, SOCKET_FD_SET *fdExcept, SOCKET_TIMEVAL *ptvTimeout, RTS_I32 *pnReady);
        virtual RTS_RESULT CDECL ISysSock2Shutdown(RTS_I32 iHow);
        virtual RTS_RESULT CDECL ISysSock2Ioctl(RTS_I32 iCommand, RTS_I32 *piParameter);
        virtual RTS_BOOL CDECL ISysSock2FdIsset(SOCKET_FD_SET *pfs);
        virtual RTS_RESULT CDECL ISysSock2FdInit(SOCKET_FD_SET *pfs);
        virtual RTS_SSIZE CDECL ISysSock2Recv(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult);
        virtual RTS_SSIZE CDECL ISysSock2Send(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult);
        virtual RTS_SSIZE CDECL ISysSock2RecvFrom(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult);
        virtual RTS_SSIZE CDECL ISysSock2SendTo(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult);
        virtual RTS_RESULT CDECL ISysSock2GetPeerName(SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize);
        virtual RTS_RESULT CDECL ISysSock2GetSockName(SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize);
        virtual CLASSID CDECL ISysSock2GetClassId(RTS_RESULT *pResult);
        virtual RTS_HANDLE CDECL ITlsCreateContext(char* pszNamespace, RTS_RESULT* pResult);
        virtual RTS_HANDLE CDECL ITlsCreateContext2(RTS_HANDLE hCert, RTS_UI32 ui32TlsMethod, char* szCipherList, RTS_I32 i32VerifyMode, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL ITlsFreeContext(RTS_HANDLE hTlsContext);
        virtual RTS_HANDLE CDECL ITlsBufferOpen(RTS_HANDLE hContext, RtsByteString* pRxBuffer, RtsByteString* pTxBuffer, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL ITlsBufferDataReveived(RTS_HANDLE hTlsConn);
        virtual RTS_RESULT CDECL ITlsBufferDataSent(RTS_HANDLE hTlsConn);
        virtual RTS_BOOL CDECL ITlsBufferDataToSendAvailable(RTS_HANDLE hTlsConn);
        virtual RTS_UI32 CDECL ITlsBufferNumOfWrittenBlocks(RTS_HANDLE hTlsConn);
        virtual RTS_RESULT CDECL ITlsAccept(RTS_HANDLE hTlsConn);
        virtual RTS_RESULT CDECL ITlsConnect(RTS_HANDLE hTlsConn);
        virtual RTS_SSIZE CDECL ITlsRead(RTS_HANDLE hTlsConn, RTS_UI8* pbyBuffer, RTS_SSIZE ulBufferSize, RTS_RESULT* pResult);
        virtual RTS_SSIZE CDECL ITlsWrite(RTS_HANDLE hTlsConn, RTS_UI8* pbyData, RTS_SSIZE ulDataSize, RTS_RESULT* pResult);
        virtual RTS_RESULT CDECL ITlsShutdown(RTS_HANDLE hTlsConn);
        virtual RTS_RESULT CDECL ITlsClose(RTS_HANDLE hTlsConn);
        virtual void CDECL ITlsRandAdd(const RTS_UI8* pui8Buffer, RTS_I32 i32BufferSize, RTS_REAL64 r64Entroy);
        virtual RTS_BOOL CDECL ITlsRandCheckStatus(void);

    public:
        RTS_HANDLE hCmpOpenSSLOEM;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpOpenSSLOEM Declarations for uRTS */
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
#define USE_HOOK_FUNCTION	RTS_RESULT CmpOpenSSLOEM_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpOpenSSLOEM_ExternalsTable[] = \
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
