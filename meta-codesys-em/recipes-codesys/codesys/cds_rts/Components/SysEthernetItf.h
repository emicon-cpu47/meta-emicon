 /**
 * <interfacename>SysEthernet</interfacename>
 * <description> 
 *	<p>The SysEthernet interface contains low level routines for a direct access to an ethernet controller.
 *	This interface is typically used by an EtherCAT driver.</p>
 *	<p>All other ethernet communciation components use higher level routines (see SysSocket interface).</p>
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _SYSETHERNETITF_H_
#define _SYSETHERNETITF_H_

#include "CmpStd.h"

 

 




/**
 * <category>Static defines</category>
 * <description>Maximum number of supported adapters</description>
 */
#define MAX_NUM_ADAPTERS 5

/**
 * <category>Static defines</category>
 * <description>Maximum mac address length</description>
 */
#define MAX_MAC_ADDR_LENGTH 8

/**
 * <category>Static defines</category>
 * <description>Maximum packet size</description>
 */
#define MAX_PACKET_SIZE 1514

/**
 * <category>Static defines</category>
 * <description>Maximum queue size</description>
 */
#define MAX_QUEUE_SIZE 15000

/**
 * <category>Static defines</category>
 * <description></description>
 */
#define DEFAULT_ADAPTER_NAMELIST 1000

/**
 * <category>Static defines</category>
 * <description>Ethercat protocol type</description>
 */
#define PROTO_ECAT 0x88A4

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>filter for incoming packets by protocol type. Default is Ethercat</description>
 */
#define SYSETHERNETKEY_INT_LINUX_PROTOCOLFILTER			"Linux.ProtocolFilter"
#define SYSETHERNETKEY_INT_LINUX_PROTOCOLFILTER_DEFAULT	PROTO_ECAT

/**
 * <category>Event parameter</category>
 * <element name="pFrame" type="IN">Pointer to one ethernet frame</element>
 */
typedef struct
{
	unsigned char* pFrame;
} EVTPARAM_SysEthernet;
#define EVTPARAMID_SysEthernet		0x0001
#define EVTVERSION_SysEthernet		0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when ethernet packet has arrived</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthPacketArrived					MAKE_EVENTID(EVTCLASS_INFO, 1)

/**
 * <category>Events</category>
 * <description>Event is sent when ethernet packet was sent</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthPacketSent						MAKE_EVENTID(EVTCLASS_INFO, 2)

/**
 * <category>Events</category>
 * <description>Event is created by the platformspecific adaptation of SysEthernet, in case there are parameters, that are designed to be changed by the application.
 * This way it is possible for the application to check if there are such possibilities and to get some paramters by calling "EventPost"</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthGetParameterValue						MAKE_EVENTID(EVTCLASS_INFO, 3)

/**
 * <category>Events</category>
 * <description>Event is created by the platformspecific adaptation of SysEthernet, in case there are parameters, that are designed to be changed by the application.
 * This way it is possible for the application to check if there are such possibilities and to set some paramters by calling "EventPost"</description>
 * <param name="pEventParam" type="IN">EVTPARAM_SysEthernet</param>
 */
#define EVT_EthSetParameterValue						MAKE_EVENTID(EVTCLASS_INFO, 4)

/**
 * <category>Event parameter</category>
 * <element name="ulLength" type="IN">Length of the parameter data.</element>
 * <element name="ulID" type="IN">A 32 bit value that identifies the parameter.</element>
 * <element name="pData" type="IN">A pointer to the value data of the parameter.</element>
 */
typedef struct
{
	unsigned long ulID;
	int iMasterNum;
	unsigned long ulLength;
	void* pData;
} EVTPARAM_SysEthernetSetGetParameter;
#define EVTPARAM_SysEthernetSetGetParameterID_NoPollingInGetEthframe	0x0001
#define EVTPARAM_SysEthernetSetGetParameterID_PollingOnlyNoInterrupts	0x0002
#define EVTPARAMID_SysEthernetParameter		0x0002


