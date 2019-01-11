/**
 * <interfacename>CmpIoDrv</interfacename>
 * <description> 
 * <p>Standard IO-driver interface.</p>
 * <p>THis interface is used for I/O drivers written in C as well as I/O
 * drivers written in IEC. IEC I/O drivers are typically written as a function
 * block, which implementes the IIoDrv Interface.</p>
 * <p>To be able to access this IEC interface from C (which is for example
 * necessary for the IoMgr), the component CmpIoDrvIec acts as a wrapper
 * between C and IEC and implements exactly this interface.</p>
 * </description>
 *
 * <copyright>
 * Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 * </copyright>
 */

SET_INTERFACE_NAME(`CmpIoDrv')

#include "CmpItf.h"

REF_ITF(`CmpIoMgrItf.m4')

/**
 * <category>Connector types</category>
 * <description>
 * <p>These are the connector types which are used most frequently. This list
 * is not complete.</p>
 * </description>
 * <element name="CT_PROGRAMMABLE">Programmable connector (can be programmed by CoDeSys)</element>
 * <element name="CT_PARAMETRIZABLE">Connector is only parametrizable</element>
 * <element name="CT_CAN_MASTER">CAN Master</element>
 * <element name="CT_CAN_SLAVE">CAN Slave</element>
 * <element name="CT_CAN_DEVICE">CAN Device</element>
 * <element name="CT_CANOPEN_SAFETY">Safety Master and Slave</element>
 * <element name="CT_J1939_MANAGER">J1939 Manager</element>
 * <element name="CT_J1939_ECU">J1939 ECU</element>
 * <element name="CT_PROFIBUS_MASTER">Profibus Master</element>
 * <element name="CT_PROFIBUS_SLAVE">Profibus Slave</element>
 * <element name="CT_PROFIBUS_DEVICE">Profibus Device</element>
 * <element name="CT_PROFIBUS_MOD_MASTER">Profibus modular Master</element>
 * <element name="CT_PROFIBUS_MOD_SLAVE">Profibus modular Slave</element>
 * <element name="CT_DEVICENET_MASTER">Profibus DeviceNet Master</element>
 * <element name="CT_DEVICENET_SLAVE">Profibus DeviceNet Slave</element>
 * <element name="CT_DEVICENET_DEVICE">Profibus DeviceNet Device</element>
 * <element name="CT_ETHERCAT_MASTER">EtherCAT Master</element>
 * <element name="CT_ETHERCAT_SLAVE">EtherCAT Slave</element>
 * <element name="CT_ETHERCAT_DEVICE">EtherCAT Device</element>
 * <element name="CT_SIL2_UNSAFE_BRIDGE_MASTER">IoDrvUnsafeBridge Master</element>
 * <element name="CT_SIL2_UNSAFE_BRIDGE_SLAVE">IoDrvUnsafeBridge Slave</element>
 * <element name="CT_PCI_MASTER">PCI Master</element>
 * <element name="CT_PCI_SLAVE">PCI Slave</element>
 * <element name="0x8000..0x8FFF">Special Connectors</element>
 */
#define CT_PROGRAMMABLE						0x1000
#define CT_SAFETY							0x1002
#define CT_DRIVE							0x1003
#define CT_PARAMETRIZABLE					0x1004
#define CT_HMI								0x1005
#define CT_SOFTMOTION_CONTROLLER_3S			0x1006
#define CT_GATEWAY_3S						0x1007

#define CT_CAN_MASTER						0x0010
#define CT_CAN_SLAVE						0x0011
#define CT_CAN_DEVICE						0x0012
#define CT_CAN_MODULE						0x0013

#define CT_CANOPEN_SAFETY					0x0015
#define CT_CANOPEN_SAFETY_SLAVE				0x001A

#define CT_J1939_MANAGER					0x0018
#define CT_J1939_ECU						0x0019

#define CT_PROFIBUS_MASTER					0x0020
#define CT_PROFIBUS_SLAVE					0x0021
#define CT_PROFIBUS_DEVICE					0x0022
#define CT_PROFIBUS_MOD_MASTER				0x0023
#define CT_PROFIBUS_MOD_SLAVE				0x0024

#define CT_DEVICENET_CANBUS					0x002F
#define CT_DEVICENET_MASTER					0x0030
#define CT_DEVICENET_SLAVE					0x0031
#define CT_DEVICENET_DEVICE					0x0032

#define CT_ETHERCAT_MASTER					0x0040
#define CT_ETHERCAT_SLAVE					0x0041
#define CT_ETHERCAT_DEVICE					0x0042
#define CT_ETHERCAT_MODULE_PARENT_CONNECTOR		0x0043
#define CT_ETHERCAT_KBUS_MODULE				0x0044

#define CT_SERCOSIII_MASTER					0x0046
#define CT_SERCOSIII_SLAVE					0x0047
#define CT_SERCOSIII_MODULE					0x0048
#define CT_SERCOSIII_SAFETY_MODULE			0x0049
#define CT_SERCOSIII_SLAVE_CONNECTOR_TO_MODULE	0x004A

#define CT_PROFINET_IO_MASTER				0x0050
#define CT_PROFINET_IO_SLAVE				0x0051
#define CT_PROFINET_IO_MODULE				0x0052
#define CT_PROFINET_IO_DEVICE				0x0053
#define CT_PROFINET_IO_SUBMODULE			0x0054

#define CT_MODBUS_TCP_MASTER				0x0058
#define CT_MODBUS_TCP_SLAVE					0x0059
#define CT_MODBUS_TCP_SLAVE_DEVICE			0x0073

#define CT_MODBUS_SERIAL_MASTER				0x005A
#define CT_MODBUS_SERIAL_SLAVE_TO_MASTER	0x005B
#define CT_MODBUS_SERIAL_PORT				0x005C
#define CT_MODBUS_SERIAL_MASTER_TO_PORT		0x005D

#define CT_ETHERNET_IP_SCANNER				0x0064
#define CT_ETHERNET_IP_REMOTE_ADAPTER		0x0065
#define CT_ETHERNET_IP_MODULE				0x0066
#define CT_ETHERNET_IP_LOCAL_ADAPTER		0x0078

#define CT_ETHERNET_ADAPTER					0x006E

#define CT_ASI_MASTER						0x0082
#define CT_ASI_SLAVE						0x0083

#define CT_SOFTIO_MASTER					0x0094
#define CT_SOFTIO_SLAVE						0x0095

#define CT_GENERIC_LOGICAL_DEVICE			0x0096
#define CT_GENERATED_LOGICAL_DEVICE			0x0097
#define CT_LOGICAL_GVL_DEVICE				0x0098

#define CT_IOLINK_MASTER					0x00A0
#define CT_IOLINK_DEVICE_V101				0x00A2
#define CT_IOLINK_DEVICE_V11				0x00A3
#define CT_IOLINK_STANDARD_INOUT			0x00B0

#define CT_SIL2_UNSAFE_BRIDGE_MASTER		0x00C0
#define CT_SIL2_UNSAFE_BRIDGE_SLAVE			0x00C1

#define CT_PCI_MASTER						0x0100
#define CT_PCI_SLAVE						0x0101

#define CT_IEC61850_SERVER					0x0200
#define CT_IEC61850_SERVER_PARENT			0x0201
#define CT_IEC61850_CONTROL_BLOCKS			0x0202	/*..0x021F */
#define CT_IEC61850_LOGICAL_DEVICE			0x0230	/*..0x023F */
#define CT_IEC61850_LOGICAL_NODE			0x0240  /*..0x024F */
#define CT_IEC61850_DATA_SETS_NODE			0x0250
#define CT_IEC61850_REPORT_CONTROL_BLOCKS_NODE	0x0260
#define CT_IEC61850_LOG_CONTROL_BLOCKS_NODE		0x270
#define CT_IEC61850_GOOSE_CONTROL_BLOCKS_NODE	0x280
#define CT_IEC61850_SAMPLED_VALUE_CONTROL_NODE	0x290
	
#define CT_SAFETYSP_IO_MASTER				0x301
#define CT_SAFETYSP_IP_SLAVE				0x302
	
#define CT_SOFTMOTION_ALLGEMEIN				0x400
#define CT_SOFTMOTION_POSCONTROL			0x401
#define CT_SoftMotion_CAN					0x402
#define CT_SOFTMOTION_ETHERCAT				0x403
#define CT_SOFTMOTION_SERCOSIII				0x404
#define CT_SOFTMOTION_FREE_ENCODER			0x480
#define CT_SOFTMOTION_FIX_ENCODER			0x481
#define CT_SOFTMOTION_ENCODER_CAN			0x482
#define CT_SOFTMOTION_ENCODER_ETHERCAT		0x483
#define CT_SOFTMOTION_LOGICAL_AXIS			0x4e0
#define CT_SOFTMOTION_DRIVEPOOL				0x4ff

#define CT_SOFTVISION_CAMERA_DEVICE			0x800

#define CT_USB_GAME_CONTROLLER				0x900

#define CT_FDT_Communication_DTM			0xFD7
#define CT_FDT_Gateway_DTM					0xFD8
#define CT_FDT_Device_DTM					0xFD9

#define CT_OEM_START						0x8000
#define CT_OEM_END							0x8FFF



/**
 * <category>Connector flags</category>
 * <description>
 * Flags that specifies diagnostic informations of a connector
 * </description>
 * <element name="CF_ENABLE">Connector enabled</element>
 * <element name="CF_CONNECTOR_FOUND">Connector found (device detected)</element>
 * <element name="CF_CONNECTOR_CONFIGURED">Connector configured</element>
 * <element name="CF_CONNECTOR_ACTIVE">Connector active</element>
 * <element name="CF_CONNECTOR_BUS_ERROR">Bus error</element>
 * <element name="CF_CONNECTOR_ERROR">General connector error</element>
 * <element name="CF_CONNECTOR_DIAGNOSTIC_AVAILABLE">Diagnostic information available</element>
 * <element name="CF_CONNECTOR_PASSIVE">Passive mode of the second master in redundancy systems</element>
 */
#define CF_ENABLE							0x0001
#define CF_DRIVER_AVAILABLE					0x0010
#define CF_CONNECTOR_FOUND					0x0020
#define CF_CONNECTOR_CONFIGURED				0x0040
#define CF_CONNECTOR_ACTIVE					0x0080
#define CF_CONNECTOR_BUS_ERROR				0x0100
#define CF_CONNECTOR_ERROR					0x0200
#define CF_CONNECTOR_DIAGNOSTIC_AVAILABLE	0x0400
#define CF_CONNECTOR_PASSIVE				0x0800

/**
 * <category>Connector options</category>
 * <description>
 * Options to specify properties of a connector
 * </description>
 * <element name="CO_SCAN_PENDING_SUPPORTED">Scan the IO-configuration with segmented transfer is supported. In this case, the call of IoDrvScanModules()
 *	can return ERR_PENDING to get further calls to transmit more scan results.
 * </element>
 */
#define CO_NONE								0x0000
#define CO_SCAN_PENDING_SUPPORTED			0x0001
/* ATTENTION: If new flags are added here, you have to add this at the CO_ALLOWED macro. This is necessary for SIL2 consistency checks! */
#define CO_ALLOWED							CO_SCAN_PENDING_SUPPORTED
#define CO_OPTIONS_VALID(options)			((options & ~CO_ALLOWED)? FALSE : TRUE)

/**
 * <category>Parameter value flags</category>
 * <description>
 * <p>Defines the type of the parameter</p>
 * <p>Actually only PVF_POINTER is currently supported by CoDeSys</p>
 * </description>
 * <element name="PVF_FUNCTION">Functional access to the parameter, Value is a function pointer.</element>
 * <element name="PVF_POINTER">Value is a pointer to the value</element>
 * <element name="PVF_VALUE">Obsolete: NOT USED. Value can be interpreted directly as a value (max. 32 Bit datatypes)</element>
 * <element name="PVF_READ">Parameter can be read</element>
 * <element name="PVF_WRITE">Parameter can be written</element>
 */
#define PVF_FUNCTION			0x0001
#define PVF_POINTER				0x0002
#define PVF_VALUE				0x0004
#define PVF_READ				0x0010
#define PVF_WRITE				0x0020

/**
 * <category>Fieldbus independent parameters</category>
 * <description>
 * </description>
 * <element name="FIP_NETX_DEVICE">Parameter to identify netX devices.</element>
 * <element name="FIP_WATCHDOG">Master Watchdog time</element>
 */
#define FIP_NETX_DEVICE			0x70000000
#define FIP_WATCHDOG			0x70000001


/**
 * <category>Driver property flags</category>
 * <description>
 * </description>
 * <element name="DRVPROP_CONSISTENCY">
 * The io driver realizes bit-consistency by its own (atomar bit access).
 * If this flag is 0, the I/O Manager takes care about the consistency.
 * </element>
 * <element name="DRVPROP_WATCHTDOG">
 * The io driver needs a cyclic call to the IoDrvWatchdogTrigger interface
 * function. This property is deprecated.
 * </element>
 * <element name="DRVPROP_REDUNDANCY">
 * The I/O driver is running in redundancy mode (passive)
 * </element>
 * <element name="DRVPROP_ACTIVE">
 * The I/O driver is running in redundancy mode (active).
 * </element>
 * <element name="DRVPROP_ERROR_ACTIVE">
 * Inform the 3S redundancy Manager about an error of an active driver. This
 * will lead to a switch between active and passive PLC.
 * </element>
 * <element name="DRVPROP_ERROR_PASSIVE">
 * Inform the 3S redundancy Manager about an error of a passive driver.
 * </element>
 * <element name="DRVPROP_BACKGROUND_GETDIAG">
 * If this property is set, the interface function IoDrvGetModuleDiagnosis() of the driver is called cyclically from a background task.
 *	NOTE:
 *	In this case, IoDrvGetModuleDiagnosis is called with:	IoDrvGetModuleDiagnosis(hIoDrv, NULL);
 *	This must be handled correctly in the IO-driver!
 * </element>
 */
#define DRVPROP_CONSISTENCY			0x0001
#define DRVPROP_WATCHTDOG			0x0002
#define DRVPROP_REDUNDANCY			0x0004
#define DRVPROP_ACTIVE				0x0008
#define DRVPROP_ERROR_ACTIVE		0x0010
#define DRVPROP_ERROR_PASSIVE		0x0020
#define DRVPROP_BACKGROUND_GETDIAG	0x0040

/**
 * <category>Channel Map List Swapping Information</category>
 * <description>
 * <p>Every Io driver needs information on the base data type of an io channel
 * to perform a correct swapping operation.The basedata type and some
 * additional swapping information can be found in the wDummy Byte of the
 * ChannelMapList struct.</p>
 * </description>
 * <element name="CMLSI_BaseTypeMask">
 * This is the mask of the base type information
 * </element>
 * <element name="CMLSI_BaseDataTypeIsSet">
 * If this bit is set, the low byte of the wDummy word contains the base type
 * information. The base type is of type TypClass3 of component SysInternalLib.
 * </element>
 * <element name="CMLSI_SwappingEnabled">
 * If this bit is set, the driver has to determine, if the io channel must be
 * swapped.
 * </element>
 */
#define CMLSI_BaseTypeMask 0x00FF
#define CMLSI_BaseDataTypeIsSet 0x0100
#define CMLSI_SwappingEnabled 0x8000



#ifdef __cplusplus
extern "C" {
#endif

/* <SIL2/> */
typedef struct tagIoDrvInfo
{
	RTS_IEC_WORD wId;
	RTS_IEC_WORD wModuleType;
	RTS_IEC_HANDLE hSpecific;
	RTS_IEC_STRING szDriverName[32];
	RTS_IEC_STRING szVendorName[32];
	RTS_IEC_STRING szDeviceName[32];
	RTS_IEC_STRING szFirmwareVersion[64];
	RTS_IEC_DWORD dwVersion;
} IoDrvInfo;


/* <SIL2/> */
typedef struct
{
	/*pointer to virtual function table*/
	void* __VFTABLEPOINTER;
} ieciodrvinstance_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoDrvInfo **ppIoDrv;
	RTS_IEC_UDINT Result;
} iodrvgetinfo_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnectorList;
	RTS_IEC_DINT nCount;
	RTS_IEC_UDINT Result;
} iodrvupdateconfiguration_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigTaskMap *pTaskMapList;
	RTS_IEC_DINT nCount;
	RTS_IEC_UDINT Result;
} iodrvupdatemapping_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnectorMap *pConnectorMapList;
	RTS_IEC_DINT nCount;
	RTS_IEC_UDINT Result;
} iodrvreadinputs_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnectorMap *pConnectorMapList;
	RTS_IEC_DINT nCount;
	RTS_IEC_UDINT Result;
} iodrvwriteoutputs_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_UDINT Result;
} iodrvstartbuscycle_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	IoConfigConnector **ppConnectorList;
	RTS_IEC_DINT *pnCount;
	RTS_IEC_UDINT Result;
} iodrvscanmodules_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_UDINT Result;
} iodrvgetmodulediagnosis_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_UDINT Result;
} iodrvidentify_struct;

