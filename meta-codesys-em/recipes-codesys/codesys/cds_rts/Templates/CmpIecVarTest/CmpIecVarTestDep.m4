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
SET_COMPONENT_NAME(`CmpIecVarTest')
COMPONENT_SOURCES(`CmpIecVarTest.c')

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x5678')				

#define CMPID_CmpIecVarTest		0x2000		/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpIecVarTest	0x2000		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpIecVarTest		0x2000		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Customer')

USE_ITF(`SysTimeItf.m4')
USE_ITF(`SysOutItf.m4')
USE_ITF(`SysMemItf.m4')
USE_ITF(`CmpIecVarAccessItf.m4')

IMPLEMENT_ITF(`CmpIecVarTestItf.m4')


REQUIRED_IMPORTS(
SysTimeGetMs,
SysOutPrintf,
SysMemAllocData,
SysMemFreeData,
IecVarAccGetFirstInterface,
IecVarAccGetNextInterface,
IecVarAccGetApplicationName,
IecVarAccGetNodeFullPath,
IecVarAccBrowseDown,
IecVarAccBrowseGetNext,
IecVarAccGetNode3,
IecVarAccGetSize3,
IecVarAccGetValue3,
IecVarAccSetValue3,
IecVarAccGetTypeNode3,
IecVarAccGetNodeType,
IecVarAccGetNodeName,
IecVarAccGetTypeDesc,
IecVarAccGetTypeClass3,
IecVarAccBrowseGetRoot)

