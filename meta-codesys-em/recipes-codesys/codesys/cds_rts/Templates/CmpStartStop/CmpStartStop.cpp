/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpStartStop.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpStartStop		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpStartStop	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpStartStop		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





void CDECL CCmpStartStop::IEventCallback(EventParam *pEventParam)
{
	EventCallback(hCmpStartStop,pEventParam);
}







