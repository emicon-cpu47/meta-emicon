/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Test component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpIecVarTestDep.h"

USE_STMT

static RTS_HANDLE s_hInterface = RTS_INVALID_HANDLE;

void DumpAll(RTS_HANDLE hNode);

#ifndef RTS_COMPACT_MICRO

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

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpIecVarTest);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpIecVarTest)
	{
		CCmpIecVarTest *pCCmpIecVarTest = static_cast<CCmpIecVarTest *>(new CCmpIecVarTest());
		return (IBase*)pCCmpIecVarTest->QueryInterface(pCCmpIecVarTest, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release();
	return ERR_OK;
#else
	return ERR_NOTIMPLEMENTED;
#endif
}

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

#endif

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
			break;
		case CH_INIT3:
			break;
		case CH_INIT_TASKS:
			break;
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
		{
			/* ONLY FOR TESTING */
			static int bDebug = 0;
			if (bDebug)	
				DumpAll(RTS_INVALID_HANDLE);
			break;
		}
#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
			break;
		case CH_EXIT3:
			break;
		case CH_EXIT2:
			break;
		case CH_EXIT:
		{
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
#endif

		default:
			break;
	}
	return ERR_OK;
}


void DumpOne(char *szName) {
	RTS_RESULT result;
	RTS_HANDLE hNode;
	VariableInformationStruct3 VarInfo;
	RTS_HANDLE hInterface = RTS_INVALID_HANDLE;

    CAL_IecVarAccInitVarInfo((VariableInformationStruct2*)&VarInfo, sizeof(VarInfo));
	hNode = CAL_IecVarAccGetNode3(szName, &hInterface, (VariableInformationStruct2*)&VarInfo, &result);
	
	if(result == ERR_OK) {
		TreeNodeType type;

		type = CAL_IecVarAccGetNodeType(hInterface, hNode, &result);
		if(type == LeafNode) {
			TypeClass3 varType;
			long lSize;
			unsigned long ulValue;
			unsigned short usValue;
			
			/* read value */
			lSize = CAL_IecVarAccGetSize3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &result);
			varType = CAL_IecVarAccGetTypeClass3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &result);
			switch(varType) {
			case TYPE3_INT:
				CAL_IecVarAccGetValue3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &usValue, lSize, &result);
				CAL_SysOutPrintf("%s: Var %s: Value: %d (size: %d)\n", COMPONENT_NAME, szName, (int)usValue, lSize);
				break;
			case TYPE3_UDINT:
				CAL_IecVarAccGetValue3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &ulValue, lSize, &result);
				CAL_SysOutPrintf("%s: Var %s: Value: %lu (size: %d)\n", COMPONENT_NAME, szName, ulValue, lSize);
				break;
			default:
				CAL_SysOutPrintf("%s: Var %s: Todo - type is not read in this example code\n", COMPONENT_NAME, szName);
				break;
			}
		}
		else
		{
			CAL_SysOutPrintf("%s: Var %s: no value, node is not a LeafNode\n", COMPONENT_NAME, szName);
		}
	}
    CAL_IecVarAccExitVarInfo((VariableInformationStruct2*)&VarInfo);
}


