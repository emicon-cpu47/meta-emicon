/**
 * <name>RtsExternalLibs.c</name>
 * <description> 
 *	Template component to show some example external IEC libs. See CmpTemplate.library for the declaration.
 *
 *	- The function must be exported from the IEC library in CmpTemplateItf.m4 and the C-Stubs. These Stubs can be integrated here.
 *	  The m4 file must be compile to CmpTemplateItf.h and the corresponding CmpTemplateDep.m4 must be compiled to CmpTemplateDep.h.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"

/* Example for a external library functions function */

void CDECL myexternalfunction(myexternalfunction_struct *p)
{
	p->MyExternalFunction = p->p1 + 1;
}

void CDECL myexternalfunctionblock__fb_init(myexternalfunctionblock_fb_init_struct *p)
{
	memset(p->pInstance, 0, sizeof(myexternalfunctionblock_struct));
	p->pInstance->_internalVar = 111;
	p->FB_Init = 1;
}

void CDECL myexternalfunctionblock__fb_reinit(myexternalfunctionblock_fb_reinit_struct *p)
{
	p->FB_Reinit = 1;
}

void CDECL myexternalfunctionblock__fb_exit(myexternalfunctionblock_fb_exit_struct *p)
{
	p->pInstance->_internalVar = 222;
	p->FB_Exit = 1;
}

void CDECL myexternalfunctionblock__main(myexternalfunctionblock_main_struct *p)
{	if (p->pInstance->bShow)
	{
		if (p->pInstance->bError)
		{
#ifndef STD_CALL
#ifndef WIN32
			printf("* Error *:");
			printf(p->pInstance->MessageText);
#else
			MessageBox(NULL, p->pInstance->MessageText, "CmpTemplate", MB_ICONERROR | MB_OK);
#endif
#endif
		}
		else
		{
#ifndef STD_CALL
#ifndef WIN32
			printf("  Info  :");
			printf(p->pInstance->MessageText);
#else
			MessageBox(NULL, p->pInstance->MessageText, "CmpTemplate", MB_ICONINFORMATION | MB_OK);
#endif
#endif
		}
		p->pInstance->bShow = 0;
	}
}

void CDECL CDECL_EXT myexternalfunctionblock__getproptest(myexternalfunctionblock_getproptest_struct *p)
{
	p->__getPropTest = p->pInstance->_property;
}

void CDECL CDECL_EXT myexternalfunctionblock__setproptest(myexternalfunctionblock_setproptest_struct *p)
{
	p->pInstance->_property = p->PropTest;
	p->__setPropTest = 1;
}

void CDECL CDECL_EXT myexternalfunctionblock__mymethod(myexternalfunctionblock_mymethod_struct *p)
{
	p->MyMethod = TRUE;
}

void CDECL CDECL_EXT myexternalfunctionblock__mysleep(myexternalfunctionblock_mysleep_struct *p)
{
	if (CHK_SysTaskWaitSleep)
	{
		CAL_SysTaskWaitSleep(RTS_INVALID_HANDLE, p->dwSleepMs);
		p->MySleep = TRUE;
		return;
	}
	p->MySleep = FALSE;
}

void CDECL CDECL_EXT myexternalfunctionblock__mygenerateexception(myexternalfunctionblock_mygenerateexception_struct *p)
{
	RTS_UI32 b = 10, a = 0;
	a = b / a;
	p->MyGenerateException = FALSE;
}


/* Examples to show the different types of functions 
-> See also CmpTemplateItf.m4 */ 

RTS_HANDLE CDECL CmpTemplateOpen(char *pszTemplate, RTS_RESULT *pResult)
{
	/*Do anything*/
	RTS_SETRESULT(pResult, ERR_FAILED);
	return RTS_INVALID_HANDLE;
}

char* CDECL CmpTemplateDoAnything(RTS_HANDLE hTemplate)
{
	if (hTemplate == RTS_INVALID_HANDLE)
		return 0;

	/*Do anything*/

	return 0;
}

RTS_RESULT CDECL CmpTemplateDoAnythingTheSecond(char *pszTemplate)
{
	if (pszTemplate == 0)
		return 0;

	/*Do anything*/

	return 1;
}

void* CDECL CmpTemplateSingleton(char *pszTemplate)
{
	if (pszTemplate == 0)
		return 0;

	/*Do anything*/

	return 0;
}
