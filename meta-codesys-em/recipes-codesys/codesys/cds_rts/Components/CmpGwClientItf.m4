/**
 * <interfacename>CmpGwClient</interfacename>
 * <description> 
 *	Interface of the gateway client as an entry point in the plc network.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpGwClient')

REF_ITF(`CmpCommunicationLibItf.m4')

#ifdef __cplusplus
	extern "C" {
#endif 


/**
* <category>Settings</category>
* <type>Int</type>
* <description>
*	Setting to modify the default value of the Gateway inactivity timeout in ms.
*	This default value is only used, if the Gateway connect is started by BeginConnectToGateway() instead of BeginConnectToGateway2().
*	If no piece of data (also no keepalive) is received or sent wihtin this time, the GwClient closes the connection to the Gateway.
* </description>
*/
#define GWCLIENTKEY_INT_INACTIVITY_TIMEOUT					"InactivityTimeoutMs"
#ifndef GWCLIENTKEY_INT_INACTIVITY_TIMEOUT_DEFAULT
	#define GWCLIENTKEY_INT_INACTIVITY_TIMEOUT_DEFAULT		30000
#endif


enum 
{
	PT_CHAR = 17,  /* char */
	PT_BYTE = 18,	/* unsigned char */
	PT_INT16 = 19,
	PT_UINT16 = 20,
	PT_INT32 = 21,
	PT_UINT32 = 22,
	PT_INT64 = 23,
	PT_UINT64 = 24,  
	PT_WCHAR = 25,	 /* RTS_WCHAR (2-byte UNICODE char) */
	PT_FLOAT = 26,   /* "float" (32 bit floating point value) */
	PT_DOUBLE = 27,  /* "double" (64 bit floating point value) */
	PT_BOOLEAN = 28, /* an int which is interpreted as a boolean value (0 or != 0) */
	PT_STRING = 29,
	PT_WSTRING = 30
};

typedef struct
{
	ADDRESSCOMPONENT *pAddress;
	unsigned short nLength;
}NODEADDRESS_OLD;

#define MAX_CHANNEL_NAME 19

typedef struct 
{
	unsigned long dwCommBuffer;
	RTS_WCHAR wszName[MAX_CHANNEL_NAME + 1];
}CHANNELQOS;


#define MAX_PARAM_NAME 19

/* This struct is used to describe a parameter */
typedef struct
{
	RTS_WCHAR pwszName[MAX_PARAM_NAME+1];
	unsigned long dwParamId;
	unsigned long dwType; /* PT_xxx */
	void *pDefaultValue; /* points to the default value of this parameter. May be null */
}PARAMETERDEFINITION;

/* This struct is used to pass a parameter.
   pValue is a pointer to the value of the parameter
   ( e.g. a pointer to an int (PT_INT) or a pointer to a wchar-string (PT_WSTRING)).
*/
typedef struct
{
	unsigned long dwParamId;
	unsigned long type;
	void * pValue; /* Pointer to the value */
}PARAMETER;

typedef struct
{
	int nNumParams;
	PARAMETERDEFINITION *pParam; /* An array of nNumParams parameter definitions*/
}PARAMDEFLIST;

typedef struct
{
	int nNumParams;
	PARAMETER *pParam; /* An array of nNumParams parameters */
}PARAMLIST;

/* Describe a communication driver */
typedef struct
{
	RTS_UI32 dwStructLength;	/* Must be set to the size of this struct */
	RTS_HANDLE hDriver;   /* Identifies the driver during application execution. May change in different instances of an application */
	RTS_GUID guid;              /* Use to identify a wellknown communication driver */
	RTS_WCHAR *pwszName;
	PARAMDEFLIST params;          /* E.g. a tcp/ip driver uses 2 parameters: ip-address and port */
	RTS_I32 nMinPingInterval;  /* The number of seconds to wait, between pinging a gateway using this driver. Set to 0 to disable polling at all.*/
}COMMDRVINFO;

