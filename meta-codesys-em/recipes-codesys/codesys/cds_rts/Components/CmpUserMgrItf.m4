/**
 * <interfacename>CmpUserMgr</interfacename>
 * <description> 
 *  Interface for the user management component.
 *
 *  The user management in the runtime system is based on ACL (Access Control Lists). Here we have Users and UserGroups
 *  and access rights on objects.
 *
 *  Here are the principles of the user management:
 *
 *  1. There are users which are identified by its user name 
 *  2. A User can be a member of one or several UserGroups. But at least the user is a member of the group "Everyone".
 *  3. There are some predefined UserGroups, which covers the most typical use cases: 
 *     - "Administrator": Administrator group. A member of this groups has all access rights on all objects!
 *     - "Developer": Developer group. A member of this groups has all access to the IEC applications an all related stuff.
 *     - "Service": Service group. A member of this groups has all access to object for maintenance and service operations.
 *     - "Watch": Watch group. A member of this groups has read-only access to the objects.
 *     - "Everyone": Everyone group. A member of this groups has read-only access to the objects.
 *
 *  4. A UserGroup can be derived from another UserGroup an inherits all rights from the base group
 *  5. Every object in the runtime system, that must be protected with access rights is registered dynamically during startup of the runtime by the corresponding
 *     component under the appropriate folder.
 *     The objects in the runtime system are organized as a tree with 2 root nodes:
 *     - Runtime system object:
 *          "Device"
 *              |----- "PlcLogic"
 *              |----------- "Application"
 *              |----- "Logger"
 *              |----- "Settings"
 *              |----- "UserManagement"	
 *
 *     - Filesystem objects:
 *             "/"
 *              |----- "Temp"
 *              |----------- "Test.txt"
 *
 *  6. There are 5 different access rights that can be specified at every group for each object:
 *     - USERDB_RIGHT_NONE: Access denied
 *     - USERDB_RIGHT_VIEW: Only view rights on the object. Object cannot be modified in any case!
 *     - USERDB_RIGHT_MODIFY: Object can be viewed and modified
 *     - USERDB_RIGHT_EXECUTE: Object can be executed
 *     - USERDB_RIGHT_ADD_REMOVE_CHILDS: It is allowed to add and remove subobjects
 *     - USERDB_RIGHT_ALL: All rights allowed on the object
 *
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

SET_INTERFACE_NAME(`CmpUserMgr')

REF_ITF(`CmpUserDBItf.m4')
REF_ITF(`CmpBinTagUtilItf.m4')
REF_ITF(`CmpDeviceItf.m4')

#include "CmpItf.h"


/**
 * <category>Static defines</category>
 * <description>Number of predefined static session entries</description>
 */
#ifndef USERMGR_NUM_OF_STATIC_SESSIONS
	#define USERMGR_NUM_OF_STATIC_SESSIONS			8
#endif


/**
 * <category>Online services</category>
 * <description>
 *	Online service to read the user management.
 * </description>
 * <service name="SRV_READ_USER_MGMT">
 *	<Request>
 *		<No further tag>
 *	</Request>
 *	<Response>
 *		<tag name="TAG_PROPERTY_USERS" required="mandatory">[RTS_UI32]: User property</tag>
 *		<tag name="TAG_PROPERTY_GROUPS" required="mandatory">[RTS_UI32]: Group property</tag>
 *		<tag name="TAG_USER" required="mandatory">Top level tag may contain the following sub tags</tag>
 *			<tag name="TAG_NAME" required="optional">[char*]: NUL terminated name of the user</tag>
 *			<tag name="TAG_PASSWORD" required="optional">[char*]: Password as MD5 hash</tag>
 *			<tag name="TAG_PROPERTY" required="optional">[RTS_UI32]: User property</tag>
 *		<tag name="TAG_GROUP" required="mandatory">Top level tag may contain the following sub tags</tag>
 *			<tag name="TAG_NAME" required="optional">[char*]: NUL terminated name of the user</tag>
 *			<tag name="TAG_PASSWORD" required="optional">[char*]: Password as MD5 hash</tag>
 *			<tag name="TAG_PROPERTY" required="optional">[RTS_UI32]: User property</tag>
 *	</Response>
 * </service>
 */
#define SRV_READ_USER_MGMT							0x01

/**
 * <category>Online services</category>
 * <description>Online service to write the user management</description>
 */
