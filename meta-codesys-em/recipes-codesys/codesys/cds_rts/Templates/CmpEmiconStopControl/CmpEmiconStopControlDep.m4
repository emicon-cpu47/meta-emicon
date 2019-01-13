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
SET_COMPONENT_NAME(`CmpEmiconStopControl')
COMPONENT_SOURCES(`CmpEmiconStopControl.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x163f')				

#define CMPID_CmpEmiconStopControl		0x2003								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconStopControl	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconStopControl		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Templates')

USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysFileItf.m4')
USE_ITF(`CmpEmiconLCDItf.m4')
USE_ITF(`SysEventItf.m4')
USE_ITF(`CmpEventMgrItf.m4')
USE_ITF(`CmpLogItf.m4')
USE_ITF(`CmpAppItf.m4')

IMPLEMENT_ITF(`CmpEmiconStopControlItf.m4')

REQUIRED_IMPORTS(
CmpEmiconLCD_puts,
CmpEmiconLCD_display_screen,
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
AppStartApplications,
AppStopApplications,
CMUtlSafeStrCpy)

OPTIONAL_IMPORTS(
SysFileOpen,
SysFileClose,
SysFileRead,
SysFileWrite)
