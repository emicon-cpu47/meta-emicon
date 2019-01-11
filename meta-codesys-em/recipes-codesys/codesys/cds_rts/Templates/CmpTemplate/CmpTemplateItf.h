 
	
	
#ifndef _CMPTEMPLATEITF_H_
#define _CMPTEMPLATEITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#define CH_USER_1						10000
/*	First user hook
	ulParam1: Not used
	ulParam2: Not used
*/

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Generated comment for MyExternalFunction
 * RETURN: Returns the runtime system error code (see CmpErrors.library)
 */
typedef struct tagmyexternalfunction_struct
{
	RTS_IEC_DINT p1;					/* VAR_INPUT */	/* Dummy parameter */
	RTS_IEC_DINT MyExternalFunction;	/* VAR_OUTPUT */	
} myexternalfunction_struct;

void CDECL CDECL_EXT myexternalfunction(myexternalfunction_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTION_IEC) (myexternalfunction_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTION_NOTIMPLEMENTED)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunction(p0) 
	#define CHK_myexternalfunction  FALSE
	#define EXP_myexternalfunction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0x184DFC0B, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0x184DFC0B, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunction
	#define EXT_CmpTemplatemyexternalfunction
	#define GET_CmpTemplatemyexternalfunction  ERR_OK
	#define CAL_CmpTemplatemyexternalfunction  myexternalfunction
	#define CHK_CmpTemplatemyexternalfunction  TRUE
	#define EXP_CmpTemplatemyexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0x184DFC0B, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunction
	#define EXT_myexternalfunction
	#define GET_myexternalfunction(fl)  CAL_CMGETAPI( "myexternalfunction" ) 
	#define CAL_myexternalfunction  myexternalfunction
	#define CHK_myexternalfunction  TRUE
	#define EXP_myexternalfunction  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0x184DFC0B, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunction  PFMYEXTERNALFUNCTION_IEC pfmyexternalfunction;
	#define EXT_myexternalfunction  extern PFMYEXTERNALFUNCTION_IEC pfmyexternalfunction;
	#define GET_myexternalfunction(fl)  s_pfCMGetAPI2( "myexternalfunction", (RTS_VOID_FCTPTR *)&pfmyexternalfunction, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x184DFC0B, 0x03050600)
	#define CAL_myexternalfunction  pfmyexternalfunction
	#define CHK_myexternalfunction  (pfmyexternalfunction != NULL)
	#define EXP_myexternalfunction   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunction", (RTS_UINTPTR)myexternalfunction, 1, 0x184DFC0B, 0x03050600) 
#endif


/**
 * Generated comment for MyExternalFunctionblock
 */
typedef struct tagmyexternalfunctionblock_struct
{
	void* __VFTABLEPOINTER;				/* Pointer to virtual function table */

	RTS_IEC_BOOL bShow;					/* VAR_INPUT */	/* Partmeter to show message box: 1=Message box will be displayed, 0=else */
	RTS_IEC_BOOL bError;				/* VAR_INPUT */	/* Parameter to select the Icon of the message box: 1=Show error message box, 0=show information message box */
	RTS_IEC_STRING *MessageText;		/* VAR_INPUT */	/* Message text to show in the message box */
	RTS_IEC_DINT Out;					/* VAR_OUTPUT */	/* Result of the operation:
 + 1: Successful
 + 0: Failed */
	RTS_IEC_DINT _internalVar;			/* Local variable */	
	RTS_IEC_DWORD _property;			/* Local variable */	
	RTS_IEC_DWORD PropTest;				/* Local variable */	
} myexternalfunctionblock_struct;

/**
 * <description>myexternalfunctionblock_main</description>
 */
typedef struct tagmyexternalfunctionblock_main_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
} myexternalfunctionblock_main_struct;

void CDECL CDECL_EXT myexternalfunctionblock__main(myexternalfunctionblock_main_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__MAIN_IEC) (myexternalfunctionblock_main_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__MAIN_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__main
	#define EXT_myexternalfunctionblock__main
	#define GET_myexternalfunctionblock__main(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__main(p0) 
	#define CHK_myexternalfunctionblock__main  FALSE
	#define EXP_myexternalfunctionblock__main  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__main
	#define EXT_myexternalfunctionblock__main
	#define GET_myexternalfunctionblock__main(fl)  CAL_CMGETAPI( "myexternalfunctionblock__main" ) 
	#define CAL_myexternalfunctionblock__main  myexternalfunctionblock__main
	#define CHK_myexternalfunctionblock__main  TRUE
	#define EXP_myexternalfunctionblock__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__main", (RTS_UINTPTR)myexternalfunctionblock__main, 1, 0x39AB6C8B, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__main
	#define EXT_myexternalfunctionblock__main
	#define GET_myexternalfunctionblock__main(fl)  CAL_CMGETAPI( "myexternalfunctionblock__main" ) 
	#define CAL_myexternalfunctionblock__main  myexternalfunctionblock__main
	#define CHK_myexternalfunctionblock__main  TRUE
	#define EXP_myexternalfunctionblock__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__main", (RTS_UINTPTR)myexternalfunctionblock__main, 1, 0x39AB6C8B, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__main
	#define EXT_CmpTemplatemyexternalfunctionblock__main
	#define GET_CmpTemplatemyexternalfunctionblock__main  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__main  myexternalfunctionblock__main
	#define CHK_CmpTemplatemyexternalfunctionblock__main  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__main", (RTS_UINTPTR)myexternalfunctionblock__main, 1, 0x39AB6C8B, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__main
	#define EXT_myexternalfunctionblock__main
	#define GET_myexternalfunctionblock__main(fl)  CAL_CMGETAPI( "myexternalfunctionblock__main" ) 
	#define CAL_myexternalfunctionblock__main  myexternalfunctionblock__main
	#define CHK_myexternalfunctionblock__main  TRUE
	#define EXP_myexternalfunctionblock__main  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__main", (RTS_UINTPTR)myexternalfunctionblock__main, 1, 0x39AB6C8B, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__main  PFMYEXTERNALFUNCTIONBLOCK__MAIN_IEC pfmyexternalfunctionblock__main;
	#define EXT_myexternalfunctionblock__main  extern PFMYEXTERNALFUNCTIONBLOCK__MAIN_IEC pfmyexternalfunctionblock__main;
	#define GET_myexternalfunctionblock__main(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__main", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__main, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x39AB6C8B, 0x03050600)
	#define CAL_myexternalfunctionblock__main  pfmyexternalfunctionblock__main
	#define CHK_myexternalfunctionblock__main  (pfmyexternalfunctionblock__main != NULL)
	#define EXP_myexternalfunctionblock__main   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__main", (RTS_UINTPTR)myexternalfunctionblock__main, 1, 0x39AB6C8B, 0x03050600) 
#endif


/**
 * <description>myexternalfunctionblock_mygenerateexception</description>
 */
typedef struct tagmyexternalfunctionblock_mygenerateexception_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD dwException;			/* VAR_INPUT */	
	RTS_IEC_BOOL MyGenerateException;	/* VAR_OUTPUT */	
} myexternalfunctionblock_mygenerateexception_struct;

