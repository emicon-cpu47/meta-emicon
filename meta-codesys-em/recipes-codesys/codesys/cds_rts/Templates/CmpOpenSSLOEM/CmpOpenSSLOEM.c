/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		CmpOpenSSLOEM component
*	Version:
*	Description:
******************************************************************************/

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif

/* Standard headers*/
#include "CmpStd.h"
#include "CmpOpenSSLOEMDep.h"

#ifdef CMP_TEST_CRYPTO
	static void CmpTestCrypto(void);
#endif

#ifdef CMP_TEST_CERTS
	static void CmpTestCerts(void);
#endif


USE_STMT

#ifdef CPLUSPLUS
	static CCmpOpenSSL *s_pCmpOpenSSLOEM = NULL;
#else
	DECLARE_ADDREF
	DECLARE_RELEASE
	DECLARE_QUERYINTERFACE

	typedef struct CCmpOpenSSLOEM_
	{
		IBase Base;
		ISysSocket2 Socket;	
	} CCmpOpenSSLOEM;

	static unsigned char s_StaticSysSocket2List[MEM_GET_STATIC_LEN(NETSERVER_MAXCHANNELS * 2, CCmpOpenSSLOEM)];
	static RTS_HANDLE s_hSysSocket2Pool = RTS_INVALID_HANDLE;
#endif


#ifndef RTS_COMPACT_MICRO

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	
#ifdef CPLUSPLUS
	INIT_LOCALS_STMT;
	s_pCmpOpenSSLOEM = NULL;
#endif

	if (pInitStruct->pfCMRegisterClass != NULL)
	{
		RTS_HANDLE hClass = pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpTls);
		if (hClass == RTS_INVALID_HANDLE)
			return ERR_FAILED;
		hClass = pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpCrypto);
		if (hClass == RTS_INVALID_HANDLE)
			return ERR_FAILED;
		hClass = pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpX509Cert);
		if (hClass == RTS_INVALID_HANDLE)
			return ERR_FAILED;
	}
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpTls)
	{
		CCmpOpenSSLOEM *pCmpOpenSSLOEM;
		pCmpOpenSSLOEM = static_cast<CCmpOpenSSLOEM *>(new CCmpOpenSSLOEM());
		return (IBase*)pCmpOpenSSLOEM->QueryInterface((ICmpTls *)pCmpOpenSSLOEM, ITFID_IBase, pResult);
	}
	else if (cid == CLASSID_CCmpCrypto || cid == CLASSID_CCmpX509Cert)
	{
		if (s_pCmpOpenSSLOEM == NULL)
			s_pCmpOpenSSLOEM = static_cast<CCmpOpenSSLOEM *>(new CCmpOpenSSLOEM());
		return (IBase*)s_pCmpOpenSSLOEM->QueryInterface((ICmpCrypto *)s_pCmpOpenSSLOEM, ITFID_IBase, pResult);
	}
#else
	if (cid == CLASSID_CCmpTls)
	{
		CCmpOpenSSLOEM *pICmpOpenSSLOEM = (CCmpOpenSSLOEM*)CAL_MemPoolGetBlock2(s_hSysSocket2Pool, 1, COMPONENT_NAME, pResult);
		if (pICmpOpenSSLOEM == NULL)
			return NULL;
		CAL_MemPoolAddUsedBlock(pICmpOpenSSLOEM);
		return QueryInterface(&pICmpOpenSSLOEM->Base, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	if (pIBase->Release())
	{
		if (pIBase == (IBase *)(ICmpTls *)s_pCmpOpenSSLOEM)
			s_pCmpOpenSSLOEM = NULL;
	}
	return ERR_OK;
#else
	pIBase->iRefCount--;
	(void)CAL_MemPoolRemoveUsedBlock(pIBase);
	return CAL_MemPoolPutBlock(pIBase);
#endif
}

#ifndef CPLUSPLUS

IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer ro the IBase interface. So it doesn't matter, which interface
		   is used to get the IBase pointer */
		pBase->bIEC = 0;
		pBase->AddRef = AddRef;
		pBase->Release = Release;
		pBase->QueryInterface = QueryInterface;
		pBase->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pBase;
	}
	if (iid == ITFID_ISysSocket2)
	{
		CCmpOpenSSLOEM *pI = (CCmpOpenSSLOEM *)pBase;
		
		pI->Socket.pBase = pBase;
		pI->Socket.ISysSock2Create = SysSock2Create;
		pI->Socket.ISysSock2Close = SysSock2Close;
		pI->Socket.ISysSock2SetOption = SysSock2SetOption;
		pI->Socket.ISysSock2GetOption = SysSock2GetOption;
		pI->Socket.ISysSock2Bind = SysSock2Bind;
		pI->Socket.ISysSock2Listen = SysSock2Listen;
		pI->Socket.ISysSock2Accept = SysSock2Accept;
		pI->Socket.ISysSock2Connect = SysSock2Connect;
		pI->Socket.ISysSock2Select = SysSock2Select;
		pI->Socket.ISysSock2Shutdown = SysSock2Shutdown;
		pI->Socket.ISysSock2Ioctl = SysSock2Ioctl;
		pI->Socket.ISysSock2Recv = SysSock2Recv;
		pI->Socket.ISysSock2Send = SysSock2Send;
		pI->Socket.ISysSock2FdIsset = SysSock2FdIsset;
		pI->Socket.ISysSock2FdInit = SysSock2FdInit;

		pBase->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pI->Socket;
	}
	RTS_SETRESULT(pResult, ERR_NOT_SUPPORTED);
	return NULL;
}
#endif

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	RTS_RESULT Result = ERR_OK;

	switch (ulHook)
	{
		case CH_INIT2:
		{
	#ifndef CPLUSPLUS
			RTS_RESULT result;
			s_hSysSocket2Pool = CAL_MemPoolCreateStatic(sizeof(CCmpOpenSSLOEM), sizeof(s_StaticSysSocket2List), s_StaticSysSocket2List, &result);
			if (result != ERR_OK)
				return result;
	#endif

			break;
		}
		case CH_INIT3:
		{
			break;
		}
		/* Cyclic */
		case CH_COMM_CYCLE:
		{
#ifdef CMP_TEST_CRYPTO
			{
				static int testdone = 0;
				if (!testdone)
				{
					CmpTestCrypto();
					testdone = 1;
				}
			}
#endif
#ifdef CMP_TEST_CERTS
			{
				static int testdone2 = 0;
				if (!testdone2)
				{
					CmpTestCerts();
					testdone2 = 1;
				}
			}
#endif
			break;
		}
	#ifndef RTS_COMPACT_MICRO		
		/* Shutdown of OpenSSL */
		case CH_EXIT_COMM:
		{
			break;
		}
		case CH_EXIT3:
		{
			break;
		}
		/* OpenSSL shutdown */
		case CH_EXIT2:
		{
	#ifndef CPLUSPLUS
			(void)CAL_MemPoolDelete(s_hSysSocket2Pool, COMPONENT_NAME);
			s_hSysSocket2Pool = RTS_INVALID_HANDLE;
	#endif
			break;
		}
	#endif
		case CH_EXIT:
		{
			EXIT_STMT;
			break;
		}
		default:
			break;
	}
	return Result;
}

