/**
 * <interfacename>CmpChannelClientIec</interfacename>
 * <description>
 *	Interface for the IEC channel client.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpChannelClientIec')

#ifndef NO_PRAGMA_PACK
	#pragma pack(4)
#endif

typedef struct
{
	RTS_IEC_USINT			components[2];
} addresscomponent_iec_struct;

typedef struct
{
	RTS_IEC_DWORD					dwStructSize;
	RTS_IEC_DINT					addrType;
	RTS_IEC_DINT					nAddrOffset;
	RTS_IEC_UDINT					nAddrLen;
	RTS_IEC_UDINT					nAddrComponentCount;
	addresscomponent_iec_struct		pComponents[MAX_NODEADDR_LEN];		/* an array of nAddrComponentCount entries */
} peeraddress_iec_struct;

typedef struct
{
	RTS_IEC_DWORD			dwSize;
	RTS_IEC_VOIDPTR			pData;
} protocoldataunit_iec_struct;

typedef struct
{
	RTS_IEC_UINT					wChannelHandle;
	protocoldataunit_iec_struct		pdu;
	RTS_IEC_DWORD					Result;
} netclientreplyreceived_struct;

typedef struct
{
	RTS_IEC_UINT				wChannelHandle;
	RTS_IEC_UDINT				udiError;
	RTS_IEC_DWORD				Result;
} netclientchannelerror_struct;

typedef void (CDECL *PFNETCLIENTREPLYRECEIVEDCALLBACK)(netclientreplyreceived_struct* p);
typedef void (CDECL *PFNETCLIENTCHANNELERRORCALLBACK)(netclientchannelerror_struct* p);

typedef struct
{
	peeraddress_iec_struct				addrReceiver;
	RTS_IEC_DWORD						dwCommBufferSize;
	RTS_IEC_DWORD						*pdwReqId;
	PFNETCLIENTREPLYRECEIVEDCALLBACK	pfnReplyReceived;
	PFNETCLIENTCHANNELERRORCALLBACK		pfnChannelError;
	RTS_IEC_DWORD						Result;
} netclientopenchannel_struct;

typedef struct
{
	RTS_IEC_DWORD			dwReqId;
	RTS_IEC_UINT			*pwChannelHandle;
	RTS_IEC_UDINT			*pdwCommBufferSize;
	RTS_IEC_BOOL			*pbBigEndianByteOrder;
	RTS_IEC_DWORD			Result;
} netclientopenchannelresult_struct;

typedef struct
{
	RTS_IEC_UINT			wChannelHandle;
	RTS_IEC_DWORD			Result;
} netclientclosechannel_struct;

typedef struct
{
	RTS_IEC_UINT					wChannelHandle;
	protocoldataunit_iec_struct		pduData;
	RTS_IEC_DWORD					Result;
} netclientsend_struct;

#ifndef NO_PRAGMA_PACK
	#pragma pack()
#endif

#ifdef __cplusplus
extern "C" {
#endif

DEF_API(`void',`CDECL',`netclientopenchannel',`(netclientopenchannel_struct *p)',1,0)

DEF_API(`void',`CDECL',`netclientopenchannelresult',`(netclientopenchannelresult_struct* p)',1,0)

DEF_API(`void',`CDECL',`netclientclosechannel',`(netclientclosechannel_struct* p)',1,0)

DEF_API(`void',`CDECL',`netclientsend',`(netclientsend_struct* p)',1,0)

#ifdef __cplusplus
}
#endif
