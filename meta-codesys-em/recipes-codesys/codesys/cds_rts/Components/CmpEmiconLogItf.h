 /**
 * <interfacename>CmpEmiconLog</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPEMICONLOGITF_H_
#define _CMPEMICONLOGITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>clr_sys_log</description>
 */
typedef struct tagclr_sys_log_struct
{
	RTS_IEC_UDINT clr_sys_log;			/* VAR_OUTPUT */	
} clr_sys_log_struct;

void CDECL CDECL_EXT clr_sys_log(clr_sys_log_struct *p);
typedef void (CDECL CDECL_EXT* PFCLR_SYS_LOG_IEC) (clr_sys_log_struct *p);
#if defined(CMPEMICONLOG_NOTIMPLEMENTED) || defined(CLR_SYS_LOG_NOTIMPLEMENTED)
	#define USE_clr_sys_log
	#define EXT_clr_sys_log
	#define GET_clr_sys_log(fl)  ERR_NOTIMPLEMENTED
	#define CAL_clr_sys_log(p0) 
	#define CHK_clr_sys_log  FALSE
	#define EXP_clr_sys_log  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_clr_sys_log
	#define EXT_clr_sys_log
	#define GET_clr_sys_log(fl)  CAL_CMGETAPI( "clr_sys_log" ) 
	#define CAL_clr_sys_log  clr_sys_log
	#define CHK_clr_sys_log  TRUE
	#define EXP_clr_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_sys_log", (RTS_UINTPTR)clr_sys_log, 1, 0x8B141454, 0x03050D00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLOG_EXTERNAL)
	#define USE_clr_sys_log
	#define EXT_clr_sys_log
	#define GET_clr_sys_log(fl)  CAL_CMGETAPI( "clr_sys_log" ) 
	#define CAL_clr_sys_log  clr_sys_log
	#define CHK_clr_sys_log  TRUE
	#define EXP_clr_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_sys_log", (RTS_UINTPTR)clr_sys_log, 1, 0x8B141454, 0x03050D00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLogclr_sys_log
	#define EXT_CmpEmiconLogclr_sys_log
	#define GET_CmpEmiconLogclr_sys_log  ERR_OK
	#define CAL_CmpEmiconLogclr_sys_log  clr_sys_log
	#define CHK_CmpEmiconLogclr_sys_log  TRUE
	#define EXP_CmpEmiconLogclr_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_sys_log", (RTS_UINTPTR)clr_sys_log, 1, 0x8B141454, 0x03050D00) 
#elif defined(CPLUSPLUS)
	#define USE_clr_sys_log
	#define EXT_clr_sys_log
	#define GET_clr_sys_log(fl)  CAL_CMGETAPI( "clr_sys_log" ) 
	#define CAL_clr_sys_log  clr_sys_log
	#define CHK_clr_sys_log  TRUE
	#define EXP_clr_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_sys_log", (RTS_UINTPTR)clr_sys_log, 1, 0x8B141454, 0x03050D00) 
#else /* DYNAMIC_LINK */
	#define USE_clr_sys_log  PFCLR_SYS_LOG_IEC pfclr_sys_log;
	#define EXT_clr_sys_log  extern PFCLR_SYS_LOG_IEC pfclr_sys_log;
	#define GET_clr_sys_log(fl)  s_pfCMGetAPI2( "clr_sys_log", (RTS_VOID_FCTPTR *)&pfclr_sys_log, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x8B141454, 0x03050D00)
	#define CAL_clr_sys_log  pfclr_sys_log
	#define CHK_clr_sys_log  (pfclr_sys_log != NULL)
	#define EXP_clr_sys_log   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_sys_log", (RTS_UINTPTR)clr_sys_log, 1, 0x8B141454, 0x03050D00) 
#endif


/**
 * <description>create_log_files</description>
 */
typedef struct tagcreate_log_files_struct
{
	RTS_IEC_DINT create_log_files;		/* VAR_OUTPUT */	
} create_log_files_struct;

