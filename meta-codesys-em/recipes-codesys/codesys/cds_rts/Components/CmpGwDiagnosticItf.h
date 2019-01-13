 /**
 * <interfacename>CmpGwDiagnostic</interfacename>
 * <description> 
 *   This interface provides diagnostic access to the gateway. It allows other
 *   components to register as a listener. After that they will be informed about
 *   activities in the gateway like addition of new channels, closing of channels,
 *   connected clients, etc. 
 *   It also allows the client to query the state of several objects. The state of
 *   a channel for example includes the number of open requests or the current quality
 *   (error rate, round-trip-time).
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPGWDIAGNOSTICITF_H_
#define _CMPGWDIAGNOSTICITF_H_

#include "CmpStd.h"

 

 




#include "CmpCommunicationLibItf.h"

#ifdef __cplusplus
extern "C" {
#endif

/* 
 * Object types
 */
enum
{
	GWDOT_COMMDRV, /* A communication driver (client-gateway communication) */
	GWDOT_CLIENT,
	GWDOT_CHANNEL,
	GWDOT_VIRTUALCHANNEL,
	GWDOT_VIRTUALCHANNELREF
};

/* This struct is used to pass name/value pairs in different contexts */
typedef struct 
{
	RTS_WCHAR *wszName;
	RTS_WCHAR *wszValue;
}GWDPROPERTY;

typedef struct
{
	int nSize; /* Size of the structure */
	unsigned long ulObjectId; /* The object id is unique only within one object type (ie. different object types may use the same id)! */
}GWDOBJECTINFO;

typedef struct
{
	GWDOBJECTINFO objInfo;
	RTS_WCHAR *wszName;

	int nNumSettings; /* Number of valid entries in the driverSettings array */
	GWDPROPERTY *driverSettings; /* An array of properties of the driver - eg. port(TCP) or BaudRate(RS232) etc.*/
}GWDCOMMDRVINFO;

typedef struct
{
	GWDOBJECTINFO objInfo;

	unsigned long ulDriverId; /* Id of the commdriver used */
	RTS_WCHAR *wszAddress;	  /* Address of the client. The content depends highly on the commdriver */
	RTS_WCHAR *wszUserName;	  /* Name of the authenticated user */

	/* TODO: Connected since (timestamp) */
}GWDCLIENTINFO;

typedef struct
{
	GWDOBJECTINFO objInfo;

	NODEADDRESSREF addrDevice; /* Address of the remote device */
	unsigned long ulCommBufferSize; 
}GWDCHANNELINFO;

/* Information about a virtual channel passed as pInfo in a call to the ObjectAdded function. */
typedef struct
{
	GWDOBJECTINFO objInfo;

	unsigned long ulChannelId; /* The channel used by this virtual channel */
	RTS_WCHAR *wszChannelName;
}GWDVIRTUALCHANNELINFO;

/* Information about a reference to a virtual channel.
   This struct is passed as pInfo in a call to the ObjectAdded function. 
*/
typedef struct
{
	GWDOBJECTINFO objInfo;
	
	unsigned long ulVirtualChannelId;
	unsigned long ulClientId;
}GWDVIRTUALCHANNELREFINFO;

/**
 * <description>
 *   This structure describes the current state of a channel. The information provided
 *   describes a snapshot of the channel state and is likely to change when retrieved next.
 *   This structure is intended for future extension; new members may be appended to the end.
 *   Any component using this structure or an extension of it must be prepared to also handle 
 *   this base structure.
 * </description>
 */
typedef struct
{
	int nStructSize; /* Size of this struct. Allows for future extension of this struct */

	unsigned long ulOpenRequests; /* Number of requests currently waiting to be handled for this channel */

	unsigned long ulBlocksSent;   /* Number of blocks sent to the remote node. Retransmitted blocks are counted twice. */
	unsigned long ulBlocksFailed; /* Number of blocks that had to be retransmitted */

	unsigned long ulRoundTripTime; /* Average time from the sending of a block until the answer is received (microseconds)*/
}GWDCHANNELSTATE;

/** 
 * <description>
 *   Is called every time an object is added in the gateway. 
 * </description>
 * <param name="nObjType" type="IN">
 *   The type of the object which is added. One of the GWDOT_xxx constants.
 *   Since new object types may be added in the future, implementations should
 *   handle unknown objects types gracefully.
 * </param>
 * <param name="pInfo" type="IN">
 *   Additional information about the added object. Depending on the object type
 *   an extension of the GWOBJECTINFO struct will be passed.
 * </param>
 */
