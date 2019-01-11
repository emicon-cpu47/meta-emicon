#ifndef __SYSDEFINES__H__
#define __SYSDEFINES__H__

/*
 * This include file is required by CmpStd.h. 
 * It's intention is to contain system specific "#define"'s.
 *
 */

/* Set customer-specific defines to overload the defaults, below */
#include <targetdefines.h>
#include <license_sil2linux.h>

#define CDECL
#define __cdecl CDECL /*necessary for sqlite in CmpCAAStorage*/
#define STDCALL 
#define HUGEPTR
#define SYSTARGET_OS_NONE
#undef WIN32

#define RTS_STRUCTURED_EXCEPTION_HANDLING
#include <setjmp.h>
#define RTS_JMP_BUF 	sigjmp_buf
#define RTS_SETJMP(x)	sigsetjmp(x,1)
#define RTS_LONGJMP	siglongjmp

void SysTimerRestoreContextException(void);

#define RTS_CPU_CONTEXT_ATTRIBUTE
#define RTS_CPU_CONTEXT_BUFFER					sigjmp_buf
#define RTS_CPU_STORE_CONTEXT(context, piResult)		/*lint -e64 */(*((int*)piResult) = sigsetjmp(context,1))
#define RTS_CPU_RESTORE_CONTEXT(context, parameter)		siglongjmp(context, parameter)
#define RTS_CPU_RESTORE_CONTEXT_EXCEPTION(context, parameter)	SysTimerRestoreContextException()

#define RTS_SIL2_ATTRIBUTE __attribute__((section(".sil2")))


#ifndef SYSTARGET_SIGNATUREID
	#if defined (TRG_X86)
		#define SYSTARGET_SIGNATUREID		0x1D36140B
	#elif defined (TRG_ARM)
		#define SYSTARGET_SIGNATUREID		????????
	#elif defined (TRG_PPC)
		#define SYSTARGET_SIGNATUREID		????????
	#elif defined (TRG_MIPS)
		#define SYSTARGET_SIGNATUREID		????????
	#elif defined (TRG_SH)
		#if defined (TRG_SH3)
			#define SYSTARGET_SIGNATUREID		????????
		#elif defined (TRG_SH4)
			#define SYSTARGET_SIGNATUREID		????????
		#endif
	#elif defined (TRG_CORTEX)
		#define SYSTARGET_SIGNATUREID		????????
	#endif
#endif

#define BASE64BITTYPES_DEFINED
#ifndef STDINT_H_UINTPTR_T_DEFINED
	#define STDINT_H_UINTPTR_T_DEFINED
#endif

#ifndef NO_C99
	#define C99_FLOAT_FUNCTIONS
#endif

#ifndef MEMPOOL_8BYTE_ALIGNED
	#define MEMPOOL_8BYTE_ALIGNED
#endif

#ifndef INTEL_BYTE_ORDER
#ifndef  MOTOROLA_BYTE_ORDER
	#define INTEL_BYTE_ORDER
#endif
#endif
#if defined  (MOTOROLA_BYTE_ORDER) && defined (INTEL_BYTE_ORDER)
	#error "choose only ONE byteorder, that's enough"
#endif

typedef long long RTS_I64;
typedef unsigned long long RTS_UI64;

#define RTS_WCHAR_DEFINED
typedef unsigned short RTS_WCHAR;

#define  SOCK_BIND_TWO_SOCKETS 

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

#ifndef LOWMEMORY
	#define NETSERVER_BUFFERSIZE 800000
	#define NETSERVER_MAXCHANNELS 4
#else
	#define NETSERVER_BUFFERSIZE 40000
	#define NETSERVER_MAXCHANNELS 2
#endif

/*** NOT IMPLEMENTED ***/


#ifndef SYSTARGET_DEVICE_TYPE
	#define SYSTARGET_DEVICE_TYPE		SYSTARGET_TYPE_PROGRAMMABLE
#endif

#ifndef SYSTARGET_DEVICE_ID
	#if defined (TRG_X86)
		#define SYSTARGET_DEVICE_ID		0x8011
	#elif defined (TRG_ARM)
		#define SYSTARGET_DEVICE_ID		????????
	#elif defined (TRG_PPC)
		#define SYSTARGET_DEVICE_ID 	????????
	#elif defined (TRG_CORTEX)
		#define SYSTARGET_DEVICE_ID		????????
	#elif defined (TRG_MIPS)
		#define SYSTARGET_DEVICE_ID		????????
	#elif defined (TRG_SH)
		#ifdef TRG_SH3
			#define SYSTARGET_DEVICE_ID		????????
		#endif
		#ifdef TRG_SH4
			#define SYSTARGET_DEVICE_ID		????????
		#endif
	#else
		#define SYSTARGET_DEVICE_ID		0
	#endif