void CDECL CDECL_EXT create_log_files(create_log_files_struct *p);
typedef void (CDECL CDECL_EXT* PFCREATE_LOG_FILES_IEC) (create_log_files_struct *p);
#if defined(CMPEMICONLOG_NOTIMPLEMENTED) || defined(CREATE_LOG_FILES_NOTIMPLEMENTED)
	#define USE_create_log_files
	#define EXT_create_log_files
	#define GET_create_log_files(fl)  ERR_NOTIMPLEMENTED
	#define CAL_create_log_files(p0) 
	#define CHK_create_log_files  FALSE
	#define EXP_create_log_files  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_create_log_files
	#define EXT_create_log_files
	#define GET_create_log_files(fl)  CAL_CMGETAPI( "create_log_files" ) 
	#define CAL_create_log_files  create_log_files
	#define CHK_create_log_files  TRUE
	#define EXP_create_log_files  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"create_log_files", (RTS_UINTPTR)create_log_files, 1, 0x5B82FD55, 0x03050D00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLOG_EXTERNAL)
	#define USE_create_log_files
	#define EXT_create_log_files
	#define GET_create_log_files(fl)  CAL_CMGETAPI( "create_log_files" ) 
	#define CAL_create_log_files  create_log_files
	#define CHK_create_log_files  TRUE
	#define EXP_create_log_files  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"create_log_files", (RTS_UINTPTR)create_log_files, 1, 0x5B82FD55, 0x03050D00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLogcreate_log_files
	#define EXT_CmpEmiconLogcreate_log_files
	#define GET_CmpEmiconLogcreate_log_files  ERR_OK
	#define CAL_CmpEmiconLogcreate_log_files  create_log_files
	#define CHK_CmpEmiconLogcreate_log_files  TRUE
	#define EXP_CmpEmiconLogcreate_log_files  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"create_log_files", (RTS_UINTPTR)create_log_files, 1, 0x5B82FD55, 0x03050D00) 
#elif defined(CPLUSPLUS)
	#define USE_create_log_files
	#define EXT_create_log_files
	#define GET_create_log_files(fl)  CAL_CMGETAPI( "create_log_files" ) 
	#define CAL_create_log_files  create_log_files
	#define CHK_create_log_files  TRUE
	#define EXP_create_log_files  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"create_log_files", (RTS_UINTPTR)create_log_files, 1, 0x5B82FD55, 0x03050D00) 
#else /* DYNAMIC_LINK */
	#define USE_create_log_files  PFCREATE_LOG_FILES_IEC pfcreate_log_files;
	#define EXT_create_log_files  extern PFCREATE_LOG_FILES_IEC pfcreate_log_files;
	#define GET_create_log_files(fl)  s_pfCMGetAPI2( "create_log_files", (RTS_VOID_FCTPTR *)&pfcreate_log_files, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x5B82FD55, 0x03050D00)
	#define CAL_create_log_files  pfcreate_log_files
	#define CHK_create_log_files  (pfcreate_log_files != NULL)
	#define EXP_create_log_files   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"create_log_files", (RTS_UINTPTR)create_log_files, 1, 0x5B82FD55, 0x03050D00) 
#endif


/**
 * <description>get_next_log_item</description>
 */
typedef struct tagget_next_log_item_struct
{
	RTS_IEC_BOOL get_first;				/* VAR_INPUT */	
	RTS_IEC_STRING *log_str;			/* VAR_INPUT */	
	RTS_IEC_INT get_next_log_item;		/* VAR_OUTPUT */	
} get_next_log_item_struct;

void CDECL CDECL_EXT get_next_log_item(get_next_log_item_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_NEXT_LOG_ITEM_IEC) (get_next_log_item_struct *p);
#if defined(CMPEMICONLOG_NOTIMPLEMENTED) || defined(GET_NEXT_LOG_ITEM_NOTIMPLEMENTED)
	#define USE_get_next_log_item
	#define EXT_get_next_log_item
	#define GET_get_next_log_item(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_next_log_item(p0) 
	#define CHK_get_next_log_item  FALSE
	#define EXP_get_next_log_item  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_next_log_item
	#define EXT_get_next_log_item
	#define GET_get_next_log_item(fl)  CAL_CMGETAPI( "get_next_log_item" ) 
	#define CAL_get_next_log_item  get_next_log_item
	#define CHK_get_next_log_item  TRUE
	#define EXP_get_next_log_item  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_next_log_item", (RTS_UINTPTR)get_next_log_item, 1, 0xDA44E7BB, 0x03050D00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLOG_EXTERNAL)
	#define USE_get_next_log_item
	#define EXT_get_next_log_item
	#define GET_get_next_log_item(fl)  CAL_CMGETAPI( "get_next_log_item" ) 
	#define CAL_get_next_log_item  get_next_log_item
	#define CHK_get_next_log_item  TRUE
	#define EXP_get_next_log_item  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_next_log_item", (RTS_UINTPTR)get_next_log_item, 1, 0xDA44E7BB, 0x03050D00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLogget_next_log_item
	#define EXT_CmpEmiconLogget_next_log_item
	#define GET_CmpEmiconLogget_next_log_item  ERR_OK
	#define CAL_CmpEmiconLogget_next_log_item  get_next_log_item
	#define CHK_CmpEmiconLogget_next_log_item  TRUE
	#define EXP_CmpEmiconLogget_next_log_item  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_next_log_item", (RTS_UINTPTR)get_next_log_item, 1, 0xDA44E7BB, 0x03050D00) 
