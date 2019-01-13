/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpEmiconEmu.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpEmiconEmu		0x2007								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconEmu	ADDVENDORID(CMP_VENDORID, 0x2007)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconEmu		ADDVENDORID(CMP_VENDORID, 0x2007)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */






bool CDECL CCmpEmiconEmu::ICmpEmiconEmu_is_emu(void)
{
	return CmpEmiconEmu_is_emu();
}






