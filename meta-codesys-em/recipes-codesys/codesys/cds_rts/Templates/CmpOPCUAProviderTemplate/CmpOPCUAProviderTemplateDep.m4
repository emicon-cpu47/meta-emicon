/**
 *  <name>Component IecVarAccess OPC UA Provider</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpOPCUAProviderTemplate')
COMPONENT_SOURCES(`CmpOPCUAProviderTemplate.c')

EXTERNAL_INCLUDES(`.',
				  `../../Components__AddOns__/CmpOPCUA/include')

COMPONENT_VERSION(`0x03050A00')
COMPONENT_VENDORID(`9999')

CATEGORY(`OPCUA')

USE_ITF(`CmpOPCUAStackItf.m4')
USE_ITF(`CmpOPCUAServerItf.m4')
USE_ITF(`SysMemItf.m4')

IMPLEMENT_ITF(`CmpOPCUAProviderItf.m4')

REQUIRED_IMPORTS(LogAdd,
SysMemAllocData,
SysMemFreeData,
OpcUaByteStringInitialize,
OpcUaByteStringClear,
OpcUaByteStringCompare,
OpcUaByteStringCopyTo,
OpcUaByteStringConcatenate,
OpcUaDateTimeUtcNow,
OpcUaEncodeableObjectCreate,
OpcUaEncodeableObjectDelete,
OpcUaEncodeableObjectCreateExtension,
OpcUaLocalizedTextInitialize,
OpcUaLocalizedTextClear,
OpcUaLocalizedTextCompare,
OpcUaLocalizedTextCopyTo,
OpcUaNodeIdInitialize,
OpcUaNodeIdClear,
OpcUaNodeIdCompare,
OpcUaNodeIdCopyTo,
OpcUaNodeIdIsNull,
OpcUaQualifiedNameInitialize,
OpcUaQualifiedNameClear,
OpcUaQualifiedNameCompare,
OpcUaQualifiedNameCopyTo,
OpcUaStringAttachCopy,
OpcUaStringAttachReadOnly,
OpcUaStringAttachToString,
OpcUaStringClear,
OpcUaStringGetRawString,
OpcUaStringInitialize,
OpcUaStringIsEmpty,
OpcUaStringIsNull,
OpcUaStringStrLen,
OpcUaStringStrSize,
OpcUaStringStrnCat,
OpcUaStringStrnCpy,
OpcUaStringStrnCmp,
OpcUaVariantInitialize,
OpcUaVariantClear,
OpcUaVariantCompare,
OpcUaVariantCopyTo,
OpcUaGetEncodableObjectType,
OpcUaServerParseIndexRange,
OpcUaServerRegisterProvider,
OpcUaServerUnRegisterProvider,
OpcUaServerGetNamespaceIndex,
OpcUaServerRegisterNamespace,
OpcUaServerCheckIfReferenceIsValid,
OpcUaServerCheckReferenceRecursive)
