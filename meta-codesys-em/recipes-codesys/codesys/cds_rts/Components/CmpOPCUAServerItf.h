 /**
 * <interfacename>CmpOPCUAServer</interfacename>
 * <description></description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */


	
	
#ifndef _CMPOPCUASERVERITF_H_
#define _CMPOPCUASERVERITF_H_

#include "CmpStd.h"

 

 



#include "CmpOPCUAProviderItf.h"

#include "opcua.h"

/**
 * <category>Settings</category>
 * <type>String</type>
 * <description>Configure the name network adapter to be used by the OPC UA server. By Default OPC UA will bind to ANY adress.</description>
 */
#define CMPOPCUAKEY_STRING_NETWORK_ADAPTER					"NetworkAdapter"
#ifndef CMPOPCUAVALUE_STRING_NETWORK_ADAPTER_DEFAULT	
	#define CMPOPCUAVALUE_STRING_NETWORK_ADAPTER_DEFAULT	""
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Configure the port used by the OPC UA server. Default: 4840</description>
 */
#define CMPOPCUAKEY_INT_NETWORK_PORT						"NetworkPort"
#ifndef CMPOPCUAVALUE_INT_NETWORK_PORT_DEFAULT
	#define CMPOPCUAVALUE_INT_NETWORK_PORT_DEFAULT			4840
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Use this setting to add the loopback adapter as an OPC UA endpoint if it is missing in your configuration.</description>
 */
#define CMPOPCUAKEY_INT_USE_LOOPBACK						"UseLoopback"
#ifndef CMPOPCUAVALUE_INT_USE_LOOPBACK_DEFAULT	
	#define CMPOPCUAVALUE_INT_USE_LOOPBACK_DEFAULT			0
#endif



#define Max_NumericRanges 5
typedef enum _NumericRangeType
{
	RangeType_Index = 0,
	RangeType_Range
} NumericRangeType;


/**
 * <element name="uiFrom">Index or start of range if Type = Range.</element>
 * <element name="uiTo">End of range if Type = Range, unused otherwise.</element>
 */
typedef struct _NumericRange
{
	NumericRangeType Type;
	OpcUa_Int32 uiFrom;
	OpcUa_Int32 uiTo;
} NumericRange;


/**
 * <description>Register a new data provider within the OPC UA server.</description>
 * <param name="providerInterface" type="IN">Table of the provider interface.</param>
 * <result>Operation result:
 * </result>
 **/
