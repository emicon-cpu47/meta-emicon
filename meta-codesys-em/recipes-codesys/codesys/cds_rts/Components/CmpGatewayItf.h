 /**
 * <interfacename>CmpGateway</interfacename>
 * <description>
 *	Interface of the gateway
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPGATEWAYITF_H_
#define _CMPGATEWAYITF_H_

#include "CmpStd.h"

 

 




#include "CmpRouterItf.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
* <category>Settings</category>
* <type>Int</type>
* <description>
*	Setting to modify the client inactivity timeout in ms. 
*	If no piece of data (also no keepalive) is received or successfully sent wihtin this time, the Gateway closes the connection to the client.
* </description>
*/
#define GATEWAYKEY_INT_INACTIVITY_TIMEOUT					"InactivityTimeoutMs"
#ifndef GATEWAYKEY_INT_INACTIVITY_TIMEOUT_DEFAULT
	#define GATEWAYKEY_INT_INACTIVITY_TIMEOUT_DEFAULT		60000
#endif


/* -- Functions exported by communication drivers to the Gateway -- */

/* Send data on a connection. If not all of the data could be sent, the number of bytes 
   sent is returned in pdwSent and the function has to be called again later with the remaining
   bytes. 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
   dwConnHandle   IN  identifies the connection.
   data           IN  The data to be sent
   pdwSent        OUT The number of bytes the could actually be sent.

   RETURNS: 
	ERR_NOTCONNECTED if the provided connection handle is not connected.
*/
typedef int (CDECL *PFCOMMDRVSEND)(RTS_UI32 dwConnHandle, PROTOCOL_DATA_UNIT data, RTS_UI32 *pdwSent);

/* Receive data from an existent connection. 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
   dwConnHandle IN    identifies the connection
   pData        INOUT 
       .pData  (IN) Provides a buffer for the received data.
	   .nCount (IN) Size of the buffer. (OUT) Number of bytes actually received.
*/
typedef int (CDECL *PFCOMMDRVRECEIVE)(RTS_UI32 dwConnHandle, PROTOCOL_DATA_UNIT *pData);

/* Close a connection 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
*/
typedef int (CDECL *PFCOMMDRVCLOSE)(RTS_UI32 dwConnHandle);

/* -- Functions exported to communication drivers -- */

typedef struct
{
	PFCOMMDRVSEND    pfSend;
	PFCOMMDRVRECEIVE pfReceive;
	PFCOMMDRVCLOSE   pfClose;
} COMMDRVINFO;

