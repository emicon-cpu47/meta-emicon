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

SET_INTERFACE_NAME(`SysEthernet')

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
DEF_ITF_API(`void',`CDECL',`openethernet',`(OpenEthernetInterface* poei)',1)

/**
 * <description>Send etherpacket</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`sendethframe',`(SendEthernetInterface* psfi)',1)

/**
 * <description>Get ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`getethframe',`(GetEthernetInterface* pgei)',1)

/**
 * <description>Close network adapter</description>
 * <param name="pcei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`closeethernet',`(CloseEthernetInterface* pcei)',1)

/**
 * <description>Get number of network adapters</description>
 * <param name="pnoei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_API(`void',`CDECL',`getnumberofadapters',`(GetNumberOfEthernetInterface* pnoei)',1)

/**
 *  <description>Get info about specified network adapters</description>
 * <param name="paiei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_API(`void',`CDECL',`getadapterinfo',`(GetAdapterInfoEthernetInterface* paiei)',1)


/**
 * <description>Send IP etherpacket (EoE)</description>
 * <param name="psfi" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`sendIPethframe',`(SendIPEthernetInterface* psfi)',1)

/**
 * <description>Get IP ethernet packet</description>
 * <param name="pgei" type="IN">Pointer to parameters</param>
 * <result>error code</result>
 */
DEF_ITF_API(`void',`CDECL',`getIPethframe',`(GetIPEthernetInterface* pgei)',1)

#ifdef __cplusplus
}
#endif