/* 
  Application provided function to be called when an asynchronous operation
  completes. pAsyncRes may not point to the same object as provided in the
  BeginXXX function, but is an exact copy of this object 
*/
struct tagASYNCRESULT;
typedef void (STDCALL *PFASYNCCALLBACK)(struct tagASYNCRESULT *pAsyncRes);

/* Use this struct to call one of the BeginXXX functions asynchronously. 
   Passing a NULL pointer for this struct will result in a synchronous call.
   When using this struct the application has to provide the pUser and pfCallback
   field, the others are set by the asynchronous function. An application may set
   both of those - pUser and pfCallback - to NULL. In the case of pfCallback 
   no callback will be triggered when the operation completes. pUser is not 
   interpreted by the asynchronous function anyways, it simply serves as an 
   identifier of the call for the application.
*/
typedef struct tagASYNCRESULT
{
	void *pUser; 
		/* Application supplied value to identify the asynchronous call.*/
	PFASYNCCALLBACK pfCallback;
		/* Application supplied function to be called when the asynchronous call completes.*/
	RTS_HANDLE hEvent;
		/* This event will be set when the asynchronous call completes. 
		   Is set by the BeginXXX function
		*/
	unsigned long ulRequestId;
		/* Internally used. To be ignored by the application */
}ASYNCRESULT;

/* -- Functions exported by communication drivers to the Gateway-Client -- */

/* Send data on a connection. If not all of the data could be sent, the number of bytes 
   sent is returned in pdwSent and the function has to be called again later with the remaining
   bytes. 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
   dwConnHandle   IN  identifies the connection.
   data           IN  The data to be sent
   pdwSent        OUT The number of bytes the could actually be sent.
*/
typedef int (CDECL *PFCOMMDRVSEND)(RTS_HANDLE hConnHandle, PROTOCOL_DATA_UNIT data, unsigned long *pdwSent);

/* Receive data from an existent connection. 
   NOTE: This function must not block and it must not call any functions of the 
         gateway, since this may lead to deadlocks.
   dwConnHandle IN      identifies the connection
   pData        OUT  The data to be received.
   dwReceive    IN   Number of bytes to receive.
*/
typedef int (CDECL *PFCOMMDRVRECEIVE)(RTS_HANDLE hConnHandle, PROTOCOL_DATA_UNIT *pData, unsigned long dwReceive);

/* Open a connection as described by pParams
   pParams        IN  
   pdwConnHandle  OUT    If successfull pdwConnHandle is set to the handle for the connection.
   pAsyncRes      IN/OUT Async result.
 */
typedef int (CDECL *PFCOMMDRVBEGINCONNECT)( PARAMLIST *pParams, RTS_HANDLE *phConnHandle, ASYNCRESULT *pAsyncRes);

/* Wait until the BeginConnect call identified by pAsyncRes has completed. 
   pAsyncRes     IN   Identifies the matching BeginConnect call.
   pdwConnHandle OUT  If the call was successfull, then this parameter is set to the 
                      handle for the newly created connection.
*/
typedef int (CDECL *PFCOMMDRVENDCONNECT) ( ASYNCRESULT *pAsyncRes, RTS_HANDLE *phConnHandle);

/* Close a connection 
   NOTE: This function must not block and it must not call any functions of the 
         gateway client, since this may lead to deadlocks.
*/
typedef int (CDECL *PFCOMMDRVCLOSE)(RTS_HANDLE hConnHandle);

typedef struct 
{
	PFCOMMDRVBEGINCONNECT   pfBeginConnect;
	PFCOMMDRVENDCONNECT     pfEndConnect;
	PFCOMMDRVSEND           pfSend;
	PFCOMMDRVRECEIVE        pfReceive;
	PFCOMMDRVCLOSE          pfClose;
}COMMDRVITF;

/* ByteOrders of the answering node used only for GWCLIENTNODEINFO.byIntelByteOrder. */
#define GWCLIENT_NI_BYTEORDER_MOTOROLA		0
#define GWCLIENT_NI_BYTEORDER_INTEL			1
#define GWCLIENT_NI_BYTEORDER_UNKNOWN		255