/* Called by a gateway communication driver to register 
   with the gateway. 
   pInfo       IN  Contains function pointers to the comm driver api.
   pdwDriverId OUT Set to a unique value for the comm driver. The driver must provide
                   the assigned value in all other calls to the gateway functions 
				   in order to identify itself.
*/
int CDECL GWRegisterCommDrv(COMMDRVINFO *pInfo, unsigned long *pdwDriverId);
typedef int (CDECL * PFGWREGISTERCOMMDRV) (COMMDRVINFO *pInfo, unsigned long *pdwDriverId);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWREGISTERCOMMDRV_NOTIMPLEMENTED)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWRegisterCommDrv(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_GWRegisterCommDrv  FALSE
	#define EXP_GWRegisterCommDrv  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  CAL_CMGETAPI( "GWRegisterCommDrv" ) 
	#define CAL_GWRegisterCommDrv  GWRegisterCommDrv
	#define CHK_GWRegisterCommDrv  TRUE
	#define EXP_GWRegisterCommDrv  CAL_CMEXPAPI( "GWRegisterCommDrv" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  CAL_CMGETAPI( "GWRegisterCommDrv" ) 
	#define CAL_GWRegisterCommDrv  GWRegisterCommDrv
	#define CHK_GWRegisterCommDrv  TRUE
	#define EXP_GWRegisterCommDrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWRegisterCommDrv", (RTS_UINTPTR)GWRegisterCommDrv, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWRegisterCommDrv
	#define EXT_CmpGatewayGWRegisterCommDrv
	#define GET_CmpGatewayGWRegisterCommDrv  ERR_OK
	#define CAL_CmpGatewayGWRegisterCommDrv pICmpGateway->IGWRegisterCommDrv
	#define CHK_CmpGatewayGWRegisterCommDrv (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWRegisterCommDrv  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWRegisterCommDrv
	#define EXT_GWRegisterCommDrv
	#define GET_GWRegisterCommDrv(fl)  CAL_CMGETAPI( "GWRegisterCommDrv" ) 
	#define CAL_GWRegisterCommDrv pICmpGateway->IGWRegisterCommDrv
	#define CHK_GWRegisterCommDrv (pICmpGateway != NULL)
	#define EXP_GWRegisterCommDrv  CAL_CMEXPAPI( "GWRegisterCommDrv" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWRegisterCommDrv  PFGWREGISTERCOMMDRV pfGWRegisterCommDrv;
	#define EXT_GWRegisterCommDrv  extern PFGWREGISTERCOMMDRV pfGWRegisterCommDrv;
	#define GET_GWRegisterCommDrv(fl)  s_pfCMGetAPI2( "GWRegisterCommDrv", (RTS_VOID_FCTPTR *)&pfGWRegisterCommDrv, (fl), 0, 0)
	#define CAL_GWRegisterCommDrv  pfGWRegisterCommDrv
	#define CHK_GWRegisterCommDrv  (pfGWRegisterCommDrv != NULL)
	#define EXP_GWRegisterCommDrv  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWRegisterCommDrv", (RTS_UINTPTR)GWRegisterCommDrv, 0, 0) 
#endif




enum
{
	COMMDRV_ACTION_SEND = 0,
	COMMDRV_ACTION_RECEIVE = 1
};

/**
 * <description>
 *  May be called by a commdriver if a connection is ready to send/receive.
 *  This function shall not signal a condition more then once without the 
 *  gateway reacting to that signal.
 *  Eg. if the commdriver signals that a connection is ready to send it shall not
 *  signal this situation again before the gateway actually called "send".
 *  The gwclient must not rely on this function to be called but may use 
 *  it to increase the performance of the connection.
 * </description>
 * <param name="dwDriverHandle" type="IN">
 *  The driver handle returned by GWRegisterCommDrv.
 * </param>
 * <param name="dwConnHandle" type="IN">
 *  The handle to the connection.
 * </param>
 * <param name="nAction" type="IN">
 *  The action that is ready on this connection - eg. COMMDRV_ACTION_SEND, COMMDRV_ACTION_RECEIVE
 * </param>
 */
int CDECL GWConnectionReady(unsigned long dwDriverHandle, unsigned long dwConnHandle, int nAction);
typedef int (CDECL * PFGWCONNECTIONREADY) (unsigned long dwDriverHandle, unsigned long dwConnHandle, int nAction);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWCONNECTIONREADY_NOTIMPLEMENTED)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWConnectionReady(p0,p1,p2)  (int)ERR_NOTIMPLEMENTED
	#define CHK_GWConnectionReady  FALSE
	#define EXP_GWConnectionReady  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  CAL_CMGETAPI( "GWConnectionReady" ) 
	#define CAL_GWConnectionReady  GWConnectionReady
	#define CHK_GWConnectionReady  TRUE
	#define EXP_GWConnectionReady  CAL_CMEXPAPI( "GWConnectionReady" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  CAL_CMGETAPI( "GWConnectionReady" ) 
	#define CAL_GWConnectionReady  GWConnectionReady
	#define CHK_GWConnectionReady  TRUE
	#define EXP_GWConnectionReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWConnectionReady", (RTS_UINTPTR)GWConnectionReady, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWConnectionReady
	#define EXT_CmpGatewayGWConnectionReady
	#define GET_CmpGatewayGWConnectionReady  ERR_OK
	#define CAL_CmpGatewayGWConnectionReady pICmpGateway->IGWConnectionReady
	#define CHK_CmpGatewayGWConnectionReady (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWConnectionReady  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWConnectionReady
	#define EXT_GWConnectionReady
	#define GET_GWConnectionReady(fl)  CAL_CMGETAPI( "GWConnectionReady" ) 
	#define CAL_GWConnectionReady pICmpGateway->IGWConnectionReady
	#define CHK_GWConnectionReady (pICmpGateway != NULL)
	#define EXP_GWConnectionReady  CAL_CMEXPAPI( "GWConnectionReady" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWConnectionReady  PFGWCONNECTIONREADY pfGWConnectionReady;
	#define EXT_GWConnectionReady  extern PFGWCONNECTIONREADY pfGWConnectionReady;
	#define GET_GWConnectionReady(fl)  s_pfCMGetAPI2( "GWConnectionReady", (RTS_VOID_FCTPTR *)&pfGWConnectionReady, (fl), 0, 0)
	#define CAL_GWConnectionReady  pfGWConnectionReady
	#define CHK_GWConnectionReady  (pfGWConnectionReady != NULL)
	#define EXP_GWConnectionReady  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWConnectionReady", (RTS_UINTPTR)GWConnectionReady, 0, 0) 
