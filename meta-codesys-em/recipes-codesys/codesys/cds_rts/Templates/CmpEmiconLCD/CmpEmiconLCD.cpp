/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpEmiconLCD.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpEmiconLCD		0x2004								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconLCD	ADDVENDORID(CMP_VENDORID, 0x2004)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconLCD		ADDVENDORID(CMP_VENDORID, 0x2004)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */













uint32_t CDECL CCmpEmiconLCD::ICmpEmiconLCD_puts(uint8_t n, uint8_t line, uint8_t pos, char *str)
{
	return CmpEmiconLCD_puts(n,line,pos,str);
}

uint32_t CDECL CCmpEmiconLCD::ICmpEmiconLCD_display_screen(uint8_t n)
{
	return CmpEmiconLCD_display_screen(n);
}