RTS_RESULT CDECL OpcUaServerRegisterProvider(OpcUaProvider_Info* providerInterface);
typedef RTS_RESULT (CDECL * PFOPCUASERVERREGISTERPROVIDER) (OpcUaProvider_Info* providerInterface);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERREGISTERPROVIDER_NOTIMPLEMENTED)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerRegisterProvider(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerRegisterProvider  FALSE
	#define EXP_OpcUaServerRegisterProvider  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerRegisterProvider" ) 
	#define CAL_OpcUaServerRegisterProvider  OpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider  TRUE
	#define EXP_OpcUaServerRegisterProvider  CAL_CMEXPAPI( "OpcUaServerRegisterProvider" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerRegisterProvider" ) 
	#define CAL_OpcUaServerRegisterProvider  OpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider  TRUE
	#define EXP_OpcUaServerRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterProvider", (RTS_UINTPTR)OpcUaServerRegisterProvider, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerRegisterProvider
	#define EXT_CmpOPCUAServerOpcUaServerRegisterProvider
	#define GET_CmpOPCUAServerOpcUaServerRegisterProvider  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerRegisterProvider pICmpOPCUAServer->IOpcUaServerRegisterProvider
	#define CHK_CmpOPCUAServerOpcUaServerRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerRegisterProvider  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerRegisterProvider
	#define EXT_OpcUaServerRegisterProvider
	#define GET_OpcUaServerRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerRegisterProvider" ) 
	#define CAL_OpcUaServerRegisterProvider pICmpOPCUAServer->IOpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerRegisterProvider  CAL_CMEXPAPI( "OpcUaServerRegisterProvider" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerRegisterProvider  PFOPCUASERVERREGISTERPROVIDER pfOpcUaServerRegisterProvider;
	#define EXT_OpcUaServerRegisterProvider  extern PFOPCUASERVERREGISTERPROVIDER pfOpcUaServerRegisterProvider;
	#define GET_OpcUaServerRegisterProvider(fl)  s_pfCMGetAPI2( "OpcUaServerRegisterProvider", (RTS_VOID_FCTPTR *)&pfOpcUaServerRegisterProvider, (fl), 0, 0)
	#define CAL_OpcUaServerRegisterProvider  pfOpcUaServerRegisterProvider
	#define CHK_OpcUaServerRegisterProvider  (pfOpcUaServerRegisterProvider != NULL)
	#define EXP_OpcUaServerRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterProvider", (RTS_UINTPTR)OpcUaServerRegisterProvider, 0, 0) 
#endif




/**
 * <description>Unregister an already registered data provider within the OPC UA server.</description>
 * <param name="providerInterface" type="IN">Table of the provider interface.</param>
 * <result>Operation result:
 * </result>
 **/
RTS_RESULT CDECL OpcUaServerUnRegisterProvider(OpcUaProvider_Info* providerInterface);
typedef RTS_RESULT (CDECL * PFOPCUASERVERUNREGISTERPROVIDER) (OpcUaProvider_Info* providerInterface);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERUNREGISTERPROVIDER_NOTIMPLEMENTED)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerUnRegisterProvider(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerUnRegisterProvider  FALSE
	#define EXP_OpcUaServerUnRegisterProvider  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerUnRegisterProvider" ) 
	#define CAL_OpcUaServerUnRegisterProvider  OpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider  TRUE
	#define EXP_OpcUaServerUnRegisterProvider  CAL_CMEXPAPI( "OpcUaServerUnRegisterProvider" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerUnRegisterProvider" ) 
	#define CAL_OpcUaServerUnRegisterProvider  OpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider  TRUE
	#define EXP_OpcUaServerUnRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnRegisterProvider", (RTS_UINTPTR)OpcUaServerUnRegisterProvider, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerUnRegisterProvider
	#define EXT_CmpOPCUAServerOpcUaServerUnRegisterProvider
	#define GET_CmpOPCUAServerOpcUaServerUnRegisterProvider  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerUnRegisterProvider pICmpOPCUAServer->IOpcUaServerUnRegisterProvider
	#define CHK_CmpOPCUAServerOpcUaServerUnRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerUnRegisterProvider  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerUnRegisterProvider
	#define EXT_OpcUaServerUnRegisterProvider
	#define GET_OpcUaServerUnRegisterProvider(fl)  CAL_CMGETAPI( "OpcUaServerUnRegisterProvider" ) 
	#define CAL_OpcUaServerUnRegisterProvider pICmpOPCUAServer->IOpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerUnRegisterProvider  CAL_CMEXPAPI( "OpcUaServerUnRegisterProvider" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerUnRegisterProvider  PFOPCUASERVERUNREGISTERPROVIDER pfOpcUaServerUnRegisterProvider;
	#define EXT_OpcUaServerUnRegisterProvider  extern PFOPCUASERVERUNREGISTERPROVIDER pfOpcUaServerUnRegisterProvider;
	#define GET_OpcUaServerUnRegisterProvider(fl)  s_pfCMGetAPI2( "OpcUaServerUnRegisterProvider", (RTS_VOID_FCTPTR *)&pfOpcUaServerUnRegisterProvider, (fl), 0, 0)
	#define CAL_OpcUaServerUnRegisterProvider  pfOpcUaServerUnRegisterProvider
	#define CHK_OpcUaServerUnRegisterProvider  (pfOpcUaServerUnRegisterProvider != NULL)
	#define EXP_OpcUaServerUnRegisterProvider  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerUnRegisterProvider", (RTS_UINTPTR)OpcUaServerUnRegisterProvider, 0, 0) 
#endif




/**
 * <description>Check if to follow OPCU UA referencetype ID. Since referenctype IDs may are derived only the server who knows all IDs can check this.</description>
 * <param name="pRequestedReference" type="IN">The referencetype ID the client requested.</param>
 * <param name="bIncludeSubtypes" type="IN">The flag if subtypes should be followed too. Set by the client.</param>
 * <param name="pReferenceToCheck" type="IN">The referencetype ID the compare against. Usually the referencetype ID of the current node (e.g. while browsing) in the adress space.</param>
 * <result>The function returns OpcUa_True if following the referencetype ID is allowd. OpcUa_False is returned otherwhise.</result>
 **/
OpcUa_Boolean CDECL OpcUaServerCheckReferenceRecursive(const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck);
typedef OpcUa_Boolean (CDECL * PFOPCUASERVERCHECKREFERENCERECURSIVE) (const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERCHECKREFERENCERECURSIVE_NOTIMPLEMENTED)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerCheckReferenceRecursive(p0,p1,p2)  (OpcUa_Boolean)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerCheckReferenceRecursive  FALSE
	#define EXP_OpcUaServerCheckReferenceRecursive  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  CAL_CMGETAPI( "OpcUaServerCheckReferenceRecursive" ) 
	#define CAL_OpcUaServerCheckReferenceRecursive  OpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive  TRUE
	#define EXP_OpcUaServerCheckReferenceRecursive  CAL_CMEXPAPI( "OpcUaServerCheckReferenceRecursive" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  CAL_CMGETAPI( "OpcUaServerCheckReferenceRecursive" ) 
	#define CAL_OpcUaServerCheckReferenceRecursive  OpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive  TRUE
	#define EXP_OpcUaServerCheckReferenceRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckReferenceRecursive", (RTS_UINTPTR)OpcUaServerCheckReferenceRecursive, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerCheckReferenceRecursive
	#define EXT_CmpOPCUAServerOpcUaServerCheckReferenceRecursive
	#define GET_CmpOPCUAServerOpcUaServerCheckReferenceRecursive  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerCheckReferenceRecursive pICmpOPCUAServer->IOpcUaServerCheckReferenceRecursive
	#define CHK_CmpOPCUAServerOpcUaServerCheckReferenceRecursive (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerCheckReferenceRecursive  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerCheckReferenceRecursive
	#define EXT_OpcUaServerCheckReferenceRecursive
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  CAL_CMGETAPI( "OpcUaServerCheckReferenceRecursive" ) 
	#define CAL_OpcUaServerCheckReferenceRecursive pICmpOPCUAServer->IOpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerCheckReferenceRecursive  CAL_CMEXPAPI( "OpcUaServerCheckReferenceRecursive" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerCheckReferenceRecursive  PFOPCUASERVERCHECKREFERENCERECURSIVE pfOpcUaServerCheckReferenceRecursive;
	#define EXT_OpcUaServerCheckReferenceRecursive  extern PFOPCUASERVERCHECKREFERENCERECURSIVE pfOpcUaServerCheckReferenceRecursive;
	#define GET_OpcUaServerCheckReferenceRecursive(fl)  s_pfCMGetAPI2( "OpcUaServerCheckReferenceRecursive", (RTS_VOID_FCTPTR *)&pfOpcUaServerCheckReferenceRecursive, (fl), 0, 0)
	#define CAL_OpcUaServerCheckReferenceRecursive  pfOpcUaServerCheckReferenceRecursive
	#define CHK_OpcUaServerCheckReferenceRecursive  (pfOpcUaServerCheckReferenceRecursive != NULL)
	#define EXP_OpcUaServerCheckReferenceRecursive  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckReferenceRecursive", (RTS_UINTPTR)OpcUaServerCheckReferenceRecursive, 0, 0) 
#endif




/**
 * <description>This funtion checks if a referencetype ID is valid.</description>
 * <param name="pRefTypeId" type="IN">Referecetype ID to check.</param>
 * <result>Returns either OpcUa_Good or OpcUa_BadRefereceTypeIdInvalid.</result>
 **/
OpcUa_StatusCode CDECL OpcUaServerCheckIfReferenceIsValid(const OpcUa_NodeId* pRefTypeId);
typedef OpcUa_StatusCode (CDECL * PFOPCUASERVERCHECKIFREFERENCEISVALID) (const OpcUa_NodeId* pRefTypeId);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERCHECKIFREFERENCEISVALID_NOTIMPLEMENTED)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerCheckIfReferenceIsValid(p0)  (OpcUa_StatusCode)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerCheckIfReferenceIsValid  FALSE
	#define EXP_OpcUaServerCheckIfReferenceIsValid  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  CAL_CMGETAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
	#define CAL_OpcUaServerCheckIfReferenceIsValid  OpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid  TRUE
	#define EXP_OpcUaServerCheckIfReferenceIsValid  CAL_CMEXPAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  CAL_CMGETAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
	#define CAL_OpcUaServerCheckIfReferenceIsValid  OpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid  TRUE
	#define EXP_OpcUaServerCheckIfReferenceIsValid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckIfReferenceIsValid", (RTS_UINTPTR)OpcUaServerCheckIfReferenceIsValid, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid
	#define EXT_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid
	#define GET_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid pICmpOPCUAServer->IOpcUaServerCheckIfReferenceIsValid
	#define CHK_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerCheckIfReferenceIsValid  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerCheckIfReferenceIsValid
	#define EXT_OpcUaServerCheckIfReferenceIsValid
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  CAL_CMGETAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
	#define CAL_OpcUaServerCheckIfReferenceIsValid pICmpOPCUAServer->IOpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerCheckIfReferenceIsValid  CAL_CMEXPAPI( "OpcUaServerCheckIfReferenceIsValid" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerCheckIfReferenceIsValid  PFOPCUASERVERCHECKIFREFERENCEISVALID pfOpcUaServerCheckIfReferenceIsValid;
	#define EXT_OpcUaServerCheckIfReferenceIsValid  extern PFOPCUASERVERCHECKIFREFERENCEISVALID pfOpcUaServerCheckIfReferenceIsValid;
	#define GET_OpcUaServerCheckIfReferenceIsValid(fl)  s_pfCMGetAPI2( "OpcUaServerCheckIfReferenceIsValid", (RTS_VOID_FCTPTR *)&pfOpcUaServerCheckIfReferenceIsValid, (fl), 0, 0)
	#define CAL_OpcUaServerCheckIfReferenceIsValid  pfOpcUaServerCheckIfReferenceIsValid
	#define CHK_OpcUaServerCheckIfReferenceIsValid  (pfOpcUaServerCheckIfReferenceIsValid != NULL)
	#define EXP_OpcUaServerCheckIfReferenceIsValid  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerCheckIfReferenceIsValid", (RTS_UINTPTR)OpcUaServerCheckIfReferenceIsValid, 0, 0) 
