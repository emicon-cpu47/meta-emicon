 /**
 * <interfacename>EmiconSys</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _EMICONSYSITF_H_
#define _EMICONSYSITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>get_ptr_to_dpm</description>
 */
typedef struct tagget_ptr_to_dpm_struct
{
	RTS_IEC_WORD *Get_ptr_to_DPM;		/* VAR_OUTPUT */	
} get_ptr_to_dpm_struct;

void CDECL CDECL_EXT get_ptr_to_dpm(get_ptr_to_dpm_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_DPM_IEC) (get_ptr_to_dpm_struct *p);
#if defined(EMICONSYS_NOTIMPLEMENTED) || defined(GET_PTR_TO_DPM_NOTIMPLEMENTED)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_dpm(p0) 
	#define CHK_get_ptr_to_dpm  FALSE
	#define EXP_get_ptr_to_dpm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  CAL_CMGETAPI( "get_ptr_to_dpm" ) 
	#define CAL_get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  TRUE
	#define EXP_get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_EXTERNAL)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  CAL_CMGETAPI( "get_ptr_to_dpm" ) 
	#define CAL_get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  TRUE
	#define EXP_get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSysget_ptr_to_dpm
	#define EXT_EmiconSysget_ptr_to_dpm
	#define GET_EmiconSysget_ptr_to_dpm  ERR_OK
	#define CAL_EmiconSysget_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_EmiconSysget_ptr_to_dpm  TRUE
	#define EXP_EmiconSysget_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  CAL_CMGETAPI( "get_ptr_to_dpm" ) 
	#define CAL_get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  TRUE
	#define EXP_get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_dpm  PFGET_PTR_TO_DPM_IEC pfget_ptr_to_dpm;
	#define EXT_get_ptr_to_dpm  extern PFGET_PTR_TO_DPM_IEC pfget_ptr_to_dpm;
	#define GET_get_ptr_to_dpm(fl)  s_pfCMGetAPI2( "get_ptr_to_dpm", (RTS_VOID_FCTPTR *)&pfget_ptr_to_dpm, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7C8941E2, 0x03050A00)
	#define CAL_get_ptr_to_dpm  pfget_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  (pfget_ptr_to_dpm != NULL)
	#define EXP_get_ptr_to_dpm   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03050A00) 
#endif


/**
 * <description>get_ptr_to_slot0</description>
 */
typedef struct tagget_ptr_to_slot0_struct
{
	RTS_IEC_BYTE *Get_ptr_to_slot0;		/* VAR_OUTPUT */	
} get_ptr_to_slot0_struct;

void CDECL CDECL_EXT get_ptr_to_slot0(get_ptr_to_slot0_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_SLOT0_IEC) (get_ptr_to_slot0_struct *p);
#if defined(EMICONSYS_NOTIMPLEMENTED) || defined(GET_PTR_TO_SLOT0_NOTIMPLEMENTED)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_slot0(p0) 
	#define CHK_get_ptr_to_slot0  FALSE
	#define EXP_get_ptr_to_slot0  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  CAL_CMGETAPI( "get_ptr_to_slot0" ) 
	#define CAL_get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  TRUE
	#define EXP_get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_EXTERNAL)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  CAL_CMGETAPI( "get_ptr_to_slot0" ) 
	#define CAL_get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  TRUE
	#define EXP_get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSysget_ptr_to_slot0
	#define EXT_EmiconSysget_ptr_to_slot0
	#define GET_EmiconSysget_ptr_to_slot0  ERR_OK
	#define CAL_EmiconSysget_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_EmiconSysget_ptr_to_slot0  TRUE
	#define EXP_EmiconSysget_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  CAL_CMGETAPI( "get_ptr_to_slot0" ) 
	#define CAL_get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  TRUE
	#define EXP_get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_slot0  PFGET_PTR_TO_SLOT0_IEC pfget_ptr_to_slot0;
	#define EXT_get_ptr_to_slot0  extern PFGET_PTR_TO_SLOT0_IEC pfget_ptr_to_slot0;
	#define GET_get_ptr_to_slot0(fl)  s_pfCMGetAPI2( "get_ptr_to_slot0", (RTS_VOID_FCTPTR *)&pfget_ptr_to_slot0, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE6CB94A0, 0x03050A00)
	#define CAL_get_ptr_to_slot0  pfget_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  (pfget_ptr_to_slot0 != NULL)
	#define EXP_get_ptr_to_slot0   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03050A00) 
