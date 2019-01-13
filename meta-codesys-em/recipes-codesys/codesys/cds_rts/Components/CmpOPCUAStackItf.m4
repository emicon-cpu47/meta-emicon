/**
 * <interfacename>CmpOPCUAStack</interfacename>
 * <description></description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
 
/*
 * This interface publishes the functions of the OPC UA Foundation stack that are needed by the OPC UA Providers.
 */

SET_INTERFACE_NAME(`CmpOPCUAStack')

/* OPC UA Stack header files */
#include "opcua.h"
#include "opcua_list.h"
#include "opcua_endpoint.h"
#include "opcua_timer.h"

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Enable tracing of OPC UA component. Select 0 to disable and 1 to enable tracing</description>
 */
#define CMPOPCUAKEY_INT_TRACE_ENABLE				"EnableTrace"
#ifndef CMPOPCUAVALUE_INT_TRACE_ENABLE_DEFAULT
	#define CMPOPCUAVALUE_INT_TRACE_ENABLE_DEFAULT	1
#endif

/**
 * <category>Settings</category>
 * <type>Int</type>
 * <description>Set the trace level. Select out of the following values. Add them to select multiple values.
 * Trace Content:   0x1
 * Trace Debug:     0x2
 * Trace Info:      0x4
 * Trace System:    0x8
 * Trace Warning:   0x10
 * Trace Error:     0x20
 * Trace Datetime:  0x80
 * Trace Mutex:     0x100
 * Trace Semaphore: 0x200
 * Trace Memory:    0x400
 * Trace Seocket:   0x800
 * </description>
 */
#define CMPOPCUAKEY_INT_TRACE_LEVEL					"TraceLevel"
#ifndef CMPOPCUAVALUE_INT_TRACE_LEVEL_DEFAULT
	#define CMPOPCUAVALUE_INT_TRACE_LEVEL_DEFAULT	(OPCUA_TRACE_LEVEL_ERROR | OPCUA_TRACE_LEVEL_WARNING)
#endif

#define CAL_OpcUaStringCompare(xValue1, xValue2) CAL_OpcUaStringStrnCmp(xValue1, xValue2, OPCUA_STRING_LENDONTCARE, OpcUa_False)
#define CAL_OpcUaStringCopyTo(xSource, xDestination) CAL_OpcUaStringStrnCpy(xDestination, xSource, OPCUA_STRING_LENDONTCARE)

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaByteStringInitialize',`(OpcUa_ByteString* value)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaByteStringClear',`(OpcUa_ByteString* value)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaByteStringCompare',`(const OpcUa_ByteString* value1, const OpcUa_ByteString* value2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaByteStringCopyTo',`(const OpcUa_ByteString* source, OpcUa_ByteString* destination)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaByteStringConcatenate',`(const OpcUa_ByteString* source, OpcUa_ByteString* destination, OpcUa_Int len)')

