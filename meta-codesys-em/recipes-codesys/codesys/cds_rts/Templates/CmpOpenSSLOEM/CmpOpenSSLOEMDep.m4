/**
 * <name>OpenSSL</name>
 * <description> 
 * A component implementing all interfaces for security issues (replaces the existing CmpOpenSSL component).
 * </description>
 * <copyright>
 * (c) 2003-2016 3S-Smart Software Solutions
 * </copyright>
 */
SET_COMPONENT_NAME(`CmpOpenSSLOEM')
COMPONENT_SOURCES(`CmpOpenSSLOEM.c')
COMPONENT_VERSION(`0x03050A00')

/* TODO: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0001')				

/* TODO: Start defining your ComponentIDs with 0x2000 */
#define CMPID_CmpOpenSSLOEM		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */

#define CLASSID_COpenSSLOEM		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_IOpenSSLOEM		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Templates')

#if defined(CPLUSPLUS) && !defined(CPP_IMPLEMENTATION_SysSockAccept2)
	#define CPP_IMPLEMENTATION_SysSockAccept2\
			CCmpOpenSSLOEM *pCOpenSSLOEM = (COpenSSLOEM *)(ISysSocket2 *)hSocket;\
			hSocket = pCOpenSSLOEM->hOpenSSLOEM;\
			hOpenSSLOEM = SysSockAccept2(hISysSocket,ClassId,hSocket,pSockAddr,piSockAddrSize,pResult);\
			return (RTS_HANDLE)QueryInterface((IBase *)(ISysSocket2 *)this, ITFID_ISysSocket2, NULL);
#endif

USE_ITF(`CMItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`SysSocketItf.m4')
USE_ITF(`SysSocket2Itf.m4')
USE_ITF(`CmpMemPoolItf.m4')
USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysFileItf.m4')
USE_ITF(`SysMemItf.m4')

IMPLEMENT_ITF(`CmpTlsItf.m4',`SysSocket2Itf.m4', `CmpCryptoItf.m4', `CmpX509CertItf.m4')

REQUIRED_IMPORTS(
SettgGetStringValue,
SettgGetIntValue,
SysSockCreate,
SysSockClose,
SysSockSetOption,
SysSockGetOption,
SysSockBind,
SysSockListen,
SysSockAccept,
SysSockConnect,
SysSockSelect,
SysSockShutdown,
SysSockIoctl,
SysSockRecv,
SysSockSend,
SysSockFdIsset,
SysSockFdInit,
SysSockFdZero,
SysSockInetAddr,
SysSockHtons,
SysSockInetNtoa,
SysSockGetSockName,
SysSockGetPeerName,
CMExit,
MemPoolCreateStatic,
MemPoolCreateDynamic,
MemPoolDelete,
MemPoolGetBlock,
MemPoolGetBlock2,
MemPoolPutBlock,
MemPoolAddUsedBlock,
MemPoolAppendUsedBlock,
MemPoolCleanup,
MemPoolRemoveUsedBlock,
MemPoolLock,
MemPoolUnlock,
MemPoolLockBlock,
MemPoolUnlockBlock,
MemPoolIsValidBlock,
CMUtlStrLen,
CMUtlSafeStrCat,
CMUtlSafeStrCpy,
CMUtlStrNICmp,
CMUtlStrICmp,
CMUtlsnprintf,
CMGetCmpName,
SysMemAllocData,
SysMemFreeData)

OPTIONAL_IMPORTS(
EventOpen,
EventClose,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction,
SysFileOpen,
SysFileClose,
SysFileGetSize,
SysFileRead)
