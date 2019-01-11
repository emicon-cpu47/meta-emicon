/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/








#include "CmpLoopbackCanDrv.c"


#define CMPID_CmpLoopbackCanDrv 0x2000



#include "CmpStd.h"
#include "CmpItf.h"




int CDECL CCmpLoopbackCanDrv::ILoopback_CanMiniDriver_Setup(void)
{
	return Loopback_CanMiniDriver_Setup();
}

int CDECL CCmpLoopbackCanDrv::ILoopback_CanMiniDriver_Dispose(void)
{
	return Loopback_CanMiniDriver_Dispose();
}

void CDECL CCmpLoopbackCanDrv::ILoopback_CanMiniDriver_Handler(void)
{
	Loopback_CanMiniDriver_Handler();
}






/**
 * <category>Task</category>
 * <description>
 *	CAN communication task.
 * </description>
 */