DEF_ITF_API(`OpcUa_DateTime',`CDECL',`OpcUaDateTimeUtcNow',`(void)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEncodeableObjectCreate',`(OpcUa_EncodeableType* pType, OpcUa_Void** ppEncodeable)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaEncodeableObjectDelete',`(OpcUa_EncodeableType* pType, OpcUa_Void** ppEncodeable)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEncodeableObjectCreateExtension',`(OpcUa_EncodeableType* pType, OpcUa_ExtensionObject* pExtension, OpcUa_Void** ppEncodeableObject)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaLocalizedTextInitialize',`(OpcUa_LocalizedText* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaLocalizedTextClear',`(OpcUa_LocalizedText* pValue)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaLocalizedTextCompare',`(const OpcUa_LocalizedText* pValue1, const OpcUa_LocalizedText* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaLocalizedTextCopyTo',`(const OpcUa_LocalizedText* pSource, OpcUa_LocalizedText* pDestination)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaNodeIdInitialize',`(OpcUa_NodeId* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaNodeIdClear',`(OpcUa_NodeId* pValue)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaNodeIdCompare',`(const OpcUa_NodeId* pValue1, const OpcUa_NodeId* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaNodeIdCopyTo',`(const OpcUa_NodeId* pSource, OpcUa_NodeId* pDestination)')
DEF_ITF_API(`OpcUa_Boolean',`CDECL',`OpcUaNodeIdIsNull',`(OpcUa_NodeId* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaExpandedNodeIdInitialize',`(OpcUa_ExpandedNodeId* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaExpandedNodeIdClear',`(OpcUa_ExpandedNodeId* pValue)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaExpandedNodeIdCompare',`(const OpcUa_ExpandedNodeId* pValue1, const OpcUa_ExpandedNodeId* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaExpandedNodeIdCopyTo',`(const OpcUa_ExpandedNodeId* pSource, OpcUa_ExpandedNodeId* pDestination)')
DEF_ITF_API(`OpcUa_Boolean',`CDECL',`OpcUaExpandedNodeIdIsNull',`(OpcUa_ExpandedNodeId* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaQualifiedNameInitialize',`(OpcUa_QualifiedName* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaQualifiedNameClear',`(OpcUa_QualifiedName* pValue)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaQualifiedNameCompare',`(const OpcUa_QualifiedName* pValue1, const OpcUa_QualifiedName* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaQualifiedNameCopyTo',`(const OpcUa_QualifiedName* pSource, OpcUa_QualifiedName* pDestination)')

DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaStringAttachCopy',`(OpcUa_String* pDst, const OpcUa_CharA* pSrc)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaStringAttachReadOnly',`(OpcUa_String* a_pDst, const OpcUa_CharA* a_pSrc)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaStringAttachToString',`(OpcUa_StringA strSource, OpcUa_UInt32  uLength, OpcUa_UInt32  uBufferSize, OpcUa_Boolean bDoCopy, OpcUa_Boolean bFreeOnClear, OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaStringClear',`(OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_CharA*',`CDECL',`OpcUaStringGetRawString',`(const OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaStringInitialize',`(OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_Boolean',`CDECL',`OpcUaStringIsEmpty',`(const OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_Boolean',`CDECL',`OpcUaStringIsNull',`(const OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_UInt32',`CDECL',`OpcUaStringStrLen',`(const OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_UInt32',`CDECL',`OpcUaStringStrSize',`(const OpcUa_String* pString)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaStringStrnCat',`(OpcUa_String* pDestString, const OpcUa_String* pSrcString, OpcUa_UInt32 uLength)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaStringStrnCpy',`(OpcUa_String* pDestString, const OpcUa_String* pSrcString, OpcUa_UInt32 uLength)')
DEF_ITF_API(`OpcUa_Int32',`CDECL',`OpcUaStringStrnCmp',`(const OpcUa_String* a_pLeftString, const OpcUa_String* a_pRightString,OpcUa_UInt32 a_uLength, OpcUa_Boolean a_bIgnoreCase)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaVariantInitialize',`(OpcUa_Variant* value)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaVariantClear',`(OpcUa_Variant* value)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaVariantCompare',`(const OpcUa_Variant* pValue1, const OpcUa_Variant* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaVariantCopyTo',`(const OpcUa_Variant* pSource, OpcUa_Variant* pDestination)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaDataValueInitialize',`(OpcUa_DataValue* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaDataValueClear',`(OpcUa_DataValue* pValue)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaDataValueCompare',`(const OpcUa_DataValue* pValue1, const OpcUa_DataValue* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaDataValueCopyTo',`(const OpcUa_DataValue* pSource, OpcUa_DataValue* pDestination)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaExtensionObjectCreate',`(OpcUa_ExtensionObject** ppValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaExtensionObjectInitialize',`(OpcUa_ExtensionObject* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaExtensionObjectClear',`(OpcUa_ExtensionObject* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaExtensionObjectDelete',`(OpcUa_ExtensionObject** ppValue)')
DEF_ITF_API(`OpcUa_Int',`CDECL',`OpcUaExtensionObjectCompare',`(const OpcUa_ExtensionObject* pValue1, const OpcUa_ExtensionObject* pValue2)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaExtensionObjectCopyTo',`(const OpcUa_ExtensionObject* pSource, OpcUa_ExtensionObject* pDestination)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaReadValueIdInitialize',`(OpcUa_ReadValueId* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaReadValueIdClear',`(OpcUa_ReadValueId* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowseDescriptionInitialize',`(OpcUa_BrowseDescription* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowseDescriptionClear',`(OpcUa_BrowseDescription* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowsePathInitialize',`(OpcUa_BrowsePath* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowsePathClear',`(OpcUa_BrowsePath* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaStatusChangeNotificationInitialize',`(OpcUa_StatusChangeNotification* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaStatusChangeNotificationClear',`(OpcUa_StatusChangeNotification* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaNotificationMessageInitialize',`(OpcUa_NotificationMessage* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaNotificationMessageClear',`(OpcUa_NotificationMessage* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaPublishResponseInitialize',`(OpcUa_PublishResponse* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaPublishResponseClear',`(OpcUa_PublishResponse* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaDataChangeNotificationInitialize',`(OpcUa_DataChangeNotification* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaDataChangeNotificationClear',`(OpcUa_DataChangeNotification* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowseResultInitialize',`(OpcUa_BrowseResult* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowseResultClear',`(OpcUa_BrowseResult* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowsePathResultInitialize',`(OpcUa_BrowsePathResult* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaBrowsePathResultClear',`(OpcUa_BrowsePathResult* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaReferenceDescriptionInitialize',`(OpcUa_ReferenceDescription* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaReferenceDescriptionClear',`(OpcUa_ReferenceDescription* pValue)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaUserTokenPolicyInitialize',`(OpcUa_UserTokenPolicy* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaUserTokenPolicyClear',`(OpcUa_UserTokenPolicy* pValue)')

DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListCreate',`(OpcUa_List** ppList)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListInitialize',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaListClear',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaListDelete',`(OpcUa_List** ppList)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaListEnter',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaListLeave',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListAddElement',`(OpcUa_List* pList, OpcUa_Void* pElementData)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListAddElementToEnd',`(OpcUa_List* pList, OpcUa_Void* pElementData)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListInsertElement',`(OpcUa_List* pList, OpcUa_Void* pElementData)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListResetCurrent',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void*',`CDECL',`OpcUaListGetNextElement',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void*',`CDECL',`OpcUaListGetCurrentElement',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void*',`CDECL',`OpcUaListGetPrevElement',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_Void*',`CDECL',`OpcUaListGetElement',`(OpcUa_List* pList, OpcUa_Void* pElementData)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaListDeleteCurrentElement',`(OpcUa_List* pList)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListDeleteElement',`(OpcUa_List* pList, OpcUa_Void* pElementData)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaListGetNumberOfElements',`(OpcUa_List* pList, OpcUa_UInt32* uintElementCount)')
DEF_ITF_API(`OpcUa_Void*',`CDECL',`OpcUaListRemoveFirstElement',`(OpcUa_List* pList)')

DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaEndpointDescriptionInitialize',`(OpcUa_EndpointDescription* pValue)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaEndpointDescriptionClear',`(OpcUa_EndpointDescription* pValue)')

DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointBeginSendResponse',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle hContext, OpcUa_Void** ppResponse, OpcUa_EncodeableType** ppResponseType)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointCancelSendResponse',`(OpcUa_Endpoint hEndpoint, OpcUa_StatusCode uStatus, OpcUa_String* psReason, OpcUa_Handle* hContext)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointClose',`(OpcUa_Endpoint hEndpoint)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointCreate',`(OpcUa_Endpoint* phEndpoint, OpcUa_Endpoint_SerializerType eSerializerType, OpcUa_ServiceType** pSupportedServices)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaEndpointDelete',`(OpcUa_Endpoint* phEndpoint)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointEndSendResponse',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle* hContext, OpcUa_StatusCode uStatusCode, OpcUa_Void* pResponse, OpcUa_EncodeableType* pResponseType)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointGetMessageSecureChannelId',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle hContext, OpcUa_UInt32* pSecureChannelId)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointGetMessageSecureChannelSecurityPolicy',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle hContext, OpcUa_Endpoint_SecurityPolicyConfiguration* pSecurityPolicy)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointOpen',`(OpcUa_Endpoint hEndpoint, OpcUa_StringA sUrl, OpcUa_StringA sTransportProfileUri, OpcUa_Endpoint_PfnEndpointCallback* pfEndpointCallback, OpcUa_Void* pvEndpointCallbackData, OpcUa_ByteString* pServerCertificate, OpcUa_Key* pServerPrivateKey, OpcUa_Void* pPKIConfig, OpcUa_UInt32 nNoOfSecurityPolicies, OpcUa_Endpoint_SecurityPolicyConfiguration* pSecurityPolicies)')
DEF_ITF_API(`OpcUa_Void',`CDECL',`OpcUaEndpointSendErrorResponse',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle hContext, OpcUa_StatusCode uStatus)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointGetServiceFunction',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle hContext, OpcUa_PfnInvokeService** ppInvoke)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointUpdateServiceFunctions',`(OpcUa_Endpoint hEndpoint, OpcUa_UInt32 uRequestTypeId, OpcUa_PfnBeginInvokeService* pBeginInvoke, OpcUa_PfnInvokeService* pInvoke)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointGetCallbackData',`(OpcUa_Endpoint hEndpoint, OpcUa_Void** ppvCallbackData)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointGetPeerInfoFromContext',`(OpcUa_Endpoint hEndpoint, OpcUa_Handle hContext, OpcUa_String* psPeerInfo)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointGetPeerInfoBySecureChannelId',`(OpcUa_Endpoint hEndpoint, OpcUa_UInt32 uSecureChannelId, OpcUa_String* psPeerInfo)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaEndpointCloseSecureChannel',`(OpcUa_Endpoint hEndpoint, OpcUa_UInt32 uSecureChannelId, OpcUa_StatusCode uStatus)')

DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaTimerCreate',`(OpcUa_Timer* hTimer, OpcUa_UInt32 msecInterval, OpcUa_Timer_Callback* fpTimerCallback, OpcUa_Timer_Callback* fpKillCallback, OpcUa_Void* pvCallbackData)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaTimerDelete',`(OpcUa_Timer* phTimer)')

DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaSocketManagerLoop',`(OpcUa_SocketManager pSocketManager, OpcUa_UInt32 msecTimeout, OpcUa_Boolean bRunOnce)')
DEF_ITF_API(`OpcUa_StatusCode',`CDECL',`OpcUaServerApiCreateFault',`(OpcUa_RequestHeader* pRequestHeader, OpcUa_StatusCode uServiceResult, OpcUa_DiagnosticInfo* pServiceDiagnostics, OpcUa_Int32* pNoOfStringTable, OpcUa_String** ppStringTable, OpcUa_Void** ppFault, OpcUa_EncodeableType** ppFaultType)')

/**
 * <description>Get the adress of an encodable object type description. This adress can be passed directly to OpcUaEncodableObjectCreate or OpcUaEncodableObjectCreateExtension.
 * As ui32TypeId use the OpcUaId_... Macros. If the type is not available the function will return NULL.</description>
 */
DEF_ITF_API(`OpcUa_EncodeableType*',`CDECL',`OpcUaGetEncodableObjectType',`(OpcUa_UInt32 ui32TypeId)')
DEF_ITF_API(`OpcUa_PfnBeginInvokeService*',`CDECL',`OpcUaGetBeginServiceFunction',`(OpcUa_UInt32 ui32ServiceId)')