#endif




/**
 * <description>Get the namespace index of the given namespace. Do not relay on constant referencetype IDs. They may depend on the registration order of different providers.</description>
 * <param name="pNamespace" type="IN">The namespace of intrest.</param>
 * <result>-1: If the namespace is not registerd yet. index: The index of the namespace. This does not change while the server is running.</result>
 **/
OpcUa_Int16 CDECL OpcUaServerGetNamespaceIndex(OpcUa_String* pNamespace);
typedef OpcUa_Int16 (CDECL * PFOPCUASERVERGETNAMESPACEINDEX) (OpcUa_String* pNamespace);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETNAMESPACEINDEX_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetNamespaceIndex(p0)  (OpcUa_Int16)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetNamespaceIndex  FALSE
	#define EXP_OpcUaServerGetNamespaceIndex  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  CAL_CMGETAPI( "OpcUaServerGetNamespaceIndex" ) 
	#define CAL_OpcUaServerGetNamespaceIndex  OpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex  TRUE
	#define EXP_OpcUaServerGetNamespaceIndex  CAL_CMEXPAPI( "OpcUaServerGetNamespaceIndex" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  CAL_CMGETAPI( "OpcUaServerGetNamespaceIndex" ) 
	#define CAL_OpcUaServerGetNamespaceIndex  OpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex  TRUE
	#define EXP_OpcUaServerGetNamespaceIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetNamespaceIndex", (RTS_UINTPTR)OpcUaServerGetNamespaceIndex, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetNamespaceIndex
	#define EXT_CmpOPCUAServerOpcUaServerGetNamespaceIndex
	#define GET_CmpOPCUAServerOpcUaServerGetNamespaceIndex  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetNamespaceIndex pICmpOPCUAServer->IOpcUaServerGetNamespaceIndex
	#define CHK_CmpOPCUAServerOpcUaServerGetNamespaceIndex (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetNamespaceIndex  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetNamespaceIndex
	#define EXT_OpcUaServerGetNamespaceIndex
	#define GET_OpcUaServerGetNamespaceIndex(fl)  CAL_CMGETAPI( "OpcUaServerGetNamespaceIndex" ) 
	#define CAL_OpcUaServerGetNamespaceIndex pICmpOPCUAServer->IOpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetNamespaceIndex  CAL_CMEXPAPI( "OpcUaServerGetNamespaceIndex" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetNamespaceIndex  PFOPCUASERVERGETNAMESPACEINDEX pfOpcUaServerGetNamespaceIndex;
	#define EXT_OpcUaServerGetNamespaceIndex  extern PFOPCUASERVERGETNAMESPACEINDEX pfOpcUaServerGetNamespaceIndex;
	#define GET_OpcUaServerGetNamespaceIndex(fl)  s_pfCMGetAPI2( "OpcUaServerGetNamespaceIndex", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetNamespaceIndex, (fl), 0, 0)
	#define CAL_OpcUaServerGetNamespaceIndex  pfOpcUaServerGetNamespaceIndex
	#define CHK_OpcUaServerGetNamespaceIndex  (pfOpcUaServerGetNamespaceIndex != NULL)
	#define EXP_OpcUaServerGetNamespaceIndex  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetNamespaceIndex", (RTS_UINTPTR)OpcUaServerGetNamespaceIndex, 0, 0) 
