 /**
 * <interfacename>SysCpuMultiCore</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _SYSCPUMULTICOREITF_H_
#define _SYSCPUMULTICOREITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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

void CDECL CDECL_EXT sysmcbindprocess(sysmcbindprocess_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBINDPROCESS_IEC) (sysmcbindprocess_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDPROCESS_NOTIMPLEMENTED)
	#define USE_sysmcbindprocess
	#define EXT_sysmcbindprocess
	#define GET_sysmcbindprocess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbindprocess(p0) 
	#define CHK_sysmcbindprocess  FALSE
	#define EXP_sysmcbindprocess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbindprocess
	#define EXT_sysmcbindprocess
	#define GET_sysmcbindprocess(fl)  CAL_CMGETAPI( "sysmcbindprocess" ) 
	#define CAL_sysmcbindprocess  sysmcbindprocess
	#define CHK_sysmcbindprocess  TRUE
	#define EXP_sysmcbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindprocess", (RTS_UINTPTR)sysmcbindprocess, 1, RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbindprocess
	#define EXT_sysmcbindprocess
	#define GET_sysmcbindprocess(fl)  CAL_CMGETAPI( "sysmcbindprocess" ) 
	#define CAL_sysmcbindprocess  sysmcbindprocess
	#define CHK_sysmcbindprocess  TRUE
	#define EXP_sysmcbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindprocess", (RTS_UINTPTR)sysmcbindprocess, 1, RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbindprocess
	#define EXT_SysCpuMultiCoresysmcbindprocess
	#define GET_SysCpuMultiCoresysmcbindprocess  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbindprocess  sysmcbindprocess
	#define CHK_SysCpuMultiCoresysmcbindprocess  TRUE
	#define EXP_SysCpuMultiCoresysmcbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindprocess", (RTS_UINTPTR)sysmcbindprocess, 1, RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbindprocess
	#define EXT_sysmcbindprocess
	#define GET_sysmcbindprocess(fl)  CAL_CMGETAPI( "sysmcbindprocess" ) 
	#define CAL_sysmcbindprocess  sysmcbindprocess
	#define CHK_sysmcbindprocess  TRUE
	#define EXP_sysmcbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindprocess", (RTS_UINTPTR)sysmcbindprocess, 1, RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbindprocess  PFSYSMCBINDPROCESS_IEC pfsysmcbindprocess;
	#define EXT_sysmcbindprocess  extern PFSYSMCBINDPROCESS_IEC pfsysmcbindprocess;
	#define GET_sysmcbindprocess(fl)  s_pfCMGetAPI2( "sysmcbindprocess", (RTS_VOID_FCTPTR *)&pfsysmcbindprocess, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1), 0x03050800)
	#define CAL_sysmcbindprocess  pfsysmcbindprocess
	#define CHK_sysmcbindprocess  (pfsysmcbindprocess != NULL)
	#define EXP_sysmcbindprocess   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindprocess", (RTS_UINTPTR)sysmcbindprocess, 1, RTSITF_GET_SIGNATURE(0xEF41205F, 0xEF59CBC1), 0x03050800) 
#endif


/**
 *Function to bind a task to a core / core group.
 */
typedef struct tagsysmcbindtask_struct
{
	CpuCoreBindingDesc CoreID;			/* VAR_INPUT */	/* Identifier (index) of the core to bind the process to. */
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCBindTask;		/* VAR_OUTPUT */	
} sysmcbindtask_struct;

void CDECL CDECL_EXT sysmcbindtask(sysmcbindtask_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCBINDTASK_IEC) (sysmcbindtask_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDTASK_NOTIMPLEMENTED)
	#define USE_sysmcbindtask
	#define EXT_sysmcbindtask
	#define GET_sysmcbindtask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcbindtask(p0) 
	#define CHK_sysmcbindtask  FALSE
	#define EXP_sysmcbindtask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcbindtask
	#define EXT_sysmcbindtask
	#define GET_sysmcbindtask(fl)  CAL_CMGETAPI( "sysmcbindtask" ) 
	#define CAL_sysmcbindtask  sysmcbindtask
	#define CHK_sysmcbindtask  TRUE
	#define EXP_sysmcbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindtask", (RTS_UINTPTR)sysmcbindtask, 1, RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcbindtask
	#define EXT_sysmcbindtask
	#define GET_sysmcbindtask(fl)  CAL_CMGETAPI( "sysmcbindtask" ) 
	#define CAL_sysmcbindtask  sysmcbindtask
	#define CHK_sysmcbindtask  TRUE
	#define EXP_sysmcbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindtask", (RTS_UINTPTR)sysmcbindtask, 1, RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcbindtask
	#define EXT_SysCpuMultiCoresysmcbindtask
	#define GET_SysCpuMultiCoresysmcbindtask  ERR_OK
	#define CAL_SysCpuMultiCoresysmcbindtask  sysmcbindtask
	#define CHK_SysCpuMultiCoresysmcbindtask  TRUE
	#define EXP_SysCpuMultiCoresysmcbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindtask", (RTS_UINTPTR)sysmcbindtask, 1, RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcbindtask
	#define EXT_sysmcbindtask
	#define GET_sysmcbindtask(fl)  CAL_CMGETAPI( "sysmcbindtask" ) 
	#define CAL_sysmcbindtask  sysmcbindtask
	#define CHK_sysmcbindtask  TRUE
	#define EXP_sysmcbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindtask", (RTS_UINTPTR)sysmcbindtask, 1, RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcbindtask  PFSYSMCBINDTASK_IEC pfsysmcbindtask;
	#define EXT_sysmcbindtask  extern PFSYSMCBINDTASK_IEC pfsysmcbindtask;
	#define GET_sysmcbindtask(fl)  s_pfCMGetAPI2( "sysmcbindtask", (RTS_VOID_FCTPTR *)&pfsysmcbindtask, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447), 0x03050800)
	#define CAL_sysmcbindtask  pfsysmcbindtask
	#define CHK_sysmcbindtask  (pfsysmcbindtask != NULL)
	#define EXP_sysmcbindtask   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcbindtask", (RTS_UINTPTR)sysmcbindtask, 1, RTSITF_GET_SIGNATURE(0x15C18ACA, 0xF8047447), 0x03050800) 
#endif


/**
 *Function to remove a dedicated core from the management of the runtime system.
 *This core will not be used by the runtime and is therefore exclusively available for other applications.
 */
typedef struct tagsysmcdisablecore_struct
{
	RTS_IEC_XWORD nCoreIdx;				/* VAR_INPUT */	/* Platform dependent identifier (index) of the core to remove. */
	RTS_IEC_RESULT SysMCDisableCore;	/* VAR_OUTPUT */	
} sysmcdisablecore_struct;

void CDECL CDECL_EXT sysmcdisablecore(sysmcdisablecore_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCDISABLECORE_IEC) (sysmcdisablecore_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCDISABLECORE_NOTIMPLEMENTED)
	#define USE_sysmcdisablecore
	#define EXT_sysmcdisablecore
	#define GET_sysmcdisablecore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcdisablecore(p0) 
	#define CHK_sysmcdisablecore  FALSE
	#define EXP_sysmcdisablecore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcdisablecore
	#define EXT_sysmcdisablecore
	#define GET_sysmcdisablecore(fl)  CAL_CMGETAPI( "sysmcdisablecore" ) 
	#define CAL_sysmcdisablecore  sysmcdisablecore
	#define CHK_sysmcdisablecore  TRUE
	#define EXP_sysmcdisablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcdisablecore", (RTS_UINTPTR)sysmcdisablecore, 1, RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcdisablecore
	#define EXT_sysmcdisablecore
	#define GET_sysmcdisablecore(fl)  CAL_CMGETAPI( "sysmcdisablecore" ) 
	#define CAL_sysmcdisablecore  sysmcdisablecore
	#define CHK_sysmcdisablecore  TRUE
	#define EXP_sysmcdisablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcdisablecore", (RTS_UINTPTR)sysmcdisablecore, 1, RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcdisablecore
	#define EXT_SysCpuMultiCoresysmcdisablecore
	#define GET_SysCpuMultiCoresysmcdisablecore  ERR_OK
	#define CAL_SysCpuMultiCoresysmcdisablecore  sysmcdisablecore
	#define CHK_SysCpuMultiCoresysmcdisablecore  TRUE
	#define EXP_SysCpuMultiCoresysmcdisablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcdisablecore", (RTS_UINTPTR)sysmcdisablecore, 1, RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcdisablecore
	#define EXT_sysmcdisablecore
	#define GET_sysmcdisablecore(fl)  CAL_CMGETAPI( "sysmcdisablecore" ) 
	#define CAL_sysmcdisablecore  sysmcdisablecore
	#define CHK_sysmcdisablecore  TRUE
	#define EXP_sysmcdisablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcdisablecore", (RTS_UINTPTR)sysmcdisablecore, 1, RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcdisablecore  PFSYSMCDISABLECORE_IEC pfsysmcdisablecore;
	#define EXT_sysmcdisablecore  extern PFSYSMCDISABLECORE_IEC pfsysmcdisablecore;
	#define GET_sysmcdisablecore(fl)  s_pfCMGetAPI2( "sysmcdisablecore", (RTS_VOID_FCTPTR *)&pfsysmcdisablecore, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8), 0x03050800)
	#define CAL_sysmcdisablecore  pfsysmcdisablecore
	#define CHK_sysmcdisablecore  (pfsysmcdisablecore != NULL)
	#define EXP_sysmcdisablecore   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcdisablecore", (RTS_UINTPTR)sysmcdisablecore, 1, RTSITF_GET_SIGNATURE(0x48575919, 0xD40C62F8), 0x03050800) 
#endif


/**
 *Function to add a formerlay removed dedicated core back to the management of the runtime system.
 */
typedef struct tagsysmcenablecore_struct
{
	RTS_IEC_XWORD nCoreIdx;				/* VAR_INPUT */	/* Platform dependent identifier (index) of the core. */
	RTS_IEC_RESULT SysMCEnableCore;		/* VAR_OUTPUT */	
} sysmcenablecore_struct;

void CDECL CDECL_EXT sysmcenablecore(sysmcenablecore_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCENABLECORE_IEC) (sysmcenablecore_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCENABLECORE_NOTIMPLEMENTED)
	#define USE_sysmcenablecore
	#define EXT_sysmcenablecore
	#define GET_sysmcenablecore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcenablecore(p0) 
	#define CHK_sysmcenablecore  FALSE
	#define EXP_sysmcenablecore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcenablecore
	#define EXT_sysmcenablecore
	#define GET_sysmcenablecore(fl)  CAL_CMGETAPI( "sysmcenablecore" ) 
	#define CAL_sysmcenablecore  sysmcenablecore
	#define CHK_sysmcenablecore  TRUE
	#define EXP_sysmcenablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcenablecore", (RTS_UINTPTR)sysmcenablecore, 1, RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcenablecore
	#define EXT_sysmcenablecore
	#define GET_sysmcenablecore(fl)  CAL_CMGETAPI( "sysmcenablecore" ) 
	#define CAL_sysmcenablecore  sysmcenablecore
	#define CHK_sysmcenablecore  TRUE
	#define EXP_sysmcenablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcenablecore", (RTS_UINTPTR)sysmcenablecore, 1, RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcenablecore
	#define EXT_SysCpuMultiCoresysmcenablecore
	#define GET_SysCpuMultiCoresysmcenablecore  ERR_OK
	#define CAL_SysCpuMultiCoresysmcenablecore  sysmcenablecore
	#define CHK_SysCpuMultiCoresysmcenablecore  TRUE
	#define EXP_SysCpuMultiCoresysmcenablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcenablecore", (RTS_UINTPTR)sysmcenablecore, 1, RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcenablecore
	#define EXT_sysmcenablecore
	#define GET_sysmcenablecore(fl)  CAL_CMGETAPI( "sysmcenablecore" ) 
	#define CAL_sysmcenablecore  sysmcenablecore
	#define CHK_sysmcenablecore  TRUE
	#define EXP_sysmcenablecore  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcenablecore", (RTS_UINTPTR)sysmcenablecore, 1, RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcenablecore  PFSYSMCENABLECORE_IEC pfsysmcenablecore;
	#define EXT_sysmcenablecore  extern PFSYSMCENABLECORE_IEC pfsysmcenablecore;
	#define GET_sysmcenablecore(fl)  s_pfCMGetAPI2( "sysmcenablecore", (RTS_VOID_FCTPTR *)&pfsysmcenablecore, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0), 0x03050800)
	#define CAL_sysmcenablecore  pfsysmcenablecore
	#define CHK_sysmcenablecore  (pfsysmcenablecore != NULL)
	#define EXP_sysmcenablecore   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcenablecore", (RTS_UINTPTR)sysmcenablecore, 1, RTSITF_GET_SIGNATURE(0xD975D612, 0x2F1B61C0), 0x03050800) 
#endif


/**
 * <description>sysmcgetload</description>
 */
typedef struct tagsysmcgetload_struct
{
	RTS_IEC_XWORD CoreID;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pPercent;				/* VAR_INPUT */	/* CPU-Core load in percent. */
	RTS_IEC_RESULT SysMCGetLoad;		/* VAR_OUTPUT */	
} sysmcgetload_struct;

void CDECL CDECL_EXT sysmcgetload(sysmcgetload_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETLOAD_IEC) (sysmcgetload_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETLOAD_NOTIMPLEMENTED)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgetload(p0) 
	#define CHK_sysmcgetload  FALSE
	#define EXP_sysmcgetload  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  CAL_CMGETAPI( "sysmcgetload" ) 
	#define CAL_sysmcgetload  sysmcgetload
	#define CHK_sysmcgetload  TRUE
	#define EXP_sysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  CAL_CMGETAPI( "sysmcgetload" ) 
	#define CAL_sysmcgetload  sysmcgetload
	#define CHK_sysmcgetload  TRUE
	#define EXP_sysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgetload
	#define EXT_SysCpuMultiCoresysmcgetload
	#define GET_SysCpuMultiCoresysmcgetload  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgetload  sysmcgetload
	#define CHK_SysCpuMultiCoresysmcgetload  TRUE
	#define EXP_SysCpuMultiCoresysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgetload
	#define EXT_sysmcgetload
	#define GET_sysmcgetload(fl)  CAL_CMGETAPI( "sysmcgetload" ) 
	#define CAL_sysmcgetload  sysmcgetload
	#define CHK_sysmcgetload  TRUE
	#define EXP_sysmcgetload  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgetload  PFSYSMCGETLOAD_IEC pfsysmcgetload;
	#define EXT_sysmcgetload  extern PFSYSMCGETLOAD_IEC pfsysmcgetload;
	#define GET_sysmcgetload(fl)  s_pfCMGetAPI2( "sysmcgetload", (RTS_VOID_FCTPTR *)&pfsysmcgetload, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E), 0x03050800)
	#define CAL_sysmcgetload  pfsysmcgetload
	#define CHK_sysmcgetload  (pfsysmcgetload != NULL)
	#define EXP_sysmcgetload   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetload", (RTS_UINTPTR)sysmcgetload, 1, RTSITF_GET_SIGNATURE(0x21F877E6, 0x7598BC7E), 0x03050800) 
#endif


/**
 *Returns the number of available cores.
 *Available means: Available to be used by runtime system.
 */
typedef struct tagsysmcgetnumofcores_struct
{
	RTS_IEC_RESULT *Result;				/* VAR_INPUT */	/* Pointer to retrieve optional error code. */
	RTS_IEC_DWORD SysMCGetNumOfCores;	/* VAR_OUTPUT */	
} sysmcgetnumofcores_struct;

void CDECL CDECL_EXT sysmcgetnumofcores(sysmcgetnumofcores_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETNUMOFCORES_IEC) (sysmcgetnumofcores_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNUMOFCORES_NOTIMPLEMENTED)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgetnumofcores(p0) 
	#define CHK_sysmcgetnumofcores  FALSE
	#define EXP_sysmcgetnumofcores  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  CAL_CMGETAPI( "sysmcgetnumofcores" ) 
	#define CAL_sysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  TRUE
	#define EXP_sysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0xA3C2E550, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  CAL_CMGETAPI( "sysmcgetnumofcores" ) 
	#define CAL_sysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  TRUE
	#define EXP_sysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0xA3C2E550, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgetnumofcores
	#define EXT_SysCpuMultiCoresysmcgetnumofcores
	#define GET_SysCpuMultiCoresysmcgetnumofcores  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_SysCpuMultiCoresysmcgetnumofcores  TRUE
	#define EXP_SysCpuMultiCoresysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0xA3C2E550, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgetnumofcores
	#define EXT_sysmcgetnumofcores
	#define GET_sysmcgetnumofcores(fl)  CAL_CMGETAPI( "sysmcgetnumofcores" ) 
	#define CAL_sysmcgetnumofcores  sysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  TRUE
	#define EXP_sysmcgetnumofcores  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0xA3C2E550, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgetnumofcores  PFSYSMCGETNUMOFCORES_IEC pfsysmcgetnumofcores;
	#define EXT_sysmcgetnumofcores  extern PFSYSMCGETNUMOFCORES_IEC pfsysmcgetnumofcores;
	#define GET_sysmcgetnumofcores(fl)  s_pfCMGetAPI2( "sysmcgetnumofcores", (RTS_VOID_FCTPTR *)&pfsysmcgetnumofcores, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA3C2E550, 0x03050800)
	#define CAL_sysmcgetnumofcores  pfsysmcgetnumofcores
	#define CHK_sysmcgetnumofcores  (pfsysmcgetnumofcores != NULL)
	#define EXP_sysmcgetnumofcores   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetnumofcores", (RTS_UINTPTR)sysmcgetnumofcores, 1, 0xA3C2E550, 0x03050800) 
#endif


/**
 *Read the binding description of a process.
 */
typedef struct tagsysmcgetprocessbinding_struct
{
	RTS_IEC_HANDLE hProcess;				/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetProcessBinding;	/* VAR_OUTPUT */	
} sysmcgetprocessbinding_struct;

void CDECL CDECL_EXT sysmcgetprocessbinding(sysmcgetprocessbinding_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETPROCESSBINDING_IEC) (sysmcgetprocessbinding_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETPROCESSBINDING_NOTIMPLEMENTED)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgetprocessbinding(p0) 
	#define CHK_sysmcgetprocessbinding  FALSE
	#define EXP_sysmcgetprocessbinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  CAL_CMGETAPI( "sysmcgetprocessbinding" ) 
	#define CAL_sysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  TRUE
	#define EXP_sysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  CAL_CMGETAPI( "sysmcgetprocessbinding" ) 
	#define CAL_sysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  TRUE
	#define EXP_sysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgetprocessbinding
	#define EXT_SysCpuMultiCoresysmcgetprocessbinding
	#define GET_SysCpuMultiCoresysmcgetprocessbinding  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_SysCpuMultiCoresysmcgetprocessbinding  TRUE
	#define EXP_SysCpuMultiCoresysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgetprocessbinding
	#define EXT_sysmcgetprocessbinding
	#define GET_sysmcgetprocessbinding(fl)  CAL_CMGETAPI( "sysmcgetprocessbinding" ) 
	#define CAL_sysmcgetprocessbinding  sysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  TRUE
	#define EXP_sysmcgetprocessbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgetprocessbinding  PFSYSMCGETPROCESSBINDING_IEC pfsysmcgetprocessbinding;
	#define EXT_sysmcgetprocessbinding  extern PFSYSMCGETPROCESSBINDING_IEC pfsysmcgetprocessbinding;
	#define GET_sysmcgetprocessbinding(fl)  s_pfCMGetAPI2( "sysmcgetprocessbinding", (RTS_VOID_FCTPTR *)&pfsysmcgetprocessbinding, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917), 0x03050800)
	#define CAL_sysmcgetprocessbinding  pfsysmcgetprocessbinding
	#define CHK_sysmcgetprocessbinding  (pfsysmcgetprocessbinding != NULL)
	#define EXP_sysmcgetprocessbinding   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgetprocessbinding", (RTS_UINTPTR)sysmcgetprocessbinding, 1, RTSITF_GET_SIGNATURE(0x6877335F, 0x9C17E917), 0x03050800) 
#endif


/**
 *Read the binding description of a task.
 */
typedef struct tagsysmcgettaskbinding_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	CpuCoreBindingDesc *pBindingDesc;	/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCGetTaskBinding;	/* VAR_OUTPUT */	
} sysmcgettaskbinding_struct;

void CDECL CDECL_EXT sysmcgettaskbinding(sysmcgettaskbinding_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCGETTASKBINDING_IEC) (sysmcgettaskbinding_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKBINDING_NOTIMPLEMENTED)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcgettaskbinding(p0) 
	#define CHK_sysmcgettaskbinding  FALSE
	#define EXP_sysmcgettaskbinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  CAL_CMGETAPI( "sysmcgettaskbinding" ) 
	#define CAL_sysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  TRUE
	#define EXP_sysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A), 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  CAL_CMGETAPI( "sysmcgettaskbinding" ) 
	#define CAL_sysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  TRUE
	#define EXP_sysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A), 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcgettaskbinding
	#define EXT_SysCpuMultiCoresysmcgettaskbinding
	#define GET_SysCpuMultiCoresysmcgettaskbinding  ERR_OK
	#define CAL_SysCpuMultiCoresysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_SysCpuMultiCoresysmcgettaskbinding  TRUE
	#define EXP_SysCpuMultiCoresysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A), 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcgettaskbinding
	#define EXT_sysmcgettaskbinding
	#define GET_sysmcgettaskbinding(fl)  CAL_CMGETAPI( "sysmcgettaskbinding" ) 
	#define CAL_sysmcgettaskbinding  sysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  TRUE
	#define EXP_sysmcgettaskbinding  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A), 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcgettaskbinding  PFSYSMCGETTASKBINDING_IEC pfsysmcgettaskbinding;
	#define EXT_sysmcgettaskbinding  extern PFSYSMCGETTASKBINDING_IEC pfsysmcgettaskbinding;
	#define GET_sysmcgettaskbinding(fl)  s_pfCMGetAPI2( "sysmcgettaskbinding", (RTS_VOID_FCTPTR *)&pfsysmcgettaskbinding, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A), 0x03050800)
	#define CAL_sysmcgettaskbinding  pfsysmcgettaskbinding
	#define CHK_sysmcgettaskbinding  (pfsysmcgettaskbinding != NULL)
	#define EXP_sysmcgettaskbinding   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcgettaskbinding", (RTS_UINTPTR)sysmcgettaskbinding, 1, RTSITF_GET_SIGNATURE(0xF701342B, 0x0023E80A), 0x03050800) 
#endif


/**
 *Function to remove the core binding of a process.
 * 
 */
typedef struct tagsysmcunbindprocess_struct
{
	RTS_IEC_HANDLE hProcess;			/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCUnbindProcess;	/* VAR_OUTPUT */	
} sysmcunbindprocess_struct;

void CDECL CDECL_EXT sysmcunbindprocess(sysmcunbindprocess_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCUNBINDPROCESS_IEC) (sysmcunbindprocess_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDPROCESS_NOTIMPLEMENTED)
	#define USE_sysmcunbindprocess
	#define EXT_sysmcunbindprocess
	#define GET_sysmcunbindprocess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcunbindprocess(p0) 
	#define CHK_sysmcunbindprocess  FALSE
	#define EXP_sysmcunbindprocess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcunbindprocess
	#define EXT_sysmcunbindprocess
	#define GET_sysmcunbindprocess(fl)  CAL_CMGETAPI( "sysmcunbindprocess" ) 
	#define CAL_sysmcunbindprocess  sysmcunbindprocess
	#define CHK_sysmcunbindprocess  TRUE
	#define EXP_sysmcunbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindprocess", (RTS_UINTPTR)sysmcunbindprocess, 1, 0x91976CA3, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcunbindprocess
	#define EXT_sysmcunbindprocess
	#define GET_sysmcunbindprocess(fl)  CAL_CMGETAPI( "sysmcunbindprocess" ) 
	#define CAL_sysmcunbindprocess  sysmcunbindprocess
	#define CHK_sysmcunbindprocess  TRUE
	#define EXP_sysmcunbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindprocess", (RTS_UINTPTR)sysmcunbindprocess, 1, 0x91976CA3, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcunbindprocess
	#define EXT_SysCpuMultiCoresysmcunbindprocess
	#define GET_SysCpuMultiCoresysmcunbindprocess  ERR_OK
	#define CAL_SysCpuMultiCoresysmcunbindprocess  sysmcunbindprocess
	#define CHK_SysCpuMultiCoresysmcunbindprocess  TRUE
	#define EXP_SysCpuMultiCoresysmcunbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindprocess", (RTS_UINTPTR)sysmcunbindprocess, 1, 0x91976CA3, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcunbindprocess
	#define EXT_sysmcunbindprocess
	#define GET_sysmcunbindprocess(fl)  CAL_CMGETAPI( "sysmcunbindprocess" ) 
	#define CAL_sysmcunbindprocess  sysmcunbindprocess
	#define CHK_sysmcunbindprocess  TRUE
	#define EXP_sysmcunbindprocess  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindprocess", (RTS_UINTPTR)sysmcunbindprocess, 1, 0x91976CA3, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcunbindprocess  PFSYSMCUNBINDPROCESS_IEC pfsysmcunbindprocess;
	#define EXT_sysmcunbindprocess  extern PFSYSMCUNBINDPROCESS_IEC pfsysmcunbindprocess;
	#define GET_sysmcunbindprocess(fl)  s_pfCMGetAPI2( "sysmcunbindprocess", (RTS_VOID_FCTPTR *)&pfsysmcunbindprocess, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x91976CA3, 0x03050800)
	#define CAL_sysmcunbindprocess  pfsysmcunbindprocess
	#define CHK_sysmcunbindprocess  (pfsysmcunbindprocess != NULL)
	#define EXP_sysmcunbindprocess   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindprocess", (RTS_UINTPTR)sysmcunbindprocess, 1, 0x91976CA3, 0x03050800) 
#endif


/**
 * <description>sysmcunbindtask</description>
 */
typedef struct tagsysmcunbindtask_struct
{
	RTS_IEC_HANDLE hTask;				/* VAR_INPUT */	
	RTS_IEC_RESULT SysMCUnbindTask;		/* VAR_OUTPUT */	
} sysmcunbindtask_struct;

void CDECL CDECL_EXT sysmcunbindtask(sysmcunbindtask_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSMCUNBINDTASK_IEC) (sysmcunbindtask_struct *p);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDTASK_NOTIMPLEMENTED)
	#define USE_sysmcunbindtask
	#define EXT_sysmcunbindtask
	#define GET_sysmcunbindtask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_sysmcunbindtask(p0) 
	#define CHK_sysmcunbindtask  FALSE
	#define EXP_sysmcunbindtask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_sysmcunbindtask
	#define EXT_sysmcunbindtask
	#define GET_sysmcunbindtask(fl)  CAL_CMGETAPI( "sysmcunbindtask" ) 
	#define CAL_sysmcunbindtask  sysmcunbindtask
	#define CHK_sysmcunbindtask  TRUE
	#define EXP_sysmcunbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindtask", (RTS_UINTPTR)sysmcunbindtask, 1, 0x7D06154E, 0x03050800) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_sysmcunbindtask
	#define EXT_sysmcunbindtask
	#define GET_sysmcunbindtask(fl)  CAL_CMGETAPI( "sysmcunbindtask" ) 
	#define CAL_sysmcunbindtask  sysmcunbindtask
	#define CHK_sysmcunbindtask  TRUE
	#define EXP_sysmcunbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindtask", (RTS_UINTPTR)sysmcunbindtask, 1, 0x7D06154E, 0x03050800) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoresysmcunbindtask
	#define EXT_SysCpuMultiCoresysmcunbindtask
	#define GET_SysCpuMultiCoresysmcunbindtask  ERR_OK
	#define CAL_SysCpuMultiCoresysmcunbindtask  sysmcunbindtask
	#define CHK_SysCpuMultiCoresysmcunbindtask  TRUE
	#define EXP_SysCpuMultiCoresysmcunbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindtask", (RTS_UINTPTR)sysmcunbindtask, 1, 0x7D06154E, 0x03050800) 
#elif defined(CPLUSPLUS)
	#define USE_sysmcunbindtask
	#define EXT_sysmcunbindtask
	#define GET_sysmcunbindtask(fl)  CAL_CMGETAPI( "sysmcunbindtask" ) 
	#define CAL_sysmcunbindtask  sysmcunbindtask
	#define CHK_sysmcunbindtask  TRUE
	#define EXP_sysmcunbindtask  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindtask", (RTS_UINTPTR)sysmcunbindtask, 1, 0x7D06154E, 0x03050800) 
#else /* DYNAMIC_LINK */
	#define USE_sysmcunbindtask  PFSYSMCUNBINDTASK_IEC pfsysmcunbindtask;
	#define EXT_sysmcunbindtask  extern PFSYSMCUNBINDTASK_IEC pfsysmcunbindtask;
	#define GET_sysmcunbindtask(fl)  s_pfCMGetAPI2( "sysmcunbindtask", (RTS_VOID_FCTPTR *)&pfsysmcunbindtask, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7D06154E, 0x03050800)
	#define CAL_sysmcunbindtask  pfsysmcunbindtask
	#define CHK_sysmcunbindtask  (pfsysmcunbindtask != NULL)
	#define EXP_sysmcunbindtask   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"sysmcunbindtask", (RTS_UINTPTR)sysmcunbindtask, 1, 0x7D06154E, 0x03050800) 
#endif


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
RTS_RESULT CDECL SysMCBindProcess(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCBINDPROCESS) (CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDPROCESS_NOTIMPLEMENTED)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindProcess(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindProcess  FALSE
	#define EXP_SysMCBindProcess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  CAL_CMGETAPI( "SysMCBindProcess" ) 
	#define CAL_SysMCBindProcess  SysMCBindProcess
	#define CHK_SysMCBindProcess  TRUE
	#define EXP_SysMCBindProcess  CAL_CMEXPAPI( "SysMCBindProcess" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  CAL_CMGETAPI( "SysMCBindProcess" ) 
	#define CAL_SysMCBindProcess  SysMCBindProcess
	#define CHK_SysMCBindProcess  TRUE
	#define EXP_SysMCBindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess", (RTS_UINTPTR)SysMCBindProcess, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindProcess
	#define EXT_SysCpuMultiCoreSysMCBindProcess
	#define GET_SysCpuMultiCoreSysMCBindProcess  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindProcess pISysCpuMultiCore->ISysMCBindProcess
	#define CHK_SysCpuMultiCoreSysMCBindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindProcess  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindProcess
	#define EXT_SysMCBindProcess
	#define GET_SysMCBindProcess(fl)  CAL_CMGETAPI( "SysMCBindProcess" ) 
	#define CAL_SysMCBindProcess pISysCpuMultiCore->ISysMCBindProcess
	#define CHK_SysMCBindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindProcess  CAL_CMEXPAPI( "SysMCBindProcess" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindProcess  PFSYSMCBINDPROCESS pfSysMCBindProcess;
	#define EXT_SysMCBindProcess  extern PFSYSMCBINDPROCESS pfSysMCBindProcess;
	#define GET_SysMCBindProcess(fl)  s_pfCMGetAPI2( "SysMCBindProcess", (RTS_VOID_FCTPTR *)&pfSysMCBindProcess, (fl), 0, 0)
	#define CAL_SysMCBindProcess  pfSysMCBindProcess
	#define CHK_SysMCBindProcess  (pfSysMCBindProcess != NULL)
	#define EXP_SysMCBindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess", (RTS_UINTPTR)SysMCBindProcess, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCBindProcess
 * </description>
 */
RTS_RESULT CDECL SysMCBindProcess_(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCBINDPROCESS_) (CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDPROCESS__NOTIMPLEMENTED)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindProcess_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindProcess_  FALSE
	#define EXP_SysMCBindProcess_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  CAL_CMGETAPI( "SysMCBindProcess_" ) 
	#define CAL_SysMCBindProcess_  SysMCBindProcess_
	#define CHK_SysMCBindProcess_  TRUE
	#define EXP_SysMCBindProcess_  CAL_CMEXPAPI( "SysMCBindProcess_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  CAL_CMGETAPI( "SysMCBindProcess_" ) 
	#define CAL_SysMCBindProcess_  SysMCBindProcess_
	#define CHK_SysMCBindProcess_  TRUE
	#define EXP_SysMCBindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess_", (RTS_UINTPTR)SysMCBindProcess_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindProcess_
	#define EXT_SysCpuMultiCoreSysMCBindProcess_
	#define GET_SysCpuMultiCoreSysMCBindProcess_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindProcess_ pISysCpuMultiCore->ISysMCBindProcess_
	#define CHK_SysCpuMultiCoreSysMCBindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindProcess_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindProcess_
	#define EXT_SysMCBindProcess_
	#define GET_SysMCBindProcess_(fl)  CAL_CMGETAPI( "SysMCBindProcess_" ) 
	#define CAL_SysMCBindProcess_ pISysCpuMultiCore->ISysMCBindProcess_
	#define CHK_SysMCBindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindProcess_  CAL_CMEXPAPI( "SysMCBindProcess_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindProcess_  PFSYSMCBINDPROCESS_ pfSysMCBindProcess_;
	#define EXT_SysMCBindProcess_  extern PFSYSMCBINDPROCESS_ pfSysMCBindProcess_;
	#define GET_SysMCBindProcess_(fl)  s_pfCMGetAPI2( "SysMCBindProcess_", (RTS_VOID_FCTPTR *)&pfSysMCBindProcess_, (fl), 0, 0)
	#define CAL_SysMCBindProcess_  pfSysMCBindProcess_
	#define CHK_SysMCBindProcess_  (pfSysMCBindProcess_ != NULL)
	#define EXP_SysMCBindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindProcess_", (RTS_UINTPTR)SysMCBindProcess_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCBindTask(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCBINDTASK) (CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDTASK_NOTIMPLEMENTED)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindTask(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindTask  FALSE
	#define EXP_SysMCBindTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  CAL_CMGETAPI( "SysMCBindTask" ) 
	#define CAL_SysMCBindTask  SysMCBindTask
	#define CHK_SysMCBindTask  TRUE
	#define EXP_SysMCBindTask  CAL_CMEXPAPI( "SysMCBindTask" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  CAL_CMGETAPI( "SysMCBindTask" ) 
	#define CAL_SysMCBindTask  SysMCBindTask
	#define CHK_SysMCBindTask  TRUE
	#define EXP_SysMCBindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask", (RTS_UINTPTR)SysMCBindTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindTask
	#define EXT_SysCpuMultiCoreSysMCBindTask
	#define GET_SysCpuMultiCoreSysMCBindTask  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindTask pISysCpuMultiCore->ISysMCBindTask
	#define CHK_SysCpuMultiCoreSysMCBindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindTask
	#define EXT_SysMCBindTask
	#define GET_SysMCBindTask(fl)  CAL_CMGETAPI( "SysMCBindTask" ) 
	#define CAL_SysMCBindTask pISysCpuMultiCore->ISysMCBindTask
	#define CHK_SysMCBindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindTask  CAL_CMEXPAPI( "SysMCBindTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindTask  PFSYSMCBINDTASK pfSysMCBindTask;
	#define EXT_SysMCBindTask  extern PFSYSMCBINDTASK pfSysMCBindTask;
	#define GET_SysMCBindTask(fl)  s_pfCMGetAPI2( "SysMCBindTask", (RTS_VOID_FCTPTR *)&pfSysMCBindTask, (fl), 0, 0)
	#define CAL_SysMCBindTask  pfSysMCBindTask
	#define CHK_SysMCBindTask  (pfSysMCBindTask != NULL)
	#define EXP_SysMCBindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask", (RTS_UINTPTR)SysMCBindTask, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCBindTask
 * </description>
 */
RTS_RESULT CDECL SysMCBindTask_(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCBINDTASK_) (CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCBINDTASK__NOTIMPLEMENTED)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCBindTask_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCBindTask_  FALSE
	#define EXP_SysMCBindTask_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  CAL_CMGETAPI( "SysMCBindTask_" ) 
	#define CAL_SysMCBindTask_  SysMCBindTask_
	#define CHK_SysMCBindTask_  TRUE
	#define EXP_SysMCBindTask_  CAL_CMEXPAPI( "SysMCBindTask_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  CAL_CMGETAPI( "SysMCBindTask_" ) 
	#define CAL_SysMCBindTask_  SysMCBindTask_
	#define CHK_SysMCBindTask_  TRUE
	#define EXP_SysMCBindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask_", (RTS_UINTPTR)SysMCBindTask_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCBindTask_
	#define EXT_SysCpuMultiCoreSysMCBindTask_
	#define GET_SysCpuMultiCoreSysMCBindTask_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCBindTask_ pISysCpuMultiCore->ISysMCBindTask_
	#define CHK_SysCpuMultiCoreSysMCBindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCBindTask_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCBindTask_
	#define EXT_SysMCBindTask_
	#define GET_SysMCBindTask_(fl)  CAL_CMGETAPI( "SysMCBindTask_" ) 
	#define CAL_SysMCBindTask_ pISysCpuMultiCore->ISysMCBindTask_
	#define CHK_SysMCBindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCBindTask_  CAL_CMEXPAPI( "SysMCBindTask_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCBindTask_  PFSYSMCBINDTASK_ pfSysMCBindTask_;
	#define EXT_SysMCBindTask_  extern PFSYSMCBINDTASK_ pfSysMCBindTask_;
	#define GET_SysMCBindTask_(fl)  s_pfCMGetAPI2( "SysMCBindTask_", (RTS_VOID_FCTPTR *)&pfSysMCBindTask_, (fl), 0, 0)
	#define CAL_SysMCBindTask_  pfSysMCBindTask_
	#define CHK_SysMCBindTask_  (pfSysMCBindTask_ != NULL)
	#define EXP_SysMCBindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCBindTask_", (RTS_UINTPTR)SysMCBindTask_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCUnbindProcess(RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDPROCESS) (RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDPROCESS_NOTIMPLEMENTED)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindProcess(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindProcess  FALSE
	#define EXP_SysMCUnbindProcess  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  CAL_CMGETAPI( "SysMCUnbindProcess" ) 
	#define CAL_SysMCUnbindProcess  SysMCUnbindProcess
	#define CHK_SysMCUnbindProcess  TRUE
	#define EXP_SysMCUnbindProcess  CAL_CMEXPAPI( "SysMCUnbindProcess" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  CAL_CMGETAPI( "SysMCUnbindProcess" ) 
	#define CAL_SysMCUnbindProcess  SysMCUnbindProcess
	#define CHK_SysMCUnbindProcess  TRUE
	#define EXP_SysMCUnbindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess", (RTS_UINTPTR)SysMCUnbindProcess, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindProcess
	#define EXT_SysCpuMultiCoreSysMCUnbindProcess
	#define GET_SysCpuMultiCoreSysMCUnbindProcess  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindProcess pISysCpuMultiCore->ISysMCUnbindProcess
	#define CHK_SysCpuMultiCoreSysMCUnbindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindProcess  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindProcess
	#define EXT_SysMCUnbindProcess
	#define GET_SysMCUnbindProcess(fl)  CAL_CMGETAPI( "SysMCUnbindProcess" ) 
	#define CAL_SysMCUnbindProcess pISysCpuMultiCore->ISysMCUnbindProcess
	#define CHK_SysMCUnbindProcess (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindProcess  CAL_CMEXPAPI( "SysMCUnbindProcess" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindProcess  PFSYSMCUNBINDPROCESS pfSysMCUnbindProcess;
	#define EXT_SysMCUnbindProcess  extern PFSYSMCUNBINDPROCESS pfSysMCUnbindProcess;
	#define GET_SysMCUnbindProcess(fl)  s_pfCMGetAPI2( "SysMCUnbindProcess", (RTS_VOID_FCTPTR *)&pfSysMCUnbindProcess, (fl), 0, 0)
	#define CAL_SysMCUnbindProcess  pfSysMCUnbindProcess
	#define CHK_SysMCUnbindProcess  (pfSysMCUnbindProcess != NULL)
	#define EXP_SysMCUnbindProcess  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess", (RTS_UINTPTR)SysMCUnbindProcess, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCUnbindProcess
 * </description>
 */
RTS_RESULT CDECL SysMCUnbindProcess_(RTS_IEC_HANDLE hProcess);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDPROCESS_) (RTS_IEC_HANDLE hProcess);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDPROCESS__NOTIMPLEMENTED)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindProcess_(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindProcess_  FALSE
	#define EXP_SysMCUnbindProcess_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  CAL_CMGETAPI( "SysMCUnbindProcess_" ) 
	#define CAL_SysMCUnbindProcess_  SysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_  TRUE
	#define EXP_SysMCUnbindProcess_  CAL_CMEXPAPI( "SysMCUnbindProcess_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  CAL_CMGETAPI( "SysMCUnbindProcess_" ) 
	#define CAL_SysMCUnbindProcess_  SysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_  TRUE
	#define EXP_SysMCUnbindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess_", (RTS_UINTPTR)SysMCUnbindProcess_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindProcess_
	#define EXT_SysCpuMultiCoreSysMCUnbindProcess_
	#define GET_SysCpuMultiCoreSysMCUnbindProcess_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindProcess_ pISysCpuMultiCore->ISysMCUnbindProcess_
	#define CHK_SysCpuMultiCoreSysMCUnbindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindProcess_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindProcess_
	#define EXT_SysMCUnbindProcess_
	#define GET_SysMCUnbindProcess_(fl)  CAL_CMGETAPI( "SysMCUnbindProcess_" ) 
	#define CAL_SysMCUnbindProcess_ pISysCpuMultiCore->ISysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindProcess_  CAL_CMEXPAPI( "SysMCUnbindProcess_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindProcess_  PFSYSMCUNBINDPROCESS_ pfSysMCUnbindProcess_;
	#define EXT_SysMCUnbindProcess_  extern PFSYSMCUNBINDPROCESS_ pfSysMCUnbindProcess_;
	#define GET_SysMCUnbindProcess_(fl)  s_pfCMGetAPI2( "SysMCUnbindProcess_", (RTS_VOID_FCTPTR *)&pfSysMCUnbindProcess_, (fl), 0, 0)
	#define CAL_SysMCUnbindProcess_  pfSysMCUnbindProcess_
	#define CHK_SysMCUnbindProcess_  (pfSysMCUnbindProcess_ != NULL)
	#define EXP_SysMCUnbindProcess_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindProcess_", (RTS_UINTPTR)SysMCUnbindProcess_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCUnbindTask(RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDTASK) (RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDTASK_NOTIMPLEMENTED)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindTask(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindTask  FALSE
	#define EXP_SysMCUnbindTask  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  CAL_CMGETAPI( "SysMCUnbindTask" ) 
	#define CAL_SysMCUnbindTask  SysMCUnbindTask
	#define CHK_SysMCUnbindTask  TRUE
	#define EXP_SysMCUnbindTask  CAL_CMEXPAPI( "SysMCUnbindTask" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  CAL_CMGETAPI( "SysMCUnbindTask" ) 
	#define CAL_SysMCUnbindTask  SysMCUnbindTask
	#define CHK_SysMCUnbindTask  TRUE
	#define EXP_SysMCUnbindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask", (RTS_UINTPTR)SysMCUnbindTask, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindTask
	#define EXT_SysCpuMultiCoreSysMCUnbindTask
	#define GET_SysCpuMultiCoreSysMCUnbindTask  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindTask pISysCpuMultiCore->ISysMCUnbindTask
	#define CHK_SysCpuMultiCoreSysMCUnbindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindTask  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindTask
	#define EXT_SysMCUnbindTask
	#define GET_SysMCUnbindTask(fl)  CAL_CMGETAPI( "SysMCUnbindTask" ) 
	#define CAL_SysMCUnbindTask pISysCpuMultiCore->ISysMCUnbindTask
	#define CHK_SysMCUnbindTask (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindTask  CAL_CMEXPAPI( "SysMCUnbindTask" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindTask  PFSYSMCUNBINDTASK pfSysMCUnbindTask;
	#define EXT_SysMCUnbindTask  extern PFSYSMCUNBINDTASK pfSysMCUnbindTask;
	#define GET_SysMCUnbindTask(fl)  s_pfCMGetAPI2( "SysMCUnbindTask", (RTS_VOID_FCTPTR *)&pfSysMCUnbindTask, (fl), 0, 0)
	#define CAL_SysMCUnbindTask  pfSysMCUnbindTask
	#define CHK_SysMCUnbindTask  (pfSysMCUnbindTask != NULL)
	#define EXP_SysMCUnbindTask  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask", (RTS_UINTPTR)SysMCUnbindTask, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCUnbindTask
 * </description>
 */
RTS_RESULT CDECL SysMCUnbindTask_(RTS_IEC_HANDLE hTask);
typedef RTS_RESULT (CDECL * PFSYSMCUNBINDTASK_) (RTS_IEC_HANDLE hTask);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCUNBINDTASK__NOTIMPLEMENTED)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCUnbindTask_(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCUnbindTask_  FALSE
	#define EXP_SysMCUnbindTask_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  CAL_CMGETAPI( "SysMCUnbindTask_" ) 
	#define CAL_SysMCUnbindTask_  SysMCUnbindTask_
	#define CHK_SysMCUnbindTask_  TRUE
	#define EXP_SysMCUnbindTask_  CAL_CMEXPAPI( "SysMCUnbindTask_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  CAL_CMGETAPI( "SysMCUnbindTask_" ) 
	#define CAL_SysMCUnbindTask_  SysMCUnbindTask_
	#define CHK_SysMCUnbindTask_  TRUE
	#define EXP_SysMCUnbindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask_", (RTS_UINTPTR)SysMCUnbindTask_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCUnbindTask_
	#define EXT_SysCpuMultiCoreSysMCUnbindTask_
	#define GET_SysCpuMultiCoreSysMCUnbindTask_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCUnbindTask_ pISysCpuMultiCore->ISysMCUnbindTask_
	#define CHK_SysCpuMultiCoreSysMCUnbindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCUnbindTask_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCUnbindTask_
	#define EXT_SysMCUnbindTask_
	#define GET_SysMCUnbindTask_(fl)  CAL_CMGETAPI( "SysMCUnbindTask_" ) 
	#define CAL_SysMCUnbindTask_ pISysCpuMultiCore->ISysMCUnbindTask_
	#define CHK_SysMCUnbindTask_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCUnbindTask_  CAL_CMEXPAPI( "SysMCUnbindTask_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCUnbindTask_  PFSYSMCUNBINDTASK_ pfSysMCUnbindTask_;
	#define EXT_SysMCUnbindTask_  extern PFSYSMCUNBINDTASK_ pfSysMCUnbindTask_;
	#define GET_SysMCUnbindTask_(fl)  s_pfCMGetAPI2( "SysMCUnbindTask_", (RTS_VOID_FCTPTR *)&pfSysMCUnbindTask_, (fl), 0, 0)
	#define CAL_SysMCUnbindTask_  pfSysMCUnbindTask_
	#define CHK_SysMCUnbindTask_  (pfSysMCUnbindTask_ != NULL)
	#define EXP_SysMCUnbindTask_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCUnbindTask_", (RTS_UINTPTR)SysMCUnbindTask_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCGetLoad(RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent);
typedef RTS_RESULT (CDECL * PFSYSMCGETLOAD) (RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETLOAD_NOTIMPLEMENTED)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetLoad(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetLoad  FALSE
	#define EXP_SysMCGetLoad  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  CAL_CMGETAPI( "SysMCGetLoad" ) 
	#define CAL_SysMCGetLoad  SysMCGetLoad
	#define CHK_SysMCGetLoad  TRUE
	#define EXP_SysMCGetLoad  CAL_CMEXPAPI( "SysMCGetLoad" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  CAL_CMGETAPI( "SysMCGetLoad" ) 
	#define CAL_SysMCGetLoad  SysMCGetLoad
	#define CHK_SysMCGetLoad  TRUE
	#define EXP_SysMCGetLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad", (RTS_UINTPTR)SysMCGetLoad, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetLoad
	#define EXT_SysCpuMultiCoreSysMCGetLoad
	#define GET_SysCpuMultiCoreSysMCGetLoad  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetLoad pISysCpuMultiCore->ISysMCGetLoad
	#define CHK_SysCpuMultiCoreSysMCGetLoad (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetLoad  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetLoad
	#define EXT_SysMCGetLoad
	#define GET_SysMCGetLoad(fl)  CAL_CMGETAPI( "SysMCGetLoad" ) 
	#define CAL_SysMCGetLoad pISysCpuMultiCore->ISysMCGetLoad
	#define CHK_SysMCGetLoad (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetLoad  CAL_CMEXPAPI( "SysMCGetLoad" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetLoad  PFSYSMCGETLOAD pfSysMCGetLoad;
	#define EXT_SysMCGetLoad  extern PFSYSMCGETLOAD pfSysMCGetLoad;
	#define GET_SysMCGetLoad(fl)  s_pfCMGetAPI2( "SysMCGetLoad", (RTS_VOID_FCTPTR *)&pfSysMCGetLoad, (fl), 0, 0)
	#define CAL_SysMCGetLoad  pfSysMCGetLoad
	#define CHK_SysMCGetLoad  (pfSysMCGetLoad != NULL)
	#define EXP_SysMCGetLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad", (RTS_UINTPTR)SysMCGetLoad, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetLoad
 * </description>
 */
RTS_RESULT CDECL SysMCGetLoad_(RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent);
typedef RTS_RESULT (CDECL * PFSYSMCGETLOAD_) (RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETLOAD__NOTIMPLEMENTED)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetLoad_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetLoad_  FALSE
	#define EXP_SysMCGetLoad_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  CAL_CMGETAPI( "SysMCGetLoad_" ) 
	#define CAL_SysMCGetLoad_  SysMCGetLoad_
	#define CHK_SysMCGetLoad_  TRUE
	#define EXP_SysMCGetLoad_  CAL_CMEXPAPI( "SysMCGetLoad_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  CAL_CMGETAPI( "SysMCGetLoad_" ) 
	#define CAL_SysMCGetLoad_  SysMCGetLoad_
	#define CHK_SysMCGetLoad_  TRUE
	#define EXP_SysMCGetLoad_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad_", (RTS_UINTPTR)SysMCGetLoad_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetLoad_
	#define EXT_SysCpuMultiCoreSysMCGetLoad_
	#define GET_SysCpuMultiCoreSysMCGetLoad_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetLoad_ pISysCpuMultiCore->ISysMCGetLoad_
	#define CHK_SysCpuMultiCoreSysMCGetLoad_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetLoad_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetLoad_
	#define EXT_SysMCGetLoad_
	#define GET_SysMCGetLoad_(fl)  CAL_CMGETAPI( "SysMCGetLoad_" ) 
	#define CAL_SysMCGetLoad_ pISysCpuMultiCore->ISysMCGetLoad_
	#define CHK_SysMCGetLoad_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetLoad_  CAL_CMEXPAPI( "SysMCGetLoad_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetLoad_  PFSYSMCGETLOAD_ pfSysMCGetLoad_;
	#define EXT_SysMCGetLoad_  extern PFSYSMCGETLOAD_ pfSysMCGetLoad_;
	#define GET_SysMCGetLoad_(fl)  s_pfCMGetAPI2( "SysMCGetLoad_", (RTS_VOID_FCTPTR *)&pfSysMCGetLoad_, (fl), 0, 0)
	#define CAL_SysMCGetLoad_  pfSysMCGetLoad_
	#define CHK_SysMCGetLoad_  (pfSysMCGetLoad_ != NULL)
	#define EXP_SysMCGetLoad_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetLoad_", (RTS_UINTPTR)SysMCGetLoad_, 0, 0) 
#endif




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
RTS_UI32 CDECL SysMCGetNumOfCores(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETNUMOFCORES) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNUMOFCORES_NOTIMPLEMENTED)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetNumOfCores(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetNumOfCores  FALSE
	#define EXP_SysMCGetNumOfCores  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores" ) 
	#define CAL_SysMCGetNumOfCores  SysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores  TRUE
	#define EXP_SysMCGetNumOfCores  CAL_CMEXPAPI( "SysMCGetNumOfCores" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores" ) 
	#define CAL_SysMCGetNumOfCores  SysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores  TRUE
	#define EXP_SysMCGetNumOfCores  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores", (RTS_UINTPTR)SysMCGetNumOfCores, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetNumOfCores
	#define EXT_SysCpuMultiCoreSysMCGetNumOfCores
	#define GET_SysCpuMultiCoreSysMCGetNumOfCores  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetNumOfCores pISysCpuMultiCore->ISysMCGetNumOfCores
	#define CHK_SysCpuMultiCoreSysMCGetNumOfCores (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetNumOfCores  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetNumOfCores
	#define EXT_SysMCGetNumOfCores
	#define GET_SysMCGetNumOfCores(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores" ) 
	#define CAL_SysMCGetNumOfCores pISysCpuMultiCore->ISysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetNumOfCores  CAL_CMEXPAPI( "SysMCGetNumOfCores" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetNumOfCores  PFSYSMCGETNUMOFCORES pfSysMCGetNumOfCores;
	#define EXT_SysMCGetNumOfCores  extern PFSYSMCGETNUMOFCORES pfSysMCGetNumOfCores;
	#define GET_SysMCGetNumOfCores(fl)  s_pfCMGetAPI2( "SysMCGetNumOfCores", (RTS_VOID_FCTPTR *)&pfSysMCGetNumOfCores, (fl), 0, 0)
	#define CAL_SysMCGetNumOfCores  pfSysMCGetNumOfCores
	#define CHK_SysMCGetNumOfCores  (pfSysMCGetNumOfCores != NULL)
	#define EXP_SysMCGetNumOfCores  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores", (RTS_UINTPTR)SysMCGetNumOfCores, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetNumOfCores
 * </description>
 */
RTS_UI32 CDECL SysMCGetNumOfCores_(RTS_RESULT* pResult);
typedef RTS_UI32 (CDECL * PFSYSMCGETNUMOFCORES_) (RTS_RESULT* pResult);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETNUMOFCORES__NOTIMPLEMENTED)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetNumOfCores_(p0)  (RTS_UI32)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetNumOfCores_  FALSE
	#define EXP_SysMCGetNumOfCores_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores_" ) 
	#define CAL_SysMCGetNumOfCores_  SysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_  TRUE
	#define EXP_SysMCGetNumOfCores_  CAL_CMEXPAPI( "SysMCGetNumOfCores_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores_" ) 
	#define CAL_SysMCGetNumOfCores_  SysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_  TRUE
	#define EXP_SysMCGetNumOfCores_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores_", (RTS_UINTPTR)SysMCGetNumOfCores_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetNumOfCores_
	#define EXT_SysCpuMultiCoreSysMCGetNumOfCores_
	#define GET_SysCpuMultiCoreSysMCGetNumOfCores_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetNumOfCores_ pISysCpuMultiCore->ISysMCGetNumOfCores_
	#define CHK_SysCpuMultiCoreSysMCGetNumOfCores_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetNumOfCores_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetNumOfCores_
	#define EXT_SysMCGetNumOfCores_
	#define GET_SysMCGetNumOfCores_(fl)  CAL_CMGETAPI( "SysMCGetNumOfCores_" ) 
	#define CAL_SysMCGetNumOfCores_ pISysCpuMultiCore->ISysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetNumOfCores_  CAL_CMEXPAPI( "SysMCGetNumOfCores_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetNumOfCores_  PFSYSMCGETNUMOFCORES_ pfSysMCGetNumOfCores_;
	#define EXT_SysMCGetNumOfCores_  extern PFSYSMCGETNUMOFCORES_ pfSysMCGetNumOfCores_;
	#define GET_SysMCGetNumOfCores_(fl)  s_pfCMGetAPI2( "SysMCGetNumOfCores_", (RTS_VOID_FCTPTR *)&pfSysMCGetNumOfCores_, (fl), 0, 0)
	#define CAL_SysMCGetNumOfCores_  pfSysMCGetNumOfCores_
	#define CHK_SysMCGetNumOfCores_  (pfSysMCGetNumOfCores_ != NULL)
	#define EXP_SysMCGetNumOfCores_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetNumOfCores_", (RTS_UINTPTR)SysMCGetNumOfCores_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCEnableCore(RTS_IEC_XWORD CoreID);
typedef RTS_RESULT (CDECL * PFSYSMCENABLECORE) (RTS_IEC_XWORD CoreID);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCENABLECORE_NOTIMPLEMENTED)
	#define USE_SysMCEnableCore
	#define EXT_SysMCEnableCore
	#define GET_SysMCEnableCore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCEnableCore(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCEnableCore  FALSE
	#define EXP_SysMCEnableCore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCEnableCore
	#define EXT_SysMCEnableCore
	#define GET_SysMCEnableCore(fl)  CAL_CMGETAPI( "SysMCEnableCore" ) 
	#define CAL_SysMCEnableCore  SysMCEnableCore
	#define CHK_SysMCEnableCore  TRUE
	#define EXP_SysMCEnableCore  CAL_CMEXPAPI( "SysMCEnableCore" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCEnableCore
	#define EXT_SysMCEnableCore
	#define GET_SysMCEnableCore(fl)  CAL_CMGETAPI( "SysMCEnableCore" ) 
	#define CAL_SysMCEnableCore  SysMCEnableCore
	#define CHK_SysMCEnableCore  TRUE
	#define EXP_SysMCEnableCore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCEnableCore", (RTS_UINTPTR)SysMCEnableCore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCEnableCore
	#define EXT_SysCpuMultiCoreSysMCEnableCore
	#define GET_SysCpuMultiCoreSysMCEnableCore  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCEnableCore pISysCpuMultiCore->ISysMCEnableCore
	#define CHK_SysCpuMultiCoreSysMCEnableCore (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCEnableCore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCEnableCore
	#define EXT_SysMCEnableCore
	#define GET_SysMCEnableCore(fl)  CAL_CMGETAPI( "SysMCEnableCore" ) 
	#define CAL_SysMCEnableCore pISysCpuMultiCore->ISysMCEnableCore
	#define CHK_SysMCEnableCore (pISysCpuMultiCore != NULL)
	#define EXP_SysMCEnableCore  CAL_CMEXPAPI( "SysMCEnableCore" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCEnableCore  PFSYSMCENABLECORE pfSysMCEnableCore;
	#define EXT_SysMCEnableCore  extern PFSYSMCENABLECORE pfSysMCEnableCore;
	#define GET_SysMCEnableCore(fl)  s_pfCMGetAPI2( "SysMCEnableCore", (RTS_VOID_FCTPTR *)&pfSysMCEnableCore, (fl), 0, 0)
	#define CAL_SysMCEnableCore  pfSysMCEnableCore
	#define CHK_SysMCEnableCore  (pfSysMCEnableCore != NULL)
	#define EXP_SysMCEnableCore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCEnableCore", (RTS_UINTPTR)SysMCEnableCore, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCDisableCore(RTS_IEC_XWORD CoreID);
typedef RTS_RESULT (CDECL * PFSYSMCDISABLECORE) (RTS_IEC_XWORD CoreID);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCDISABLECORE_NOTIMPLEMENTED)
	#define USE_SysMCDisableCore
	#define EXT_SysMCDisableCore
	#define GET_SysMCDisableCore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCDisableCore(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCDisableCore  FALSE
	#define EXP_SysMCDisableCore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCDisableCore
	#define EXT_SysMCDisableCore
	#define GET_SysMCDisableCore(fl)  CAL_CMGETAPI( "SysMCDisableCore" ) 
	#define CAL_SysMCDisableCore  SysMCDisableCore
	#define CHK_SysMCDisableCore  TRUE
	#define EXP_SysMCDisableCore  CAL_CMEXPAPI( "SysMCDisableCore" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCDisableCore
	#define EXT_SysMCDisableCore
	#define GET_SysMCDisableCore(fl)  CAL_CMGETAPI( "SysMCDisableCore" ) 
	#define CAL_SysMCDisableCore  SysMCDisableCore
	#define CHK_SysMCDisableCore  TRUE
	#define EXP_SysMCDisableCore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCDisableCore", (RTS_UINTPTR)SysMCDisableCore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCDisableCore
	#define EXT_SysCpuMultiCoreSysMCDisableCore
	#define GET_SysCpuMultiCoreSysMCDisableCore  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCDisableCore pISysCpuMultiCore->ISysMCDisableCore
	#define CHK_SysCpuMultiCoreSysMCDisableCore (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCDisableCore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCDisableCore
	#define EXT_SysMCDisableCore
	#define GET_SysMCDisableCore(fl)  CAL_CMGETAPI( "SysMCDisableCore" ) 
	#define CAL_SysMCDisableCore pISysCpuMultiCore->ISysMCDisableCore
	#define CHK_SysMCDisableCore (pISysCpuMultiCore != NULL)
	#define EXP_SysMCDisableCore  CAL_CMEXPAPI( "SysMCDisableCore" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCDisableCore  PFSYSMCDISABLECORE pfSysMCDisableCore;
	#define EXT_SysMCDisableCore  extern PFSYSMCDISABLECORE pfSysMCDisableCore;
	#define GET_SysMCDisableCore(fl)  s_pfCMGetAPI2( "SysMCDisableCore", (RTS_VOID_FCTPTR *)&pfSysMCDisableCore, (fl), 0, 0)
	#define CAL_SysMCDisableCore  pfSysMCDisableCore
	#define CHK_SysMCDisableCore  (pfSysMCDisableCore != NULL)
	#define EXP_SysMCDisableCore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCDisableCore", (RTS_UINTPTR)SysMCDisableCore, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCGetProcessBinding(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID);
typedef RTS_RESULT (CDECL * PFSYSMCGETPROCESSBINDING) (RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETPROCESSBINDING_NOTIMPLEMENTED)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetProcessBinding(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetProcessBinding  FALSE
	#define EXP_SysMCGetProcessBinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding" ) 
	#define CAL_SysMCGetProcessBinding  SysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding  TRUE
	#define EXP_SysMCGetProcessBinding  CAL_CMEXPAPI( "SysMCGetProcessBinding" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding" ) 
	#define CAL_SysMCGetProcessBinding  SysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding  TRUE
	#define EXP_SysMCGetProcessBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding", (RTS_UINTPTR)SysMCGetProcessBinding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetProcessBinding
	#define EXT_SysCpuMultiCoreSysMCGetProcessBinding
	#define GET_SysCpuMultiCoreSysMCGetProcessBinding  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetProcessBinding pISysCpuMultiCore->ISysMCGetProcessBinding
	#define CHK_SysCpuMultiCoreSysMCGetProcessBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetProcessBinding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetProcessBinding
	#define EXT_SysMCGetProcessBinding
	#define GET_SysMCGetProcessBinding(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding" ) 
	#define CAL_SysMCGetProcessBinding pISysCpuMultiCore->ISysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetProcessBinding  CAL_CMEXPAPI( "SysMCGetProcessBinding" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetProcessBinding  PFSYSMCGETPROCESSBINDING pfSysMCGetProcessBinding;
	#define EXT_SysMCGetProcessBinding  extern PFSYSMCGETPROCESSBINDING pfSysMCGetProcessBinding;
	#define GET_SysMCGetProcessBinding(fl)  s_pfCMGetAPI2( "SysMCGetProcessBinding", (RTS_VOID_FCTPTR *)&pfSysMCGetProcessBinding, (fl), 0, 0)
	#define CAL_SysMCGetProcessBinding  pfSysMCGetProcessBinding
	#define CHK_SysMCGetProcessBinding  (pfSysMCGetProcessBinding != NULL)
	#define EXP_SysMCGetProcessBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding", (RTS_UINTPTR)SysMCGetProcessBinding, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetProcessBinding
 * </description>
 */
RTS_RESULT CDECL SysMCGetProcessBinding_(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID);
typedef RTS_RESULT (CDECL * PFSYSMCGETPROCESSBINDING_) (RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETPROCESSBINDING__NOTIMPLEMENTED)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetProcessBinding_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetProcessBinding_  FALSE
	#define EXP_SysMCGetProcessBinding_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding_" ) 
	#define CAL_SysMCGetProcessBinding_  SysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_  TRUE
	#define EXP_SysMCGetProcessBinding_  CAL_CMEXPAPI( "SysMCGetProcessBinding_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding_" ) 
	#define CAL_SysMCGetProcessBinding_  SysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_  TRUE
	#define EXP_SysMCGetProcessBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding_", (RTS_UINTPTR)SysMCGetProcessBinding_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetProcessBinding_
	#define EXT_SysCpuMultiCoreSysMCGetProcessBinding_
	#define GET_SysCpuMultiCoreSysMCGetProcessBinding_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetProcessBinding_ pISysCpuMultiCore->ISysMCGetProcessBinding_
	#define CHK_SysCpuMultiCoreSysMCGetProcessBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetProcessBinding_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetProcessBinding_
	#define EXT_SysMCGetProcessBinding_
	#define GET_SysMCGetProcessBinding_(fl)  CAL_CMGETAPI( "SysMCGetProcessBinding_" ) 
	#define CAL_SysMCGetProcessBinding_ pISysCpuMultiCore->ISysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetProcessBinding_  CAL_CMEXPAPI( "SysMCGetProcessBinding_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetProcessBinding_  PFSYSMCGETPROCESSBINDING_ pfSysMCGetProcessBinding_;
	#define EXT_SysMCGetProcessBinding_  extern PFSYSMCGETPROCESSBINDING_ pfSysMCGetProcessBinding_;
	#define GET_SysMCGetProcessBinding_(fl)  s_pfCMGetAPI2( "SysMCGetProcessBinding_", (RTS_VOID_FCTPTR *)&pfSysMCGetProcessBinding_, (fl), 0, 0)
	#define CAL_SysMCGetProcessBinding_  pfSysMCGetProcessBinding_
	#define CHK_SysMCGetProcessBinding_  (pfSysMCGetProcessBinding_ != NULL)
	#define EXP_SysMCGetProcessBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetProcessBinding_", (RTS_UINTPTR)SysMCGetProcessBinding_, 0, 0) 
#endif




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
RTS_RESULT CDECL SysMCGetTaskBinding(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID);
typedef RTS_RESULT (CDECL * PFSYSMCGETTASKBINDING) (RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKBINDING_NOTIMPLEMENTED)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskBinding(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskBinding  FALSE
	#define EXP_SysMCGetTaskBinding  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding" ) 
	#define CAL_SysMCGetTaskBinding  SysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding  TRUE
	#define EXP_SysMCGetTaskBinding  CAL_CMEXPAPI( "SysMCGetTaskBinding" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding" ) 
	#define CAL_SysMCGetTaskBinding  SysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding  TRUE
	#define EXP_SysMCGetTaskBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding", (RTS_UINTPTR)SysMCGetTaskBinding, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskBinding
	#define EXT_SysCpuMultiCoreSysMCGetTaskBinding
	#define GET_SysCpuMultiCoreSysMCGetTaskBinding  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskBinding pISysCpuMultiCore->ISysMCGetTaskBinding
	#define CHK_SysCpuMultiCoreSysMCGetTaskBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskBinding  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskBinding
	#define EXT_SysMCGetTaskBinding
	#define GET_SysMCGetTaskBinding(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding" ) 
	#define CAL_SysMCGetTaskBinding pISysCpuMultiCore->ISysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskBinding  CAL_CMEXPAPI( "SysMCGetTaskBinding" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskBinding  PFSYSMCGETTASKBINDING pfSysMCGetTaskBinding;
	#define EXT_SysMCGetTaskBinding  extern PFSYSMCGETTASKBINDING pfSysMCGetTaskBinding;
	#define GET_SysMCGetTaskBinding(fl)  s_pfCMGetAPI2( "SysMCGetTaskBinding", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskBinding, (fl), 0, 0)
	#define CAL_SysMCGetTaskBinding  pfSysMCGetTaskBinding
	#define CHK_SysMCGetTaskBinding  (pfSysMCGetTaskBinding != NULL)
	#define EXP_SysMCGetTaskBinding  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding", (RTS_UINTPTR)SysMCGetTaskBinding, 0, 0) 
#endif




/**
 * <description>
 * The OS implementation of SysMCGetTaskBinding
 * </description>
 */
RTS_RESULT CDECL SysMCGetTaskBinding_(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID);
typedef RTS_RESULT (CDECL * PFSYSMCGETTASKBINDING_) (RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID);
#if defined(SYSCPUMULTICORE_NOTIMPLEMENTED) || defined(SYSMCGETTASKBINDING__NOTIMPLEMENTED)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  ERR_NOTIMPLEMENTED
	#define CAL_SysMCGetTaskBinding_(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_SysMCGetTaskBinding_  FALSE
	#define EXP_SysMCGetTaskBinding_  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding_" ) 
	#define CAL_SysMCGetTaskBinding_  SysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_  TRUE
	#define EXP_SysMCGetTaskBinding_  CAL_CMEXPAPI( "SysMCGetTaskBinding_" ) 
#elif defined(MIXED_LINK) && !defined(SYSCPUMULTICORE_EXTERNAL)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding_" ) 
	#define CAL_SysMCGetTaskBinding_  SysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_  TRUE
	#define EXP_SysMCGetTaskBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding_", (RTS_UINTPTR)SysMCGetTaskBinding_, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_SysCpuMultiCoreSysMCGetTaskBinding_
	#define EXT_SysCpuMultiCoreSysMCGetTaskBinding_
	#define GET_SysCpuMultiCoreSysMCGetTaskBinding_  ERR_OK
	#define CAL_SysCpuMultiCoreSysMCGetTaskBinding_ pISysCpuMultiCore->ISysMCGetTaskBinding_
	#define CHK_SysCpuMultiCoreSysMCGetTaskBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysCpuMultiCoreSysMCGetTaskBinding_  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_SysMCGetTaskBinding_
	#define EXT_SysMCGetTaskBinding_
	#define GET_SysMCGetTaskBinding_(fl)  CAL_CMGETAPI( "SysMCGetTaskBinding_" ) 
	#define CAL_SysMCGetTaskBinding_ pISysCpuMultiCore->ISysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_ (pISysCpuMultiCore != NULL)
	#define EXP_SysMCGetTaskBinding_  CAL_CMEXPAPI( "SysMCGetTaskBinding_" ) 
#else /* DYNAMIC_LINK */
	#define USE_SysMCGetTaskBinding_  PFSYSMCGETTASKBINDING_ pfSysMCGetTaskBinding_;
	#define EXT_SysMCGetTaskBinding_  extern PFSYSMCGETTASKBINDING_ pfSysMCGetTaskBinding_;
	#define GET_SysMCGetTaskBinding_(fl)  s_pfCMGetAPI2( "SysMCGetTaskBinding_", (RTS_VOID_FCTPTR *)&pfSysMCGetTaskBinding_, (fl), 0, 0)
	#define CAL_SysMCGetTaskBinding_  pfSysMCGetTaskBinding_
	#define CHK_SysMCGetTaskBinding_  (pfSysMCGetTaskBinding_ != NULL)
	#define EXP_SysMCGetTaskBinding_  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"SysMCGetTaskBinding_", (RTS_UINTPTR)SysMCGetTaskBinding_, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
	PFSYSMCBINDPROCESS ISysMCBindProcess;
 	PFSYSMCBINDPROCESS_ ISysMCBindProcess_;
 	PFSYSMCBINDTASK ISysMCBindTask;
 	PFSYSMCBINDTASK_ ISysMCBindTask_;
 	PFSYSMCUNBINDPROCESS ISysMCUnbindProcess;
 	PFSYSMCUNBINDPROCESS_ ISysMCUnbindProcess_;
 	PFSYSMCUNBINDTASK ISysMCUnbindTask;
 	PFSYSMCUNBINDTASK_ ISysMCUnbindTask_;
 	PFSYSMCGETLOAD ISysMCGetLoad;
 	PFSYSMCGETLOAD_ ISysMCGetLoad_;
 	PFSYSMCGETNUMOFCORES ISysMCGetNumOfCores;
 	PFSYSMCGETNUMOFCORES_ ISysMCGetNumOfCores_;
 	PFSYSMCENABLECORE ISysMCEnableCore;
 	PFSYSMCDISABLECORE ISysMCDisableCore;
 	PFSYSMCGETPROCESSBINDING ISysMCGetProcessBinding;
 	PFSYSMCGETPROCESSBINDING_ ISysMCGetProcessBinding_;
 	PFSYSMCGETTASKBINDING ISysMCGetTaskBinding;
 	PFSYSMCGETTASKBINDING_ ISysMCGetTaskBinding_;
 } ISysCpuMultiCore_C;

#ifdef CPLUSPLUS
class ISysCpuMultiCore : public IBase
{
	public:
		virtual RTS_RESULT CDECL ISysMCBindProcess(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCBindProcess_(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCBindTask(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCBindTask_(CpuCoreBindingDesc *pCoreID, RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindProcess(RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindProcess_(RTS_IEC_HANDLE hProcess) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindTask(RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCUnbindTask_(RTS_IEC_HANDLE hTask) =0;
		virtual RTS_RESULT CDECL ISysMCGetLoad(RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent) =0;
		virtual RTS_RESULT CDECL ISysMCGetLoad_(RTS_IEC_XWORD CoreID, RTS_IEC_BYTE *pPercent) =0;
		virtual RTS_UI32 CDECL ISysMCGetNumOfCores(RTS_RESULT* pResult) =0;
		virtual RTS_UI32 CDECL ISysMCGetNumOfCores_(RTS_RESULT* pResult) =0;
		virtual RTS_RESULT CDECL ISysMCEnableCore(RTS_IEC_XWORD CoreID) =0;
		virtual RTS_RESULT CDECL ISysMCDisableCore(RTS_IEC_XWORD CoreID) =0;
		virtual RTS_RESULT CDECL ISysMCGetProcessBinding(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID) =0;
		virtual RTS_RESULT CDECL ISysMCGetProcessBinding_(RTS_IEC_HANDLE hProcess, CpuCoreBindingDesc *pCoreID) =0;
		virtual RTS_RESULT CDECL ISysMCGetTaskBinding(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID) =0;
		virtual RTS_RESULT CDECL ISysMCGetTaskBinding_(RTS_IEC_HANDLE hTask, CpuCoreBindingDesc *pCoreID) =0;
};
	#ifndef ITF_SysCpuMultiCore
		#define ITF_SysCpuMultiCore static ISysCpuMultiCore *pISysCpuMultiCore = NULL;
	#endif
	#define EXTITF_SysCpuMultiCore
#else	/*CPLUSPLUS*/
	typedef ISysCpuMultiCore_C		ISysCpuMultiCore;
	#ifndef ITF_SysCpuMultiCore
		#define ITF_SysCpuMultiCore
	#endif
	#define EXTITF_SysCpuMultiCore
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_SYSCPUMULTICOREITF_H_*/
