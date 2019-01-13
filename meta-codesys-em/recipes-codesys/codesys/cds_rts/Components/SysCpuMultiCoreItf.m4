/**
 * <interfacename>SysCpuMultiCore</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`SysCpuMultiCore')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Enum: eCoreBindingKindOf</description>
 */
#define ECOREBINDINGKINDOF_COREBINDINGDESC_UNBOUND    0	
#define ECOREBINDINGKINDOF_COREBINDINGDESC_SINGLECORE    1	
#define ECOREBINDINGKINDOF_COREBINDINGDESC_COREGROUP    2	
/* Typed enum definition */
#define ECOREBINDINGKINDOF    RTS_IEC_INT

/**
 * <description>CoreGroupDefinition</description>
 */
typedef struct tagCoreGroupDefinition
{
	RTS_IEC_DWORD dwNumCoresInGroup;		
	RTS_IEC_XWORD *CoreIDs;		/* A core identifier can be a number or a pointer to a description. */
} CoreGroupDefinition;

/**
 * <description>CpuCoreIdentifier</description>
 */
typedef union
{
	RTS_IEC_XWORD nCoreID;		
	CoreGroupDefinition CoreGroupID;		
} CpuCoreIdentifier;

/**
 * <description>CpuCoreBindingDesc</description>
 */
typedef struct tagCpuCoreBindingDesc
{
	RTS_IEC_INT eCoreKindOfBinding;		
	CpuCoreIdentifier idCpuCoreIdentifier;		
} CpuCoreBindingDesc;

/**
 *Function to bind a process to a core / core group.
 */
typedef struct tagsysmcbindprocess_struct
{
	CpuCoreBindingDesc CoreID;			/* VAR_INPUT */	/* Identifier (index) of the core to bind the process to. */
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBindProcess;	/* VAR_OUTPUT */	
} sysmcbindprocess_struct;

