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
static RTS_HANDLE s_hEventNotifier = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEvent = RTS_INVALID_HANDLE;

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
	COMPONENT_ID
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
			if ((*valueB % 100) == 0)
			{
				OpcUa_Variant evt_values[6];
				OpcUa_ByteString EventId;
				OpcUa_NodeId SourceNode;
				OpcUa_LocalizedText Message;
				OpcUa_String SourceName;
				OpcUa_DateTime Time = CAL_OpcUaDateTimeUtcNow();
				OpcUa_UInt16 Severity = (*valueB % 1000 ) + 1; /* Apply severity range between 1 and 1000 */

				/*
				 *  1. EventId: Unique Id of the event : Datatype : OpcUa_ByteString
				 *  2. SourceNode : NodeId of the event source node.Datatype : OpcUa_NodeId
				 *  3. SourceName : Name of the event source.Datatype : OpcUa_String
				 *  4. Time : UtcTimestamp when the event occured.Datatype : OpcUa_UtcTime
				 *  5. Message : Message of the event.Datatype : OpcUa_LocalizedText
				 *  6. Severity : Severity of the event.Datatype : OpcUa_UInt16.Range from 1 to 1000 is allowed< / param>
				 */
				memset(evt_values, 0, sizeof(evt_values));
				memset(&EventId, 0, sizeof(EventId));
				memset(&SourceNode, 0, sizeof(SourceNode));
				memset(&Message, 0, sizeof(Message));
				memset(&SourceName, 0, sizeof(SourceName));

				EventId.Data = (OpcUa_Byte*)valueB;
				EventId.Length = sizeof(*valueB);

				SourceNode.Identifier.Numeric = 1001;
				SourceNode.NamespaceIndex = s_NamespaceIndex;

				CAL_OpcUaStringAttachReadOnly(&Message.Locale, "en-Us");
				CAL_OpcUaStringAttachReadOnly(&Message.Text, "Sample event provided by MyFolder of CmpOpcUaProviderTemplate!!!");

				CAL_OpcUaStringAttachReadOnly(&SourceName, "MyFolder");

				evt_values[0].Datatype = (OpcUa_Byte)OpcUaType_ByteString;
				evt_values[0].Value.ByteString = EventId;

				evt_values[1].Datatype = (OpcUa_Byte)OpcUaType_NodeId;
				evt_values[1].Value.NodeId = &SourceNode;

				evt_values[2].Datatype = (OpcUa_Byte)OpcUaType_String;
				evt_values[2].Value.String = SourceName;

				evt_values[3].Datatype = (OpcUa_Byte)OpcUaType_DateTime;
				evt_values[3].Value.DateTime = Time;

				evt_values[4].Datatype = (OpcUa_Byte)OpcUaType_LocalizedText;
				evt_values[4].Value.LocalizedText = &Message;


				evt_values[5].Datatype = (OpcUa_Byte)OpcUaType_UInt16;
				evt_values[5].Value.UInt16 = Severity;



				CAL_OpcUaServerFireEvent(s_hEventNotifier, s_hEvent, evt_values);
			}
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
	RTS_RESULT Result = ERR_OK;
	s_NamespaceIndex = CAL_OpcUaServerRegisterNamespace(&s_Namespace);
	OpcUa_NodeId nodeId;
	OpcUa_NodeId serverNode;
	OpcUa_NodeId baseEventType;

	memset(&nodeId, 0, sizeof(nodeId));
	memset(&serverNode, 0, sizeof(serverNode));
	memset(&baseEventType, 0, sizeof(baseEventType));

	nodeId.IdentifierType = OpcUa_IdentifierType_Numeric;
	nodeId.NamespaceIndex = s_NamespaceIndex;
	nodeId.Identifier.Numeric = 1001;

	serverNode.IdentifierType = OpcUa_IdentifierType_Numeric;
	serverNode.NamespaceIndex = 0;
	serverNode.Identifier.Numeric = OpcUaId_Server;

	baseEventType.IdentifierType = OpcUa_IdentifierType_Numeric;
	baseEventType.NamespaceIndex = 0;
	baseEventType.Identifier.Numeric = OpcUaId_BaseEventType;

	s_hEventNotifier = CAL_OpcUaServerRegisterEventNotifier(&nodeId, &serverNode, &Result);
	s_hEvent = CAL_OpcUaServerRegisterEvent(&s_OpcUaProviderInfo, &baseEventType, 0, NULL, &Result);
	return OpcUa_Good;
}