typedef void (CDECL *PFOBJECTADDED)(unsigned long ulListenerId, int nObjType, GWDOBJECTINFO *pInfo);

/** 
 * <description>
 *   Called by the gateway when an object is removed. 
 * </description>
 * <param name="nObjType" type="IN">
 *   Same as in PFOBJECTADDED. ulObjectId is not unique across different object types!
 * </param>
 * <param name="ulObjectId" type="IN">
 *   Refers to the object id passed in the ObjectAdded routines pInfo parameter.
 * </param>
 */
typedef void (CDECL *PFOBJECTREMOVED)(unsigned long ulListenerId, int nObjType, unsigned long ulObjectId);

typedef struct
{
	int nStructSize; /* Allows for future extension of this structure */

	PFOBJECTADDED pfObjectAdded;
	PFOBJECTREMOVED pfObjectRemoved;
}GWDLISTENERCALLBACKS;
 
/**
 * <description>
 *   Register a listener for the gateway diagnostics interface. The listener will be informed about
 *   activities within the gateway using the provided callbacks.
 *   When calling this function, the listener is expected to be in an initial state. 
 *   Therefore the pfObjectAdded function will be called for each object that exists in the gateway
 *   in order to synchronize the listener with the gateway.
 * </description>
 * <param name="callbacks" type="IN">callback functions of the listener</param>
 * <param name="pulListenerId" type="OUT">
 *   Will be set to a unique number that identifies the listener. Use this value in a call to 
 *   unsubscribe.
 * </param>
 */
int CDECL GWDRegisterListener(GWDLISTENERCALLBACKS callbacks, unsigned long *pulListenerId);
typedef int (CDECL * PFGWDREGISTERLISTENER) (GWDLISTENERCALLBACKS callbacks, unsigned long *pulListenerId);
#if defined(CMPGWDIAGNOSTIC_NOTIMPLEMENTED) || defined(GWDREGISTERLISTENER_NOTIMPLEMENTED)
	#define USE_GWDRegisterListener
	#define EXT_GWDRegisterListener
	#define GET_GWDRegisterListener(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWDRegisterListener(p0,p1) (int)ERR_NOTIMPLEMENTED
	#define CHK_GWDRegisterListener  FALSE
	#define EXP_GWDRegisterListener  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWDRegisterListener
	#define EXT_GWDRegisterListener
	#define GET_GWDRegisterListener(fl)  CAL_CMGETAPI( "GWDRegisterListener" ) 
	#define CAL_GWDRegisterListener  GWDRegisterListener
	#define CHK_GWDRegisterListener  TRUE
	#define EXP_GWDRegisterListener  CAL_CMEXPAPI( "GWDRegisterListener" ) 
#elif defined(MIXED_LINK) && !defined(CMPGWDIAGNOSTIC_EXTERNAL)
	#define USE_GWDRegisterListener
	#define EXT_GWDRegisterListener
	#define GET_GWDRegisterListener(fl)  CAL_CMGETAPI( "GWDRegisterListener" ) 
	#define CAL_GWDRegisterListener  GWDRegisterListener
	#define CHK_GWDRegisterListener  TRUE
	#define EXP_GWDRegisterListener  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWDRegisterListener", (RTS_UINTPTR)GWDRegisterListener, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGwDiagnosticGWDRegisterListener
	#define EXT_CmpGwDiagnosticGWDRegisterListener
	#define GET_CmpGwDiagnosticGWDRegisterListener  ERR_OK
	#define CAL_CmpGwDiagnosticGWDRegisterListener  GWDRegisterListener
	#define CHK_CmpGwDiagnosticGWDRegisterListener  TRUE
	#define EXP_CmpGwDiagnosticGWDRegisterListener  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWDRegisterListener
	#define EXT_GWDRegisterListener
	#define GET_GWDRegisterListener(fl)  CAL_CMGETAPI( "GWDRegisterListener" ) 
	#define CAL_GWDRegisterListener  GWDRegisterListener
	#define CHK_GWDRegisterListener  TRUE
	#define EXP_GWDRegisterListener  CAL_CMEXPAPI( "GWDRegisterListener" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWDRegisterListener  PFGWDREGISTERLISTENER pfGWDRegisterListener;
	#define EXT_GWDRegisterListener  extern PFGWDREGISTERLISTENER pfGWDRegisterListener;
	#define GET_GWDRegisterListener(fl)  s_pfCMGetAPI2( "GWDRegisterListener", (RTS_VOID_FCTPTR *)&pfGWDRegisterListener, (fl), 0, 0)
	#define CAL_GWDRegisterListener  pfGWDRegisterListener
	#define CHK_GWDRegisterListener  (pfGWDRegisterListener != NULL)
	#define EXP_GWDRegisterListener   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWDRegisterListener", (RTS_UINTPTR)GWDRegisterListener, 0, 0) 
