 /**
 * <interfacename>CmpChannelClientIec</interfacename>
 * <description>
 *	Interface for the IEC channel client.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPCHANNELCLIENTIECITF_H_
#define _CMPCHANNELCLIENTIECITF_H_

#include "CmpStd.h"

 

 




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

void CDECL CDECL_EXT netclientopenchannel(netclientopenchannel_struct *p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTOPENCHANNEL_IEC) (netclientopenchannel_struct *p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTOPENCHANNEL_NOTIMPLEMENTED)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientopenchannel(p0) 
	#define CHK_netclientopenchannel  FALSE
	#define EXP_netclientopenchannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  CAL_CMGETAPI( "netclientopenchannel" ) 
	#define CAL_netclientopenchannel  netclientopenchannel
	#define CHK_netclientopenchannel  TRUE
	#define EXP_netclientopenchannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  CAL_CMGETAPI( "netclientopenchannel" ) 
	#define CAL_netclientopenchannel  netclientopenchannel
	#define CHK_netclientopenchannel  TRUE
	#define EXP_netclientopenchannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientopenchannel
	#define EXT_CmpChannelClientIecnetclientopenchannel
	#define GET_CmpChannelClientIecnetclientopenchannel  ERR_OK
	#define CAL_CmpChannelClientIecnetclientopenchannel  netclientopenchannel
	#define CHK_CmpChannelClientIecnetclientopenchannel  TRUE
	#define EXP_CmpChannelClientIecnetclientopenchannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_netclientopenchannel
	#define EXT_netclientopenchannel
	#define GET_netclientopenchannel(fl)  CAL_CMGETAPI( "netclientopenchannel" ) 
	#define CAL_netclientopenchannel  netclientopenchannel
	#define CHK_netclientopenchannel  TRUE
	#define EXP_netclientopenchannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_netclientopenchannel  PFNETCLIENTOPENCHANNEL_IEC pfnetclientopenchannel;
	#define EXT_netclientopenchannel  extern PFNETCLIENTOPENCHANNEL_IEC pfnetclientopenchannel;
	#define GET_netclientopenchannel(fl)  s_pfCMGetAPI2( "netclientopenchannel", (RTS_VOID_FCTPTR *)&pfnetclientopenchannel, (fl), 0, 0)
	#define CAL_netclientopenchannel  pfnetclientopenchannel
	#define CHK_netclientopenchannel  (pfnetclientopenchannel != NULL)
	#define EXP_netclientopenchannel   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannel", (RTS_UINTPTR)netclientopenchannel, 1, 0) 
#endif


void CDECL CDECL_EXT netclientopenchannelresult(netclientopenchannelresult_struct* p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTOPENCHANNELRESULT_IEC) (netclientopenchannelresult_struct* p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTOPENCHANNELRESULT_NOTIMPLEMENTED)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientopenchannelresult(p0) 
	#define CHK_netclientopenchannelresult  FALSE
	#define EXP_netclientopenchannelresult  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  CAL_CMGETAPI( "netclientopenchannelresult" ) 
	#define CAL_netclientopenchannelresult  netclientopenchannelresult
	#define CHK_netclientopenchannelresult  TRUE
	#define EXP_netclientopenchannelresult  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  CAL_CMGETAPI( "netclientopenchannelresult" ) 
	#define CAL_netclientopenchannelresult  netclientopenchannelresult
	#define CHK_netclientopenchannelresult  TRUE
	#define EXP_netclientopenchannelresult  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientopenchannelresult
	#define EXT_CmpChannelClientIecnetclientopenchannelresult
	#define GET_CmpChannelClientIecnetclientopenchannelresult  ERR_OK
	#define CAL_CmpChannelClientIecnetclientopenchannelresult  netclientopenchannelresult
	#define CHK_CmpChannelClientIecnetclientopenchannelresult  TRUE
	#define EXP_CmpChannelClientIecnetclientopenchannelresult  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_netclientopenchannelresult
	#define EXT_netclientopenchannelresult
	#define GET_netclientopenchannelresult(fl)  CAL_CMGETAPI( "netclientopenchannelresult" ) 
	#define CAL_netclientopenchannelresult  netclientopenchannelresult
	#define CHK_netclientopenchannelresult  TRUE
	#define EXP_netclientopenchannelresult  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_netclientopenchannelresult  PFNETCLIENTOPENCHANNELRESULT_IEC pfnetclientopenchannelresult;
	#define EXT_netclientopenchannelresult  extern PFNETCLIENTOPENCHANNELRESULT_IEC pfnetclientopenchannelresult;
	#define GET_netclientopenchannelresult(fl)  s_pfCMGetAPI2( "netclientopenchannelresult", (RTS_VOID_FCTPTR *)&pfnetclientopenchannelresult, (fl), 0, 0)
	#define CAL_netclientopenchannelresult  pfnetclientopenchannelresult
	#define CHK_netclientopenchannelresult  (pfnetclientopenchannelresult != NULL)
	#define EXP_netclientopenchannelresult   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientopenchannelresult", (RTS_UINTPTR)netclientopenchannelresult, 1, 0) 
#endif


void CDECL CDECL_EXT netclientclosechannel(netclientclosechannel_struct* p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTCLOSECHANNEL_IEC) (netclientclosechannel_struct* p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTCLOSECHANNEL_NOTIMPLEMENTED)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientclosechannel(p0) 
	#define CHK_netclientclosechannel  FALSE
	#define EXP_netclientclosechannel  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  CAL_CMGETAPI( "netclientclosechannel" ) 
	#define CAL_netclientclosechannel  netclientclosechannel
	#define CHK_netclientclosechannel  TRUE
	#define EXP_netclientclosechannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  CAL_CMGETAPI( "netclientclosechannel" ) 
	#define CAL_netclientclosechannel  netclientclosechannel
	#define CHK_netclientclosechannel  TRUE
	#define EXP_netclientclosechannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientclosechannel
	#define EXT_CmpChannelClientIecnetclientclosechannel
	#define GET_CmpChannelClientIecnetclientclosechannel  ERR_OK
	#define CAL_CmpChannelClientIecnetclientclosechannel  netclientclosechannel
	#define CHK_CmpChannelClientIecnetclientclosechannel  TRUE
	#define EXP_CmpChannelClientIecnetclientclosechannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_netclientclosechannel
	#define EXT_netclientclosechannel
	#define GET_netclientclosechannel(fl)  CAL_CMGETAPI( "netclientclosechannel" ) 
	#define CAL_netclientclosechannel  netclientclosechannel
	#define CHK_netclientclosechannel  TRUE
	#define EXP_netclientclosechannel  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_netclientclosechannel  PFNETCLIENTCLOSECHANNEL_IEC pfnetclientclosechannel;
	#define EXT_netclientclosechannel  extern PFNETCLIENTCLOSECHANNEL_IEC pfnetclientclosechannel;
	#define GET_netclientclosechannel(fl)  s_pfCMGetAPI2( "netclientclosechannel", (RTS_VOID_FCTPTR *)&pfnetclientclosechannel, (fl), 0, 0)
	#define CAL_netclientclosechannel  pfnetclientclosechannel
	#define CHK_netclientclosechannel  (pfnetclientclosechannel != NULL)
	#define EXP_netclientclosechannel   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientclosechannel", (RTS_UINTPTR)netclientclosechannel, 1, 0) 
#endif


void CDECL CDECL_EXT netclientsend(netclientsend_struct* p);
typedef void (CDECL CDECL_EXT* PFNETCLIENTSEND_IEC) (netclientsend_struct* p);
#if defined(CMPCHANNELCLIENTIEC_NOTIMPLEMENTED) || defined(NETCLIENTSEND_NOTIMPLEMENTED)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  ERR_NOTIMPLEMENTED
	#define CAL_netclientsend(p0) 
	#define CHK_netclientsend  FALSE
	#define EXP_netclientsend  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  CAL_CMGETAPI( "netclientsend" ) 
	#define CAL_netclientsend  netclientsend
	#define CHK_netclientsend  TRUE
	#define EXP_netclientsend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0) 
#elif defined(MIXED_LINK) && !defined(CMPCHANNELCLIENTIEC_EXTERNAL)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  CAL_CMGETAPI( "netclientsend" ) 
	#define CAL_netclientsend  netclientsend
	#define CHK_netclientsend  TRUE
	#define EXP_netclientsend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpChannelClientIecnetclientsend
	#define EXT_CmpChannelClientIecnetclientsend
	#define GET_CmpChannelClientIecnetclientsend  ERR_OK
	#define CAL_CmpChannelClientIecnetclientsend  netclientsend
	#define CHK_CmpChannelClientIecnetclientsend  TRUE
	#define EXP_CmpChannelClientIecnetclientsend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0) 
#elif defined(CPLUSPLUS)
	#define USE_netclientsend
	#define EXT_netclientsend
	#define GET_netclientsend(fl)  CAL_CMGETAPI( "netclientsend" ) 
	#define CAL_netclientsend  netclientsend
	#define CHK_netclientsend  TRUE
	#define EXP_netclientsend  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0) 
#else /* DYNAMIC_LINK */
	#define USE_netclientsend  PFNETCLIENTSEND_IEC pfnetclientsend;
	#define EXT_netclientsend  extern PFNETCLIENTSEND_IEC pfnetclientsend;
	#define GET_netclientsend(fl)  s_pfCMGetAPI2( "netclientsend", (RTS_VOID_FCTPTR *)&pfnetclientsend, (fl), 0, 0)
	#define CAL_netclientsend  pfnetclientsend
	#define CHK_netclientsend  (pfnetclientsend != NULL)
	#define EXP_netclientsend   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"netclientsend", (RTS_UINTPTR)netclientsend, 1, 0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpChannelClientIec_C;

#ifdef CPLUSPLUS
class ICmpChannelClientIec : public IBase
{
	public:
};
	#ifndef ITF_CmpChannelClientIec
		#define ITF_CmpChannelClientIec static ICmpChannelClientIec *pICmpChannelClientIec = NULL;
	#endif
	#define EXTITF_CmpChannelClientIec
#else	/*CPLUSPLUS*/
	typedef ICmpChannelClientIec_C		ICmpChannelClientIec;
	#ifndef ITF_CmpChannelClientIec
		#define ITF_CmpChannelClientIec
	#endif
	#define EXTITF_CmpChannelClientIec
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCHANNELCLIENTIECITF_H_*/
