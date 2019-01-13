/**
 * <interfacename>CmpNameServiceServer</interfacename>
 * <description> 
 *	External interface for the naming service server
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpNameServiceServer')

#include "CmpNameService.h"

#ifdef __cplusplus
	extern "C" {
#endif

/**
 * <category>Event parameter</category>
 * <element name="ui8OemDataLen" type="INOUT">IN: Maximum length that can be written. OUT: Length needed / written by OEM.</element>
 * <element name="pData" type="IN">Buffer where to write the OEM data.</element>
 */
typedef struct
{
	RTS_UI8 ui8OemDataLen;
	char *pData;
} EVTPARAM_CmpNSSOemCallback;
#define EVTPARAMID_CmpNSSOemCallback						0x0001
#define EVTVERSION_CmpNSSOemCallback						0x0001

/**
 * <category>Events</category>
 * <description>Event is sent when a the NameServiceServer retrieves the information put into the OEM field of the naming response.
 * Note: The information put here are not evaluted by the default Automation Platform. A OEM plug in is needed to handle this data in the Automation Platform.
 * Note: The event is sent twice. The first time pData is NULL and ui8OemDataLen is 0. This is used to get the needed length of the OEM data.The OEM should 
 *       fill up the needed length into the ui8OemDataLen. 
 *       The second time the pData is available an can be filled up. ui8OemDataLen should be filled up with the actual written length.
 * </description>
 * <param name="pEventParam" type="IN">EVTPARAMID_CmpNSSOem</param>
 */
#define EVT_CmpNSSOemCallback					MAKE_EVENTID(EVTCLASS_NONE, 1)

/* -- Functions exported to the Router component */

/** <description> Protocol handler of CmpNameServiceServer. 
*   Attention: Must only be called by CmpRouter to forward an incoming data package.</description>
* <param name="hRouter" type="IN">Handle of router instance calling this function.
*   For L4 client implementations, by default it is called by the router instance 0.
*   For L4 server implementations, it is called by the router instance which has received the package originally.</param>
* <param name="hNetworkInterface" type="IN">Handle of the network interface receiving originally the package</param>
* <param name="byServiceId" type="IN">The protocol id of the package</param>
* <param name="byMessageId" type="IN">The message id of the package</param>
* <param name="addrSender"	type="IN"> Sender address.
*   The pointer within will not be valid after this function returns.</param>
* <param name="addrReceiver" type="IN">
*   Receiver address (either the address of this node or a broadcast address). 
*   The pointer within will not be valid after this function returns.</param>
* <param name="pduData" type="IN">
*   The received data. The data pointer will not be valid after this function returns.</param>
* <param name="nRouterError" type="IN">
*   If this value is not ERR_OK, then this message has been generated by an intermediate node in response to a
*   message previously sent by this node, that could not be delivered.
*   nRouterError identifies the kind of error that happened.
*   pduData then contains a detailed error description depending on the kind of error.
* </param>
* <result>error code</result>
*/
DEF_ITF_API(`RTS_RESULT',`CDECL',`NSServerHandleData',`(RTS_HANDLE hRouter, RTS_HANDLE hNetworkInterface, RTS_UI8 byServiceId, RTS_UI8 byMessageId, PEERADDRESS addrSender, PEERADDRESS addrReceiver, PROTOCOL_DATA_UNIT pduData, RTS_RESULT nRouterError)')

#ifdef __cplusplus
}
#endif

