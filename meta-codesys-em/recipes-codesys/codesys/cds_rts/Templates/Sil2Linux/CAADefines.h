/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		SysDefines.h
*	Version:		2.4
*	Purpose:		Parameter to system specific features.
*
******************************************************************************/
#ifndef __CAADEFINES_H__                                   
#define __CAADEFINES_H__                                   

#define CL2_NNET	1	/* Max. Number of physical CANbus Networks */

#define CAA_MSR_SAVE
#define CAA_CRITSEC					RTS_UI32 _sema;
#define CAA_ENTER_CRITSEC(h)		CAL_SysIntDisableAll((RTS_UI32 *)&h)
#define CAA_EXIT_CRITSEC(h)			CAL_SysIntEnableAll((RTS_UI32 *)&h)

#define CAA_LOCK 					RTS_HANDLE _rts_lock;
#define CAA_CREATE_LOCK()			(RTS_HANDLE)RTS_INVALID_HANDLE
#define CAA_ENTER_LOCK(h)			CAL_SysIntDisableAll((RTS_UI32 *)&h)
#define CAA_LEAVE_LOCK(h)			CAL_SysIntEnableAll((RTS_UI32 *)&h)
#define CAA_DELETE_LOCK(h)

#define CAA_FREE(pBlock, szSize)	CAL_SysMemFreeData(COMPONENT_NAME, ((void*)(pBlock)))

/*Generic CAA defines. Change the defines, before CAADefinesGeneric.h is included.*/
#include "CAADefinesGeneric.h"

#endif /* __CAADEFINES_H__ */
