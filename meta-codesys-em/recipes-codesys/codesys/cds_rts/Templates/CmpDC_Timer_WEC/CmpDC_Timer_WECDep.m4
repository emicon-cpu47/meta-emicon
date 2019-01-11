/**
 *  <name>Component CmpDC_Timer_WEC</name>
 *  <description> 
 *  Simulation of (microsecond) hardware timer event handling on WinCE
 *  We call an external event triggered task with interval from the comm cycle hook. 
 *  In a real EtherCAT soft motion controller, the OEM has to implement a kernel 
 *  driver for his specific timer which sets a (Windows CE) event. 
 *  This template here then must catch this event and call PostExternalEvent, 
 *  and this leads to one cycle of the EtherCAT master task. 
 *  </description>
 *  <copyright>
 *  (c) 2003-2018 CODESYS GmbH
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpDC_Timer_WEC')
COMPONENT_SOURCES(`CmpDC_Timer_WEC.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0000')
#define CMPID_CmpDC_Timer_WEC		0x2227
#define CLASSID_CCmpDC_Timer_WEC	0x2227
#define ITFID_ICmpDC_Timer_WEC		0x2227


CATEGORY(`Templates')

IMPLEMENT_ITF(`CmpDC_Timer_WECItf.m4',`CmpEventCallbackItf.m4')

USE_ITF(`SysMemItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`SysTimeItf.m4')
USE_ITF(`CmpScheduleItf.m4')


REQUIRED_IMPORTS(
SysMemAllocData,
SysMemFreeData,
SettgSetStringValue,
SettgGetStringValue,
SettgSetIntValue,
SettgGetIntValue,
EventOpen,
EventClose,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction,
EventPost,
SchedPostExternalEvent,
SchedRegisterExternalEvent,
SchedUnregisterExternalEvent)

OPTIONAL_IMPORTS(
SysMemIsValidPointer)