STATICITF OpcUa_StatusCode CDECL OpcUaProviderCleanup(RTS_HANDLE hProvider)
{
	CAL_OpcUaServerUnregisterEvent(s_hEvent);
	CAL_OpcUaServerUnregisterEventNotifier(s_hEventNotifier);
	return OpcUa_Good;
}

OpcUa_StatusCode BrowseObjectsNode(OpcUaProvider_BrowseContext *a_pContext)
{
	OpcUa_StatusCode uStatus = OpcUa_BadNodeIdUnknown;
	const OpcUa_BrowseDescription* pNodeToBrowse = a_pContext->pNodeToBrowse;
	OpcUa_NodeId reftypeid;

	CAL_OpcUaNodeIdInitialize(&reftypeid);
	reftypeid.Identifier.Numeric = OpcUaId_Organizes;
	reftypeid.NamespaceIndex = 0;
	reftypeid.IdentifierType = OpcUa_IdentifierType_Numeric;

	if (!CAL_OpcUaServerCheckReferenceRecursive(&pNodeToBrowse->ReferenceTypeId, pNodeToBrowse->IncludeSubtypes, &reftypeid))
		return OpcUa_BadNodeIdUnknown;

	/* Check result mask */
	if ((pNodeToBrowse->NodeClassMask & OpcUa_NodeClass_Variable | OpcUa_NodeClass_Object || pNodeToBrowse->NodeClassMask == 0) == 0)
		return OpcUa_BadNodeIdUnknown;

	/* Check browse direction */
	if (pNodeToBrowse->BrowseDirection == OpcUa_BrowseDirection_Inverse)
		return OpcUa_BadNodeIdUnknown;

	/* Add variable nodes */
	if (pNodeToBrowse->NodeClassMask & OpcUa_NodeClass_Variable || pNodeToBrowse->NodeClassMask == 0)
	{
		int i;
		uStatus = OpcUa_Good;
		for (i = 0; i < sizeof(values) / sizeof(OpcUa_UInt32); i++)
		{
			/* We have two nodes to add */
			if (a_pContext->pReference == OpcUa_Null)
			{
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
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
							if (i == 0)
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
				}
			}
		}
	}
	/* Add object node */
	if (pNodeToBrowse->NodeClassMask & OpcUa_NodeClass_Object || pNodeToBrowse->NodeClassMask == 0)
	{
		uStatus = OpcUa_Good;
		if (a_pContext->pReference == OpcUa_Null)
		{
			if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
			{
				BrowseContextSetUnfinishedFlag(a_pContext);
				return uStatus;
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
					pRefDesc->NodeId.NodeId.Identifier.Numeric = 1001;


					/* Set browse name and display name */
					if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_BrowseName) != 0)
					{
						pRefDesc->BrowseName.NamespaceIndex = s_NamespaceIndex;
						CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, "MyFolder");
					}
					if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_DisplayName) != 0)
					{
						CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, "MyFolder");
						CAL_OpcUaStringStrnCpy(&pRefDesc->DisplayName.Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
					}

					/* Set reference type */
					if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_ReferenceTypeId) != 0)
					{
						CAL_OpcUaNodeIdCopyTo(&reftypeid, &pRefDesc->ReferenceTypeId);
					}
				}
				if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_TypeDefinition) != 0)
				{
					pRefDesc->TypeDefinition.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
					pRefDesc->TypeDefinition.NodeId.Identifier.Numeric = (OpcUa_UInt32)OpcUaId_FolderType;
					pRefDesc->TypeDefinition.NodeId.NamespaceIndex = 0;
					pRefDesc->TypeDefinition.ServerIndex = 0;
				}

				if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_NodeClass) != 0)
					pRefDesc->NodeClass = OpcUa_NodeClass_Object;
			}
			else
			{
				BrowseContextSetUnfinishedFlag(a_pContext);
				return uStatus;
			}
		}
	}
	return uStatus;
}