typedef struct
{
	RTS_UI32	dwRtsMaxChannels;		/* Number of communciation channels */
	RTS_UI32	dwTargetType;			/* Target type, e. g. SYSTARGET_TYPE_PROGRAMMABLE */
	RTS_UI32	dwTargetId;				/* Target id, consists of SYSTARGET_VENDOR_ID and SYSTARGET_DEVICE_ID */
	RTS_UI32	dwTargetVersion;		/* (OEM) version */
	RTS_UI32	dwFlags;				/* See name service package flags NSPF_ - unused flags have to be set to 0 */
	RTS_UI8		byIntelByteOrder;		/* Byte order: 0="Motorola", 1="Intel", 255=Unknown, see defines GWCLIENT_NI_BYTEORDER_xxx */
	RTS_UI8		byByte;					/* Reserved, always 0 */
	RTS_UI16	wRtsBlkDrvType;			/* Type of block driver instance on runtime on which this node info was sent, e.g. RTS_BLK_DRV_TYPE_UDP */
	RTS_UI16	wGwBlkDrvType;			/* Type of block driver instance on Gateway on which this node info was received, e.g. RTS_BLK_DRV_TYPE_UDP */
	RTS_UI16	wGwRtsNsVersion;		/* Name service version used between runtime system and Gateway */
	RTS_UI32	dwGwClientGwVersion;	/* Name service version used between GwClient and Gateway */
}GWCLIENTNODEINFO;

/* -- Functions exported by the Gateway-Client to the communication drivers -- */

