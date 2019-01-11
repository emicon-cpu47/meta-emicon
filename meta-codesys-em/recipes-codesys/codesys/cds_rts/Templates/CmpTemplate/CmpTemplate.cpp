/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpTemplate.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpTemplate		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpTemplate	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpTemplate		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */















RTS_HANDLE CDECL CCmpTemplate::ICmpTemplateOpen(char *pszTemplate, RTS_RESULT *pResult)
{
	hCmpTemplate = CmpTemplateOpen(pszTemplate,pResult);
	if (hCmpTemplate == RTS_INVALID_HANDLE)
	{
		DeleteInstance((IBase *)(ICmpTemplate *)this);
		return RTS_INVALID_HANDLE;
	}
	return (RTS_HANDLE)this;
}

char* CDECL CCmpTemplate::ICmpTemplateDoAnything(void)
{
	return CmpTemplateDoAnything(hCmpTemplate);
}

RTS_RESULT CDECL CCmpTemplate::ICmpTemplateDoAnythingTheSecond(char *pszTemplate)
{
	return CmpTemplateDoAnythingTheSecond(pszTemplate);
}

void* CDECL CCmpTemplate::ICmpTemplateSingleton(char *pszTemplate)
{
	return CmpTemplateSingleton(pszTemplate);
}





void CDECL CCmpTemplate::IEventCallback(EventParam *pEventParam)
{
	EventCallback(hCmpTemplate,pEventParam);
}







