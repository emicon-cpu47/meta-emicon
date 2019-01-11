/**
 *  <name>Component IOMgr Sub</name>
 *  <description> 
 *  An empty implementation of the interface CmpIoMgrItf. This implementation can be
 *  used for example as a template for specially developed IOManagers or when an empty
 *  implemented IOMgr is necessary.
 *  </description>
 *  <copyright>
 *  Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 *  </copyright>
 */
SET_COMPONENT_NAME(`CmpIoMgrStub')
COMPONENT_SOURCES(`CmpIoMgrStub.c')

COMPONENT_VERSION(`0x03050D00')
COMPONENT_VENDORID(`RTS_VENDORID_3S')

#define CMPID_CmpIoMgrStub		0x2000								/* To prevent conflicts with "real" components, we use this component id in the oem range */
#define CLASSID_CCmpIoMgrStub	ADDVENDORID(CMP_VENDORID, 0x2000)	/* To prevent conflicts with "real" components, we use this component id in the oem range */
#define ITFID_ICmpIoMgrStub		ADDVENDORID(CMP_VENDORID, 0x2000)	/* To prevent conflicts with "real" components, we use this component id in the oem range */

CATEGORY(`Application.IO')

IMPLEMENT_ITF(`CmpIoMgrItf.m4')


