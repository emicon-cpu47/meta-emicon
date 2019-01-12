/**
 * <interfacename>EmiconSys</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`EmiconSys')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`get_ptr_to_dpm',`(get_ptr_to_dpm_struct *p)',1,0x7C8941E2,0x03050A00)

/**
 * <description>get_ptr_to_slot0</description>
 */
typedef struct tagget_ptr_to_slot0_struct
{
	RTS_IEC_BYTE *Get_ptr_to_slot0;		/* VAR_OUTPUT */	
} get_ptr_to_slot0_struct;

DEF_API(`void',`CDECL',`get_ptr_to_slot0',`(get_ptr_to_slot0_struct *p)',1,0xE6CB94A0,0x03050A00)

/**
 * <description>get_ptr_to_sock_arr</description>
 */
typedef struct tagget_ptr_to_sock_arr_struct
{
	RTS_IEC_UDINT *Get_ptr_to_sock_arr;	/* VAR_OUTPUT */	
} get_ptr_to_sock_arr_struct;

DEF_API(`void',`CDECL',`get_ptr_to_sock_arr',`(get_ptr_to_sock_arr_struct *p)',1,0x7F4ADBA2,0x03050A00)

/**
 * <description>set_inhibit</description>
 */
typedef struct tagset_inhibit_struct
{
	RTS_IEC_INT set_inhibit;			/* VAR_OUTPUT */	
} set_inhibit_struct;

DEF_API(`void',`CDECL',`set_inhibit',`(set_inhibit_struct *p)',1,0xAFE8BB40,0x03050A00)

/**
 * <description>set_watchdog</description>
 */
typedef struct tagset_watchdog_struct
{
	RTS_IEC_INT set_watchdog;			/* VAR_OUTPUT */	
} set_watchdog_struct;

DEF_API(`void',`CDECL',`set_watchdog',`(set_watchdog_struct *p)',1,0x9CA67B6B,0x03050A00)

/**
 * <description>syssync</description>
 */
typedef struct tagsyssync_struct
{
	RTS_IEC_INT SysSync;				/* VAR_OUTPUT */	
} syssync_struct;

DEF_API(`void',`CDECL',`syssync',`(syssync_struct *p)',1,0xDC1119C9,0x03050A00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

