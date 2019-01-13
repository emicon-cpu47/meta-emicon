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

#ifdef RTS_ASSERT
  #undef RTS_ASSERT
#endif
 #define RTS_ASSERT(expr) \
        if (!(expr)) DEBUGP("ASSERT: '%s'\n", #expr)

 #ifdef PLC_HANDLER
  #define DEBUGP(fmt, args...) \
        printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
 #endif

#else
 #ifdef PLC_HANDLER
  #define DEBUGP(fmt, args...)
 #endif
#endif

#ifndef PLC_HANDLER

 extern int b_debug;

 #define DEBUGP(fmt, args...) \
        if(b_debug)printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
 #define DEBUGP2(fmt, args...) \
        if(b_debug >= 2)printf("%s[%d]: " fmt "\n", __FUNCTION__, __LINE__, ## args)
#else
 #define DEBUGP2(fmt, args...)
#endif
/* --------------------------------------------------------------------------------------------------- */

#ifdef RASPBERRYPI
	#define memcpy(a,b,c) CMUtlMemCpy(a,b,c)
#endif


extern int rts_system(const char *command);
#endif	/*__SYSSPECIFIC__H__*/
  	