OpcUa_StatusCode BrowseServerNode(OpcUaProvider_BrowseContext *a_pContext)
{
	OpcUa_StatusCode uStatus = OpcUa_BadNodeIdUnknown;
	const OpcUa_BrowseDescription* pNodeToBrowse = a_pContext->pNodeToBrowse;
	OpcUa_NodeId reftypeid;

	CAL_OpcUaNodeIdInitialize(&reftypeid);
	reftypeid.Identifier.Numeric = OpcUaId_HasNotifier;
	reftypeid.NamespaceIndex = 0;
	reftypeid.IdentifierType = OpcUa_IdentifierType_Numeric;

	if (!CAL_OpcUaServerCheckReferenceRecursive(&pNodeToBrowse->ReferenceTypeId, pNodeToBrowse->IncludeSubtypes, &reftypeid))
		return OpcUa_BadNodeIdUnknown;

	/* Check result mask */
	if ((pNodeToBrowse->NodeClassMask & OpcUa_NodeClass_Variable | OpcUa_NodeClass_Object || pNodeToBrowse->NodeClassMask == 0) == 0)
		return OpcUa_BadNodeIdUnknown;

	/* Check browse direction */
	if (pNodeToBrowse->BrowseDirection == OpcUa_BrowseDirection_Inverse)
		return OpcUa_BadNodeIdUnknown;

	/* Add object node */
	if (pNodeToBrowse->NodeClassMask & OpcUa_NodeClass_Object || pNodeToBrowse->NodeClassMask == 0)
	{
		uStatus = OpcUa_Good;
		if (a_pContext->pReference == OpcUa_Null)
		{
			if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
			{
				BrowseContextSetUnfinishedFlag(a_pContext);
				return uStatus;
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
					pRefDesc->NodeId.NodeId.Identifier.Numeric = 1001;


					/* Set browse name and display name */
					if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_BrowseName) != 0)
					{
						pRefDesc->BrowseName.NamespaceIndex = s_NamespaceIndex;
						CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, "MyFolder");
					}
					if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_DisplayName) != 0)
					{
						CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, "MyFolder");
						CAL_OpcUaStringStrnCpy(&pRefDesc->DisplayName.Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
					}

					/* Set reference type */
					if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_ReferenceTypeId) != 0)
					{
						CAL_OpcUaNodeIdCopyTo(&reftypeid, &pRefDesc->ReferenceTypeId);
					}
				}
				if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_TypeDefinition) != 0)
				{
					pRefDesc->TypeDefinition.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
					pRefDesc->TypeDefinition.NodeId.Identifier.Numeric = (OpcUa_UInt32)OpcUaId_FolderType;
					pRefDesc->TypeDefinition.NodeId.NamespaceIndex = 0;
					pRefDesc->TypeDefinition.ServerIndex = 0;
				}

				if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_NodeClass) != 0)
					pRefDesc->NodeClass = OpcUa_NodeClass_Object;
			}
			else
			{
				BrowseContextSetUnfinishedFlag(a_pContext);
				return uStatus;
			}
		}
	}
	return uStatus;
}

