/**
 * <interfacename>SysModRTMain</interfacename>
 * <description> 
 *
 * </description>
 *
 * <copyright>
 * Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 * </copyright>
 */
 
SET_INTERFACE_NAME(`SysModRTMain')

REF_ITF(`SysFlashItf.m4')
REF_ITF(`SysTimeItf.m4')
REF_ITF(`SysModRTSubItf.m4')

#include "CmpItf.h"

/**
 * <category>Static defines</category>
 * <description>Memory address of SysModRTMainFunctionTable</description>
 */
#ifndef MODRTMAIN_FUNCTION_TABLE_ADDRESS
	#error MODRTMAIN_FUNCTION_TABLE_ADDRESS not defined!!
#endif


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	PFSYSFLASHERASE pfSysFlashErase;
	PFSYSFLASHWRITE pfSysFlashWrite;
	PFSYSFLASHFLUSH pfSysFlashFlush;
	PFSYSTIMEGETMS pfSysTimeGetMs;
	PFSYSTIMEGETUS pfSysTimeGetUs;
	PFSYSTIMEGETNS pfSysTimeGetNs;
} SysModRTMainFunctionTable;

/* no functions to export */


/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