/* <SIL2/> */
typedef struct
{
	ieciodrvinstance_struct *pInstance;
	IoConfigConnector *pConnector;
	RTS_IEC_UDINT Result;
} iodrvwatchdogtrigger_struct;

#ifdef __cplusplus
}
#endif

/**
 * <description>Create a new I/O driver instance. Is typically internally used by the IO-driver itself</description>
 * <param name="hIIoDrv" type="IN">Handle to the IO-driver interface. Must be 0 and is filled automatically by calling the CAL_IoDrvCreate() macro!</param>
 * <param name="ClassId" type="IN">ClassID of the driver. See "Class IDs" section in CmpItf.h or in the Dep.h file of the IO-driver.</param>
 * <param name="iId" type="IN">Instance number of the IO-driver</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <result>Should return RTS_INVALID_HANDLE</result>
 */
DEF_CREATECLASSITF_API(`RTS_HANDLE', `CDECL', `IoDrvCreate', `(RTS_HANDLE hIIoDrv, CLASSID ClassId, int iId, RTS_RESULT *pResult)')

/**
 * <description>Delete an I/O driver instance. Is typically internally used by the IO-driver itself</description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param>
 * <param name="hIIoDrv" type="IN">Handle of the ITFID_ICmpIoDrv interface</param>
 * <result>Should return ERR_NOTIMPLEMENTED</result>
 */
DEF_DELETECLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvDelete', `(RTS_HANDLE hIoDrv, RTS_HANDLE hIIoDrv)')

/**
 * <description>
 * <p>Get a driver specific info structure.</p>
 * <p>This structure contains IDs and names of the driver.</p>
 * </description>
 * <param name="hIoDrv" type="IN" range="[RTS_INVALID_HANDLE,VALID_IODRIVER]">Handle to the IO-driver instance</param> 
 * <param name="ppIoDrv" type="OUT" range="[NULL,VALID_IODRVIERINFO]">Pointer to pointer to the driver info. Pointer must be set by the driver to its internal driver info structure!</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">The info structure was returned successfully</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or ppIoDrv was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvGetInfo', `(RTS_HANDLE hIoDrv, IoDrvInfo **ppIoDrv)')

/**
 * <description>
 * <p>Update Connector Flags in the device tree.</p>
 * <p>The driver should write the current diagnostic information (available, no driver,
 * bus error,...) with the function IoDrvSetModuleDiagnosis() to the I/O connector.</p>
 * <p>This function can be used by other components or from the IEC application to
 * update the diagnostic flags of the connector. To update the status from the 
 * driver, it has to call this function manually.</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pConnector" type="IN">Pointer to the connector, that the diagostic information is requested</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK"></errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">...</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvGetModuleDiagnosis', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>Identify plugable I/O card or slave.</p>
 * <p>If the configurator supports scanning of modules, this
 * function can be used our of a communication service to
 * identify a module on the bus or locally on the PLC. This 
 * This might be done by a blinking LED or whatever the hardware
 * supports.</p>
 *</description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pConnector" type="IN">Pointer to the connector, that should identify itself physically</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Identification was sent</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnector was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Service not enabled (e.g. bus not connected)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Not provided by the driver</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvIdentify', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>Read inputs for one task</p>
 * <p>This function is called cyclically from every task
 * that is using inputs. A part of the task map list,
 * which contains only the data of one connector are passed
 * to the driver (called connector map list).</p>
 * <p>If a driver has registered one instance to more
 * than one connector, it might get more than one call with
 * a different subset of the task map list.</p>
 * <p>The I/O driver should read the data from the local
 * hardware or a buffer and write them to the corresponding
 * IEC variables.</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pConnectorMapList" type="IN">Pointer to the connector map list</param> 
 * <param name="nCount" type="IN">Number of entries in the connector map list</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ReadInputs was executed successfully.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnectorList was NULL.</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_LICENSE_MISSING">No License</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvReadInputs', `(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)')

/**
 * <description>
 * <p>Scan for submodules of a connector.</p>
 * <p>This function is executed when the driver is downloaded. It
 * is called over a communication service.</p>
 * <p>The I/O driver should search for connected subumodules and
 * return them via ppConnectorList.</p>
 * <p>NOTE: This interface is called synchronously and the buffer for
 * the connector list has to be allocated by the driver.</p>
 * <p>The buffer might be freed at the next scan or at the next
 * UpdateConfiguration.</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pConnector" type="IN">Pointer to the connector, which layout should be scanned</param> 
 * <param name="ppConnectorList" type="IN">Pointer to the scanned connectors (devices) to return</param> 
 * <param name="pnCount" type="IN">Pointer to the number of entries in the connector list to return</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Scan for modules finished</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid, pConnector, ppConnectorList or pnCount was NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal error</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Scan feature is not implemented</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PENDING">Scan still in progress. Function will be called again. ppConnectorList and pnCount may contain a partial scan result.</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvScanModules', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector, IoConfigConnector **ppConnectorList, int *pnCount)')

/**
 * <description>
 * <p>Start bus cycle for a specific connector.</p>
 * <p>The bus cycle task is defined globally for the whole PLC
 * or locally for a specific I/O connector in the CoDeSys project.
 * This call can be used by the I/O driver to flush the I/O data
 * if it was cached before.</p>
 * <p>This way we can get a better and consistent timing on the bus.</p>d
 * <p>Note: This function is called for every connector which has a
 * registered I/O driver and "needsbuscycle" set in the device description
 * (this means that it might also be called for children of the connector).</p>
 * <p>Depending on the device description, this function might be executed
 * at the beginning or at the end of the task cycle.</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN">Pointer to the connector, on which the buscycle must be triggered</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Bus cycle was triggered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">hIoDrv was invalid or pConnector NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Internal Error</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvStartBusCycle', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>Propagate I/O configuration to the drivers.</p>
 * <p>This call passes the I/O configuration (based on the
 * configuration tree in the CoDeSys programming system) to
 * all registered I/O drivers. Every driver has the chance
 * to pass this tree and to register itself for a specific
 * connector.</p>
 * <p>The driver can use the I/O Manager Interface to iterate
 * over the I/O Connectors and to read the I/O Parameters.
 * If it decides to handle the I/Os of one of those connectors,
 * it can register it's driver handle (IBase) to the connector
 * in the member hIoDrv.</p>
 * <p>This function is called when the application is initialized
 * as well as when it is de- or reinitialized. In this case it is
 * called with pConnectorList = NULL.</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pConnectorList" type="IN">Pointer to the complete connector list
 *	NOTE:
 *		The function is called with pConnectorList = NULL to signalize the driver, that the IO-configuration will be deleted!
 *		In this case, the driver can cleanup its configuration, can stop the bus etc.
 * </param> 
 * <param name="nCount" type="IN">Number of entries in the connector list</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">UpdateConfiguration was successfull and found a driver</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No connector for this driver was found</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_LICENSE">No license for this driver</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvUpdateConfiguration', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnectorList, int nCount)')

/**
 * <description>
 * <p>Propagate the task map lists to the drivers.</p>
 * <p>This functions gives the drivers a chance to optimize
 * their internal data structures based on the real task map
 * lists. The function is called on every initialization
 * of the application (download, bootproject,...).</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pTaskMapList" type="IN">Pointer to the task map list of one task</param> 
 * <param name="nCount" type="IN">Number of entries in the map list</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Default Result (mappings reorganized or nothing changed)</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">UpdateMapping is not implemented</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvUpdateMapping', `(RTS_HANDLE hIoDrv, IoConfigTaskMap *pTaskMapList, int nCount)')

/**
 * <description>
 * Trigger the hardware watchdog of this fieldbus master / IO system.
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param>
 * <param name="pConnector" type="IN">Pointer to the connector, on which the watchdog should be retriggered</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Watchdog successfully retriggered</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Watchdog not available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Watchdog interface not implemented</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWatchdogTrigger', `(RTS_HANDLE hIoDrv, IoConfigConnector *pConnector)')

/**
 * <description>
 * <p>Write outputs for one task</p>
 * <p>This function is called cyclically from every task
 * that is using outputs. A part of the task map list,
 * which contains only the data of one connector are passed
 * to the driver (called connector map list).</p>
 * <p>If a driver has registered one instance to more
 * than one connector, it might get more than one call with
 * a different subset of the task map list.</p>
 * <p>The I/O driver should write out the data to the local
 * hardware, a buffer or a fieldbus.</p>
 * </description>
 * <param name="hIoDrv" type="IN">Handle to the IO-driver instance</param> 
 * <param name="pConnectorMapList" type="IN">Pointer to the connector map list</param> 
 * <param name="nCount" type="IN">Number of entries in the connector map list</param> 
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Outputs successfully written</errorcode>
 */
DEF_CLASSITF_API(`RTS_RESULT', `CDECL', `IoDrvWriteOutputs', `(RTS_HANDLE hIoDrv, IoConfigConnectorMap *pConnectorMapList, int nCount)')

