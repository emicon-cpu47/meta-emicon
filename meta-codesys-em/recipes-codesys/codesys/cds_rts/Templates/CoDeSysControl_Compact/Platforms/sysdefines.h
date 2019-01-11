#ifndef __SYSDEFINES__H__
#define __SYSDEFINES__H__

#ifdef _WINDOWS
	#ifndef WIN32
		#define WIN32
	#endif
#endif

#if defined(WIN32) || defined (_WIN32_WCE)
	#pragma warning( disable: 4100 )	/* Disable warning messages in Visual C++ */
	#pragma warning( disable: 4152 )	/* Disable warning messages in Visual C++ */
	#pragma warning( disable: 4505 )	/* Disable warning messages in Visual C++ */
	#pragma warning( disable: 4127 )	/* Disable warning messages in Visual C++ */
	#pragma warning( disable: 4996 )	/* Disable warning messages in Visual C++ */

	#pragma warning( disable: 4214 )	/* Warning only disabled because of CAA components. If this is fixed, this warning can be removed. */
	#pragma warning( disable: 4054 )	/* Warning only disabled because of wrong interfaces in SysCpuHandling and SysApp, after fix => remove */
	#pragma warning( disable: 4055 )	/* Warning only disabled because of type cast warning in CmpApp */
#endif

#define __STDC_FORMAT_MACROS

#if (_MSC_VER < 1600)
	#define RTS_NO_STDINT_H
#endif

#if (_MSC_VER < 1400)
	#define RTS_VSNPRINTF			_vsnprintf
#else
	/* Needed for Visual Studio >= 2005 */
	#define RTS_VSNPRINTF(s,len,format,arglist)			vsnprintf_s(s,len,len,format,arglist)

	#if !defined(_WIN64) && !defined(_USE_32BIT_TIME_T)
		#define _USE_32BIT_TIME_T
	#endif

	#ifndef _CRT_SECURE_NO_DEPRECATE 
		#define _CRT_SECURE_NO_DEPRECATE
	#endif

	#ifndef _CRT_SECURE_NO_WARNINGS
		#define _CRT_SECURE_NO_WARNINGS
	#endif
#endif

#ifndef CPLUSPLUS
	#define STATIC_LINK
	#ifndef RTS_COMPACT
		#define RTS_COMPACT
	#endif
#endif

/*********** uRTS specific macros *********/
/* Moved to the build settings! */
/*
#define RTS_COMPACT_MICRO
#define SYSINTERNAL_DISABLE_64BIT

#ifndef RTS_CONFIG_FILE
#	define RTS_CONFIG_FILE uRtsWin.h
#endif
*/
/******************************************/
#ifndef PREFER_PORTABLE_SNPRINTF
#	define PREFER_PORTABLE_SNPRINTF
#endif

/*
#ifndef CONV_TO_STR_TEST
#	define CONV_TO_STR_TEST
#endif


#ifndef PORTABLE_SNPRINTF_TEST
#	define PORTABLE_SNPRINTF_TEST
#endif

#ifndef ULTOA_TEST
#	define ULTOA_TEST
#endif

#ifndef LTOA_TEST
#	define LTOA_TEST
#endif
*/

/*
 * This include file is required by CmpStd.h. 
 * It's intention is to contain system specific "#define"'s.
 *
 */
#ifdef CODESYSCONTROL_COMPACT_TIMER
	#include "CoDeSysControl_Compact_Timer_NotImpl.h"
#else
	#ifdef RTS_SIL2
		#include "CoDeSysControl_Compact_SIL2_NotImpl.h"		
	#elif defined(RTS_COMPACT_MICRO)
		#include "CoDeSysControl_uRTS_NotImpl.h"
	#elif defined (CODESYSCONTROL_COMPACT_CAN)
		#include "CoDeSysControl_Compact_CAN_NotImpl.h"	
	#elif !defined(CPLUSPLUS)
		#include "CoDeSysControl_Compact_NotImpl.h"	
	#endif
#endif

#if defined(RTS_COMPACT) || defined(RTS_SIL2)
	#define CM_NO_EXIT
	#define CM_NO_DYNAMIC_COMPONENTS
#endif


#define INTEL_BYTE_ORDER
/*
#define MOTOROLA_BYTE_ORDER
*/

#define TRG_X86
/*
#define TRG_ARM
#define TRG_PPC
#define TRG_MIPS
#define TRG_SH
*/

#define SYSTARGET_OS_NONE

#define HUGEPTR
#define RTS_UNICODE


#define APPL_NUM_OF_STATIC_APPLS			1
#define APPL_NUM_OF_STATIC_SESSIONIDS		2
#define APPL_NUM_OF_STATIC_AREAS			4
#define APPL_STATIC_FORCE_ENTRIES			10

#ifdef RTS_COMPACT_MICRO
#define APP_STATIC_BP_ENTRIES				0
#else
#define APP_STATIC_BP_ENTRIES				10
#endif

