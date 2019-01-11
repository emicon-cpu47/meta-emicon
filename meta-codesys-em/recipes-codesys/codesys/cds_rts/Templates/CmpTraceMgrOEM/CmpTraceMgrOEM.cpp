/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpTraceMgrOEM.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpTraceMgrOEM		0x200A								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpTraceMgrOEM	ADDVENDORID(CMP_VENDORID, 0x200A)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpTraceMgrOEM		ADDVENDORID(CMP_VENDORID, 0x200A)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */









void CDECL CCmpTraceMgrOEM::IEventCallback(EventParam *pEventParam)
{
	EventCallback(hCmpTraceMgrOEM,pEventParam);
}