#define SRV_WRITE_USER_MGMT							0x02

/**
 * <category>Online services</category>
 * <description>Online service to read the user rights management</description>
 */
#define SRV_READ_USER_RIGHTS_MGMT					0x03

/**
 * <category>Online services</category>
 * <description>Online service to write the user rights management</description>
 */
#define SRV_WRITE_USER_RIGHTS_MGMT					0x04

/**
 * <category>Online services</category>
 * <description>Online service to add a single user</description>
 */
#define SRV_USER_ADD								0x05

/**
 * <category>Online services</category>
 * <description>Online service to add a single user</description>
 */
#define SRV_USER_DELETE								0x06

/**
 * <category>Online services</category>
 * <description>Online service to add a single user</description>
 */
#define SRV_USER_CHANGE_PASSWORD					0x07


/**
 * <category>Online tags</category>
 * <description>Property of the database for users</description>
 */
#define TAG_PROPERTY_USERS							0x01

/**
 * <category>Online tags</category>
 * <description>Property of the database for groups</description>
 */
#define TAG_PROPERTY_GROUPS							0x02

/**
 * <category>Online tags</category>
 * <description>Name tag</description>
 */
#define TAG_NAME									0x03

/**
 * <category>Online tags</category>
 * <description>Property of an entry</description>
 */
#define TAG_PROPERTY								0x04

/**
 * <category>Online tags</category>
 * <description>Property of an entry</description>
 */
#define TAG_PASSWORD								0x05

/**
 * <category>Online tags</category>
 * <description>Group member</description>
 */
#define TAG_GROUP_MEMBER							0x06

/**
 * <category>Online tags</category>
 * <description>User member</description>
 */
#define TAG_USER_MEMBER								0x07

/**
 * <category>Online tags</category>
 * <description>Property of the database for groups</description>
 */
#define TAG_RIGHTS									0x08

/**
 * <category>Online tags</category>
 * <description>Property of the database for groups</description>
 */
#define TAG_DENIED_RIGHTS							0x09

/**
 * <category>Online tags</category>
 * <description>ID of an object</description>
 */
#define TAG_ID										0x0A

/**
 * <category>Online tags</category>
 * <description>Parent ID of an object</description>
 */
#define TAG_PARENT_ID								0x0B

/**
 * <category>Online tags</category>
 * <description>Object handle</description>
 */
#define TAG_OBJECT_HANDLE							0x0C

/**
 * <category>Online tags</category>
 * <description>Group handle</description>
 */
#define TAG_GROUP_HANDLE							0x0D

/**
 * <category>Online tags</category>
 * <description>Contains user information</description>
 */
#define TAG_USER									0x81

/**
 * <category>Online tags</category>
 * <description>Contains group information:
 *                     - group name
 *                     - list of users in this group
 *                     - list of child groups derived from this group
 * </description>
 */
#define TAG_GROUP									0x82

/**
 * <category>Online tags</category>
 * <description>Contains object information</description>
 */
#define TAG_OBJECT									0x83


/**
 * <category>User management session entry</category>
 * <description>
 *	Contains the correlation between the SessionID of the connection and the logged in User.
 * </description>
 * <element name="ulSessionId" type="IN">SessionID of the connection</element>
 * <element name="hUser" type="IN">Handle of the logged in user on the SessionID</element>
 */
typedef struct
{
	RTS_UI32 ulSessionId;
	RTS_HANDLE hUser;
} UserMgrSessionEntry;


/**
 * <category>Crypt types</category>
 * <description>Crypt types to chiffre the password</description>
 * <element name="USERMGR_CRYPT_INVALID" type="IN">Invalid of unknown crypt type</element>
 * <element name="USERMGR_CRYPT_XOR" type="IN">Disguise password with an XOR algorithm</element>
 */
#define USERMGR_CRYPT_INVALID				0x00000000
#define USERMGR_CRYPT_XOR					0x00000001

/**
 * <category>Static defines</category>
 * <description>Predefined objects in the runtime</description>
 */
#define USERDB_OBJECT_USERMGMT		"Device.UserManagement"


#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>Login user on the usermanagement</description>
 * <param name="pszUser" type="IN">Name of the user</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User is available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If pszUser is NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT or ERR_PARAMETER">The user is not available in the user management</errorcode>
 * <result>Handle to the user or RTS_INVALID_HANDLE if not available</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserMgrLogin', `(char *pszUser, RTS_RESULT *pResult)')

