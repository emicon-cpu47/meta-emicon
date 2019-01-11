/**
 *  <name>Component Test</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpPlcShellHandler')
COMPONENT_SOURCES(`CmpPlcShellHandler.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x5678')				

#define CMPID_CmpPlcShellHandler		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpPlcShellHandler	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpPlcShellHandler		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Customer')

IMPLEMENT_ITF(`CmpPlcShellHandlerItf.m4')

USE_ITF(`CmpPlcShellItf.m4')
USE_ITF(`CmpEventMgrItf.m4')

OPTIONAL_IMPORTS(
EventOpen,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction)

REQUIRED_IMPORTS(
PlcShellRegister,
PlcShellUnregister,
PlcShellAppend,
PlcShellSkip,
PlcShellSetEof)

