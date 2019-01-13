/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		
*	Version:
*	Description:
******************************************************************************/

#ifndef STATICITF_DEF
#define STATICITF_DEF	static
#endif

#include "CmpTemplateIDs.h"
#include "CmpStd.h"
#include "CmpOpcUaProviderTemplateDep.h"

#define CLASSID_CCmpOpcUaProviderTemplate		ADDVENDORID(CMP_VENDORID, 1234)

USE_STMT

static OpcUa_Int16 s_NamespaceIndex;
static OpcUa_String s_Namespace = OPCUA_STRING_STATICINITIALIZEWITH("MyNewProvider", sizeof("MyNewProvider"));
static OpcUa_String s_ApplicationLocal = OPCUA_STRING_STATICINITIALIZEWITH("en - Us", sizeof("en-Us"));
/* Values to sample */


OpcUa_UInt32 values[2];
static OpcUa_UInt32* valueA = &values[0];
static OpcUa_UInt32* valueB = &values[1];

typedef struct
{
	OpcUa_TimestampsToReturn eTimestamps;
	OpcUa_UInt32 id;
}SamplingInfo;


static OpcUa_Boolean BrowseContextCheckAddNodes(OpcUaProvider_BrowseContext *a_pContext, OpcUa_UInt32 ui32NumToAdd);
static OpcUa_Boolean BrowseContextCheckNodes(OpcUaProvider_BrowseContext* a_pContext, OpcUa_UInt32 ui32NumOfNodes);
static OpcUa_Void BrowseContextSetUnfinishedFlag(OpcUaProvider_BrowseContext* a_pContext);
static OpcUa_ReferenceDescription* BrowseContextGetNextRefDesc(OpcUaProvider_BrowseContext* a_pContext);

#ifdef CPLUSPLUS
	static CCmpOpcUaProviderTemplate *s_pCCmpOpcUaProviderTemplate;
#endif

typedef struct
{
#ifndef CPLUSPLUS
	IBase_C base;
	ICmpOPCUAProvider_C provider;
#endif
	IBase *pIBase;
	ICmpOPCUAProvider *pIOpcUaProvider;

} OpcUaProvider_C;

static OpcUaProvider_C s_OpcUaProviderInterface;

static OpcUaProvider_Info s_OpcUaProviderInfo = {
	sizeof(s_OpcUaProviderInfo),
	sizeof(ICmpOPCUAProvider_C),
	CMP_VERSION, /* Provider version*/
	OPCUA_STRING_STATICINITIALIZEWITH(COMPONENT_NAME, sizeof(COMPONENT_NAME)),
	RTS_INVALID_HANDLE,
};


DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
	pfExportFunctions	OUT Pointer to function that exports component functions
	pfImportFunctions	OUT Pointer to function that imports functions from other components
	pfGetVersion		OUT Pointer to function to get component version
	pfRegisterAPI		IN	Pointer to component mangager function to register a api function
	pfGetAPI			IN	Pointer to component mangager function to get a api function
	pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

#ifdef CPLUSPLUS
	INIT_LOCALS_STMT;
#endif
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpOpcUaProviderTemplate);

	return ERR_OK;
}


#ifndef CPLUSPLUS

DECLARE_ADDREF
DECLARE_RELEASE
DECLARE_QUERYINTERFACE

#endif

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpOpcUaProviderTemplate)
	{
		CCmpOpcUaProviderTemplate *pCCmpOpcUaProviderTemplate = static_cast<CCmpOpcUaProviderTemplate *>(new CCmpOpcUaProviderTemplate());
		IBase *pIBase = (IBase *)pCCmpOpcUaProviderTemplate->QueryInterface(pCCmpOpcUaProviderTemplate, ITFID_IBase, pResult);
		RTS_SETRESULT(pResult, ERR_OK);
		return pIBase;
	}
#else
	if (cid == CLASSID_CCmpOpcUaProviderTemplate)
	{
		IBase *pI = &s_OpcUaProviderInterface.base;
		
		memset(&s_OpcUaProviderInterface, 0, sizeof(s_OpcUaProviderInterface));
		s_OpcUaProviderInterface.pIBase = pI;
		pI->bIEC = 0;
		pI->AddRef = AddRef;
		pI->Release = Release;
		pI->QueryInterface = QueryInterface;
		pI->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pI;
	}