/**
 * <description>Logout specified by User</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User is available and logout succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If user is not avilable or hUser is RTS_INVALID_HANDLE</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrLogout', `(RTS_HANDLE hUser)')

/**
 * <description>Logout specified by SessionID</description>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">SessionID or user is available and logout succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If SessionID or user is not avilable</errorcode>
 */
 DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrLogoutBySessionId', `(RTS_UI32 ulSessionId)')

/**
 * <description>Check user password against credentials (authentication)!</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszPassword" type="IN">Pointer to the cleartext password!</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User is available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If user is not avilable or hUser is RTS_INVALID_HANDLE</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">If user password does not match credentials</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrCheckPassword', `(RTS_HANDLE hUser, char *pszPassword)')

/**
 * <description>Check user access rights on the specified object (authorization)!</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <param name="ulRequestedRights" type="IN">Requested rights on that object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">If user has the requested rights on the object or if no user management is configured</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If SessionID or user is not avilable or the object does not exist</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">If something failed retrieving the access rights</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS">Explicitly denied rights</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrHasAccessRights', `(char *pszObject, RTS_UI32 ulSessionId, RTS_UI32 ulRequestedRights)')

/**
 * <description>Get user access rights on the specified object (authorization)!</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <param name="pulRights" type="IN">Pointer to get admitted rights</param>
 * <param name="pulDeniedRights" type="IN">Pointer to get denied rights.
 *	 NOTE:
 *	 If the required right is denied _and_ admitted on the specified object, the denied right is more significant and so the access must be denied !!</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">If user has the requested rights on the object or if no user management is configured</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If SessionID or user is not avilable or the object does not exist</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">If something failed retrieving the access rights</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS">Explicitly denied rights</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrGetAccessRights', `(char *pszObject, RTS_UI32 ulSessionId, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights)')

/**
 * <description>Check user access rights on the specified object (authorization)!</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="ulRequestedRights" type="IN">Requested rights on that object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">If user has the requested rights on the object or if no user management is configured</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If SessionID or user is not avilable or the object does not exist</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">If something failed retrieving the access rights</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS">Explicitly denied rights</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrHasUserAccessRights', `(char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights)')

/**
 * <description>Get user access rights on the specified object (authorization)!</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pulRights" type="IN">Pointer to get admitted rights</param>
 * <param name="pulDeniedRights" type="IN">Pointer to get denied rights.
 *	 NOTE:
 *	 If the required right is denied _and_ admitted on the specified object, the denied right is more significant and so the access must be denied !!</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">If user has the requested rights on the object or if no user management is configured</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If SessionID or user is not avilable or the object does not exist</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">If something failed retrieving the access rights</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS">Explicitly denied rights</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrGetUserAccessRights', `(char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights)')

/**
 * <description>Add online SessionID to the user (bind the user at this session)</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">If user has the requested rights on the object or if no user management is configured</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">If CmpUserMgr component is still not initialized</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Could not store SessionID</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrAddSessionId', `(RTS_HANDLE hUser, RTS_UI32 *pulSessionId)')

/**
 * <description>Remove online SessionID from the user (unbind the user from this session)</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">If user has the requested rights on the object or if no user management is configured</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">If CmpUserMgr component is still not initialized</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">Could not store SessionID</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrRemoveSessionId', `(RTS_UI32 ulSessionId)')

/**
 * <description>Returns the user bound at the SessionID</description>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User is available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">If SessionID is invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT or ERR_PARAMETER">The user is not available in the user management</errorcode>
 * <result>Handle to the user or RTS_INVALID_HANDLE if not available</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserMgrFindUserBySessionId', `(RTS_UI32 ulSessionId, RTS_RESULT *pResult)')

/**
 * <description>Add the error tag to the reply stream of an online service, if the service is denied because of a failed access right (authorization error)!</description>
 * <param name="pWriter" type="IN">Pointer the writer stream</param>
 * <param name="Result" type="IN">Result code of the operation</param>
 * <param name="pszObject" type="IN">Pointer to name of the object, whose access was denied</param>
 * <param name="ulRequestedRights" type="IN">Requested rights on the object, which are not enabled</param>
 * <param name="ulSessionId" type="IN">SessionID of the device online connection (see CmpDeviceItf.h)</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Reply tag could be created</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Reply tag could not be created</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrAddOnlineAccessError', `(BINTAGWRITER *pWriter, RTS_RESULT Result, char *pszObject, RTS_UI32 ulRequestedRights, RTS_UI32 ulSessionID)')

/**
 * <description>
 *	Add a new object to the user management, so the access rights can be configured on that object.
 *	NOTE:
 *	The name of the object must include the full namespace with "Device" as the root node, e.g. "Device.MyObject" or if it's a filesystem object with "/" as the root node.
 * </description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Object invalid = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">If memory could not be allocated to store this object</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if it could not be added</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserMgrObjectAdd', `(char *pszObject, RTS_RESULT *pResult)')

/**
 * <description>Remove an object from the user management and all its children</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrObjectRemove', `(RTS_HANDLE hObject)')

/**
 * <description>
 *	Add a new object under a father object specified by its name to the user management, so the access rights can be configured on that object.
 * </description>
 * <param name="hFatherObject" type="IN">Handle to the father object, under which the object will be added</param>
 * <param name="pszObject" type="IN">Object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Object invalid = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">If memory could not be allocated to store this object</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if it could not be added</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserMgrObjectAddChild', `(RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult)')

/**
 * <description>
 *	Open an existing object.
 *	NOTE:
 *	The name of the object must include the full namespace with "Device" as the root node, e.g. "Device.MyObject" or if it's a filesystem object with "/" as the root node.
 * </description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Object not available of invalid</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if it is not available</result>
 */