DEF_API(`void',`CDECL',`sysmcbindprocess',`(sysmcbindprocess_struct *p)',1,RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1),0x03050800)

/**
 *Function to bind a task to a core / core group.
 */
typedef struct tagsysmcbindtask_struct
{
	CpuCoreBindingDesc CoreID;			/* VAR_INPUT */	/* Identifier (index) of the core to bind the process to. */
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBindTask;		/* VAR_OUTPUT */	
} sysmcbindtask_struct;

DEF_API(`void',`CDECL',`sysmcbindtask',`(sysmcbindtask_struct *p)',1,RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447),0x03050800)

/**
 *Function to remove a dedicated core from the management of the runtime system.
 *This core will not be used by the runtime and is therefore exclusively available for other applications.
 */
typedef struct tagsysmcdisablecore_struct
{
	RTS_IEC_XWORD nCoreIdx;				/* VAR_INPUT */	/* Platform dependent identifier (index) of the core to remove. */
	RTS_IEC_RESULT SysMCDisableCore;	/* VAR_OUTPUT */	
} sysmcdisablecore_struct;

DEF_API(`void',`CDECL',`sysmcdisablecore',`(sysmcdisablecore_struct *p)',1,RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8),0x03050800)

/**
 *Function to add a formerlay removed dedicated core back to the management of the runtime system.
 */
typedef struct tagsysmcenablecore_struct
{
	RTS_IEC_XWORD nCoreIdx;				/* VAR_INPUT */	/* Platform dependent identifier (index) of the core. */
	RTS_IEC_RESULT SysMCEnableCore;		/* VAR_OUTPUT */	
} sysmcenablecore_struct;

DEF_API(`void',`CDECL',`sysmcenablecore',`(sysmcenablecore_struct *p)',1,RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0),0x03050800)

/**
 * <description>sysmcgetload</description>
 */
typedef struct tagsysmcgetload_struct
{
	RTS_IEC_XWORD CoreID;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pPercent;				/* VAR_INPUT */	/* CPU-Core load in percent. */
	RTS_IEC_RESULT SysMCGetLoad;		/* VAR_OUTPUT */	
} sysmcgetload_struct;

DEF_API(`void',`CDECL',`sysmcgetload',`(sysmcgetload_struct *p)',1,RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E),0x03050800)

/**
 *Returns the number of available cores.
 *Available means: Available to be used by runtime system.
 */
typedef struct tagsysmcgetnumofcores_struct
{
	RTS_IEC_RESULT *Result;				/* VAR_INPUT */	/* Pointer to retrieve optional error code. */
	RTS_IEC_DWORD SysMCGetNumOfCores;	/* VAR_OUTPUT */	
} sysmcgetnumofcores_struct;

DEF_API(`void',`CDECL',`sysmcgetnumofcores',`(sysmcgetnumofcores_struct *p)',1,0xA3C2E550,0x03050800)

/**
 *Read the binding description of a process.
 */
typedef struct tagsysmcgetprocessbinding_struct
{
	RTS_IEC_HANDLE hProcess;				/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetProcessBinding;	/* VAR_OUTPUT */	
} sysmcgetprocessbinding_struct;

DEF_API(`void',`CDECL',`sysmcgetprocessbinding',`(sysmcgetprocessbinding_struct *p)',1,RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917),0x03050800)

/**
 *Read the binding description of a task.
 */
typedef struct tagsysmcgettaskbinding_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetTaskBinding;	/* VAR_OUTPUT */	
} sysmcgettaskbinding_struct;

DEF_API(`void',`CDECL',`sysmcgettaskbinding',`(sysmcgettaskbinding_struct *p)',1,RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A),0x03050800)

/**
 *Function to remove the core binding of a process.
 * 
 */
typedef struct tagsysmcunbindprocess_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCUnbindProcess;	/* VAR_OUTPUT */	
} sysmcunbindprocess_struct;

DEF_API(`void',`CDECL',`sysmcunbindprocess',`(sysmcunbindprocess_struct *p)',1,0x91976CA3,0x03050800)

/**
 * <description>sysmcunbindtask</description>
 */
typedef struct tagsysmcunbindtask_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCUnbindTask;		/* VAR_OUTPUT */	
} sysmcunbindtask_struct;

DEF_API(`void',`CDECL',`sysmcunbindtask',`(sysmcunbindtask_struct *p)',1,0x7D06154E,0x03050800)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

/* Init routines for OS specific modules */
RTS_RESULT CDECL SysCpuMultiCoreOSInit(INIT_STRUCT *pInit);
RTS_RESULT CDECL SysCpuMultiCoreOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);

/**
 * <description>
 * <p>Function to bind a process to a CPU core or a group of CPU cores.</p>
 * <p>
 * To bind a process to a single core, set the member "eCoreKindOfBinding" of the input structure CpuCoreBindingDesc to ECOREBINDINGKINDOF_COREBINDINGDESC_SINGLECORE.
 * Set the union member nCoreID to the identifier of the core. This is a system dependent value.
 * </p>
 * <p>
 * To bind a process to a group of cores, set the member "eCoreKindOfBinding" of the input structure CpuCoreBindingDesc to ECOREBINDINGKINDOF_COREBINDINGDESC_COREGROUP.
 * Set the union member CoreGroupID.dwNumCoresInGroup to the number of cores in the group. Set the union member of CoreGroupID.CoreIDs to the address of the first array elelment of an array of identifiers of cores.
 * </p>
 * </description>
 * <param name="pCoreID" type="IN">Pointer to the binding description for the new core binding.</param>
 * <param name="hProcess" type="IN">Handle of the process to bind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindProcess',`(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * The OS implementation of SysMCBindProcess
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindProcess_',`(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * <p>Function to bind a task to a CPU core or a group of CPU cores.</p>
 * <p>
 * To bind a task to a single core, set the member "eCoreKindOfBinding" of the input structure CpuCoreBindingDesc to ECOREBINDINGKINDOF_COREBINDINGDESC_SINGLECORE.
 * Set the union member nCoreID to the identifier of the core. This is a system dependent value.
 * </p>
 * <p>
 * To bind a task to a group of cores, set the member "eCoreKindOfBinding" of the input structure CpuCoreBindingDesc to ECOREBINDINGKINDOF_COREBINDINGDESC_COREGROUP.
 * Set the union member CoreGroupID.dwNumCoresInGroup to the number of cores in the group. Set the union member of CoreGroupID.CoreIDs to the address of the first array elelment of an array of identifiers of cores.
 * </p>
 * </description>
 * <param name="pCoreID" type="IN">Pointer to the binding description for the new core binding.</param>
 * <param name="hTask" type="IN">Handle of the task to bind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindTask',`(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * The OS implementation of SysMCBindTask
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCBindTask_',`(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * <p>Function to remove the binding to a core or a group of cores of a process.</p>
 * <p>
 * This means the OS is again responsible on which core the process is allowed to run on.
 * </p>
 * </description>
 * <param name="hProcess" type="IN">Handle of the process to unbind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindProcess',`(RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * The OS implementation of SysMCUnbindProcess
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindProcess_',`(RTS_IEC_HANDLE hProcess)')

/**
 * <description>
 * <p>Function to remove the binding to a core or a group of cores of a task.</p>
 * <p>
 * This means the OS is again responsible on which core the task is allowed to run on.
 * </p>
 * </description>
 * <param name="hTask" type="IN">Handle of the task to unbind.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_OPERATION_DENIED">Operation is denied on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_INVALID_HANDLE">Handle is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindTask',`(RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * The OS implementation of SysMCUnbindTask
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCUnbindTask_',`(RTS_IEC_HANDLE hTask)')

/**
 * <description>
 * <p>Function to get the current average workload of a dedicated core, identified by the input parameter.</p>
 * </description>
 * <param name="CoreID" type="IN">Identifies the core whose load has to be returned.</param>
 * <param name="pPercent" type="OUT">CPU-Core load in percent.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">Function is not initialized.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOBUFFER">Not enough memory for the performance counters</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetLoad',`(RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent)')

/**
 * <description>
 * The OS implementation of SysMCGetLoad
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetLoad_',`(RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent)')

/**
 * <description>
 * <p>Function to get the number of CPU cores available for use by the runtime system.</p>
 * </description>
 * <param name="Result" type="IN">Address of a variable to return an optional errorcode.</param>
 * <result>Returns the number of cores.</result>
 * <errorcode name="RTS_RESULT pResult" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT pResult" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetNumOfCores',`(RTS_RESULT* pResult)')

/**
 * <description>
 * The OS implementation of SysMCGetNumOfCores
 * </description>
 */
DEF_ITF_API(`RTS_UI32',`CDECL',`SysMCGetNumOfCores_',`(RTS_RESULT* pResult)')

/**
 * <description>
 * <p>Administration function to enable a dedicated (formerly disabled) core identified by the input parameter CoreID to be used by the runtime system.</p>
 * </description>
 * <param name="CoreID" type="IN">Identifies the core to be removed from the list of available cores.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCEnableCore',`(RTS_IEC_XWORD CoreID)')

/**
 * <description>
 * <p>Administration function to disable a dedicated core identified by the input parameter CoreID not to be used by the runtime system.</p>
 * </description>
 * <param name="CoreID" type="IN">Identifies the core to be removed from the list of available cores.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid, e.g. core does not exist.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCDisableCore',`(RTS_IEC_XWORD CoreID)')

/**
 * <description>
 * <p>Function to read the binding of a process to CPU core(s).</p>
 * </description>
 * <param name="hProcess" type="IN">Handle of the process.</param>
 * <param name="pCoreID" type="OUT">Pointer to the binding description for the core binding.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetProcessBinding',`(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID)')

/**
 * <description>
 * The OS implementation of SysMCGetProcessBinding
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetProcessBinding_',`(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID)')

/**
 * <description>
 * <p>Function to read the binding of a task to CPU core(s).</p>
 * </description>
 * <param name="hTask" type="IN">Handle of the task.</param>
 * <param name="pCoreID" type="OUT">Pointer to the binding description for the core binding.</param>
 * <result>Returns the result.</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Call was sucessfull.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Parameter is invalid.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Function failed for any reason on OS level.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Function is not supported.</errorcode>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetTaskBinding',`(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID)')

/**
 * <description>
 * The OS implementation of SysMCGetTaskBinding
 * </description>
 */
DEF_ITF_API(`RTS_RESULT',`CDECL',`SysMCGetTaskBinding_',`(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID)')

#ifdef __cplusplus
}
#endif

