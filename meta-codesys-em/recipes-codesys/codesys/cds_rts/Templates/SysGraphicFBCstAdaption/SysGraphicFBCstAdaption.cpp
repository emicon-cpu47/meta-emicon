/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "SysGraphicFBCstAdaption.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_SysGraphicFBCstAdaption		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CSysGraphicFBCstAdaption	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpSysGraphicFBCstAdaption		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





RTS_RESULT CDECL CSysGraphicFBCstAdaption::ISysGraphicFBCstAdaptionGetGlobalParameters(SysGraphicGlobalParameters* pParameters)
{
	return SysGraphicFBCstAdaptionGetGlobalParameters(pParameters);
}

RTS_RESULT CDECL CSysGraphicFBCstAdaption::ISysGraphicFBCstAdaptionBufferWasUpdated(char* pcFBAddress)
{
	return SysGraphicFBCstAdaptionBufferWasUpdated(pcFBAddress);
}

char* CDECL CSysGraphicFBCstAdaption::ISysGraphicFBCstAdaptionGetFBAddress(char* pcFBAddress)
{
	return SysGraphicFBCstAdaptionGetFBAddress(pcFBAddress);
}

RTS_RESULT CDECL CSysGraphicFBCstAdaption::ISysGraphicFBCstAdaptionGetTouchPosition(int* iX, int* iY, int* bPressed)
{
	return SysGraphicFBCstAdaptionGetTouchPosition(iX,iY,bPressed);
}