#endif

#ifndef SYSTARGET_DEVICE_VERSION
	#define SYSTARGET_DEVICE_VERSION	RTS_VERSION
#endif

/*#ifndef SYSTARGET_DEVICE_NAME*/
#ifdef SYSTARGET_DEVICE_NAME
        #undef SYSTARGET_DEVICE_NAME
#endif

#define SYSTARGET_DEVICE_NAME		"SIL2 Unsafe Linux"


#ifndef SYSTARGET_VENDOR_NAME
	#define	SYSTARGET_VENDOR_NAME		"3S - Smart Software Solutions GmbH"
#endif

#ifndef SYSTARGET_VENDOR_ID
	#define SYSTARGET_VENDOR_ID			RTS_VENDORID_3S
#endif

#define FILE_END_OF_LINE_DELIMITER 		"\n"

# if defined(__ARM_ARCH_6__)  || defined(__ARM_ARCH_6J__)  || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__) || defined(__ARM_ARCH_6T2__) || defined(__ARM_ARCH_6M__) 
	#define RTS_ARM_ARCH_VERSION 6
#elif defined(__ARM_ARCH_7__)  || defined(__ARM_ARCH_7A__)  || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7M__) 
	#define RTS_ARM_ARCH_VERSION 7
#else
	#define RTS_ARM_ARCH_VERSION 5
#endif

#define RTS_COMPACT
#define STATIC_LINK
#define CMPXMLPARSER_NOTIMPLEMENTED
#define CMPAPPBP_NOTIMPLEMENTED
#define CMPAPPFORCE_NOTIMPLEMENTED
#define CMPASYNCMGR_NOTIMPLEMENTED
#define CMPMEMGC_NOTIMPLEMENTED
#define CMPTRACEMGR_NOTIMPLEMENTED
#define CMPUSERMGR_NOTIMPLEMENTED
#define SYSEVENT_NOTIMPLEMENTED
#define SYSSEM_NOTIMPLEMENTED
#define SYSTASK_NOTIMPLEMENTED
#define SYSTIMERTC_NOTIMPLEMENTED
#define CMPMONITOR2_NOTIMPLEMENTED
#define SYSSEMPROCESS_NOTIMPLEMENTED
#define CMPSIL2_NOTIMPLEMENTED



#define FLASH_SIZE    0x80000
#define FLASH_START_ADDRESS   0x40000

#define FILE1_SIZE    FLASH_SIZE
/* Filemap */
#define FILE_MAP FILE_DESC m_FileSystem[] = \
{ \
	/*Name					Offset				MaxSize				read index	write index */\
	{"Application.app",		0x0,				FILE1_SIZE,			0xFFFFFFFF, 0xFFFFFFFF},\
};

#define EVENTMGR_NUM_OF_STATIC_EVENTS 				80
#define EVENTMGR_NUM_OF_STATIC_CALLBACKS 			10

#define APPL_NUM_OF_STATIC_APPLS 					1
#define APPL_NUM_OF_STATIC_SESSIONIDS 				2
#define APPL_NUM_OF_STATIC_AREAS 					5
#define APPL_STATIC_FORCE_ENTRIES 					0
#define APP_STATIC_BP_ENTRIES 						0
#define APP_NUM_OF_STATIC_ASYNC_SERVICES 			0

#define NUM_OF_STATIC_IEC_TASKS 					3
#define MAX_IEC_TASKS 								NUM_OF_STATIC_IEC_TASKS
#define NUM_OF_STATIC_IEC_SLOTS 					5
#define MAX_IEC_SLOTS 								NUM_OF_STATIC_IEC_SLOTS
#define CMPSCHEDULE_IECTASK_STACK_SIZE				0x1500
#define SCHEDULEKEY_INT_SCHEDULER_INTERVAL_DEFAULT	30000

#define LOG_STD_MAX_NUM_OF_ENTRIES 					50
#define LOG_TEXT(s) 								s

#define CM_NUM_OF_STATIC_COMPONENTS 				50
#define CM_NUM_OF_STATIC_CLASSES 					8
#define CM_NUM_OF_STATIC_INSTANCES					5


#ifdef RTS_MODULETEST
#    define COPIED_IO_CONFIG_SIZE 0x8000
#else
#    define COPIED_IO_CONFIG_SIZE 0x20000
#endif

#define SETTG_ENTRIES_INT \
	{"CmpAppEmbedded", "Bootproject.RunInFlash", 1}, \
	{"CmpSocketCanDrv", "Timestamps", 1}, \
	{0, 0, 0}

#define SETTG_ENTRIES_STRING \
	{0, 0, 0}

#endif /* __SYSDEFINES__H__ */