#endif
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release();
	return ERR_OK;
#else
	pIBase->iRefCount--;
	if (pIBase->iRefCount == 0)
		memset(&s_OpcUaProviderInterface, 0, sizeof(s_OpcUaProviderInterface));
	return ERR_OK;
#endif
}

#if !defined(CPLUSPLUS)
IMPLEMENT_ADDREF
IMPLEMENT_RELEASE

static void *CDECL QueryInterface(IBase *pBase, ITFID iid, RTS_RESULT *pResult)
{
	if (iid == ITFID_IBase)
	{
		/* Every interface has as first element a pointer to the IBase interface. So it doesn't matter, which interface
		is used to get the IBase pointer */
		OpcUaProvider_C *pC = (OpcUaProvider_C *)pBase;
		pC->pIBase->iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return pC->pIBase;
	}
	if (iid == ITFID_ICmpOPCUAProvider)
	{
		OpcUaProvider_C *pC = (OpcUaProvider_C *)pBase;
		pC->provider.pBase = pBase;
		
		pC->provider.IOpcUaProviderCreate = OpcUaProviderCreate;
		pC->provider.IOpcUaProviderDelete = OpcUaProviderDelete;
		pC->provider.IOpcUaProviderBrowse = OpcUaProviderBrowse;
		pC->provider.IOpcUaProviderCreateMonitoredItem = OpcUaProviderCreateMonitoredItem;
		pC->provider.IOpcUaProviderDeleteMonitoredItem = OpcUaProviderDeleteMonitoredItem;
		pC->provider.IOpcUaProviderSampleMonitoredItem = OpcUaProviderSampleMonitoredItem;
		pC->provider.IOpcUaProviderInitialize = OpcUaProviderInitialize;
		pC->provider.IOpcUaProviderCleanup = OpcUaProviderCleanup;
		pC->provider.IOpcUaProviderRead = OpcUaProviderRead;
		pC->provider.IOpcUaProviderWrite = OpcUaProviderWrite;

		pC->pIOpcUaProvider = &pC->provider;
		pC->base.iRefCount++;
		RTS_SETRESULT(pResult, ERR_OK);
		return &pC->provider;
	}
	RTS_SETRESULT(pResult, ERR_FAILED);
	return NULL;
}
#endif


static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	RTS_RESULT result = ERR_OK;

	switch (ulHook)
	{
		case CH_INIT_COMM:
		{
			/* Register Provider at the OPC UA server */
			IBase *pIBase = NULL;

			CAL_OpcUaProviderCreate(pIBase, CLASSID_CCmpOpcUaProviderTemplate, 0, &result);
			s_OpcUaProviderInfo.hProvider = pIBase->QueryInterface(pIBase, ITFID_ICmpOPCUAProvider, &result);

			result = CAL_OpcUaServerRegisterProvider(&s_OpcUaProviderInfo);
			if (result != ERR_OK)
			{
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, result, 0, "The registration of the OPC UA Template provider failed!");
			}
			break;
		}
		case CH_COMM_CYCLE:
		{
			(*valueB)++;
			break;
		}
		case CH_EXIT3:
		{
			/* Unregister Provider at the OPC UA server */
			CAL_OpcUaServerUnRegisterProvider(&s_OpcUaProviderInfo);
			CAL_OpcUaProviderDelete(s_OpcUaProviderInfo.hProvider);
			break;
		}
		default:
			break;
	}
	return ERR_OK;
}


/******************************************************************************
 * Implementation of OPC UA Provider
 ******************************************************************************/

STATICITF RTS_HANDLE CDECL OpcUaProviderCreate(RTS_HANDLE hIOpcUaProvider, CLASSID ClassId, int iId, RTS_RESULT *pResult)
{
	return hIOpcUaProvider;
}

