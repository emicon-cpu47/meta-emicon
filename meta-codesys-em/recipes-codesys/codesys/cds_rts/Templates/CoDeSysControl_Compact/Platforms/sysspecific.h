#ifndef __SYSSPECIFIC__H__
#define __SYSSPECIFIC__H__

/* 
 * ---WIN32 specific---
 * 
 * This file is included by CmpStd.h.
 * It may contain system specific include files etc. 
 * 
 */

#if defined (_WIN32_WCE)
	/*Some Makros do not exist under Win CE*/
	#ifndef offsetof 
		#define offsetof(s,m)   (size_t)&(((s *)0)->m)
	#endif
	
	#define max(a,b)    (((a) > (b)) ? (a) : (b))
	#define min(a,b)    (((a) < (b)) ? (a) : (b))
#else
	#include <conio.h>
#endif

#if defined(WIN32) && defined(_DEBUG)
	#define RTS_DEBUG
#endif

#define RTS_CPU_SET_STACKPOINTER(pStack)				_asm mov esp, pStack
#define RTS_CPU_CALL_ON_STACK(pFunc, pParam, pStack) \
	_asm mov eax, pFunc \
	_asm mov ebx, pParam \
	_asm mov esp, pStack \
	_asm push ebx \
	_asm call eax

#define RTS_STRUCTURED_EXCEPTION_HANDLING

#define SYS_ATOMIC_COMPARE_AND_SWAP(piValue, iExchangeValue, iCompareValue, Result) \
	do { \
		if (InterlockedCompareExchange((volatile LONG *)piValue, iExchangeValue, iCompareValue) == iCompareValue) \
			Result = ERR_OK; \
		else \
			Result = ERR_FAILED; \
	} while (0)


#endif	/*__SYSSPECIFIC__H__*/
