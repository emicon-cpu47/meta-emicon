/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpQtControl.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpQtControl		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpQtControl	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpQtControl		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





void CDECL CCmpQtControl::IEventCallback(EventParam *pEventParam)
{
	EventCallback(hCmpQtControl,pEventParam);
}







