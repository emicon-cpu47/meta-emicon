/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpJitter.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpJitter		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpJitter	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpJitter		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





void CDECL CCmpJitter::IEventCallback(EventParam *pEventParam)
{
	EventCallback(hCmpJitter,pEventParam);
}







