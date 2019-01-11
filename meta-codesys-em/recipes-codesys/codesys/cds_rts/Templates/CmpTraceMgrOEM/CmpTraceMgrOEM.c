/**
 * <name>CmpTraceMgrOEM.c</name>
 * <description> 
 *	Example to create a traceconfiguration and to handle and update a system variable.
 *	A so called device traceconfiguration is a trace, that is created by a RTS component or an IEC Program/FB. This trace can
 *	be uploaded in CODESYS an can be monitored without an Application.
 *	So this can be used to trace system variables resp. build in variables (like actual velocity of a drive or response time on a fieldbus).

 *	That such a system variable can be added in CODESYS to a user defined trace, this must be specified in the DeviceDescription with the attribute "TraceSystemRecord"
 *	at the IO-configuration parameter:
 *      <Parameter ParameterId="1073741826" type="std:DWORD">
 *         <!--16#40000002-->
 *         <Attributes offlineaccess="readwrite" download="true" functional="false" TraceSystemRecord="true" />
 *         <Default>0</Default>
 *         <Name>TestSystemVariable</Name>
 *         <Description>Test system variable for tracing</Description>
 *      </Parameter>
 *
 *	If you would like that the user can select a system task in which the trace is running, you have to specify this in the DeviceDescription too (:ref:`trace_systemtasks`):
 *	   <ts:section name="trace">
 *			...
 *			<ts:setting name="systemtasks" type="string" access="visible">
 *				<ts:value>SystemTask</ts:value>
 *			</ts:setting>
 *			...
 *		</ts:section>
 *
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"
#include "CmpTraceMgrOEMDep.h"

USE_STMT

static RTS_HANDLE s_hPacket;
static RTS_HANDLE s_hRecord;
static RTS_HANDLE s_hEventRecordAdd = RTS_INVALID_HANDLE;
static RTS_HANDLE s_hEventRecordUpdate = RTS_INVALID_HANDLE;

/* This is the example for a sysmtem variable which can be traced */
static RTS_UI32 s_ulSystemTraceVariable = 0;

static RTS_RESULT InitTraceEvents(void);
static RTS_RESULT ExitTraceEvents(void);
static RTS_RESULT CreateTraceConfiguration(void);
static RTS_RESULT DeleteTraceConfiguration(void);
static RTS_RESULT CycliceUpdateTrace(void);
static void CDECL CBTraceMgr(EventParam *pEventParam);


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
#ifndef RTS_COMPACT_MICRO
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
#endif

	s_hEventRecordAdd = RTS_INVALID_HANDLE;
	s_hEventRecordUpdate = RTS_INVALID_HANDLE;

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpTraceMgrOEM);
	*/
	return ERR_OK;
}