#elif defined(CPLUSPLUS)
	#define USE_get_next_log_item
	#define EXT_get_next_log_item
	#define GET_get_next_log_item(fl)  CAL_CMGETAPI( "get_next_log_item" ) 
	#define CAL_get_next_log_item  get_next_log_item
	#define CHK_get_next_log_item  TRUE
	#define EXP_get_next_log_item  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_next_log_item", (RTS_UINTPTR)get_next_log_item, 1, 0xDA44E7BB, 0x03050D00) 
#else /* DYNAMIC_LINK */
	#define USE_get_next_log_item  PFGET_NEXT_LOG_ITEM_IEC pfget_next_log_item;
	#define EXT_get_next_log_item  extern PFGET_NEXT_LOG_ITEM_IEC pfget_next_log_item;
	#define GET_get_next_log_item(fl)  s_pfCMGetAPI2( "get_next_log_item", (RTS_VOID_FCTPTR *)&pfget_next_log_item, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDA44E7BB, 0x03050D00)
	#define CAL_get_next_log_item  pfget_next_log_item
	#define CHK_get_next_log_item  (pfget_next_log_item != NULL)
	#define EXP_get_next_log_item   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_next_log_item", (RTS_UINTPTR)get_next_log_item, 1, 0xDA44E7BB, 0x03050D00) 
#endif


/**
 * <description>write_sys_log</description>
 */
typedef struct tagwrite_sys_log_struct
{
	RTS_IEC_BYTE byClassId;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwValue;				/* VAR_INPUT */	
	RTS_IEC_UDINT write_sys_log;		/* VAR_OUTPUT */	
} write_sys_log_struct;

void CDECL CDECL_EXT write_sys_log(write_sys_log_struct *p);
typedef void (CDECL CDECL_EXT* PFWRITE_SYS_LOG_IEC) (write_sys_log_struct *p);
#if defined(CMPEMICONLOG_NOTIMPLEMENTED) || defined(WRITE_SYS_LOG_NOTIMPLEMENTED)
	#define USE_write_sys_log
	#define EXT_write_sys_log
	#define GET_write_sys_log(fl)  ERR_NOTIMPLEMENTED
	#define CAL_write_sys_log(p0) 
	#define CHK_write_sys_log  FALSE
	#define EXP_write_sys_log  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_write_sys_log
	#define EXT_write_sys_log
	#define GET_write_sys_log(fl)  CAL_CMGETAPI( "write_sys_log" ) 
	#define CAL_write_sys_log  write_sys_log
	#define CHK_write_sys_log  TRUE
	#define EXP_write_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_sys_log", (RTS_UINTPTR)write_sys_log, 1, 0xA5470BCD, 0x03050D00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLOG_EXTERNAL)
	#define USE_write_sys_log
	#define EXT_write_sys_log
	#define GET_write_sys_log(fl)  CAL_CMGETAPI( "write_sys_log" ) 
	#define CAL_write_sys_log  write_sys_log
	#define CHK_write_sys_log  TRUE
	#define EXP_write_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_sys_log", (RTS_UINTPTR)write_sys_log, 1, 0xA5470BCD, 0x03050D00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLogwrite_sys_log
	#define EXT_CmpEmiconLogwrite_sys_log
	#define GET_CmpEmiconLogwrite_sys_log  ERR_OK
	#define CAL_CmpEmiconLogwrite_sys_log  write_sys_log
	#define CHK_CmpEmiconLogwrite_sys_log  TRUE
	#define EXP_CmpEmiconLogwrite_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_sys_log", (RTS_UINTPTR)write_sys_log, 1, 0xA5470BCD, 0x03050D00) 