/**
 * <category>Online services</category>
 */

#define SRV_ETC_GETSOCKADAPTERINFO			0x76
#define SRV_ETC_GETADAPTERINFO				0x77

/**
 * <category>Online service tags</category>
 */
#define TAG_ETC_MASTERLIST					0x81
#define TAG_ETC_MASTERNAME					0x02
#define TAG_ETC_MASTERDESC					0x03
#define TAG_ETC_MASTERMAC					0x04

#define TAG_ETC_SOCKADAPTER					0x11
#define TAG_ETC_SOCKADAPTER_NEXT_INDEX		0x12

/**
 * <category>Online services</category>
 * <Description>
 *  Service to retrieve the adapter info on SysSocket level. Should be polled until the content of TAG_SERVICE_RESULT is 
 *  different from ERR_ENTRIES_REMAINING to get all adapters. 
 * </Description>
 * <service name="SRV_ETC_GETSOCKADAPTERINFO">
 *	<Request>
 *		<tag name="TAG_ETC_SOCKADAPTER_NEXT_INDEX" required="optional">[RTS_UI32]: Index of first adapter, which should be read. Default is 0, if tag is omitted.</tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_ETC_SOCKADAPTER" required="optional">[SOCK_ADAPTER_INFORMATION]: Adapter information for one network adapter. 
 *			For each adapter one tag of this type is added. Layout of IEC structure SOCK_ADAPTER_INFORMATION is used.
 *			Is not returned, if no adapter is available.</tag>
 *		<tag name="TAG_ETC_SOCKADAPTER_NEXT_INDEX" required="optional">[RTS_UI32]: Index of next adapter, which should be requested by next service
 *			Only returned, if not all adapter informations fits into the communication buffer.</tag>
 *		<tag name="TAG_SERVICE_RESULT" required="mandatory">[RTS_UI16]: Result code of online service: 
 *				ERR_OK (all adapters have been read), 
 *				ERR_NOTIMPLEMENTED (SysSocket does not provide the functionality to read the adapter information),
 *				ERR_NOT_SUPPORTED (SysSockGetFirstAdapterInfo or SysSockGetFirstAdapterInfo are not available),
 *				ERR_FAILED (no adapter information available, e. g. no adapter present), 
 *				ERR_ENTRIES_REMAINING (not all adapter informations fits into the communication buffer).</tag>
 *	</Response>
 * </service>
 */
 

typedef struct
{
	RTS_UI32 MacAddressLen;					/* Length of the link layer address */
	unsigned char MacAddress[MAX_MAC_ADDR_LENGTH];	/* Link layer address */
}MacAdr;

typedef struct
{
	unsigned char dest_mac[6];
	unsigned char source_mac[6];
	unsigned short eth_type;
	unsigned char head_length;
	unsigned char service;
	unsigned char firsttel[1500];
}Ethernetframe;


typedef struct
{
	RTS_I32 iMasterNum;
	MacAdr MacAddress;
	RTS_I32 nReturnVal;
}OpenEthernetInterface;

typedef struct
{
	RTS_I32 iMasterNum;
	RTS_I32 nReturnVal;
}CloseEthernetInterface;


typedef struct
{
	RTS_I32 iMasterNum;
	Ethernetframe *pFrame;
	RTS_I32 nSize;
	RTS_I32 nReturnVal;
}SendEthernetInterface;

typedef struct
{
	RTS_I32 iMasterNum;
	unsigned char **ppFrame;
	RTS_I32* pnSize;
	RTS_I32 nReturnVal;
}GetEthernetInterface;

typedef struct
{
	unsigned char **ppFrame;
	RTS_I32* pnSize;
	RTS_I32 nReturnVal;
}GetIPEthernetInterface;

typedef struct
{
	Ethernetframe *pFrame;
	RTS_I32 nSize;
	RTS_I32 nReturnVal;
}SendIPEthernetInterface;

typedef struct
{
	RTS_I32* piAdapterCnt;
	RTS_I32 nReturnVal;
}GetNumberOfEthernetInterface;

typedef struct
{
	int iAdapterNum;
	char *pszName;
	char *pszDescription;
	int iBuffersize;
	int iMacLength;
	char* MacAddress;
	RTS_I32 nReturnVal;
}GetAdapterInfoEthernetInterface;

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysEthernetOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysEthernetOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>Open a network adapter</description>
 * <param name="poei" type="IN">pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT openethernet(OpenEthernetInterface* poei);
typedef void (CDECL * PFOPENETHERNET) (OpenEthernetInterface* poei);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(OPENETHERNET_NOTIMPLEMENTED)
	#define USE_openethernet
	#define EXT_openethernet
	#define GET_openethernet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_openethernet(p0)  
	#define CHK_openethernet  FALSE
	#define EXP_openethernet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_openethernet
	#define EXT_openethernet
	#define GET_openethernet(fl)  CAL_CMGETAPI( "openethernet" ) 
	#define CAL_openethernet  openethernet
	#define CHK_openethernet  TRUE
	#define EXP_openethernet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"openethernet", (RTS_UINTPTR)openethernet, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_openethernet
	#define EXT_openethernet
	#define GET_openethernet(fl)  CAL_CMGETAPI( "openethernet" ) 
	#define CAL_openethernet  openethernet
	#define CHK_openethernet  TRUE
	#define EXP_openethernet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"openethernet", (RTS_UINTPTR)openethernet, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetopenethernet
	#define EXT_SysEthernetopenethernet
	#define GET_SysEthernetopenethernet  ERR_OK
	#define CAL_SysEthernetopenethernet pISysEthernet->Iopenethernet
	#define CHK_SysEthernetopenethernet (pISysEthernet != NULL)
	#define EXP_SysEthernetopenethernet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_openethernet
	#define EXT_openethernet
	#define GET_openethernet(fl)  CAL_CMGETAPI( "openethernet" ) 
	#define CAL_openethernet pISysEthernet->Iopenethernet
	#define CHK_openethernet (pISysEthernet != NULL)
	#define EXP_openethernet  CAL_CMEXPAPI( "openethernet" ) 
#else /* DYNAMIC_LINK */
	#define USE_openethernet  PFOPENETHERNET pfopenethernet;
	#define EXT_openethernet  extern PFOPENETHERNET pfopenethernet;
	#define GET_openethernet(fl)  s_pfCMGetAPI2( "openethernet", (RTS_VOID_FCTPTR *)&pfopenethernet, (fl), 0, 0)
	#define CAL_openethernet  pfopenethernet
	#define CHK_openethernet  (pfopenethernet != NULL)
	#define EXP_openethernet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"openethernet", (RTS_UINTPTR)openethernet, 1, 0) 
#endif