DEF_ITF_API(`RTS_HANDLE', `CDECL', `UserMgrObjectOpen', `(char *pszObject, RTS_RESULT *pResult)')

/**
 * <description>Close an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrObjectClose', `(RTS_HANDLE hObject)')

/**
 * <description>Get a new challenge value to encrypt the password</description>
 * <param name="pulChallenge" type="OUT">Pointer to challenge to get the value</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Challenge could be generated</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter: pulChallenge = NULL</errorcode>
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrGetChallenge', `(RTS_UI32 *pulChallenge)')

/**
 * <description>Encrypt the password specified by crypt type</description>
 * <param name="pszPassword" type="IN">Cleartext password</param>
 * <param name="pszPasswordCrypted" type="OUT">Pointer to get the encrypted password</param>
 * <param name="pnPasswordCryptedSize" type="INOUT">Pointer to transmit the buffer length of pszPasswordCrypted or to return the necessary encrypted password length if result code is ERR_BUFFERSIZE</param>
 * <param name="ulCryptType" type="IN">Crypt type. See category "Crypt types" for details</param>
 * <param name="ulChallenge" type="IN">Challenge value to encrypt the password</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be encrypted</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">At least one parameter is invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Unsupported encryption type</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">Buffer for pszPasswordCrypted is too short, so the requested length is returned in *pnPasswordCryptedSize</errorcode> 
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrCryptPassword', `(char *pszPassword, char *pszPasswordCrypted, int *pnPasswordCryptedSize, RTS_UI32 ulCryptType, RTS_UI32 ulChallenge)')

/**
 * <description>Decrypt the password specified by crypt type</description>
 * <param name="pszPasswordCrypted" type="IN">Encrypted password</param>
 * <param name="nPasswordCryptedSize" type="IN">Lenght of the encrypted password</param>
 * <param name="ulCryptType" type="IN">Crypt type. See category "Crypt types" for details</param>
 * <param name="ulChallenge" type="IN">Challenge value to encrypt the password</param>
 * <param name="pszPassword" type="IN">Cleartext password</param>
 * <param name="pnMaxLenPassword" type="INOUT">Pointer to transmit the buffer length of pszPassword or to return the necessary decrypted password length if result code is ERR_BUFFERSIZE</param>
  * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be decrypted</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">At least one parameter is invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOT_SUPPORTED">Unsupported decryption type</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">Buffer for pszPassword is too short, so the requested length is returned in *pnMaxLenPassword</errorcode> 
 */
DEF_ITF_API(`RTS_RESULT', `CDECL', `UserMgrDecryptPassword', `(char *pszPasswordCrypted, int nPasswordCryptedSize, RTS_UI32 ulCryptType, RTS_UI32 ulChallenge, char *pszPassword, int *pnMaxLenPassword)')

#ifdef __cplusplus
}
#endif