/**
 * <description>
 *  Register a commdriver with the gateway client. 
 * </description>
 * <param name="pItf" type="IN">The interface functions of the comm driver.</param>
 * <param name="pDrvInfo" type="IN">
 *  Information about the driver. The hDriver field is unused in this call.
 * </param>
 * <param name="pulDriverHandle" type="OUT">
 *  Will be set with the handle assigned to the communication-driver.
 *  The driver must use this handle in all callbacks (eg. GWClientSendReady).
 * </param>
*/
DEF_API(`int',`CDECL',`GWClientRegisterCommDrv',`(COMMDRVITF *pItf, COMMDRVINFO *pDrvInfo, RTS_HANDLE *phDriverHandle)')

enum
{
	COMMDRV_ACTION_SEND = 0,
	COMMDRV_ACTION_RECEIVE = 1
};

/**
 * <description>
 *  May be called by a commdriver if a connection is ready to send/receive.
 *  This function shall not signal a condition more then once without the 
 *  gateway client reacting to that signal.
 *  Eg. if the commdriver signals that a connection is ready to send it shall not
 *  signal this situation again before the gateway client actually called "send".
 *  The gwclient must not rely on this function to be called but may use 
 *  it to increase the performance of the connection.
 * </description>
 * <param name="dwDriverHandle" type="IN">
 *  The driver handle returned by GWClientRegisterCommDrv.
 * </param>
 * <param name="dwConnHandle" type="IN">
 *  The handle to the connection.
 * </param>
 * <param name="nAction" type="IN">
 *  The action that is ready on this connection - eg. COMMDRV_ACTION_SEND, COMMDRV_ACTION_RECEIVE
 * </param>
 */
DEF_API(`int',`CDECL',`GWClientConnectionReady',`(RTS_HANDLE hDriverHandle, RTS_HANDLE hConnHandle, int nAction)')

typedef void (STDCALL *PFENUMCOMMDRVCALLBACK)(RTS_HANDLE hDriver, RTS_GUID *guid, RTS_WCHAR *pwszName, PARAMDEFLIST *pParams, char bLast, int nMinPingInterval);
typedef void (STDCALL *PFENUMCOMMDRVCALLBACK2)(unsigned long dwUser, RTS_HANDLE hDriver, RTS_GUID *guid, RTS_WCHAR *pwszName, PARAMDEFLIST *pParams, char bLast, int nMinPingInterval);

/* This callback is called by the nameservice functions (e.g. ResolveAllNodes) for each 
   answering node.
   dwUser       IN  userdefined value simply passed to this function
   addrNode     IN  The address of the answering node
   addrParent   IN  The address of its parent node (length zero if node is toplevel)
   nMaxChannels IN  Maximum number of channels that the runtime system is able to deal with.
   dwTargetId   IN  Target identifier
   wszNodeName  IN  The name of the node.
   wszTargetName IN The description of the target
*/
typedef void (STDCALL *PFNODEINFOCALLBACK)( unsigned long dwUser, NODEADDRESS_OLD addrNode, NODEADDRESS_OLD addrParent, int nMaxChannels, unsigned long dwTargetId, RTS_WCHAR *wszNodeName, RTS_WCHAR *wszTargetName);

/* This callback is called by the nameservice functions (e.g. ResolveAllNodes) for each 
   answering node.
   dwUser       IN  userdefined value simply passed to this function
   addrNode     IN  The address of the answering node
   addrParent   IN  The address of its parent node (length zero if node is toplevel)
   nMaxChannels IN  Maximum number of channels that the runtime system is able to deal with.
   dwTargetType IN  Target type
   dwTargetId	IN  Target ident number
   dwTargetVersion IN  Target version
   wszNodeName  IN  The name of the node.
   wszDeviceName IN The name of the device
   wszVendorName IN The name of the vendor
*/
typedef void (STDCALL *PFNODEINFOCALLBACK2)( unsigned long dwUser, NODEADDRESS_OLD addrNode, NODEADDRESS_OLD addrParent, int nMaxChannels, unsigned long dwTargetType, unsigned long dwTargetId, unsigned long dwTargetVersion, RTS_WCHAR *wszNodeName, RTS_WCHAR *wszDeviceName, RTS_WCHAR *wszVendorName);

/* This callback is called by the nameservice functions (e.g. ResolveAllNodes) for each
answering node.
dwUser				IN  Userdefined value simply passed to this function
addrNode			IN  The address of the answering node
addrParent			IN  The address of its parent node (length zero if node is toplevel)
GWCLIENTNODEINFO	IN  Detailed node information 
wszNodeName			IN  Node name
wszDeviceName		IN  Device name
wszVendorName;		IN  Vendor name, may be an empty string
pszSerialNumber		IN  Serial number, may be an empty string
pbyOemData;			IN  OEM data; may be NULL, if dwOemDataLength==0
dwOemDataLength		IN  Length of OEM specific data
*/
typedef void (STDCALL *PFNODEINFOCALLBACK3)(RTS_UINTPTR dwUser, NODEADDRESS_OLD addrNode, NODEADDRESS_OLD addrParent, GWCLIENTNODEINFO *pGwClientNodeInfo, RTS_WCHAR *wszNodeName, RTS_WCHAR *wszDeviceName, RTS_WCHAR *wszVendorName, RTS_CSTRING *pszSerialNumber, RTS_UI8 *pbyOemData, RTS_UI32 dwOemDataLength);


DEF_API(`RTS_RESULT',`CDECL',`GWClientGetInterfaceVersion',`(RTS_UI16 *pwMajor, RTS_UI16 *pwMinor)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEnumCommDrivers',`(PFENUMCOMMDRVCALLBACK pfCallback)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEnumCommDrivers2',`(PFENUMCOMMDRVCALLBACK2 pfCallback, unsigned long dwUser)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginConnectToGateway',`(RTS_HANDLE hDriver, int nNumParams, PARAMETER *pParams, RTS_HANDLE *phGateway, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginConnectToGateway2',`(RTS_HANDLE hDriver, RTS_I32 nNumParams, PARAMETER *pParams, RTS_UI32 ui32GwInactivityTimeout, RTS_HANDLE *phGateway, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndConnectToGateway',`(ASYNCRESULT *pAsyncRes, RTS_HANDLE *phGateway)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientDisconnectFromGateway',`(RTS_HANDLE hGateway)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginIncrementalResolveAllNodes',`(RTS_HANDLE hGateway, unsigned long dwUser, PFNODEINFOCALLBACK pfCallback, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginIncrementalResolveAllNodes2',`(RTS_HANDLE hGateway, unsigned long dwUser, PFNODEINFOCALLBACK2 pfCallback2, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginIncrementalResolveAllNodes3',`(RTS_HANDLE hGateway, RTS_UI32 dwTimeout, RTS_UINTPTR dwUser, PFNODEINFOCALLBACK3 pfCallback3, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientAdjustIncrementalResolveAllNodesTimeout',`(RTS_UI32 dwRemainingTimeout, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndIncrementalResolveAllNodes',`(ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginIncrementalResolveName',`(const RTS_WCHAR *pwszNodeName, RTS_HANDLE hGateway, unsigned long dwUser, PFNODEINFOCALLBACK pfCallback, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginIncrementalResolveName3',`(const RTS_WCHAR *pwszNodeName, RTS_HANDLE hGateway, RTS_UI32 dwTimeout, RTS_BOOL bFinishWithFirstNode, RTS_UINTPTR dwUser, PFNODEINFOCALLBACK3 pfCallback3, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientAdjustIncrementalResolveNameTimeout',`(RTS_UI32 dwRemainingTimeout, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndIncrementalResolveName',`(ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginResolveBlockDriverAddress',`(RTS_UI8 byBlkDrvType, RTS_UI8 byBlkDrvFlags, RTS_UI8 byAddrBitLength, RTS_UI8 *pbyAddress, RTS_HANDLE hGateway, unsigned long dwUser, PFNODEINFOCALLBACK2 pfCallback, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginResolveBlockDriverAddress3',`(RTS_UI8 byBlkDrvType, RTS_UI8 byBlkDrvFlags, RTS_UI8 byAddrBitLength, RTS_UI8 *pbyAddress, RTS_HANDLE hGateway, RTS_UI32 dwTimeout, RTS_UINTPTR dwUser, PFNODEINFOCALLBACK3 pfCallback3, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientAdjustResolveBlockDriverAddressTimeout',`(RTS_UI32 dwRemainingTimeout, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndResolveBlockDriverAddress',`(ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginResolveAddress',`(RTS_UI8 byAddrComponentLength, RTS_UI8 *pbyAddress, RTS_HANDLE hGateway, unsigned long dwUser, PFNODEINFOCALLBACK2 pfCallback, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginResolveAddress3',`(RTS_UI8 byAddrComponentLength, RTS_UI8 *pbyAddress, RTS_HANDLE hGateway, RTS_UI32 dwTimeout, RTS_UINTPTR dwUser, PFNODEINFOCALLBACK3 pfCallback3, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientAdjustResolveAddressTimeout',`(RTS_UI32 dwRemainingTimeout, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndResolveAddress',`(ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginSendRequest',`(RTS_HANDLE hGateway, RTS_HANDLE hChannel, PROTOCOL_DATA_UNIT pduReq, PROTOCOL_DATA_UNIT *ppduResp, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndSendRequest',`(ASYNCRESULT *pAsyncRes, PROTOCOL_DATA_UNIT *ppduResp)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginOpenChannel',`(RTS_HANDLE hGateway, NODEADDRESS_OLD addrTo, CHANNELQOS qosChannel, RTS_HANDLE *phChannel, unsigned long *pdwCommBufferSize, RTS_UI8 *pbBigEndianTarget, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginOpenChannel2',`(RTS_HANDLE hGateway, PEERADDRESS addrTo, CHANNELQOS qosChannel, RTS_HANDLE *phChannel, unsigned long *pdwCommBufferSize, RTS_UI8 *pbBigEndianTarget, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndOpenChannel',`(ASYNCRESULT *pAsyncRes, RTS_HANDLE *phChannel, unsigned long *pdwCommBufferSize, RTS_UI8 *pbBigEndianTarget)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientBeginCloseChannel',`(RTS_HANDLE hGateway, RTS_HANDLE hChannel, ASYNCRESULT *pAsyncRes)')
DEF_API(`RTS_RESULT',`CDECL',`GWClientEndCloseChannel',`(ASYNCRESULT *pAsyncRes)')

#ifdef __cplusplus
	}
#endif 