/* Init and exit hooks*/

static RTS_RESULT CmpOpenSSLOEMOnInit2(void)
{
	/* TODO: Do your init stuff here */
	return ERR_OK;
}

static RTS_RESULT CmpOpenSSLOEMOnExit2(void)
{
	/* TODO: Do your exit stuff here */
	return ERR_OK;
}

/* Init3 hook */
static RTS_RESULT CmpOpenSSLOEMOnInit3(void)
{
	/* TODO: Do your init stuff here */
	return ERR_OK;
}

/* Exit3 hook */
static RTS_RESULT CmpOpenSSLOEMOnExit3(void)
{
	/* TODO: Do your exit stuff here */
	return ERR_OK;
}




/* *****************************************************************************
 *
 *	CmpTlsItf Implementation 
 *
 ******************************************************************************/

RTS_HANDLE CDECL TlsCreateContext(char* pszNamespace, RTS_RESULT* pResult)
{
	RTS_HANDLE hNewContext = RTS_INVALID_HANDLE;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hNewContext;
}

RTS_HANDLE CDECL TlsCreateContext2(RTS_HANDLE hCert, RTS_UI32 ui32TlsMethod, char* szCipherList, RTS_I32 i32VerifyMode,  RTS_RESULT* pResult)
{
	RTS_HANDLE hNewContext = RTS_INVALID_HANDLE;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hNewContext;
}


RTS_RESULT CDECL TlsFreeContext(RTS_HANDLE hTlsContext)
{
	if (hTlsContext == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

void CDECL TlsRandAdd(const RTS_UI8* pui8Buffer, RTS_I32 i32BufferSize, RTS_REAL64 r64Entroy)
{
	/* TODO */
}

RTS_BOOL CDECL TlsRandCheckStatus(void)
{
	/* TODO */
	return TRUE;
}

RTS_HANDLE CDECL TlsBufferOpen(RTS_HANDLE hContext, RtsByteString* pRxBuffer, RtsByteString* pTxBuffer, RTS_RESULT* pResult)
{
	/* TODO */
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return RTS_INVALID_HANDLE;
}

RTS_RESULT CDECL TlsBufferDataReveived(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL TlsBufferDataSent(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

RTS_BOOL CDECL TlsBufferDataToSendAvailable(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return FALSE;
}

RTS_UI32 CDECL TlsBufferNumOfWrittenBlocks(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return 0;
}

RTS_RESULT CDECL TlsAccept(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL TlsConnect(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

RTS_SSIZE CDECL TlsRead(RTS_HANDLE hTlsConn, RTS_UI8* pbyBuffer, RTS_SSIZE ulBufferSize, RTS_RESULT* pResult)
{
	/* TODO */
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

RTS_SSIZE CDECL TlsWrite(RTS_HANDLE hTlsConn, RTS_UI8* pbyData, RTS_SSIZE ulDataSize, RTS_RESULT* pResult)
{
	/* TODO */
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

RTS_RESULT CDECL TlsShutdown(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL TlsClose(RTS_HANDLE hTlsConn)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}


/* ****************************************************************************
 *
 *	CmpTlsSocket2Itf Implementation 
 *
 ******************************************************************************/

/* Create and destroy TLSSocket connections */
STATICITF RTS_HANDLE CDECL SysSock2Create(RTS_HANDLE hISysSocket, CLASSID ClassId, SysSock_Parameter *pParameter, RTS_RESULT *pResult)
{
	RTS_HANDLE hConnection = RTS_INVALID_HANDLE;
	if (ClassId != CLASSID_CCmpTls || pParameter->ui32Type != SYSSOCK_TYPE_TLS)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO: Create a new socket and set hConnection */

	RTS_SETRESULT(pResult, ERR_OK);
	return hConnection;
}

STATICITF RTS_RESULT CDECL SysSock2Close(RTS_HANDLE hSocket)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2SetOption(RTS_HANDLE hSocket, RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 iOptionLen)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2GetOption(RTS_HANDLE hSocket, RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 *piOptionLen)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2Bind(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2Listen(RTS_HANDLE hSocket, RTS_I32 iMaxConnections)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

/* By default TlsSocket will be nonblocking. If you use FIONBIO, to set blocking mode
 * Tls connecting and shutdown will be blocking to.
 */
STATICITF RTS_RESULT CDECL SysSock2Ioctl(RTS_HANDLE hSocket, RTS_I32 iCommand, RTS_I32 *piParameter)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_HANDLE CDECL SysSock2Accept(RTS_HANDLE hISysSocket, CLASSID ClassId, RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize, RTS_RESULT *pResult)
{
	RTS_HANDLE hNewTlsConn = RTS_INVALID_HANDLE;
	if (hISysSocket == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}
		
	/* TODO: Accept new socket in hNewTlsConn */
	RTS_SETRESULT(pResult, ERR_OK);
	return hNewTlsConn;
}

STATICITF RTS_RESULT CDECL SysSock2Connect(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2Select(RTS_HANDLE hSocket, RTS_I32 iWidth, SOCKET_FD_SET *fdRead, SOCKET_FD_SET *fdWrite, SOCKET_FD_SET *fdExcept, SOCKET_TIMEVAL *ptvTimeout, RTS_I32 *pnReady)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2Shutdown(RTS_HANDLE hSocket, RTS_I32 iHow)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_BOOL CDECL SysSock2FdIsset(RTS_HANDLE hSocket, SOCKET_FD_SET *pfs)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_RESULT CDECL SysSock2FdInit(RTS_HANDLE hSocket, SOCKET_FD_SET *pfs)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF RTS_SSIZE CDECL SysSock2Recv(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult)
{
	RTS_SSIZE lBytesReceived = 0;
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return lBytesReceived;
	
}

STATICITF RTS_SSIZE CDECL SysSock2Send(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult)
{
	RTS_SSIZE lBytesSent = 0;
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return lBytesSent;
}

STATICITF RTS_SSIZE CDECL SysSockRecvFrom2(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

STATICITF RTS_SSIZE CDECL SysSockSendTo2(RTS_HANDLE hSocket, char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult)
{
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return 0;
}

STATICITF_DEF RTS_RESULT CDECL SysSockGetSockName2(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

STATICITF_DEF RTS_RESULT CDECL SysSockGetPeerName2(RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize)
{
	if (hSocket == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}


/* *****************************************************************************
 *
 *	CmpCryptoItf Implementation 
 *
 ******************************************************************************/
RTS_HANDLE CDECL CryptoGetAlgorithmById(RTS_UI32 ui32CryptoID, RTS_RESULT* pResult)
{
	RTS_HANDLE hCrypto = RTS_INVALID_HANDLE;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCrypto;
}

RTS_HANDLE CDECL CryptoGetFirstAlgorithm(RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult)
{
	RTS_HANDLE hCrypto = RTS_INVALID_HANDLE;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCrypto;
}

RTS_HANDLE CDECL CryptoGetNextAlgorithm(RTS_HANDLE hCrypto, RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult)
{
	RTS_HANDLE hCryptoNext = RTS_INVALID_HANDLE;

	if (hCrypto == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCryptoNext;
}

RtsCryptoInfo* CDECL CryptoGetAlgorithmInfo(RTS_HANDLE hCrypto, RTS_RESULT* pResult)
{
	RtsCryptoInfo *pInfo = NULL;
	if (hCrypto == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return NULL;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return pInfo;
}

RTS_RESULT CDECL CryptoSymmetricEncrypt(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pCipherText)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoSymmetricDecrypt(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pPlainText)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoAsymmetricEncrypt(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey publicKey, RtsByteString* pCipherText)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoAsymmetricDecrypt(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey privateKey, RtsByteString* pPlainText)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoGenerateHash(RTS_HANDLE hAlgo, RtsByteString* pData, RtsByteString* pHash)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	if (pData == NULL || pHash == NULL || pData->ui32Len == 0 || pData->pByData == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoHMACSign(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	if (pData == NULL || pSignature == NULL || pData->ui32Len == 0 || pData->pByData == NULL ||
		key.keyType != KEYTYPE_KEY || (key.keyType == KEYTYPE_KEY && (key.key.byteString.pByData == NULL || key.key.byteString.ui32Len == 0)))
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoHMACVerify(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	if (pData == NULL || pSignature == NULL || pData->ui32Len == 0 || pData->pByData == NULL ||
		key.keyType != KEYTYPE_KEY || (key.keyType == KEYTYPE_KEY && (key.key.byteString.pByData == NULL || key.key.byteString.ui32Len == 0)))
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoSignatureGenerate(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey privateKey, RtsByteString* pSignature)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	if (pData == NULL || pSignature == NULL || pData->ui32Len == 0 || pData->pByData == NULL)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoSignatureVerify(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey publicKey, RtsByteString* pSignature)
{
	if (hAlgo == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	if (pData == NULL || pSignature == NULL || pData->ui32Len == 0 || pData->pByData == NULL)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoGenerateRandomNumber(RTS_UI32 ui32NumOfRandomBytes, RtsByteString* pRandom)
{
	if(pRandom == NULL|| (pRandom != NULL && (pRandom->pByData == NULL || pRandom->ui32MaxLen == 0)) || ui32NumOfRandomBytes == 0)
		return ERR_PARAMETER;
	if(ui32NumOfRandomBytes > pRandom->ui32MaxLen)
		return ERR_PARAMETER;

	/* TODO */
	pRandom->ui32Len = ui32NumOfRandomBytes;
	return ERR_OK;
}

RTS_UI32 CDECL CryptoGetAsymmetricKeyLength(RtsCryptoKey privateKey, RTS_RESULT* pResult)
{
	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return 0;
}

RTS_RESULT CDECL CryptoRtsByteStringInit(RtsByteString* pByteString)
{
	if (pByteString == NULL)
		return ERR_PARAMETER;

	memset(pByteString, 0, sizeof(RtsByteString));
	return ERR_OK;
}

RTS_RESULT CryptoRtsByteStringInit2(RtsByteString* pByteString, RTS_UI32 ui32BufferSize, RTS_UI8* pBuffer)
{
	RTS_RESULT Result = ERR_OK;

	Result = CryptoRtsByteStringInit(pByteString);
	if (ui32BufferSize != 0 && pBuffer != NULL)
	{
		pByteString->pByData = pBuffer;
		pByteString->ui32MaxLen = ui32BufferSize;
		pByteString->xDynamic = FALSE;
		Result = ERR_OK;
	}
	else if (ui32BufferSize != 0)
	{
		pByteString->pByData = (RTS_UI8*)CAL_SysMemAllocData(COMPONENT_NAME, ui32BufferSize, &Result);
		if (pByteString->pByData != NULL)
		{
			pByteString->ui32MaxLen = ui32BufferSize;
			pByteString->xDynamic = TRUE;
			Result = ERR_OK;
		}
		else
			Result = ERR_FAILED;
	}
	return Result;
}

RTS_RESULT CDECL CryptoRtsByteStringExit(RtsByteString* pByteString)
{
	if (pByteString == NULL)
		return ERR_PARAMETER;

	if (pByteString->xDynamic && pByteString->pByData != NULL)
		CAL_SysMemFreeData(COMPONENT_NAME, pByteString->pByData);
	memset(pByteString, 0, sizeof(RtsByteString));
	return ERR_OK;
}

RTS_RESULT CDECL CryptoKeyInit(RtsCryptoKey* pKey, RtsCryptoKeyStorage key, RTSCRYPTOKEYTYPE keyType)
{
	if (pKey == NULL)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL CryptoKeyExit(RtsCryptoKey* pKey)
{
	if (pKey == NULL)
		return ERR_PARAMETER;

	/* TODO */
	memset(pKey, 0, sizeof(RtsCryptoKey));
	return ERR_OK;
}

/* *****************************************************************************
*
*	CmpX509CertItf Implementation
*
******************************************************************************/

/* --------------------------------------------------------------------------- */
/*                   Basic Certificate store functions                         */
/* --------------------------------------------------------------------------- */
RTS_HANDLE CDECL X509CertStoreOpen(CMPID componentID, RTS_RESULT* pResult)
{
	RTS_HANDLE hCertStore = RTS_INVALID_HANDLE;

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCertStore;
}

RTS_RESULT CDECL X509CertStoreClose(RTS_HANDLE hCertStore)
{
	if (hCertStore == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertVerify(RTS_HANDLE hCertStore, RTS_HANDLE hCert)
{
	if (hCertStore == RTS_INVALID_HANDLE || hCert == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_HANDLE CDECL X509CertStoreSearchGetFirst(RTS_HANDLE hCertStore, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult)
{
	RTS_HANDLE hCert = RTS_INVALID_HANDLE;
	
	if (hCertStore == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCert;
}

RTS_HANDLE CDECL X509CertStoreSearchGetNext(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult)
{
	RTS_HANDLE hCertNext = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE || hCert == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}
	
	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCertNext;
}

RTS_RESULT CDECL X509CertGetPrivateKey(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsCryptoKey* pPrivateKey)
{
	if (hCertStore == RTS_INVALID_HANDLE || hCert == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

/* --------------------------------------------------------------------------- */
/*                      Handling single certificates                           */
/* --------------------------------------------------------------------------- */
RTS_HANDLE CDECL X509ParseCertificate(RtsByteString* pCert, RTSCERTENCODING encoding, RTS_RESULT * pResult)
{
	RTS_HANDLE hParsedCert = RTS_INVALID_HANDLE;
	if (pCert == NULL)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hParsedCert;
}

RTS_RESULT CDECL X509CertGetContent(RTS_HANDLE hCert, RtsX509CertInfo* pCertInfo)
{
	if (hCert == RTS_INVALID_HANDLE || pCertInfo == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertGetBinary(RTS_HANDLE hCert, RTSCERTENCODING encoding, RtsByteString* pCert)
{
	if (hCert == RTS_INVALID_HANDLE || pCert == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertGetPublicKey(RTS_HANDLE hCert, RtsCryptoKey* pPublicKey)
{
	if (hCert == RTS_INVALID_HANDLE || pPublicKey == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertGetThumbprint(RTS_HANDLE hCert, RTSCRYPTOID* hashAlgorithm, RtsByteString* pThumbprint)
{
	if (hCert == RTS_INVALID_HANDLE || hashAlgorithm == NULL || pThumbprint == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_BOOL CDECL X509CertIsDateValid(RTS_HANDLE hCert, RTS_RESULT *pResult)
{
	if (hCert == RTS_INVALID_HANDLE || hCert == NULL)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return FALSE;
	}
	/* TODO */
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return FALSE;
}

RTS_BOOL CDECL X509CertIsSelfSigned(RTS_HANDLE hCert, RTS_RESULT *pResult)
{
	if (hCert == RTS_INVALID_HANDLE || hCert == NULL)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return FALSE;
	}
	/* TODO */
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return FALSE;
}

RTS_BOOL CDECL X509CertHasExtendedKeyUsage(RTS_HANDLE hCert, RTS_UI32 numOfExKeyUsages, RtsOID *pExKeyUsages, RTS_RESULT *pResult)
{
	RtsX509CertInfo certInfo;
	RTS_IEC_UDINT i, j;
	RTS_BOOL bKeyUsageFound = FALSE;
	RTS_RESULT Result = ERR_FAILED;

	X509CertInfoInit(&certInfo, sizeof(certInfo));

	do
	{
		if (hCert == RTS_INVALID_HANDLE || hCert == NULL)
		{
			Result = ERR_PARAMETER;
			break;
		}
		if (numOfExKeyUsages == 0 || pExKeyUsages == NULL)
		{
			Result = ERR_PARAMETER;
			break;
		}


		Result = X509CertGetContent(hCert, &certInfo);
		if (Result != ERR_OK)
			break;

		if (certInfo.numOfExKeyUsages < numOfExKeyUsages)
		{
			bKeyUsageFound = FALSE;
			break;
		}

		for (i = 0; i < numOfExKeyUsages; i++)
		{
			bKeyUsageFound = FALSE;
			for (j = 0; j < certInfo.numOfExKeyUsages; j++)
			{
				if (pExKeyUsages[i].length == certInfo.pExKeyUsages[j].length)
				{
					if (pExKeyUsages[i].length > sizeof(RtsOIDStore))
					{
						if (memcmp(pExKeyUsages[i].data.pOID, certInfo.pExKeyUsages[j].data.pOID, pExKeyUsages[i].length) == 0)
						{
							bKeyUsageFound = TRUE;
							break;
						}
					}
					else
					{
						if (memcmp(pExKeyUsages[i].data.aOID, certInfo.pExKeyUsages[j].data.aOID, pExKeyUsages[i].length) == 0)
						{
							bKeyUsageFound = TRUE;
							break;
						}
					}
				}
			}
			if (bKeyUsageFound == FALSE)
				break;
		}
	} while (0);

	X509CertInfoExit(&certInfo);
	RTS_SETRESULT(pResult, Result);
	return bKeyUsageFound;
}

RTS_RESULT CDECL X509CertKeyClose(RtsCryptoKey* pKey)
{
	if (pKey == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertKeyCloseInternal(RtsCryptoKey* pKey)
{
	if (pKey == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_BOOL CDECL X509CertCompare(RTS_HANDLE hCert1, RTS_HANDLE hCert2)
{
	/* TODO */
	return FALSE;
}

RTS_RESULT CDECL X509CertClose(RTS_HANDLE hCert)
{
	if (hCert == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

/* --------------------------------------------------------------------------- */
/*                      Handling CMS containers                               */
/* --------------------------------------------------------------------------- */
RTS_RESULT CDECL X509CertCmsVerify(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData)
{
	return X509CertCmsVerify2(hCertStore, pCms, encoding, pInData, pOutData, NULL);
}


RTS_RESULT CDECL X509CertCmsVerify2(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData, RTS_HANDLE* phSignerCert)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL X509CertCmsDecrypt(RTS_HANDLE hCertStore, RTS_HANDLE hRecipientCert, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pOutData)
{
	/* TODO */
	return ERR_NOTIMPLEMENTED;
}

/* --------------------------------------------------------------------------- */
/*                             Utility functions                               */
/* --------------------------------------------------------------------------- */

RTS_RESULT CDECL X509SplitCertificateChain(RtsByteString* pCertificateChain, RtsByteString* pCertificates, RTS_UI32* pui32NumOfCertificates)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL RtsOIDCreate(char* id, RtsOID* oid)
{
	if (id == NULL || oid == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL RtsOIDGetID(RtsOID* oid, RtsByteString* pBuffer)
{
	if (oid == NULL || pBuffer == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL RtsOIDGetName(RtsOID* oid, RtsByteString* pBuffer)
{
	if (oid == NULL || pBuffer == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL RtsOIDClear(RtsOID* oid)
{
	if (oid == NULL)
		return ERR_PARAMETER;
	
	/* TODO */
	memset(oid, 0, sizeof(RtsOID));
	return ERR_OK;
}

RTS_RESULT CDECL X509CertInfoInit(RtsX509CertInfo* pCertInfo, RTS_UI32 structSize)
{
	if (pCertInfo == NULL)
		return ERR_PARAMETER;
	if (structSize != sizeof(RtsX509CertInfo))
		return ERR_PARAMETER;
	memset(pCertInfo, 0, structSize);
	pCertInfo->ui32StructSize = structSize;
	return ERR_OK;
}

RTS_RESULT CDECL X509CertInfoExit(RtsX509CertInfo* pCertInfo)
{
	if (pCertInfo == NULL)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

/* --------------------------------------------------------------------------- */
/*                   Organizing the certificate store                          */
/* --------------------------------------------------------------------------- */

RTS_HANDLE CDECL X509CertStoreGetFirstBackend(RTS_HANDLE hCertStore, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult)
{
	RTS_HANDLE hBackend = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hBackend;
}

RTS_HANDLE CDECL X509CertStoreGetNextBackend(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult)
{
	RTS_HANDLE hNextBackend = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE || hBackend == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hNextBackend;
}

RTS_RESULT CDECL X509CertStorGetBackendInfo(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo)
{
	if (hCertStore == RTS_INVALID_HANDLE || hBackend == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertCreateSelfSignedAsync(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTS_UI32 nIndex, PFX509ASYNCCALLBACK pfCallback)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_HANDLE CDECL X509CertCreateSelfSigned(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTS_RESULT *pResult)
{
	RTS_HANDLE hCert = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE || pCertInfo == NULL)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCert;
}

RTS_RESULT CDECL X509CertCreateCSRAsync(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, CMPID cmpID, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR, RTS_UI32 nIndex, PFX509ASYNCCALLBACK pfCallback)
{
	return ERR_NOTIMPLEMENTED;
}

RTS_RESULT CDECL X509CertCreateCSR(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString * pCSR)
{
	if (hCertStore == RTS_INVALID_HANDLE || pCertInfo == NULL)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertStoreAddCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTSCERTTRUSTLEVEL trustLevel)
{
	if (hCertStore == RTS_INVALID_HANDLE || hCert == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_RESULT CDECL X509CertStoreRemoveCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_BOOL bRemovePrivateKey)
{
	if (hCertStore == RTS_INVALID_HANDLE || hCert == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;

	/* TODO */
	return ERR_OK;
}

RTS_HANDLE CDECL X509CertStoreGetFirstCert(RTS_HANDLE hCertStore, RTS_HANDLE* hBackend, RTSCERTTRUSTLEVEL trustLevel, RTS_RESULT* pResult)
{
	RTS_HANDLE hCert = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hCert;
}

RTS_HANDLE CDECL X509CertStoreGetNextCert(RTS_HANDLE hCertStore, RTS_HANDLE* hBackend, RTS_HANDLE hCert, RTS_RESULT* pResult)
{
	RTS_HANDLE hNextCert = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE || hCert == RTS_INVALID_HANDLE)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hNextCert;
}

RTS_HANDLE CDECL X509CertStoreRegister(RTS_HANDLE hCertStore, CMPID cmpID, RtsX509CertInfo* pCertInfo, RTS_RESULT* pResult)
{
	RTS_HANDLE hRegistered = RTS_INVALID_HANDLE;
	if (hCertStore == RTS_INVALID_HANDLE || cmpID == 0 || pCertInfo == NULL)
	{
		RTS_SETRESULT(pResult, ERR_PARAMETER);
		return RTS_INVALID_HANDLE;
	}

	/* TODO */
	RTS_SETRESULT(pResult, ERR_OK);
	return hRegistered;
}

RTS_RESULT CDECL X509CertStoreUnregister(RTS_HANDLE hCertStore, RTS_HANDLE hRegisteredComponent)
{
	if (hCertStore == RTS_INVALID_HANDLE || hRegisteredComponent == RTS_INVALID_HANDLE)
		return ERR_PARAMETER;
	
	/* TODO */
	return ERR_OK;
}

RTS_HANDLE CDECL X509CertStoreGetRegisteredCert(RTS_HANDLE hCertStore, RTS_HANDLE hUseCase, RTS_RESULT* pResult)
{
	/* TODO */
	RTS_SETRESULT(pResult, ERR_NOTIMPLEMENTED);
	return RTS_INVALID_HANDLE;
}


/* **************************************************************************
 * External library implementation 
*****************************************************************************/
/* External library implementation */
void CDECL CDECL_EXT cryptoasymmetricdecrypt(cryptoasymmetricdecrypt_struct *p)
{
	p->CryptoAsymmetricDecrypt = CryptoAsymmetricDecrypt(p->hAlgo, p->pCipherText, p->privateKey, p->pPlainText);
}

void CDECL CDECL_EXT cryptoasymmetricencrypt(cryptoasymmetricencrypt_struct *p)
{
	p->CryptoAsymmetricEncrypt = CryptoAsymmetricEncrypt(p->hAlgo, p->pCipherText, p->publicKey, p->pCipherText);
}

void CDECL CDECL_EXT cryptogeneratehash(cryptogeneratehash_struct *p)
{
	p->CryptoGenerateHash = CryptoGenerateHash(p->hAlgo, p->pData, p->pHash);
}

void CDECL CDECL_EXT cryptogeneraterandomnumber(cryptogeneraterandomnumber_struct *p)
{
	p->CryptoGenerateRandomNumber = CryptoGenerateRandomNumber(p->ui32NumOfRandomBytes, p->pRandom);
}

void CDECL CDECL_EXT cryptogetalgorithmbyid(cryptogetalgorithmbyid_struct *p)
{
	p->CryptoGetAlgorithmById = CryptoGetAlgorithmById(p->ui32CryptoID, p->pResult);
}

void CDECL CDECL_EXT cryptogetasymmetrickeylength(cryptogetasymmetrickeylength_struct *p)
{
	p->CryptoGetAsymmetricKeyLength = CryptoGetAsymmetricKeyLength(p->asymmetricKey, p->pResult);
}

void CDECL CDECL_EXT cryptogetfirstalgorithm(cryptogetfirstalgorithm_struct *p)
{
	p->CryptoGetFirstAlgorithm = CryptoGetFirstAlgorithm(p->ui32CryptoType, p->pszName, p->i32MaxNameLen, p->pui32CryptoID, p->pResult);
}

void CDECL CDECL_EXT cryptogetnextalgorithm(cryptogetnextalgorithm_struct *p)
{
	p->CryptoGetNextAlgorithm = CryptoGetNextAlgorithm(p->hCrypto, p->ui32CryptoType, p->pszName, p->i32MaxNameLen, p->pui32CryptoID, p->pResult);
}

void CDECL CDECL_EXT cryptohmacsign(cryptohmacsign_struct *p)
{
	p->CryptoHMACSign = CryptoHMACSign(p->hAlgo, p->pData, p->key, p->pSignature);
}

void CDECL CDECL_EXT cryptohmacverify(cryptohmacverify_struct *p)
{
	p->CryptoHMACVerify = CryptoHMACVerify(p->hAlgo, p->pData, p->key, p->pSignature);
}

void CDECL CDECL_EXT cryptosignaturegenerate(cryptosignaturegenerate_struct *p)
{
	p->CryptoSignatureGenerate = CryptoSignatureGenerate(p->hAlgo, p->pData, p->privateKey, p->pSignature);
}

void CDECL CDECL_EXT cryptosignatureverify(cryptosignatureverify_struct *p)
{
	p->CryptoSignatureVerify = CryptoSignatureVerify(p->hAlgo, p->pData, p->publicKey, p->pSignature);
}

void CDECL CDECL_EXT cryptosymmetricdecrypt(cryptosymmetricdecrypt_struct *p)
{
	p->CryptoSymmetricDecrypt = CryptoSymmetricDecrypt(p->hAlgo, p->pCipherText, p->key, p->pInitVector, p->xEnablePadding, p->pPlainText);
}

void CDECL CDECL_EXT cryptosymmetricencrypt(cryptosymmetricencrypt_struct *p)
{
	p->CryptoSymmetricEncrypt = CryptoSymmetricEncrypt(p->hAlgo, p->pPlainText, p->key, p->pInitVector, p->xEnablePadding, p->pCipherText);
}

void CDECL CDECL_EXT cryptokeyinit(cryptokeyinit_struct *p)
{
	p->CryptoKeyInit = CryptoKeyInit(p->pKey, p->key, p->keyType);
}

void CDECL CDECL_EXT cryptokeyexit(cryptokeyexit_struct *p)
{
	p->CryptoKeyExit = CryptoKeyExit(p->pKey);
}

void CDECL CDECL_EXT cryptortsbytestringinit(cryptortsbytestringinit_struct *p)
{
	p->CryptoRtsByteStringInit = CryptoRtsByteStringInit(p->pByteString);
}

void CDECL CDECL_EXT cryptortsbytestringexit(cryptortsbytestringexit_struct *p)
{
	p->CryptoRtsByteStringExit = CryptoRtsByteStringExit(p->pByteString);
}

void CDECL CDECL_EXT rtsoidclear(rtsoidclear_struct *p)
{
	if (p != NULL)
	{
		p->RtsOIDClear = RtsOIDClear(p->oid);
	}
}

void CDECL CDECL_EXT rtsoidcreate(rtsoidcreate_struct *p)
{
	if (p != NULL)
	{
		p->RtsOIDCreate = RtsOIDCreate(p->id, p->oid);
	}
}

void CDECL CDECL_EXT rtsoidgetid(rtsoidgetid_struct *p)
{
	if (p != NULL)
	{
		p->RtsOIDGetID = RtsOIDGetID(p->oid, p->pBuffer);
	}
}

void CDECL CDECL_EXT rtsoidgetname(rtsoidgetname_struct *p)
{
	if (p != NULL)
	{
		p->RtsOIDGetName = RtsOIDGetName(p->oid, p->pBuffer);
	}
}

void CDECL CDECL_EXT x509certclose(x509certclose_struct *p)
{
	if (p != NULL)
	{
		p->X509CertClose = X509CertClose(p->hCert);
	}
}

void CDECL CDECL_EXT x509certgetbinary(x509certgetbinary_struct *p)
{
	if (p != NULL)
	{
		p->X509CertGetBinary = X509CertGetBinary(p->hCert, p->encoding, p->pCert);
	}
}

void CDECL CDECL_EXT x509certgetcontent(x509certgetcontent_struct *p)
{
	if (p != NULL)
	{
		p->X509CertGetContent = X509CertGetContent(p->hCert, p->pCertContent);
	}
}

void CDECL CDECL_EXT x509certgetpublickey(x509certgetpublickey_struct *p)
{
	if (p != NULL)
	{
		p->X509CertGetPublicKey = X509CertGetPublicKey(p->hCert, p->pPublicKey);
	}
}

void CDECL CDECL_EXT x509certgetthumbprint(x509certgetthumbprint_struct *p)
{
	if (p != NULL)
	{
		p->X509CertGetThumbprint = X509CertGetThumbprint(p->hCert, p->hashAlgorithm, p->pThumprint);
	}
}

void CDECL CDECL_EXT x509certinfoexit(x509certinfoexit_struct *p)
{
	if (p != NULL)
	{
		p->X509CertInfoExit = X509CertInfoExit(p->pCertInfo);
	}
}

void CDECL CDECL_EXT x509certinfoinit(x509certinfoinit_struct *p)
{
	if (p != NULL)
	{
		p->X509CertInfoInit = X509CertInfoInit(p->pCertInfo, p->structSize);
	}
}

void CDECL CDECL_EXT x509certkeyclose(x509certkeyclose_struct *p)
{
	if (p != NULL)
	{
		p->X509CertKeyClose = X509CertKeyClose(p->pKey);
	}
}

void CDECL CDECL_EXT x509parsecertificate(x509parsecertificate_struct *p)
{
	if (p != NULL)
	{
		p->X509ParseCertificate = X509ParseCertificate(p->pCert, p->encoding, p->pResult);
	}
}

void CDECL CDECL_EXT x509certgetprivatekey(x509certgetprivatekey_struct *p)
{
	if (p != NULL)
	{
		p->X509CertGetPrivateKey = X509CertGetPrivateKey(p->hCertStore, p->hCert, p->pPrivateKey);
	}
}

void CDECL CDECL_EXT x509certstoreclose(x509certstoreclose_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreClose = X509CertStoreClose(p->hCertStore);
	}
}

void CDECL CDECL_EXT x509certstoreopen(x509certstoreopen_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreOpen = X509CertStoreOpen(p->componentID, p->pResult);
	}

}

void CDECL CDECL_EXT x509certstoresearchgetfirst(x509certstoresearchgetfirst_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreSearchGetFirst = X509CertStoreSearchGetFirst(p->hCertStore, p->pFilters, p->ui32NumOfFilters, p->pResult);
	}
}

void CDECL CDECL_EXT x509certstoresearchgetnext(x509certstoresearchgetnext_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreSearchGetNext = X509CertStoreSearchGetNext(p->hCertStore, p->hCert, p->pFilters, p->ui32NumOfFilters, p->pResult);
	}
}

void CDECL CDECL_EXT x509certstoreregister(x509certstoreregister_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreRegister = X509CertStoreRegister(p->hCertStore, p->cmpID, p->pCertInfo, p->pResult);
	}
}

void CDECL CDECL_EXT x509certstoreunregister(x509certstoreunregister_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreUnregister = X509CertStoreUnregister(p->hCertStore, p->hRegisteredComponent);
	}
}

void CDECL CDECL_EXT x509certcreateselfsigned(x509certcreateselfsigned_struct *p)
{
	if (p != NULL)
	{
		p->X509CertCreateSelfSigned = X509CertCreateSelfSigned(p->hCertStore, p->hBackend, p->pCertInfo, p->ui32KeySize, p->pResult);
	}
}

void CDECL CDECL_EXT x509certverify(x509certverify_struct *p)
{
	if (p != NULL)
	{
		p->X509CertVerify = X509CertVerify(p->hCertStore, p->hCert);
	}
}

void CDECL CDECL_EXT x509certcmsverify(x509certcmsverify_struct *p)
{
	if (p != NULL)
	{
		p->X509CertCmsVerify = X509CertCmsVerify(p->hCertStore, p->pCms, p->encoding, p->pInData, p->pOutData);
	}
}

void CDECL CDECL_EXT x509certcmsdecrypt(x509certcmsdecrypt_struct *p)
{
	if (p != NULL)
	{
		p->X509CertCmsDecrypt = X509CertCmsDecrypt(p->hCertStore, p->hRecipientCert, p->pCms, p->encoding, p->pOutData);
	}
}

void CDECL CDECL_EXT x509certcreatecsr(x509certcreatecsr_struct *p)
{
	if (p != NULL)
	{
		p->X509CertCreateCSR = X509CertCreateCSR(p->hCertStore, p->hBackend, p->pCertInfo, p->ui32KeySize, p->encoding, p->pCSR);
	}
}

void CDECL CDECL_EXT x509certstoreaddcert(x509certstoreaddcert_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreAddCert = X509CertStoreAddCert(p->hCertStore, p->hBackend, p->hCert, p->trustLevel);
	}
}

void CDECL CDECL_EXT x509certstoreremovecert(x509certstoreremovecert_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreRemoveCert = X509CertStoreRemoveCert(p->hCertStore, p->hBackend, p->hCert, p->xRemovePrivateKey);
	}
}

void CDECL CDECL_EXT x509certstoregetfirstcert(x509certstoregetfirstcert_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreGetFirstCert = X509CertStoreGetFirstCert(p->hCertStore, p->hBackend, p->trustLevel, p->pResult);
	}
}


void CDECL CDECL_EXT x509certstoregetnextcert(x509certstoregetnextcert_struct *p)
{
	if (p != NULL)
	{
		p->X509CertStoreGetNextCert = X509CertStoreGetNextCert(p->hCertStore, p->hBackend, p->hCert, p->pResult);
	}
}

void CDECL CDECL_EXT cmptlscreatecontext(cmptlscreatecontext_struct *p)
{
	p->CmpTlsCreateContext = TlsCreateContext2(p->hCert, p->tlsMethod, p->cipherList, p->verifyMode, p->pResult);
}

void CDECL CDECL_EXT cmptlsfreecontext(cmptlsfreecontext_struct *p)
{
	p->CmpTlsFreeContext = TlsFreeContext(p->hTlsContext);
}

void CDECL CDECL_EXT cmptlsaccept(cmptlsaccept_struct *p)
{
	p->CmpTlsAccept = TlsAccept(p->hTlsConn);
}

void CDECL CDECL_EXT cmptlsbufferdatareceived(cmptlsbufferdatareceived_struct *p)
{
	p->CmpTlsBufferDataReceived = TlsBufferDataReveived(p->hTlsConn);
}

void CDECL CDECL_EXT cmptlsbufferdatasent(cmptlsbufferdatasent_struct *p)
{
	p->CmpTlsBufferDataSent = TlsBufferDataSent(p->hTlsConn);
}

void CDECL CDECL_EXT cmptlsbufferdatatosendavailable(cmptlsbufferdatatosendavailable_struct *p)
{
	if (TlsBufferDataToSendAvailable(p->hTlsConn))
		p->CmpTlsBufferDataToSendAvailable = TRUE;
	else
		p->CmpTlsBufferDataToSendAvailable = FALSE;
}

void CDECL CDECL_EXT cmptlsbufferopen(cmptlsbufferopen_struct *p)
{
	p->CmpTlsBufferOpen = TlsBufferOpen(p->hTlsContext, p->pRxBuffer, p->pTxBuffer, p->pResult);
}

void CDECL CDECL_EXT cmptlsclose(cmptlsclose_struct *p)
{
	p->CmpTlsClose = TlsClose(p->hTlsConn);
}

void CDECL CDECL_EXT cmptlsconnect(cmptlsconnect_struct *p)
{
	p->CmpTlsConnect = TlsConnect(p->hTlsConn);
}

void CDECL CDECL_EXT cmptlsread(cmptlsread_struct *p)
{
	p->CmpTlsRead = TlsRead(p->hTlsConn, p->pbyBuffer, p->xiBufferSize, p->pResult);
}

void CDECL CDECL_EXT cmptlsshutdown(cmptlsshutdown_struct *p)
{
	p->CmpTlsShutdown = TlsShutdown(p->hTlsConn);
}

void CDECL CDECL_EXT cmptlswrite(cmptlswrite_struct *p)
{
	p->CmpTlsWrite = TlsWrite(p->hTlsConn, p->pbyData, p->xiDataSize, p->pResult);
}


/* ******************************************************
 * Crypto test functions 
 ********************************************************/
#ifdef CMP_TEST_CRYPTO
static void CmpTestCrypto(void)
{

	RTS_HANDLE hAlgo = RTS_INVALID_HANDLE, hAlgo2 = RTS_INVALID_HANDLE;
	RTS_RESULT Result = ERR_OK;
	unsigned char szplainText[] = "Hallo Welt das ist ein erster Test des neuen Crypto Interfaces des Laufzeitsystems. Bitte verschlüssele mich gut. Test 012345678";
	unsigned char szcipherTest[512] = {0};
	unsigned char szdecryptedText[512] = {0};
	unsigned char szInitVector[16] = {0};
	unsigned char szkey[16] = {0};
	unsigned char szHash[20] = {0};
	unsigned char szSignature[512] ={0};
	unsigned char* test = NULL;
	unsigned char* test2 = NULL;

	RtsByteString plainText;
	RtsByteString cipherText;
	RtsByteString decryptedText;
	RtsByteString initVector;
	RtsByteString key;
	RtsByteString hash;
	RtsByteString signature;
	RtsCryptoKey crypto_key;

	memset(&plainText, 0, sizeof(plainText));
	memset(&cipherText, 0, sizeof(cipherText));
	memset(&decryptedText, 0, sizeof(decryptedText));
	memset(&initVector, 0, sizeof(initVector));
	memset(&key, 0, sizeof(key));
	memset(&crypto_key, 0, sizeof(crypto_key));
	memset(&hash, 0, sizeof(hash));
	memset(&signature, 0, sizeof(signature));


	plainText.pByData = szplainText;
	plainText.ui32Len = plainText.ui32MaxLen = sizeof(szplainText);

	cipherText.pByData = szcipherTest;
	cipherText.ui32Len = 0;
	cipherText.ui32MaxLen = sizeof(szcipherTest);

	decryptedText.pByData = szdecryptedText;
	decryptedText.ui32Len = 0;
	decryptedText.ui32MaxLen = sizeof(szdecryptedText);

	initVector.pByData = szInitVector;
	initVector.ui32Len = initVector.ui32MaxLen = sizeof(szInitVector);

	key.pByData = szkey;
	key.ui32Len = key.ui32MaxLen = sizeof(szkey);

	crypto_key.keyType = KEYTYPE_KEY;
	/*crypto_key.key.key.pKey = &key;*/

	hash.pByData = szHash;
	hash.ui32MaxLen = sizeof(szHash);

	signature.pByData = szSignature;
	signature.ui32MaxLen = sizeof(szSignature);

	RAND_pseudo_bytes(szInitVector, sizeof(szInitVector));
	RAND_pseudo_bytes(szkey, sizeof(szkey));

	hAlgo = CryptoGetAlgorithmById(RTSCRYPTOID_AES_128_CBC, &Result);
	if(Result == ERR_OK)
	{
		CryptoSymmetricEncrypt(hAlgo, &plainText, crypto_key, &initVector,1, &cipherText);
		CryptoSymmetricDecrypt(hAlgo, &cipherText, crypto_key, &initVector,1, &decryptedText);
	}

	hAlgo = CryptoGetAlgorithmById(RTSCRYPTOID_HASH_SHA1, &Result);
	if(Result == ERR_OK)
	{
		CryptoGenerateHash(hAlgo, &plainText, &hash);
	}

	hAlgo = CryptoGetAlgorithmById(RTSCRYPTOID_HMAC_SHA1, &Result);
	if(Result == ERR_OK)
	{
		memset(cipherText.pByData, 0, cipherText.ui32MaxLen);
		CryptoHMACSign(hAlgo, &plainText, crypto_key, &cipherText);
		CryptoHMACVerify(hAlgo, &plainText, crypto_key, &cipherText);
	}

	hAlgo = CryptoGetAlgorithmById(RTSCRYPTOID_RSA_OAEP_PADDING, &Result);
	hAlgo2 = CryptoGetAlgorithmById(RTSCRYPTOID_RSA_PKCS1_V15_SHA1, &Result);
}
#endif /* CMP_TEST_CRYPTO */

#ifdef CMP_TEST_CERTS
/* Test of CmpX509 ITF*/
static void CmpTestCerts(void)
{
	RTS_RESULT TestResult = ERR_OK;
	unsigned char cert[2048];
	do
	{
		RtsByteString temp;
		RtsByteString temp2;
		RTS_RESULT Result;
		RTS_HANDLE hResult = RTS_INVALID_HANDLE, hFile;
		RtsX509CertInfo info;
		RtsX509CertInfo info2;
		RtsOID oid;
		RTS_SYSTIMEDATE timeDate;
		RtsX509NameEntry entry[2];
		RtsOID exKeyUsage[2];
		RtsX509AltName altNames[2];
		RtsCryptoKey privateKey;
		RtsCryptoKey publicKey;
		RTS_HANDLE hCertStore;
		RTS_HANDLE hAlgo;
		RtsByteString signature;
		RtsByteString bsdata;
		char aData[] = "Hallo Welt das ist ein Signaturetest den ich mit der neuen X509 Schnittstelle durchfuehre!";
		char aSignature[1024];
		int i;
		RtsX509CertFilter filters[2];

		/* Open the certificate store */
		hCertStore = X509CertStoreOpen(COMPONENT_ID, &Result);

		/* Try to create a self signed certificate */
		X509CertInfoInit(&info, sizeof(info));
		info.subject.numOfEntries = 2;
		info.subject.entries = entry;
		RtsOIDCreate(RTS_OID_COMMON_NAME, &entry[0].id);
		entry[0].value = "AdrianTestCert";
		RtsOIDCreate(RTS_OID_RSA_EMAILADDR, &entry[1].id);
		entry[1].value = "a.scholl@codesys.com";


		CAL_SysTimeRtcHighResGet(&info.notBefore);
		memset(&timeDate, 0, sizeof(timeDate));
		CAL_SysTimeRtcConvertHighResToDate(&info.notBefore, &timeDate);
		timeDate.wYear++;
		CAL_SysTimeRtcConvertDateToHighRes(&timeDate, &info.notAfter);
		info.keyUsage = RTS_KEY_USAGE_DIGITAL_SIGNATURE | RTS_KEY_USAGE_DATA_ENCIPHERMENT;
		info.numOfExKeyUsages = 2;
		info.pExKeyUsages = exKeyUsage;
		memset(exKeyUsage, 0, sizeof(exKeyUsage));
		RtsOIDCreate("1.3.6.1.5.5.7.3.1", &info.pExKeyUsages[0]);
		RtsOIDCreate("1.3.6.1.5.5.7.3.2", &info.pExKeyUsages[1]);

		info.numOfAltNames = 2;
		info.pAltNames = altNames;
		memset(altNames, 0, sizeof(altNames));
		info.pAltNames[0].valueType = RTSX509ALTNAMETYPE_DNSNAME;
		info.pAltNames[0].value.pDnsName = "bachelor05";
		info.pAltNames[1].valueType = RTSX509ALTNAMETYPE_IPADDRESS;
		info.pAltNames[1].value.ipAddress.S_un.S_un_b.s_b1 = 192;
		info.pAltNames[1].value.ipAddress.S_un.S_un_b.s_b2 = 168;
		info.pAltNames[1].value.ipAddress.S_un.S_un_b.s_b3 = 101;
		info.pAltNames[1].value.ipAddress.S_un.S_un_b.s_b4 = 147;
		hResult = X509CertCreateSelfSigned(hCertStore, RTS_INVALID_HANDLE, &info, 2048, &Result);
		X509CertClose(hResult);

		/* Verify Certificate */
		memset(cert, 0, sizeof(cert));
		hFile = CAL_SysFileOpen("opcua.der", RTS_ACCESS_MODE_AM_READ, &Result);
		CAL_SysFileGetSize("opcua.der", &Result);
		temp.pByData = cert;
		temp.ui32Len = CAL_SysFileGetSize("opcua.der", &Result);
		temp.ui32MaxLen = sizeof(cert);

		CAL_SysFileRead(hFile, cert, sizeof(cert), &Result);
		CAL_SysFileClose(hFile);

		memset(&oid, 0, sizeof(oid));
		hResult = X509ParseCertificate(&temp, RTSCERTENCODING_ASN1, &Result);
		Result = X509CertVerify(hCertStore, hResult);

		filters[0].filterType = RTSX509CERTFILTERTYPE_TRUST_LEVEL;
		filters[0].filterContent.trustLevel = RTSCERTTRUSTLEVEL_OWN;
		filters[1].filterType = RTSX509CERTFILTERTYPE_SUBJECT;
		filters[1].filterContent.subject = &info.subject;
		hResult = X509CertStoreSearchGetFirst(hCertStore, filters, 2, &Result);

		/* Try do sign and verify some data with a public and private key */
		X509CertGetPublicKey(hResult, &publicKey);
		X509CertGetPrivateKey(hCertStore, hResult, &privateKey);

		hAlgo = CryptoGetAlgorithmById(RTSCRYPTOID_RSA_OAEP_SHA256, &Result);
		memset(&bsdata, 0, sizeof(bsdata));
		memset(&signature, 0, sizeof(signature));
		bsdata.pByData = (RTS_IEC_BYTE *)aData;
		bsdata.ui32Len = strlen(aData);

		signature.pByData = (RTS_IEC_BYTE *)aSignature;
		signature.ui32MaxLen = sizeof(aSignature);

		Result = CryptoSignatureGenerate(hAlgo, &bsdata, privateKey, &signature);
		Result = CryptoSignatureVerify(hAlgo, &bsdata, publicKey, &signature);

		X509CertKeyClose(&publicKey);
		X509CertKeyClose(&privateKey);

		while (hResult != RTS_INVALID_HANDLE)
		{
			RTS_HANDLE hTemp;
			char data[128];
			RtsByteString tmp;
			RTSCRYPTOID algo = 0;
			X509CertInfoInit(&info2, sizeof(info2));
			X509CertGetContent(hResult, &info2);
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 0, 0, "Found Cert: ");
			for (i = 0; i < (int)info2.subject.numOfEntries; i++)
			{

				memset(data, 0, 128);
				tmp.pByData = (RTS_IEC_BYTE *)data;
				tmp.ui32MaxLen = sizeof(data);
				tmp.ui32Len = 0;
				RtsOIDGetName(&info2.subject.entries[i].id, &tmp);
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 0, 0, "%s: %s", data, info2.subject.entries[i].value);
			}
			memset(data, 0, sizeof(data));
			tmp.pByData = (RTS_IEC_BYTE *)data;
			tmp.ui32MaxLen = sizeof(data);
			tmp.ui32Len = 0;
			X509Thumbprint2Text(hResult, sizeof(data), data);
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 0, 0, "Thumbprint: %s", data);
			X509CertInfoExit(&info2);
			hTemp = X509CertStoreSearchGetNext(hCertStore, hResult, filters, 2, &Result);

			X509CertClose(hResult);
			hResult = hTemp;
		}


		X509CertStoreClose(hCertStore);

	} while (0);

	if (TestResult == ERR_OK)
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_DEBUG, 0, 0, "X.509: Test successful!");
	else
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_DEBUG, 0, 0, "X.509: ### Test failed=%ld", TestResult);
}
#endif	/* CMP_TEST_CERTS */

