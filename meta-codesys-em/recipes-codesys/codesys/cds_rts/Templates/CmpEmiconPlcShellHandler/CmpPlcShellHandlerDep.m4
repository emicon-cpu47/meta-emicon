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

COMPONENT_VERSION(`0x03050D00')

/* NOTE: REPLACE 0x0000 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x163f')				

#define CMPID_CmpPlcShellHandler		0x2006									/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpPlcShellHandler		ADDVENDORID(CMP_VENDORID, 0x2006)		/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpPlcShellHandler		ADDVENDORID(CMP_VENDORID, 0x2006)		/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Customer')

IMPLEMENT_ITF(`CmpPlcShellHandlerItf.m4')

USE_ITF(`CmpPlcShellItf.m4')
USE_ITF(`CmpEmiconLogItf.m4')
USE_ITF(`CmpEmiconMemManagerItf.m4')

REQUIRED_IMPORTS(
PlcShellRegister,
PlcShellUnregister,
PlcShellAppend,
PlcShellSkip,
PlcShellSetEof,
get_next_log_item,
create_log_files,
clr_sys_log,
CmpEmiconMemManager_mem_to_file,
CmpEmiconMemManager_file_to_mem)

