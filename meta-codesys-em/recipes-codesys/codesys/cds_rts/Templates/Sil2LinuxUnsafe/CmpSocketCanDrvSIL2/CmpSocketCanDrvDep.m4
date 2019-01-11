/**
 *  <name>Component Socket Can Mini Driver</name>
 *  <description> 
 *  </description>
 *  <copyright>
 *  (c) 2008-2018 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpSocketCanDrv')
COMPONENT_SOURCES(`CmpSocketCanDrv.c', `SocketCanDrv.c')

COMPONENT_VERSION(`0x03050D00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

CATEGORY(`Application.IO.IoDriver.CAN.Socket')

#include "CmpItf.h"

#include "CAATypes.h"
#include "CAACanMiniDriver.h"
#include "SocketCanDrv.h"

IMPLEMENT_ITF(`CmpSocketCanDrvItf.m4')

USE_ITF(`CmpLogItf.m4')
USE_ITF(`CmpCAACanL2Itf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`SysTaskItf.m4')
USE_ITF(`SysTimeItf.m4')
USE_ITF(`CMUtilsItf.m4')


/**
 * <category>Task</category>
 * <description>
 *	Socket CAN receive task.
 * </description>
 */
TASK(`SocketRXThread', `65')

/**
 * <category>Task</category>
 * <description>
 *	Socket CAN transmit task.
 * </description>
 */
TASK(`SocketTXThread', `TASKPRIO_SYSTEM_END')


REQUIRED_IMPORTS(
LogAdd,
SettgGetIntValue,
SettgGetStringValue,
CL2_CmdRegister,
CL2_CmdUnRegister,
CL2_MsgAlloc,
CL2_MsgFree,
CL2_MsgSendAckn,
CL2_MsgPutRQueue,
CL2_MsgGetData,
SysTaskCreate,
SysTaskResume,
SysTaskExit,
SysTaskEnd,
SysTaskLeave,
SysTaskEnter,
SysTaskSetExit,
SysTimeGetMs,
SysTimeGetUs,
CMUtlSafeStrCpy,
CMUtlsnprintf)