#endif




/**
 * <description>Register a new namespace to the server. If the namespace is registerd already this index is retruned.</description>
 * <param name="pNamespace" type="IN">Namespace to register at the server.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
OpcUa_Int16 CDECL OpcUaServerRegisterNamespace(OpcUa_String* pNamespace);
typedef OpcUa_Int16 (CDECL * PFOPCUASERVERREGISTERNAMESPACE) (OpcUa_String* pNamespace);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERREGISTERNAMESPACE_NOTIMPLEMENTED)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerRegisterNamespace(p0)  (OpcUa_Int16)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerRegisterNamespace  FALSE
	#define EXP_OpcUaServerRegisterNamespace  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  CAL_CMGETAPI( "OpcUaServerRegisterNamespace" ) 
	#define CAL_OpcUaServerRegisterNamespace  OpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace  TRUE
	#define EXP_OpcUaServerRegisterNamespace  CAL_CMEXPAPI( "OpcUaServerRegisterNamespace" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  CAL_CMGETAPI( "OpcUaServerRegisterNamespace" ) 
	#define CAL_OpcUaServerRegisterNamespace  OpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace  TRUE
	#define EXP_OpcUaServerRegisterNamespace  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterNamespace", (RTS_UINTPTR)OpcUaServerRegisterNamespace, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerRegisterNamespace
	#define EXT_CmpOPCUAServerOpcUaServerRegisterNamespace
	#define GET_CmpOPCUAServerOpcUaServerRegisterNamespace  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerRegisterNamespace pICmpOPCUAServer->IOpcUaServerRegisterNamespace
	#define CHK_CmpOPCUAServerOpcUaServerRegisterNamespace (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerRegisterNamespace  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerRegisterNamespace
	#define EXT_OpcUaServerRegisterNamespace
	#define GET_OpcUaServerRegisterNamespace(fl)  CAL_CMGETAPI( "OpcUaServerRegisterNamespace" ) 
	#define CAL_OpcUaServerRegisterNamespace pICmpOPCUAServer->IOpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerRegisterNamespace  CAL_CMEXPAPI( "OpcUaServerRegisterNamespace" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerRegisterNamespace  PFOPCUASERVERREGISTERNAMESPACE pfOpcUaServerRegisterNamespace;
	#define EXT_OpcUaServerRegisterNamespace  extern PFOPCUASERVERREGISTERNAMESPACE pfOpcUaServerRegisterNamespace;
	#define GET_OpcUaServerRegisterNamespace(fl)  s_pfCMGetAPI2( "OpcUaServerRegisterNamespace", (RTS_VOID_FCTPTR *)&pfOpcUaServerRegisterNamespace, (fl), 0, 0)
	#define CAL_OpcUaServerRegisterNamespace  pfOpcUaServerRegisterNamespace
	#define CHK_OpcUaServerRegisterNamespace  (pfOpcUaServerRegisterNamespace != NULL)
	#define EXP_OpcUaServerRegisterNamespace  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerRegisterNamespace", (RTS_UINTPTR)OpcUaServerRegisterNamespace, 0, 0) 
#endif




/**
 * <description>Parse the index range string which is part of some OPC UA requests with arrays to a strcutred form.</description>
 * <param name="pString" type="IN">String to parse.</param>
 * <param name="pRangeArray" type="INOUT">Pointer to the arrays where to store the parsed index ranges.</param>
 * <param name="pMaxRanges" type="IN">Maximum length of the array.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
OpcUa_StatusCode CDECL OpcUaServerParseIndexRange(const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges);
typedef OpcUa_StatusCode (CDECL * PFOPCUASERVERPARSEINDEXRANGE) (const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERPARSEINDEXRANGE_NOTIMPLEMENTED)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerParseIndexRange(p0,p1,p2)  (OpcUa_StatusCode)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerParseIndexRange  FALSE
	#define EXP_OpcUaServerParseIndexRange  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  CAL_CMGETAPI( "OpcUaServerParseIndexRange" ) 
	#define CAL_OpcUaServerParseIndexRange  OpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange  TRUE
	#define EXP_OpcUaServerParseIndexRange  CAL_CMEXPAPI( "OpcUaServerParseIndexRange" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  CAL_CMGETAPI( "OpcUaServerParseIndexRange" ) 
	#define CAL_OpcUaServerParseIndexRange  OpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange  TRUE
	#define EXP_OpcUaServerParseIndexRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerParseIndexRange", (RTS_UINTPTR)OpcUaServerParseIndexRange, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerParseIndexRange
	#define EXT_CmpOPCUAServerOpcUaServerParseIndexRange
	#define GET_CmpOPCUAServerOpcUaServerParseIndexRange  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerParseIndexRange pICmpOPCUAServer->IOpcUaServerParseIndexRange
	#define CHK_CmpOPCUAServerOpcUaServerParseIndexRange (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerParseIndexRange  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerParseIndexRange
	#define EXT_OpcUaServerParseIndexRange
	#define GET_OpcUaServerParseIndexRange(fl)  CAL_CMGETAPI( "OpcUaServerParseIndexRange" ) 
	#define CAL_OpcUaServerParseIndexRange pICmpOPCUAServer->IOpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerParseIndexRange  CAL_CMEXPAPI( "OpcUaServerParseIndexRange" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerParseIndexRange  PFOPCUASERVERPARSEINDEXRANGE pfOpcUaServerParseIndexRange;
	#define EXT_OpcUaServerParseIndexRange  extern PFOPCUASERVERPARSEINDEXRANGE pfOpcUaServerParseIndexRange;
	#define GET_OpcUaServerParseIndexRange(fl)  s_pfCMGetAPI2( "OpcUaServerParseIndexRange", (RTS_VOID_FCTPTR *)&pfOpcUaServerParseIndexRange, (fl), 0, 0)
	#define CAL_OpcUaServerParseIndexRange  pfOpcUaServerParseIndexRange
	#define CHK_OpcUaServerParseIndexRange  (pfOpcUaServerParseIndexRange != NULL)
	#define EXP_OpcUaServerParseIndexRange  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerParseIndexRange", (RTS_UINTPTR)OpcUaServerParseIndexRange, 0, 0) 
#endif




/**
 * <description>This function returns the mininum sampling rate supported by the server.</description>
 **/