#endif


/**
 * <description>
 *   Stop informing the specified listener about activities in the gateway.
 * </description>
 * <param name="ulListenerId" type="IN">The id returned by the GWDRegisterListener</param>
 */
int CDECL GWDUnregisterListener(unsigned long ulListenerId);
typedef int (CDECL * PFGWDUNREGISTERLISTENER) (unsigned long ulListenerId);
#if defined(CMPGWDIAGNOSTIC_NOTIMPLEMENTED) || defined(GWDUNREGISTERLISTENER_NOTIMPLEMENTED)
	#define USE_GWDUnregisterListener
	#define EXT_GWDUnregisterListener
	#define GET_GWDUnregisterListener(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWDUnregisterListener(p0) (int)ERR_NOTIMPLEMENTED
	#define CHK_GWDUnregisterListener  FALSE
	#define EXP_GWDUnregisterListener  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWDUnregisterListener
	#define EXT_GWDUnregisterListener
	#define GET_GWDUnregisterListener(fl)  CAL_CMGETAPI( "GWDUnregisterListener" ) 
	#define CAL_GWDUnregisterListener  GWDUnregisterListener
	#define CHK_GWDUnregisterListener  TRUE
	#define EXP_GWDUnregisterListener  CAL_CMEXPAPI( "GWDUnregisterListener" ) 
#elif defined(MIXED_LINK) && !defined(CMPGWDIAGNOSTIC_EXTERNAL)
	#define USE_GWDUnregisterListener
	#define EXT_GWDUnregisterListener
	#define GET_GWDUnregisterListener(fl)  CAL_CMGETAPI( "GWDUnregisterListener" ) 
	#define CAL_GWDUnregisterListener  GWDUnregisterListener
	#define CHK_GWDUnregisterListener  TRUE
	#define EXP_GWDUnregisterListener  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWDUnregisterListener", (RTS_UINTPTR)GWDUnregisterListener, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGwDiagnosticGWDUnregisterListener
	#define EXT_CmpGwDiagnosticGWDUnregisterListener
	#define GET_CmpGwDiagnosticGWDUnregisterListener  ERR_OK
	#define CAL_CmpGwDiagnosticGWDUnregisterListener  GWDUnregisterListener
	#define CHK_CmpGwDiagnosticGWDUnregisterListener  TRUE
	#define EXP_CmpGwDiagnosticGWDUnregisterListener  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWDUnregisterListener
	#define EXT_GWDUnregisterListener
	#define GET_GWDUnregisterListener(fl)  CAL_CMGETAPI( "GWDUnregisterListener" ) 
	#define CAL_GWDUnregisterListener  GWDUnregisterListener
	#define CHK_GWDUnregisterListener  TRUE
	#define EXP_GWDUnregisterListener  CAL_CMEXPAPI( "GWDUnregisterListener" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWDUnregisterListener  PFGWDUNREGISTERLISTENER pfGWDUnregisterListener;
	#define EXT_GWDUnregisterListener  extern PFGWDUNREGISTERLISTENER pfGWDUnregisterListener;
	#define GET_GWDUnregisterListener(fl)  s_pfCMGetAPI2( "GWDUnregisterListener", (RTS_VOID_FCTPTR *)&pfGWDUnregisterListener, (fl), 0, 0)
	#define CAL_GWDUnregisterListener  pfGWDUnregisterListener
	#define CHK_GWDUnregisterListener  (pfGWDUnregisterListener != NULL)
	#define EXP_GWDUnregisterListener   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWDUnregisterListener", (RTS_UINTPTR)GWDUnregisterListener, 0, 0) 
#endif


/**
 * <description>
 *   Fills the pState structure with the current state of a channel. 
 * </description>  
 * <param name="ulChannelId" type="IN">id of the channel as provided in the addObject callback</param>
 * <param name="pState" type="OUT">
 *   Will be filled with the current channel state. Must not be NULL and the nStructSize member of the
 *   struct must be set to thesize of the structure provided. 
 *   On success this member will be set to the size of the structure actually used, which is less or equal
 *   to the provided size. If a component passes in an extension of GWDCHANNELSTATE it must be prepared
 *   that the gateway only fills the basic structure.
 * </param>
 */
