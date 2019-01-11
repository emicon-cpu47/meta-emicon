/**
 * <name>SysTargetOEM</name>
 * <description> 
 *	Target specific functions
 * </description>
 *
 * <copyright>
 * Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 * </copyright>
 */
#define CMPID_SysTargetOEM 0x12345

SET_COMPONENT_NAME(`SysTargetOEM')
COMPONENT_SOURCES(`SysTargetOEM.c')
COMPONENT_SYSSOURCES(`SysTargetOS.c')

COMPONENT_VERSION(`0x03050D00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

CATEGORY(`System')

USE_ITF(`CMItf.m4')
USE_ITF(`CMUtilsItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`SysMemItf.m4')
USE_ITF(`SysTargetItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')

IMPLEMENT_ITF(`SysTargetItf.m4')

OPTIONAL_IMPORTS(
EventCreate3,
EventDelete,
EventPost2)

REQUIRED_IMPORTS(
CMUtlwstrcpy,
CMUtlwstrcat,
CMUtlwstrlen,
CMUtlStrToW,
CMUtlsnprintf,
CMCheckSysTargetSignature,
SettgGetWStringValue,
SettgGetStringValue,
SettgGetIntValue,
SysMemAllocData,
SysMemFreeData,
SysMemSwap,
SysTargetGetConfiguredNodeName,
SettgRemoveKey,
SettgSetWStringValue)