#define APP_NUM_OF_STATIC_ASYNC_SERVICES	0

#define NUM_OF_STATIC_IEC_TASKS				3
#define MAX_IEC_TASKS						NUM_OF_STATIC_IEC_TASKS
#ifdef RTS_COMPACT_MICRO
#define NUM_OF_STATIC_IEC_SLOTS				5
#else
#define NUM_OF_STATIC_IEC_SLOTS				10
#endif
#define MAX_IEC_SLOTS						NUM_OF_STATIC_IEC_SLOTS	

#define	LOG_STD_MAX_NUM_OF_ENTRIES			3
#ifndef _DEBUG
	#define LOG_TEXT(s)						NULL
#endif

#define MAX_COM_PORTS						1
#define MAX_UDP_DEVICES						1

#ifndef CPLUSPLUS
	#define CM_NUM_OF_STATIC_CLASSES			8
	#define CM_NUM_OF_STATIC_INSTANCES			5
#endif

/* #define SYSINTERNAL_DISABLE_64BIT */
#define CMPSETTINGSEMBEDDEDSRV_NOTIMPLEMENTED
#define SYSDIR_NOTIMPLEMETED

#define CM_NO_DYNAMIC_COMPONENTS

/* Disable not needed external library functions */
#ifndef CPLUSPLUS
#define CMPAPPEMBEDDED_DISABLE_EXTREF
#define CMPCHECKSUM_DISABLE_EXTREF
#define CMPEVENTMGR_DISABLE_EXTREF
#define CMPROUTEREMBEDDED_DISABLE_EXTREF
#define CMPSETTINGSEMBEDDED_DISABLE_EXTREF
#define SYSCOM_DISABLE_EXTREF
#define SYSSOCKET_DISABLE_EXTREF
#endif

#define BTAG_MAX_NESTED_TAGS	5

#define CMPSCHEDULE_IECTASK_STACK_SIZE 8192

/**
 * <category>Static defines</category>
 * <description>Defines the available communication buffers in the
 *	communication server. Since each channel needs separate send and receive channels
 *	the available communication buffer is NETSERVER_BUFFERSIZE / (2*NETSERVER_MAXCHANNELS).
 *	NETSERVER_BUFFERSIZE is the overall amount of memory to be used by all channels.
 * </description>
 */
#define NETSERVER_BUFFERSIZE	4096

/**
 * <category>Static defines</category>
 * <description>Defines the available communication buffers in the
 *	communication server
 *	NETSERVER_MAXCHANNELS defines the number of channels that may be handled 
 *  concurrently.
 * </description>
 */
#define NETSERVER_MAXCHANNELS	1

#ifdef RUN_IN_FLASH
	#define APPKEY_INT_BOOTPROJECT_RUN_IN_FLASH_DEFAULT				1
#endif

#define SETTG_ENTRIES_INT \
	{"CmpBlkDrvCom", "Com.0.Port", 1}, \
	{"CmpBlkDrvCom", "Com.0.Baudrate", 115200}, \
	{0, 0, 0}


#ifdef CPLUSPLUS
	#define FILE1_SIZE	0x100000
#else
	#define FILE1_SIZE	0x80000
#endif
#define FILE2_SIZE	0x5000

#define SYSFILEFLASH_MAX_SIZE		(FILE1_SIZE + FILE2_SIZE)
#define FILE_MAP					static FILE_DESC m_FileSystem[] =	{ \
																			/*Name					Offset				MaxSize				read index	write index */\
																			{"Application.app",		0x0,				FILE1_SIZE,			0xFFFFFFFF, 0xFFFFFFFF},\
																			{"Test.txt",			FILE1_SIZE,			FILE2_SIZE,			0xFFFFFFFF, 0xFFFFFFFF}\
																		}

#ifdef WIN32
	#include <windows.h>
	#include <windowsx.h>
	typedef signed   __int64 RTS_I64;
	typedef unsigned __int64 RTS_UI64;

	#define RTS_I64_CONST(a)	(a##i64)
	#define RTS_UI64_CONST(a)	(a##ui64)
#else
	typedef signed   long long RTS_I64;
	typedef unsigned long long RTS_UI64;
#endif
#define BASE64BITTYPES_DEFINED

#ifdef _DEBUG
	#include <assert.h>
	#define RTS_ASSERT	assert
#endif


#if defined(RTS_SIL2)
	#include "targetdefines_sil2.h"
#elif defined(RTS_COMPACT_MICRO)
	#include "targetdefines_micro.h"
#else
	#include "targetdefines_compact.h"
#endif

#ifdef RTS_MODULETEST
#    define COPIED_IO_CONFIG_SIZE 0x8000
#else
#    define COPIED_IO_CONFIG_SIZE 0x20000
#endif

#ifndef RTS_SIL2
	#ifndef CMPSIL2_NOTIMPLEMENTED
		#define CMPSIL2_NOTIMPLEMENTED
	#endif
#endif


#endif /* __SYSDEFINES__H__ */
