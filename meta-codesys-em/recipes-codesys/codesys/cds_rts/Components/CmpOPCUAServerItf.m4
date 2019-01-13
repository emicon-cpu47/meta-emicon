/**
 * <interfacename>CmpOPCUAServer</interfacename>
 * <description></description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpOPCUAServer')
REF_ITF(`CmpOPCUAProviderItf.m4')

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
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerRegisterProvider',`(OpcUaProvider_Info* providerInterface)')

/**
 * <description>Unregister an already registered data provider within the OPC UA server.</description>
 * <param name="providerInterface" type="IN">Table of the provider interface.</param>
 * <result>Operation result:
 * </result>
 **/
DEF_ITF_API(`RTS_RESULT',`CDECL',`OpcUaServerUnRegisterProvider',`(OpcUaProvider_Info* providerInterface)')

/**
 * <description>Check if to follow OPCU UA referencetype ID. Since referenctype IDs may are derived only the server who knows all IDs can check this.</description>
 * <param name="pRequestedReference" type="IN">The referencetype ID the client requested.</param>
 * <param name="bIncludeSubtypes" type="IN">The flag if subtypes should be followed too. Set by the client.</param>
 * <param name="pReferenceToCheck" type="IN">The referencetype ID the compare against. Usually the referencetype ID of the current node (e.g. while browsing) in the adress space.</param>
 * <result>The function returns OpcUa_True if following the referencetype ID is allowd. OpcUa_False is returned otherwhise.</result>
 **/
DEF_ITF_API(`OpcUa_Boolean',`CDECL',`OpcUaServerCheckReferenceRecursive',`(const OpcUa_NodeId* pRequestedReference, OpcUa_Boolean bIncludeSubtypes, const OpcUa_NodeId* pReferenceToCheck)')

/**
 * <description>This funtion checks if a referencetype ID is valid.</description>
 * <param name="pRefTypeId" type="IN">Referecetype ID to check.</param>
 * <result>Returns either OpcUa_Good or OpcUa_BadRefereceTypeIdInvalid.</result>
 **/
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaServerCheckIfReferenceIsValid',`(const OpcUa_NodeId* pRefTypeId)')

/**
 * <description>Get the namespace index of the given namespace. Do not relay on constant referencetype IDs. They may depend on the registration order of different providers.</description>
 * <param name="pNamespace" type="IN">The namespace of intrest.</param>
 * <result>-1: If the namespace is not registerd yet. index: The index of the namespace. This does not change while the server is running.</result>
 **/
DEF_ITF_API(`OpcUa_Int16',`CDECL',`OpcUaServerGetNamespaceIndex',`(OpcUa_String* pNamespace)')

/**
 * <description>Register a new namespace to the server. If the namespace is registerd already this index is retruned.</description>
 * <param name="pNamespace" type="IN">Namespace to register at the server.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
DEF_ITF_API(`OpcUa_Int16',`CDECL',`OpcUaServerRegisterNamespace',`(OpcUa_String* pNamespace)')

/**
 * <description>Parse the index range string which is part of some OPC UA requests with arrays to a strcutred form.</description>
 * <param name="pString" type="IN">String to parse.</param>
 * <param name="pRangeArray" type="INOUT">Pointer to the arrays where to store the parsed index ranges.</param>
 * <param name="pMaxRanges" type="IN">Maximum length of the array.</param>
 * <result>Returns the index of the registerd namespace.</result>
 **/
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaServerParseIndexRange',`(const OpcUa_String *pString, NumericRange *pRangeArray, OpcUa_UInt32 *pMaxRanges)')

/**
 * <description>This function returns the mininum sampling rate supported by the server.</description>
 **/
DEF_ITF_API(`OpcUa_Double',`CDECL',`OpcUaServerGetMinimumSamplingRate',`(void)')