#endif


/**
 * <description>get_ptr_to_sock_arr</description>
 */
typedef struct tagget_ptr_to_sock_arr_struct
{
	RTS_IEC_UDINT *Get_ptr_to_sock_arr;	/* VAR_OUTPUT */	
} get_ptr_to_sock_arr_struct;

void CDECL CDECL_EXT get_ptr_to_sock_arr(get_ptr_to_sock_arr_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_SOCK_ARR_IEC) (get_ptr_to_sock_arr_struct *p);
#if defined(EMICONSYS_NOTIMPLEMENTED) || defined(GET_PTR_TO_SOCK_ARR_NOTIMPLEMENTED)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_sock_arr(p0) 
	#define CHK_get_ptr_to_sock_arr  FALSE
	#define EXP_get_ptr_to_sock_arr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  CAL_CMGETAPI( "get_ptr_to_sock_arr" ) 
	#define CAL_get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  TRUE
	#define EXP_get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_EXTERNAL)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  CAL_CMGETAPI( "get_ptr_to_sock_arr" ) 
	#define CAL_get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  TRUE
	#define EXP_get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSysget_ptr_to_sock_arr
	#define EXT_EmiconSysget_ptr_to_sock_arr
	#define GET_EmiconSysget_ptr_to_sock_arr  ERR_OK
	#define CAL_EmiconSysget_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_EmiconSysget_ptr_to_sock_arr  TRUE
	#define EXP_EmiconSysget_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  CAL_CMGETAPI( "get_ptr_to_sock_arr" ) 
	#define CAL_get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  TRUE
	#define EXP_get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_sock_arr  PFGET_PTR_TO_SOCK_ARR_IEC pfget_ptr_to_sock_arr;
	#define EXT_get_ptr_to_sock_arr  extern PFGET_PTR_TO_SOCK_ARR_IEC pfget_ptr_to_sock_arr;
	#define GET_get_ptr_to_sock_arr(fl)  s_pfCMGetAPI2( "get_ptr_to_sock_arr", (RTS_VOID_FCTPTR *)&pfget_ptr_to_sock_arr, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7F4ADBA2, 0x03050A00)
	#define CAL_get_ptr_to_sock_arr  pfget_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  (pfget_ptr_to_sock_arr != NULL)
	#define EXP_get_ptr_to_sock_arr   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03050A00) 
#endif


/**
 * <description>set_inhibit</description>
 */
typedef struct tagset_inhibit_struct
{
	RTS_IEC_INT set_inhibit;			/* VAR_OUTPUT */	
} set_inhibit_struct;

void CDECL CDECL_EXT set_inhibit(set_inhibit_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_INHIBIT_IEC) (set_inhibit_struct *p);
#if defined(EMICONSYS_NOTIMPLEMENTED) || defined(SET_INHIBIT_NOTIMPLEMENTED)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_inhibit(p0) 
	#define CHK_set_inhibit  FALSE
	#define EXP_set_inhibit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  CAL_CMGETAPI( "set_inhibit" ) 
	#define CAL_set_inhibit  set_inhibit
	#define CHK_set_inhibit  TRUE
	#define EXP_set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_EXTERNAL)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  CAL_CMGETAPI( "set_inhibit" ) 
	#define CAL_set_inhibit  set_inhibit
	#define CHK_set_inhibit  TRUE
	#define EXP_set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSysset_inhibit
	#define EXT_EmiconSysset_inhibit
	#define GET_EmiconSysset_inhibit  ERR_OK
	#define CAL_EmiconSysset_inhibit  set_inhibit
	#define CHK_EmiconSysset_inhibit  TRUE
	#define EXP_EmiconSysset_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  CAL_CMGETAPI( "set_inhibit" ) 
	#define CAL_set_inhibit  set_inhibit
	#define CHK_set_inhibit  TRUE
	#define EXP_set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_set_inhibit  PFSET_INHIBIT_IEC pfset_inhibit;
	#define EXT_set_inhibit  extern PFSET_INHIBIT_IEC pfset_inhibit;
	#define GET_set_inhibit(fl)  s_pfCMGetAPI2( "set_inhibit", (RTS_VOID_FCTPTR *)&pfset_inhibit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xAFE8BB40, 0x03050A00)
	#define CAL_set_inhibit  pfset_inhibit
	#define CHK_set_inhibit  (pfset_inhibit != NULL)
	#define EXP_set_inhibit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03050A00) 
#endif


