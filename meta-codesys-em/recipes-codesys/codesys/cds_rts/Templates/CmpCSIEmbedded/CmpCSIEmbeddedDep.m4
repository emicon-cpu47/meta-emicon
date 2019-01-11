/**
 *  <name>Component CSIEmbedded</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpCSIEmbedded')
COMPONENT_SOURCES(`CmpCSIEmbedded.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0001')				

#define CMPID_CmpCSIEmbedded		0x2000								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpCSIEmbedded	ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpCSIEmbedded		ADDVENDORID(CMP_VENDORID, 0x2000)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`CSIEmbeddeds')

IMPLEMENT_ITF(`CmpCSIEmbeddedItf.m4')

USE_ITF(`CMItf.m4')
USE_ITF(`CmpAppItf.m4')


REQUIRED_IMPORTS(
CMLoadComponent,
CMInitComponent,
EventOpen,
EventClose,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction)

