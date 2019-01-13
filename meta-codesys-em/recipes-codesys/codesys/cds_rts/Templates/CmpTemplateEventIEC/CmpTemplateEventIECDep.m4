/**
 *  <name>Component Template</name>
 *  <description> 
 *  Simple example about using runtime system events in IEC applications.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpTemplateEventIEC')
COMPONENT_SOURCES(`CmpTemplateEventIEC.c')

COMPONENT_VERSION(`0x03050A00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0001')				

#define CMPID_CmpTemplateEventIEC		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpTemplateEventIEC	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpTemplateEventIEC		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Templates')

IMPLEMENT_ITF(`CmpTemplateEventIECItf.m4')

USE_ITF(`CMItf.m4')
USE_ITF(`CmpEventMgrItf.m4')

REQUIRED_IMPORTS(
EventCreate,
EventCreate2,
EventDelete,
EventOpen,
EventClose,
EventPost)