STATICITF RTS_RESULT CDECL OpcUaProviderDelete(RTS_HANDLE hOpcUaProvider)
{
	return ERR_OK;
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderInitialize(RTS_HANDLE hProvider)
{
	s_NamespaceIndex = CAL_OpcUaServerRegisterNamespace(&s_Namespace);
	return OpcUa_Good;
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderCleanup(RTS_HANDLE hProvider)
{
	return OpcUa_BadNotImplemented;
}

STATICITF OpcUa_StatusCode OpcUaProviderBrowse(RTS_HANDLE hProvider, OpcUaProvider_BrowseContext *a_pContext)
{

	OpcUa_StatusCode uStatus = OpcUa_Good;
	const OpcUa_BrowseDescription* pNodeToBrowse = a_pContext->pNodeToBrowse;
	OpcUa_NodeId reftypeid;
	int i;
	do
	{
		if (pNodeToBrowse->BrowseDirection != OpcUa_BrowseDirection_Forward)
			break;

		/* Node where to insert the childs */
		if (pNodeToBrowse->NodeId.NamespaceIndex != 0)
			break;
		if (pNodeToBrowse->NodeId.IdentifierType != OpcUa_IdentifierType_Numeric)
			break;
		if (pNodeToBrowse->NodeId.Identifier.Numeric != OpcUaId_ObjectsFolder)
			break;

		/* Check reference */
		CAL_OpcUaNodeIdInitialize(&reftypeid);
		reftypeid.Identifier.Numeric = OpcUaId_Organizes;
		reftypeid.NamespaceIndex = 0;
		reftypeid.IdentifierType = OpcUa_IdentifierType_Numeric;
		if (!CAL_OpcUaServerCheckReferenceRecursive(&pNodeToBrowse->ReferenceTypeId, pNodeToBrowse->IncludeSubtypes, &reftypeid))
			break;

		/* Check result mask */
		if ((pNodeToBrowse->NodeClassMask & OpcUa_NodeClass_Variable || pNodeToBrowse->NodeClassMask == 0) == 0)
			break;

		for (i = 0; i < sizeof(values) / sizeof(OpcUa_UInt32); i++)
		{
			/* We have two nodes to add */
			if (a_pContext->pReference == OpcUa_Null)
			{
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					break;
				}
			}
			else
			{
				if (BrowseContextCheckNodes(a_pContext, 1) == OpcUa_True)
				{
					OpcUa_ReferenceDescription* pRefDesc = OpcUa_Null;
					const OpcUa_BrowseDescription* pBrowseDesc = a_pContext->pNodeToBrowse;




					pRefDesc = BrowseContextGetNextRefDesc(a_pContext);
					if (pRefDesc != OpcUa_Null)
					{
						/* Set forward flag */
						if (pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_IsForward)
							pRefDesc->IsForward = OpcUa_True;

						/* Set Node id */
						pRefDesc->NodeId.NodeId.NamespaceIndex = s_NamespaceIndex;
						pRefDesc->NodeId.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
						pRefDesc->NodeId.NodeId.Identifier.Numeric = i;


						/* Set browse name and display name */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_BrowseName) != 0)
						{
							pRefDesc->BrowseName.NamespaceIndex = s_NamespaceIndex;
							if(i == 0)
								CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, "ValueA");
							if (i == 1)
								CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, "ValueB");
						}
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_DisplayName) != 0)
						{
							if (i == 0)
								CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, "ValueA");
							if (i == 1)
								CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, "ValueB");
							CAL_OpcUaStringStrnCpy(&pRefDesc->DisplayName.Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
						}

						/* Set reference type */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_ReferenceTypeId) != 0)
						{
							CAL_OpcUaNodeIdCopyTo(&reftypeid, &pRefDesc->ReferenceTypeId);
						}

						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_NodeClass) != 0)
							pRefDesc->NodeClass = OpcUa_NodeClass_Variable;

						/* Set type definition of node */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_TypeDefinition) != 0)
						{
							pRefDesc->TypeDefinition.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
							pRefDesc->TypeDefinition.NodeId.Identifier.Numeric = (OpcUa_UInt32)OpcUaId_UInt32;
							pRefDesc->TypeDefinition.NodeId.NamespaceIndex = 0;
							pRefDesc->TypeDefinition.ServerIndex = 0;
						}
					}
				}
				else
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					break;
				}
			}
		}

	} while (0);
	
	return uStatus;
	
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderCreateMonitoredItem(RTS_HANDLE hProvider, OpcUaProvider_CreateMonitoredItemContext *a_pContext)
{
	OpcUa_StatusCode uStatus = OpcUa_BadNodeIdUnknown;
	OpcUa_UInt32 attributeId = a_pContext->pItemToCreate->AttributeId;
	const OpcUa_NodeId* pNodeId = &a_pContext->pItemToCreate->NodeId;
	OpcUaProvider_ReadContext readContext;
	if (attributeId != OpcUa_Attributes_Value)
	{
		uStatus = OpcUa_BadAttributeIdInvalid;
		return uStatus;
	}
	readContext.eTimestampsToReturn = OpcUa_TimestampsToReturn_Server;
	readContext.pNodeToRead = a_pContext->pItemToCreate;
	readContext.pDataValue = a_pContext->pValue;
	uStatus = OpcUaProviderRead(hProvider, &readContext);
	if(uStatus == OpcUa_Good)
	{
		SamplingInfo* pInfo;
		a_pContext->pProviderInformation = CAL_SysMemAllocData(COMPONENT_NAME, sizeof(SamplingInfo), NULL);
		pInfo = (SamplingInfo*)a_pContext->pProviderInformation;
		pInfo->id = pNodeId->Identifier.Numeric;


	}
	return uStatus;	
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderDeleteMonitoredItem(RTS_HANDLE hProvider, OpcUaProvider_DeleteMonitoredItemContext *a_pContext)
{
	CAL_SysMemFreeData(COMPONENT_NAME, a_pContext->pProviderInformation);
	return OpcUa_Good;
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderSampleMonitoredItem(RTS_HANDLE hProvider, OpcUaProvider_SampleMonitoredItemContext *a_pContext)
{
	SamplingInfo* pInfo = (SamplingInfo*)a_pContext->pProviderInformation;
	a_pContext->pDataValue->SourceTimestamp = CAL_OpcUaDateTimeUtcNow();
	if (pInfo->id == 0)
		a_pContext->pDataValue->Value.Value.UInt32 = *valueA;
	if (pInfo->id == 1)
		a_pContext->pDataValue->Value.Value.UInt32 = *valueB;
	return OpcUa_Good;
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderRead(RTS_HANDLE hProvider, OpcUaProvider_ReadContext *a_pContext)
{
	OpcUa_StatusCode uStatus = OpcUa_BadNodeIdUnknown;
	OpcUa_Variant *pValue = &a_pContext->pDataValue->Value;
	OpcUa_UInt32 uAttributeId = a_pContext->pNodeToRead->AttributeId;
	OpcUa_TimestampsToReturn eTimestampsToReturn = a_pContext->eTimestampsToReturn;
	const OpcUa_NodeId* pNode = &a_pContext->pNodeToRead->NodeId;

	do
	{
		if (pNode->IdentifierType != OpcUa_IdentifierType_Numeric)
			break;
		if (pNode->NamespaceIndex != s_NamespaceIndex)
			break;
		if (pNode->Identifier.Numeric != 0 && pNode->Identifier.Numeric != 1)
			break;

		switch (uAttributeId)
		{
			/* Read attributes contained in all node classes */
			case OpcUa_Attributes_NodeId:
			{
				pValue->Datatype = (OpcUa_Byte)OpcUaType_NodeId;
				pValue->Value.NodeId = (OpcUa_NodeId*)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(OpcUa_NodeId), NULL);
				CAL_OpcUaNodeIdInitialize(pValue->Value.NodeId);
				uStatus = CAL_OpcUaNodeIdCopyTo(&a_pContext->pNodeToRead->NodeId, pValue->Value.NodeId);
				break;
			}
			case OpcUa_Attributes_NodeClass:
			{
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Int32;
				uStatus = OpcUa_Good;
				pValue->Value.Int32 = (OpcUa_Int32)OpcUa_NodeClass_Variable;
				break;
			}
			case OpcUa_Attributes_BrowseName:
			{
				pValue->Datatype = (OpcUa_Byte)OpcUaType_QualifiedName;
				pValue->Value.QualifiedName = (OpcUa_QualifiedName*)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(OpcUa_QualifiedName), NULL);
				CAL_OpcUaQualifiedNameInitialize(pValue->Value.QualifiedName);
				pValue->Value.QualifiedName->NamespaceIndex = s_NamespaceIndex;
				if(pNode->Identifier.Numeric == 0)
					uStatus = CAL_OpcUaStringAttachReadOnly(&pValue->Value.QualifiedName->Name, "ValueA");
				if(pNode->Identifier.Numeric == 1)
					uStatus = CAL_OpcUaStringAttachReadOnly(&pValue->Value.QualifiedName->Name, "ValueB");
				break;
			}
			case OpcUa_Attributes_DisplayName:
			{
				pValue->Datatype = (OpcUa_Byte)OpcUaType_LocalizedText;
				pValue->Value.LocalizedText = (OpcUa_LocalizedText*)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(OpcUa_LocalizedText), NULL);
				CAL_OpcUaLocalizedTextInitialize(pValue->Value.LocalizedText);
				CAL_OpcUaStringStrnCpy(&pValue->Value.LocalizedText->Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
				if (pNode->Identifier.Numeric == 0)
					CAL_OpcUaStringAttachReadOnly(&pValue->Value.LocalizedText->Text, "ValueA");
				if (pNode->Identifier.Numeric == 1)
					CAL_OpcUaStringAttachReadOnly(&pValue->Value.LocalizedText->Text, "ValueB");
				uStatus = OpcUa_Good;
				break;
			}
			case OpcUa_Attributes_Description:
			{
				uStatus = OpcUa_BadAttributeIdInvalid;
				break;
			}
			case OpcUa_Attributes_WriteMask:
			{
				pValue->Datatype = (OpcUa_Byte)OpcUaType_UInt32;
				pValue->Value.UInt32 = 0;
				uStatus = OpcUa_Good;
				break;
			}
			case OpcUa_Attributes_UserWriteMask:
			{
				pValue->Datatype = (OpcUa_Byte)OpcUaType_UInt32;
				pValue->Value.UInt32 = 0;
				uStatus = OpcUa_Good;
				break;
			}

			case OpcUa_Attributes_Value:
			{
				OpcUa_Variant* pVariant = &a_pContext->pDataValue->Value;
				if (eTimestampsToReturn == OpcUa_TimestampsToReturn_Both || eTimestampsToReturn == OpcUa_TimestampsToReturn_Server)
				{
					a_pContext->pDataValue->ServerTimestamp = CAL_OpcUaDateTimeUtcNow();
				}
				if (eTimestampsToReturn == OpcUa_TimestampsToReturn_Both || eTimestampsToReturn == OpcUa_TimestampsToReturn_Source)
				{
					a_pContext->pDataValue->SourceTimestamp = a_pContext->pDataValue->ServerTimestamp;
				}
				pVariant->ArrayType = OpcUa_VariantArrayType_Scalar;
				pVariant->Datatype = (OpcUa_Byte)OpcUaType_UInt32;
				if (pNode->Identifier.Numeric == 0)
					pVariant->Value.UInt32 = *valueA;
				if (pNode->Identifier.Numeric == 1)
					pVariant->Value.UInt32 = *valueB;
				uStatus = OpcUa_Good;
				break;
			}
			case OpcUa_Attributes_DataType:
				pValue->Datatype = (OpcUa_Byte)OpcUaType_NodeId;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.NodeId = (OpcUa_NodeId*)CAL_SysMemAllocData(COMPONENT_NAME, sizeof(OpcUa_NodeId), NULL);
				CAL_OpcUaNodeIdInitialize(pValue->Value.NodeId);
				pValue->Value.NodeId->IdentifierType = OpcUa_IdentifierType_Numeric;
				pValue->Value.NodeId->NamespaceIndex = 0;
				pValue->Value.NodeId->Identifier.Numeric = (OpcUa_UInt32)OpcUaId_UInt32;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_ValueRank:
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Int32;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Int32 = OpcUa_ValueRanks_Scalar;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_AccessLevel:
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Byte;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Byte = OpcUa_AccessLevels_CurrentRead | OpcUa_AccessLevels_CurrentWrite;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_UserAccessLevel:
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Byte;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Byte = OpcUa_AccessLevels_CurrentRead | OpcUa_AccessLevels_CurrentWrite;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_Historizing:
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Boolean;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Boolean = OpcUa_False;
				uStatus = OpcUa_Good;
				break;
			default:
				uStatus = OpcUa_BadAttributeIdInvalid;
				break;
		}
	} while (0);
	a_pContext->pDataValue->StatusCode = uStatus;
	return uStatus;
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderWrite(RTS_HANDLE hProvider, OpcUaProvider_WriteContext *a_pContext)
{
	OpcUa_StatusCode uStatus = OpcUa_BadNodeIdUnknown;
	const OpcUa_NodeId* pNode = &a_pContext->pNodeToWrite->NodeId;
	OpcUa_UInt32 attributeId = a_pContext->pNodeToWrite->AttributeId;
	const OpcUa_DataValue* pValue = &a_pContext->pNodeToWrite->Value;
	do
	{
		if (pNode->IdentifierType != OpcUa_IdentifierType_Numeric)
			break;
		if (pNode->NamespaceIndex != s_NamespaceIndex)
			break;
		if (pNode->Identifier.Numeric != 0 && pNode->Identifier.Numeric != 1)
			break;
		switch (attributeId)
		{
			case OpcUa_Attributes_Value:
			{
				if (pValue->Value.Datatype == (OpcUa_Byte)OpcUaType_UInt32)
				{
					if (pNode->Identifier.Numeric == 0)
						*valueA = pValue->Value.Value.UInt32;
					if (pNode->Identifier.Numeric == 1)
						*valueB = pValue->Value.Value.UInt32;
					uStatus = OpcUa_Good;
				}
				else
				{
					uStatus = OpcUa_BadNotWritable;
				}
			}
			break;
			default:
				uStatus = OpcUa_BadNotWritable;
				break;
		}
	} while (0);
	return uStatus;
}

/* Checks if the needed amount of nodes can be added and adds them to the result.*/
static OpcUa_Boolean BrowseContextCheckAddNodes(OpcUaProvider_BrowseContext *a_pContext, OpcUa_UInt32 ui32NumToAdd)
{
	if ((a_pContext->ui32NumNodes + ui32NumToAdd) <= a_pContext->ui32MaxNumOfResults)
	{
		a_pContext->ui32NumNodes += ui32NumToAdd;
		return OpcUa_True;
	}
	else
	{
		return OpcUa_False;
	}
}

/* Checks if the needed amount of nodes can be added to the result. */
static OpcUa_Boolean BrowseContextCheckNodes(OpcUaProvider_BrowseContext* a_pContext, OpcUa_UInt32 ui32NumOfNodes)
{
	if ((a_pContext->ui32CurrentNode + ui32NumOfNodes) <= a_pContext->ui32MaxNumOfResults)
	{
		return OpcUa_True;
	}
	else
	{
		return OpcUa_False;
	}
}

static OpcUa_Void BrowseContextSetUnfinishedFlag(OpcUaProvider_BrowseContext* a_pContext)
{
	a_pContext->bFinished = OpcUa_False;
	a_pContext->hProviderContinueInfo = NULL;
}

static OpcUa_ReferenceDescription* BrowseContextGetNextRefDesc(OpcUaProvider_BrowseContext* a_pContext)
{
	OpcUa_ReferenceDescription* pResult = OpcUa_Null;
	if (a_pContext->ui32CurrentNode <= a_pContext->ui32NumNodes)
	{
		pResult = &a_pContext->pReference[a_pContext->ui32CurrentNode];
		a_pContext->ui32CurrentNode++;
	}
	return pResult;
}