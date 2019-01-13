/**
 *  <name>Loopback Can Mini Driver</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpLoopbackCanDrv')
COMPONENT_SOURCES(`CmpLoopbackCanDrv.c')
#define CMPID_CmpLoopbackCanDrv 0x2000


COMPONENT_VERSION(`0x03050A00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

#include "CmpStd.h"
#include "CmpItf.h"

IMPLEMENT_ITF(`CmpLoopbackCanDrvItf.m4')

USE_ITF(`CmpCAACanL2Itf.m4')
USE_ITF(`SysTaskItf.m4')

/**
 * <category>Task</category>
 * <description>
 *	CAN communication task.
 * </description>
 */
TASK(`PCANCommThread', `TASKPRIO_HIGH_END')

OPTIONAL_IMPORTS(
SysTaskCreate,
SysTaskResume,
SysTaskExit,
SysTaskEnd,
SysTaskJoin,
SysTaskGetCurrent,
SysTaskDestroy,
SysTaskGetInfo,
SysTaskLeave,
SysTaskEnter,
SysTaskSetExit,
SysTaskWaitSleep,
SysTaskGetName)

REQUIRED_IMPORTS(
CL2_CmdRegister,
CL2_CmdUnRegister,
CL2_MsgAlloc,
CL2_MsgFree,
CL2_MsgSendAcknNoIRQ,
CL2_MsgPutRQueue,
CL2_MsgGetData)
