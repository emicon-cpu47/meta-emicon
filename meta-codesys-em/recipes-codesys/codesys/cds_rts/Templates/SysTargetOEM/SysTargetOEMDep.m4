/**
 * <name>SysTargetOEM</name>
 * <description> 
 *	Target specific functions
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
#define CMPID_SysTargetOEM 0x12345

SET_COMPONENT_NAME(`SysTargetOEM')
COMPONENT_SOURCES(`SysTargetOEM.c')
COMPONENT_SYSSOURCES(`SysTargetOS.c')

COMPONENT_VERSION(`0x03050A00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

CATEGORY(`System')

USE_ITF(`CMItf.m4')
USE_ITF(`CMUtilsItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`SysMemItf.m4')
USE_ITF(`SysTargetItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')

IMPLEMENT_ITF(`SysTargetItf.m4')

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
SysMemSwap,
SysTargetGetConfiguredNodeName)
