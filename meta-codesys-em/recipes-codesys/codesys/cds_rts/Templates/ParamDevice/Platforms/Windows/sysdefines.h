#ifndef __SYSDEFINES__H__
#define __SYSDEFINES__H__

/*
 * This include file is required by CmpStd.h. 
 * It's intention is to contain system specific "#define"'s.
 *
 */
#define INTEL_BYTE_ORDER

#if defined(_WINDOWS) || defined(WIN32) || defined (_WIN32_WCE)
	#include <windows.h>
	#include <windowsx.h>
#endif

#ifndef WIN32
	#define WIN32
#endif

#ifndef CDECL
	#define CDECL
#endif

#ifndef CDECL_EXT
	#define CDECL_EXT
#endif

#ifndef _PLCWinNT_
	#define _PLCWinNT_
#endif

#ifndef _WIN32_WCE
	#define TRG_X86
#endif

#ifdef _i386_
	#define TRG_X86
#endif

#ifdef _ARM_
	#define TRG_ARM		1
#endif

#ifdef _MPS_
	#define TRG_MIPS
#endif

#ifdef _SH4_
	#define TRG_SH
#endif

typedef signed   __int64 RTS_I64;
typedef unsigned __int64 RTS_UI64;
#define BASE64BITTYPES_DEFINED

#ifdef _WIN32_WCE
	#define BTAG_MAX_NESTED_TAGS	50
#else
	#define BTAG_MAX_NESTED_TAGS	100
#endif

/*
 * Defines the available communication buffers in the
 * communication server.
 * 
 * BUFFERSIZE is the overall amount of memory to be used by
 *  all channels
 * MAXCHANNELS defines the number of channels that may be handled 
 *  concurrently. 
 *
 * Since each channel needs separate send and receive channels
 * the available communication buffer is BUFFERSIZE / (2*MAXCHANNELS)
 */
#define NETSERVER_BUFFERSIZE	800000
#define NETSERVER_MAXCHANNELS	4

#define HUGEPTR
#define RTS_UNICODE
#ifdef CPLUSPLUS
	#define STATICITF_DEF
#endif

#define RTS_I64_CONST(a)	(a##i64)
#define RTS_UI64_CONST(a)	(a##ui64)


#ifdef _DEBUG
	#if !defined (_WIN32_WCE)
		#include <assert.h>
		#define RTS_ASSERT	assert
	#endif
#endif

#define SYSTARGET_DEVICE_TYPE		SYSTARGET_TYPE_PARAMETRIZABLE	
#define SYSTARGET_VENDOR_ID			RTS_VENDORID_3S
#define SYSTARGET_DEVICE_ID			0x0005
#define SYSTARGET_DEVICE_VERSION	RTS_VERSION
#define	SYSTARGET_NODE_NAME_WINCE	"CoDeSys ParamDevice"
#define SYSTARGET_DEVICE_NAME		"CoDeSys ParamDevice"
#define	SYSTARGET_VENDOR_NAME		"3S - Smart Software Solutions GmbH"

#endif /* __SYSDEFINES__H__ */
