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
SET_COMPONENT_NAME(`CmpEmiconLCD')
COMPONENT_SOURCES(`CmpEmiconLCD.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x163f')				

#define CMPID_CmpEmiconLCD		0x2004								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconLCD	ADDVENDORID(CMP_VENDORID, 0x2004)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconLCD		ADDVENDORID(CMP_VENDORID, 0x2004)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Templates')

USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysFileItf.m4')
USE_ITF(`CmpLogItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`SysEventItf.m4')
USE_ITF(`SysCpuHandlingItf.m4')
USE_ITF(`CmpEmiconEmuItf.m4')

IMPLEMENT_ITF(`CmpEmiconLCDItf.m4')

REQUIRED_IMPORTS(
CMUtlSafeStrCpy,
SysCpuCallIecFuncWithParams)

OPTIONAL_IMPORTS(
SysFileOpen,
SysFileClose,
SysFileRead,
SysFileWrite,
EventOpen,
EventClose,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction,
CmpEmiconEmu_is_emu)