#elif defined(CPLUSPLUS)
	#define USE_write_sys_log
	#define EXT_write_sys_log
	#define GET_write_sys_log(fl)  CAL_CMGETAPI( "write_sys_log" ) 
	#define CAL_write_sys_log  write_sys_log
	#define CHK_write_sys_log  TRUE
	#define EXP_write_sys_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_sys_log", (RTS_UINTPTR)write_sys_log, 1, 0xA5470BCD, 0x03050D00) 
#else /* DYNAMIC_LINK */
	#define USE_write_sys_log  PFWRITE_SYS_LOG_IEC pfwrite_sys_log;
	#define EXT_write_sys_log  extern PFWRITE_SYS_LOG_IEC pfwrite_sys_log;
	#define GET_write_sys_log(fl)  s_pfCMGetAPI2( "write_sys_log", (RTS_VOID_FCTPTR *)&pfwrite_sys_log, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xA5470BCD, 0x03050D00)
	#define CAL_write_sys_log  pfwrite_sys_log
	#define CHK_write_sys_log  (pfwrite_sys_log != NULL)
	#define EXP_write_sys_log   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_sys_log", (RTS_UINTPTR)write_sys_log, 1, 0xA5470BCD, 0x03050D00) 
#endif


/**
 * <description>write_ti_log</description>
 */
typedef struct tagwrite_ti_log_struct
{
	RTS_IEC_BYTE byClassId;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_UDINT write_ti_log;			/* VAR_OUTPUT */	
} write_ti_log_struct;

void CDECL CDECL_EXT write_ti_log(write_ti_log_struct *p);
typedef void (CDECL CDECL_EXT* PFWRITE_TI_LOG_IEC) (write_ti_log_struct *p);
#if defined(CMPEMICONLOG_NOTIMPLEMENTED) || defined(WRITE_TI_LOG_NOTIMPLEMENTED)
	#define USE_write_ti_log
	#define EXT_write_ti_log
	#define GET_write_ti_log(fl)  ERR_NOTIMPLEMENTED
	#define CAL_write_ti_log(p0) 
	#define CHK_write_ti_log  FALSE
	#define EXP_write_ti_log  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_write_ti_log
	#define EXT_write_ti_log
	#define GET_write_ti_log(fl)  CAL_CMGETAPI( "write_ti_log" ) 
	#define CAL_write_ti_log  write_ti_log
	#define CHK_write_ti_log  TRUE
	#define EXP_write_ti_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ti_log", (RTS_UINTPTR)write_ti_log, 1, 0xEED4B686, 0x03050D00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLOG_EXTERNAL)
	#define USE_write_ti_log
	#define EXT_write_ti_log
	#define GET_write_ti_log(fl)  CAL_CMGETAPI( "write_ti_log" ) 
	#define CAL_write_ti_log  write_ti_log
	#define CHK_write_ti_log  TRUE
	#define EXP_write_ti_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ti_log", (RTS_UINTPTR)write_ti_log, 1, 0xEED4B686, 0x03050D00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLogwrite_ti_log
	#define EXT_CmpEmiconLogwrite_ti_log
	#define GET_CmpEmiconLogwrite_ti_log  ERR_OK
	#define CAL_CmpEmiconLogwrite_ti_log  write_ti_log
	#define CHK_CmpEmiconLogwrite_ti_log  TRUE
	#define EXP_CmpEmiconLogwrite_ti_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ti_log", (RTS_UINTPTR)write_ti_log, 1, 0xEED4B686, 0x03050D00) 
#elif defined(CPLUSPLUS)
	#define USE_write_ti_log
	#define EXT_write_ti_log
	#define GET_write_ti_log(fl)  CAL_CMGETAPI( "write_ti_log" ) 
	#define CAL_write_ti_log  write_ti_log
	#define CHK_write_ti_log  TRUE
	#define EXP_write_ti_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ti_log", (RTS_UINTPTR)write_ti_log, 1, 0xEED4B686, 0x03050D00) 
#else /* DYNAMIC_LINK */
	#define USE_write_ti_log  PFWRITE_TI_LOG_IEC pfwrite_ti_log;
	#define EXT_write_ti_log  extern PFWRITE_TI_LOG_IEC pfwrite_ti_log;
	#define GET_write_ti_log(fl)  s_pfCMGetAPI2( "write_ti_log", (RTS_VOID_FCTPTR *)&pfwrite_ti_log, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xEED4B686, 0x03050D00)
	#define CAL_write_ti_log  pfwrite_ti_log
	#define CHK_write_ti_log  (pfwrite_ti_log != NULL)
	#define EXP_write_ti_log   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ti_log", (RTS_UINTPTR)write_ti_log, 1, 0xEED4B686, 0x03050D00) 