/**
 * <description>Send etherpacket</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT sendethframe(SendEthernetInterface* psfi);
typedef void (CDECL * PFSENDETHFRAME) (SendEthernetInterface* psfi);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(SENDETHFRAME_NOTIMPLEMENTED)
	#define USE_sendethframe
	#define EXT_sendethframe
	#define GET_sendethframe(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sendethframe(p0)  
	#define CHK_sendethframe  FALSE
	#define EXP_sendethframe  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sendethframe
	#define EXT_sendethframe
	#define GET_sendethframe(fl)  CAL_CMGETAPI( "sendethframe" ) 
	#define CAL_sendethframe  sendethframe
	#define CHK_sendethframe  TRUE
	#define EXP_sendethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendethframe", (RTS_UINTPTR)sendethframe, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_sendethframe
	#define EXT_sendethframe
	#define GET_sendethframe(fl)  CAL_CMGETAPI( "sendethframe" ) 
	#define CAL_sendethframe  sendethframe
	#define CHK_sendethframe  TRUE
	#define EXP_sendethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendethframe", (RTS_UINTPTR)sendethframe, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetsendethframe
	#define EXT_SysEthernetsendethframe
	#define GET_SysEthernetsendethframe  ERR_OK
	#define CAL_SysEthernetsendethframe pISysEthernet->Isendethframe
	#define CHK_SysEthernetsendethframe (pISysEthernet != NULL)
	#define EXP_SysEthernetsendethframe  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_sendethframe
	#define EXT_sendethframe
	#define GET_sendethframe(fl)  CAL_CMGETAPI( "sendethframe" ) 
	#define CAL_sendethframe pISysEthernet->Isendethframe
	#define CHK_sendethframe (pISysEthernet != NULL)
	#define EXP_sendethframe  CAL_CMEXPAPI( "sendethframe" ) 
#else /* DYNAMIC_LINK */
	#define USE_sendethframe  PFSENDETHFRAME pfsendethframe;
	#define EXT_sendethframe  extern PFSENDETHFRAME pfsendethframe;
	#define GET_sendethframe(fl)  s_pfCMGetAPI2( "sendethframe", (RTS_VOID_FCTPTR *)&pfsendethframe, (fl), 0, 0)
	#define CAL_sendethframe  pfsendethframe
	#define CHK_sendethframe  (pfsendethframe != NULL)
	#define EXP_sendethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendethframe", (RTS_UINTPTR)sendethframe, 1, 0) 
#endif




/**
 * <description>Get ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getethframe(GetEthernetInterface* pgei);
typedef void (CDECL * PFGETETHFRAME) (GetEthernetInterface* pgei);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(GETETHFRAME_NOTIMPLEMENTED)
	#define USE_getethframe
	#define EXT_getethframe
	#define GET_getethframe(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getethframe(p0)  
	#define CHK_getethframe  FALSE
	#define EXP_getethframe  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getethframe
	#define EXT_getethframe
	#define GET_getethframe(fl)  CAL_CMGETAPI( "getethframe" ) 
	#define CAL_getethframe  getethframe
	#define CHK_getethframe  TRUE
	#define EXP_getethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframe", (RTS_UINTPTR)getethframe, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_getethframe
	#define EXT_getethframe
	#define GET_getethframe(fl)  CAL_CMGETAPI( "getethframe" ) 
	#define CAL_getethframe  getethframe
	#define CHK_getethframe  TRUE
	#define EXP_getethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframe", (RTS_UINTPTR)getethframe, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetgetethframe
	#define EXT_SysEthernetgetethframe
	#define GET_SysEthernetgetethframe  ERR_OK
	#define CAL_SysEthernetgetethframe pISysEthernet->Igetethframe
	#define CHK_SysEthernetgetethframe (pISysEthernet != NULL)
	#define EXP_SysEthernetgetethframe  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_getethframe
	#define EXT_getethframe
	#define GET_getethframe(fl)  CAL_CMGETAPI( "getethframe" ) 
	#define CAL_getethframe pISysEthernet->Igetethframe
	#define CHK_getethframe (pISysEthernet != NULL)
	#define EXP_getethframe  CAL_CMEXPAPI( "getethframe" ) 
#else /* DYNAMIC_LINK */
	#define USE_getethframe  PFGETETHFRAME pfgetethframe;
	#define EXT_getethframe  extern PFGETETHFRAME pfgetethframe;
	#define GET_getethframe(fl)  s_pfCMGetAPI2( "getethframe", (RTS_VOID_FCTPTR *)&pfgetethframe, (fl), 0, 0)
	#define CAL_getethframe  pfgetethframe
	#define CHK_getethframe  (pfgetethframe != NULL)
	#define EXP_getethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getethframe", (RTS_UINTPTR)getethframe, 1, 0) 
#endif