OpcUa_StatusCode BrowseOwnNodes(OpcUaProvider_BrowseContext *a_pContext)
{
	OpcUa_StatusCode uStatus = OpcUa_BadNodeIdUnknown;
	const OpcUa_BrowseDescription* pNodeToBrowse = a_pContext->pNodeToBrowse;
	OpcUa_NodeId reftypeid;

	if (pNodeToBrowse->NodeId.NamespaceIndex != s_NamespaceIndex)
		return OpcUa_BadNodeIdUnknown;

	if (pNodeToBrowse->NodeId.Identifier.Numeric != 0 && pNodeToBrowse->NodeId.Identifier.Numeric != 1 && pNodeToBrowse->NodeId.Identifier.Numeric != 1001)
		return OpcUa_BadNodeIdUnknown;

	uStatus = OpcUa_Good;

	/* Fill forward references */
	if ((pNodeToBrowse->BrowseDirection == OpcUa_BrowseDirection_Forward || pNodeToBrowse->BrowseDirection == OpcUa_BrowseDirection_Both) && 
		(pNodeToBrowse->NodeClassMask == 0 || pNodeToBrowse->NodeClassMask & (OpcUa_NodeClass_VariableType| OpcUa_NodeClass_ObjectType)
		))
	{
		CAL_OpcUaNodeIdInitialize(&reftypeid);
		reftypeid.Identifier.Numeric = OpcUaId_HasTypeDefinition;
		reftypeid.NamespaceIndex = 0;
		reftypeid.IdentifierType = OpcUa_IdentifierType_Numeric;

		/* Check if the client was intrested in this reference type */
		if (CAL_OpcUaServerCheckReferenceRecursive(&pNodeToBrowse->ReferenceTypeId, pNodeToBrowse->IncludeSubtypes, &reftypeid) == OpcUa_True)
		{
			if (a_pContext->pReference == NULL)
			{
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
				}
			}
			else
			{
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_True)
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
						pRefDesc->NodeId.NodeId.NamespaceIndex = 0;
						pRefDesc->NodeId.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
						if (pNodeToBrowse->NodeId.Identifier.Numeric == 0 || pNodeToBrowse->NodeId.Identifier.Numeric == 0)
						{
							pRefDesc->NodeId.NodeId.Identifier.Numeric = OpcUaId_BaseVariableType;
						}
						if (pNodeToBrowse->NodeId.Identifier.Numeric == 1001)
						{
							pRefDesc->NodeId.NodeId.Identifier.Numeric = OpcUaId_FolderType;
						}
						


						/* Set browse name and display name */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_BrowseName) != 0)
						{
							pRefDesc->BrowseName.NamespaceIndex = 0;
							if (pNodeToBrowse->NodeId.Identifier.Numeric == 0 || pNodeToBrowse->NodeId.Identifier.Numeric == 1)
							{
								CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, OpcUa_BrowseName_BaseVariableType);
							}
							if (pNodeToBrowse->NodeId.Identifier.Numeric == 1001)
							{
								CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, OpcUa_BrowseName_FolderType);
							}
						}
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_DisplayName) != 0)
						{
							if (pNodeToBrowse->NodeId.Identifier.Numeric == 0 || pNodeToBrowse->NodeId.Identifier.Numeric == 1)
							{
								CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, OpcUa_BrowseName_BaseVariableType);
							}
							if (pNodeToBrowse->NodeId.Identifier.Numeric == 1001)
							{
								CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, OpcUa_BrowseName_FolderType);
							}
							CAL_OpcUaStringStrnCpy(&pRefDesc->DisplayName.Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
						}

						/* Set reference type */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_ReferenceTypeId) != 0)
						{
							CAL_OpcUaNodeIdCopyTo(&reftypeid, &pRefDesc->ReferenceTypeId);
						}

						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_NodeClass) != 0)
						{
							if (pNodeToBrowse->NodeId.Identifier.Numeric == 0 || pNodeToBrowse->NodeId.Identifier.Numeric == 1)
							{
								pRefDesc->NodeClass = OpcUa_NodeClass_VariableType;
							}
							if (pNodeToBrowse->NodeId.Identifier.Numeric == 1001)
							{
								pRefDesc->NodeClass = OpcUa_NodeClass_ObjectType;
							}
						}

					}
				}
				else
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
				}
				
			}
		}

	}

	/* Fill backward references */
	if ((pNodeToBrowse->BrowseDirection == OpcUa_BrowseDirection_Inverse || pNodeToBrowse->BrowseDirection == OpcUa_BrowseDirection_Both) &&
		(pNodeToBrowse->NodeClassMask == 0 || pNodeToBrowse->NodeClassMask & (OpcUa_NodeClass_Object)
			))
	{

		/* Fill Reference to Objects node 
		*/
		CAL_OpcUaNodeIdInitialize(&reftypeid);
		reftypeid.Identifier.Numeric = OpcUaId_Organizes;
		reftypeid.NamespaceIndex = 0;
		reftypeid.IdentifierType = OpcUa_IdentifierType_Numeric;
		/* Check if the client was intrested in this reference type */
		if (CAL_OpcUaServerCheckReferenceRecursive(&pNodeToBrowse->ReferenceTypeId, pNodeToBrowse->IncludeSubtypes, &reftypeid))
		{
			if (a_pContext->pReference == NULL)
			{
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
				}
			}
			else
			{
				/* Add reference to Objects node */
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_True)
				{
					OpcUa_ReferenceDescription* pRefDesc = OpcUa_Null;
					const OpcUa_BrowseDescription* pBrowseDesc = a_pContext->pNodeToBrowse;

					pRefDesc = BrowseContextGetNextRefDesc(a_pContext);
					if (pRefDesc != OpcUa_Null)
					{
						if (pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_IsForward)
							pRefDesc->IsForward = OpcUa_False;

						/* Set Node id */
						pRefDesc->NodeId.NodeId.NamespaceIndex = 0;
						pRefDesc->NodeId.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
						pRefDesc->NodeId.NodeId.Identifier.Numeric = OpcUaId_ObjectsFolder;



						/* Set browse name and display name */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_BrowseName) != 0)
						{
							CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, OpcUa_BrowseName_ObjectsFolder);
						}
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_DisplayName) != 0)
						{
							CAL_OpcUaStringStrnCpy(&pRefDesc->DisplayName.Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
							CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, OpcUa_BrowseName_ObjectsFolder);
						}

						/* Set reference type */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_ReferenceTypeId) != 0)
						{
							CAL_OpcUaNodeIdCopyTo(&reftypeid, &pRefDesc->ReferenceTypeId);
						}

						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_NodeClass) != 0)
						{
							pRefDesc->NodeClass = OpcUa_NodeClass_Object;
						}

					}
				}
				else
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
				}
			}
		}

		/* Add Notifier Of Reference to Server Node */
		CAL_OpcUaNodeIdInitialize(&reftypeid);
		reftypeid.Identifier.Numeric = OpcUaId_HasNotifier;
		reftypeid.NamespaceIndex = 0;
		reftypeid.IdentifierType = OpcUa_IdentifierType_Numeric;
		/* Check if the client was intrested in this reference type */
		if (CAL_OpcUaServerCheckReferenceRecursive(&pNodeToBrowse->ReferenceTypeId, pNodeToBrowse->IncludeSubtypes, &reftypeid))
		{
			if (a_pContext->pReference == NULL)
			{
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_False)
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
				}
			}
			else
			{
				/* Add reference to Objects node */
				if (BrowseContextCheckAddNodes(a_pContext, 1) == OpcUa_True)
				{
					OpcUa_ReferenceDescription* pRefDesc = OpcUa_Null;
					const OpcUa_BrowseDescription* pBrowseDesc = a_pContext->pNodeToBrowse;

					pRefDesc = BrowseContextGetNextRefDesc(a_pContext);
					if (pRefDesc != OpcUa_Null)
					{
						if (pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_IsForward)
							pRefDesc->IsForward = OpcUa_False;

						/* Set Node id */
						pRefDesc->NodeId.NodeId.NamespaceIndex = 0;
						pRefDesc->NodeId.NodeId.IdentifierType = (OpcUa_UInt16)OpcUa_IdentifierType_Numeric;
						pRefDesc->NodeId.NodeId.Identifier.Numeric = OpcUaId_Server;



						/* Set browse name and display name */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_BrowseName) != 0)
						{
							CAL_OpcUaStringAttachCopy(&pRefDesc->BrowseName.Name, OpcUa_BrowseName_Server);
						}
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_DisplayName) != 0)
						{
							CAL_OpcUaStringStrnCpy(&pRefDesc->DisplayName.Locale, &s_ApplicationLocal, OPCUA_STRING_LENDONTCARE);
							CAL_OpcUaStringAttachReadOnly(&pRefDesc->DisplayName.Text, OpcUa_BrowseName_Server);
						}

						/* Set reference type */
						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_ReferenceTypeId) != 0)
						{
							CAL_OpcUaNodeIdCopyTo(&reftypeid, &pRefDesc->ReferenceTypeId);
						}

						if ((pBrowseDesc->ResultMask & (OpcUa_UInt32)OpcUa_BrowseResultMask_NodeClass) != 0)
						{
							pRefDesc->NodeClass = OpcUa_NodeClass_Object;
						}

					}
				}
				else
				{
					BrowseContextSetUnfinishedFlag(a_pContext);
					return uStatus;
				}
			}
		}
	}

	return uStatus;
}

