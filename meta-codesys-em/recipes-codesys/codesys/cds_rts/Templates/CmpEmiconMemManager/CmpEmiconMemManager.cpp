/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpEmiconMemManager.c"




/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */

#define CMPID_CmpEmiconMemManager		0x2001								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconMemManager	ADDVENDORID(CMP_VENDORID, 0x2001)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconMemManager		ADDVENDORID(CMP_VENDORID, 0x2001)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */





uint32_t CDECL CCmpEmiconMemManager::ICmpEmiconMemManager_get_cs3_allocated_mem_size(void)
{
	return CmpEmiconMemManager_get_cs3_allocated_mem_size();
}

int16_t CDECL CCmpEmiconMemManager::ICmpEmiconMemManager_mem_to_file(long int l_byte, long int b_byte)
{
	return CmpEmiconMemManager_mem_to_file(l_byte,b_byte);
}

int16_t CDECL CCmpEmiconMemManager::ICmpEmiconMemManager_file_to_mem(void)
{
	return CmpEmiconMemManager_file_to_mem();
}





void CDECL CCmpEmiconMemManager::IEventCallback(EventParam *pEventParam)
{
	EventCallback(hCmpEmiconMemManager,pEventParam);
}