/**
 * <description>Close network adapter</description>
 * <param name="pcei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT closeethernet(CloseEthernetInterface* pcei);
typedef void (CDECL * PFCLOSEETHERNET) (CloseEthernetInterface* pcei);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(CLOSEETHERNET_NOTIMPLEMENTED)
	#define USE_closeethernet
	#define EXT_closeethernet
	#define GET_closeethernet(fl)  ERR_NOTIMPLEMENTED
	#define CAL_closeethernet(p0)  
	#define CHK_closeethernet  FALSE
	#define EXP_closeethernet  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_closeethernet
	#define EXT_closeethernet
	#define GET_closeethernet(fl)  CAL_CMGETAPI( "closeethernet" ) 
	#define CAL_closeethernet  closeethernet
	#define CHK_closeethernet  TRUE
	#define EXP_closeethernet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"closeethernet", (RTS_UINTPTR)closeethernet, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_closeethernet
	#define EXT_closeethernet
	#define GET_closeethernet(fl)  CAL_CMGETAPI( "closeethernet" ) 
	#define CAL_closeethernet  closeethernet
	#define CHK_closeethernet  TRUE
	#define EXP_closeethernet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"closeethernet", (RTS_UINTPTR)closeethernet, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetcloseethernet
	#define EXT_SysEthernetcloseethernet
	#define GET_SysEthernetcloseethernet  ERR_OK
	#define CAL_SysEthernetcloseethernet pISysEthernet->Icloseethernet
	#define CHK_SysEthernetcloseethernet (pISysEthernet != NULL)
	#define EXP_SysEthernetcloseethernet  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_closeethernet
	#define EXT_closeethernet
	#define GET_closeethernet(fl)  CAL_CMGETAPI( "closeethernet" ) 
	#define CAL_closeethernet pISysEthernet->Icloseethernet
	#define CHK_closeethernet (pISysEthernet != NULL)
	#define EXP_closeethernet  CAL_CMEXPAPI( "closeethernet" ) 
#else /* DYNAMIC_LINK */
	#define USE_closeethernet  PFCLOSEETHERNET pfcloseethernet;
	#define EXT_closeethernet  extern PFCLOSEETHERNET pfcloseethernet;
	#define GET_closeethernet(fl)  s_pfCMGetAPI2( "closeethernet", (RTS_VOID_FCTPTR *)&pfcloseethernet, (fl), 0, 0)
	#define CAL_closeethernet  pfcloseethernet
	#define CHK_closeethernet  (pfcloseethernet != NULL)
	#define EXP_closeethernet  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"closeethernet", (RTS_UINTPTR)closeethernet, 1, 0) 
#endif




