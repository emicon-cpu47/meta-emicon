/**
 * <interfacename>CmpEmiconLog</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpEmiconLog')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`clr_sys_log',`(clr_sys_log_struct *p)',1,0x8B141454,0x03050D00)

/**
 * <description>create_log_files</description>
 */
typedef struct tagcreate_log_files_struct
{
	RTS_IEC_DINT create_log_files;		/* VAR_OUTPUT */	
} create_log_files_struct;

DEF_API(`void',`CDECL',`create_log_files',`(create_log_files_struct *p)',1,0x5B82FD55,0x03050D00)

/**
 * <description>get_next_log_item</description>
 */
typedef struct tagget_next_log_item_struct
{
	RTS_IEC_BOOL get_first;				/* VAR_INPUT */	
	RTS_IEC_STRING *log_str;			/* VAR_INPUT */	
	RTS_IEC_INT get_next_log_item;		/* VAR_OUTPUT */	
} get_next_log_item_struct;

DEF_API(`void',`CDECL',`get_next_log_item',`(get_next_log_item_struct *p)',1,0xDA44E7BB,0x03050D00)

/**
 * <description>write_sys_log</description>
 */
typedef struct tagwrite_sys_log_struct
{
	RTS_IEC_BYTE byClassId;				/* VAR_INPUT */	
	RTS_IEC_DWORD dwValue;				/* VAR_INPUT */	
	RTS_IEC_UDINT write_sys_log;		/* VAR_OUTPUT */	
} write_sys_log_struct;

DEF_API(`void',`CDECL',`write_sys_log',`(write_sys_log_struct *p)',1,0xA5470BCD,0x03050D00)

/**
 * <description>write_ti_log</description>
 */
typedef struct tagwrite_ti_log_struct
{
	RTS_IEC_BYTE byClassId;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_UDINT write_ti_log;			/* VAR_OUTPUT */	
} write_ti_log_struct;

DEF_API(`void',`CDECL',`write_ti_log',`(write_ti_log_struct *p)',1,0xEED4B686,0x03050D00)

/**
 * <description>write_ts_log</description>
 */
typedef struct tagwrite_ts_log_struct
{
	RTS_IEC_BYTE byClassId;				/* VAR_INPUT */	
	RTS_IEC_BYTE *pbyData;				/* VAR_INPUT */	
	RTS_IEC_UDINT write_ts_log;			/* VAR_OUTPUT */	
} write_ts_log_struct;

DEF_API(`void',`CDECL',`write_ts_log',`(write_ts_log_struct *p)',1,0xBBC343F7,0x03050D00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