void CDECL CDECL_EXT myexternalfunctionblock__mygenerateexception(myexternalfunctionblock_mygenerateexception_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__MYGENERATEEXCEPTION_IEC) (myexternalfunctionblock_mygenerateexception_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__MYGENERATEEXCEPTION_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__mygenerateexception
	#define EXT_myexternalfunctionblock__mygenerateexception
	#define GET_myexternalfunctionblock__mygenerateexception(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__mygenerateexception(p0) 
	#define CHK_myexternalfunctionblock__mygenerateexception  FALSE
	#define EXP_myexternalfunctionblock__mygenerateexception  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__mygenerateexception
	#define EXT_myexternalfunctionblock__mygenerateexception
	#define GET_myexternalfunctionblock__mygenerateexception(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mygenerateexception" ) 
	#define CAL_myexternalfunctionblock__mygenerateexception  myexternalfunctionblock__mygenerateexception
	#define CHK_myexternalfunctionblock__mygenerateexception  TRUE
	#define EXP_myexternalfunctionblock__mygenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mygenerateexception", (RTS_UINTPTR)myexternalfunctionblock__mygenerateexception, 1, 0x6B216090, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__mygenerateexception
	#define EXT_myexternalfunctionblock__mygenerateexception
	#define GET_myexternalfunctionblock__mygenerateexception(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mygenerateexception" ) 
	#define CAL_myexternalfunctionblock__mygenerateexception  myexternalfunctionblock__mygenerateexception
	#define CHK_myexternalfunctionblock__mygenerateexception  TRUE
	#define EXP_myexternalfunctionblock__mygenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mygenerateexception", (RTS_UINTPTR)myexternalfunctionblock__mygenerateexception, 1, 0x6B216090, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__mygenerateexception
	#define EXT_CmpTemplatemyexternalfunctionblock__mygenerateexception
	#define GET_CmpTemplatemyexternalfunctionblock__mygenerateexception  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__mygenerateexception  myexternalfunctionblock__mygenerateexception
	#define CHK_CmpTemplatemyexternalfunctionblock__mygenerateexception  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__mygenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mygenerateexception", (RTS_UINTPTR)myexternalfunctionblock__mygenerateexception, 1, 0x6B216090, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__mygenerateexception
	#define EXT_myexternalfunctionblock__mygenerateexception
	#define GET_myexternalfunctionblock__mygenerateexception(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mygenerateexception" ) 
	#define CAL_myexternalfunctionblock__mygenerateexception  myexternalfunctionblock__mygenerateexception
	#define CHK_myexternalfunctionblock__mygenerateexception  TRUE
	#define EXP_myexternalfunctionblock__mygenerateexception  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mygenerateexception", (RTS_UINTPTR)myexternalfunctionblock__mygenerateexception, 1, 0x6B216090, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__mygenerateexception  PFMYEXTERNALFUNCTIONBLOCK__MYGENERATEEXCEPTION_IEC pfmyexternalfunctionblock__mygenerateexception;
	#define EXT_myexternalfunctionblock__mygenerateexception  extern PFMYEXTERNALFUNCTIONBLOCK__MYGENERATEEXCEPTION_IEC pfmyexternalfunctionblock__mygenerateexception;
	#define GET_myexternalfunctionblock__mygenerateexception(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__mygenerateexception", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__mygenerateexception, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6B216090, 0x03050600)
	#define CAL_myexternalfunctionblock__mygenerateexception  pfmyexternalfunctionblock__mygenerateexception
	#define CHK_myexternalfunctionblock__mygenerateexception  (pfmyexternalfunctionblock__mygenerateexception != NULL)
	#define EXP_myexternalfunctionblock__mygenerateexception   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mygenerateexception", (RTS_UINTPTR)myexternalfunctionblock__mygenerateexception, 1, 0x6B216090, 0x03050600) 
#endif


/**
 * FB init routine
 */
typedef struct tagmyexternalfunctionblock_fb_init_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL bInitRetains;			/* VAR_INPUT */	
	RTS_IEC_BOOL bInCopyCode;			/* VAR_INPUT */	
	RTS_IEC_BOOL FB_Init;				/* VAR_OUTPUT */	
} myexternalfunctionblock_fb_init_struct;

void CDECL CDECL_EXT myexternalfunctionblock__fb_init(myexternalfunctionblock_fb_init_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__FB_INIT_IEC) (myexternalfunctionblock_fb_init_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__FB_INIT_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__fb_init
	#define EXT_myexternalfunctionblock__fb_init
	#define GET_myexternalfunctionblock__fb_init(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__fb_init(p0) 
	#define CHK_myexternalfunctionblock__fb_init  FALSE
	#define EXP_myexternalfunctionblock__fb_init  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__fb_init
	#define EXT_myexternalfunctionblock__fb_init
	#define GET_myexternalfunctionblock__fb_init(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_init" ) 
	#define CAL_myexternalfunctionblock__fb_init  myexternalfunctionblock__fb_init
	#define CHK_myexternalfunctionblock__fb_init  TRUE
	#define EXP_myexternalfunctionblock__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_init", (RTS_UINTPTR)myexternalfunctionblock__fb_init, 1, 0x537E01E5, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__fb_init
	#define EXT_myexternalfunctionblock__fb_init
	#define GET_myexternalfunctionblock__fb_init(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_init" ) 
	#define CAL_myexternalfunctionblock__fb_init  myexternalfunctionblock__fb_init
	#define CHK_myexternalfunctionblock__fb_init  TRUE
	#define EXP_myexternalfunctionblock__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_init", (RTS_UINTPTR)myexternalfunctionblock__fb_init, 1, 0x537E01E5, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__fb_init
	#define EXT_CmpTemplatemyexternalfunctionblock__fb_init
	#define GET_CmpTemplatemyexternalfunctionblock__fb_init  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__fb_init  myexternalfunctionblock__fb_init
	#define CHK_CmpTemplatemyexternalfunctionblock__fb_init  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_init", (RTS_UINTPTR)myexternalfunctionblock__fb_init, 1, 0x537E01E5, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__fb_init
	#define EXT_myexternalfunctionblock__fb_init
	#define GET_myexternalfunctionblock__fb_init(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_init" ) 
	#define CAL_myexternalfunctionblock__fb_init  myexternalfunctionblock__fb_init
	#define CHK_myexternalfunctionblock__fb_init  TRUE
	#define EXP_myexternalfunctionblock__fb_init  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_init", (RTS_UINTPTR)myexternalfunctionblock__fb_init, 1, 0x537E01E5, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__fb_init  PFMYEXTERNALFUNCTIONBLOCK__FB_INIT_IEC pfmyexternalfunctionblock__fb_init;
	#define EXT_myexternalfunctionblock__fb_init  extern PFMYEXTERNALFUNCTIONBLOCK__FB_INIT_IEC pfmyexternalfunctionblock__fb_init;
	#define GET_myexternalfunctionblock__fb_init(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__fb_init", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__fb_init, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x537E01E5, 0x03050600)
	#define CAL_myexternalfunctionblock__fb_init  pfmyexternalfunctionblock__fb_init
	#define CHK_myexternalfunctionblock__fb_init  (pfmyexternalfunctionblock__fb_init != NULL)
	#define EXP_myexternalfunctionblock__fb_init   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_init", (RTS_UINTPTR)myexternalfunctionblock__fb_init, 1, 0x537E01E5, 0x03050600) 
#endif


/**
 * <description>myexternalfunctionblock_setproptest</description>
 */
typedef struct tagmyexternalfunctionblock_setproptest_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD PropTest;				/* VAR_INPUT */	
	RTS_IEC_BOOL __setPropTest;			/* VAR_OUTPUT */	
} myexternalfunctionblock_setproptest_struct;