/**
 * <description>Get number of network adapters</description>
 * <param name="pnoei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getnumberofadapters(GetNumberOfEthernetInterface* pnoei);
typedef void (CDECL * PFGETNUMBEROFADAPTERS) (GetNumberOfEthernetInterface* pnoei);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(GETNUMBEROFADAPTERS_NOTIMPLEMENTED)
	#define USE_getnumberofadapters
	#define EXT_getnumberofadapters
	#define GET_getnumberofadapters(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getnumberofadapters(p0) 
	#define CHK_getnumberofadapters  FALSE
	#define EXP_getnumberofadapters  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getnumberofadapters
	#define EXT_getnumberofadapters
	#define GET_getnumberofadapters(fl)  CAL_CMGETAPI( "getnumberofadapters" ) 
	#define CAL_getnumberofadapters  getnumberofadapters
	#define CHK_getnumberofadapters  TRUE
	#define EXP_getnumberofadapters  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getnumberofadapters", (RTS_UINTPTR)getnumberofadapters, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_getnumberofadapters
	#define EXT_getnumberofadapters
	#define GET_getnumberofadapters(fl)  CAL_CMGETAPI( "getnumberofadapters" ) 
	#define CAL_getnumberofadapters  getnumberofadapters
	#define CHK_getnumberofadapters  TRUE
	#define EXP_getnumberofadapters  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getnumberofadapters", (RTS_UINTPTR)getnumberofadapters, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetgetnumberofadapters
	#define EXT_SysEthernetgetnumberofadapters
	#define GET_SysEthernetgetnumberofadapters  ERR_OK
	#define CAL_SysEthernetgetnumberofadapters  getnumberofadapters
	#define CHK_SysEthernetgetnumberofadapters  TRUE
	#define EXP_SysEthernetgetnumberofadapters  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getnumberofadapters", (RTS_UINTPTR)getnumberofadapters, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_getnumberofadapters
	#define EXT_getnumberofadapters
	#define GET_getnumberofadapters(fl)  CAL_CMGETAPI( "getnumberofadapters" ) 
	#define CAL_getnumberofadapters  getnumberofadapters
	#define CHK_getnumberofadapters  TRUE
	#define EXP_getnumberofadapters  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getnumberofadapters", (RTS_UINTPTR)getnumberofadapters, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_getnumberofadapters  PFGETNUMBEROFADAPTERS pfgetnumberofadapters;
	#define EXT_getnumberofadapters  extern PFGETNUMBEROFADAPTERS pfgetnumberofadapters;
	#define GET_getnumberofadapters(fl)  s_pfCMGetAPI2( "getnumberofadapters", (RTS_VOID_FCTPTR *)&pfgetnumberofadapters, (fl), 0, 0)
	#define CAL_getnumberofadapters  pfgetnumberofadapters
	#define CHK_getnumberofadapters  (pfgetnumberofadapters != NULL)
	#define EXP_getnumberofadapters   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getnumberofadapters", (RTS_UINTPTR)getnumberofadapters, 1, 0) 
#endif


/**
 *  <description>Get info about specified network adapters</description>
 * <param name="paiei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getadapterinfo(GetAdapterInfoEthernetInterface* paiei);
typedef void (CDECL * PFGETADAPTERINFO) (GetAdapterInfoEthernetInterface* paiei);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(GETADAPTERINFO_NOTIMPLEMENTED)
	#define USE_getadapterinfo
	#define EXT_getadapterinfo
	#define GET_getadapterinfo(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getadapterinfo(p0) 
	#define CHK_getadapterinfo  FALSE
	#define EXP_getadapterinfo  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getadapterinfo
	#define EXT_getadapterinfo
	#define GET_getadapterinfo(fl)  CAL_CMGETAPI( "getadapterinfo" ) 
	#define CAL_getadapterinfo  getadapterinfo
	#define CHK_getadapterinfo  TRUE
	#define EXP_getadapterinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterinfo", (RTS_UINTPTR)getadapterinfo, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_getadapterinfo
	#define EXT_getadapterinfo
	#define GET_getadapterinfo(fl)  CAL_CMGETAPI( "getadapterinfo" ) 
	#define CAL_getadapterinfo  getadapterinfo
	#define CHK_getadapterinfo  TRUE
	#define EXP_getadapterinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterinfo", (RTS_UINTPTR)getadapterinfo, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetgetadapterinfo
	#define EXT_SysEthernetgetadapterinfo
	#define GET_SysEthernetgetadapterinfo  ERR_OK
	#define CAL_SysEthernetgetadapterinfo  getadapterinfo
	#define CHK_SysEthernetgetadapterinfo  TRUE
	#define EXP_SysEthernetgetadapterinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterinfo", (RTS_UINTPTR)getadapterinfo, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_getadapterinfo
	#define EXT_getadapterinfo
	#define GET_getadapterinfo(fl)  CAL_CMGETAPI( "getadapterinfo" ) 
	#define CAL_getadapterinfo  getadapterinfo
	#define CHK_getadapterinfo  TRUE
	#define EXP_getadapterinfo  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterinfo", (RTS_UINTPTR)getadapterinfo, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_getadapterinfo  PFGETADAPTERINFO pfgetadapterinfo;
	#define EXT_getadapterinfo  extern PFGETADAPTERINFO pfgetadapterinfo;
	#define GET_getadapterinfo(fl)  s_pfCMGetAPI2( "getadapterinfo", (RTS_VOID_FCTPTR *)&pfgetadapterinfo, (fl), 0, 0)
	#define CAL_getadapterinfo  pfgetadapterinfo
	#define CHK_getadapterinfo  (pfgetadapterinfo != NULL)
	#define EXP_getadapterinfo   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getadapterinfo", (RTS_UINTPTR)getadapterinfo, 1, 0) 
#endif



/**
 * <description>Send IP etherpacket (EoE)</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT sendIPethframe(SendIPEthernetInterface* psfi);
typedef void (CDECL * PFSENDIPETHFRAME) (SendIPEthernetInterface* psfi);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(SENDIPETHFRAME_NOTIMPLEMENTED)
	#define USE_sendIPethframe
	#define EXT_sendIPethframe
	#define GET_sendIPethframe(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sendIPethframe(p0)  
	#define CHK_sendIPethframe  FALSE
	#define EXP_sendIPethframe  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sendIPethframe
	#define EXT_sendIPethframe
	#define GET_sendIPethframe(fl)  CAL_CMGETAPI( "sendIPethframe" ) 
	#define CAL_sendIPethframe  sendIPethframe
	#define CHK_sendIPethframe  TRUE
	#define EXP_sendIPethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendIPethframe", (RTS_UINTPTR)sendIPethframe, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_sendIPethframe
	#define EXT_sendIPethframe
	#define GET_sendIPethframe(fl)  CAL_CMGETAPI( "sendIPethframe" ) 
	#define CAL_sendIPethframe  sendIPethframe
	#define CHK_sendIPethframe  TRUE
	#define EXP_sendIPethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendIPethframe", (RTS_UINTPTR)sendIPethframe, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetsendIPethframe
	#define EXT_SysEthernetsendIPethframe
	#define GET_SysEthernetsendIPethframe  ERR_OK
	#define CAL_SysEthernetsendIPethframe pISysEthernet->IsendIPethframe
	#define CHK_SysEthernetsendIPethframe (pISysEthernet != NULL)
	#define EXP_SysEthernetsendIPethframe  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_sendIPethframe
	#define EXT_sendIPethframe
	#define GET_sendIPethframe(fl)  CAL_CMGETAPI( "sendIPethframe" ) 
	#define CAL_sendIPethframe pISysEthernet->IsendIPethframe
	#define CHK_sendIPethframe (pISysEthernet != NULL)
	#define EXP_sendIPethframe  CAL_CMEXPAPI( "sendIPethframe" ) 
#else /* DYNAMIC_LINK */
	#define USE_sendIPethframe  PFSENDIPETHFRAME pfsendIPethframe;
	#define EXT_sendIPethframe  extern PFSENDIPETHFRAME pfsendIPethframe;
	#define GET_sendIPethframe(fl)  s_pfCMGetAPI2( "sendIPethframe", (RTS_VOID_FCTPTR *)&pfsendIPethframe, (fl), 0, 0)
	#define CAL_sendIPethframe  pfsendIPethframe
	#define CHK_sendIPethframe  (pfsendIPethframe != NULL)
	#define EXP_sendIPethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"sendIPethframe", (RTS_UINTPTR)sendIPethframe, 1, 0) 