OpcUa_Double CDECL OpcUaServerGetMinimumSamplingRate(void);
typedef OpcUa_Double (CDECL * PFOPCUASERVERGETMINIMUMSAMPLINGRATE) (void);
#if defined(CMPOPCUASERVER_NOTIMPLEMENTED) || defined(OPCUASERVERGETMINIMUMSAMPLINGRATE_NOTIMPLEMENTED)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  ERR_NOTIMPLEMENTED
	#define CAL_OpcUaServerGetMinimumSamplingRate()  (OpcUa_Double)ERR_NOTIMPLEMENTED
	#define CHK_OpcUaServerGetMinimumSamplingRate  FALSE
	#define EXP_OpcUaServerGetMinimumSamplingRate  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  CAL_CMGETAPI( "OpcUaServerGetMinimumSamplingRate" ) 
	#define CAL_OpcUaServerGetMinimumSamplingRate  OpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate  TRUE
	#define EXP_OpcUaServerGetMinimumSamplingRate  CAL_CMEXPAPI( "OpcUaServerGetMinimumSamplingRate" ) 
#elif defined(MIXED_LINK) && !defined(CMPOPCUASERVER_EXTERNAL)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  CAL_CMGETAPI( "OpcUaServerGetMinimumSamplingRate" ) 
	#define CAL_OpcUaServerGetMinimumSamplingRate  OpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate  TRUE
	#define EXP_OpcUaServerGetMinimumSamplingRate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetMinimumSamplingRate", (RTS_UINTPTR)OpcUaServerGetMinimumSamplingRate, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate
	#define EXT_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate
	#define GET_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate  ERR_OK
	#define CAL_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate pICmpOPCUAServer->IOpcUaServerGetMinimumSamplingRate
	#define CHK_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate (pICmpOPCUAServer != NULL)
	#define EXP_CmpOPCUAServerOpcUaServerGetMinimumSamplingRate  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_OpcUaServerGetMinimumSamplingRate
	#define EXT_OpcUaServerGetMinimumSamplingRate
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  CAL_CMGETAPI( "OpcUaServerGetMinimumSamplingRate" ) 
	#define CAL_OpcUaServerGetMinimumSamplingRate pICmpOPCUAServer->IOpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate (pICmpOPCUAServer != NULL)
	#define EXP_OpcUaServerGetMinimumSamplingRate  CAL_CMEXPAPI( "OpcUaServerGetMinimumSamplingRate" ) 