void CDECL CDECL_EXT myexternalfunctionblock__setproptest(myexternalfunctionblock_setproptest_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__SETPROPTEST_IEC) (myexternalfunctionblock_setproptest_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__SETPROPTEST_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__setproptest
	#define EXT_myexternalfunctionblock__setproptest
	#define GET_myexternalfunctionblock__setproptest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__setproptest(p0) 
	#define CHK_myexternalfunctionblock__setproptest  FALSE
	#define EXP_myexternalfunctionblock__setproptest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__setproptest
	#define EXT_myexternalfunctionblock__setproptest
	#define GET_myexternalfunctionblock__setproptest(fl)  CAL_CMGETAPI( "myexternalfunctionblock__setproptest" ) 
	#define CAL_myexternalfunctionblock__setproptest  myexternalfunctionblock__setproptest
	#define CHK_myexternalfunctionblock__setproptest  TRUE
	#define EXP_myexternalfunctionblock__setproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__setproptest", (RTS_UINTPTR)myexternalfunctionblock__setproptest, 1, 0xBECAA1D8, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__setproptest
	#define EXT_myexternalfunctionblock__setproptest
	#define GET_myexternalfunctionblock__setproptest(fl)  CAL_CMGETAPI( "myexternalfunctionblock__setproptest" ) 
	#define CAL_myexternalfunctionblock__setproptest  myexternalfunctionblock__setproptest
	#define CHK_myexternalfunctionblock__setproptest  TRUE
	#define EXP_myexternalfunctionblock__setproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__setproptest", (RTS_UINTPTR)myexternalfunctionblock__setproptest, 1, 0xBECAA1D8, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__setproptest
	#define EXT_CmpTemplatemyexternalfunctionblock__setproptest
	#define GET_CmpTemplatemyexternalfunctionblock__setproptest  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__setproptest  myexternalfunctionblock__setproptest
	#define CHK_CmpTemplatemyexternalfunctionblock__setproptest  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__setproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__setproptest", (RTS_UINTPTR)myexternalfunctionblock__setproptest, 1, 0xBECAA1D8, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__setproptest
	#define EXT_myexternalfunctionblock__setproptest
	#define GET_myexternalfunctionblock__setproptest(fl)  CAL_CMGETAPI( "myexternalfunctionblock__setproptest" ) 
	#define CAL_myexternalfunctionblock__setproptest  myexternalfunctionblock__setproptest
	#define CHK_myexternalfunctionblock__setproptest  TRUE
	#define EXP_myexternalfunctionblock__setproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__setproptest", (RTS_UINTPTR)myexternalfunctionblock__setproptest, 1, 0xBECAA1D8, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__setproptest  PFMYEXTERNALFUNCTIONBLOCK__SETPROPTEST_IEC pfmyexternalfunctionblock__setproptest;
	#define EXT_myexternalfunctionblock__setproptest  extern PFMYEXTERNALFUNCTIONBLOCK__SETPROPTEST_IEC pfmyexternalfunctionblock__setproptest;
	#define GET_myexternalfunctionblock__setproptest(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__setproptest", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__setproptest, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xBECAA1D8, 0x03050600)
	#define CAL_myexternalfunctionblock__setproptest  pfmyexternalfunctionblock__setproptest
	#define CHK_myexternalfunctionblock__setproptest  (pfmyexternalfunctionblock__setproptest != NULL)
	#define EXP_myexternalfunctionblock__setproptest   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__setproptest", (RTS_UINTPTR)myexternalfunctionblock__setproptest, 1, 0xBECAA1D8, 0x03050600) 
#endif


/**
 * FB exit routine
 */
typedef struct tagmyexternalfunctionblock_fb_exit_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL bInCopyCode;			/* VAR_INPUT */	
	RTS_IEC_BOOL FB_Exit;				/* VAR_OUTPUT */	
} myexternalfunctionblock_fb_exit_struct;