#ifndef RTS_COMPACT_MICRO

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpTraceMgrOEM)
	{
		CCmpTraceMgrOEM *pCCmpTraceMgrOEM = static_cast<CCmpTraceMgrOEM *>(new CCmpTraceMgrOEM());
		return (IBase*)pCCmpTraceMgrOEM->QueryInterface(pCCmpTraceMgrOEM, ITFID_IBase, pResult);
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
#ifdef RTS_COMPACT_MICRO
			ComponentEntry(NULL);
#endif
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
			break;
		case CH_INIT3:
		{
			InitTraceEvents();
			break;
		}
		case CH_INIT_TASKS:
		{
			CreateTraceConfiguration();
			break;
		}
		case CH_INIT_COMM:
			break;

		/* Cyclic */
		case CH_COMM_CYCLE:
		{
			CycliceUpdateTrace();
			break;
		}

#ifndef RTS_COMPACT_MICRO
		case CH_EXIT_COMM:
			break;
		case CH_EXIT_TASKS:
		{
			DeleteTraceConfiguration();
			break;
		}
		case CH_EXIT3:
		{
			ExitTraceEvents();
			break;
		}
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

/**
 * <description>Function to open event and register the callback function to handle trace events.
 *	USAGE:
 *	- Must be called in CH_INIT3 out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT InitTraceEvents(void)
{
	if (CHK_EventOpen)
	{
		RTS_RESULT Result;

		s_hEventRecordAdd = CAL_EventOpen(EVT_TRACEMGR_ADD_RECORD, CMPID_CmpTraceMgr, &Result);
		s_hEventRecordUpdate = CAL_EventOpen(EVT_TRACEMGR_UPDATE_RECORD, CMPID_CmpTraceMgr, &Result);
	}
	if (CHK_EventRegisterCallbackFunction)
	{
		CAL_EventRegisterCallbackFunction(s_hEventRecordAdd, CBTraceMgr, 0);
		CAL_EventRegisterCallbackFunction(s_hEventRecordUpdate, CBTraceMgr, 0);
	}
	return ERR_OK;
}

/**
 * <description>Function to close event and unregister callback function.
 *	USAGE:
 *	- Must be called in CH_EXIT3 out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT ExitTraceEvents(void)
{
	if (CHK_EventUnregisterCallbackFunction)
	{
		CAL_EventUnregisterCallbackFunction(s_hEventRecordAdd, CBTraceMgr);
		CAL_EventUnregisterCallbackFunction(s_hEventRecordUpdate, CBTraceMgr);
	}
	if (CHK_EventClose)
	{
		CAL_EventClose(s_hEventRecordAdd);
		CAL_EventClose(s_hEventRecordUpdate);
	}
	return ERR_OK;
}

/**
 * <description>Function to create a new device trace configuration and add the system variable to this trace.
 *	USAGE:
 *	- Must be called in CH_INIT_TASKS out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CreateTraceConfiguration(void)
{
	TracePacketConfiguration tc = {0};
	RTS_RESULT Result;
											
	tc.pszName = "TestPacket";
	tc.ulBufferEntries = 100;
	tc.ulFlags = TRACE_PACKET_FLAGS_TIMESTAMP_US;

	s_hPacket = CAL_TraceMgrPacketCreate(&tc, &Result);
	if (s_hPacket != RTS_INVALID_HANDLE)
	{
		TraceRecordConfiguration trcVariable = {0};
		trcVariable.pszVariable = "TestSystemVariable";
		trcVariable.tcClass = (RTS_IEC_UDINT)TYPE3_DWORD;
		trcVariable.ulSize = sizeof(s_ulSystemTraceVariable);
		trcVariable.tvaAddress.ulAddressFlags = TRACE_VAR_ADDRESS_FLAGS_SYSTEM;
		trcVariable.tvaAddress.taAddress.systemParameter.ulID = 4711;
		trcVariable.tvaAddress.taAddress.systemParameter.ulOffset = 0;
		trcVariable.tvaAddress.taAddress.systemParameter.ulModuleType = 0;
		trcVariable.tvaAddress.taAddress.systemParameter.ulInstance = 0;

		trcVariable.ulGraphColor = 0xFF0000FF;
		trcVariable.ulGraphType = 1;

		s_hRecord = CAL_TraceMgrRecordAdd(s_hPacket, &trcVariable, &Result);
		CAL_TraceMgrPacketComplete(s_hPacket);
	}
	return ERR_OK;
}

/**
 * <description>Function to delete the device trace configuration.
 *	USAGE:
 *	- Must be called in CH_EXIT_TASKS out of component HookFunction()!
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT DeleteTraceConfiguration(void)
{
	CAL_TraceMgrRecordRemove(s_hPacket, s_hRecord);
	CAL_TraceMgrPacketDelete(s_hPacket);
	return ERR_OK;
}

/**
 * <description>Function to cyclic update the system variable value in the trace. So a new value entry in the trace buffer is set with the corresponding timestamp.
 *	USAGE:
 *	- Is called here as an example in CH_COMM_CYCLE out of component HookFunction(). But can be any system task or IEC slot.
 * </description>
 * <result>error code</result>
 */
static RTS_RESULT CycliceUpdateTrace(void)
{
	TraceState state;
	CAL_TraceMgrPacketGetState(s_hPacket, &state);
	if (state.ulState == TRACE_PACKET_STATE_STOPPED || state.ulState == TRACE_PACKET_STATE_ENABLED)
		CAL_TraceMgrPacketStart(s_hPacket);

	s_ulSystemTraceVariable += 1;
	CAL_TraceMgrRecordUpdate3(s_hPacket, s_hRecord, &s_ulSystemTraceVariable, sizeof(s_ulSystemTraceVariable));
	return ERR_OK;
}

/**
 * <description>Callback function to handle trace manager event if our system variable is added in a trace configuration in CODESYS:
 *	- In the EVT_TRACEMGR_ADD_RECORD event we are notified, that the our system variable was added to a trace configuration in CODESYS
 *	- In the EVT_TRACEMGR_UPDATE_RECORD event we are notified out of the context af an IEC task, that we have to provide a new value to the trace packet
 * </description>
 * <param name="pEventParam" type="IN">Pointer to event parameter set. pEventParam->pParameter is a pointer to EVTPARAM_CmpTraceMgr_Record</param> 
 * <result>None</result>
 */
static void CDECL CBTraceMgr(EventParam *pEventParam)
{
	switch (pEventParam->EventId)
	{	
		case EVT_TRACEMGR_ADD_RECORD:
		{
			TraceRecordConfiguration configuration;
			EVTPARAM_CmpTraceMgr_Record *pParam = (EVTPARAM_CmpTraceMgr_Record *)pEventParam->pParameter;;

			CAL_TraceMgrRecordGetConfig(pParam->hPacket, pParam->hRecord, &configuration);

			if (strcmp(configuration.pszVariable, "TestSystemVariable") != 0 &&
				configuration.tvaAddress.ulAddressFlags == TRACE_VAR_ADDRESS_FLAGS_SYSTEM)
			{
				/* This is a system variable that is requested by a trace packet generated from CoDeSys */
			}
			break;
		}
		case EVT_TRACEMGR_UPDATE_RECORD:
		{
			TraceRecordConfiguration configuration;
			EVTPARAM_CmpTraceMgr_Record *pParam = (EVTPARAM_CmpTraceMgr_Record *)pEventParam->pParameter;;

			CAL_TraceMgrRecordGetConfig(pParam->hPacket, pParam->hRecord, &configuration);

			if (strcmp(configuration.pszVariable, "TestSystemVariable") != 0 &&
				configuration.tvaAddress.ulAddressFlags == TRACE_VAR_ADDRESS_FLAGS_SYSTEM)
			{
			   /*
				* Here ist the handling, if the system variable is added in a trace packet generated from CODESYS.
				* In this event you have to update the values in the corresponding trace record. Typically you can use the following function to synchronize 
				* your buffer with the record buffer:
				CAL_TraceMgrRecordUpdate2(pParam->hPacket, pParam->hRecord, TraceRecordEntry *pBuffer, unsigned long ulLen);
				*/
			}
			break;
		}
		default:
			break;
	}
}