#endif




/* Called when a client connects. If anything else then ERR_OK is returned
   the communication driver should close the connection immediatly.
   dwDriverId   IN  The value assigned during GWRegisterCommDrv.
   dwConnHandle IN  A handle identifing the new connection.
*/
int CDECL GWClientConnect(unsigned long dwDriverId, unsigned long dwConnHandle);
typedef int (CDECL * PFGWCLIENTCONNECT) (unsigned long dwDriverId, unsigned long dwConnHandle);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWCLIENTCONNECT_NOTIMPLEMENTED)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWClientConnect(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_GWClientConnect  FALSE
	#define EXP_GWClientConnect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  CAL_CMGETAPI( "GWClientConnect" ) 
	#define CAL_GWClientConnect  GWClientConnect
	#define CHK_GWClientConnect  TRUE
	#define EXP_GWClientConnect  CAL_CMEXPAPI( "GWClientConnect" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  CAL_CMGETAPI( "GWClientConnect" ) 
	#define CAL_GWClientConnect  GWClientConnect
	#define CHK_GWClientConnect  TRUE
	#define EXP_GWClientConnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientConnect", (RTS_UINTPTR)GWClientConnect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWClientConnect
	#define EXT_CmpGatewayGWClientConnect
	#define GET_CmpGatewayGWClientConnect  ERR_OK
	#define CAL_CmpGatewayGWClientConnect pICmpGateway->IGWClientConnect
	#define CHK_CmpGatewayGWClientConnect (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWClientConnect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWClientConnect
	#define EXT_GWClientConnect
	#define GET_GWClientConnect(fl)  CAL_CMGETAPI( "GWClientConnect" ) 
	#define CAL_GWClientConnect pICmpGateway->IGWClientConnect
	#define CHK_GWClientConnect (pICmpGateway != NULL)
	#define EXP_GWClientConnect  CAL_CMEXPAPI( "GWClientConnect" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWClientConnect  PFGWCLIENTCONNECT pfGWClientConnect;
	#define EXT_GWClientConnect  extern PFGWCLIENTCONNECT pfGWClientConnect;
	#define GET_GWClientConnect(fl)  s_pfCMGetAPI2( "GWClientConnect", (RTS_VOID_FCTPTR *)&pfGWClientConnect, (fl), 0, 0)
	#define CAL_GWClientConnect  pfGWClientConnect
	#define CHK_GWClientConnect  (pfGWClientConnect != NULL)
	#define EXP_GWClientConnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientConnect", (RTS_UINTPTR)GWClientConnect, 0, 0) 
#endif




/* Called when a client connection has been disconnected.
   dwDriverId   IN  The value assigned during GWRegisterCommDrv.
   dwConnHandle IN  A handle identifing the disconnected connection. 
*/
int CDECL GWClientDisconnect(unsigned long dwDriverId, unsigned long dwConnHandle);
typedef int (CDECL * PFGWCLIENTDISCONNECT) (unsigned long dwDriverId, unsigned long dwConnHandle);
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWCLIENTDISCONNECT_NOTIMPLEMENTED)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWClientDisconnect(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_GWClientDisconnect  FALSE
	#define EXP_GWClientDisconnect  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  CAL_CMGETAPI( "GWClientDisconnect" ) 
	#define CAL_GWClientDisconnect  GWClientDisconnect
	#define CHK_GWClientDisconnect  TRUE
	#define EXP_GWClientDisconnect  CAL_CMEXPAPI( "GWClientDisconnect" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  CAL_CMGETAPI( "GWClientDisconnect" ) 
	#define CAL_GWClientDisconnect  GWClientDisconnect
	#define CHK_GWClientDisconnect  TRUE
	#define EXP_GWClientDisconnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientDisconnect", (RTS_UINTPTR)GWClientDisconnect, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWClientDisconnect
	#define EXT_CmpGatewayGWClientDisconnect
	#define GET_CmpGatewayGWClientDisconnect  ERR_OK
	#define CAL_CmpGatewayGWClientDisconnect pICmpGateway->IGWClientDisconnect
	#define CHK_CmpGatewayGWClientDisconnect (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWClientDisconnect  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWClientDisconnect
	#define EXT_GWClientDisconnect
	#define GET_GWClientDisconnect(fl)  CAL_CMGETAPI( "GWClientDisconnect" ) 
	#define CAL_GWClientDisconnect pICmpGateway->IGWClientDisconnect
	#define CHK_GWClientDisconnect (pICmpGateway != NULL)
	#define EXP_GWClientDisconnect  CAL_CMEXPAPI( "GWClientDisconnect" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWClientDisconnect  PFGWCLIENTDISCONNECT pfGWClientDisconnect;
	#define EXT_GWClientDisconnect  extern PFGWCLIENTDISCONNECT pfGWClientDisconnect;
	#define GET_GWClientDisconnect(fl)  s_pfCMGetAPI2( "GWClientDisconnect", (RTS_VOID_FCTPTR *)&pfGWClientDisconnect, (fl), 0, 0)
	#define CAL_GWClientDisconnect  pfGWClientDisconnect
	#define CHK_GWClientDisconnect  (pfGWClientDisconnect != NULL)
	#define EXP_GWClientDisconnect  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWClientDisconnect", (RTS_UINTPTR)GWClientDisconnect, 0, 0) 
#endif




/* -- Functions exported by authentication modules to the Gateway -- */

/* This function is called after a STARTAUTH message has been received from a connecting 
   client. Its intention is to make sure the authorisation module has sufficient resources
   to handle authorisation of the new client. If not, it should return ERR_NO_BUFFER.
   The auth-module must handle authorisation messages from that client until it calls the
   GWAuthFinished method.
   dwClientId  IN  This is the "handle" used for all communication between the gateway and
                   the auth-module to identify the client.
   Returns 
       ERR_OK if the auth-module is ready to handle the new client.
	   ERR_NO_BUFER otherwise
*/
int CDECL AuthModBeginAuth( unsigned long dwClientId);
typedef int (CDECL *PFAUTHMODBEGINAUTH)( unsigned long dwClientId);

/* Called by the gateway for every message that arrives from a client that
   is still in authorisation state. 
   dwClientId   IN  Same as in AuthModBeginAuth
   wCommand     IN  Auth-module defined command-id
   dwRequestId  IN  Request-Id as sent by the client. Should be provided in answers.
   data         IN  Auth-module specific protocol data. 
*/
int CDECL AuthModHandleMessage( unsigned long dwClientId, unsigned short wCommandId, unsigned long dwRequestId, PROTOCOL_DATA_UNIT data);
typedef int (CDECL *PFAUTHMODHANDLEMESSAGE)( unsigned long dwClientId, unsigned short wCommandId, unsigned long dwRequestId, PROTOCOL_DATA_UNIT data);


/* -- Functions exported to authentication modules -- */

typedef int (CDECL *PFGWSENDREPLY)(unsigned long dwClientId, unsigned long dwRequestId, PROTOCOL_DATA_UNIT data);
typedef int (CDECL *PFGWAUTHFINISHED) (unsigned long dwClientId, int nResult);

typedef struct
{
	RTS_GUID guid;
		/* This guid identifies the authorisation module. */
	PFAUTHMODBEGINAUTH pfBeginAuth;
		/* Function to be called when a client wants to start authorisation. */
	PFAUTHMODHANDLEMESSAGE pfHandleMessage;
		/* Called for each authorisation message from a client. */
}AUTHMODINFO;

typedef struct 
{
	PFGWSENDREPLY pfSendReply;
		/* Authmodule uses this function to send a reply back to a client */
	PFGWAUTHFINISHED pfGWAuthFinished;
		/* Auth-module calls this function when the authorisation succeeded or definitly failed. */
}GWAUTHFUNCS;

/* This function is called on initialization by an autorisation module to register itself
   with the gateway. 
   pfAuthModInfo  IN  Function pointer etc. of the authentication module
   pfGWFuncs      OUT Functions of the gateway exported to the auth-module    
*/
int CDECL GWRegisterAuthModule( AUTHMODINFO *pfAuthModInfo, GWAUTHFUNCS *pfGWFuncs );
typedef int (CDECL * PFGWREGISTERAUTHMODULE) ( AUTHMODINFO *pfAuthModInfo, GWAUTHFUNCS *pfGWFuncs );
#if defined(CMPGATEWAY_NOTIMPLEMENTED) || defined(GWREGISTERAUTHMODULE_NOTIMPLEMENTED)
	#define USE_GWRegisterAuthModule
	#define EXT_GWRegisterAuthModule
	#define GET_GWRegisterAuthModule(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWRegisterAuthModule(p0,p1)  (int)ERR_NOTIMPLEMENTED
	#define CHK_GWRegisterAuthModule  FALSE
	#define EXP_GWRegisterAuthModule  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWRegisterAuthModule
	#define EXT_GWRegisterAuthModule
	#define GET_GWRegisterAuthModule(fl)  CAL_CMGETAPI( "GWRegisterAuthModule" ) 
	#define CAL_GWRegisterAuthModule  GWRegisterAuthModule
	#define CHK_GWRegisterAuthModule  TRUE
	#define EXP_GWRegisterAuthModule  CAL_CMEXPAPI( "GWRegisterAuthModule" ) 
#elif defined(MIXED_LINK) && !defined(CMPGATEWAY_EXTERNAL)
	#define USE_GWRegisterAuthModule
	#define EXT_GWRegisterAuthModule
	#define GET_GWRegisterAuthModule(fl)  CAL_CMGETAPI( "GWRegisterAuthModule" ) 
	#define CAL_GWRegisterAuthModule  GWRegisterAuthModule
	#define CHK_GWRegisterAuthModule  TRUE
	#define EXP_GWRegisterAuthModule  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWRegisterAuthModule", (RTS_UINTPTR)GWRegisterAuthModule, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGatewayGWRegisterAuthModule
	#define EXT_CmpGatewayGWRegisterAuthModule
	#define GET_CmpGatewayGWRegisterAuthModule  ERR_OK
	#define CAL_CmpGatewayGWRegisterAuthModule pICmpGateway->IGWRegisterAuthModule
	#define CHK_CmpGatewayGWRegisterAuthModule (pICmpGateway != NULL)
	#define EXP_CmpGatewayGWRegisterAuthModule  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWRegisterAuthModule
	#define EXT_GWRegisterAuthModule
	#define GET_GWRegisterAuthModule(fl)  CAL_CMGETAPI( "GWRegisterAuthModule" ) 
	#define CAL_GWRegisterAuthModule pICmpGateway->IGWRegisterAuthModule
	#define CHK_GWRegisterAuthModule (pICmpGateway != NULL)
	#define EXP_GWRegisterAuthModule  CAL_CMEXPAPI( "GWRegisterAuthModule" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWRegisterAuthModule  PFGWREGISTERAUTHMODULE pfGWRegisterAuthModule;
	#define EXT_GWRegisterAuthModule  extern PFGWREGISTERAUTHMODULE pfGWRegisterAuthModule;
	#define GET_GWRegisterAuthModule(fl)  s_pfCMGetAPI2( "GWRegisterAuthModule", (RTS_VOID_FCTPTR *)&pfGWRegisterAuthModule, (fl), 0, 0)
	#define CAL_GWRegisterAuthModule  pfGWRegisterAuthModule
	#define CHK_GWRegisterAuthModule  (pfGWRegisterAuthModule != NULL)
	#define EXP_GWRegisterAuthModule  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWRegisterAuthModule", (RTS_UINTPTR)GWRegisterAuthModule, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFGWREGISTERCOMMDRV IGWRegisterCommDrv;
 	PFGWCONNECTIONREADY IGWConnectionReady;
 	PFGWCLIENTCONNECT IGWClientConnect;
 	PFGWCLIENTDISCONNECT IGWClientDisconnect;
 	PFGWREGISTERAUTHMODULE IGWRegisterAuthModule;
 } ICmpGateway_C;

#ifdef CPLUSPLUS
class ICmpGateway : public IBase
{
	public:
		virtual int CDECL IGWRegisterCommDrv(COMMDRVINFO *pInfo, unsigned long *pdwDriverId) =0;
		virtual int CDECL IGWConnectionReady(unsigned long dwDriverHandle, unsigned long dwConnHandle, int nAction) =0;
		virtual int CDECL IGWClientConnect(unsigned long dwDriverId, unsigned long dwConnHandle) =0;
		virtual int CDECL IGWClientDisconnect(unsigned long dwDriverId, unsigned long dwConnHandle) =0;
		virtual int CDECL IGWRegisterAuthModule(AUTHMODINFO *pfAuthModInfo, GWAUTHFUNCS *pfGWFuncs ) =0;
};
	#ifndef ITF_CmpGateway
		#define ITF_CmpGateway static ICmpGateway *pICmpGateway = NULL;
	#endif
	#define EXTITF_CmpGateway
#else	/*CPLUSPLUS*/
	typedef ICmpGateway_C		ICmpGateway;
	#ifndef ITF_CmpGateway
		#define ITF_CmpGateway
	#endif
	#define EXTITF_CmpGateway
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPGATEWAYITF_H_*/