#else /* DYNAMIC_LINK */
	#define USE_OpcUaServerGetMinimumSamplingRate  PFOPCUASERVERGETMINIMUMSAMPLINGRATE pfOpcUaServerGetMinimumSamplingRate;
	#define EXT_OpcUaServerGetMinimumSamplingRate  extern PFOPCUASERVERGETMINIMUMSAMPLINGRATE pfOpcUaServerGetMinimumSamplingRate;
	#define GET_OpcUaServerGetMinimumSamplingRate(fl)  s_pfCMGetAPI2( "OpcUaServerGetMinimumSamplingRate", (RTS_VOID_FCTPTR *)&pfOpcUaServerGetMinimumSamplingRate, (fl), 0, 0)
	#define CAL_OpcUaServerGetMinimumSamplingRate  pfOpcUaServerGetMinimumSamplingRate
	#define CHK_OpcUaServerGetMinimumSamplingRate  (pfOpcUaServerGetMinimumSamplingRate != NULL)
	#define EXP_OpcUaServerGetMinimumSamplingRate  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"OpcUaServerGetMinimumSamplingRate", (RTS_UINTPTR)OpcUaServerGetMinimumSamplingRate, 0, 0) 
#endif






typedef struct
{
	IBase_C *pBase;
	PFOPCUASERVERREGISTERPROVIDER IOpcUaServerRegisterProvider;
 	PFOPCUASERVERUNREGISTERPROVIDER IOpcUaServerUnRegisterProvider;
 	PFOPCUASERVERCHECKREFERENCERECURSIVE IOpcUaServerCheckReferenceRecursive;
 	PFOPCUASERVERCHECKIFREFERENCEISVALID IOpcUaServerCheckIfReferenceIsValid;
 	PFOPCUASERVERGETNAMESPACEINDEX IOpcUaServerGetNamespaceIndex;
 	PFOPCUASERVERREGISTERNAMESPACE IOpcUaServerRegisterNamespace;
 	PFOPCUASERVERPARSEINDEXRANGE IOpcUaServerParseIndexRange;
 	PFOPCUASERVERGETMINIMUMSAMPLINGRATE IOpcUaServerGetMinimumSamplingRate;
 } ICmpOPCUAServer_C;

