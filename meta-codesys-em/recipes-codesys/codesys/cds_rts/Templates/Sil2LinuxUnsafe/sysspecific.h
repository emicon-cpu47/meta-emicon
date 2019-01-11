#include <limits.h>

#ifndef __SYSSPECIFIC__H__
#define __SYSSPECIFIC__H__
/*
 * ---Linux/QNX specific---
 * 
 * This file is included at the end of  CmpStd.h.
 * It may contain system specific include files etc. 
 * 
 */

#ifndef PTHREAD_STACK_MIN
	#define PTHREAD_STACK_MIN		0x4000
#endif

#define HANDLE2FD(h)	(int)(unsigned long)h
#define FD2HANDLE(fd)	(RTS_HANDLE)(unsigned long)(fd)

/* Debugging  ---------------------------------------------------------------------------------------- */
#ifdef RTS_DEBUG

#ifndef DEBUGPRINT
#define DEBUGPRINT
#endif

#ifdef RTS_ASSERT
  #undef RTS_ASSERT
#endif
#define RTS_ASSERT(expr) \
        if (!(expr)) DEBUGP("ASSERT: '%s'\n", #expr)

#endif

#ifdef DEBUGPRINT
#define DEBUGP(fmt, args...) \
        printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
#else
#define	DEBUGP(fmt, args...)
#endif
/* --------------------------------------------------------------------------------------------------- */

#define RTS_CPU_SET_STACKPOINTER(pStack)		asm volatile("mov %0, %esp"::"r"(pStack):);

#define RTS_CPU_CALL_ON_STACK(pFunc, pParam, pStack) asm volatile("mov %1, %%ebx\n\t""mov %2, %%esp\n\t""push %%ebx\n\t""call *%0\n\t"::"r"(pFunc),"r"(pParam),"r"(pStack));

#endif	/*__SYSSPECIFIC__H__*/
  	