STATICITF OpcUa_StatusCode OpcUaProviderBrowse(RTS_HANDLE hProvider, OpcUaProvider_BrowseContext *a_pContext)
{

	OpcUa_StatusCode uStatus = OpcUa_Good;
	const OpcUa_BrowseDescription* pNodeToBrowse = a_pContext->pNodeToBrowse;
	do
	{
		/* Only accept numeric node ids. Only these one are used in the template  */
		if (pNodeToBrowse->NodeId.IdentifierType != OpcUa_IdentifierType_Numeric)
			break;

		/* Children nodes of objects folder */
		if (pNodeToBrowse->NodeId.NamespaceIndex == 0)
		{
			switch (pNodeToBrowse->NodeId.Identifier.Numeric)
			{
				case OpcUaId_ObjectsFolder:
					uStatus = BrowseObjectsNode(a_pContext);
					break;
					/* Add Has EventNotifier reference */
				case OpcUaId_Server:
					uStatus = BrowseServerNode(a_pContext);
					break;
				default:
					break;
			}
				
			
		}

		/* Browsing the own nodes */
		if (pNodeToBrowse->NodeId.NamespaceIndex == s_NamespaceIndex)
		{
			uStatus = BrowseOwnNodes(a_pContext);
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
		if (pNode->Identifier.Numeric != 0 && pNode->Identifier.Numeric != 1 && pNode->Identifier.Numeric != 1001)
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
				if(pNode->Identifier.Numeric == 1001)
					pValue->Value.Int32 = (OpcUa_Int32)OpcUa_NodeClass_Object;
				else
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
				if (pNode->Identifier.Numeric == 1001)
					uStatus = CAL_OpcUaStringAttachReadOnly(&pValue->Value.QualifiedName->Name, "MyFolder");
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
				if (pNode->Identifier.Numeric == 1001)
					CAL_OpcUaStringAttachReadOnly(&pValue->Value.LocalizedText->Text, "MyFolder");
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
				if (pNode->Identifier.Numeric == 1001)
				{
					uStatus = OpcUa_BadAttributeIdInvalid;
					break;
				}
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
				if (pNode->Identifier.Numeric == 1001)
				{
					uStatus = OpcUa_BadAttributeIdInvalid;
					break;
				}
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
				if (pNode->Identifier.Numeric == 1001)
				{
					uStatus = OpcUa_BadAttributeIdInvalid;
					break;
				}
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Int32;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Int32 = OpcUa_ValueRanks_Scalar;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_AccessLevel:
				if (pNode->Identifier.Numeric == 1001)
				{
					uStatus = OpcUa_BadAttributeIdInvalid;
					break;
				}
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Byte;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Byte = OpcUa_AccessLevels_CurrentRead | OpcUa_AccessLevels_CurrentWrite;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_UserAccessLevel:
				if (pNode->Identifier.Numeric == 1001)
				{
					uStatus = OpcUa_BadAttributeIdInvalid;
					break;
				}
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Byte;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Byte = OpcUa_AccessLevels_CurrentRead | OpcUa_AccessLevels_CurrentWrite;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_Historizing:
				if (pNode->Identifier.Numeric == 1001)
				{
					uStatus = OpcUa_BadAttributeIdInvalid;
					break;
				}
				pValue->Datatype = (OpcUa_Byte)OpcUaType_Boolean;
				pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
				pValue->Value.Boolean = OpcUa_False;
				uStatus = OpcUa_Good;
				break;
			case OpcUa_Attributes_EventNotifier:
				if (pNode->Identifier.Numeric == 1001)
				{
					pValue->Datatype = (OpcUa_Byte)OpcUaType_Byte;
					pValue->ArrayType = OpcUa_VariantArrayType_Scalar;
					pValue->Value.Byte = OpcUa_EventNotifiers_SubscribeToEvents;
					uStatus = OpcUa_Good;
					break;
				}
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
