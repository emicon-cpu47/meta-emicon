/**
 *  <name>Component CEDistributedClocks</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpCEDistributedClocks')
COMPONENT_SOURCES(`CmpCEDistributedClocks.c')

COMPONENT_VERSION(`0x03050A00')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0000')
#define CMPID_CmpCEDistributedClocks		0x2222		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpCEDistributedClocks		0x2222		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpCEDistributedClocks		0x2222		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */


CATEGORY(`Templates')

IMPLEMENT_ITF(`CmpCEDistributedClocksItf.m4',`CmpEventCallbackItf.m4')

USE_ITF(`CmpSrvItf.m4')
USE_ITF(`CmpBinTagUtilItf.m4')
USE_ITF(`SysTaskItf.m4')
USE_ITF(`SysMemItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`SysTimeItf.m4')
USE_ITF(`SysEventItf.m4')
USE_ITF(`CmpScheduleItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')
USE_ITF(`CmpIecTaskItf.m4')

REQUIRED_IMPORTS(
SysMemAllocData,
SysMemFreeData,
SysMemAllocArea,
SysMemFreeArea,
SettgSetStringValue,
SettgGetStringValue,
SettgSetIntValue,
SettgGetIntValue,
AppGetApplicationByIndex,
AppGetAreaPointerByType,
EventCreate,
EventCreate2,
EventDelete,
EventOpen,
EventClose,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction,
EventRegisterCallback,
EventUnregisterCallback,
EventPost,
EventPostByEvent,
SysCpuCallIecFuncWithParams,
SysEventSet,
SysTaskCreate,
IecTaskCycle)

OPTIONAL_IMPORTS(
SysMemIsValidPointer)
