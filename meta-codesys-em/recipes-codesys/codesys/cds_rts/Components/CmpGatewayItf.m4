/**
 * <interfacename>CmpGateway</interfacename>
 * <description>
 *	Interface of the gateway
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpGateway')

REF_ITF(`CmpRouterItf.m4')

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
DEF_ITF_API(`int',`CDECL',`GWRegisterCommDrv',`(COMMDRVINFO *pInfo, unsigned long *pdwDriverId)')

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
DEF_ITF_API(`int',`CDECL',`GWConnectionReady',`(unsigned long dwDriverHandle, unsigned long dwConnHandle, int nAction)')

/* Called when a client connects. If anything else then ERR_OK is returned
   the communication driver should close the connection immediatly.
   dwDriverId   IN  The value assigned during GWRegisterCommDrv.
   dwConnHandle IN  A handle identifing the new connection.
*/
DEF_ITF_API(`int',`CDECL',`GWClientConnect',`(unsigned long dwDriverId, unsigned long dwConnHandle)')

/* Called when a client connection has been disconnected.
   dwDriverId   IN  The value assigned during GWRegisterCommDrv.
   dwConnHandle IN  A handle identifing the disconnected connection. 
*/
DEF_ITF_API(`int',`CDECL',`GWClientDisconnect',`(unsigned long dwDriverId, unsigned long dwConnHandle)')

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
DEF_ITF_API(`int',`CDECL',`GWRegisterAuthModule',`( AUTHMODINFO *pfAuthModInfo, GWAUTHFUNCS *pfGWFuncs )')

#ifdef __cplusplus
}
#endif
