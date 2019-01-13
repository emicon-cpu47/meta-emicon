SET_COMPONENT_NAME(`CmpLEDMgr')
COMPONENT_SOURCES(`CmpLEDMgr.c')

/* NOTE: REPLACE 0x03040000 BY YOUR VERSION*/
COMPONENT_VERSION(`0x03050A00')

/* NOTE: REPLACE 0xABCD BY YOUR VENDORID */
COMPONENT_VENDORID(`0xABCD')				

/* NOTE: START HERE WITH YOUR COMPONENTIDS */
#define CMPID_CmpLEDMgr		0x2000		

/* NOTE: START HERE WITH YOUR CLASSIDS*/
#define CLASSID_CCmpLEDMgr	0x2000	

/* NOTE: START HERE WITH YOUR INTERFACEIDS*/	
#define ITFID_ICmpLEDMgr		0x2000
		
IMPLEMENT_ITF(`CmpLEDMgrItf.m4')

/* NOTE: Add your own used component interfaces*/
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpIoMgrItf.m4')
USE_ITF(`CmpIoDrvItf.m4')

/* NOTE: Add or remove your own IMPORTS*/
REQUIRED_IMPORTS(
AppGetState,
AppGetFirstApp,
AppGetNextApp,
IoMgrGetConfigApplication,
IoMgrConfigGetFirstConnector,
IoMgrConfigGetNextConnector,
IoMgrConfigGetConnectorList)