#endif


/**
 * <description>write_ts_log</description>
 */
typedef struct tagwrite_ts_log_struct
{
	RTS_IEC_BYTE byClassId;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_UDINT write_ts_log;			/* VAR_OUTPUT */	
} write_ts_log_struct;

void CDECL CDECL_EXT write_ts_log(write_ts_log_struct *p);
typedef void (CDECL CDECL_EXT* PFWRITE_TS_LOG_IEC) (write_ts_log_struct *p);
#if defined(CMPEMICONLOG_NOTIMPLEMENTED) || defined(WRITE_TS_LOG_NOTIMPLEMENTED)
	#define USE_write_ts_log
	#define EXT_write_ts_log
	#define GET_write_ts_log(fl)  ERR_NOTIMPLEMENTED
	#define CAL_write_ts_log(p0) 
	#define CHK_write_ts_log  FALSE
	#define EXP_write_ts_log  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_write_ts_log
	#define EXT_write_ts_log
	#define GET_write_ts_log(fl)  CAL_CMGETAPI( "write_ts_log" ) 
	#define CAL_write_ts_log  write_ts_log
	#define CHK_write_ts_log  TRUE
	#define EXP_write_ts_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ts_log", (RTS_UINTPTR)write_ts_log, 1, 0xBBC343F7, 0x03050D00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONLOG_EXTERNAL)
	#define USE_write_ts_log
	#define EXT_write_ts_log
	#define GET_write_ts_log(fl)  CAL_CMGETAPI( "write_ts_log" ) 
	#define CAL_write_ts_log  write_ts_log
	#define CHK_write_ts_log  TRUE
	#define EXP_write_ts_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ts_log", (RTS_UINTPTR)write_ts_log, 1, 0xBBC343F7, 0x03050D00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconLogwrite_ts_log
	#define EXT_CmpEmiconLogwrite_ts_log
	#define GET_CmpEmiconLogwrite_ts_log  ERR_OK
	#define CAL_CmpEmiconLogwrite_ts_log  write_ts_log
	#define CHK_CmpEmiconLogwrite_ts_log  TRUE
	#define EXP_CmpEmiconLogwrite_ts_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ts_log", (RTS_UINTPTR)write_ts_log, 1, 0xBBC343F7, 0x03050D00) 
#elif defined(CPLUSPLUS)
	#define USE_write_ts_log
	#define EXT_write_ts_log
	#define GET_write_ts_log(fl)  CAL_CMGETAPI( "write_ts_log" ) 
	#define CAL_write_ts_log  write_ts_log
	#define CHK_write_ts_log  TRUE
	#define EXP_write_ts_log  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ts_log", (RTS_UINTPTR)write_ts_log, 1, 0xBBC343F7, 0x03050D00) 
#else /* DYNAMIC_LINK */
	#define USE_write_ts_log  PFWRITE_TS_LOG_IEC pfwrite_ts_log;
	#define EXT_write_ts_log  extern PFWRITE_TS_LOG_IEC pfwrite_ts_log;
	#define GET_write_ts_log(fl)  s_pfCMGetAPI2( "write_ts_log", (RTS_VOID_FCTPTR *)&pfwrite_ts_log, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xBBC343F7, 0x03050D00)
	#define CAL_write_ts_log  pfwrite_ts_log
	#define CHK_write_ts_log  (pfwrite_ts_log != NULL)
	#define EXP_write_ts_log   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"write_ts_log", (RTS_UINTPTR)write_ts_log, 1, 0xBBC343F7, 0x03050D00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpEmiconLog_C;

#ifdef CPLUSPLUS
class ICmpEmiconLog : public IBase
{
	public:
};
	#ifndef ITF_CmpEmiconLog
		#define ITF_CmpEmiconLog static ICmpEmiconLog *pICmpEmiconLog = NULL;
	#endif
	#define EXTITF_CmpEmiconLog
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconLog_C		ICmpEmiconLog;
	#ifndef ITF_CmpEmiconLog
		#define ITF_CmpEmiconLog
	#endif
	#define EXTITF_CmpEmiconLog
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONLOGITF_H_*/
