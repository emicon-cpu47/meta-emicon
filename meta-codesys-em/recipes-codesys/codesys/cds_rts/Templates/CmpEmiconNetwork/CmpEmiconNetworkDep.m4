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
SET_COMPONENT_NAME(`CmpEmiconNetwork')
COMPONENT_SOURCES(`CmpEmiconNetwork.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x163f')				

#define CMPID_CmpEmiconNetwork		0x2005								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconNetwork	ADDVENDORID(CMP_VENDORID, 0x2005)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconNetwork		ADDVENDORID(CMP_VENDORID, 0x2005)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Templates')

USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysFileItf.m4')

IMPLEMENT_ITF(`CmpEmiconNetworkItf.m4')

REQUIRED_IMPORTS(
CMUtlSafeStrCpy)

OPTIONAL_IMPORTS(
SysFileOpen,
SysFileClose,
SysFileRead,
SysFileWrite)