void CDECL CDECL_EXT myexternalfunctionblock__fb_exit(myexternalfunctionblock_fb_exit_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__FB_EXIT_IEC) (myexternalfunctionblock_fb_exit_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__FB_EXIT_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__fb_exit
	#define EXT_myexternalfunctionblock__fb_exit
	#define GET_myexternalfunctionblock__fb_exit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__fb_exit(p0) 
	#define CHK_myexternalfunctionblock__fb_exit  FALSE
	#define EXP_myexternalfunctionblock__fb_exit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__fb_exit
	#define EXT_myexternalfunctionblock__fb_exit
	#define GET_myexternalfunctionblock__fb_exit(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_exit" ) 
	#define CAL_myexternalfunctionblock__fb_exit  myexternalfunctionblock__fb_exit
	#define CHK_myexternalfunctionblock__fb_exit  TRUE
	#define EXP_myexternalfunctionblock__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_exit", (RTS_UINTPTR)myexternalfunctionblock__fb_exit, 1, 0xF3365F57, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__fb_exit
	#define EXT_myexternalfunctionblock__fb_exit
	#define GET_myexternalfunctionblock__fb_exit(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_exit" ) 
	#define CAL_myexternalfunctionblock__fb_exit  myexternalfunctionblock__fb_exit
	#define CHK_myexternalfunctionblock__fb_exit  TRUE
	#define EXP_myexternalfunctionblock__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_exit", (RTS_UINTPTR)myexternalfunctionblock__fb_exit, 1, 0xF3365F57, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__fb_exit
	#define EXT_CmpTemplatemyexternalfunctionblock__fb_exit
	#define GET_CmpTemplatemyexternalfunctionblock__fb_exit  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__fb_exit  myexternalfunctionblock__fb_exit
	#define CHK_CmpTemplatemyexternalfunctionblock__fb_exit  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_exit", (RTS_UINTPTR)myexternalfunctionblock__fb_exit, 1, 0xF3365F57, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__fb_exit
	#define EXT_myexternalfunctionblock__fb_exit
	#define GET_myexternalfunctionblock__fb_exit(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_exit" ) 
	#define CAL_myexternalfunctionblock__fb_exit  myexternalfunctionblock__fb_exit
	#define CHK_myexternalfunctionblock__fb_exit  TRUE
	#define EXP_myexternalfunctionblock__fb_exit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_exit", (RTS_UINTPTR)myexternalfunctionblock__fb_exit, 1, 0xF3365F57, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__fb_exit  PFMYEXTERNALFUNCTIONBLOCK__FB_EXIT_IEC pfmyexternalfunctionblock__fb_exit;
	#define EXT_myexternalfunctionblock__fb_exit  extern PFMYEXTERNALFUNCTIONBLOCK__FB_EXIT_IEC pfmyexternalfunctionblock__fb_exit;
	#define GET_myexternalfunctionblock__fb_exit(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__fb_exit", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__fb_exit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF3365F57, 0x03050600)
	#define CAL_myexternalfunctionblock__fb_exit  pfmyexternalfunctionblock__fb_exit
	#define CHK_myexternalfunctionblock__fb_exit  (pfmyexternalfunctionblock__fb_exit != NULL)
	#define EXP_myexternalfunctionblock__fb_exit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_exit", (RTS_UINTPTR)myexternalfunctionblock__fb_exit, 1, 0xF3365F57, 0x03050600) 
#endif


/**
 * <description>myexternalfunctionblock_getproptest</description>
 */
typedef struct tagmyexternalfunctionblock_getproptest_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD __getPropTest;		/* VAR_OUTPUT */	
} myexternalfunctionblock_getproptest_struct;

void CDECL CDECL_EXT myexternalfunctionblock__getproptest(myexternalfunctionblock_getproptest_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__GETPROPTEST_IEC) (myexternalfunctionblock_getproptest_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__GETPROPTEST_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__getproptest
	#define EXT_myexternalfunctionblock__getproptest
	#define GET_myexternalfunctionblock__getproptest(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__getproptest(p0) 
	#define CHK_myexternalfunctionblock__getproptest  FALSE
	#define EXP_myexternalfunctionblock__getproptest  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__getproptest
	#define EXT_myexternalfunctionblock__getproptest
	#define GET_myexternalfunctionblock__getproptest(fl)  CAL_CMGETAPI( "myexternalfunctionblock__getproptest" ) 
	#define CAL_myexternalfunctionblock__getproptest  myexternalfunctionblock__getproptest
	#define CHK_myexternalfunctionblock__getproptest  TRUE
	#define EXP_myexternalfunctionblock__getproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__getproptest", (RTS_UINTPTR)myexternalfunctionblock__getproptest, 1, 0x885DF09F, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__getproptest
	#define EXT_myexternalfunctionblock__getproptest
	#define GET_myexternalfunctionblock__getproptest(fl)  CAL_CMGETAPI( "myexternalfunctionblock__getproptest" ) 
	#define CAL_myexternalfunctionblock__getproptest  myexternalfunctionblock__getproptest
	#define CHK_myexternalfunctionblock__getproptest  TRUE
	#define EXP_myexternalfunctionblock__getproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__getproptest", (RTS_UINTPTR)myexternalfunctionblock__getproptest, 1, 0x885DF09F, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__getproptest
	#define EXT_CmpTemplatemyexternalfunctionblock__getproptest
	#define GET_CmpTemplatemyexternalfunctionblock__getproptest  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__getproptest  myexternalfunctionblock__getproptest
	#define CHK_CmpTemplatemyexternalfunctionblock__getproptest  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__getproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__getproptest", (RTS_UINTPTR)myexternalfunctionblock__getproptest, 1, 0x885DF09F, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__getproptest
	#define EXT_myexternalfunctionblock__getproptest
	#define GET_myexternalfunctionblock__getproptest(fl)  CAL_CMGETAPI( "myexternalfunctionblock__getproptest" ) 
	#define CAL_myexternalfunctionblock__getproptest  myexternalfunctionblock__getproptest
	#define CHK_myexternalfunctionblock__getproptest  TRUE
	#define EXP_myexternalfunctionblock__getproptest  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__getproptest", (RTS_UINTPTR)myexternalfunctionblock__getproptest, 1, 0x885DF09F, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__getproptest  PFMYEXTERNALFUNCTIONBLOCK__GETPROPTEST_IEC pfmyexternalfunctionblock__getproptest;
	#define EXT_myexternalfunctionblock__getproptest  extern PFMYEXTERNALFUNCTIONBLOCK__GETPROPTEST_IEC pfmyexternalfunctionblock__getproptest;
	#define GET_myexternalfunctionblock__getproptest(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__getproptest", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__getproptest, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x885DF09F, 0x03050600)
	#define CAL_myexternalfunctionblock__getproptest  pfmyexternalfunctionblock__getproptest
	#define CHK_myexternalfunctionblock__getproptest  (pfmyexternalfunctionblock__getproptest != NULL)
	#define EXP_myexternalfunctionblock__getproptest   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__getproptest", (RTS_UINTPTR)myexternalfunctionblock__getproptest, 1, 0x885DF09F, 0x03050600) 
#endif


/**
 * <description>myexternalfunctionblock_mysleep</description>
 */
typedef struct tagmyexternalfunctionblock_mysleep_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD dwSleepMs;			/* VAR_INPUT */	
	RTS_IEC_BOOL MySleep;				/* VAR_OUTPUT */	
} myexternalfunctionblock_mysleep_struct;

void CDECL CDECL_EXT myexternalfunctionblock__mysleep(myexternalfunctionblock_mysleep_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__MYSLEEP_IEC) (myexternalfunctionblock_mysleep_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__MYSLEEP_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__mysleep
	#define EXT_myexternalfunctionblock__mysleep
	#define GET_myexternalfunctionblock__mysleep(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__mysleep(p0) 
	#define CHK_myexternalfunctionblock__mysleep  FALSE
	#define EXP_myexternalfunctionblock__mysleep  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__mysleep
	#define EXT_myexternalfunctionblock__mysleep
	#define GET_myexternalfunctionblock__mysleep(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mysleep" ) 
	#define CAL_myexternalfunctionblock__mysleep  myexternalfunctionblock__mysleep
	#define CHK_myexternalfunctionblock__mysleep  TRUE
	#define EXP_myexternalfunctionblock__mysleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mysleep", (RTS_UINTPTR)myexternalfunctionblock__mysleep, 1, 0xD0F5CB15, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__mysleep
	#define EXT_myexternalfunctionblock__mysleep
	#define GET_myexternalfunctionblock__mysleep(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mysleep" ) 
	#define CAL_myexternalfunctionblock__mysleep  myexternalfunctionblock__mysleep
	#define CHK_myexternalfunctionblock__mysleep  TRUE
	#define EXP_myexternalfunctionblock__mysleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mysleep", (RTS_UINTPTR)myexternalfunctionblock__mysleep, 1, 0xD0F5CB15, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__mysleep
	#define EXT_CmpTemplatemyexternalfunctionblock__mysleep
	#define GET_CmpTemplatemyexternalfunctionblock__mysleep  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__mysleep  myexternalfunctionblock__mysleep
	#define CHK_CmpTemplatemyexternalfunctionblock__mysleep  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__mysleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mysleep", (RTS_UINTPTR)myexternalfunctionblock__mysleep, 1, 0xD0F5CB15, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__mysleep
	#define EXT_myexternalfunctionblock__mysleep
	#define GET_myexternalfunctionblock__mysleep(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mysleep" ) 
	#define CAL_myexternalfunctionblock__mysleep  myexternalfunctionblock__mysleep
	#define CHK_myexternalfunctionblock__mysleep  TRUE
	#define EXP_myexternalfunctionblock__mysleep  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mysleep", (RTS_UINTPTR)myexternalfunctionblock__mysleep, 1, 0xD0F5CB15, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__mysleep  PFMYEXTERNALFUNCTIONBLOCK__MYSLEEP_IEC pfmyexternalfunctionblock__mysleep;
	#define EXT_myexternalfunctionblock__mysleep  extern PFMYEXTERNALFUNCTIONBLOCK__MYSLEEP_IEC pfmyexternalfunctionblock__mysleep;
	#define GET_myexternalfunctionblock__mysleep(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__mysleep", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__mysleep, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD0F5CB15, 0x03050600)
	#define CAL_myexternalfunctionblock__mysleep  pfmyexternalfunctionblock__mysleep
	#define CHK_myexternalfunctionblock__mysleep  (pfmyexternalfunctionblock__mysleep != NULL)
	#define EXP_myexternalfunctionblock__mysleep   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mysleep", (RTS_UINTPTR)myexternalfunctionblock__mysleep, 1, 0xD0F5CB15, 0x03050600) 
#endif


/**
 * FB reinit routine
 */
typedef struct tagmyexternalfunctionblock_fb_reinit_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL FB_Reinit;				/* VAR_OUTPUT */	
} myexternalfunctionblock_fb_reinit_struct;

void CDECL CDECL_EXT myexternalfunctionblock__fb_reinit(myexternalfunctionblock_fb_reinit_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__FB_REINIT_IEC) (myexternalfunctionblock_fb_reinit_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__FB_REINIT_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__fb_reinit
	#define EXT_myexternalfunctionblock__fb_reinit
	#define GET_myexternalfunctionblock__fb_reinit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__fb_reinit(p0) 
	#define CHK_myexternalfunctionblock__fb_reinit  FALSE
	#define EXP_myexternalfunctionblock__fb_reinit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__fb_reinit
	#define EXT_myexternalfunctionblock__fb_reinit
	#define GET_myexternalfunctionblock__fb_reinit(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_reinit" ) 
	#define CAL_myexternalfunctionblock__fb_reinit  myexternalfunctionblock__fb_reinit
	#define CHK_myexternalfunctionblock__fb_reinit  TRUE
	#define EXP_myexternalfunctionblock__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_reinit", (RTS_UINTPTR)myexternalfunctionblock__fb_reinit, 1, 0x4B02BCD4, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__fb_reinit
	#define EXT_myexternalfunctionblock__fb_reinit
	#define GET_myexternalfunctionblock__fb_reinit(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_reinit" ) 
	#define CAL_myexternalfunctionblock__fb_reinit  myexternalfunctionblock__fb_reinit
	#define CHK_myexternalfunctionblock__fb_reinit  TRUE
	#define EXP_myexternalfunctionblock__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_reinit", (RTS_UINTPTR)myexternalfunctionblock__fb_reinit, 1, 0x4B02BCD4, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__fb_reinit
	#define EXT_CmpTemplatemyexternalfunctionblock__fb_reinit
	#define GET_CmpTemplatemyexternalfunctionblock__fb_reinit  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__fb_reinit  myexternalfunctionblock__fb_reinit
	#define CHK_CmpTemplatemyexternalfunctionblock__fb_reinit  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_reinit", (RTS_UINTPTR)myexternalfunctionblock__fb_reinit, 1, 0x4B02BCD4, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__fb_reinit
	#define EXT_myexternalfunctionblock__fb_reinit
	#define GET_myexternalfunctionblock__fb_reinit(fl)  CAL_CMGETAPI( "myexternalfunctionblock__fb_reinit" ) 
	#define CAL_myexternalfunctionblock__fb_reinit  myexternalfunctionblock__fb_reinit
	#define CHK_myexternalfunctionblock__fb_reinit  TRUE
	#define EXP_myexternalfunctionblock__fb_reinit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_reinit", (RTS_UINTPTR)myexternalfunctionblock__fb_reinit, 1, 0x4B02BCD4, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__fb_reinit  PFMYEXTERNALFUNCTIONBLOCK__FB_REINIT_IEC pfmyexternalfunctionblock__fb_reinit;
	#define EXT_myexternalfunctionblock__fb_reinit  extern PFMYEXTERNALFUNCTIONBLOCK__FB_REINIT_IEC pfmyexternalfunctionblock__fb_reinit;
	#define GET_myexternalfunctionblock__fb_reinit(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__fb_reinit", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__fb_reinit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x4B02BCD4, 0x03050600)
	#define CAL_myexternalfunctionblock__fb_reinit  pfmyexternalfunctionblock__fb_reinit
	#define CHK_myexternalfunctionblock__fb_reinit  (pfmyexternalfunctionblock__fb_reinit != NULL)
	#define EXP_myexternalfunctionblock__fb_reinit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__fb_reinit", (RTS_UINTPTR)myexternalfunctionblock__fb_reinit, 1, 0x4B02BCD4, 0x03050600) 
#endif


/**
 * <description>myexternalfunctionblock_mymethod</description>
 */
typedef struct tagmyexternalfunctionblock_mymethod_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD dwIn;					/* VAR_INPUT */	
	RTS_IEC_BOOL MyMethod;				/* VAR_OUTPUT */	
} myexternalfunctionblock_mymethod_struct;

void CDECL CDECL_EXT myexternalfunctionblock__mymethod(myexternalfunctionblock_mymethod_struct *p);
typedef void (CDECL CDECL_EXT* PFMYEXTERNALFUNCTIONBLOCK__MYMETHOD_IEC) (myexternalfunctionblock_mymethod_struct *p);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(MYEXTERNALFUNCTIONBLOCK__MYMETHOD_NOTIMPLEMENTED)
	#define USE_myexternalfunctionblock__mymethod
	#define EXT_myexternalfunctionblock__mymethod
	#define GET_myexternalfunctionblock__mymethod(fl)  ERR_NOTIMPLEMENTED
	#define CAL_myexternalfunctionblock__mymethod(p0) 
	#define CHK_myexternalfunctionblock__mymethod  FALSE
	#define EXP_myexternalfunctionblock__mymethod  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_myexternalfunctionblock__mymethod
	#define EXT_myexternalfunctionblock__mymethod
	#define GET_myexternalfunctionblock__mymethod(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mymethod" ) 
	#define CAL_myexternalfunctionblock__mymethod  myexternalfunctionblock__mymethod
	#define CHK_myexternalfunctionblock__mymethod  TRUE
	#define EXP_myexternalfunctionblock__mymethod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mymethod", (RTS_UINTPTR)myexternalfunctionblock__mymethod, 1, 0xD3C026DC, 0x03050600) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_myexternalfunctionblock__mymethod
	#define EXT_myexternalfunctionblock__mymethod
	#define GET_myexternalfunctionblock__mymethod(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mymethod" ) 
	#define CAL_myexternalfunctionblock__mymethod  myexternalfunctionblock__mymethod
	#define CHK_myexternalfunctionblock__mymethod  TRUE
	#define EXP_myexternalfunctionblock__mymethod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mymethod", (RTS_UINTPTR)myexternalfunctionblock__mymethod, 1, 0xD3C026DC, 0x03050600) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplatemyexternalfunctionblock__mymethod
	#define EXT_CmpTemplatemyexternalfunctionblock__mymethod
	#define GET_CmpTemplatemyexternalfunctionblock__mymethod  ERR_OK
	#define CAL_CmpTemplatemyexternalfunctionblock__mymethod  myexternalfunctionblock__mymethod
	#define CHK_CmpTemplatemyexternalfunctionblock__mymethod  TRUE
	#define EXP_CmpTemplatemyexternalfunctionblock__mymethod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mymethod", (RTS_UINTPTR)myexternalfunctionblock__mymethod, 1, 0xD3C026DC, 0x03050600) 
#elif defined(CPLUSPLUS)
	#define USE_myexternalfunctionblock__mymethod
	#define EXT_myexternalfunctionblock__mymethod
	#define GET_myexternalfunctionblock__mymethod(fl)  CAL_CMGETAPI( "myexternalfunctionblock__mymethod" ) 
	#define CAL_myexternalfunctionblock__mymethod  myexternalfunctionblock__mymethod
	#define CHK_myexternalfunctionblock__mymethod  TRUE
	#define EXP_myexternalfunctionblock__mymethod  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mymethod", (RTS_UINTPTR)myexternalfunctionblock__mymethod, 1, 0xD3C026DC, 0x03050600) 
#else /* DYNAMIC_LINK */
	#define USE_myexternalfunctionblock__mymethod  PFMYEXTERNALFUNCTIONBLOCK__MYMETHOD_IEC pfmyexternalfunctionblock__mymethod;
	#define EXT_myexternalfunctionblock__mymethod  extern PFMYEXTERNALFUNCTIONBLOCK__MYMETHOD_IEC pfmyexternalfunctionblock__mymethod;
	#define GET_myexternalfunctionblock__mymethod(fl)  s_pfCMGetAPI2( "myexternalfunctionblock__mymethod", (RTS_VOID_FCTPTR *)&pfmyexternalfunctionblock__mymethod, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xD3C026DC, 0x03050600)
	#define CAL_myexternalfunctionblock__mymethod  pfmyexternalfunctionblock__mymethod
	#define CHK_myexternalfunctionblock__mymethod  (pfmyexternalfunctionblock__mymethod != NULL)
	#define EXP_myexternalfunctionblock__mymethod   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"myexternalfunctionblock__mymethod", (RTS_UINTPTR)myexternalfunctionblock__mymethod, 1, 0xD3C026DC, 0x03050600) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. It corresponds approximately a C++
 * Constructor
 * </description>
 * <result>ERR_OK</result>
 */
RTS_HANDLE CDECL CmpTemplateOpen(char *pszTemplate, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFCMPTEMPLATEOPEN) (char *pszTemplate, RTS_RESULT *pResult);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(CMPTEMPLATEOPEN_NOTIMPLEMENTED)
	#define USE_CmpTemplateOpen
	#define EXT_CmpTemplateOpen
	#define GET_CmpTemplateOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpTemplateOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_CmpTemplateOpen  FALSE
	#define EXP_CmpTemplateOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpTemplateOpen
	#define EXT_CmpTemplateOpen
	#define GET_CmpTemplateOpen(fl)  CAL_CMGETAPI( "CmpTemplateOpen" ) 
	#define CAL_CmpTemplateOpen  CmpTemplateOpen
	#define CHK_CmpTemplateOpen  TRUE
	#define EXP_CmpTemplateOpen  CAL_CMEXPAPI( "CmpTemplateOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_CmpTemplateOpen
	#define EXT_CmpTemplateOpen
	#define GET_CmpTemplateOpen(fl)  CAL_CMGETAPI( "CmpTemplateOpen" ) 
	#define CAL_CmpTemplateOpen  CmpTemplateOpen
	#define CHK_CmpTemplateOpen  TRUE
	#define EXP_CmpTemplateOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateOpen", (RTS_UINTPTR)CmpTemplateOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplateCmpTemplateOpen
	#define EXT_CmpTemplateCmpTemplateOpen
	#define GET_CmpTemplateCmpTemplateOpen  ERR_OK
	#define CAL_CmpTemplateCmpTemplateOpen  ((ICmpTemplate*)s_pfCMCreateInstance(CLASSID_CCmpTemplate, NULL))->ICmpTemplateOpen
	#define CHK_CmpTemplateCmpTemplateOpen	(s_pfCMCreateInstance != NULL && pICmpTemplate != NULL)
	#define EXP_CmpTemplateCmpTemplateOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpTemplateOpen
	#define EXT_CmpTemplateOpen
	#define GET_CmpTemplateOpen(fl)  CAL_CMGETAPI( "CmpTemplateOpen" ) 
	#define CAL_CmpTemplateOpen  ((ICmpTemplate*)s_pfCMCreateInstance(CLASSID_CCmpTemplate, NULL))->ICmpTemplateOpen
	#define CHK_CmpTemplateOpen	(s_pfCMCreateInstance != NULL && pICmpTemplate != NULL)
	#define EXP_CmpTemplateOpen  CAL_CMEXPAPI( "CmpTemplateOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpTemplateOpen  PFCMPTEMPLATEOPEN pfCmpTemplateOpen;
	#define EXT_CmpTemplateOpen  extern PFCMPTEMPLATEOPEN pfCmpTemplateOpen;
	#define GET_CmpTemplateOpen(fl)  s_pfCMGetAPI2( "CmpTemplateOpen", (RTS_VOID_FCTPTR *)&pfCmpTemplateOpen, (fl), 0, 0)
	#define CAL_CmpTemplateOpen  pfCmpTemplateOpen
	#define CHK_CmpTemplateOpen  (pfCmpTemplateOpen != NULL)
	#define EXP_CmpTemplateOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateOpen", (RTS_UINTPTR)CmpTemplateOpen, 0, 0) 
#endif




/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. It corresponds approximately a C++
 * method. 
 * </description>
 * <result>ERR_OK</result>
 */
char* CDECL CmpTemplateDoAnything(RTS_HANDLE hTemplate);
typedef char* (CDECL * PFCMPTEMPLATEDOANYTHING) (RTS_HANDLE hTemplate);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(CMPTEMPLATEDOANYTHING_NOTIMPLEMENTED)
	#define USE_CmpTemplateDoAnything
	#define EXT_CmpTemplateDoAnything
	#define GET_CmpTemplateDoAnything(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpTemplateDoAnything(p0)  (char*)ERR_NOTIMPLEMENTED
	#define CHK_CmpTemplateDoAnything  FALSE
	#define EXP_CmpTemplateDoAnything  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpTemplateDoAnything
	#define EXT_CmpTemplateDoAnything
	#define GET_CmpTemplateDoAnything(fl)  CAL_CMGETAPI( "CmpTemplateDoAnything" ) 
	#define CAL_CmpTemplateDoAnything  CmpTemplateDoAnything
	#define CHK_CmpTemplateDoAnything  TRUE
	#define EXP_CmpTemplateDoAnything  CAL_CMEXPAPI( "CmpTemplateDoAnything" ) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_CmpTemplateDoAnything
	#define EXT_CmpTemplateDoAnything
	#define GET_CmpTemplateDoAnything(fl)  CAL_CMGETAPI( "CmpTemplateDoAnything" ) 
	#define CAL_CmpTemplateDoAnything  CmpTemplateDoAnything
	#define CHK_CmpTemplateDoAnything  TRUE
	#define EXP_CmpTemplateDoAnything  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateDoAnything", (RTS_UINTPTR)CmpTemplateDoAnything, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplateCmpTemplateDoAnything
	#define EXT_CmpTemplateCmpTemplateDoAnything
	#define GET_CmpTemplateCmpTemplateDoAnything  ERR_OK
	#define CAL_CmpTemplateCmpTemplateDoAnything(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpTemplate->ICmpTemplateDoAnything() : ((ICmpTemplate*)p0)->ICmpTemplateDoAnything())
	#define CHK_CmpTemplateCmpTemplateDoAnything  (pICmpTemplate != NULL)
	#define EXP_CmpTemplateCmpTemplateDoAnything  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpTemplateDoAnything
	#define EXT_CmpTemplateDoAnything
	#define GET_CmpTemplateDoAnything(fl)  CAL_CMGETAPI( "CmpTemplateDoAnything" ) 
	#define CAL_CmpTemplateDoAnything(p0)		(p0 == RTS_INVALID_HANDLE || p0 == NULL ? pICmpTemplate->ICmpTemplateDoAnything() : ((ICmpTemplate*)p0)->ICmpTemplateDoAnything())
	#define CHK_CmpTemplateDoAnything  (pICmpTemplate != NULL)
	#define EXP_CmpTemplateDoAnything  CAL_CMEXPAPI( "CmpTemplateDoAnything" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpTemplateDoAnything  PFCMPTEMPLATEDOANYTHING pfCmpTemplateDoAnything;
	#define EXT_CmpTemplateDoAnything  extern PFCMPTEMPLATEDOANYTHING pfCmpTemplateDoAnything;
	#define GET_CmpTemplateDoAnything(fl)  s_pfCMGetAPI2( "CmpTemplateDoAnything", (RTS_VOID_FCTPTR *)&pfCmpTemplateDoAnything, (fl), 0, 0)
	#define CAL_CmpTemplateDoAnything  pfCmpTemplateDoAnything
	#define CHK_CmpTemplateDoAnything  (pfCmpTemplateDoAnything != NULL)
	#define EXP_CmpTemplateDoAnything  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateDoAnything", (RTS_UINTPTR)CmpTemplateDoAnything, 0, 0) 
#endif




/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. It corresponds approximately a C++
 * static function. 
 * </description>
 * <result>ERR_OK</result>
 */
RTS_RESULT CDECL CmpTemplateDoAnythingTheSecond(char *pszTemplate);
typedef RTS_RESULT (CDECL * PFCMPTEMPLATEDOANYTHINGTHESECOND) (char *pszTemplate);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(CMPTEMPLATEDOANYTHINGTHESECOND_NOTIMPLEMENTED)
	#define USE_CmpTemplateDoAnythingTheSecond
	#define EXT_CmpTemplateDoAnythingTheSecond
	#define GET_CmpTemplateDoAnythingTheSecond(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpTemplateDoAnythingTheSecond(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_CmpTemplateDoAnythingTheSecond  FALSE
	#define EXP_CmpTemplateDoAnythingTheSecond  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpTemplateDoAnythingTheSecond
	#define EXT_CmpTemplateDoAnythingTheSecond
	#define GET_CmpTemplateDoAnythingTheSecond(fl)  CAL_CMGETAPI( "CmpTemplateDoAnythingTheSecond" ) 
	#define CAL_CmpTemplateDoAnythingTheSecond  CmpTemplateDoAnythingTheSecond
	#define CHK_CmpTemplateDoAnythingTheSecond  TRUE
	#define EXP_CmpTemplateDoAnythingTheSecond  CAL_CMEXPAPI( "CmpTemplateDoAnythingTheSecond" ) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_CmpTemplateDoAnythingTheSecond
	#define EXT_CmpTemplateDoAnythingTheSecond
	#define GET_CmpTemplateDoAnythingTheSecond(fl)  CAL_CMGETAPI( "CmpTemplateDoAnythingTheSecond" ) 
	#define CAL_CmpTemplateDoAnythingTheSecond  CmpTemplateDoAnythingTheSecond
	#define CHK_CmpTemplateDoAnythingTheSecond  TRUE
	#define EXP_CmpTemplateDoAnythingTheSecond  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateDoAnythingTheSecond", (RTS_UINTPTR)CmpTemplateDoAnythingTheSecond, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplateCmpTemplateDoAnythingTheSecond
	#define EXT_CmpTemplateCmpTemplateDoAnythingTheSecond
	#define GET_CmpTemplateCmpTemplateDoAnythingTheSecond  ERR_OK
	#define CAL_CmpTemplateCmpTemplateDoAnythingTheSecond CCmpTemplate::ICmpTemplateDoAnythingTheSecond
	#define CHK_CmpTemplateCmpTemplateDoAnythingTheSecond  TRUE
	#define EXP_CmpTemplateCmpTemplateDoAnythingTheSecond  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpTemplateDoAnythingTheSecond
	#define EXT_CmpTemplateDoAnythingTheSecond
	#define GET_CmpTemplateDoAnythingTheSecond(fl)  CAL_CMGETAPI( "CmpTemplateDoAnythingTheSecond" ) 
	#define CAL_CmpTemplateDoAnythingTheSecond CCmpTemplate::ICmpTemplateDoAnythingTheSecond
	#define CHK_CmpTemplateDoAnythingTheSecond  TRUE
	#define EXP_CmpTemplateDoAnythingTheSecond  CAL_CMEXPAPI( "CmpTemplateDoAnythingTheSecond" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpTemplateDoAnythingTheSecond  PFCMPTEMPLATEDOANYTHINGTHESECOND pfCmpTemplateDoAnythingTheSecond;
	#define EXT_CmpTemplateDoAnythingTheSecond  extern PFCMPTEMPLATEDOANYTHINGTHESECOND pfCmpTemplateDoAnythingTheSecond;
	#define GET_CmpTemplateDoAnythingTheSecond(fl)  s_pfCMGetAPI2( "CmpTemplateDoAnythingTheSecond", (RTS_VOID_FCTPTR *)&pfCmpTemplateDoAnythingTheSecond, (fl), 0, 0)
	#define CAL_CmpTemplateDoAnythingTheSecond  pfCmpTemplateDoAnythingTheSecond
	#define CHK_CmpTemplateDoAnythingTheSecond  (pfCmpTemplateDoAnythingTheSecond != NULL)
	#define EXP_CmpTemplateDoAnythingTheSecond  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateDoAnythingTheSecond", (RTS_UINTPTR)CmpTemplateDoAnythingTheSecond, 0, 0) 
#endif




/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. This is only for Components, which have
 * exactly one instance of itself in the whole runtime.
 * </description>
 * <result>ERR_OK</result>
 */
void* CDECL CmpTemplateSingleton(char *pszTemplate);
typedef void* (CDECL * PFCMPTEMPLATESINGLETON) (char *pszTemplate);
#if defined(CMPTEMPLATE_NOTIMPLEMENTED) || defined(CMPTEMPLATESINGLETON_NOTIMPLEMENTED)
	#define USE_CmpTemplateSingleton
	#define EXT_CmpTemplateSingleton
	#define GET_CmpTemplateSingleton(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpTemplateSingleton(p0)  (void*)ERR_NOTIMPLEMENTED
	#define CHK_CmpTemplateSingleton  FALSE
	#define EXP_CmpTemplateSingleton  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpTemplateSingleton
	#define EXT_CmpTemplateSingleton
	#define GET_CmpTemplateSingleton(fl)  CAL_CMGETAPI( "CmpTemplateSingleton" ) 
	#define CAL_CmpTemplateSingleton  CmpTemplateSingleton
	#define CHK_CmpTemplateSingleton  TRUE
	#define EXP_CmpTemplateSingleton  CAL_CMEXPAPI( "CmpTemplateSingleton" ) 
#elif defined(MIXED_LINK) && !defined(CMPTEMPLATE_EXTERNAL)
	#define USE_CmpTemplateSingleton
	#define EXT_CmpTemplateSingleton
	#define GET_CmpTemplateSingleton(fl)  CAL_CMGETAPI( "CmpTemplateSingleton" ) 
	#define CAL_CmpTemplateSingleton  CmpTemplateSingleton
	#define CHK_CmpTemplateSingleton  TRUE
	#define EXP_CmpTemplateSingleton  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateSingleton", (RTS_UINTPTR)CmpTemplateSingleton, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpTemplateCmpTemplateSingleton
	#define EXT_CmpTemplateCmpTemplateSingleton
	#define GET_CmpTemplateCmpTemplateSingleton  ERR_OK
	#define CAL_CmpTemplateCmpTemplateSingleton pICmpTemplate->ICmpTemplateSingleton
	#define CHK_CmpTemplateCmpTemplateSingleton (pICmpTemplate != NULL)
	#define EXP_CmpTemplateCmpTemplateSingleton  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpTemplateSingleton
	#define EXT_CmpTemplateSingleton
	#define GET_CmpTemplateSingleton(fl)  CAL_CMGETAPI( "CmpTemplateSingleton" ) 
	#define CAL_CmpTemplateSingleton pICmpTemplate->ICmpTemplateSingleton
	#define CHK_CmpTemplateSingleton (pICmpTemplate != NULL)
	#define EXP_CmpTemplateSingleton  CAL_CMEXPAPI( "CmpTemplateSingleton" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpTemplateSingleton  PFCMPTEMPLATESINGLETON pfCmpTemplateSingleton;
	#define EXT_CmpTemplateSingleton  extern PFCMPTEMPLATESINGLETON pfCmpTemplateSingleton;
	#define GET_CmpTemplateSingleton(fl)  s_pfCMGetAPI2( "CmpTemplateSingleton", (RTS_VOID_FCTPTR *)&pfCmpTemplateSingleton, (fl), 0, 0)
	#define CAL_CmpTemplateSingleton  pfCmpTemplateSingleton
	#define CHK_CmpTemplateSingleton  (pfCmpTemplateSingleton != NULL)
	#define EXP_CmpTemplateSingleton  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpTemplateSingleton", (RTS_UINTPTR)CmpTemplateSingleton, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCMPTEMPLATEOPEN ICmpTemplateOpen;
 	PFCMPTEMPLATEDOANYTHING ICmpTemplateDoAnything;
 	PFCMPTEMPLATEDOANYTHINGTHESECOND ICmpTemplateDoAnythingTheSecond;
 	PFCMPTEMPLATESINGLETON ICmpTemplateSingleton;
 } ICmpTemplate_C;

#ifdef CPLUSPLUS
class ICmpTemplate : public IBase
{
	public:
		virtual RTS_HANDLE CDECL ICmpTemplateOpen(char *pszTemplate, RTS_RESULT *pResult) =0;
		virtual char* CDECL ICmpTemplateDoAnything(void) =0;
		static RTS_RESULT CDECL ICmpTemplateDoAnythingTheSecond(char *pszTemplate);
		virtual void* CDECL ICmpTemplateSingleton(char *pszTemplate) =0;
};
	#ifndef ITF_CmpTemplate
		#define ITF_CmpTemplate static ICmpTemplate *pICmpTemplate = NULL;
	#endif
	#define EXTITF_CmpTemplate
#else	/*CPLUSPLUS*/
	typedef ICmpTemplate_C		ICmpTemplate;
	#ifndef ITF_CmpTemplate
		#define ITF_CmpTemplate
	#endif
	#define EXTITF_CmpTemplate
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTEMPLATEITF_H_*/