#endif




/**
 * <description>Get IP ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
void CDECL CDECL_EXT getIPethframe(GetIPEthernetInterface* pgei);
typedef void (CDECL * PFGETIPETHFRAME) (GetIPEthernetInterface* pgei);
#if defined(SYSETHERNET_NOTIMPLEMENTED) || defined(GETIPETHFRAME_NOTIMPLEMENTED)
	#define USE_getIPethframe
	#define EXT_getIPethframe
	#define GET_getIPethframe(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getIPethframe(p0)  
	#define CHK_getIPethframe  FALSE
	#define EXP_getIPethframe  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getIPethframe
	#define EXT_getIPethframe
	#define GET_getIPethframe(fl)  CAL_CMGETAPI( "getIPethframe" ) 
	#define CAL_getIPethframe  getIPethframe
	#define CHK_getIPethframe  TRUE
	#define EXP_getIPethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getIPethframe", (RTS_UINTPTR)getIPethframe, 1, 0) 
#elif defined(MIXED_LINK) && !defined(SYSETHERNET_EXTERNAL)
	#define USE_getIPethframe
	#define EXT_getIPethframe
	#define GET_getIPethframe(fl)  CAL_CMGETAPI( "getIPethframe" ) 
	#define CAL_getIPethframe  getIPethframe
	#define CHK_getIPethframe  TRUE
	#define EXP_getIPethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getIPethframe", (RTS_UINTPTR)getIPethframe, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysEthernetgetIPethframe
	#define EXT_SysEthernetgetIPethframe
	#define GET_SysEthernetgetIPethframe  ERR_OK
	#define CAL_SysEthernetgetIPethframe pISysEthernet->IgetIPethframe
	#define CHK_SysEthernetgetIPethframe (pISysEthernet != NULL)
	#define EXP_SysEthernetgetIPethframe  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_getIPethframe
	#define EXT_getIPethframe
	#define GET_getIPethframe(fl)  CAL_CMGETAPI( "getIPethframe" ) 
	#define CAL_getIPethframe pISysEthernet->IgetIPethframe
	#define CHK_getIPethframe (pISysEthernet != NULL)
	#define EXP_getIPethframe  CAL_CMEXPAPI( "getIPethframe" ) 
#else /* DYNAMIC_LINK */
	#define USE_getIPethframe  PFGETIPETHFRAME pfgetIPethframe;
	#define EXT_getIPethframe  extern PFGETIPETHFRAME pfgetIPethframe;
	#define GET_getIPethframe(fl)  s_pfCMGetAPI2( "getIPethframe", (RTS_VOID_FCTPTR *)&pfgetIPethframe, (fl), 0, 0)
	#define CAL_getIPethframe  pfgetIPethframe
	#define CHK_getIPethframe  (pfgetIPethframe != NULL)
	#define EXP_getIPethframe  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"getIPethframe", (RTS_UINTPTR)getIPethframe, 1, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFOPENETHERNET Iopenethernet;
 	PFSENDETHFRAME Isendethframe;
 	PFGETETHFRAME Igetethframe;
 	PFCLOSEETHERNET Icloseethernet;
 	PFSENDIPETHFRAME IsendIPethframe;
 	PFGETIPETHFRAME IgetIPethframe;
 } ISysEthernet_C;

#ifdef CPLUSPLUS
class ISysEthernet : public IBase
{
	public:
		virtual void CDECL Iopenethernet(OpenEthernetInterface* poei) =0;
		virtual void CDECL Isendethframe(SendEthernetInterface* psfi) =0;
		virtual void CDECL Igetethframe(GetEthernetInterface* pgei) =0;
		virtual void CDECL Icloseethernet(CloseEthernetInterface* pcei) =0;
		virtual void CDECL IsendIPethframe(SendIPEthernetInterface* psfi) =0;
		virtual void CDECL IgetIPethframe(GetIPEthernetInterface* pgei) =0;
};
	#ifndef ITF_SysEthernet
		#define ITF_SysEthernet static ISysEthernet *pISysEthernet = NULL;
	#endif
	#define EXTITF_SysEthernet
#else	/*CPLUSPLUS*/
	typedef ISysEthernet_C		ISysEthernet;
	#ifndef ITF_SysEthernet
		#define ITF_SysEthernet
	#endif
	#define EXTITF_SysEthernet
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSETHERNETITF_H_*/
