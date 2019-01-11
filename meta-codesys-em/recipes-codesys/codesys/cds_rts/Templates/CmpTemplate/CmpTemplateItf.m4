SET_INTERFACE_NAME(`CmpTemplate')

#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#define CH_USER_1						10000
/*	First user hook
	ulParam1: Not used
	ulParam2: Not used
*/

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`myexternalfunction',`(myexternalfunction_struct *p)',1,0x184DFC0B,0x03050600)

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

DEF_API(`void',`CDECL',`myexternalfunctionblock__main',`(myexternalfunctionblock_main_struct *p)',1,0x39AB6C8B,0x03050600)

/**
 * <description>myexternalfunctionblock_mygenerateexception</description>
 */
typedef struct tagmyexternalfunctionblock_mygenerateexception_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD dwException;			/* VAR_INPUT */	
	RTS_IEC_BOOL MyGenerateException;	/* VAR_OUTPUT */	
} myexternalfunctionblock_mygenerateexception_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__mygenerateexception',`(myexternalfunctionblock_mygenerateexception_struct *p)',1,0x6B216090,0x03050600)

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

DEF_API(`void',`CDECL',`myexternalfunctionblock__fb_init',`(myexternalfunctionblock_fb_init_struct *p)',1,0x537E01E5,0x03050600)

/**
 * <description>myexternalfunctionblock_setproptest</description>
 */
typedef struct tagmyexternalfunctionblock_setproptest_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD PropTest;				/* VAR_INPUT */	
	RTS_IEC_BOOL __setPropTest;			/* VAR_OUTPUT */	
} myexternalfunctionblock_setproptest_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__setproptest',`(myexternalfunctionblock_setproptest_struct *p)',1,0xBECAA1D8,0x03050600)

/**
 * FB exit routine
 */
typedef struct tagmyexternalfunctionblock_fb_exit_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL bInCopyCode;			/* VAR_INPUT */	
	RTS_IEC_BOOL FB_Exit;				/* VAR_OUTPUT */	
} myexternalfunctionblock_fb_exit_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__fb_exit',`(myexternalfunctionblock_fb_exit_struct *p)',1,0xF3365F57,0x03050600)

/**
 * <description>myexternalfunctionblock_getproptest</description>
 */
typedef struct tagmyexternalfunctionblock_getproptest_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD __getPropTest;		/* VAR_OUTPUT */	
} myexternalfunctionblock_getproptest_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__getproptest',`(myexternalfunctionblock_getproptest_struct *p)',1,0x885DF09F,0x03050600)

/**
 * <description>myexternalfunctionblock_mysleep</description>
 */
typedef struct tagmyexternalfunctionblock_mysleep_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD dwSleepMs;			/* VAR_INPUT */	
	RTS_IEC_BOOL MySleep;				/* VAR_OUTPUT */	
} myexternalfunctionblock_mysleep_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__mysleep',`(myexternalfunctionblock_mysleep_struct *p)',1,0xD0F5CB15,0x03050600)

/**
 * FB reinit routine
 */
typedef struct tagmyexternalfunctionblock_fb_reinit_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_BOOL FB_Reinit;				/* VAR_OUTPUT */	
} myexternalfunctionblock_fb_reinit_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__fb_reinit',`(myexternalfunctionblock_fb_reinit_struct *p)',1,0x4B02BCD4,0x03050600)

/**
 * <description>myexternalfunctionblock_mymethod</description>
 */
typedef struct tagmyexternalfunctionblock_mymethod_struct
{
	myexternalfunctionblock_struct *pInstance;	/* VAR_INPUT */	
	RTS_IEC_DWORD dwIn;					/* VAR_INPUT */	
	RTS_IEC_BOOL MyMethod;				/* VAR_OUTPUT */	
} myexternalfunctionblock_mymethod_struct;

DEF_API(`void',`CDECL',`myexternalfunctionblock__mymethod',`(myexternalfunctionblock_mymethod_struct *p)',1,0xD3C026DC,0x03050600)

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
DEF_CREATEITF_API(`RTS_HANDLE',`CDECL',`CmpTemplateOpen',`(char *pszTemplate, RTS_RESULT *pResult)')

/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. It corresponds approximately a C++
 * method. 
 * </description>
 * <result>ERR_OK</result>
 */
DEF_HANDLEITF_API(`char*',`CDECL',`CmpTemplateDoAnything',`(RTS_HANDLE hTemplate)')

/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. It corresponds approximately a C++
 * static function. 
 * </description>
 * <result>ERR_OK</result>
 */
DEF_STATICITF_API(`RTS_RESULT',`CDECL',`CmpTemplateDoAnythingTheSecond',`(char *pszTemplate)')

/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. This is only for Components, which have
 * exactly one instance of itself in the whole runtime.
 * </description>
 * <result>ERR_OK</result>
 */
DEF_ITF_API(`void*',`CDECL',`CmpTemplateSingleton',`(char *pszTemplate)')

#ifdef __cplusplus
}
#endif