int CDECL GWDGetChannelState(unsigned long ulChannelId, GWDCHANNELSTATE *pState);
typedef int (CDECL * PFGWDGETCHANNELSTATE) (unsigned long ulChannelId, GWDCHANNELSTATE *pState);
#if defined(CMPGWDIAGNOSTIC_NOTIMPLEMENTED) || defined(GWDGETCHANNELSTATE_NOTIMPLEMENTED)
	#define USE_GWDGetChannelState
	#define EXT_GWDGetChannelState
	#define GET_GWDGetChannelState(fl)  ERR_NOTIMPLEMENTED
	#define CAL_GWDGetChannelState(p0,p1) (int)ERR_NOTIMPLEMENTED
	#define CHK_GWDGetChannelState  FALSE
	#define EXP_GWDGetChannelState  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_GWDGetChannelState
	#define EXT_GWDGetChannelState
	#define GET_GWDGetChannelState(fl)  CAL_CMGETAPI( "GWDGetChannelState" ) 
	#define CAL_GWDGetChannelState  GWDGetChannelState
	#define CHK_GWDGetChannelState  TRUE
	#define EXP_GWDGetChannelState  CAL_CMEXPAPI( "GWDGetChannelState" ) 
#elif defined(MIXED_LINK) && !defined(CMPGWDIAGNOSTIC_EXTERNAL)
	#define USE_GWDGetChannelState
	#define EXT_GWDGetChannelState
	#define GET_GWDGetChannelState(fl)  CAL_CMGETAPI( "GWDGetChannelState" ) 
	#define CAL_GWDGetChannelState  GWDGetChannelState
	#define CHK_GWDGetChannelState  TRUE
	#define EXP_GWDGetChannelState  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWDGetChannelState", (RTS_UINTPTR)GWDGetChannelState, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpGwDiagnosticGWDGetChannelState
	#define EXT_CmpGwDiagnosticGWDGetChannelState
	#define GET_CmpGwDiagnosticGWDGetChannelState  ERR_OK
	#define CAL_CmpGwDiagnosticGWDGetChannelState  GWDGetChannelState
	#define CHK_CmpGwDiagnosticGWDGetChannelState  TRUE
	#define EXP_CmpGwDiagnosticGWDGetChannelState  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_GWDGetChannelState
	#define EXT_GWDGetChannelState
	#define GET_GWDGetChannelState(fl)  CAL_CMGETAPI( "GWDGetChannelState" ) 
	#define CAL_GWDGetChannelState  GWDGetChannelState
	#define CHK_GWDGetChannelState  TRUE
	#define EXP_GWDGetChannelState  CAL_CMEXPAPI( "GWDGetChannelState" ) 
#else /* DYNAMIC_LINK */
	#define USE_GWDGetChannelState  PFGWDGETCHANNELSTATE pfGWDGetChannelState;
	#define EXT_GWDGetChannelState  extern PFGWDGETCHANNELSTATE pfGWDGetChannelState;
	#define GET_GWDGetChannelState(fl)  s_pfCMGetAPI2( "GWDGetChannelState", (RTS_VOID_FCTPTR *)&pfGWDGetChannelState, (fl), 0, 0)
	#define CAL_GWDGetChannelState  pfGWDGetChannelState
	#define CHK_GWDGetChannelState  (pfGWDGetChannelState != NULL)
	#define EXP_GWDGetChannelState   s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"GWDGetChannelState", (RTS_UINTPTR)GWDGetChannelState, 0, 0) 
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpGwDiagnostic_C;

#ifdef CPLUSPLUS
class ICmpGwDiagnostic : public IBase
{
	public:
};
	#ifndef ITF_CmpGwDiagnostic
		#define ITF_CmpGwDiagnostic static ICmpGwDiagnostic *pICmpGwDiagnostic = NULL;
	#endif
	#define EXTITF_CmpGwDiagnostic
#else	/*CPLUSPLUS*/
	typedef ICmpGwDiagnostic_C		ICmpGwDiagnostic;
	#ifndef ITF_CmpGwDiagnostic
		#define ITF_CmpGwDiagnostic
	#endif
	#define EXTITF_CmpGwDiagnostic
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPGWDIAGNOSTICITF_H_*/
