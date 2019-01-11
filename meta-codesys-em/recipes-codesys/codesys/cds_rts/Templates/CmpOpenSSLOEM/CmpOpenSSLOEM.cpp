/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpOpenSSLOEM.c"



/* TODO: REPLACE 0x0001 BY YOUR VENDORID */

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





RTS_HANDLE CDECL CCmpOpenSSLOEM::ITlsCreateContext(char* pszNamespace, RTS_RESULT* pResult)
{
	return TlsCreateContext(pszNamespace,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::ITlsCreateContext2(RTS_HANDLE hCert, RTS_UI32 ui32TlsMethod, char* szCipherList, RTS_I32 i32VerifyMode,  RTS_RESULT* pResult)
{
	return TlsCreateContext2(hCert,ui32TlsMethod,szCipherList,i32VerifyMode,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsFreeContext(RTS_HANDLE hTlsContext)
{
	return TlsFreeContext(hTlsContext);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::ITlsBufferOpen(RTS_HANDLE hContext, RtsByteString* pRxBuffer, RtsByteString* pTxBuffer, RTS_RESULT* pResult)
{
	return TlsBufferOpen(hContext,pRxBuffer,pTxBuffer,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsBufferDataReveived(RTS_HANDLE hTlsConn)
{
	return TlsBufferDataReveived(hTlsConn);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsBufferDataSent(RTS_HANDLE hTlsConn)
{
	return TlsBufferDataSent(hTlsConn);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::ITlsBufferDataToSendAvailable(RTS_HANDLE hTlsConn)
{
	return TlsBufferDataToSendAvailable(hTlsConn);
}

RTS_UI32 CDECL CCmpOpenSSLOEM::ITlsBufferNumOfWrittenBlocks(RTS_HANDLE hTlsConn)
{
	return TlsBufferNumOfWrittenBlocks(hTlsConn);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsAccept(RTS_HANDLE hTlsConn)
{
	return TlsAccept(hTlsConn);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsConnect(RTS_HANDLE hTlsConn)
{
	return TlsConnect(hTlsConn);
}

RTS_SSIZE CDECL CCmpOpenSSLOEM::ITlsRead(RTS_HANDLE hTlsConn, RTS_UI8* pbyBuffer, RTS_SSIZE ulBufferSize, RTS_RESULT* pResult)
{
	return TlsRead(hTlsConn,pbyBuffer,ulBufferSize,pResult);
}

RTS_SSIZE CDECL CCmpOpenSSLOEM::ITlsWrite(RTS_HANDLE hTlsConn, RTS_UI8* pbyData, RTS_SSIZE ulDataSize, RTS_RESULT* pResult)
{
	return TlsWrite(hTlsConn,pbyData,ulDataSize,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsShutdown(RTS_HANDLE hTlsConn)
{
	return TlsShutdown(hTlsConn);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ITlsClose(RTS_HANDLE hTlsConn)
{
	return TlsClose(hTlsConn);
}

void CDECL CCmpOpenSSLOEM::ITlsRandAdd(const RTS_UI8* pui8Buffer, RTS_I32 i32BufferSize, RTS_REAL64 r64Entroy)
{
	TlsRandAdd(pui8Buffer,i32BufferSize,r64Entroy);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::ITlsRandCheckStatus(void)
{
	return TlsRandCheckStatus();
}

















RTS_HANDLE CDECL CCmpOpenSSLOEM::ISysSock2Create(RTS_HANDLE hISysSocket, CLASSID ClassId, SysSock_Parameter *pParameter, RTS_RESULT *pResult)
{
	hCmpOpenSSLOEM = SysSock2Create(hISysSocket,ClassId,pParameter,pResult);
	RTS_HANDLE h = (RTS_HANDLE)QueryInterface((IBase *)(ISysSocket2 *)this, ITFID_ISysSocket2, NULL);
	Release();
	return h;
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Close(void)
{
	RTS_RESULT Result = SysSock2Close(hCmpOpenSSLOEM);
	DeleteInstance((IBase *)(ISysSocket2 *)this);
	return Result;
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2SetOption(RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 iOptionLen)
{
	return SysSock2SetOption(hCmpOpenSSLOEM,iLevel,iOption,pcOptionValue,iOptionLen);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2GetOption(RTS_I32 iLevel, RTS_I32 iOption, char *pcOptionValue, RTS_I32 *piOptionLen)
{
	return SysSock2GetOption(hCmpOpenSSLOEM,iLevel,iOption,pcOptionValue,piOptionLen);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Bind(SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize)
{
	return SysSock2Bind(hCmpOpenSSLOEM,pSockAddr,iSockAddrSize);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Listen(RTS_I32 iMaxConnections)
{
	return SysSock2Listen(hCmpOpenSSLOEM,iMaxConnections);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::ISysSock2Accept(RTS_HANDLE hISysSocket, CLASSID ClassId, RTS_HANDLE hSocket, SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize, RTS_RESULT *pResult)
{
	CPP_IMPLEMENTATION_SysSock2Accept
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Connect(SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize)
{
	return SysSock2Connect(hCmpOpenSSLOEM,pSockAddr,iSockAddrSize);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Select(RTS_I32 iWidth, SOCKET_FD_SET *fdRead, SOCKET_FD_SET *fdWrite, SOCKET_FD_SET *fdExcept, SOCKET_TIMEVAL *ptvTimeout, RTS_I32 *pnReady)
{
	return SysSock2Select(hCmpOpenSSLOEM,iWidth,fdRead,fdWrite,fdExcept,ptvTimeout,pnReady);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Shutdown(RTS_I32 iHow)
{
	return SysSock2Shutdown(hCmpOpenSSLOEM,iHow);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2Ioctl(RTS_I32 iCommand, RTS_I32 *piParameter)
{
	return SysSock2Ioctl(hCmpOpenSSLOEM,iCommand,piParameter);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::ISysSock2FdIsset(SOCKET_FD_SET *pfs)
{
	return SysSock2FdIsset(hCmpOpenSSLOEM,pfs);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2FdInit(SOCKET_FD_SET *pfs)
{
	return SysSock2FdInit(hCmpOpenSSLOEM,pfs);
}

RTS_SSIZE CDECL CCmpOpenSSLOEM::ISysSock2Recv(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult)
{
	return SysSock2Recv(hCmpOpenSSLOEM,pbyBuffer,iBufferSize,iFlags,pResult);
}

RTS_SSIZE CDECL CCmpOpenSSLOEM::ISysSock2Send(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, RTS_RESULT *pResult)
{
	return SysSock2Send(hCmpOpenSSLOEM,pbyBuffer,iBufferSize,iFlags,pResult);
}

RTS_SSIZE CDECL CCmpOpenSSLOEM::ISysSock2RecvFrom(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult)
{
	return SysSock2RecvFrom(hCmpOpenSSLOEM,pbyBuffer,iBufferSize,iFlags,pSockAddr,iSockAddrSize,pResult);
}

RTS_SSIZE CDECL CCmpOpenSSLOEM::ISysSock2SendTo(char *pbyBuffer, RTS_SSIZE iBufferSize, RTS_I32 iFlags, SOCKADDRESS *pSockAddr, RTS_I32 iSockAddrSize, RTS_RESULT *pResult)
{
	return SysSock2SendTo(hCmpOpenSSLOEM,pbyBuffer,iBufferSize,iFlags,pSockAddr,iSockAddrSize,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2GetPeerName(SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize)
{
	return SysSock2GetPeerName(hCmpOpenSSLOEM,pSockAddr,piSockAddrSize);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ISysSock2GetSockName(SOCKADDRESS *pSockAddr, RTS_I32 *piSockAddrSize)
{
	return SysSock2GetSockName(hCmpOpenSSLOEM,pSockAddr,piSockAddrSize);
}

CLASSID CDECL CCmpOpenSSLOEM::ISysSock2GetClassId(RTS_RESULT *pResult)
{
	return SysSock2GetClassId(hCmpOpenSSLOEM,pResult);
}























RTS_HANDLE CDECL CCmpOpenSSLOEM::ICryptoGetAlgorithmById(RTS_UI32 ui32CryptoID, RTS_RESULT* pResult)
{
	return CryptoGetAlgorithmById(ui32CryptoID,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::ICryptoGetFirstAlgorithm(RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult)
{
	return CryptoGetFirstAlgorithm(ui32CryptoType,pszName,i32MaxNameLen,pui32CryptoID,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::ICryptoGetNextAlgorithm(RTS_HANDLE hCrypto, RTS_UI32 ui32CryptoType, char *pszName, RTS_I32 i32MaxNameLen, RTS_UI32 *pui32CryptoID, RTS_RESULT *pResult)
{
	return CryptoGetNextAlgorithm(hCrypto,ui32CryptoType,pszName,i32MaxNameLen,pui32CryptoID,pResult);
}

RtsCryptoInfo* CDECL CCmpOpenSSLOEM::ICryptoGetAlgorithmInfo(RTS_HANDLE hCrypto, RTS_RESULT* pCryptoInfo)
{
	return CryptoGetAlgorithmInfo(hCrypto,pCryptoInfo);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoSymmetricEncrypt(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pCipherText)
{
	return CryptoSymmetricEncrypt(hAlgo,pPlainText,key,pInitVector,bEnablePadding,pCipherText);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoSymmetricDecrypt(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey key, RtsByteString* pInitVector, RTS_BOOL bEnablePadding, RtsByteString* pPlainText)
{
	return CryptoSymmetricDecrypt(hAlgo,pCipherText,key,pInitVector,bEnablePadding,pPlainText);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoAsymmetricEncrypt(RTS_HANDLE hAlgo, RtsByteString* pPlainText, RtsCryptoKey publicKey, RtsByteString* pCipherText)
{
	return CryptoAsymmetricEncrypt(hAlgo,pPlainText,publicKey,pCipherText);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoAsymmetricDecrypt(RTS_HANDLE hAlgo, RtsByteString* pCipherText, RtsCryptoKey privateKey, RtsByteString* pPlainText)
{
	return CryptoAsymmetricDecrypt(hAlgo,pCipherText,privateKey,pPlainText);
}

RTS_UI32 CDECL CCmpOpenSSLOEM::ICryptoGetAsymmetricKeyLength(RtsCryptoKey asymmetricKey, RTS_RESULT* pResult)
{
	return CryptoGetAsymmetricKeyLength(asymmetricKey,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoGenerateHash(RTS_HANDLE hAlgo, RtsByteString* pData, RtsByteString* pHash)
{
	return CryptoGenerateHash(hAlgo,pData,pHash);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoHMACSign(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature)
{
	return CryptoHMACSign(hAlgo,pData,key,pSignature);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoHMACVerify(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey key, RtsByteString* pSignature)
{
	return CryptoHMACVerify(hAlgo,pData,key,pSignature);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoSignatureGenerate(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey privateKey, RtsByteString* pSignature)
{
	return CryptoSignatureGenerate(hAlgo,pData,privateKey,pSignature);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoSignatureVerify(RTS_HANDLE hAlgo, RtsByteString* pData, RtsCryptoKey publicKey, RtsByteString* pSignature)
{
	return CryptoSignatureVerify(hAlgo,pData,publicKey,pSignature);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoGenerateRandomNumber(RTS_UI32 ui32NumOfRandomBytes, RtsByteString* pRandom)
{
	return CryptoGenerateRandomNumber(ui32NumOfRandomBytes,pRandom);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoKeyInit(RtsCryptoKey* pKey, RtsCryptoKeyStorage key, RTSCRYPTOKEYTYPE keyType)
{
	return CryptoKeyInit(pKey,key,keyType);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoKeyExit(RtsCryptoKey* pKey)
{
	return CryptoKeyExit(pKey);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoRtsByteStringInit(RtsByteString* pByteString)
{
	return CryptoRtsByteStringInit(pByteString);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoRtsByteStringInit2(RtsByteString* pByteString, RTS_UI32 ui32BufferSize, RTS_UI8* pBuffer)
{
	return CryptoRtsByteStringInit2(pByteString,ui32BufferSize,pBuffer);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::ICryptoRtsByteStringExit(RtsByteString* pByteString)
{
	return CryptoRtsByteStringExit(pByteString);
}



































RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreOpen(CMPID componentID, RTS_RESULT* pResult)
{
	return X509CertStoreOpen(componentID,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertStoreClose(RTS_HANDLE hCertStore)
{
	return X509CertStoreClose(hCertStore);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertVerify(RTS_HANDLE hCertStore, RTS_HANDLE hCert)
{
	return X509CertVerify(hCertStore,hCert);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreSearchGetFirst(RTS_HANDLE hCertStore, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult)
{
	return X509CertStoreSearchGetFirst(hCertStore,pFilters,ui32NumOfFilters,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreSearchGetNext(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsX509CertFilter *pFilters, RTS_UI32 ui32NumOfFilters, RTS_RESULT *pResult)
{
	return X509CertStoreSearchGetNext(hCertStore,hCert,pFilters,ui32NumOfFilters,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509ParseCertificate(RtsByteString* pCert, RTSCERTENCODING encoding, RTS_RESULT* pResult)
{
	return X509ParseCertificate(pCert,encoding,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertGetContent(RTS_HANDLE hCert, RtsX509CertInfo* pCertContent)
{
	return X509CertGetContent(hCert,pCertContent);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertGetBinary(RTS_HANDLE hCert, RTSCERTENCODING encoding, RtsByteString* pCert)
{
	return X509CertGetBinary(hCert,encoding,pCert);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertGetPublicKey(RTS_HANDLE hCert, RtsCryptoKey* pPublicKey)
{
	return X509CertGetPublicKey(hCert,pPublicKey);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertGetPrivateKey(RTS_HANDLE hCertStore, RTS_HANDLE hCert, RtsCryptoKey* pPrivateKey)
{
	return X509CertGetPrivateKey(hCertStore,hCert,pPrivateKey);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertGetThumbprint(RTS_HANDLE hCert,  RTSCRYPTOID* hashAlgorithm, RtsByteString* pThumbprint)
{
	return X509CertGetThumbprint(hCert,hashAlgorithm,pThumbprint);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::IX509CertIsDateValid(RTS_HANDLE hCert, RTS_RESULT *pResult)
{
	return X509CertIsDateValid(hCert,pResult);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::IX509CertIsSelfSigned(RTS_HANDLE hCert, RTS_RESULT *pResult)
{
	return X509CertIsSelfSigned(hCert,pResult);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::IX509CertHasExtendedKeyUsage(RTS_HANDLE hCert, RTS_UI32 numOfExKeyUsages, RtsOID *pExKeyUsages, RTS_RESULT *pResult)
{
	return X509CertHasExtendedKeyUsage(hCert,numOfExKeyUsages,pExKeyUsages,pResult);
}

RTS_BOOL CDECL CCmpOpenSSLOEM::IX509CertCompare(RTS_HANDLE hCert1, RTS_HANDLE hCert2)
{
	return X509CertCompare(hCert1,hCert2);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertKeyClose(RtsCryptoKey* pKey)
{
	return X509CertKeyClose(pKey);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertClose(RTS_HANDLE hCert)
{
	return X509CertClose(hCert);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertCmsVerify(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData)
{
	return X509CertCmsVerify(hCertStore,pCms,encoding,pInData,pOutData);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertCmsVerify2(RTS_HANDLE hCertStore, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pInData, RtsByteString* pOutData, RTS_HANDLE* phSignerCert)
{
	return X509CertCmsVerify2(hCertStore,pCms,encoding,pInData,pOutData,phSignerCert);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertCmsDecrypt(RTS_HANDLE hCertStore, RTS_HANDLE hRecipientCert, RtsByteString* pCms, RTSCERTENCODING encoding, RtsByteString* pOutData)
{
	return X509CertCmsDecrypt(hCertStore,hRecipientCert,pCms,encoding,pOutData);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IRtsOIDCreate(char* id, RtsOID* oid)
{
	return RtsOIDCreate(id,oid);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IRtsOIDGetID(RtsOID* oid, RtsByteString* pBuffer)
{
	return RtsOIDGetID(oid,pBuffer);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IRtsOIDGetName(RtsOID* oid, RtsByteString* pBuffer)
{
	return RtsOIDGetName(oid,pBuffer);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IRtsOIDClear(RtsOID* oid)
{
	return RtsOIDClear(oid);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertInfoInit(RtsX509CertInfo* pCertInfo, RTS_UI32 structSize)
{
	return X509CertInfoInit(pCertInfo,structSize);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertInfoExit(RtsX509CertInfo* pCertInfo)
{
	return X509CertInfoExit(pCertInfo);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreGetFirstBackend(RTS_HANDLE hCertStore, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult)
{
	return X509CertStoreGetFirstBackend(hCertStore,pInfo,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreGetNextBackend(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo, RTS_RESULT* pResult)
{
	return X509CertStoreGetNextBackend(hCertStore,hBackend,pInfo,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertStorGetBackendInfo(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsCertBackendInfo* pInfo)
{
	return X509CertStorGetBackendInfo(hCertStore,hBackend,pInfo);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertCreateSelfSigned(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTS_RESULT *pResult)
{
	return X509CertCreateSelfSigned(hCertStore,hBackend,pCertInfo,ui32KeySize,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertCreateSelfSignedAsync(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, void* pCallbackParam, PFX509ASYNCCALLBACK pfCallback)
{
	return X509CertCreateSelfSignedAsync(hCertStore,hBackend,pCertInfo,ui32KeySize,pCallbackParam,pfCallback);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertCreateCSR(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR)
{
	return X509CertCreateCSR(hCertStore,hBackend,pCertInfo,ui32KeySize,encoding,pCSR);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertCreateCSRAsync(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RtsX509CertInfo* pCertInfo, CMPID cmpID, RTS_UI32 ui32KeySize, RTSCERTENCODING encoding, RtsByteString* pCSR, void* pCallbackParam, PFX509ASYNCCALLBACK pfCallback)
{
	return X509CertCreateCSRAsync(hCertStore,hBackend,pCertInfo,cmpID,ui32KeySize,encoding,pCSR,pCallbackParam,pfCallback);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertStoreAddCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTSCERTTRUSTLEVEL trustLevel)
{
	return X509CertStoreAddCert(hCertStore,hBackend,hCert,trustLevel);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertStoreRemoveCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_BOOL bRemovePrivateKey)
{
	return X509CertStoreRemoveCert(hCertStore,hBackend,hCert,bRemovePrivateKey);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreGetFirstCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTSCERTTRUSTLEVEL trustLevel, RTS_RESULT* pResult)
{
	return X509CertStoreGetFirstCert(hCertStore,hBackend,trustLevel,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreGetNextCert(RTS_HANDLE hCertStore, RTS_HANDLE hBackend, RTS_HANDLE hCert, RTS_RESULT* pResult)
{
	return X509CertStoreGetNextCert(hCertStore,hBackend,hCert,pResult);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreRegister(RTS_HANDLE hCertStore, CMPID cmpID, RtsX509CertInfo* pCertInfo, RTS_RESULT* pResult)
{
	return X509CertStoreRegister(hCertStore,cmpID,pCertInfo,pResult);
}

RTS_RESULT CDECL CCmpOpenSSLOEM::IX509CertStoreUnregister(RTS_HANDLE hCertStore, RTS_HANDLE hRegisteredComponent)
{
	return X509CertStoreUnregister(hCertStore,hRegisteredComponent);
}

RTS_HANDLE CDECL CCmpOpenSSLOEM::IX509CertStoreGetRegisteredCert(RTS_HANDLE hCertStore, RTS_HANDLE hUseCase, RTS_RESULT* pResult)
{
	return X509CertStoreGetRegisteredCert(hCertStore,hUseCase,pResult);
}






