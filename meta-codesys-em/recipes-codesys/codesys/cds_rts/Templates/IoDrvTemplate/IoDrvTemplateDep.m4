/**
 * <name>Component IO-driver template</name>
 * <description> 
 *  An example on how to implement an IO-driver in C.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
SET_COMPONENT_NAME(`IoDrvTemplate')
COMPONENT_SOURCES(`IoDrvTemplate.c')

COMPONENT_VERSION(`0x03050A00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0001')

#define CMPID_IoDrvTemplate		0x2001								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CIoDrvTemplate	ADDVENDORID(CMP_VENDORID, 0x2001)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */

CATEGORY(`Application.IO.IoDriver.Template')

USE_ITF(`SysMemItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CMItf.m4')
USE_ITF(`CmpIoMgrItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpIecTaskItf.m4')
USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')
USE_ITF(`SysTimeItf.m4')

IMPLEMENT_ITF(`CmpIoDrvItf.m4',`CmpIoDrvParameterItf.m4')

REQUIRED_IMPORTS(
SysMemAllocData,
SysMemFreeData,
SysMemAllocArea,
SysMemFreeArea,
SettgSetStringValue,
SettgGetStringValue,
SettgSetIntValue,
SettgGetIntValue,
IoMgrConfigGetParameter,
IoMgrConfigGetFirstConnector,
IoMgrConfigGetNextConnector,
IoMgrConfigGetFirstChild,
IoMgrConfigGetNextChild,
IoMgrConfigGetParameterValueWord,
IoMgrConfigGetParameterValueDword,
IoMgrConfigGetParameterValuePointer,
IoMgrConfigSetDiagnosis,
IoMgrConfigResetDiagnosis,
IoMgrSetDriverProperties,
IoMgrRegisterInstance,
IoMgrUnregisterInstance,
IoMgrConfigSetDiagnosis,
IoMgrConfigResetDiagnosis,
IoMgrCopyInputLE,
IoMgrCopyOutputLE,
IoDrvCreate,
IoDrvDelete,
EventCreate,
EventDelete,
EventOpen,
EventClose,
EventRegisterCallback,
EventUnregisterCallback,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction,
EventRegisteredCallbacks,
EventPost,
IecTaskRegisterSlotCallback,
IecTaskRegisterSlotCallbacks,
CMUtlSafeStrCpy,
SysCpuTestAndSet,
SysCpuTestAndReset,
SysTimeGetMs)
