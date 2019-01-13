/**
 * <name>Component IO-driver template</name>
 * <description> 
 *  An example on how to implement an IO-driver in C.
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
SET_COMPONENT_NAME(`IoDrvSoundDemo')
COMPONENT_SOURCES(`IoDrvSoundDemo.c')

COMPONENT_VERSION(`0x03050A00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

#define CMPID_IoDrvSoundDemo		0x0000FF02
#define CLASSID_CIoDrvSoundDemo		0x0000FF02

CATEGORY(`Application.IO.IoDriver.Demo')

USE_ITF(`SysMemItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CMItf.m4')
USE_ITF(`CmpIoMgrItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpIecTaskItf.m4')
USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')

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
IoMgrRegisterInstance,
IoMgrUnregisterInstance,
IoMgrConfigGetParameter,
IoMgrConfigGetFirstConnector,
IoMgrConfigGetNextConnector,
IoMgrConfigGetFirstChild,
IoMgrConfigGetNextChild,
IoMgrConfigGetParameterValuePointer,
IoMgrConfigGetParameterValueWord,
IoMgrConfigSetDiagnosis,
IoMgrConfigResetDiagnosis,
IoMgrSetDriverProperties,
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
SysCpuTestAndReset)