#ifdef CPLUSPLUS
class ICmpOPCUAServer : public IBase
{
	public:
		virtual RTS_RESULT CDECL IOpcUaServerRegisterProvider(OpcUaProvider_Info* providerInterface) =0;
		virtual RTS_RESULT CDECL IOpcUaServerUnRegisterProvider(OpcUaProvider_Info* providerInterface) =0;
		virtual OpcUa_Boolean CDECL IOpcUaServerCheckReferenceRecursive(const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck) =0;
		virtual OpcUa_StatusCode CDECL IOpcUaServerCheckIfReferenceIsValid(const OpcUa_NodeId* pRefTypeId) =0;
		virtual OpcUa_Int16 CDECL IOpcUaServerGetNamespaceIndex(OpcUa_String* pNamespace) =0;
		virtual OpcUa_Int16 CDECL IOpcUaServerRegisterNamespace(OpcUa_String* pNamespace) =0;
		virtual OpcUa_StatusCode CDECL IOpcUaServerParseIndexRange(const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges) =0;
		virtual OpcUa_Double CDECL IOpcUaServerGetMinimumSamplingRate(void) =0;
};
	#ifndef ITF_CmpOPCUAServer
		#define ITF_CmpOPCUAServer static ICmpOPCUAServer *pICmpOPCUAServer = NULL;
	#endif
	#define EXTITF_CmpOPCUAServer
#else	/*CPLUSPLUS*/
	typedef ICmpOPCUAServer_C		ICmpOPCUAServer;
	#ifndef ITF_CmpOPCUAServer
		#define ITF_CmpOPCUAServer
	#endif
	#define EXTITF_CmpOPCUAServer
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPOPCUASERVERITF_H_*/
