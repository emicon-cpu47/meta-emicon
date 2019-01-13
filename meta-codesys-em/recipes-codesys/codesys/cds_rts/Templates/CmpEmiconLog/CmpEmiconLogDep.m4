/**
 *  <name>Component Template</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
 SET_COMPONENT_NAME(`CmpEmiconLog')
COMPONENT_SOURCES(`CmpEmiconLog.c')
COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x163f')

#define CMPID_CmpEmiconLog		0x2002								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconLog	ADDVENDORID(CMP_VENDORID, 0x2002)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconLog		ADDVENDORID(CMP_VENDORID, 0x2002)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Emicon')

USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysFileItf.m4')
USE_ITF(`CmpLogItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpEmiconMemManagerItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`SysEventItf.m4')
USE_ITF(`CmpEmiconEmuItf.m4')

IMPLEMENT_ITF(`CmpEmiconLogItf.m4')

REQUIRED_IMPORTS(
CMUtlSafeStrCpy,
SettgGetStringValue,
SettgGetIntValue,
CmpEmiconMemManager_get_cs3_allocated_mem_size,
EventOpen,
EventClose,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction)

OPTIONAL_IMPORTS(
CmpEmiconEmu_is_emu)