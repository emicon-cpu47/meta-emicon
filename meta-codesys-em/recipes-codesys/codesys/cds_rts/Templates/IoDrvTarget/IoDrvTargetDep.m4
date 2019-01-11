/**
 *  <name>Component Target</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
SET_COMPONENT_NAME(`IoDrvTarget')
COMPONENT_SOURCES(`IoDrvBase.c', `IoDrvTarget.c')

COMPONENT_VERSION(`0x03050D00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

USE_ITF(`SysMemItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CMItf.m4')
USE_ITF(`CmpIoMgrItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpIecTaskItf.m4')
USE_ITF(`CMUtilsItf.m4')

IMPLEMENT_ITF(`CmpIoDrvItf.m4',`CmpIoDrvParameterItf.m4',`CmpIoDrvDPV1C1MasterItf.m4',`CmpIoDrvDPV1C1SlaveItf.m4')

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
IoMgrConfigGetParameterValueWord,
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
CMUtlSafeStrCpy)
