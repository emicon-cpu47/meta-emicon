/**
 *  <name>Component Test</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpPlcShellHandler')
COMPONENT_SOURCES(`CmpPlcShellHandler.c')

COMPONENT_VERSION(`0x03050A00')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x5678')				

#define CMPID_CmpPlcShellHandler		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpPlcShellHandler	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpPlcShellHandler		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Customer')

IMPLEMENT_ITF(`CmpPlcShellHandlerItf.m4')

USE_ITF(`CmpPlcShellItf.m4')

REQUIRED_IMPORTS(
PlcShellRegister,
PlcShellUnregister,
PlcShellAppend,
PlcShellSkip,
PlcShellSetEof)