void ExpandNode(char *szName) {
	RTS_RESULT result;
	RTS_HANDLE hNode;
	VariableInformationStruct3 VarInfo;
	RTS_HANDLE hInterface = RTS_INVALID_HANDLE;
	TypeClass3 varType;

    CAL_IecVarAccInitVarInfo((VariableInformationStruct2*)&VarInfo, sizeof(VarInfo));
	hNode = CAL_IecVarAccGetNode3(szName, &hInterface, (VariableInformationStruct2*)&VarInfo, &result);
	varType = CAL_IecVarAccGetTypeClass3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &result);
	switch(varType) {
		case TYPE3_ARRAY:
		{
			char szNodeName[512];
			TypeDescAsUnion typeDesc;
			RTS_HANDLE hTypeNode;

			CAL_SysOutPrintf("%s: Expand array %s\n", COMPONENT_NAME, szName);

			hTypeNode = CAL_IecVarAccGetTypeNode3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &result);
			memset(&typeDesc, 0, sizeof(typeDesc));
			result = CAL_IecVarAccGetTypeDesc(hInterface, hTypeNode, &typeDesc);

			if ( result == ERR_OK)
			{
				long i,j,k;
				
				if ( typeDesc._union._array._iDimensions < 1 || typeDesc._union._array._iDimensions > 3)
				{
					typeDesc._union._array._iDimensions = 0;
					typeDesc._union._array._Dimension[0].MinRange = 0;
					typeDesc._union._array._Dimension[0].MaxRange = 0;
				}
				if ( typeDesc._union._array._iDimensions <= 1 )
				{
					typeDesc._union._array._Dimension[1].MinRange = 0;
					typeDesc._union._array._Dimension[1].MaxRange = 0;
				}
				if ( typeDesc._union._array._iDimensions <= 2 )
				{
					typeDesc._union._array._Dimension[2].MinRange = 0;
					typeDesc._union._array._Dimension[2].MaxRange = 0;
				}
				if ( typeDesc._union._array._iDimensions > 0 )
				{
					for ( i=typeDesc._union._array._Dimension[0].MinRange; i <= typeDesc._union._array._Dimension[0].MaxRange; i++)
					{
						for ( j=typeDesc._union._array._Dimension[1].MinRange; j <= typeDesc._union._array._Dimension[1].MaxRange; j++)
						{
							for ( k=typeDesc._union._array._Dimension[2].MinRange; k <= typeDesc._union._array._Dimension[2].MaxRange; k++)
							{
								if ( typeDesc._union._array._iDimensions == 1)
									sprintf(szNodeName, "%s[%ld]",szName,i);
								else if (typeDesc._union._array._iDimensions == 2)
									sprintf(szNodeName, "%s[%ld,%ld]",szName,i,j);
								else
									sprintf(szNodeName, "%s[%ld,%ld,%ld]",szName,i,j,k);
								
								/* recursive call */
								ExpandNode(szNodeName);
							}
						}
					}
				}
			}	
			break;
		}
		case TYPE3_USERDEF:
		{
			int i;
			char szNodeName[512];
			TypeDescAsUnion typeDesc;
			RTS_HANDLE hTypeNode;

			CAL_SysOutPrintf("%s: Expand structure %s\n", COMPONENT_NAME, szName);

			hTypeNode = CAL_IecVarAccGetTypeNode3(hInterface, hNode, (VariableInformationStruct2*)&VarInfo, &result);
			memset(&typeDesc, 0, sizeof(typeDesc));
			CAL_IecVarAccGetTypeDesc(hInterface, hTypeNode, &typeDesc);
			typeDesc._union._struct._Components = (IBaseTreeNode **)CAL_SysMemAllocData(COMPONENT_NAME, typeDesc._union._struct._iComponents * sizeof(IBaseTreeNode*), NULL);
			result = CAL_IecVarAccGetTypeDesc(hInterface, hTypeNode, &typeDesc);
			if ( result == ERR_OK)
			{
				for (i=0; i<typeDesc._union._struct._iComponents; i++)
				{
					RTS_HANDLE hElemNode = (RTS_HANDLE)typeDesc._union._struct._Components[i];
					char* pElemName = CAL_IecVarAccGetNodeName(hInterface, hElemNode, &result);
					strcpy(szNodeName, szName);
					strcat(szNodeName, ".");
					strcat(szNodeName, pElemName);
					/* recursive call */
					ExpandNode(szNodeName);
				}
			}
			CAL_SysMemFreeData(COMPONENT_NAME, typeDesc._union._struct._Components);
			break;
		}
		default:
			DumpOne(szName);
			break;
	}
    CAL_IecVarAccExitVarInfo((VariableInformationStruct2*)&VarInfo);
}


void DumpAll(RTS_HANDLE hNode) {
	RTS_RESULT result;
	if(hNode == RTS_INVALID_HANDLE) {
		char szAppName[256];
		if (s_hInterface == RTS_INVALID_HANDLE)
		{
			s_hInterface = CAL_IecVarAccGetFirstInterface(NULL);
			/* Optinally call get CAL_IecVarAccGetNextInterface(), if there is more than one application */
		}
		if (CAL_IecVarAccGetApplicationName(s_hInterface, szAppName, sizeof(szAppName)) == ERR_OK)
			CAL_SysOutPrintf("%s: Application Name: %s\n", COMPONENT_NAME, szAppName);
		else
			CAL_SysOutPrintf("%s: No symbols available\n", COMPONENT_NAME);

		hNode = CAL_IecVarAccBrowseGetRoot(s_hInterface, &result);
		hNode = CAL_IecVarAccBrowseDown(s_hInterface, hNode, &result);
		if(result != ERR_OK)
			hNode = RTS_INVALID_HANDLE;
	}

	while(hNode != RTS_INVALID_HANDLE) {
		RTS_HANDLE hChildNode;
		RTS_HANDLE hNodeNext;
		TreeNodeType type;
		static char szPath[256];

		type = CAL_IecVarAccGetNodeType(s_hInterface, hNode, &result);
		if(type == BranchNode) {
			/* recursive call */
			hChildNode = CAL_IecVarAccBrowseDown(s_hInterface, hNode, &result); 
			if(result == ERR_OK)
				DumpAll(hChildNode);
		}
		else if(type == LeafNode) {
			CAL_IecVarAccGetNodeFullPath(s_hInterface, hNode, szPath, sizeof(szPath), &result);
			ExpandNode(szPath);
		}
		hNodeNext = CAL_IecVarAccBrowseGetNext(s_hInterface, hNode, &result);
		hNode = hNodeNext;
		if(result != ERR_OK)
			hNode = RTS_INVALID_HANDLE;
	}
}


void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p)  {
	CAL_SysOutPrintf("Dump All Symbols:\n");
	DumpAll(RTS_INVALID_HANDLE);
	CAL_SysOutPrintf("Dump 'Application.PLC_PRG.hugo':\n");
	DumpOne("Application.PLC_PRG.hugo");
}