/**
 * <description>set_watchdog</description>
 */
typedef struct tagset_watchdog_struct
{
	RTS_IEC_INT set_watchdog;			/* VAR_OUTPUT */	
} set_watchdog_struct;

void CDECL CDECL_EXT set_watchdog(set_watchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_WATCHDOG_IEC) (set_watchdog_struct *p);
#if defined(EMICONSYS_NOTIMPLEMENTED) || defined(SET_WATCHDOG_NOTIMPLEMENTED)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_watchdog(p0) 
	#define CHK_set_watchdog  FALSE
	#define EXP_set_watchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  CAL_CMGETAPI( "set_watchdog" ) 
	#define CAL_set_watchdog  set_watchdog
	#define CHK_set_watchdog  TRUE
	#define EXP_set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_EXTERNAL)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  CAL_CMGETAPI( "set_watchdog" ) 
	#define CAL_set_watchdog  set_watchdog
	#define CHK_set_watchdog  TRUE
	#define EXP_set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSysset_watchdog
	#define EXT_EmiconSysset_watchdog
	#define GET_EmiconSysset_watchdog  ERR_OK
	#define CAL_EmiconSysset_watchdog  set_watchdog
	#define CHK_EmiconSysset_watchdog  TRUE
	#define EXP_EmiconSysset_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  CAL_CMGETAPI( "set_watchdog" ) 
	#define CAL_set_watchdog  set_watchdog
	#define CHK_set_watchdog  TRUE
	#define EXP_set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_set_watchdog  PFSET_WATCHDOG_IEC pfset_watchdog;
	#define EXT_set_watchdog  extern PFSET_WATCHDOG_IEC pfset_watchdog;
	#define GET_set_watchdog(fl)  s_pfCMGetAPI2( "set_watchdog", (RTS_VOID_FCTPTR *)&pfset_watchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9CA67B6B, 0x03050A00)
	#define CAL_set_watchdog  pfset_watchdog
	#define CHK_set_watchdog  (pfset_watchdog != NULL)
	#define EXP_set_watchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03050A00) 
#endif


/**
 * <description>syssync</description>
 */
typedef struct tagsyssync_struct
{
	RTS_IEC_INT SysSync;				/* VAR_OUTPUT */	
} syssync_struct;

void CDECL CDECL_EXT syssync(syssync_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSYNC_IEC) (syssync_struct *p);
#if defined(EMICONSYS_NOTIMPLEMENTED) || defined(SYSSYNC_NOTIMPLEMENTED)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssync(p0) 
	#define CHK_syssync  FALSE
	#define EXP_syssync  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  CAL_CMGETAPI( "syssync" ) 
	#define CAL_syssync  syssync
	#define CHK_syssync  TRUE
	#define EXP_syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_EXTERNAL)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  CAL_CMGETAPI( "syssync" ) 
	#define CAL_syssync  syssync
	#define CHK_syssync  TRUE
	#define EXP_syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSyssyssync
	#define EXT_EmiconSyssyssync
	#define GET_EmiconSyssyssync  ERR_OK
	#define CAL_EmiconSyssyssync  syssync
	#define CHK_EmiconSyssyssync  TRUE
	#define EXP_EmiconSyssyssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  CAL_CMGETAPI( "syssync" ) 
	#define CAL_syssync  syssync
	#define CHK_syssync  TRUE
	#define EXP_syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_syssync  PFSYSSYNC_IEC pfsyssync;
	#define EXT_syssync  extern PFSYSSYNC_IEC pfsyssync;
	#define GET_syssync(fl)  s_pfCMGetAPI2( "syssync", (RTS_VOID_FCTPTR *)&pfsyssync, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDC1119C9, 0x03050A00)
	#define CAL_syssync  pfsyssync
	#define CHK_syssync  (pfsyssync != NULL)
	#define EXP_syssync   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03050A00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} IEmiconSys_C;

#ifdef CPLUSPLUS
class IEmiconSys : public IBase
{
	public:
};
	#ifndef ITF_EmiconSys
		#define ITF_EmiconSys static IEmiconSys *pIEmiconSys = NULL;
	#endif
	#define EXTITF_EmiconSys
#else	/*CPLUSPLUS*/
	typedef IEmiconSys_C		IEmiconSys;
	#ifndef ITF_EmiconSys
		#define ITF_EmiconSys
	#endif
	#define EXTITF_EmiconSys
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_EMICONSYSITF_H_*/
