 /**
 * <interfacename>CmpUserDB</interfacename>
 * <description> 
 *	Interface for the user management database. Two different kinds of user management items must be stored:
 *	
 *	1. Users + Groups:
 *	   Here you have to store all users with their credentials and their property flags, additionally all user groups with all assigned users and the usergroup property flags.
 *
 *	   Example:
 *			- User: Name = "MyUser"; Password = [password in a safe hash]; Property = 0x....
 *			- UserGroup: Name = "Administrator"; UserMembers = "MyUser", "..."; Property = 0x....
 *
 *	2. User Rights:
 *	   Here you have to store the tree of all objects of the runtime system with their assigned usergroups and the configured rights on it.
 *
 *	   Example:
 *			- Object: Name = "Device"; UserGroup = "Administator" | Rights = USERDB_RIGHT_ALL | DeniedRights = USERDB_RIGHT_NONE; 
 *									   UserGroup = "..." | Rights = ... | DeniedRights = ...;
 *									   ...
 *			- Object: Name = "Device.MyObject"; UserGroup = "Administator" | Rights = USERDB_RIGHT_ALL | DeniedRights = USERDB_RIGHT_NONE; 
 *												UserGroup = "..." | Rights = ... | DeniedRights = ...;
 *												...
 *
 *	For details see CmpUserMgrItf.h.
 *
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions GmbH</copyright>
 */


	
	
#ifndef _CMPUSERDBITF_H_
#define _CMPUSERDBITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CmpCryptMD5Itf.h"

/**
 * <category>Static defines</category>
 * <description>Number of users at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_USERS
	#define USERDB_NUM_OF_STATIC_USERS		8
#endif

/**
 * <category>Static defines</category>
 * <description>Number of usergroups at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_GROUPS
	#define USERDB_NUM_OF_STATIC_GROUPS		4
#endif

/**
 * <category>Static defines</category>
 * <description>Number of user and group handles at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_HANDLES
	#define USERDB_NUM_OF_STATIC_HANDLES	12
#endif

/**
 * <category>Static defines</category>
 * <description>Number of objects at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_OBJECTS
	#define USERDB_NUM_OF_STATIC_OBJECTS		6
#endif

/**
 * <category>Static defines</category>
 * <description>Number of usergroup specific rights at startup</description>
 */
#ifndef USERDB_NUM_OF_STATIC_GROUPRIGHTS
	#define USERDB_NUM_OF_STATIC_GROUPRIGHTS	10
#endif

/**
 * <category>UserDB properties</category>
 * <description>Properties for a user or usergroup</description>
 */
#define USERDB_PROP_NONE				UINT32_C(0x00000000)
#define USERDB_PROP_EDITABLE			UINT32_C(0x00000001)
#define USERDB_PROP_ADD_MEMBER			UINT32_C(0x00000002)
#define USERDB_PROP_REMOVE_MEMBER		UINT32_C(0x00000004)
#define USERDB_PROP_CREATE				UINT32_C(0x00000008)
#define USERDB_PROP_DELETE				UINT32_C(0x00000010)
#define USERDB_PROP_REMOVE_ALL_MEMBERS	UINT32_C(0x00000020)
#define USERDB_PROP_EDIT_RIGHTS			UINT32_C(0x00000040)
#define USERDB_PROP_OWNER				UINT32_C(0x00000080)
#define USERDB_PROP_NAME_EDITABLE		UINT32_C(0x00000100)
#define USERDB_PROP_ALL					(UINT32_C(0x0FFFFFFF) & ~USERDB_PROP_OWNER)

#define USERDB_PROP_GROUP_ADMINISTRATOR_DEFAULT	(USERDB_PROP_EDITABLE | USERDB_PROP_ADD_MEMBER | USERDB_PROP_REMOVE_MEMBER | USERDB_PROP_CREATE | USERDB_PROP_OWNER)
#define USERDB_PROP_USER_ADMINISTRATOR_DEFAULT	(UINT32_C(0x0FFFFFFF) & ~USERDB_PROP_NAME_EDITABLE & ~USERDB_PROP_DELETE)
#define USERDB_PROP_GROUP_EVERYONE_DEFAULT		(USERDB_PROP_ADD_MEMBER | USERDB_PROP_REMOVE_MEMBER | USERDB_PROP_CREATE | USERDB_PROP_EDIT_RIGHTS )

/**
 * <category>Static defines</category>
 * <description>Passwort types</description>
 */
#define USERDB_PASSWORD_TYPE_STRING		UINT32_C(0x00000001)
#define USERDB_PASSWORD_TYPE_MD5		UINT32_C(0x00000002)

/**
 * <category>Union to store the cleartext password or a password hash optional</category>
 * <description>
 *	Password entry.
 * </description>
 *	<element name="psz" type="IN">Cleartext password</element>
 *	<element name="abyMD5" type="IN">Buffer to store the MD5 hash</element>
 */
typedef union
{
	char *psz;			
	unsigned char abyMD5[CRYPTMD5_KEY_LENGTH];
} UserDBPassword;

/**
 * <category>User database entry</category>
 * <description>
 *	User database entry to hold all informations of a user.
 * </description>
 *	<element name="pszUser" type="IN">User name</element>
 *	<element name="ulPasswordType" type="IN">Password type</element>
 *	<element name="Password" type="IN">Stored password credential</element>
 *	<element name="ulProperty" type="IN">User properties. See category "UserDB properties"</element>
 */
typedef struct
{
	char *pszUser;
	RTS_UI32 ulPasswordType;
	UserDBPassword Password;
	RTS_UI32 ulProperty;
} UserDBEntry;

/**
 * <category>User group database entry</category>
 * <description>
 *	User group database entry to hold all informations of a usergroup.
 * </description>
 *	<element name="pszGroup" type="IN">Group name</element>
 *	<element name="hUserList" type="IN">Handle to the mempool user list assigned to the group</element>
 *	<element name="hGroupList" type="IN">Handle to the mempool group list from which this group is derived</element>
 *	<element name="ulProperty" type="IN">User group properties. See category "UserDB properties"</element>
 */
typedef struct
{
	char *pszGroup;
	RTS_HANDLE hUserList;
	RTS_HANDLE hGroupList;
	RTS_UI32 ulProperty;
} GroupDBEntry;


/**
 * <category>Predefined user groups</category>
 * <description>Predefined user groups</description>
 * <element name="USERDB_GROUP_ADMINISTRATOR" type="IN">Administrator group. A member of this groups has all access rights on all objects!</element>
 * <element name="USERDB_GROUP_DEVELOPER" type="IN">Developer group. A member of this groups has all access to the IEC applications an all related stuff.</element>
 * <element name="USERDB_GROUP_SERVICE" type="IN">Service group. A member of this groups has all access to object for maintenance and service operations.</element>
 * <element name="USERDB_GROUP_WATCH" type="IN">Watch group. A member of this groups has read-only access to the objects.</element>
 * <element name="USERDB_GROUP_EVERYONE" type="IN">Everyone group. Every user is automatically member of this group!
 *					NOTE:
 *					By default, this group has read-only access to the objects. But this can be deactivated, so every user must be a member of one of the groups above and have
 *					no access right by default!
 * </element>
 */
#define USERDB_GROUP_ADMINISTRATOR		"Administrator"
#define USERDB_GROUP_DEVELOPER			"Developer"
#define USERDB_GROUP_SERVICE			"Service"
#define USERDB_GROUP_WATCH				"Watch"
#define USERDB_GROUP_EVERYONE			"Everyone"

/**
 * <category>Predefined users</category>
 * <description>Predefined users that are created for the default user management</description>
 */
#define USERDB_USER_ADMINISTRATOR		"Administrator"
#define USERDB_USER_EVERYONE			"Everyone"


/**
 * <category>User rights</category>
 * <description>Defined rights that can fully control the access to an object</description>
 * <element name="USERDB_RIGHT_NONE" type="IN">Access denied</element>
 * <element name="USERDB_RIGHT_VIEW" type="IN">Only view rights on the object. Object cannot be modified in any way!</element>
 * <element name="USERDB_RIGHT_MODIFY" type="IN">Object can be viewed and modified</element>
 * <element name="USERDB_RIGHT_EXECUTE" type="IN">Object can be executed</element>
 * <element name="USERDB_RIGHT_ADD_REMOVE_CHILDS" type="IN">It is allowed to add and remove subobjects</element>
 * <element name="USERDB_RIGHT_OEM" type="IN">The upper 8 bits of the access rights are reserved for OEM specific access rights</element>
 * <element name="USERDB_RIGHT_ALL" type="IN">All rights allowed on the object</element>
 */
#define USERDB_RIGHT_NONE					UINT32_C(0x00000000)
#define USERDB_RIGHT_VIEW					UINT32_C(0x00000001)
#define USERDB_RIGHT_MODIFY					UINT32_C(0x00000002)
#define USERDB_RIGHT_EXECUTE				UINT32_C(0x00000004)
#define USERDB_RIGHT_ADD_REMOVE_CHILDS		UINT32_C(0x00000008)
#define USERDB_RIGHT_OEM					UINT32_C(0xFF000000)
#define USERDB_RIGHT_ALL					UINT32_C(0xFFFFFFFF)


/**
 * <category>Group rights entry</category>
 * <description>
 *	Entry to store the rights in a specified group.
 * </description>
 * <element name="hGroup" type="IN">Handle to the group</element>
 * <element name="ulRights" type="IN">Rights of the group</element>
 * <element name="ulDeniedRights" type="IN">Denied rights of the group</element>
 */
typedef struct tagGroupRightsEntry
{
	RTS_HANDLE hGroup;
	RTS_UI32 ulRights;
	RTS_UI32 ulDeniedRights;
} GroupRightsEntry;

/**
 * <category>Object entry</category>
 * <description>
 *	Entry to store an object in the object tree.
 * </description>
 * <element name="pszObject" type="IN">Name of the object</element>
 * <element name="hFatherObject" type="IN">Handle of the father object</element>
 * <element name="hGroupRightsList" type="IN">Handle to a memory pool to store the list of all usergroups on which rights are explicitly assigned to the object</element>
 * <element name="ulID" type="IN">ID of the object</element>
 */
typedef struct tagObjectEntry
{
	char *pszObject;
	RTS_HANDLE hFatherObject;
	RTS_HANDLE hGroupRightsList;
	RTS_UI32 ulID;
} ObjectEntry;


#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*                    Users and UserGroups management																														*/
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/* --------- User management configuration ---------------------------------- */ 
/* This section of functions is OPTIONAL and must only be implemented, if the */
/* Users + Groups configuration in CODESYS is used!							  */

/**
 * <description>Function to check if users and usergroups database is configurable (not fix compiled)</description>
 * <param name="pulPropertyUsers" type="OUT">Pointer to get the users property: USERDB_PROP_ALL = Users are configurable, USERDB_PROP_NONE = Users are not configurable</param>
 * <param name="pulPropertyGroups" type="OUT">Pointer to get the user groups property: USERDB_PROP_ALL = Groups are configurable, USERDB_PROP_NONE = Groups are not configurable</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Could not be retrieved</errorcode>
 */
RTS_RESULT CDECL UserDBIsConfigurable(RTS_UI32 *pulPropertyUsers, RTS_UI32 *pulPropertyGroups);
typedef RTS_RESULT (CDECL * PFUSERDBISCONFIGURABLE) (RTS_UI32 *pulPropertyUsers, RTS_UI32 *pulPropertyGroups);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBISCONFIGURABLE_NOTIMPLEMENTED)
	#define USE_UserDBIsConfigurable
	#define EXT_UserDBIsConfigurable
	#define GET_UserDBIsConfigurable(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBIsConfigurable(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBIsConfigurable  FALSE
	#define EXP_UserDBIsConfigurable  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBIsConfigurable
	#define EXT_UserDBIsConfigurable
	#define GET_UserDBIsConfigurable(fl)  CAL_CMGETAPI( "UserDBIsConfigurable" ) 
	#define CAL_UserDBIsConfigurable  UserDBIsConfigurable
	#define CHK_UserDBIsConfigurable  TRUE
	#define EXP_UserDBIsConfigurable  CAL_CMEXPAPI( "UserDBIsConfigurable" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBIsConfigurable
	#define EXT_UserDBIsConfigurable
	#define GET_UserDBIsConfigurable(fl)  CAL_CMGETAPI( "UserDBIsConfigurable" ) 
	#define CAL_UserDBIsConfigurable  UserDBIsConfigurable
	#define CHK_UserDBIsConfigurable  TRUE
	#define EXP_UserDBIsConfigurable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBIsConfigurable", (RTS_UINTPTR)UserDBIsConfigurable, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBIsConfigurable
	#define EXT_CmpUserDBUserDBIsConfigurable
	#define GET_CmpUserDBUserDBIsConfigurable  ERR_OK
	#define CAL_CmpUserDBUserDBIsConfigurable pICmpUserDB->IUserDBIsConfigurable
	#define CHK_CmpUserDBUserDBIsConfigurable (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBIsConfigurable  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBIsConfigurable
	#define EXT_UserDBIsConfigurable
	#define GET_UserDBIsConfigurable(fl)  CAL_CMGETAPI( "UserDBIsConfigurable" ) 
	#define CAL_UserDBIsConfigurable pICmpUserDB->IUserDBIsConfigurable
	#define CHK_UserDBIsConfigurable (pICmpUserDB != NULL)
	#define EXP_UserDBIsConfigurable  CAL_CMEXPAPI( "UserDBIsConfigurable" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBIsConfigurable  PFUSERDBISCONFIGURABLE pfUserDBIsConfigurable;
	#define EXT_UserDBIsConfigurable  extern PFUSERDBISCONFIGURABLE pfUserDBIsConfigurable;
	#define GET_UserDBIsConfigurable(fl)  s_pfCMGetAPI2( "UserDBIsConfigurable", (RTS_VOID_FCTPTR *)&pfUserDBIsConfigurable, (fl), 0, 0)
	#define CAL_UserDBIsConfigurable  pfUserDBIsConfigurable
	#define CHK_UserDBIsConfigurable  (pfUserDBIsConfigurable != NULL)
	#define EXP_UserDBIsConfigurable  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBIsConfigurable", (RTS_UINTPTR)UserDBIsConfigurable, 0, 0) 
#endif




/**
 * <description>Load the user database into memory</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error loading user database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDB is fix</errorcode>
 */
RTS_RESULT CDECL UserDBLoad(void);
typedef RTS_RESULT (CDECL * PFUSERDBLOAD) (void);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBLOAD_NOTIMPLEMENTED)
	#define USE_UserDBLoad
	#define EXT_UserDBLoad
	#define GET_UserDBLoad(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBLoad()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBLoad  FALSE
	#define EXP_UserDBLoad  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBLoad
	#define EXT_UserDBLoad
	#define GET_UserDBLoad(fl)  CAL_CMGETAPI( "UserDBLoad" ) 
	#define CAL_UserDBLoad  UserDBLoad
	#define CHK_UserDBLoad  TRUE
	#define EXP_UserDBLoad  CAL_CMEXPAPI( "UserDBLoad" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBLoad
	#define EXT_UserDBLoad
	#define GET_UserDBLoad(fl)  CAL_CMGETAPI( "UserDBLoad" ) 
	#define CAL_UserDBLoad  UserDBLoad
	#define CHK_UserDBLoad  TRUE
	#define EXP_UserDBLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBLoad", (RTS_UINTPTR)UserDBLoad, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBLoad
	#define EXT_CmpUserDBUserDBLoad
	#define GET_CmpUserDBUserDBLoad  ERR_OK
	#define CAL_CmpUserDBUserDBLoad pICmpUserDB->IUserDBLoad
	#define CHK_CmpUserDBUserDBLoad (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBLoad  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBLoad
	#define EXT_UserDBLoad
	#define GET_UserDBLoad(fl)  CAL_CMGETAPI( "UserDBLoad" ) 
	#define CAL_UserDBLoad pICmpUserDB->IUserDBLoad
	#define CHK_UserDBLoad (pICmpUserDB != NULL)
	#define EXP_UserDBLoad  CAL_CMEXPAPI( "UserDBLoad" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBLoad  PFUSERDBLOAD pfUserDBLoad;
	#define EXT_UserDBLoad  extern PFUSERDBLOAD pfUserDBLoad;
	#define GET_UserDBLoad(fl)  s_pfCMGetAPI2( "UserDBLoad", (RTS_VOID_FCTPTR *)&pfUserDBLoad, (fl), 0, 0)
	#define CAL_UserDBLoad  pfUserDBLoad
	#define CHK_UserDBLoad  (pfUserDBLoad != NULL)
	#define EXP_UserDBLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBLoad", (RTS_UINTPTR)UserDBLoad, 0, 0) 
#endif




/**
 * <description>Storing the current user management into permanent database file</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error storing user database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDB is fix</errorcode>
 */
RTS_RESULT CDECL UserDBStore(void);
typedef RTS_RESULT (CDECL * PFUSERDBSTORE) (void);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBSTORE_NOTIMPLEMENTED)
	#define USE_UserDBStore
	#define EXT_UserDBStore
	#define GET_UserDBStore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBStore()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBStore  FALSE
	#define EXP_UserDBStore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBStore
	#define EXT_UserDBStore
	#define GET_UserDBStore(fl)  CAL_CMGETAPI( "UserDBStore" ) 
	#define CAL_UserDBStore  UserDBStore
	#define CHK_UserDBStore  TRUE
	#define EXP_UserDBStore  CAL_CMEXPAPI( "UserDBStore" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBStore
	#define EXT_UserDBStore
	#define GET_UserDBStore(fl)  CAL_CMGETAPI( "UserDBStore" ) 
	#define CAL_UserDBStore  UserDBStore
	#define CHK_UserDBStore  TRUE
	#define EXP_UserDBStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBStore", (RTS_UINTPTR)UserDBStore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBStore
	#define EXT_CmpUserDBUserDBStore
	#define GET_CmpUserDBUserDBStore  ERR_OK
	#define CAL_CmpUserDBUserDBStore pICmpUserDB->IUserDBStore
	#define CHK_CmpUserDBUserDBStore (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBStore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBStore
	#define EXT_UserDBStore
	#define GET_UserDBStore(fl)  CAL_CMGETAPI( "UserDBStore" ) 
	#define CAL_UserDBStore pICmpUserDB->IUserDBStore
	#define CHK_UserDBStore (pICmpUserDB != NULL)
	#define EXP_UserDBStore  CAL_CMEXPAPI( "UserDBStore" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBStore  PFUSERDBSTORE pfUserDBStore;
	#define EXT_UserDBStore  extern PFUSERDBSTORE pfUserDBStore;
	#define GET_UserDBStore(fl)  s_pfCMGetAPI2( "UserDBStore", (RTS_VOID_FCTPTR *)&pfUserDBStore, (fl), 0, 0)
	#define CAL_UserDBStore  pfUserDBStore
	#define CHK_UserDBStore  (pfUserDBStore != NULL)
	#define EXP_UserDBStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBStore", (RTS_UINTPTR)UserDBStore, 0, 0) 
#endif




/**
 * <description>Release user management in memory. NOTE: The database file is not removed!</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Failed releasing user management</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDB is fix</errorcode>
 */
RTS_RESULT CDECL UserDBRelease(void);
typedef RTS_RESULT (CDECL * PFUSERDBRELEASE) (void);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBRELEASE_NOTIMPLEMENTED)
	#define USE_UserDBRelease
	#define EXT_UserDBRelease
	#define GET_UserDBRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRelease()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRelease  FALSE
	#define EXP_UserDBRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRelease
	#define EXT_UserDBRelease
	#define GET_UserDBRelease(fl)  CAL_CMGETAPI( "UserDBRelease" ) 
	#define CAL_UserDBRelease  UserDBRelease
	#define CHK_UserDBRelease  TRUE
	#define EXP_UserDBRelease  CAL_CMEXPAPI( "UserDBRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBRelease
	#define EXT_UserDBRelease
	#define GET_UserDBRelease(fl)  CAL_CMGETAPI( "UserDBRelease" ) 
	#define CAL_UserDBRelease  UserDBRelease
	#define CHK_UserDBRelease  TRUE
	#define EXP_UserDBRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRelease", (RTS_UINTPTR)UserDBRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBRelease
	#define EXT_CmpUserDBUserDBRelease
	#define GET_CmpUserDBUserDBRelease  ERR_OK
	#define CAL_CmpUserDBUserDBRelease pICmpUserDB->IUserDBRelease
	#define CHK_CmpUserDBUserDBRelease (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRelease
	#define EXT_UserDBRelease
	#define GET_UserDBRelease(fl)  CAL_CMGETAPI( "UserDBRelease" ) 
	#define CAL_UserDBRelease pICmpUserDB->IUserDBRelease
	#define CHK_UserDBRelease (pICmpUserDB != NULL)
	#define EXP_UserDBRelease  CAL_CMEXPAPI( "UserDBRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRelease  PFUSERDBRELEASE pfUserDBRelease;
	#define EXT_UserDBRelease  extern PFUSERDBRELEASE pfUserDBRelease;
	#define GET_UserDBRelease(fl)  s_pfCMGetAPI2( "UserDBRelease", (RTS_VOID_FCTPTR *)&pfUserDBRelease, (fl), 0, 0)
	#define CAL_UserDBRelease  pfUserDBRelease
	#define CHK_UserDBRelease  (pfUserDBRelease != NULL)
	#define EXP_UserDBRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRelease", (RTS_UINTPTR)UserDBRelease, 0, 0) 
#endif




/* Single user configuration */

/**
 * <description>Add a new user to the user database</description>
 * <param name="pszUser" type="IN">User name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">User already exists</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszUser = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to store new user</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the added user or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBAdd(char *pszUser, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBADD) (char *pszUser, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBADD_NOTIMPLEMENTED)
	#define USE_UserDBAdd
	#define EXT_UserDBAdd
	#define GET_UserDBAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBAdd(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBAdd  FALSE
	#define EXP_UserDBAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBAdd
	#define EXT_UserDBAdd
	#define GET_UserDBAdd(fl)  CAL_CMGETAPI( "UserDBAdd" ) 
	#define CAL_UserDBAdd  UserDBAdd
	#define CHK_UserDBAdd  TRUE
	#define EXP_UserDBAdd  CAL_CMEXPAPI( "UserDBAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBAdd
	#define EXT_UserDBAdd
	#define GET_UserDBAdd(fl)  CAL_CMGETAPI( "UserDBAdd" ) 
	#define CAL_UserDBAdd  UserDBAdd
	#define CHK_UserDBAdd  TRUE
	#define EXP_UserDBAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBAdd", (RTS_UINTPTR)UserDBAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBAdd
	#define EXT_CmpUserDBUserDBAdd
	#define GET_CmpUserDBUserDBAdd  ERR_OK
	#define CAL_CmpUserDBUserDBAdd pICmpUserDB->IUserDBAdd
	#define CHK_CmpUserDBUserDBAdd (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBAdd
	#define EXT_UserDBAdd
	#define GET_UserDBAdd(fl)  CAL_CMGETAPI( "UserDBAdd" ) 
	#define CAL_UserDBAdd pICmpUserDB->IUserDBAdd
	#define CHK_UserDBAdd (pICmpUserDB != NULL)
	#define EXP_UserDBAdd  CAL_CMEXPAPI( "UserDBAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBAdd  PFUSERDBADD pfUserDBAdd;
	#define EXT_UserDBAdd  extern PFUSERDBADD pfUserDBAdd;
	#define GET_UserDBAdd(fl)  s_pfCMGetAPI2( "UserDBAdd", (RTS_VOID_FCTPTR *)&pfUserDBAdd, (fl), 0, 0)
	#define CAL_UserDBAdd  pfUserDBAdd
	#define CHK_UserDBAdd  (pfUserDBAdd != NULL)
	#define EXP_UserDBAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBAdd", (RTS_UINTPTR)UserDBAdd, 0, 0) 
#endif




/**
 * <description>Remove user from the user database</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle</errorcode>
 */
RTS_RESULT CDECL UserDBRemove(RTS_HANDLE hUser);
typedef RTS_RESULT (CDECL * PFUSERDBREMOVE) (RTS_HANDLE hUser);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBREMOVE_NOTIMPLEMENTED)
	#define USE_UserDBRemove
	#define EXT_UserDBRemove
	#define GET_UserDBRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRemove(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRemove  FALSE
	#define EXP_UserDBRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRemove
	#define EXT_UserDBRemove
	#define GET_UserDBRemove(fl)  CAL_CMGETAPI( "UserDBRemove" ) 
	#define CAL_UserDBRemove  UserDBRemove
	#define CHK_UserDBRemove  TRUE
	#define EXP_UserDBRemove  CAL_CMEXPAPI( "UserDBRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBRemove
	#define EXT_UserDBRemove
	#define GET_UserDBRemove(fl)  CAL_CMGETAPI( "UserDBRemove" ) 
	#define CAL_UserDBRemove  UserDBRemove
	#define CHK_UserDBRemove  TRUE
	#define EXP_UserDBRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRemove", (RTS_UINTPTR)UserDBRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBRemove
	#define EXT_CmpUserDBUserDBRemove
	#define GET_CmpUserDBUserDBRemove  ERR_OK
	#define CAL_CmpUserDBUserDBRemove pICmpUserDB->IUserDBRemove
	#define CHK_CmpUserDBUserDBRemove (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRemove
	#define EXT_UserDBRemove
	#define GET_UserDBRemove(fl)  CAL_CMGETAPI( "UserDBRemove" ) 
	#define CAL_UserDBRemove pICmpUserDB->IUserDBRemove
	#define CHK_UserDBRemove (pICmpUserDB != NULL)
	#define EXP_UserDBRemove  CAL_CMEXPAPI( "UserDBRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRemove  PFUSERDBREMOVE pfUserDBRemove;
	#define EXT_UserDBRemove  extern PFUSERDBREMOVE pfUserDBRemove;
	#define GET_UserDBRemove(fl)  s_pfCMGetAPI2( "UserDBRemove", (RTS_VOID_FCTPTR *)&pfUserDBRemove, (fl), 0, 0)
	#define CAL_UserDBRemove  pfUserDBRemove
	#define CHK_UserDBRemove  (pfUserDBRemove != NULL)
	#define EXP_UserDBRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRemove", (RTS_UINTPTR)UserDBRemove, 0, 0) 
#endif




/**
 * <description>Set or overwrite the password credential of the user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszPassword" type="IN">Pointer to password in cleartext</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or password = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBSetPassword(RTS_HANDLE hUser, char *pszPassword);
typedef RTS_RESULT (CDECL * PFUSERDBSETPASSWORD) (RTS_HANDLE hUser, char *pszPassword);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBSETPASSWORD_NOTIMPLEMENTED)
	#define USE_UserDBSetPassword
	#define EXT_UserDBSetPassword
	#define GET_UserDBSetPassword(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBSetPassword(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBSetPassword  FALSE
	#define EXP_UserDBSetPassword  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBSetPassword
	#define EXT_UserDBSetPassword
	#define GET_UserDBSetPassword(fl)  CAL_CMGETAPI( "UserDBSetPassword" ) 
	#define CAL_UserDBSetPassword  UserDBSetPassword
	#define CHK_UserDBSetPassword  TRUE
	#define EXP_UserDBSetPassword  CAL_CMEXPAPI( "UserDBSetPassword" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBSetPassword
	#define EXT_UserDBSetPassword
	#define GET_UserDBSetPassword(fl)  CAL_CMGETAPI( "UserDBSetPassword" ) 
	#define CAL_UserDBSetPassword  UserDBSetPassword
	#define CHK_UserDBSetPassword  TRUE
	#define EXP_UserDBSetPassword  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBSetPassword", (RTS_UINTPTR)UserDBSetPassword, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBSetPassword
	#define EXT_CmpUserDBUserDBSetPassword
	#define GET_CmpUserDBUserDBSetPassword  ERR_OK
	#define CAL_CmpUserDBUserDBSetPassword pICmpUserDB->IUserDBSetPassword
	#define CHK_CmpUserDBUserDBSetPassword (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBSetPassword  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBSetPassword
	#define EXT_UserDBSetPassword
	#define GET_UserDBSetPassword(fl)  CAL_CMGETAPI( "UserDBSetPassword" ) 
	#define CAL_UserDBSetPassword pICmpUserDB->IUserDBSetPassword
	#define CHK_UserDBSetPassword (pICmpUserDB != NULL)
	#define EXP_UserDBSetPassword  CAL_CMEXPAPI( "UserDBSetPassword" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBSetPassword  PFUSERDBSETPASSWORD pfUserDBSetPassword;
	#define EXT_UserDBSetPassword  extern PFUSERDBSETPASSWORD pfUserDBSetPassword;
	#define GET_UserDBSetPassword(fl)  s_pfCMGetAPI2( "UserDBSetPassword", (RTS_VOID_FCTPTR *)&pfUserDBSetPassword, (fl), 0, 0)
	#define CAL_UserDBSetPassword  pfUserDBSetPassword
	#define CHK_UserDBSetPassword  (pfUserDBSetPassword != NULL)
	#define EXP_UserDBSetPassword  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBSetPassword", (RTS_UINTPTR)UserDBSetPassword, 0, 0) 
#endif




/**
 * <description>Get the password credential of the user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pbyPasswordMD5" type="IN">Pointer to MD5 hash of the password</param>
 * <param name="piMaxLen" type="INOUT">Pointer to password MD5 hash length. If it is too short, needed length is returned if error code is ERR_BUFFERSIZE</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or piMaxLen = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">If password buffer is too short. Needed length is returned in *piMaxLen </errorcode>
 */
RTS_RESULT CDECL UserDBGetPasswordMD5(RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBGETPASSWORDMD5) (RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETPASSWORDMD5_NOTIMPLEMENTED)
	#define USE_UserDBGetPasswordMD5
	#define EXT_UserDBGetPasswordMD5
	#define GET_UserDBGetPasswordMD5(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetPasswordMD5(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGetPasswordMD5  FALSE
	#define EXP_UserDBGetPasswordMD5  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetPasswordMD5
	#define EXT_UserDBGetPasswordMD5
	#define GET_UserDBGetPasswordMD5(fl)  CAL_CMGETAPI( "UserDBGetPasswordMD5" ) 
	#define CAL_UserDBGetPasswordMD5  UserDBGetPasswordMD5
	#define CHK_UserDBGetPasswordMD5  TRUE
	#define EXP_UserDBGetPasswordMD5  CAL_CMEXPAPI( "UserDBGetPasswordMD5" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetPasswordMD5
	#define EXT_UserDBGetPasswordMD5
	#define GET_UserDBGetPasswordMD5(fl)  CAL_CMGETAPI( "UserDBGetPasswordMD5" ) 
	#define CAL_UserDBGetPasswordMD5  UserDBGetPasswordMD5
	#define CHK_UserDBGetPasswordMD5  TRUE
	#define EXP_UserDBGetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetPasswordMD5", (RTS_UINTPTR)UserDBGetPasswordMD5, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetPasswordMD5
	#define EXT_CmpUserDBUserDBGetPasswordMD5
	#define GET_CmpUserDBUserDBGetPasswordMD5  ERR_OK
	#define CAL_CmpUserDBUserDBGetPasswordMD5 pICmpUserDB->IUserDBGetPasswordMD5
	#define CHK_CmpUserDBUserDBGetPasswordMD5 (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetPasswordMD5  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetPasswordMD5
	#define EXT_UserDBGetPasswordMD5
	#define GET_UserDBGetPasswordMD5(fl)  CAL_CMGETAPI( "UserDBGetPasswordMD5" ) 
	#define CAL_UserDBGetPasswordMD5 pICmpUserDB->IUserDBGetPasswordMD5
	#define CHK_UserDBGetPasswordMD5 (pICmpUserDB != NULL)
	#define EXP_UserDBGetPasswordMD5  CAL_CMEXPAPI( "UserDBGetPasswordMD5" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetPasswordMD5  PFUSERDBGETPASSWORDMD5 pfUserDBGetPasswordMD5;
	#define EXT_UserDBGetPasswordMD5  extern PFUSERDBGETPASSWORDMD5 pfUserDBGetPasswordMD5;
	#define GET_UserDBGetPasswordMD5(fl)  s_pfCMGetAPI2( "UserDBGetPasswordMD5", (RTS_VOID_FCTPTR *)&pfUserDBGetPasswordMD5, (fl), 0, 0)
	#define CAL_UserDBGetPasswordMD5  pfUserDBGetPasswordMD5
	#define CHK_UserDBGetPasswordMD5  (pfUserDBGetPasswordMD5 != NULL)
	#define EXP_UserDBGetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetPasswordMD5", (RTS_UINTPTR)UserDBGetPasswordMD5, 0, 0) 
#endif




/**
 * <description>Set or overwrite the password credential of the user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pbyPasswordMD5" type="IN">Pointer to MD5 hash of the password</param>
 * <param name="piMaxLen" type="INOUT">Pointer to password MD5 hash length. If it is too short, needed length is returned if error code is ERR_BUFFERSIZE</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or piMaxLen = NULL</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_BUFFERSIZE">If password is too short. Needed length is returned in *piMaxLen </errorcode>
 */
RTS_RESULT CDECL UserDBSetPasswordMD5(RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBSETPASSWORDMD5) (RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBSETPASSWORDMD5_NOTIMPLEMENTED)
	#define USE_UserDBSetPasswordMD5
	#define EXT_UserDBSetPasswordMD5
	#define GET_UserDBSetPasswordMD5(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBSetPasswordMD5(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBSetPasswordMD5  FALSE
	#define EXP_UserDBSetPasswordMD5  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBSetPasswordMD5
	#define EXT_UserDBSetPasswordMD5
	#define GET_UserDBSetPasswordMD5(fl)  CAL_CMGETAPI( "UserDBSetPasswordMD5" ) 
	#define CAL_UserDBSetPasswordMD5  UserDBSetPasswordMD5
	#define CHK_UserDBSetPasswordMD5  TRUE
	#define EXP_UserDBSetPasswordMD5  CAL_CMEXPAPI( "UserDBSetPasswordMD5" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBSetPasswordMD5
	#define EXT_UserDBSetPasswordMD5
	#define GET_UserDBSetPasswordMD5(fl)  CAL_CMGETAPI( "UserDBSetPasswordMD5" ) 
	#define CAL_UserDBSetPasswordMD5  UserDBSetPasswordMD5
	#define CHK_UserDBSetPasswordMD5  TRUE
	#define EXP_UserDBSetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBSetPasswordMD5", (RTS_UINTPTR)UserDBSetPasswordMD5, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBSetPasswordMD5
	#define EXT_CmpUserDBUserDBSetPasswordMD5
	#define GET_CmpUserDBUserDBSetPasswordMD5  ERR_OK
	#define CAL_CmpUserDBUserDBSetPasswordMD5 pICmpUserDB->IUserDBSetPasswordMD5
	#define CHK_CmpUserDBUserDBSetPasswordMD5 (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBSetPasswordMD5  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBSetPasswordMD5
	#define EXT_UserDBSetPasswordMD5
	#define GET_UserDBSetPasswordMD5(fl)  CAL_CMGETAPI( "UserDBSetPasswordMD5" ) 
	#define CAL_UserDBSetPasswordMD5 pICmpUserDB->IUserDBSetPasswordMD5
	#define CHK_UserDBSetPasswordMD5 (pICmpUserDB != NULL)
	#define EXP_UserDBSetPasswordMD5  CAL_CMEXPAPI( "UserDBSetPasswordMD5" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBSetPasswordMD5  PFUSERDBSETPASSWORDMD5 pfUserDBSetPasswordMD5;
	#define EXT_UserDBSetPasswordMD5  extern PFUSERDBSETPASSWORDMD5 pfUserDBSetPasswordMD5;
	#define GET_UserDBSetPasswordMD5(fl)  s_pfCMGetAPI2( "UserDBSetPasswordMD5", (RTS_VOID_FCTPTR *)&pfUserDBSetPasswordMD5, (fl), 0, 0)
	#define CAL_UserDBSetPasswordMD5  pfUserDBSetPasswordMD5
	#define CHK_UserDBSetPasswordMD5  (pfUserDBSetPasswordMD5 != NULL)
	#define EXP_UserDBSetPasswordMD5  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBSetPasswordMD5", (RTS_UINTPTR)UserDBSetPasswordMD5, 0, 0) 
#endif




/**
 * <description>Set properties of a user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pulProperty" type="IN">Pointer to set the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or property pointer = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBSetProperty(RTS_HANDLE hUser, RTS_UI32 ulProperty);
typedef RTS_RESULT (CDECL * PFUSERDBSETPROPERTY) (RTS_HANDLE hUser, RTS_UI32 ulProperty);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBSETPROPERTY_NOTIMPLEMENTED)
	#define USE_UserDBSetProperty
	#define EXT_UserDBSetProperty
	#define GET_UserDBSetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBSetProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBSetProperty  FALSE
	#define EXP_UserDBSetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBSetProperty
	#define EXT_UserDBSetProperty
	#define GET_UserDBSetProperty(fl)  CAL_CMGETAPI( "UserDBSetProperty" ) 
	#define CAL_UserDBSetProperty  UserDBSetProperty
	#define CHK_UserDBSetProperty  TRUE
	#define EXP_UserDBSetProperty  CAL_CMEXPAPI( "UserDBSetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBSetProperty
	#define EXT_UserDBSetProperty
	#define GET_UserDBSetProperty(fl)  CAL_CMGETAPI( "UserDBSetProperty" ) 
	#define CAL_UserDBSetProperty  UserDBSetProperty
	#define CHK_UserDBSetProperty  TRUE
	#define EXP_UserDBSetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBSetProperty", (RTS_UINTPTR)UserDBSetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBSetProperty
	#define EXT_CmpUserDBUserDBSetProperty
	#define GET_CmpUserDBUserDBSetProperty  ERR_OK
	#define CAL_CmpUserDBUserDBSetProperty pICmpUserDB->IUserDBSetProperty
	#define CHK_CmpUserDBUserDBSetProperty (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBSetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBSetProperty
	#define EXT_UserDBSetProperty
	#define GET_UserDBSetProperty(fl)  CAL_CMGETAPI( "UserDBSetProperty" ) 
	#define CAL_UserDBSetProperty pICmpUserDB->IUserDBSetProperty
	#define CHK_UserDBSetProperty (pICmpUserDB != NULL)
	#define EXP_UserDBSetProperty  CAL_CMEXPAPI( "UserDBSetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBSetProperty  PFUSERDBSETPROPERTY pfUserDBSetProperty;
	#define EXT_UserDBSetProperty  extern PFUSERDBSETPROPERTY pfUserDBSetProperty;
	#define GET_UserDBSetProperty(fl)  s_pfCMGetAPI2( "UserDBSetProperty", (RTS_VOID_FCTPTR *)&pfUserDBSetProperty, (fl), 0, 0)
	#define CAL_UserDBSetProperty  pfUserDBSetProperty
	#define CHK_UserDBSetProperty  (pfUserDBSetProperty != NULL)
	#define EXP_UserDBSetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBSetProperty", (RTS_UINTPTR)UserDBSetProperty, 0, 0) 
#endif





/* --------- User management ------------------------------------------------- */
/* This section of functions is MANDATORY for the user management!             */

/* User iteration */

/**
 * <description>Iteration interface to get the first configured user</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user configured</errorcode>
 * <result>Handle to the first user or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETFIRST_NOTIMPLEMENTED)
	#define USE_UserDBGetFirst
	#define EXT_UserDBGetFirst
	#define GET_UserDBGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGetFirst  FALSE
	#define EXP_UserDBGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetFirst
	#define EXT_UserDBGetFirst
	#define GET_UserDBGetFirst(fl)  CAL_CMGETAPI( "UserDBGetFirst" ) 
	#define CAL_UserDBGetFirst  UserDBGetFirst
	#define CHK_UserDBGetFirst  TRUE
	#define EXP_UserDBGetFirst  CAL_CMEXPAPI( "UserDBGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetFirst
	#define EXT_UserDBGetFirst
	#define GET_UserDBGetFirst(fl)  CAL_CMGETAPI( "UserDBGetFirst" ) 
	#define CAL_UserDBGetFirst  UserDBGetFirst
	#define CHK_UserDBGetFirst  TRUE
	#define EXP_UserDBGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetFirst", (RTS_UINTPTR)UserDBGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetFirst
	#define EXT_CmpUserDBUserDBGetFirst
	#define GET_CmpUserDBUserDBGetFirst  ERR_OK
	#define CAL_CmpUserDBUserDBGetFirst pICmpUserDB->IUserDBGetFirst
	#define CHK_CmpUserDBUserDBGetFirst (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetFirst
	#define EXT_UserDBGetFirst
	#define GET_UserDBGetFirst(fl)  CAL_CMGETAPI( "UserDBGetFirst" ) 
	#define CAL_UserDBGetFirst pICmpUserDB->IUserDBGetFirst
	#define CHK_UserDBGetFirst (pICmpUserDB != NULL)
	#define EXP_UserDBGetFirst  CAL_CMEXPAPI( "UserDBGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetFirst  PFUSERDBGETFIRST pfUserDBGetFirst;
	#define EXT_UserDBGetFirst  extern PFUSERDBGETFIRST pfUserDBGetFirst;
	#define GET_UserDBGetFirst(fl)  s_pfCMGetAPI2( "UserDBGetFirst", (RTS_VOID_FCTPTR *)&pfUserDBGetFirst, (fl), 0, 0)
	#define CAL_UserDBGetFirst  pfUserDBGetFirst
	#define CHK_UserDBGetFirst  (pfUserDBGetFirst != NULL)
	#define EXP_UserDBGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetFirst", (RTS_UINTPTR)UserDBGetFirst, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next configured user. Must be started with UserDBGetFirst()</description>
 * <param name="hPrevUser" type="IN">Handle to the previous user retrieved via UserDBGetFirst() or subsequent calls of UserDBGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user available</errorcode>
 * <result>Handle to the next user or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGetNext(RTS_HANDLE hPrevUser, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGETNEXT) (RTS_HANDLE hPrevUser, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETNEXT_NOTIMPLEMENTED)
	#define USE_UserDBGetNext
	#define EXT_UserDBGetNext
	#define GET_UserDBGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGetNext  FALSE
	#define EXP_UserDBGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetNext
	#define EXT_UserDBGetNext
	#define GET_UserDBGetNext(fl)  CAL_CMGETAPI( "UserDBGetNext" ) 
	#define CAL_UserDBGetNext  UserDBGetNext
	#define CHK_UserDBGetNext  TRUE
	#define EXP_UserDBGetNext  CAL_CMEXPAPI( "UserDBGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetNext
	#define EXT_UserDBGetNext
	#define GET_UserDBGetNext(fl)  CAL_CMGETAPI( "UserDBGetNext" ) 
	#define CAL_UserDBGetNext  UserDBGetNext
	#define CHK_UserDBGetNext  TRUE
	#define EXP_UserDBGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetNext", (RTS_UINTPTR)UserDBGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetNext
	#define EXT_CmpUserDBUserDBGetNext
	#define GET_CmpUserDBUserDBGetNext  ERR_OK
	#define CAL_CmpUserDBUserDBGetNext pICmpUserDB->IUserDBGetNext
	#define CHK_CmpUserDBUserDBGetNext (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetNext
	#define EXT_UserDBGetNext
	#define GET_UserDBGetNext(fl)  CAL_CMGETAPI( "UserDBGetNext" ) 
	#define CAL_UserDBGetNext pICmpUserDB->IUserDBGetNext
	#define CHK_UserDBGetNext (pICmpUserDB != NULL)
	#define EXP_UserDBGetNext  CAL_CMEXPAPI( "UserDBGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetNext  PFUSERDBGETNEXT pfUserDBGetNext;
	#define EXT_UserDBGetNext  extern PFUSERDBGETNEXT pfUserDBGetNext;
	#define GET_UserDBGetNext(fl)  s_pfCMGetAPI2( "UserDBGetNext", (RTS_VOID_FCTPTR *)&pfUserDBGetNext, (fl), 0, 0)
	#define CAL_UserDBGetNext  pfUserDBGetNext
	#define CHK_UserDBGetNext  (pfUserDBGetNext != NULL)
	#define EXP_UserDBGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetNext", (RTS_UINTPTR)UserDBGetNext, 0, 0) 
#endif




/* Single user access */

/**
 * <description>Open user specified by its name</description>
 * <param name="pszUser" type="IN">User name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszUser = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the user or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBOpen(char *pszUser, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOPEN) (char *pszUser, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOPEN_NOTIMPLEMENTED)
	#define USE_UserDBOpen
	#define EXT_UserDBOpen
	#define GET_UserDBOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBOpen  FALSE
	#define EXP_UserDBOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBOpen
	#define EXT_UserDBOpen
	#define GET_UserDBOpen(fl)  CAL_CMGETAPI( "UserDBOpen" ) 
	#define CAL_UserDBOpen  UserDBOpen
	#define CHK_UserDBOpen  TRUE
	#define EXP_UserDBOpen  CAL_CMEXPAPI( "UserDBOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBOpen
	#define EXT_UserDBOpen
	#define GET_UserDBOpen(fl)  CAL_CMGETAPI( "UserDBOpen" ) 
	#define CAL_UserDBOpen  UserDBOpen
	#define CHK_UserDBOpen  TRUE
	#define EXP_UserDBOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBOpen", (RTS_UINTPTR)UserDBOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBOpen
	#define EXT_CmpUserDBUserDBOpen
	#define GET_CmpUserDBUserDBOpen  ERR_OK
	#define CAL_CmpUserDBUserDBOpen pICmpUserDB->IUserDBOpen
	#define CHK_CmpUserDBUserDBOpen (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBOpen
	#define EXT_UserDBOpen
	#define GET_UserDBOpen(fl)  CAL_CMGETAPI( "UserDBOpen" ) 
	#define CAL_UserDBOpen pICmpUserDB->IUserDBOpen
	#define CHK_UserDBOpen (pICmpUserDB != NULL)
	#define EXP_UserDBOpen  CAL_CMEXPAPI( "UserDBOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBOpen  PFUSERDBOPEN pfUserDBOpen;
	#define EXT_UserDBOpen  extern PFUSERDBOPEN pfUserDBOpen;
	#define GET_UserDBOpen(fl)  s_pfCMGetAPI2( "UserDBOpen", (RTS_VOID_FCTPTR *)&pfUserDBOpen, (fl), 0, 0)
	#define CAL_UserDBOpen  pfUserDBOpen
	#define CHK_UserDBOpen  (pfUserDBOpen != NULL)
	#define EXP_UserDBOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBOpen", (RTS_UINTPTR)UserDBOpen, 0, 0) 
#endif




/**
 * <description>Close a user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle</errorcode>
 */
RTS_RESULT CDECL UserDBClose(RTS_HANDLE hUser);
typedef RTS_RESULT (CDECL * PFUSERDBCLOSE) (RTS_HANDLE hUser);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBCLOSE_NOTIMPLEMENTED)
	#define USE_UserDBClose
	#define EXT_UserDBClose
	#define GET_UserDBClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBClose  FALSE
	#define EXP_UserDBClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBClose
	#define EXT_UserDBClose
	#define GET_UserDBClose(fl)  CAL_CMGETAPI( "UserDBClose" ) 
	#define CAL_UserDBClose  UserDBClose
	#define CHK_UserDBClose  TRUE
	#define EXP_UserDBClose  CAL_CMEXPAPI( "UserDBClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBClose
	#define EXT_UserDBClose
	#define GET_UserDBClose(fl)  CAL_CMGETAPI( "UserDBClose" ) 
	#define CAL_UserDBClose  UserDBClose
	#define CHK_UserDBClose  TRUE
	#define EXP_UserDBClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBClose", (RTS_UINTPTR)UserDBClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBClose
	#define EXT_CmpUserDBUserDBClose
	#define GET_CmpUserDBUserDBClose  ERR_OK
	#define CAL_CmpUserDBUserDBClose pICmpUserDB->IUserDBClose
	#define CHK_CmpUserDBUserDBClose (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBClose
	#define EXT_UserDBClose
	#define GET_UserDBClose(fl)  CAL_CMGETAPI( "UserDBClose" ) 
	#define CAL_UserDBClose pICmpUserDB->IUserDBClose
	#define CHK_UserDBClose (pICmpUserDB != NULL)
	#define EXP_UserDBClose  CAL_CMEXPAPI( "UserDBClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBClose  PFUSERDBCLOSE pfUserDBClose;
	#define EXT_UserDBClose  extern PFUSERDBCLOSE pfUserDBClose;
	#define GET_UserDBClose(fl)  s_pfCMGetAPI2( "UserDBClose", (RTS_VOID_FCTPTR *)&pfUserDBClose, (fl), 0, 0)
	#define CAL_UserDBClose  pfUserDBClose
	#define CHK_UserDBClose  (pfUserDBClose != NULL)
	#define EXP_UserDBClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBClose", (RTS_UINTPTR)UserDBClose, 0, 0) 
#endif




/**
 * <description>Get user name</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszUser" type="OUT">Pointer to get user name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszUser. If pszUser = NULL, only the length of the user name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or pszUser = NULL and piMaxLen = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBGetName(RTS_HANDLE hUser, char *pszUser, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBGETNAME) (RTS_HANDLE hUser, char *pszUser, int *piMaxLen);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETNAME_NOTIMPLEMENTED)
	#define USE_UserDBGetName
	#define EXT_UserDBGetName
	#define GET_UserDBGetName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetName(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGetName  FALSE
	#define EXP_UserDBGetName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetName
	#define EXT_UserDBGetName
	#define GET_UserDBGetName(fl)  CAL_CMGETAPI( "UserDBGetName" ) 
	#define CAL_UserDBGetName  UserDBGetName
	#define CHK_UserDBGetName  TRUE
	#define EXP_UserDBGetName  CAL_CMEXPAPI( "UserDBGetName" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetName
	#define EXT_UserDBGetName
	#define GET_UserDBGetName(fl)  CAL_CMGETAPI( "UserDBGetName" ) 
	#define CAL_UserDBGetName  UserDBGetName
	#define CHK_UserDBGetName  TRUE
	#define EXP_UserDBGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetName", (RTS_UINTPTR)UserDBGetName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetName
	#define EXT_CmpUserDBUserDBGetName
	#define GET_CmpUserDBUserDBGetName  ERR_OK
	#define CAL_CmpUserDBUserDBGetName pICmpUserDB->IUserDBGetName
	#define CHK_CmpUserDBUserDBGetName (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetName
	#define EXT_UserDBGetName
	#define GET_UserDBGetName(fl)  CAL_CMGETAPI( "UserDBGetName" ) 
	#define CAL_UserDBGetName pICmpUserDB->IUserDBGetName
	#define CHK_UserDBGetName (pICmpUserDB != NULL)
	#define EXP_UserDBGetName  CAL_CMEXPAPI( "UserDBGetName" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetName  PFUSERDBGETNAME pfUserDBGetName;
	#define EXT_UserDBGetName  extern PFUSERDBGETNAME pfUserDBGetName;
	#define GET_UserDBGetName(fl)  s_pfCMGetAPI2( "UserDBGetName", (RTS_VOID_FCTPTR *)&pfUserDBGetName, (fl), 0, 0)
	#define CAL_UserDBGetName  pfUserDBGetName
	#define CHK_UserDBGetName  (pfUserDBGetName != NULL)
	#define EXP_UserDBGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetName", (RTS_UINTPTR)UserDBGetName, 0, 0) 
#endif




/**
 * <description>Get properties of a user</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pulProperty" type="OUT">Pointer to return the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or property pointer = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBGetProperty(RTS_HANDLE hUser, RTS_UI32 *pulProperty);
typedef RTS_RESULT (CDECL * PFUSERDBGETPROPERTY) (RTS_HANDLE hUser, RTS_UI32 *pulProperty);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETPROPERTY_NOTIMPLEMENTED)
	#define USE_UserDBGetProperty
	#define EXT_UserDBGetProperty
	#define GET_UserDBGetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGetProperty  FALSE
	#define EXP_UserDBGetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetProperty
	#define EXT_UserDBGetProperty
	#define GET_UserDBGetProperty(fl)  CAL_CMGETAPI( "UserDBGetProperty" ) 
	#define CAL_UserDBGetProperty  UserDBGetProperty
	#define CHK_UserDBGetProperty  TRUE
	#define EXP_UserDBGetProperty  CAL_CMEXPAPI( "UserDBGetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetProperty
	#define EXT_UserDBGetProperty
	#define GET_UserDBGetProperty(fl)  CAL_CMGETAPI( "UserDBGetProperty" ) 
	#define CAL_UserDBGetProperty  UserDBGetProperty
	#define CHK_UserDBGetProperty  TRUE
	#define EXP_UserDBGetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetProperty", (RTS_UINTPTR)UserDBGetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetProperty
	#define EXT_CmpUserDBUserDBGetProperty
	#define GET_CmpUserDBUserDBGetProperty  ERR_OK
	#define CAL_CmpUserDBUserDBGetProperty pICmpUserDB->IUserDBGetProperty
	#define CHK_CmpUserDBUserDBGetProperty (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetProperty
	#define EXT_UserDBGetProperty
	#define GET_UserDBGetProperty(fl)  CAL_CMGETAPI( "UserDBGetProperty" ) 
	#define CAL_UserDBGetProperty pICmpUserDB->IUserDBGetProperty
	#define CHK_UserDBGetProperty (pICmpUserDB != NULL)
	#define EXP_UserDBGetProperty  CAL_CMEXPAPI( "UserDBGetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetProperty  PFUSERDBGETPROPERTY pfUserDBGetProperty;
	#define EXT_UserDBGetProperty  extern PFUSERDBGETPROPERTY pfUserDBGetProperty;
	#define GET_UserDBGetProperty(fl)  s_pfCMGetAPI2( "UserDBGetProperty", (RTS_VOID_FCTPTR *)&pfUserDBGetProperty, (fl), 0, 0)
	#define CAL_UserDBGetProperty  pfUserDBGetProperty
	#define CHK_UserDBGetProperty  (pfUserDBGetProperty != NULL)
	#define EXP_UserDBGetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetProperty", (RTS_UINTPTR)UserDBGetProperty, 0, 0) 
#endif




/**
 * <description>Check user credentials (authentication)</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pszPassword" type="IN">Pointer to password in cleartext</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Password credential matched!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle or password = NULL so password credential does not match!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Password credential does not match!</errorcode>
 */
RTS_RESULT CDECL UserDBCheckPassword(RTS_HANDLE hUser, char *pszPassword);
typedef RTS_RESULT (CDECL * PFUSERDBCHECKPASSWORD) (RTS_HANDLE hUser, char *pszPassword);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBCHECKPASSWORD_NOTIMPLEMENTED)
	#define USE_UserDBCheckPassword
	#define EXT_UserDBCheckPassword
	#define GET_UserDBCheckPassword(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBCheckPassword(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBCheckPassword  FALSE
	#define EXP_UserDBCheckPassword  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBCheckPassword
	#define EXT_UserDBCheckPassword
	#define GET_UserDBCheckPassword(fl)  CAL_CMGETAPI( "UserDBCheckPassword" ) 
	#define CAL_UserDBCheckPassword  UserDBCheckPassword
	#define CHK_UserDBCheckPassword  TRUE
	#define EXP_UserDBCheckPassword  CAL_CMEXPAPI( "UserDBCheckPassword" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBCheckPassword
	#define EXT_UserDBCheckPassword
	#define GET_UserDBCheckPassword(fl)  CAL_CMGETAPI( "UserDBCheckPassword" ) 
	#define CAL_UserDBCheckPassword  UserDBCheckPassword
	#define CHK_UserDBCheckPassword  TRUE
	#define EXP_UserDBCheckPassword  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBCheckPassword", (RTS_UINTPTR)UserDBCheckPassword, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBCheckPassword
	#define EXT_CmpUserDBUserDBCheckPassword
	#define GET_CmpUserDBUserDBCheckPassword  ERR_OK
	#define CAL_CmpUserDBUserDBCheckPassword pICmpUserDB->IUserDBCheckPassword
	#define CHK_CmpUserDBUserDBCheckPassword (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBCheckPassword  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBCheckPassword
	#define EXT_UserDBCheckPassword
	#define GET_UserDBCheckPassword(fl)  CAL_CMGETAPI( "UserDBCheckPassword" ) 
	#define CAL_UserDBCheckPassword pICmpUserDB->IUserDBCheckPassword
	#define CHK_UserDBCheckPassword (pICmpUserDB != NULL)
	#define EXP_UserDBCheckPassword  CAL_CMEXPAPI( "UserDBCheckPassword" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBCheckPassword  PFUSERDBCHECKPASSWORD pfUserDBCheckPassword;
	#define EXT_UserDBCheckPassword  extern PFUSERDBCHECKPASSWORD pfUserDBCheckPassword;
	#define GET_UserDBCheckPassword(fl)  s_pfCMGetAPI2( "UserDBCheckPassword", (RTS_VOID_FCTPTR *)&pfUserDBCheckPassword, (fl), 0, 0)
	#define CAL_UserDBCheckPassword  pfUserDBCheckPassword
	#define CHK_UserDBCheckPassword  (pfUserDBCheckPassword != NULL)
	#define EXP_UserDBCheckPassword  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBCheckPassword", (RTS_UINTPTR)UserDBCheckPassword, 0, 0) 
#endif




/* Iteration over all groups to which the user is assigned */

/**
 * <description>Iteration interface to get the first group to which the user is assigned</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user group configured</errorcode>
 * <result>Handle to the first user group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGetFirstGroup(RTS_HANDLE hUser, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGETFIRSTGROUP) (RTS_HANDLE hUser, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETFIRSTGROUP_NOTIMPLEMENTED)
	#define USE_UserDBGetFirstGroup
	#define EXT_UserDBGetFirstGroup
	#define GET_UserDBGetFirstGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetFirstGroup(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGetFirstGroup  FALSE
	#define EXP_UserDBGetFirstGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetFirstGroup
	#define EXT_UserDBGetFirstGroup
	#define GET_UserDBGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBGetFirstGroup" ) 
	#define CAL_UserDBGetFirstGroup  UserDBGetFirstGroup
	#define CHK_UserDBGetFirstGroup  TRUE
	#define EXP_UserDBGetFirstGroup  CAL_CMEXPAPI( "UserDBGetFirstGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetFirstGroup
	#define EXT_UserDBGetFirstGroup
	#define GET_UserDBGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBGetFirstGroup" ) 
	#define CAL_UserDBGetFirstGroup  UserDBGetFirstGroup
	#define CHK_UserDBGetFirstGroup  TRUE
	#define EXP_UserDBGetFirstGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetFirstGroup", (RTS_UINTPTR)UserDBGetFirstGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetFirstGroup
	#define EXT_CmpUserDBUserDBGetFirstGroup
	#define GET_CmpUserDBUserDBGetFirstGroup  ERR_OK
	#define CAL_CmpUserDBUserDBGetFirstGroup pICmpUserDB->IUserDBGetFirstGroup
	#define CHK_CmpUserDBUserDBGetFirstGroup (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetFirstGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetFirstGroup
	#define EXT_UserDBGetFirstGroup
	#define GET_UserDBGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBGetFirstGroup" ) 
	#define CAL_UserDBGetFirstGroup pICmpUserDB->IUserDBGetFirstGroup
	#define CHK_UserDBGetFirstGroup (pICmpUserDB != NULL)
	#define EXP_UserDBGetFirstGroup  CAL_CMEXPAPI( "UserDBGetFirstGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetFirstGroup  PFUSERDBGETFIRSTGROUP pfUserDBGetFirstGroup;
	#define EXT_UserDBGetFirstGroup  extern PFUSERDBGETFIRSTGROUP pfUserDBGetFirstGroup;
	#define GET_UserDBGetFirstGroup(fl)  s_pfCMGetAPI2( "UserDBGetFirstGroup", (RTS_VOID_FCTPTR *)&pfUserDBGetFirstGroup, (fl), 0, 0)
	#define CAL_UserDBGetFirstGroup  pfUserDBGetFirstGroup
	#define CHK_UserDBGetFirstGroup  (pfUserDBGetFirstGroup != NULL)
	#define EXP_UserDBGetFirstGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetFirstGroup", (RTS_UINTPTR)UserDBGetFirstGroup, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next configured user group to which the user is assigned. Must be started with UserDBGetFirstGroup()</description>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <param name="hPrevGroup" type="IN">Handle to the previous user group retrieved via UserDBGetFirstGroup() or subsequent calls of UserDBGetNextGroup()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user group available</errorcode>
 * <result>Handle to the next user group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGetNextGroup(RTS_HANDLE hUser, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGETNEXTGROUP) (RTS_HANDLE hUser, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGETNEXTGROUP_NOTIMPLEMENTED)
	#define USE_UserDBGetNextGroup
	#define EXT_UserDBGetNextGroup
	#define GET_UserDBGetNextGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGetNextGroup(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGetNextGroup  FALSE
	#define EXP_UserDBGetNextGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGetNextGroup
	#define EXT_UserDBGetNextGroup
	#define GET_UserDBGetNextGroup(fl)  CAL_CMGETAPI( "UserDBGetNextGroup" ) 
	#define CAL_UserDBGetNextGroup  UserDBGetNextGroup
	#define CHK_UserDBGetNextGroup  TRUE
	#define EXP_UserDBGetNextGroup  CAL_CMEXPAPI( "UserDBGetNextGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGetNextGroup
	#define EXT_UserDBGetNextGroup
	#define GET_UserDBGetNextGroup(fl)  CAL_CMGETAPI( "UserDBGetNextGroup" ) 
	#define CAL_UserDBGetNextGroup  UserDBGetNextGroup
	#define CHK_UserDBGetNextGroup  TRUE
	#define EXP_UserDBGetNextGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetNextGroup", (RTS_UINTPTR)UserDBGetNextGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGetNextGroup
	#define EXT_CmpUserDBUserDBGetNextGroup
	#define GET_CmpUserDBUserDBGetNextGroup  ERR_OK
	#define CAL_CmpUserDBUserDBGetNextGroup pICmpUserDB->IUserDBGetNextGroup
	#define CHK_CmpUserDBUserDBGetNextGroup (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGetNextGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGetNextGroup
	#define EXT_UserDBGetNextGroup
	#define GET_UserDBGetNextGroup(fl)  CAL_CMGETAPI( "UserDBGetNextGroup" ) 
	#define CAL_UserDBGetNextGroup pICmpUserDB->IUserDBGetNextGroup
	#define CHK_UserDBGetNextGroup (pICmpUserDB != NULL)
	#define EXP_UserDBGetNextGroup  CAL_CMEXPAPI( "UserDBGetNextGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGetNextGroup  PFUSERDBGETNEXTGROUP pfUserDBGetNextGroup;
	#define EXT_UserDBGetNextGroup  extern PFUSERDBGETNEXTGROUP pfUserDBGetNextGroup;
	#define GET_UserDBGetNextGroup(fl)  s_pfCMGetAPI2( "UserDBGetNextGroup", (RTS_VOID_FCTPTR *)&pfUserDBGetNextGroup, (fl), 0, 0)
	#define CAL_UserDBGetNextGroup  pfUserDBGetNextGroup
	#define CHK_UserDBGetNextGroup  (pfUserDBGetNextGroup != NULL)
	#define EXP_UserDBGetNextGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGetNextGroup", (RTS_UINTPTR)UserDBGetNextGroup, 0, 0) 
#endif





/* --------- Group management configuration --------------------------------- */
/* This section of functions is OPTIONAL and must only be implemented, if the */
/* Users + Groups configuration in CODESYS is used!							  */

/**
 * <description>Add a new user group to the user database</description>
 * <param name="pszGroup" type="IN">Group name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">Group already exists</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszGroup = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to store new group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the added group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupAdd(char *pszGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPADD) (char *pszGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPADD_NOTIMPLEMENTED)
	#define USE_UserDBGroupAdd
	#define EXT_UserDBGroupAdd
	#define GET_UserDBGroupAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupAdd(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupAdd  FALSE
	#define EXP_UserDBGroupAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupAdd
	#define EXT_UserDBGroupAdd
	#define GET_UserDBGroupAdd(fl)  CAL_CMGETAPI( "UserDBGroupAdd" ) 
	#define CAL_UserDBGroupAdd  UserDBGroupAdd
	#define CHK_UserDBGroupAdd  TRUE
	#define EXP_UserDBGroupAdd  CAL_CMEXPAPI( "UserDBGroupAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupAdd
	#define EXT_UserDBGroupAdd
	#define GET_UserDBGroupAdd(fl)  CAL_CMGETAPI( "UserDBGroupAdd" ) 
	#define CAL_UserDBGroupAdd  UserDBGroupAdd
	#define CHK_UserDBGroupAdd  TRUE
	#define EXP_UserDBGroupAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupAdd", (RTS_UINTPTR)UserDBGroupAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupAdd
	#define EXT_CmpUserDBUserDBGroupAdd
	#define GET_CmpUserDBUserDBGroupAdd  ERR_OK
	#define CAL_CmpUserDBUserDBGroupAdd pICmpUserDB->IUserDBGroupAdd
	#define CHK_CmpUserDBUserDBGroupAdd (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupAdd
	#define EXT_UserDBGroupAdd
	#define GET_UserDBGroupAdd(fl)  CAL_CMGETAPI( "UserDBGroupAdd" ) 
	#define CAL_UserDBGroupAdd pICmpUserDB->IUserDBGroupAdd
	#define CHK_UserDBGroupAdd (pICmpUserDB != NULL)
	#define EXP_UserDBGroupAdd  CAL_CMEXPAPI( "UserDBGroupAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupAdd  PFUSERDBGROUPADD pfUserDBGroupAdd;
	#define EXT_UserDBGroupAdd  extern PFUSERDBGROUPADD pfUserDBGroupAdd;
	#define GET_UserDBGroupAdd(fl)  s_pfCMGetAPI2( "UserDBGroupAdd", (RTS_VOID_FCTPTR *)&pfUserDBGroupAdd, (fl), 0, 0)
	#define CAL_UserDBGroupAdd  pfUserDBGroupAdd
	#define CHK_UserDBGroupAdd  (pfUserDBGroupAdd != NULL)
	#define EXP_UserDBGroupAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupAdd", (RTS_UINTPTR)UserDBGroupAdd, 0, 0) 
#endif




/**
 * <description>Remove user group from the user database</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid group handle</errorcode>
 */
RTS_RESULT CDECL UserDBGroupRemove(RTS_HANDLE hGroup);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPREMOVE) (RTS_HANDLE hGroup);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPREMOVE_NOTIMPLEMENTED)
	#define USE_UserDBGroupRemove
	#define EXT_UserDBGroupRemove
	#define GET_UserDBGroupRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupRemove(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupRemove  FALSE
	#define EXP_UserDBGroupRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupRemove
	#define EXT_UserDBGroupRemove
	#define GET_UserDBGroupRemove(fl)  CAL_CMGETAPI( "UserDBGroupRemove" ) 
	#define CAL_UserDBGroupRemove  UserDBGroupRemove
	#define CHK_UserDBGroupRemove  TRUE
	#define EXP_UserDBGroupRemove  CAL_CMEXPAPI( "UserDBGroupRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupRemove
	#define EXT_UserDBGroupRemove
	#define GET_UserDBGroupRemove(fl)  CAL_CMGETAPI( "UserDBGroupRemove" ) 
	#define CAL_UserDBGroupRemove  UserDBGroupRemove
	#define CHK_UserDBGroupRemove  TRUE
	#define EXP_UserDBGroupRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupRemove", (RTS_UINTPTR)UserDBGroupRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupRemove
	#define EXT_CmpUserDBUserDBGroupRemove
	#define GET_CmpUserDBUserDBGroupRemove  ERR_OK
	#define CAL_CmpUserDBUserDBGroupRemove pICmpUserDB->IUserDBGroupRemove
	#define CHK_CmpUserDBUserDBGroupRemove (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupRemove
	#define EXT_UserDBGroupRemove
	#define GET_UserDBGroupRemove(fl)  CAL_CMGETAPI( "UserDBGroupRemove" ) 
	#define CAL_UserDBGroupRemove pICmpUserDB->IUserDBGroupRemove
	#define CHK_UserDBGroupRemove (pICmpUserDB != NULL)
	#define EXP_UserDBGroupRemove  CAL_CMEXPAPI( "UserDBGroupRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupRemove  PFUSERDBGROUPREMOVE pfUserDBGroupRemove;
	#define EXT_UserDBGroupRemove  extern PFUSERDBGROUPREMOVE pfUserDBGroupRemove;
	#define GET_UserDBGroupRemove(fl)  s_pfCMGetAPI2( "UserDBGroupRemove", (RTS_VOID_FCTPTR *)&pfUserDBGroupRemove, (fl), 0, 0)
	#define CAL_UserDBGroupRemove  pfUserDBGroupRemove
	#define CHK_UserDBGroupRemove  (pfUserDBGroupRemove != NULL)
	#define EXP_UserDBGroupRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupRemove", (RTS_UINTPTR)UserDBGroupRemove, 0, 0) 
#endif




/**
 * <description>Add a new user to a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be added or is already added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hUser invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to add user to group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
RTS_RESULT CDECL UserDBGroupAddUser(RTS_HANDLE hGroup, RTS_HANDLE hUser);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPADDUSER) (RTS_HANDLE hGroup, RTS_HANDLE hUser);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPADDUSER_NOTIMPLEMENTED)
	#define USE_UserDBGroupAddUser
	#define EXT_UserDBGroupAddUser
	#define GET_UserDBGroupAddUser(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupAddUser(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupAddUser  FALSE
	#define EXP_UserDBGroupAddUser  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupAddUser
	#define EXT_UserDBGroupAddUser
	#define GET_UserDBGroupAddUser(fl)  CAL_CMGETAPI( "UserDBGroupAddUser" ) 
	#define CAL_UserDBGroupAddUser  UserDBGroupAddUser
	#define CHK_UserDBGroupAddUser  TRUE
	#define EXP_UserDBGroupAddUser  CAL_CMEXPAPI( "UserDBGroupAddUser" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupAddUser
	#define EXT_UserDBGroupAddUser
	#define GET_UserDBGroupAddUser(fl)  CAL_CMGETAPI( "UserDBGroupAddUser" ) 
	#define CAL_UserDBGroupAddUser  UserDBGroupAddUser
	#define CHK_UserDBGroupAddUser  TRUE
	#define EXP_UserDBGroupAddUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupAddUser", (RTS_UINTPTR)UserDBGroupAddUser, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupAddUser
	#define EXT_CmpUserDBUserDBGroupAddUser
	#define GET_CmpUserDBUserDBGroupAddUser  ERR_OK
	#define CAL_CmpUserDBUserDBGroupAddUser pICmpUserDB->IUserDBGroupAddUser
	#define CHK_CmpUserDBUserDBGroupAddUser (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupAddUser  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupAddUser
	#define EXT_UserDBGroupAddUser
	#define GET_UserDBGroupAddUser(fl)  CAL_CMGETAPI( "UserDBGroupAddUser" ) 
	#define CAL_UserDBGroupAddUser pICmpUserDB->IUserDBGroupAddUser
	#define CHK_UserDBGroupAddUser (pICmpUserDB != NULL)
	#define EXP_UserDBGroupAddUser  CAL_CMEXPAPI( "UserDBGroupAddUser" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupAddUser  PFUSERDBGROUPADDUSER pfUserDBGroupAddUser;
	#define EXT_UserDBGroupAddUser  extern PFUSERDBGROUPADDUSER pfUserDBGroupAddUser;
	#define GET_UserDBGroupAddUser(fl)  s_pfCMGetAPI2( "UserDBGroupAddUser", (RTS_VOID_FCTPTR *)&pfUserDBGroupAddUser, (fl), 0, 0)
	#define CAL_UserDBGroupAddUser  pfUserDBGroupAddUser
	#define CHK_UserDBGroupAddUser  (pfUserDBGroupAddUser != NULL)
	#define EXP_UserDBGroupAddUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupAddUser", (RTS_UINTPTR)UserDBGroupAddUser, 0, 0) 
#endif




/**
 * <description>Remove a user from a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="hUser" type="IN">Handle to the user</param>
  * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hUser invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
RTS_RESULT CDECL UserDBGroupRemoveUser(RTS_HANDLE hGroup, RTS_HANDLE hUser);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPREMOVEUSER) (RTS_HANDLE hGroup, RTS_HANDLE hUser);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPREMOVEUSER_NOTIMPLEMENTED)
	#define USE_UserDBGroupRemoveUser
	#define EXT_UserDBGroupRemoveUser
	#define GET_UserDBGroupRemoveUser(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupRemoveUser(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupRemoveUser  FALSE
	#define EXP_UserDBGroupRemoveUser  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupRemoveUser
	#define EXT_UserDBGroupRemoveUser
	#define GET_UserDBGroupRemoveUser(fl)  CAL_CMGETAPI( "UserDBGroupRemoveUser" ) 
	#define CAL_UserDBGroupRemoveUser  UserDBGroupRemoveUser
	#define CHK_UserDBGroupRemoveUser  TRUE
	#define EXP_UserDBGroupRemoveUser  CAL_CMEXPAPI( "UserDBGroupRemoveUser" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupRemoveUser
	#define EXT_UserDBGroupRemoveUser
	#define GET_UserDBGroupRemoveUser(fl)  CAL_CMGETAPI( "UserDBGroupRemoveUser" ) 
	#define CAL_UserDBGroupRemoveUser  UserDBGroupRemoveUser
	#define CHK_UserDBGroupRemoveUser  TRUE
	#define EXP_UserDBGroupRemoveUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupRemoveUser", (RTS_UINTPTR)UserDBGroupRemoveUser, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupRemoveUser
	#define EXT_CmpUserDBUserDBGroupRemoveUser
	#define GET_CmpUserDBUserDBGroupRemoveUser  ERR_OK
	#define CAL_CmpUserDBUserDBGroupRemoveUser pICmpUserDB->IUserDBGroupRemoveUser
	#define CHK_CmpUserDBUserDBGroupRemoveUser (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupRemoveUser  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupRemoveUser
	#define EXT_UserDBGroupRemoveUser
	#define GET_UserDBGroupRemoveUser(fl)  CAL_CMGETAPI( "UserDBGroupRemoveUser" ) 
	#define CAL_UserDBGroupRemoveUser pICmpUserDB->IUserDBGroupRemoveUser
	#define CHK_UserDBGroupRemoveUser (pICmpUserDB != NULL)
	#define EXP_UserDBGroupRemoveUser  CAL_CMEXPAPI( "UserDBGroupRemoveUser" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupRemoveUser  PFUSERDBGROUPREMOVEUSER pfUserDBGroupRemoveUser;
	#define EXT_UserDBGroupRemoveUser  extern PFUSERDBGROUPREMOVEUSER pfUserDBGroupRemoveUser;
	#define GET_UserDBGroupRemoveUser(fl)  s_pfCMGetAPI2( "UserDBGroupRemoveUser", (RTS_VOID_FCTPTR *)&pfUserDBGroupRemoveUser, (fl), 0, 0)
	#define CAL_UserDBGroupRemoveUser  pfUserDBGroupRemoveUser
	#define CHK_UserDBGroupRemoveUser  (pfUserDBGroupRemoveUser != NULL)
	#define EXP_UserDBGroupRemoveUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupRemoveUser", (RTS_UINTPTR)UserDBGroupRemoveUser, 0, 0) 
#endif




/**
 * <description>Set properties of a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="pulProperty" type="IN">Pointer to set the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group or property pointer = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBGroupSetProperty(RTS_HANDLE hGroup, RTS_UI32 ulProperty);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPSETPROPERTY) (RTS_HANDLE hGroup, RTS_UI32 ulProperty);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPSETPROPERTY_NOTIMPLEMENTED)
	#define USE_UserDBGroupSetProperty
	#define EXT_UserDBGroupSetProperty
	#define GET_UserDBGroupSetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupSetProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupSetProperty  FALSE
	#define EXP_UserDBGroupSetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupSetProperty
	#define EXT_UserDBGroupSetProperty
	#define GET_UserDBGroupSetProperty(fl)  CAL_CMGETAPI( "UserDBGroupSetProperty" ) 
	#define CAL_UserDBGroupSetProperty  UserDBGroupSetProperty
	#define CHK_UserDBGroupSetProperty  TRUE
	#define EXP_UserDBGroupSetProperty  CAL_CMEXPAPI( "UserDBGroupSetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupSetProperty
	#define EXT_UserDBGroupSetProperty
	#define GET_UserDBGroupSetProperty(fl)  CAL_CMGETAPI( "UserDBGroupSetProperty" ) 
	#define CAL_UserDBGroupSetProperty  UserDBGroupSetProperty
	#define CHK_UserDBGroupSetProperty  TRUE
	#define EXP_UserDBGroupSetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupSetProperty", (RTS_UINTPTR)UserDBGroupSetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupSetProperty
	#define EXT_CmpUserDBUserDBGroupSetProperty
	#define GET_CmpUserDBUserDBGroupSetProperty  ERR_OK
	#define CAL_CmpUserDBUserDBGroupSetProperty pICmpUserDB->IUserDBGroupSetProperty
	#define CHK_CmpUserDBUserDBGroupSetProperty (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupSetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupSetProperty
	#define EXT_UserDBGroupSetProperty
	#define GET_UserDBGroupSetProperty(fl)  CAL_CMGETAPI( "UserDBGroupSetProperty" ) 
	#define CAL_UserDBGroupSetProperty pICmpUserDB->IUserDBGroupSetProperty
	#define CHK_UserDBGroupSetProperty (pICmpUserDB != NULL)
	#define EXP_UserDBGroupSetProperty  CAL_CMEXPAPI( "UserDBGroupSetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupSetProperty  PFUSERDBGROUPSETPROPERTY pfUserDBGroupSetProperty;
	#define EXT_UserDBGroupSetProperty  extern PFUSERDBGROUPSETPROPERTY pfUserDBGroupSetProperty;
	#define GET_UserDBGroupSetProperty(fl)  s_pfCMGetAPI2( "UserDBGroupSetProperty", (RTS_VOID_FCTPTR *)&pfUserDBGroupSetProperty, (fl), 0, 0)
	#define CAL_UserDBGroupSetProperty  pfUserDBGroupSetProperty
	#define CHK_UserDBGroupSetProperty  (pfUserDBGroupSetProperty != NULL)
	#define EXP_UserDBGroupSetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupSetProperty", (RTS_UINTPTR)UserDBGroupSetProperty, 0, 0) 
#endif




/**
 * <description>Add a group as a member to another group. So that group is derived from the first one</description>
 * <param name="hGroup" type="IN">First group to derive from</param>
 * <param name="hGroupMember" type="IN">New member group which is derived from the first group (hGroup) after this operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_DUPLICATE">Group is already added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hGroupMember invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory available to add group to another group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
RTS_RESULT CDECL UserDBGroupAddMember(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPADDMEMBER) (RTS_HANDLE hGroup, RTS_HANDLE hGroupMember);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPADDMEMBER_NOTIMPLEMENTED)
	#define USE_UserDBGroupAddMember
	#define EXT_UserDBGroupAddMember
	#define GET_UserDBGroupAddMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupAddMember(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupAddMember  FALSE
	#define EXP_UserDBGroupAddMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupAddMember
	#define EXT_UserDBGroupAddMember
	#define GET_UserDBGroupAddMember(fl)  CAL_CMGETAPI( "UserDBGroupAddMember" ) 
	#define CAL_UserDBGroupAddMember  UserDBGroupAddMember
	#define CHK_UserDBGroupAddMember  TRUE
	#define EXP_UserDBGroupAddMember  CAL_CMEXPAPI( "UserDBGroupAddMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupAddMember
	#define EXT_UserDBGroupAddMember
	#define GET_UserDBGroupAddMember(fl)  CAL_CMGETAPI( "UserDBGroupAddMember" ) 
	#define CAL_UserDBGroupAddMember  UserDBGroupAddMember
	#define CHK_UserDBGroupAddMember  TRUE
	#define EXP_UserDBGroupAddMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupAddMember", (RTS_UINTPTR)UserDBGroupAddMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupAddMember
	#define EXT_CmpUserDBUserDBGroupAddMember
	#define GET_CmpUserDBUserDBGroupAddMember  ERR_OK
	#define CAL_CmpUserDBUserDBGroupAddMember pICmpUserDB->IUserDBGroupAddMember
	#define CHK_CmpUserDBUserDBGroupAddMember (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupAddMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupAddMember
	#define EXT_UserDBGroupAddMember
	#define GET_UserDBGroupAddMember(fl)  CAL_CMGETAPI( "UserDBGroupAddMember" ) 
	#define CAL_UserDBGroupAddMember pICmpUserDB->IUserDBGroupAddMember
	#define CHK_UserDBGroupAddMember (pICmpUserDB != NULL)
	#define EXP_UserDBGroupAddMember  CAL_CMEXPAPI( "UserDBGroupAddMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupAddMember  PFUSERDBGROUPADDMEMBER pfUserDBGroupAddMember;
	#define EXT_UserDBGroupAddMember  extern PFUSERDBGROUPADDMEMBER pfUserDBGroupAddMember;
	#define GET_UserDBGroupAddMember(fl)  s_pfCMGetAPI2( "UserDBGroupAddMember", (RTS_VOID_FCTPTR *)&pfUserDBGroupAddMember, (fl), 0, 0)
	#define CAL_UserDBGroupAddMember  pfUserDBGroupAddMember
	#define CHK_UserDBGroupAddMember  (pfUserDBGroupAddMember != NULL)
	#define EXP_UserDBGroupAddMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupAddMember", (RTS_UINTPTR)UserDBGroupAddMember, 0, 0) 
#endif




/**
 * <description>Remove a group as a member from another group. So the group is no longer derived from the first one</description>
 * <param name="hGroup" type="IN">First group to remove the derived group from</param>
 * <param name="hGroupMember" type="IN">Member group which is no longer derived from the first group (hGroup) after this operation</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. hGroup or hGroupMember invalid</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 */
 RTS_RESULT CDECL UserDBGroupRemoveMember(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPREMOVEMEMBER) (RTS_HANDLE hGroup, RTS_HANDLE hGroupMember);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPREMOVEMEMBER_NOTIMPLEMENTED)
	#define USE_UserDBGroupRemoveMember
	#define EXT_UserDBGroupRemoveMember
	#define GET_UserDBGroupRemoveMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupRemoveMember(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupRemoveMember  FALSE
	#define EXP_UserDBGroupRemoveMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupRemoveMember
	#define EXT_UserDBGroupRemoveMember
	#define GET_UserDBGroupRemoveMember(fl)  CAL_CMGETAPI( "UserDBGroupRemoveMember" ) 
	#define CAL_UserDBGroupRemoveMember  UserDBGroupRemoveMember
	#define CHK_UserDBGroupRemoveMember  TRUE
	#define EXP_UserDBGroupRemoveMember  CAL_CMEXPAPI( "UserDBGroupRemoveMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupRemoveMember
	#define EXT_UserDBGroupRemoveMember
	#define GET_UserDBGroupRemoveMember(fl)  CAL_CMGETAPI( "UserDBGroupRemoveMember" ) 
	#define CAL_UserDBGroupRemoveMember  UserDBGroupRemoveMember
	#define CHK_UserDBGroupRemoveMember  TRUE
	#define EXP_UserDBGroupRemoveMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupRemoveMember", (RTS_UINTPTR)UserDBGroupRemoveMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupRemoveMember
	#define EXT_CmpUserDBUserDBGroupRemoveMember
	#define GET_CmpUserDBUserDBGroupRemoveMember  ERR_OK
	#define CAL_CmpUserDBUserDBGroupRemoveMember pICmpUserDB->IUserDBGroupRemoveMember
	#define CHK_CmpUserDBUserDBGroupRemoveMember (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupRemoveMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupRemoveMember
	#define EXT_UserDBGroupRemoveMember
	#define GET_UserDBGroupRemoveMember(fl)  CAL_CMGETAPI( "UserDBGroupRemoveMember" ) 
	#define CAL_UserDBGroupRemoveMember pICmpUserDB->IUserDBGroupRemoveMember
	#define CHK_UserDBGroupRemoveMember (pICmpUserDB != NULL)
	#define EXP_UserDBGroupRemoveMember  CAL_CMEXPAPI( "UserDBGroupRemoveMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupRemoveMember  PFUSERDBGROUPREMOVEMEMBER pfUserDBGroupRemoveMember;
	#define EXT_UserDBGroupRemoveMember  extern PFUSERDBGROUPREMOVEMEMBER pfUserDBGroupRemoveMember;
	#define GET_UserDBGroupRemoveMember(fl)  s_pfCMGetAPI2( "UserDBGroupRemoveMember", (RTS_VOID_FCTPTR *)&pfUserDBGroupRemoveMember, (fl), 0, 0)
	#define CAL_UserDBGroupRemoveMember  pfUserDBGroupRemoveMember
	#define CHK_UserDBGroupRemoveMember  (pfUserDBGroupRemoveMember != NULL)
	#define EXP_UserDBGroupRemoveMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupRemoveMember", (RTS_UINTPTR)UserDBGroupRemoveMember, 0, 0) 
#endif





/* --------- Group management ------------------------------------------------ */
/* This section of functions is MANDATORY for the user management!             */

/* Group iteration */

/**
 * <description>Iteration interface to get the first configured user group</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user group configured</errorcode>
 * <result>Handle to the first user group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETFIRST_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetFirst
	#define EXT_UserDBGroupGetFirst
	#define GET_UserDBGroupGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupGetFirst  FALSE
	#define EXP_UserDBGroupGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetFirst
	#define EXT_UserDBGroupGetFirst
	#define GET_UserDBGroupGetFirst(fl)  CAL_CMGETAPI( "UserDBGroupGetFirst" ) 
	#define CAL_UserDBGroupGetFirst  UserDBGroupGetFirst
	#define CHK_UserDBGroupGetFirst  TRUE
	#define EXP_UserDBGroupGetFirst  CAL_CMEXPAPI( "UserDBGroupGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetFirst
	#define EXT_UserDBGroupGetFirst
	#define GET_UserDBGroupGetFirst(fl)  CAL_CMGETAPI( "UserDBGroupGetFirst" ) 
	#define CAL_UserDBGroupGetFirst  UserDBGroupGetFirst
	#define CHK_UserDBGroupGetFirst  TRUE
	#define EXP_UserDBGroupGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetFirst", (RTS_UINTPTR)UserDBGroupGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetFirst
	#define EXT_CmpUserDBUserDBGroupGetFirst
	#define GET_CmpUserDBUserDBGroupGetFirst  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetFirst pICmpUserDB->IUserDBGroupGetFirst
	#define CHK_CmpUserDBUserDBGroupGetFirst (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetFirst
	#define EXT_UserDBGroupGetFirst
	#define GET_UserDBGroupGetFirst(fl)  CAL_CMGETAPI( "UserDBGroupGetFirst" ) 
	#define CAL_UserDBGroupGetFirst pICmpUserDB->IUserDBGroupGetFirst
	#define CHK_UserDBGroupGetFirst (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetFirst  CAL_CMEXPAPI( "UserDBGroupGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetFirst  PFUSERDBGROUPGETFIRST pfUserDBGroupGetFirst;
	#define EXT_UserDBGroupGetFirst  extern PFUSERDBGROUPGETFIRST pfUserDBGroupGetFirst;
	#define GET_UserDBGroupGetFirst(fl)  s_pfCMGetAPI2( "UserDBGroupGetFirst", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetFirst, (fl), 0, 0)
	#define CAL_UserDBGroupGetFirst  pfUserDBGroupGetFirst
	#define CHK_UserDBGroupGetFirst  (pfUserDBGroupGetFirst != NULL)
	#define EXP_UserDBGroupGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetFirst", (RTS_UINTPTR)UserDBGroupGetFirst, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next configured user group. Must be started with UserDBGroupGetFirst()</description>
 * <param name="hPrevGroup" type="IN">Handle to the previous user group retrieved via UserDBGroupGetFirst() or subsequent calls of UserDBGroupGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user group available</errorcode>
 * <result>Handle to the next user group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupGetNext(RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPGETNEXT) (RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETNEXT_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetNext
	#define EXT_UserDBGroupGetNext
	#define GET_UserDBGroupGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupGetNext  FALSE
	#define EXP_UserDBGroupGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetNext
	#define EXT_UserDBGroupGetNext
	#define GET_UserDBGroupGetNext(fl)  CAL_CMGETAPI( "UserDBGroupGetNext" ) 
	#define CAL_UserDBGroupGetNext  UserDBGroupGetNext
	#define CHK_UserDBGroupGetNext  TRUE
	#define EXP_UserDBGroupGetNext  CAL_CMEXPAPI( "UserDBGroupGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetNext
	#define EXT_UserDBGroupGetNext
	#define GET_UserDBGroupGetNext(fl)  CAL_CMGETAPI( "UserDBGroupGetNext" ) 
	#define CAL_UserDBGroupGetNext  UserDBGroupGetNext
	#define CHK_UserDBGroupGetNext  TRUE
	#define EXP_UserDBGroupGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetNext", (RTS_UINTPTR)UserDBGroupGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetNext
	#define EXT_CmpUserDBUserDBGroupGetNext
	#define GET_CmpUserDBUserDBGroupGetNext  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetNext pICmpUserDB->IUserDBGroupGetNext
	#define CHK_CmpUserDBUserDBGroupGetNext (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetNext
	#define EXT_UserDBGroupGetNext
	#define GET_UserDBGroupGetNext(fl)  CAL_CMGETAPI( "UserDBGroupGetNext" ) 
	#define CAL_UserDBGroupGetNext pICmpUserDB->IUserDBGroupGetNext
	#define CHK_UserDBGroupGetNext (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetNext  CAL_CMEXPAPI( "UserDBGroupGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetNext  PFUSERDBGROUPGETNEXT pfUserDBGroupGetNext;
	#define EXT_UserDBGroupGetNext  extern PFUSERDBGROUPGETNEXT pfUserDBGroupGetNext;
	#define GET_UserDBGroupGetNext(fl)  s_pfCMGetAPI2( "UserDBGroupGetNext", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetNext, (fl), 0, 0)
	#define CAL_UserDBGroupGetNext  pfUserDBGroupGetNext
	#define CHK_UserDBGroupGetNext  (pfUserDBGroupGetNext != NULL)
	#define EXP_UserDBGroupGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetNext", (RTS_UINTPTR)UserDBGroupGetNext, 0, 0) 
#endif




/* Single group access */

/**
 * <description>Open user group specified by its name</description>
 * <param name="pszGroup" type="IN">User group name</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszGroup = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the user group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupOpen(char *pszGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPOPEN) (char *pszGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPOPEN_NOTIMPLEMENTED)
	#define USE_UserDBGroupOpen
	#define EXT_UserDBGroupOpen
	#define GET_UserDBGroupOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupOpen  FALSE
	#define EXP_UserDBGroupOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupOpen
	#define EXT_UserDBGroupOpen
	#define GET_UserDBGroupOpen(fl)  CAL_CMGETAPI( "UserDBGroupOpen" ) 
	#define CAL_UserDBGroupOpen  UserDBGroupOpen
	#define CHK_UserDBGroupOpen  TRUE
	#define EXP_UserDBGroupOpen  CAL_CMEXPAPI( "UserDBGroupOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupOpen
	#define EXT_UserDBGroupOpen
	#define GET_UserDBGroupOpen(fl)  CAL_CMGETAPI( "UserDBGroupOpen" ) 
	#define CAL_UserDBGroupOpen  UserDBGroupOpen
	#define CHK_UserDBGroupOpen  TRUE
	#define EXP_UserDBGroupOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupOpen", (RTS_UINTPTR)UserDBGroupOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupOpen
	#define EXT_CmpUserDBUserDBGroupOpen
	#define GET_CmpUserDBUserDBGroupOpen  ERR_OK
	#define CAL_CmpUserDBUserDBGroupOpen pICmpUserDB->IUserDBGroupOpen
	#define CHK_CmpUserDBUserDBGroupOpen (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupOpen
	#define EXT_UserDBGroupOpen
	#define GET_UserDBGroupOpen(fl)  CAL_CMGETAPI( "UserDBGroupOpen" ) 
	#define CAL_UserDBGroupOpen pICmpUserDB->IUserDBGroupOpen
	#define CHK_UserDBGroupOpen (pICmpUserDB != NULL)
	#define EXP_UserDBGroupOpen  CAL_CMEXPAPI( "UserDBGroupOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupOpen  PFUSERDBGROUPOPEN pfUserDBGroupOpen;
	#define EXT_UserDBGroupOpen  extern PFUSERDBGROUPOPEN pfUserDBGroupOpen;
	#define GET_UserDBGroupOpen(fl)  s_pfCMGetAPI2( "UserDBGroupOpen", (RTS_VOID_FCTPTR *)&pfUserDBGroupOpen, (fl), 0, 0)
	#define CAL_UserDBGroupOpen  pfUserDBGroupOpen
	#define CHK_UserDBGroupOpen  (pfUserDBGroupOpen != NULL)
	#define EXP_UserDBGroupOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupOpen", (RTS_UINTPTR)UserDBGroupOpen, 0, 0) 
#endif




/**
 * <description>Close a user group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handle</errorcode>
 */
RTS_RESULT CDECL UserDBGroupClose(RTS_HANDLE hGroup);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPCLOSE) (RTS_HANDLE hGroup);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPCLOSE_NOTIMPLEMENTED)
	#define USE_UserDBGroupClose
	#define EXT_UserDBGroupClose
	#define GET_UserDBGroupClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupClose  FALSE
	#define EXP_UserDBGroupClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupClose
	#define EXT_UserDBGroupClose
	#define GET_UserDBGroupClose(fl)  CAL_CMGETAPI( "UserDBGroupClose" ) 
	#define CAL_UserDBGroupClose  UserDBGroupClose
	#define CHK_UserDBGroupClose  TRUE
	#define EXP_UserDBGroupClose  CAL_CMEXPAPI( "UserDBGroupClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupClose
	#define EXT_UserDBGroupClose
	#define GET_UserDBGroupClose(fl)  CAL_CMGETAPI( "UserDBGroupClose" ) 
	#define CAL_UserDBGroupClose  UserDBGroupClose
	#define CHK_UserDBGroupClose  TRUE
	#define EXP_UserDBGroupClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupClose", (RTS_UINTPTR)UserDBGroupClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupClose
	#define EXT_CmpUserDBUserDBGroupClose
	#define GET_CmpUserDBUserDBGroupClose  ERR_OK
	#define CAL_CmpUserDBUserDBGroupClose pICmpUserDB->IUserDBGroupClose
	#define CHK_CmpUserDBUserDBGroupClose (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupClose
	#define EXT_UserDBGroupClose
	#define GET_UserDBGroupClose(fl)  CAL_CMGETAPI( "UserDBGroupClose" ) 
	#define CAL_UserDBGroupClose pICmpUserDB->IUserDBGroupClose
	#define CHK_UserDBGroupClose (pICmpUserDB != NULL)
	#define EXP_UserDBGroupClose  CAL_CMEXPAPI( "UserDBGroupClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupClose  PFUSERDBGROUPCLOSE pfUserDBGroupClose;
	#define EXT_UserDBGroupClose  extern PFUSERDBGROUPCLOSE pfUserDBGroupClose;
	#define GET_UserDBGroupClose(fl)  s_pfCMGetAPI2( "UserDBGroupClose", (RTS_VOID_FCTPTR *)&pfUserDBGroupClose, (fl), 0, 0)
	#define CAL_UserDBGroupClose  pfUserDBGroupClose
	#define CHK_UserDBGroupClose  (pfUserDBGroupClose != NULL)
	#define EXP_UserDBGroupClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupClose", (RTS_UINTPTR)UserDBGroupClose, 0, 0) 
#endif




/**
 * <description>Get user group name</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="pszGroup" type="OUT">Pointer to get user group name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszGroup. If pszGroup = NULL, only the length of the user group name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handle or pszGroup = NULL and piMaxLen = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBGroupGetName(RTS_HANDLE hGroup, char *pszGroup, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPGETNAME) (RTS_HANDLE hGroup, char *pszGroup, int *piMaxLen);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETNAME_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetName
	#define EXT_UserDBGroupGetName
	#define GET_UserDBGroupGetName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetName(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupGetName  FALSE
	#define EXP_UserDBGroupGetName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetName
	#define EXT_UserDBGroupGetName
	#define GET_UserDBGroupGetName(fl)  CAL_CMGETAPI( "UserDBGroupGetName" ) 
	#define CAL_UserDBGroupGetName  UserDBGroupGetName
	#define CHK_UserDBGroupGetName  TRUE
	#define EXP_UserDBGroupGetName  CAL_CMEXPAPI( "UserDBGroupGetName" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetName
	#define EXT_UserDBGroupGetName
	#define GET_UserDBGroupGetName(fl)  CAL_CMGETAPI( "UserDBGroupGetName" ) 
	#define CAL_UserDBGroupGetName  UserDBGroupGetName
	#define CHK_UserDBGroupGetName  TRUE
	#define EXP_UserDBGroupGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetName", (RTS_UINTPTR)UserDBGroupGetName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetName
	#define EXT_CmpUserDBUserDBGroupGetName
	#define GET_CmpUserDBUserDBGroupGetName  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetName pICmpUserDB->IUserDBGroupGetName
	#define CHK_CmpUserDBUserDBGroupGetName (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetName
	#define EXT_UserDBGroupGetName
	#define GET_UserDBGroupGetName(fl)  CAL_CMGETAPI( "UserDBGroupGetName" ) 
	#define CAL_UserDBGroupGetName pICmpUserDB->IUserDBGroupGetName
	#define CHK_UserDBGroupGetName (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetName  CAL_CMEXPAPI( "UserDBGroupGetName" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetName  PFUSERDBGROUPGETNAME pfUserDBGroupGetName;
	#define EXT_UserDBGroupGetName  extern PFUSERDBGROUPGETNAME pfUserDBGroupGetName;
	#define GET_UserDBGroupGetName(fl)  s_pfCMGetAPI2( "UserDBGroupGetName", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetName, (fl), 0, 0)
	#define CAL_UserDBGroupGetName  pfUserDBGroupGetName
	#define CHK_UserDBGroupGetName  (pfUserDBGroupGetName != NULL)
	#define EXP_UserDBGroupGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetName", (RTS_UINTPTR)UserDBGroupGetName, 0, 0) 
#endif




/**
 * <description>Get properties of a group</description>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <param name="pulProperty" type="OUT">Pointer to return the properties. For details see category "UserDB properties"</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Properties could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group or property pointer = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBGroupGetProperty(RTS_HANDLE hGroup, RTS_UI32 *pulProperty);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPGETPROPERTY) (RTS_HANDLE hGroup, RTS_UI32 *pulProperty);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETPROPERTY_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetProperty
	#define EXT_UserDBGroupGetProperty
	#define GET_UserDBGroupGetProperty(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetProperty(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupGetProperty  FALSE
	#define EXP_UserDBGroupGetProperty  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetProperty
	#define EXT_UserDBGroupGetProperty
	#define GET_UserDBGroupGetProperty(fl)  CAL_CMGETAPI( "UserDBGroupGetProperty" ) 
	#define CAL_UserDBGroupGetProperty  UserDBGroupGetProperty
	#define CHK_UserDBGroupGetProperty  TRUE
	#define EXP_UserDBGroupGetProperty  CAL_CMEXPAPI( "UserDBGroupGetProperty" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetProperty
	#define EXT_UserDBGroupGetProperty
	#define GET_UserDBGroupGetProperty(fl)  CAL_CMGETAPI( "UserDBGroupGetProperty" ) 
	#define CAL_UserDBGroupGetProperty  UserDBGroupGetProperty
	#define CHK_UserDBGroupGetProperty  TRUE
	#define EXP_UserDBGroupGetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetProperty", (RTS_UINTPTR)UserDBGroupGetProperty, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetProperty
	#define EXT_CmpUserDBUserDBGroupGetProperty
	#define GET_CmpUserDBUserDBGroupGetProperty  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetProperty pICmpUserDB->IUserDBGroupGetProperty
	#define CHK_CmpUserDBUserDBGroupGetProperty (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetProperty  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetProperty
	#define EXT_UserDBGroupGetProperty
	#define GET_UserDBGroupGetProperty(fl)  CAL_CMGETAPI( "UserDBGroupGetProperty" ) 
	#define CAL_UserDBGroupGetProperty pICmpUserDB->IUserDBGroupGetProperty
	#define CHK_UserDBGroupGetProperty (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetProperty  CAL_CMEXPAPI( "UserDBGroupGetProperty" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetProperty  PFUSERDBGROUPGETPROPERTY pfUserDBGroupGetProperty;
	#define EXT_UserDBGroupGetProperty  extern PFUSERDBGROUPGETPROPERTY pfUserDBGroupGetProperty;
	#define GET_UserDBGroupGetProperty(fl)  s_pfCMGetAPI2( "UserDBGroupGetProperty", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetProperty, (fl), 0, 0)
	#define CAL_UserDBGroupGetProperty  pfUserDBGroupGetProperty
	#define CHK_UserDBGroupGetProperty  (pfUserDBGroupGetProperty != NULL)
	#define EXP_UserDBGroupGetProperty  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetProperty", (RTS_UINTPTR)UserDBGroupGetProperty, 0, 0) 
#endif




/**
 * <description>Check if the user is a member of the group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="hUser" type="IN">Handle to the user</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User is a member of the group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user or user group handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">User is no member of the specified user group</errorcode>
 */
RTS_RESULT CDECL UserDBGroupHasUser(RTS_HANDLE hGroup, RTS_HANDLE hUser);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPHASUSER) (RTS_HANDLE hGroup, RTS_HANDLE hUser);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPHASUSER_NOTIMPLEMENTED)
	#define USE_UserDBGroupHasUser
	#define EXT_UserDBGroupHasUser
	#define GET_UserDBGroupHasUser(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupHasUser(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupHasUser  FALSE
	#define EXP_UserDBGroupHasUser  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupHasUser
	#define EXT_UserDBGroupHasUser
	#define GET_UserDBGroupHasUser(fl)  CAL_CMGETAPI( "UserDBGroupHasUser" ) 
	#define CAL_UserDBGroupHasUser  UserDBGroupHasUser
	#define CHK_UserDBGroupHasUser  TRUE
	#define EXP_UserDBGroupHasUser  CAL_CMEXPAPI( "UserDBGroupHasUser" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupHasUser
	#define EXT_UserDBGroupHasUser
	#define GET_UserDBGroupHasUser(fl)  CAL_CMGETAPI( "UserDBGroupHasUser" ) 
	#define CAL_UserDBGroupHasUser  UserDBGroupHasUser
	#define CHK_UserDBGroupHasUser  TRUE
	#define EXP_UserDBGroupHasUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupHasUser", (RTS_UINTPTR)UserDBGroupHasUser, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupHasUser
	#define EXT_CmpUserDBUserDBGroupHasUser
	#define GET_CmpUserDBUserDBGroupHasUser  ERR_OK
	#define CAL_CmpUserDBUserDBGroupHasUser pICmpUserDB->IUserDBGroupHasUser
	#define CHK_CmpUserDBUserDBGroupHasUser (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupHasUser  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupHasUser
	#define EXT_UserDBGroupHasUser
	#define GET_UserDBGroupHasUser(fl)  CAL_CMGETAPI( "UserDBGroupHasUser" ) 
	#define CAL_UserDBGroupHasUser pICmpUserDB->IUserDBGroupHasUser
	#define CHK_UserDBGroupHasUser (pICmpUserDB != NULL)
	#define EXP_UserDBGroupHasUser  CAL_CMEXPAPI( "UserDBGroupHasUser" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupHasUser  PFUSERDBGROUPHASUSER pfUserDBGroupHasUser;
	#define EXT_UserDBGroupHasUser  extern PFUSERDBGROUPHASUSER pfUserDBGroupHasUser;
	#define GET_UserDBGroupHasUser(fl)  s_pfCMGetAPI2( "UserDBGroupHasUser", (RTS_VOID_FCTPTR *)&pfUserDBGroupHasUser, (fl), 0, 0)
	#define CAL_UserDBGroupHasUser  pfUserDBGroupHasUser
	#define CHK_UserDBGroupHasUser  (pfUserDBGroupHasUser != NULL)
	#define EXP_UserDBGroupHasUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupHasUser", (RTS_UINTPTR)UserDBGroupHasUser, 0, 0) 
#endif




/**
 * <description>Iteration interface to get the first user of the user group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user in the group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user configured in the user group</errorcode>
 * <result>Handle to the first user in the user group or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupGetFirstUser(RTS_HANDLE hGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPGETFIRSTUSER) (RTS_HANDLE hGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETFIRSTUSER_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetFirstUser
	#define EXT_UserDBGroupGetFirstUser
	#define GET_UserDBGroupGetFirstUser(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetFirstUser(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupGetFirstUser  FALSE
	#define EXP_UserDBGroupGetFirstUser  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetFirstUser
	#define EXT_UserDBGroupGetFirstUser
	#define GET_UserDBGroupGetFirstUser(fl)  CAL_CMGETAPI( "UserDBGroupGetFirstUser" ) 
	#define CAL_UserDBGroupGetFirstUser  UserDBGroupGetFirstUser
	#define CHK_UserDBGroupGetFirstUser  TRUE
	#define EXP_UserDBGroupGetFirstUser  CAL_CMEXPAPI( "UserDBGroupGetFirstUser" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetFirstUser
	#define EXT_UserDBGroupGetFirstUser
	#define GET_UserDBGroupGetFirstUser(fl)  CAL_CMGETAPI( "UserDBGroupGetFirstUser" ) 
	#define CAL_UserDBGroupGetFirstUser  UserDBGroupGetFirstUser
	#define CHK_UserDBGroupGetFirstUser  TRUE
	#define EXP_UserDBGroupGetFirstUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetFirstUser", (RTS_UINTPTR)UserDBGroupGetFirstUser, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetFirstUser
	#define EXT_CmpUserDBUserDBGroupGetFirstUser
	#define GET_CmpUserDBUserDBGroupGetFirstUser  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetFirstUser pICmpUserDB->IUserDBGroupGetFirstUser
	#define CHK_CmpUserDBUserDBGroupGetFirstUser (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetFirstUser  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetFirstUser
	#define EXT_UserDBGroupGetFirstUser
	#define GET_UserDBGroupGetFirstUser(fl)  CAL_CMGETAPI( "UserDBGroupGetFirstUser" ) 
	#define CAL_UserDBGroupGetFirstUser pICmpUserDB->IUserDBGroupGetFirstUser
	#define CHK_UserDBGroupGetFirstUser (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetFirstUser  CAL_CMEXPAPI( "UserDBGroupGetFirstUser" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetFirstUser  PFUSERDBGROUPGETFIRSTUSER pfUserDBGroupGetFirstUser;
	#define EXT_UserDBGroupGetFirstUser  extern PFUSERDBGROUPGETFIRSTUSER pfUserDBGroupGetFirstUser;
	#define GET_UserDBGroupGetFirstUser(fl)  s_pfCMGetAPI2( "UserDBGroupGetFirstUser", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetFirstUser, (fl), 0, 0)
	#define CAL_UserDBGroupGetFirstUser  pfUserDBGroupGetFirstUser
	#define CHK_UserDBGroupGetFirstUser  (pfUserDBGroupGetFirstUser != NULL)
	#define EXP_UserDBGroupGetFirstUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetFirstUser", (RTS_UINTPTR)UserDBGroupGetFirstUser, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next configured user of the user group. Must be started with UserDBGroupGetFirstUser()</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="hPrevUser" type="IN">Handle to the previous user retrieved via UserDBGroupGetFirstUser() or subsequent calls of UserDBGroupGetNextUser()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user available</errorcode>
 * <result>Handle to the next user or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupGetNextUser(RTS_HANDLE hGroup, RTS_HANDLE hPrevUser, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPGETNEXTUSER) (RTS_HANDLE hGroup, RTS_HANDLE hPrevUser, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETNEXTUSER_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetNextUser
	#define EXT_UserDBGroupGetNextUser
	#define GET_UserDBGroupGetNextUser(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetNextUser(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupGetNextUser  FALSE
	#define EXP_UserDBGroupGetNextUser  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetNextUser
	#define EXT_UserDBGroupGetNextUser
	#define GET_UserDBGroupGetNextUser(fl)  CAL_CMGETAPI( "UserDBGroupGetNextUser" ) 
	#define CAL_UserDBGroupGetNextUser  UserDBGroupGetNextUser
	#define CHK_UserDBGroupGetNextUser  TRUE
	#define EXP_UserDBGroupGetNextUser  CAL_CMEXPAPI( "UserDBGroupGetNextUser" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetNextUser
	#define EXT_UserDBGroupGetNextUser
	#define GET_UserDBGroupGetNextUser(fl)  CAL_CMGETAPI( "UserDBGroupGetNextUser" ) 
	#define CAL_UserDBGroupGetNextUser  UserDBGroupGetNextUser
	#define CHK_UserDBGroupGetNextUser  TRUE
	#define EXP_UserDBGroupGetNextUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetNextUser", (RTS_UINTPTR)UserDBGroupGetNextUser, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetNextUser
	#define EXT_CmpUserDBUserDBGroupGetNextUser
	#define GET_CmpUserDBUserDBGroupGetNextUser  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetNextUser pICmpUserDB->IUserDBGroupGetNextUser
	#define CHK_CmpUserDBUserDBGroupGetNextUser (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetNextUser  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetNextUser
	#define EXT_UserDBGroupGetNextUser
	#define GET_UserDBGroupGetNextUser(fl)  CAL_CMGETAPI( "UserDBGroupGetNextUser" ) 
	#define CAL_UserDBGroupGetNextUser pICmpUserDB->IUserDBGroupGetNextUser
	#define CHK_UserDBGroupGetNextUser (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetNextUser  CAL_CMEXPAPI( "UserDBGroupGetNextUser" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetNextUser  PFUSERDBGROUPGETNEXTUSER pfUserDBGroupGetNextUser;
	#define EXT_UserDBGroupGetNextUser  extern PFUSERDBGROUPGETNEXTUSER pfUserDBGroupGetNextUser;
	#define GET_UserDBGroupGetNextUser(fl)  s_pfCMGetAPI2( "UserDBGroupGetNextUser", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetNextUser, (fl), 0, 0)
	#define CAL_UserDBGroupGetNextUser  pfUserDBGroupGetNextUser
	#define CHK_UserDBGroupGetNextUser  (pfUserDBGroupGetNextUser != NULL)
	#define EXP_UserDBGroupGetNextUser  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetNextUser", (RTS_UINTPTR)UserDBGroupGetNextUser, 0, 0) 
#endif




/**
 * <description>Check if a user group is a member of the first specified group</description>
 * <param name="hGroup" type="IN">Handle to the first user group</param>
 * <param name="hGroupMember" type="IN">Handle to the user group to check if it is a member of hGroup</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">User group is a member of the first group</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">User group is no member of the specified user group</errorcode>
 */
RTS_RESULT CDECL UserDBGroupHasMember(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember);
typedef RTS_RESULT (CDECL * PFUSERDBGROUPHASMEMBER) (RTS_HANDLE hGroup, RTS_HANDLE hGroupMember);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPHASMEMBER_NOTIMPLEMENTED)
	#define USE_UserDBGroupHasMember
	#define EXT_UserDBGroupHasMember
	#define GET_UserDBGroupHasMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupHasMember(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBGroupHasMember  FALSE
	#define EXP_UserDBGroupHasMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupHasMember
	#define EXT_UserDBGroupHasMember
	#define GET_UserDBGroupHasMember(fl)  CAL_CMGETAPI( "UserDBGroupHasMember" ) 
	#define CAL_UserDBGroupHasMember  UserDBGroupHasMember
	#define CHK_UserDBGroupHasMember  TRUE
	#define EXP_UserDBGroupHasMember  CAL_CMEXPAPI( "UserDBGroupHasMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupHasMember
	#define EXT_UserDBGroupHasMember
	#define GET_UserDBGroupHasMember(fl)  CAL_CMGETAPI( "UserDBGroupHasMember" ) 
	#define CAL_UserDBGroupHasMember  UserDBGroupHasMember
	#define CHK_UserDBGroupHasMember  TRUE
	#define EXP_UserDBGroupHasMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupHasMember", (RTS_UINTPTR)UserDBGroupHasMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupHasMember
	#define EXT_CmpUserDBUserDBGroupHasMember
	#define GET_CmpUserDBUserDBGroupHasMember  ERR_OK
	#define CAL_CmpUserDBUserDBGroupHasMember pICmpUserDB->IUserDBGroupHasMember
	#define CHK_CmpUserDBUserDBGroupHasMember (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupHasMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupHasMember
	#define EXT_UserDBGroupHasMember
	#define GET_UserDBGroupHasMember(fl)  CAL_CMGETAPI( "UserDBGroupHasMember" ) 
	#define CAL_UserDBGroupHasMember pICmpUserDB->IUserDBGroupHasMember
	#define CHK_UserDBGroupHasMember (pICmpUserDB != NULL)
	#define EXP_UserDBGroupHasMember  CAL_CMEXPAPI( "UserDBGroupHasMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupHasMember  PFUSERDBGROUPHASMEMBER pfUserDBGroupHasMember;
	#define EXT_UserDBGroupHasMember  extern PFUSERDBGROUPHASMEMBER pfUserDBGroupHasMember;
	#define GET_UserDBGroupHasMember(fl)  s_pfCMGetAPI2( "UserDBGroupHasMember", (RTS_VOID_FCTPTR *)&pfUserDBGroupHasMember, (fl), 0, 0)
	#define CAL_UserDBGroupHasMember  pfUserDBGroupHasMember
	#define CHK_UserDBGroupHasMember  (pfUserDBGroupHasMember != NULL)
	#define EXP_UserDBGroupHasMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupHasMember", (RTS_UINTPTR)UserDBGroupHasMember, 0, 0) 
#endif




/**
 * <description>Iteration interface to get the first user group as member of the specified group</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First user group member available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid user group handle</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No user group configured</errorcode>
 * <result>Handle to the first user group member or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupGetFirstMember(RTS_HANDLE hGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPGETFIRSTMEMBER) (RTS_HANDLE hGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETFIRSTMEMBER_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetFirstMember
	#define EXT_UserDBGroupGetFirstMember
	#define GET_UserDBGroupGetFirstMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetFirstMember(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupGetFirstMember  FALSE
	#define EXP_UserDBGroupGetFirstMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetFirstMember
	#define EXT_UserDBGroupGetFirstMember
	#define GET_UserDBGroupGetFirstMember(fl)  CAL_CMGETAPI( "UserDBGroupGetFirstMember" ) 
	#define CAL_UserDBGroupGetFirstMember  UserDBGroupGetFirstMember
	#define CHK_UserDBGroupGetFirstMember  TRUE
	#define EXP_UserDBGroupGetFirstMember  CAL_CMEXPAPI( "UserDBGroupGetFirstMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetFirstMember
	#define EXT_UserDBGroupGetFirstMember
	#define GET_UserDBGroupGetFirstMember(fl)  CAL_CMGETAPI( "UserDBGroupGetFirstMember" ) 
	#define CAL_UserDBGroupGetFirstMember  UserDBGroupGetFirstMember
	#define CHK_UserDBGroupGetFirstMember  TRUE
	#define EXP_UserDBGroupGetFirstMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetFirstMember", (RTS_UINTPTR)UserDBGroupGetFirstMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetFirstMember
	#define EXT_CmpUserDBUserDBGroupGetFirstMember
	#define GET_CmpUserDBUserDBGroupGetFirstMember  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetFirstMember pICmpUserDB->IUserDBGroupGetFirstMember
	#define CHK_CmpUserDBUserDBGroupGetFirstMember (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetFirstMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetFirstMember
	#define EXT_UserDBGroupGetFirstMember
	#define GET_UserDBGroupGetFirstMember(fl)  CAL_CMGETAPI( "UserDBGroupGetFirstMember" ) 
	#define CAL_UserDBGroupGetFirstMember pICmpUserDB->IUserDBGroupGetFirstMember
	#define CHK_UserDBGroupGetFirstMember (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetFirstMember  CAL_CMEXPAPI( "UserDBGroupGetFirstMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetFirstMember  PFUSERDBGROUPGETFIRSTMEMBER pfUserDBGroupGetFirstMember;
	#define EXT_UserDBGroupGetFirstMember  extern PFUSERDBGROUPGETFIRSTMEMBER pfUserDBGroupGetFirstMember;
	#define GET_UserDBGroupGetFirstMember(fl)  s_pfCMGetAPI2( "UserDBGroupGetFirstMember", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetFirstMember, (fl), 0, 0)
	#define CAL_UserDBGroupGetFirstMember  pfUserDBGroupGetFirstMember
	#define CHK_UserDBGroupGetFirstMember  (pfUserDBGroupGetFirstMember != NULL)
	#define EXP_UserDBGroupGetFirstMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetFirstMember", (RTS_UINTPTR)UserDBGroupGetFirstMember, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next configured user group as member of the specified group. Must be started with UserDBGroupGetFirstMember()</description>
 * <param name="hGroup" type="IN">Handle to the user group</param>
 * <param name="hPrevGroupMember" type="IN">Handle to the previous user group retrieved via UserDBGroupGetFirstMember() or subsequent calls of UserDBGroupGetNextMember()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next user group member available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next user group member available</errorcode>
 * <result>Handle to the next user group member or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBGroupGetNextMember(RTS_HANDLE hGroup, RTS_HANDLE hPrevGroupMember, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBGROUPGETNEXTMEMBER) (RTS_HANDLE hGroup, RTS_HANDLE hPrevGroupMember, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBGROUPGETNEXTMEMBER_NOTIMPLEMENTED)
	#define USE_UserDBGroupGetNextMember
	#define EXT_UserDBGroupGetNextMember
	#define GET_UserDBGroupGetNextMember(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBGroupGetNextMember(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBGroupGetNextMember  FALSE
	#define EXP_UserDBGroupGetNextMember  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBGroupGetNextMember
	#define EXT_UserDBGroupGetNextMember
	#define GET_UserDBGroupGetNextMember(fl)  CAL_CMGETAPI( "UserDBGroupGetNextMember" ) 
	#define CAL_UserDBGroupGetNextMember  UserDBGroupGetNextMember
	#define CHK_UserDBGroupGetNextMember  TRUE
	#define EXP_UserDBGroupGetNextMember  CAL_CMEXPAPI( "UserDBGroupGetNextMember" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBGroupGetNextMember
	#define EXT_UserDBGroupGetNextMember
	#define GET_UserDBGroupGetNextMember(fl)  CAL_CMGETAPI( "UserDBGroupGetNextMember" ) 
	#define CAL_UserDBGroupGetNextMember  UserDBGroupGetNextMember
	#define CHK_UserDBGroupGetNextMember  TRUE
	#define EXP_UserDBGroupGetNextMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetNextMember", (RTS_UINTPTR)UserDBGroupGetNextMember, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBGroupGetNextMember
	#define EXT_CmpUserDBUserDBGroupGetNextMember
	#define GET_CmpUserDBUserDBGroupGetNextMember  ERR_OK
	#define CAL_CmpUserDBUserDBGroupGetNextMember pICmpUserDB->IUserDBGroupGetNextMember
	#define CHK_CmpUserDBUserDBGroupGetNextMember (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBGroupGetNextMember  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBGroupGetNextMember
	#define EXT_UserDBGroupGetNextMember
	#define GET_UserDBGroupGetNextMember(fl)  CAL_CMGETAPI( "UserDBGroupGetNextMember" ) 
	#define CAL_UserDBGroupGetNextMember pICmpUserDB->IUserDBGroupGetNextMember
	#define CHK_UserDBGroupGetNextMember (pICmpUserDB != NULL)
	#define EXP_UserDBGroupGetNextMember  CAL_CMEXPAPI( "UserDBGroupGetNextMember" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBGroupGetNextMember  PFUSERDBGROUPGETNEXTMEMBER pfUserDBGroupGetNextMember;
	#define EXT_UserDBGroupGetNextMember  extern PFUSERDBGROUPGETNEXTMEMBER pfUserDBGroupGetNextMember;
	#define GET_UserDBGroupGetNextMember(fl)  s_pfCMGetAPI2( "UserDBGroupGetNextMember", (RTS_VOID_FCTPTR *)&pfUserDBGroupGetNextMember, (fl), 0, 0)
	#define CAL_UserDBGroupGetNextMember  pfUserDBGroupGetNextMember
	#define CHK_UserDBGroupGetNextMember  (pfUserDBGroupGetNextMember != NULL)
	#define EXP_UserDBGroupGetNextMember  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBGroupGetNextMember", (RTS_UINTPTR)UserDBGroupGetNextMember, 0, 0) 
#endif






/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */
/*                    Objects and Rights management																															*/
/* ------------------------------------------------------------------------------------------------------------------------------------------------------------------------ */

/* --------- Objects and Rights management configuration --------------------- */
/* This section of functions is MANDATORY and must be implemented			   */

/**
 * <description>Load the user rights database into memory</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error loading user rights database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
RTS_RESULT CDECL UserDBRightsLoad(void);
typedef RTS_RESULT (CDECL * PFUSERDBRIGHTSLOAD) (void);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBRIGHTSLOAD_NOTIMPLEMENTED)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRightsLoad()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRightsLoad  FALSE
	#define EXP_UserDBRightsLoad  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  CAL_CMGETAPI( "UserDBRightsLoad" ) 
	#define CAL_UserDBRightsLoad  UserDBRightsLoad
	#define CHK_UserDBRightsLoad  TRUE
	#define EXP_UserDBRightsLoad  CAL_CMEXPAPI( "UserDBRightsLoad" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  CAL_CMGETAPI( "UserDBRightsLoad" ) 
	#define CAL_UserDBRightsLoad  UserDBRightsLoad
	#define CHK_UserDBRightsLoad  TRUE
	#define EXP_UserDBRightsLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsLoad", (RTS_UINTPTR)UserDBRightsLoad, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBRightsLoad
	#define EXT_CmpUserDBUserDBRightsLoad
	#define GET_CmpUserDBUserDBRightsLoad  ERR_OK
	#define CAL_CmpUserDBUserDBRightsLoad pICmpUserDB->IUserDBRightsLoad
	#define CHK_CmpUserDBUserDBRightsLoad (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBRightsLoad  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRightsLoad
	#define EXT_UserDBRightsLoad
	#define GET_UserDBRightsLoad(fl)  CAL_CMGETAPI( "UserDBRightsLoad" ) 
	#define CAL_UserDBRightsLoad pICmpUserDB->IUserDBRightsLoad
	#define CHK_UserDBRightsLoad (pICmpUserDB != NULL)
	#define EXP_UserDBRightsLoad  CAL_CMEXPAPI( "UserDBRightsLoad" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRightsLoad  PFUSERDBRIGHTSLOAD pfUserDBRightsLoad;
	#define EXT_UserDBRightsLoad  extern PFUSERDBRIGHTSLOAD pfUserDBRightsLoad;
	#define GET_UserDBRightsLoad(fl)  s_pfCMGetAPI2( "UserDBRightsLoad", (RTS_VOID_FCTPTR *)&pfUserDBRightsLoad, (fl), 0, 0)
	#define CAL_UserDBRightsLoad  pfUserDBRightsLoad
	#define CHK_UserDBRightsLoad  (pfUserDBRightsLoad != NULL)
	#define EXP_UserDBRightsLoad  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsLoad", (RTS_UINTPTR)UserDBRightsLoad, 0, 0) 
#endif




/**
 * <description>Storing the current user rights management into permanent database file</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Error storing user rights database</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
RTS_RESULT CDECL UserDBRightsStore(void);
typedef RTS_RESULT (CDECL * PFUSERDBRIGHTSSTORE) (void);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBRIGHTSSTORE_NOTIMPLEMENTED)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRightsStore()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRightsStore  FALSE
	#define EXP_UserDBRightsStore  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  CAL_CMGETAPI( "UserDBRightsStore" ) 
	#define CAL_UserDBRightsStore  UserDBRightsStore
	#define CHK_UserDBRightsStore  TRUE
	#define EXP_UserDBRightsStore  CAL_CMEXPAPI( "UserDBRightsStore" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  CAL_CMGETAPI( "UserDBRightsStore" ) 
	#define CAL_UserDBRightsStore  UserDBRightsStore
	#define CHK_UserDBRightsStore  TRUE
	#define EXP_UserDBRightsStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsStore", (RTS_UINTPTR)UserDBRightsStore, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBRightsStore
	#define EXT_CmpUserDBUserDBRightsStore
	#define GET_CmpUserDBUserDBRightsStore  ERR_OK
	#define CAL_CmpUserDBUserDBRightsStore pICmpUserDB->IUserDBRightsStore
	#define CHK_CmpUserDBUserDBRightsStore (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBRightsStore  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRightsStore
	#define EXT_UserDBRightsStore
	#define GET_UserDBRightsStore(fl)  CAL_CMGETAPI( "UserDBRightsStore" ) 
	#define CAL_UserDBRightsStore pICmpUserDB->IUserDBRightsStore
	#define CHK_UserDBRightsStore (pICmpUserDB != NULL)
	#define EXP_UserDBRightsStore  CAL_CMEXPAPI( "UserDBRightsStore" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRightsStore  PFUSERDBRIGHTSSTORE pfUserDBRightsStore;
	#define EXT_UserDBRightsStore  extern PFUSERDBRIGHTSSTORE pfUserDBRightsStore;
	#define GET_UserDBRightsStore(fl)  s_pfCMGetAPI2( "UserDBRightsStore", (RTS_VOID_FCTPTR *)&pfUserDBRightsStore, (fl), 0, 0)
	#define CAL_UserDBRightsStore  pfUserDBRightsStore
	#define CHK_UserDBRightsStore  (pfUserDBRightsStore != NULL)
	#define EXP_UserDBRightsStore  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsStore", (RTS_UINTPTR)UserDBRightsStore, 0, 0) 
#endif




/**
 * <description>Release user rights management in memory. NOTE: The database file is not removed!</description>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Succeeded</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_FAILED">Failed releasing user rights management</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTIMPLEMENTED">Is not implemented perhaps the UserDBRights is fix</errorcode>
 */
RTS_RESULT CDECL UserDBRightsRelease(void);
typedef RTS_RESULT (CDECL * PFUSERDBRIGHTSRELEASE) (void);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBRIGHTSRELEASE_NOTIMPLEMENTED)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBRightsRelease()  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBRightsRelease  FALSE
	#define EXP_UserDBRightsRelease  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  CAL_CMGETAPI( "UserDBRightsRelease" ) 
	#define CAL_UserDBRightsRelease  UserDBRightsRelease
	#define CHK_UserDBRightsRelease  TRUE
	#define EXP_UserDBRightsRelease  CAL_CMEXPAPI( "UserDBRightsRelease" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  CAL_CMGETAPI( "UserDBRightsRelease" ) 
	#define CAL_UserDBRightsRelease  UserDBRightsRelease
	#define CHK_UserDBRightsRelease  TRUE
	#define EXP_UserDBRightsRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsRelease", (RTS_UINTPTR)UserDBRightsRelease, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBRightsRelease
	#define EXT_CmpUserDBUserDBRightsRelease
	#define GET_CmpUserDBUserDBRightsRelease  ERR_OK
	#define CAL_CmpUserDBUserDBRightsRelease pICmpUserDB->IUserDBRightsRelease
	#define CHK_CmpUserDBUserDBRightsRelease (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBRightsRelease  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBRightsRelease
	#define EXT_UserDBRightsRelease
	#define GET_UserDBRightsRelease(fl)  CAL_CMGETAPI( "UserDBRightsRelease" ) 
	#define CAL_UserDBRightsRelease pICmpUserDB->IUserDBRightsRelease
	#define CHK_UserDBRightsRelease (pICmpUserDB != NULL)
	#define EXP_UserDBRightsRelease  CAL_CMEXPAPI( "UserDBRightsRelease" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBRightsRelease  PFUSERDBRIGHTSRELEASE pfUserDBRightsRelease;
	#define EXT_UserDBRightsRelease  extern PFUSERDBRIGHTSRELEASE pfUserDBRightsRelease;
	#define GET_UserDBRightsRelease(fl)  s_pfCMGetAPI2( "UserDBRightsRelease", (RTS_VOID_FCTPTR *)&pfUserDBRightsRelease, (fl), 0, 0)
	#define CAL_UserDBRightsRelease  pfUserDBRightsRelease
	#define CHK_UserDBRightsRelease  (pfUserDBRightsRelease != NULL)
	#define EXP_UserDBRightsRelease  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBRightsRelease", (RTS_UINTPTR)UserDBRightsRelease, 0, 0) 
#endif




/* Objects management configuration */

/**
 * <description>
 *	Add a new object to the object management, so the access rights can be configured on that object.
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
RTS_HANDLE CDECL UserDBObjectAdd(char *pszObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTADD) (char *pszObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTADD_NOTIMPLEMENTED)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectAdd(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectAdd  FALSE
	#define EXP_UserDBObjectAdd  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  CAL_CMGETAPI( "UserDBObjectAdd" ) 
	#define CAL_UserDBObjectAdd  UserDBObjectAdd
	#define CHK_UserDBObjectAdd  TRUE
	#define EXP_UserDBObjectAdd  CAL_CMEXPAPI( "UserDBObjectAdd" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  CAL_CMGETAPI( "UserDBObjectAdd" ) 
	#define CAL_UserDBObjectAdd  UserDBObjectAdd
	#define CHK_UserDBObjectAdd  TRUE
	#define EXP_UserDBObjectAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAdd", (RTS_UINTPTR)UserDBObjectAdd, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectAdd
	#define EXT_CmpUserDBUserDBObjectAdd
	#define GET_CmpUserDBUserDBObjectAdd  ERR_OK
	#define CAL_CmpUserDBUserDBObjectAdd pICmpUserDB->IUserDBObjectAdd
	#define CHK_CmpUserDBUserDBObjectAdd (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectAdd  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectAdd
	#define EXT_UserDBObjectAdd
	#define GET_UserDBObjectAdd(fl)  CAL_CMGETAPI( "UserDBObjectAdd" ) 
	#define CAL_UserDBObjectAdd pICmpUserDB->IUserDBObjectAdd
	#define CHK_UserDBObjectAdd (pICmpUserDB != NULL)
	#define EXP_UserDBObjectAdd  CAL_CMEXPAPI( "UserDBObjectAdd" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectAdd  PFUSERDBOBJECTADD pfUserDBObjectAdd;
	#define EXT_UserDBObjectAdd  extern PFUSERDBOBJECTADD pfUserDBObjectAdd;
	#define GET_UserDBObjectAdd(fl)  s_pfCMGetAPI2( "UserDBObjectAdd", (RTS_VOID_FCTPTR *)&pfUserDBObjectAdd, (fl), 0, 0)
	#define CAL_UserDBObjectAdd  pfUserDBObjectAdd
	#define CHK_UserDBObjectAdd  (pfUserDBObjectAdd != NULL)
	#define EXP_UserDBObjectAdd  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAdd", (RTS_UINTPTR)UserDBObjectAdd, 0, 0) 
#endif




/**
 * <description>Remove an object from the object management and all its children</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectRemove(RTS_HANDLE hObject);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTREMOVE) (RTS_HANDLE hObject);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTREMOVE_NOTIMPLEMENTED)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectRemove(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectRemove  FALSE
	#define EXP_UserDBObjectRemove  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  CAL_CMGETAPI( "UserDBObjectRemove" ) 
	#define CAL_UserDBObjectRemove  UserDBObjectRemove
	#define CHK_UserDBObjectRemove  TRUE
	#define EXP_UserDBObjectRemove  CAL_CMEXPAPI( "UserDBObjectRemove" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  CAL_CMGETAPI( "UserDBObjectRemove" ) 
	#define CAL_UserDBObjectRemove  UserDBObjectRemove
	#define CHK_UserDBObjectRemove  TRUE
	#define EXP_UserDBObjectRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemove", (RTS_UINTPTR)UserDBObjectRemove, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectRemove
	#define EXT_CmpUserDBUserDBObjectRemove
	#define GET_CmpUserDBUserDBObjectRemove  ERR_OK
	#define CAL_CmpUserDBUserDBObjectRemove pICmpUserDB->IUserDBObjectRemove
	#define CHK_CmpUserDBUserDBObjectRemove (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectRemove  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectRemove
	#define EXT_UserDBObjectRemove
	#define GET_UserDBObjectRemove(fl)  CAL_CMGETAPI( "UserDBObjectRemove" ) 
	#define CAL_UserDBObjectRemove pICmpUserDB->IUserDBObjectRemove
	#define CHK_UserDBObjectRemove (pICmpUserDB != NULL)
	#define EXP_UserDBObjectRemove  CAL_CMEXPAPI( "UserDBObjectRemove" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectRemove  PFUSERDBOBJECTREMOVE pfUserDBObjectRemove;
	#define EXT_UserDBObjectRemove  extern PFUSERDBOBJECTREMOVE pfUserDBObjectRemove;
	#define GET_UserDBObjectRemove(fl)  s_pfCMGetAPI2( "UserDBObjectRemove", (RTS_VOID_FCTPTR *)&pfUserDBObjectRemove, (fl), 0, 0)
	#define CAL_UserDBObjectRemove  pfUserDBObjectRemove
	#define CHK_UserDBObjectRemove  (pfUserDBObjectRemove != NULL)
	#define EXP_UserDBObjectRemove  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemove", (RTS_UINTPTR)UserDBObjectRemove, 0, 0) 
#endif




/**
 * <description>
 *	Add a new object under a father object specified by its name to the object management, so the access rights can be configured on that object.
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
RTS_HANDLE CDECL UserDBObjectAddChild(RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTADDCHILD) (RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTADDCHILD_NOTIMPLEMENTED)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectAddChild(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectAddChild  FALSE
	#define EXP_UserDBObjectAddChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  CAL_CMGETAPI( "UserDBObjectAddChild" ) 
	#define CAL_UserDBObjectAddChild  UserDBObjectAddChild
	#define CHK_UserDBObjectAddChild  TRUE
	#define EXP_UserDBObjectAddChild  CAL_CMEXPAPI( "UserDBObjectAddChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  CAL_CMGETAPI( "UserDBObjectAddChild" ) 
	#define CAL_UserDBObjectAddChild  UserDBObjectAddChild
	#define CHK_UserDBObjectAddChild  TRUE
	#define EXP_UserDBObjectAddChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddChild", (RTS_UINTPTR)UserDBObjectAddChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectAddChild
	#define EXT_CmpUserDBUserDBObjectAddChild
	#define GET_CmpUserDBUserDBObjectAddChild  ERR_OK
	#define CAL_CmpUserDBUserDBObjectAddChild pICmpUserDB->IUserDBObjectAddChild
	#define CHK_CmpUserDBUserDBObjectAddChild (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectAddChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectAddChild
	#define EXT_UserDBObjectAddChild
	#define GET_UserDBObjectAddChild(fl)  CAL_CMGETAPI( "UserDBObjectAddChild" ) 
	#define CAL_UserDBObjectAddChild pICmpUserDB->IUserDBObjectAddChild
	#define CHK_UserDBObjectAddChild (pICmpUserDB != NULL)
	#define EXP_UserDBObjectAddChild  CAL_CMEXPAPI( "UserDBObjectAddChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectAddChild  PFUSERDBOBJECTADDCHILD pfUserDBObjectAddChild;
	#define EXT_UserDBObjectAddChild  extern PFUSERDBOBJECTADDCHILD pfUserDBObjectAddChild;
	#define GET_UserDBObjectAddChild(fl)  s_pfCMGetAPI2( "UserDBObjectAddChild", (RTS_VOID_FCTPTR *)&pfUserDBObjectAddChild, (fl), 0, 0)
	#define CAL_UserDBObjectAddChild  pfUserDBObjectAddChild
	#define CHK_UserDBObjectAddChild  (pfUserDBObjectAddChild != NULL)
	#define EXP_UserDBObjectAddChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddChild", (RTS_UINTPTR)UserDBObjectAddChild, 0, 0) 
#endif




/**
 * <description>Get a unique identifier of an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="pulID" type="OUT">Pointer to get the ObjectID</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ObjectID could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetID(RTS_HANDLE hObject, RTS_UI32 *pulID);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETID) (RTS_HANDLE hObject, RTS_UI32 *pulID);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETID_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetID(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetID  FALSE
	#define EXP_UserDBObjectGetID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  CAL_CMGETAPI( "UserDBObjectGetID" ) 
	#define CAL_UserDBObjectGetID  UserDBObjectGetID
	#define CHK_UserDBObjectGetID  TRUE
	#define EXP_UserDBObjectGetID  CAL_CMEXPAPI( "UserDBObjectGetID" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  CAL_CMGETAPI( "UserDBObjectGetID" ) 
	#define CAL_UserDBObjectGetID  UserDBObjectGetID
	#define CHK_UserDBObjectGetID  TRUE
	#define EXP_UserDBObjectGetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetID", (RTS_UINTPTR)UserDBObjectGetID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetID
	#define EXT_CmpUserDBUserDBObjectGetID
	#define GET_CmpUserDBUserDBObjectGetID  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetID pICmpUserDB->IUserDBObjectGetID
	#define CHK_CmpUserDBUserDBObjectGetID (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetID
	#define EXT_UserDBObjectGetID
	#define GET_UserDBObjectGetID(fl)  CAL_CMGETAPI( "UserDBObjectGetID" ) 
	#define CAL_UserDBObjectGetID pICmpUserDB->IUserDBObjectGetID
	#define CHK_UserDBObjectGetID (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetID  CAL_CMEXPAPI( "UserDBObjectGetID" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetID  PFUSERDBOBJECTGETID pfUserDBObjectGetID;
	#define EXT_UserDBObjectGetID  extern PFUSERDBOBJECTGETID pfUserDBObjectGetID;
	#define GET_UserDBObjectGetID(fl)  s_pfCMGetAPI2( "UserDBObjectGetID", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetID, (fl), 0, 0)
	#define CAL_UserDBObjectGetID  pfUserDBObjectGetID
	#define CHK_UserDBObjectGetID  (pfUserDBObjectGetID != NULL)
	#define EXP_UserDBObjectGetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetID", (RTS_UINTPTR)UserDBObjectGetID, 0, 0) 
#endif




/**
 * <description>Set a unique identifier of an object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="ulID" type="IN">ObjectID to set</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">ObjectID could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectSetID(RTS_HANDLE hObject, RTS_UI32 ulID);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETID) (RTS_HANDLE hObject, RTS_UI32 ulID);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTSETID_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetID(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetID  FALSE
	#define EXP_UserDBObjectSetID  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  CAL_CMGETAPI( "UserDBObjectSetID" ) 
	#define CAL_UserDBObjectSetID  UserDBObjectSetID
	#define CHK_UserDBObjectSetID  TRUE
	#define EXP_UserDBObjectSetID  CAL_CMEXPAPI( "UserDBObjectSetID" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  CAL_CMGETAPI( "UserDBObjectSetID" ) 
	#define CAL_UserDBObjectSetID  UserDBObjectSetID
	#define CHK_UserDBObjectSetID  TRUE
	#define EXP_UserDBObjectSetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetID", (RTS_UINTPTR)UserDBObjectSetID, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectSetID
	#define EXT_CmpUserDBUserDBObjectSetID
	#define GET_CmpUserDBUserDBObjectSetID  ERR_OK
	#define CAL_CmpUserDBUserDBObjectSetID pICmpUserDB->IUserDBObjectSetID
	#define CHK_CmpUserDBUserDBObjectSetID (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectSetID  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetID
	#define EXT_UserDBObjectSetID
	#define GET_UserDBObjectSetID(fl)  CAL_CMGETAPI( "UserDBObjectSetID" ) 
	#define CAL_UserDBObjectSetID pICmpUserDB->IUserDBObjectSetID
	#define CHK_UserDBObjectSetID (pICmpUserDB != NULL)
	#define EXP_UserDBObjectSetID  CAL_CMEXPAPI( "UserDBObjectSetID" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetID  PFUSERDBOBJECTSETID pfUserDBObjectSetID;
	#define EXT_UserDBObjectSetID  extern PFUSERDBOBJECTSETID pfUserDBObjectSetID;
	#define GET_UserDBObjectSetID(fl)  s_pfCMGetAPI2( "UserDBObjectSetID", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetID, (fl), 0, 0)
	#define CAL_UserDBObjectSetID  pfUserDBObjectSetID
	#define CHK_UserDBObjectSetID  (pfUserDBObjectSetID != NULL)
	#define EXP_UserDBObjectSetID  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetID", (RTS_UINTPTR)UserDBObjectSetID, 0, 0) 
#endif




/* Rights management configuration */

/**
 * <description>Add a group to the specified object to manage access rights</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group that should be attached</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be added or is already added</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOMEMORY">No memory to add group</errorcode>
 */
RTS_RESULT CDECL UserDBObjectAddGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTADDGROUP) (RTS_HANDLE hObject, RTS_HANDLE hGroup);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTADDGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectAddGroup(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectAddGroup  FALSE
	#define EXP_UserDBObjectAddGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  CAL_CMGETAPI( "UserDBObjectAddGroup" ) 
	#define CAL_UserDBObjectAddGroup  UserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup  TRUE
	#define EXP_UserDBObjectAddGroup  CAL_CMEXPAPI( "UserDBObjectAddGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  CAL_CMGETAPI( "UserDBObjectAddGroup" ) 
	#define CAL_UserDBObjectAddGroup  UserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup  TRUE
	#define EXP_UserDBObjectAddGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddGroup", (RTS_UINTPTR)UserDBObjectAddGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectAddGroup
	#define EXT_CmpUserDBUserDBObjectAddGroup
	#define GET_CmpUserDBUserDBObjectAddGroup  ERR_OK
	#define CAL_CmpUserDBUserDBObjectAddGroup pICmpUserDB->IUserDBObjectAddGroup
	#define CHK_CmpUserDBUserDBObjectAddGroup (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectAddGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectAddGroup
	#define EXT_UserDBObjectAddGroup
	#define GET_UserDBObjectAddGroup(fl)  CAL_CMGETAPI( "UserDBObjectAddGroup" ) 
	#define CAL_UserDBObjectAddGroup pICmpUserDB->IUserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup (pICmpUserDB != NULL)
	#define EXP_UserDBObjectAddGroup  CAL_CMEXPAPI( "UserDBObjectAddGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectAddGroup  PFUSERDBOBJECTADDGROUP pfUserDBObjectAddGroup;
	#define EXT_UserDBObjectAddGroup  extern PFUSERDBOBJECTADDGROUP pfUserDBObjectAddGroup;
	#define GET_UserDBObjectAddGroup(fl)  s_pfCMGetAPI2( "UserDBObjectAddGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectAddGroup, (fl), 0, 0)
	#define CAL_UserDBObjectAddGroup  pfUserDBObjectAddGroup
	#define CHK_UserDBObjectAddGroup  (pfUserDBObjectAddGroup != NULL)
	#define EXP_UserDBObjectAddGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectAddGroup", (RTS_UINTPTR)UserDBObjectAddGroup, 0, 0) 
#endif




/**
 * <description>Remove a group from the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group that should be removed</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Group could be removed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectRemoveGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTREMOVEGROUP) (RTS_HANDLE hObject, RTS_HANDLE hGroup);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTREMOVEGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectRemoveGroup(p0,p1)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectRemoveGroup  FALSE
	#define EXP_UserDBObjectRemoveGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  CAL_CMGETAPI( "UserDBObjectRemoveGroup" ) 
	#define CAL_UserDBObjectRemoveGroup  UserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup  TRUE
	#define EXP_UserDBObjectRemoveGroup  CAL_CMEXPAPI( "UserDBObjectRemoveGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  CAL_CMGETAPI( "UserDBObjectRemoveGroup" ) 
	#define CAL_UserDBObjectRemoveGroup  UserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup  TRUE
	#define EXP_UserDBObjectRemoveGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemoveGroup", (RTS_UINTPTR)UserDBObjectRemoveGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectRemoveGroup
	#define EXT_CmpUserDBUserDBObjectRemoveGroup
	#define GET_CmpUserDBUserDBObjectRemoveGroup  ERR_OK
	#define CAL_CmpUserDBUserDBObjectRemoveGroup pICmpUserDB->IUserDBObjectRemoveGroup
	#define CHK_CmpUserDBUserDBObjectRemoveGroup (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectRemoveGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectRemoveGroup
	#define EXT_UserDBObjectRemoveGroup
	#define GET_UserDBObjectRemoveGroup(fl)  CAL_CMGETAPI( "UserDBObjectRemoveGroup" ) 
	#define CAL_UserDBObjectRemoveGroup pICmpUserDB->IUserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup (pICmpUserDB != NULL)
	#define EXP_UserDBObjectRemoveGroup  CAL_CMEXPAPI( "UserDBObjectRemoveGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectRemoveGroup  PFUSERDBOBJECTREMOVEGROUP pfUserDBObjectRemoveGroup;
	#define EXT_UserDBObjectRemoveGroup  extern PFUSERDBOBJECTREMOVEGROUP pfUserDBObjectRemoveGroup;
	#define GET_UserDBObjectRemoveGroup(fl)  s_pfCMGetAPI2( "UserDBObjectRemoveGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectRemoveGroup, (fl), 0, 0)
	#define CAL_UserDBObjectRemoveGroup  pfUserDBObjectRemoveGroup
	#define CHK_UserDBObjectRemoveGroup  (pfUserDBObjectRemoveGroup != NULL)
	#define EXP_UserDBObjectRemoveGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectRemoveGroup", (RTS_UINTPTR)UserDBObjectRemoveGroup, 0, 0) 
#endif




/**
 * <description>Set the access rights for the group at the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <element name="ulRights" type="IN">Rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectSetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETGROUPRIGHTS) (RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTSETGROUPRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetGroupRights(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetGroupRights  FALSE
	#define EXP_UserDBObjectSetGroupRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupRights" ) 
	#define CAL_UserDBObjectSetGroupRights  UserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights  TRUE
	#define EXP_UserDBObjectSetGroupRights  CAL_CMEXPAPI( "UserDBObjectSetGroupRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupRights" ) 
	#define CAL_UserDBObjectSetGroupRights  UserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights  TRUE
	#define EXP_UserDBObjectSetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupRights", (RTS_UINTPTR)UserDBObjectSetGroupRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectSetGroupRights
	#define EXT_CmpUserDBUserDBObjectSetGroupRights
	#define GET_CmpUserDBUserDBObjectSetGroupRights  ERR_OK
	#define CAL_CmpUserDBUserDBObjectSetGroupRights pICmpUserDB->IUserDBObjectSetGroupRights
	#define CHK_CmpUserDBUserDBObjectSetGroupRights (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectSetGroupRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetGroupRights
	#define EXT_UserDBObjectSetGroupRights
	#define GET_UserDBObjectSetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupRights" ) 
	#define CAL_UserDBObjectSetGroupRights pICmpUserDB->IUserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights (pICmpUserDB != NULL)
	#define EXP_UserDBObjectSetGroupRights  CAL_CMEXPAPI( "UserDBObjectSetGroupRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetGroupRights  PFUSERDBOBJECTSETGROUPRIGHTS pfUserDBObjectSetGroupRights;
	#define EXT_UserDBObjectSetGroupRights  extern PFUSERDBOBJECTSETGROUPRIGHTS pfUserDBObjectSetGroupRights;
	#define GET_UserDBObjectSetGroupRights(fl)  s_pfCMGetAPI2( "UserDBObjectSetGroupRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetGroupRights, (fl), 0, 0)
	#define CAL_UserDBObjectSetGroupRights  pfUserDBObjectSetGroupRights
	#define CHK_UserDBObjectSetGroupRights  (pfUserDBObjectSetGroupRights != NULL)
	#define EXP_UserDBObjectSetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupRights", (RTS_UINTPTR)UserDBObjectSetGroupRights, 0, 0) 
#endif




/**
 * <description>Set the denied access rights for the group at the specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group</param>
 * <element name="ulDeniedRights" type="IN">Denied rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be set</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectSetGroupDeniedRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTSETGROUPDENIEDRIGHTS) (RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTSETGROUPDENIEDRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectSetGroupDeniedRights(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectSetGroupDeniedRights  FALSE
	#define EXP_UserDBObjectSetGroupDeniedRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupDeniedRights" ) 
	#define CAL_UserDBObjectSetGroupDeniedRights  UserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights  TRUE
	#define EXP_UserDBObjectSetGroupDeniedRights  CAL_CMEXPAPI( "UserDBObjectSetGroupDeniedRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupDeniedRights" ) 
	#define CAL_UserDBObjectSetGroupDeniedRights  UserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights  TRUE
	#define EXP_UserDBObjectSetGroupDeniedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupDeniedRights", (RTS_UINTPTR)UserDBObjectSetGroupDeniedRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectSetGroupDeniedRights
	#define EXT_CmpUserDBUserDBObjectSetGroupDeniedRights
	#define GET_CmpUserDBUserDBObjectSetGroupDeniedRights  ERR_OK
	#define CAL_CmpUserDBUserDBObjectSetGroupDeniedRights pICmpUserDB->IUserDBObjectSetGroupDeniedRights
	#define CHK_CmpUserDBUserDBObjectSetGroupDeniedRights (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectSetGroupDeniedRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectSetGroupDeniedRights
	#define EXT_UserDBObjectSetGroupDeniedRights
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  CAL_CMGETAPI( "UserDBObjectSetGroupDeniedRights" ) 
	#define CAL_UserDBObjectSetGroupDeniedRights pICmpUserDB->IUserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights (pICmpUserDB != NULL)
	#define EXP_UserDBObjectSetGroupDeniedRights  CAL_CMEXPAPI( "UserDBObjectSetGroupDeniedRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectSetGroupDeniedRights  PFUSERDBOBJECTSETGROUPDENIEDRIGHTS pfUserDBObjectSetGroupDeniedRights;
	#define EXT_UserDBObjectSetGroupDeniedRights  extern PFUSERDBOBJECTSETGROUPDENIEDRIGHTS pfUserDBObjectSetGroupDeniedRights;
	#define GET_UserDBObjectSetGroupDeniedRights(fl)  s_pfCMGetAPI2( "UserDBObjectSetGroupDeniedRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectSetGroupDeniedRights, (fl), 0, 0)
	#define CAL_UserDBObjectSetGroupDeniedRights  pfUserDBObjectSetGroupDeniedRights
	#define CHK_UserDBObjectSetGroupDeniedRights  (pfUserDBObjectSetGroupDeniedRights != NULL)
	#define EXP_UserDBObjectSetGroupDeniedRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectSetGroupDeniedRights", (RTS_UINTPTR)UserDBObjectSetGroupDeniedRights, 0, 0) 
#endif





/* --------- Objects and Rights managament ---------------------------------- */
/* This section of functions is MANDATORY and must be implemented			  */

/* Object iteration */

/**
 * <description>Iteration interface to get the first object of the user rights management</description>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First object of the user rights management available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No object available</errorcode>
 * <result>Handle to the first object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFirst(RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFIRST) (RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFIRST_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFirst(p0)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFirst  FALSE
	#define EXP_UserDBObjectGetFirst  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  CAL_CMGETAPI( "UserDBObjectGetFirst" ) 
	#define CAL_UserDBObjectGetFirst  UserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst  TRUE
	#define EXP_UserDBObjectGetFirst  CAL_CMEXPAPI( "UserDBObjectGetFirst" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  CAL_CMGETAPI( "UserDBObjectGetFirst" ) 
	#define CAL_UserDBObjectGetFirst  UserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst  TRUE
	#define EXP_UserDBObjectGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirst", (RTS_UINTPTR)UserDBObjectGetFirst, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetFirst
	#define EXT_CmpUserDBUserDBObjectGetFirst
	#define GET_CmpUserDBUserDBObjectGetFirst  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetFirst pICmpUserDB->IUserDBObjectGetFirst
	#define CHK_CmpUserDBUserDBObjectGetFirst (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetFirst  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFirst
	#define EXT_UserDBObjectGetFirst
	#define GET_UserDBObjectGetFirst(fl)  CAL_CMGETAPI( "UserDBObjectGetFirst" ) 
	#define CAL_UserDBObjectGetFirst pICmpUserDB->IUserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetFirst  CAL_CMEXPAPI( "UserDBObjectGetFirst" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFirst  PFUSERDBOBJECTGETFIRST pfUserDBObjectGetFirst;
	#define EXT_UserDBObjectGetFirst  extern PFUSERDBOBJECTGETFIRST pfUserDBObjectGetFirst;
	#define GET_UserDBObjectGetFirst(fl)  s_pfCMGetAPI2( "UserDBObjectGetFirst", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFirst, (fl), 0, 0)
	#define CAL_UserDBObjectGetFirst  pfUserDBObjectGetFirst
	#define CHK_UserDBObjectGetFirst  (pfUserDBObjectGetFirst != NULL)
	#define EXP_UserDBObjectGetFirst  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirst", (RTS_UINTPTR)UserDBObjectGetFirst, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next object of the user rights management. Must be started with UserDBObjectGetFirst()</description>
 * <param name="hPrevObject" type="IN">Handle to the previous object retrieved via UserDBObjectGetFirst() or subsequent calls of UserDBObjectGetNext()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next object available</errorcode>
 * <result>Handle to the next object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetNext(RTS_HANDLE hPrevObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETNEXT) (RTS_HANDLE hPrevObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNEXT_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetNext(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetNext  FALSE
	#define EXP_UserDBObjectGetNext  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  CAL_CMGETAPI( "UserDBObjectGetNext" ) 
	#define CAL_UserDBObjectGetNext  UserDBObjectGetNext
	#define CHK_UserDBObjectGetNext  TRUE
	#define EXP_UserDBObjectGetNext  CAL_CMEXPAPI( "UserDBObjectGetNext" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  CAL_CMGETAPI( "UserDBObjectGetNext" ) 
	#define CAL_UserDBObjectGetNext  UserDBObjectGetNext
	#define CHK_UserDBObjectGetNext  TRUE
	#define EXP_UserDBObjectGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNext", (RTS_UINTPTR)UserDBObjectGetNext, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetNext
	#define EXT_CmpUserDBUserDBObjectGetNext
	#define GET_CmpUserDBUserDBObjectGetNext  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetNext pICmpUserDB->IUserDBObjectGetNext
	#define CHK_CmpUserDBUserDBObjectGetNext (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetNext  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetNext
	#define EXT_UserDBObjectGetNext
	#define GET_UserDBObjectGetNext(fl)  CAL_CMGETAPI( "UserDBObjectGetNext" ) 
	#define CAL_UserDBObjectGetNext pICmpUserDB->IUserDBObjectGetNext
	#define CHK_UserDBObjectGetNext (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetNext  CAL_CMEXPAPI( "UserDBObjectGetNext" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetNext  PFUSERDBOBJECTGETNEXT pfUserDBObjectGetNext;
	#define EXT_UserDBObjectGetNext  extern PFUSERDBOBJECTGETNEXT pfUserDBObjectGetNext;
	#define GET_UserDBObjectGetNext(fl)  s_pfCMGetAPI2( "UserDBObjectGetNext", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetNext, (fl), 0, 0)
	#define CAL_UserDBObjectGetNext  pfUserDBObjectGetNext
	#define CHK_UserDBObjectGetNext  (pfUserDBObjectGetNext != NULL)
	#define EXP_UserDBObjectGetNext  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNext", (RTS_UINTPTR)UserDBObjectGetNext, 0, 0) 
#endif




/* Single object access */

/**
 * <description>Open object specified by its name</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be opened</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter. pszObject = NULL or empty</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectOpen(char *pszObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTOPEN) (char *pszObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTOPEN_NOTIMPLEMENTED)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectOpen(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectOpen  FALSE
	#define EXP_UserDBObjectOpen  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  CAL_CMGETAPI( "UserDBObjectOpen" ) 
	#define CAL_UserDBObjectOpen  UserDBObjectOpen
	#define CHK_UserDBObjectOpen  TRUE
	#define EXP_UserDBObjectOpen  CAL_CMEXPAPI( "UserDBObjectOpen" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  CAL_CMGETAPI( "UserDBObjectOpen" ) 
	#define CAL_UserDBObjectOpen  UserDBObjectOpen
	#define CHK_UserDBObjectOpen  TRUE
	#define EXP_UserDBObjectOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectOpen", (RTS_UINTPTR)UserDBObjectOpen, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectOpen
	#define EXT_CmpUserDBUserDBObjectOpen
	#define GET_CmpUserDBUserDBObjectOpen  ERR_OK
	#define CAL_CmpUserDBUserDBObjectOpen pICmpUserDB->IUserDBObjectOpen
	#define CHK_CmpUserDBUserDBObjectOpen (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectOpen  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectOpen
	#define EXT_UserDBObjectOpen
	#define GET_UserDBObjectOpen(fl)  CAL_CMGETAPI( "UserDBObjectOpen" ) 
	#define CAL_UserDBObjectOpen pICmpUserDB->IUserDBObjectOpen
	#define CHK_UserDBObjectOpen (pICmpUserDB != NULL)
	#define EXP_UserDBObjectOpen  CAL_CMEXPAPI( "UserDBObjectOpen" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectOpen  PFUSERDBOBJECTOPEN pfUserDBObjectOpen;
	#define EXT_UserDBObjectOpen  extern PFUSERDBOBJECTOPEN pfUserDBObjectOpen;
	#define GET_UserDBObjectOpen(fl)  s_pfCMGetAPI2( "UserDBObjectOpen", (RTS_VOID_FCTPTR *)&pfUserDBObjectOpen, (fl), 0, 0)
	#define CAL_UserDBObjectOpen  pfUserDBObjectOpen
	#define CHK_UserDBObjectOpen  (pfUserDBObjectOpen != NULL)
	#define EXP_UserDBObjectOpen  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectOpen", (RTS_UINTPTR)UserDBObjectOpen, 0, 0) 
#endif




/**
 * <description>Close an object</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object could be closed</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle</errorcode>
 */
RTS_RESULT CDECL UserDBObjectClose(RTS_HANDLE hObject);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTCLOSE) (RTS_HANDLE hObject);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTCLOSE_NOTIMPLEMENTED)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectClose(p0)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectClose  FALSE
	#define EXP_UserDBObjectClose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  CAL_CMGETAPI( "UserDBObjectClose" ) 
	#define CAL_UserDBObjectClose  UserDBObjectClose
	#define CHK_UserDBObjectClose  TRUE
	#define EXP_UserDBObjectClose  CAL_CMEXPAPI( "UserDBObjectClose" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  CAL_CMGETAPI( "UserDBObjectClose" ) 
	#define CAL_UserDBObjectClose  UserDBObjectClose
	#define CHK_UserDBObjectClose  TRUE
	#define EXP_UserDBObjectClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectClose", (RTS_UINTPTR)UserDBObjectClose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectClose
	#define EXT_CmpUserDBUserDBObjectClose
	#define GET_CmpUserDBUserDBObjectClose  ERR_OK
	#define CAL_CmpUserDBUserDBObjectClose pICmpUserDB->IUserDBObjectClose
	#define CHK_CmpUserDBUserDBObjectClose (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectClose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectClose
	#define EXT_UserDBObjectClose
	#define GET_UserDBObjectClose(fl)  CAL_CMGETAPI( "UserDBObjectClose" ) 
	#define CAL_UserDBObjectClose pICmpUserDB->IUserDBObjectClose
	#define CHK_UserDBObjectClose (pICmpUserDB != NULL)
	#define EXP_UserDBObjectClose  CAL_CMEXPAPI( "UserDBObjectClose" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectClose  PFUSERDBOBJECTCLOSE pfUserDBObjectClose;
	#define EXT_UserDBObjectClose  extern PFUSERDBOBJECTCLOSE pfUserDBObjectClose;
	#define GET_UserDBObjectClose(fl)  s_pfCMGetAPI2( "UserDBObjectClose", (RTS_VOID_FCTPTR *)&pfUserDBObjectClose, (fl), 0, 0)
	#define CAL_UserDBObjectClose  pfUserDBObjectClose
	#define CHK_UserDBObjectClose  (pfUserDBObjectClose != NULL)
	#define EXP_UserDBObjectClose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectClose", (RTS_UINTPTR)UserDBObjectClose, 0, 0) 
#endif




/**
 * <description>Get object name</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pszObject" type="OUT">Pointer to get object name</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszObject. If pszObject = NULL, only the length of the object name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or pszObject = NULL and piMaxLen = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetName(RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETNAME) (RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNAME_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetName(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetName  FALSE
	#define EXP_UserDBObjectGetName  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  CAL_CMGETAPI( "UserDBObjectGetName" ) 
	#define CAL_UserDBObjectGetName  UserDBObjectGetName
	#define CHK_UserDBObjectGetName  TRUE
	#define EXP_UserDBObjectGetName  CAL_CMEXPAPI( "UserDBObjectGetName" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  CAL_CMGETAPI( "UserDBObjectGetName" ) 
	#define CAL_UserDBObjectGetName  UserDBObjectGetName
	#define CHK_UserDBObjectGetName  TRUE
	#define EXP_UserDBObjectGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetName", (RTS_UINTPTR)UserDBObjectGetName, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetName
	#define EXT_CmpUserDBUserDBObjectGetName
	#define GET_CmpUserDBUserDBObjectGetName  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetName pICmpUserDB->IUserDBObjectGetName
	#define CHK_CmpUserDBUserDBObjectGetName (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetName  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetName
	#define EXT_UserDBObjectGetName
	#define GET_UserDBObjectGetName(fl)  CAL_CMGETAPI( "UserDBObjectGetName" ) 
	#define CAL_UserDBObjectGetName pICmpUserDB->IUserDBObjectGetName
	#define CHK_UserDBObjectGetName (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetName  CAL_CMEXPAPI( "UserDBObjectGetName" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetName  PFUSERDBOBJECTGETNAME pfUserDBObjectGetName;
	#define EXT_UserDBObjectGetName  extern PFUSERDBOBJECTGETNAME pfUserDBObjectGetName;
	#define GET_UserDBObjectGetName(fl)  s_pfCMGetAPI2( "UserDBObjectGetName", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetName, (fl), 0, 0)
	#define CAL_UserDBObjectGetName  pfUserDBObjectGetName
	#define CHK_UserDBObjectGetName  (pfUserDBObjectGetName != NULL)
	#define EXP_UserDBObjectGetName  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetName", (RTS_UINTPTR)UserDBObjectGetName, 0, 0) 
#endif




/**
 * <description>Get the complete object path name</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pszObject" type="IN">Full object path name (see object tree)</param>
 * <param name="piMaxLen" type="INOUT">Pointer to length of buffer in pszObject. If pszObject = NULL, only the length of the object name is returned in *piMaxLen</param>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Object name is returned</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid object handle or pszObject = NULL and piMaxLen = NULL</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetPath(RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETPATH) (RTS_HANDLE hObject, char *pszObject, int *piMaxLen);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETPATH_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetPath(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetPath  FALSE
	#define EXP_UserDBObjectGetPath  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  CAL_CMGETAPI( "UserDBObjectGetPath" ) 
	#define CAL_UserDBObjectGetPath  UserDBObjectGetPath
	#define CHK_UserDBObjectGetPath  TRUE
	#define EXP_UserDBObjectGetPath  CAL_CMEXPAPI( "UserDBObjectGetPath" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  CAL_CMGETAPI( "UserDBObjectGetPath" ) 
	#define CAL_UserDBObjectGetPath  UserDBObjectGetPath
	#define CHK_UserDBObjectGetPath  TRUE
	#define EXP_UserDBObjectGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetPath", (RTS_UINTPTR)UserDBObjectGetPath, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetPath
	#define EXT_CmpUserDBUserDBObjectGetPath
	#define GET_CmpUserDBUserDBObjectGetPath  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetPath pICmpUserDB->IUserDBObjectGetPath
	#define CHK_CmpUserDBUserDBObjectGetPath (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetPath  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetPath
	#define EXT_UserDBObjectGetPath
	#define GET_UserDBObjectGetPath(fl)  CAL_CMGETAPI( "UserDBObjectGetPath" ) 
	#define CAL_UserDBObjectGetPath pICmpUserDB->IUserDBObjectGetPath
	#define CHK_UserDBObjectGetPath (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetPath  CAL_CMEXPAPI( "UserDBObjectGetPath" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetPath  PFUSERDBOBJECTGETPATH pfUserDBObjectGetPath;
	#define EXT_UserDBObjectGetPath  extern PFUSERDBOBJECTGETPATH pfUserDBObjectGetPath;
	#define GET_UserDBObjectGetPath(fl)  s_pfCMGetAPI2( "UserDBObjectGetPath", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetPath, (fl), 0, 0)
	#define CAL_UserDBObjectGetPath  pfUserDBObjectGetPath
	#define CHK_UserDBObjectGetPath  (pfUserDBObjectGetPath != NULL)
	#define EXP_UserDBObjectGetPath  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetPath", (RTS_UINTPTR)UserDBObjectGetPath, 0, 0) 
#endif




/**
 * <description>Get first child object in object tree of the specified father object</description>
 * <param name="hFatherObject" type="IN">Handle to the father object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First child object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hFatherObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the child object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFirstChild(RTS_HANDLE hFatherObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFIRSTCHILD) (RTS_HANDLE hFatherObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFIRSTCHILD_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFirstChild(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFirstChild  FALSE
	#define EXP_UserDBObjectGetFirstChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstChild" ) 
	#define CAL_UserDBObjectGetFirstChild  UserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild  TRUE
	#define EXP_UserDBObjectGetFirstChild  CAL_CMEXPAPI( "UserDBObjectGetFirstChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstChild" ) 
	#define CAL_UserDBObjectGetFirstChild  UserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild  TRUE
	#define EXP_UserDBObjectGetFirstChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstChild", (RTS_UINTPTR)UserDBObjectGetFirstChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetFirstChild
	#define EXT_CmpUserDBUserDBObjectGetFirstChild
	#define GET_CmpUserDBUserDBObjectGetFirstChild  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetFirstChild pICmpUserDB->IUserDBObjectGetFirstChild
	#define CHK_CmpUserDBUserDBObjectGetFirstChild (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetFirstChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFirstChild
	#define EXT_UserDBObjectGetFirstChild
	#define GET_UserDBObjectGetFirstChild(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstChild" ) 
	#define CAL_UserDBObjectGetFirstChild pICmpUserDB->IUserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetFirstChild  CAL_CMEXPAPI( "UserDBObjectGetFirstChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFirstChild  PFUSERDBOBJECTGETFIRSTCHILD pfUserDBObjectGetFirstChild;
	#define EXT_UserDBObjectGetFirstChild  extern PFUSERDBOBJECTGETFIRSTCHILD pfUserDBObjectGetFirstChild;
	#define GET_UserDBObjectGetFirstChild(fl)  s_pfCMGetAPI2( "UserDBObjectGetFirstChild", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFirstChild, (fl), 0, 0)
	#define CAL_UserDBObjectGetFirstChild  pfUserDBObjectGetFirstChild
	#define CHK_UserDBObjectGetFirstChild  (pfUserDBObjectGetFirstChild != NULL)
	#define EXP_UserDBObjectGetFirstChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstChild", (RTS_UINTPTR)UserDBObjectGetFirstChild, 0, 0) 
#endif




/**
 * <description>Get next child object in object tree of the specified father object. Must be started with UserDBObjectGetFirstChild()</description>
 * <param name="hFatherObject" type="IN">Handle to the father object</param>
 * <param name="hPrevChildObject" type="IN">Handle to the previous child object retrieved by UserDBObjectGetFirstChild() or subsequent calls of UserDBObjectGetNextChild()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next child object available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hFatherObject or hPrevChildObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the next child object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetNextChild(RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETNEXTCHILD) (RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNEXTCHILD_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetNextChild(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetNextChild  FALSE
	#define EXP_UserDBObjectGetNextChild  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  CAL_CMGETAPI( "UserDBObjectGetNextChild" ) 
	#define CAL_UserDBObjectGetNextChild  UserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild  TRUE
	#define EXP_UserDBObjectGetNextChild  CAL_CMEXPAPI( "UserDBObjectGetNextChild" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  CAL_CMGETAPI( "UserDBObjectGetNextChild" ) 
	#define CAL_UserDBObjectGetNextChild  UserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild  TRUE
	#define EXP_UserDBObjectGetNextChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextChild", (RTS_UINTPTR)UserDBObjectGetNextChild, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetNextChild
	#define EXT_CmpUserDBUserDBObjectGetNextChild
	#define GET_CmpUserDBUserDBObjectGetNextChild  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetNextChild pICmpUserDB->IUserDBObjectGetNextChild
	#define CHK_CmpUserDBUserDBObjectGetNextChild (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetNextChild  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetNextChild
	#define EXT_UserDBObjectGetNextChild
	#define GET_UserDBObjectGetNextChild(fl)  CAL_CMGETAPI( "UserDBObjectGetNextChild" ) 
	#define CAL_UserDBObjectGetNextChild pICmpUserDB->IUserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetNextChild  CAL_CMEXPAPI( "UserDBObjectGetNextChild" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetNextChild  PFUSERDBOBJECTGETNEXTCHILD pfUserDBObjectGetNextChild;
	#define EXT_UserDBObjectGetNextChild  extern PFUSERDBOBJECTGETNEXTCHILD pfUserDBObjectGetNextChild;
	#define GET_UserDBObjectGetNextChild(fl)  s_pfCMGetAPI2( "UserDBObjectGetNextChild", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetNextChild, (fl), 0, 0)
	#define CAL_UserDBObjectGetNextChild  pfUserDBObjectGetNextChild
	#define CHK_UserDBObjectGetNextChild  (pfUserDBObjectGetNextChild != NULL)
	#define EXP_UserDBObjectGetNextChild  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextChild", (RTS_UINTPTR)UserDBObjectGetNextChild, 0, 0) 
#endif




/**
 * <description>Get the father object in object tree of the specified child object</description>
 * <param name="hChildObject" type="IN">Handle to the child object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Father object could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid parameter hChildObject</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NOTINITIALIZED">The user management is not initialized or it is not loaded yet</errorcode>
 * <result>Handle to the father/parent object or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFather(RTS_HANDLE hChildObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFATHER) (RTS_HANDLE hChildObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFATHER_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFather(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFather  FALSE
	#define EXP_UserDBObjectGetFather  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  CAL_CMGETAPI( "UserDBObjectGetFather" ) 
	#define CAL_UserDBObjectGetFather  UserDBObjectGetFather
	#define CHK_UserDBObjectGetFather  TRUE
	#define EXP_UserDBObjectGetFather  CAL_CMEXPAPI( "UserDBObjectGetFather" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  CAL_CMGETAPI( "UserDBObjectGetFather" ) 
	#define CAL_UserDBObjectGetFather  UserDBObjectGetFather
	#define CHK_UserDBObjectGetFather  TRUE
	#define EXP_UserDBObjectGetFather  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFather", (RTS_UINTPTR)UserDBObjectGetFather, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetFather
	#define EXT_CmpUserDBUserDBObjectGetFather
	#define GET_CmpUserDBUserDBObjectGetFather  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetFather pICmpUserDB->IUserDBObjectGetFather
	#define CHK_CmpUserDBUserDBObjectGetFather (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetFather  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFather
	#define EXT_UserDBObjectGetFather
	#define GET_UserDBObjectGetFather(fl)  CAL_CMGETAPI( "UserDBObjectGetFather" ) 
	#define CAL_UserDBObjectGetFather pICmpUserDB->IUserDBObjectGetFather
	#define CHK_UserDBObjectGetFather (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetFather  CAL_CMEXPAPI( "UserDBObjectGetFather" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFather  PFUSERDBOBJECTGETFATHER pfUserDBObjectGetFather;
	#define EXT_UserDBObjectGetFather  extern PFUSERDBOBJECTGETFATHER pfUserDBObjectGetFather;
	#define GET_UserDBObjectGetFather(fl)  s_pfCMGetAPI2( "UserDBObjectGetFather", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFather, (fl), 0, 0)
	#define CAL_UserDBObjectGetFather  pfUserDBObjectGetFather
	#define CHK_UserDBObjectGetFather  (pfUserDBObjectGetFather != NULL)
	#define EXP_UserDBObjectGetFather  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFather", (RTS_UINTPTR)UserDBObjectGetFather, 0, 0) 
#endif




/* Iteration over all groups that are assigned to the object */

/**
 * <description>Iteration interface to get the first group in the user rights management of the specified object</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">First group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No group available</errorcode>
 * <result>Handle to the first group of the object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetFirstGroup(RTS_HANDLE hObject, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETFIRSTGROUP) (RTS_HANDLE hObject, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETFIRSTGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetFirstGroup(p0,p1)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetFirstGroup  FALSE
	#define EXP_UserDBObjectGetFirstGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstGroup" ) 
	#define CAL_UserDBObjectGetFirstGroup  UserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup  TRUE
	#define EXP_UserDBObjectGetFirstGroup  CAL_CMEXPAPI( "UserDBObjectGetFirstGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstGroup" ) 
	#define CAL_UserDBObjectGetFirstGroup  UserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup  TRUE
	#define EXP_UserDBObjectGetFirstGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstGroup", (RTS_UINTPTR)UserDBObjectGetFirstGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetFirstGroup
	#define EXT_CmpUserDBUserDBObjectGetFirstGroup
	#define GET_CmpUserDBUserDBObjectGetFirstGroup  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetFirstGroup pICmpUserDB->IUserDBObjectGetFirstGroup
	#define CHK_CmpUserDBUserDBObjectGetFirstGroup (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetFirstGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetFirstGroup
	#define EXT_UserDBObjectGetFirstGroup
	#define GET_UserDBObjectGetFirstGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetFirstGroup" ) 
	#define CAL_UserDBObjectGetFirstGroup pICmpUserDB->IUserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetFirstGroup  CAL_CMEXPAPI( "UserDBObjectGetFirstGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetFirstGroup  PFUSERDBOBJECTGETFIRSTGROUP pfUserDBObjectGetFirstGroup;
	#define EXT_UserDBObjectGetFirstGroup  extern PFUSERDBOBJECTGETFIRSTGROUP pfUserDBObjectGetFirstGroup;
	#define GET_UserDBObjectGetFirstGroup(fl)  s_pfCMGetAPI2( "UserDBObjectGetFirstGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetFirstGroup, (fl), 0, 0)
	#define CAL_UserDBObjectGetFirstGroup  pfUserDBObjectGetFirstGroup
	#define CHK_UserDBObjectGetFirstGroup  (pfUserDBObjectGetFirstGroup != NULL)
	#define EXP_UserDBObjectGetFirstGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetFirstGroup", (RTS_UINTPTR)UserDBObjectGetFirstGroup, 0, 0) 
#endif




/**
 * <description>Iteration interface to get next group in the user rights management of the specified object. Must be started with UserDBObjectGetFirstGroup()</description>
 * <param name="hObject" type="IN">Handle to the object</param>
 * <param name="hPrevGroup" type="IN">Handle to the previous group retrieved via UserDBObjectGetFirstGroup() or subsequent calls of UserDBObjectGetNextGroup()</param>
 * <param name="pResult" type="OUT">Pointer to error code</param>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Next group available</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_OBJECT">No next group available</errorcode>
 * <result>Handle to the next group of the object in the user rights management or RTS_INVALID_HANDLE if failed</result>
 */
RTS_HANDLE CDECL UserDBObjectGetNextGroup(RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
typedef RTS_HANDLE (CDECL * PFUSERDBOBJECTGETNEXTGROUP) (RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETNEXTGROUP_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetNextGroup(p0,p1,p2)  (RTS_HANDLE)RTS_INVALID_HANDLE
	#define CHK_UserDBObjectGetNextGroup  FALSE
	#define EXP_UserDBObjectGetNextGroup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetNextGroup" ) 
	#define CAL_UserDBObjectGetNextGroup  UserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup  TRUE
	#define EXP_UserDBObjectGetNextGroup  CAL_CMEXPAPI( "UserDBObjectGetNextGroup" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetNextGroup" ) 
	#define CAL_UserDBObjectGetNextGroup  UserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup  TRUE
	#define EXP_UserDBObjectGetNextGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextGroup", (RTS_UINTPTR)UserDBObjectGetNextGroup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetNextGroup
	#define EXT_CmpUserDBUserDBObjectGetNextGroup
	#define GET_CmpUserDBUserDBObjectGetNextGroup  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetNextGroup pICmpUserDB->IUserDBObjectGetNextGroup
	#define CHK_CmpUserDBUserDBObjectGetNextGroup (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetNextGroup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetNextGroup
	#define EXT_UserDBObjectGetNextGroup
	#define GET_UserDBObjectGetNextGroup(fl)  CAL_CMGETAPI( "UserDBObjectGetNextGroup" ) 
	#define CAL_UserDBObjectGetNextGroup pICmpUserDB->IUserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetNextGroup  CAL_CMEXPAPI( "UserDBObjectGetNextGroup" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetNextGroup  PFUSERDBOBJECTGETNEXTGROUP pfUserDBObjectGetNextGroup;
	#define EXT_UserDBObjectGetNextGroup  extern PFUSERDBOBJECTGETNEXTGROUP pfUserDBObjectGetNextGroup;
	#define GET_UserDBObjectGetNextGroup(fl)  s_pfCMGetAPI2( "UserDBObjectGetNextGroup", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetNextGroup, (fl), 0, 0)
	#define CAL_UserDBObjectGetNextGroup  pfUserDBObjectGetNextGroup
	#define CHK_UserDBObjectGetNextGroup  (pfUserDBObjectGetNextGroup != NULL)
	#define EXP_UserDBObjectGetNextGroup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetNextGroup", (RTS_UINTPTR)UserDBObjectGetNextGroup, 0, 0) 
#endif




/* Get rights */

/**
 * <description>Get the rights and the denied rights of a group on a specified object</description>
 * <param name="hObject" type="IN">Handle to object</param>
 * <param name="hGroup" type="IN">Handle to the group which access rights are requested</param>
 * <element name="pulRights" type="IN">Pointer to get rights of the group. See category "User rights" for details</element>
 * <element name="pulDeniedRights" type="IN">Pointer to get denied rights of the group. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETGROUPRIGHTS) (RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETGROUPRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetGroupRights(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetGroupRights  FALSE
	#define EXP_UserDBObjectGetGroupRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectGetGroupRights" ) 
	#define CAL_UserDBObjectGetGroupRights  UserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights  TRUE
	#define EXP_UserDBObjectGetGroupRights  CAL_CMEXPAPI( "UserDBObjectGetGroupRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectGetGroupRights" ) 
	#define CAL_UserDBObjectGetGroupRights  UserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights  TRUE
	#define EXP_UserDBObjectGetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetGroupRights", (RTS_UINTPTR)UserDBObjectGetGroupRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetGroupRights
	#define EXT_CmpUserDBUserDBObjectGetGroupRights
	#define GET_CmpUserDBUserDBObjectGetGroupRights  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetGroupRights pICmpUserDB->IUserDBObjectGetGroupRights
	#define CHK_CmpUserDBUserDBObjectGetGroupRights (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetGroupRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetGroupRights
	#define EXT_UserDBObjectGetGroupRights
	#define GET_UserDBObjectGetGroupRights(fl)  CAL_CMGETAPI( "UserDBObjectGetGroupRights" ) 
	#define CAL_UserDBObjectGetGroupRights pICmpUserDB->IUserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetGroupRights  CAL_CMEXPAPI( "UserDBObjectGetGroupRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetGroupRights  PFUSERDBOBJECTGETGROUPRIGHTS pfUserDBObjectGetGroupRights;
	#define EXT_UserDBObjectGetGroupRights  extern PFUSERDBOBJECTGETGROUPRIGHTS pfUserDBObjectGetGroupRights;
	#define GET_UserDBObjectGetGroupRights(fl)  s_pfCMGetAPI2( "UserDBObjectGetGroupRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetGroupRights, (fl), 0, 0)
	#define CAL_UserDBObjectGetGroupRights  pfUserDBObjectGetGroupRights
	#define CHK_UserDBObjectGetGroupRights  (pfUserDBObjectGetGroupRights != NULL)
	#define EXP_UserDBObjectGetGroupRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetGroupRights", (RTS_UINTPTR)UserDBObjectGetGroupRights, 0, 0) 
#endif




/**
 * <description>Check access rights of a user on an object (authorization)</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="hUser" type="IN">Handle to the user which access rights are checked</param>
 * <element name="ulRequestedRights" type="IN">Requested access rights. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access permitted</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Access rights could not be retrieved, so no access rights!</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_NO_ACCESS_RIGHTS">No access rights!</errorcode>
 */
RTS_RESULT CDECL UserDBObjectHasRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTHASRIGHTS) (char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTHASRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectHasRights(p0,p1,p2)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectHasRights  FALSE
	#define EXP_UserDBObjectHasRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  CAL_CMGETAPI( "UserDBObjectHasRights" ) 
	#define CAL_UserDBObjectHasRights  UserDBObjectHasRights
	#define CHK_UserDBObjectHasRights  TRUE
	#define EXP_UserDBObjectHasRights  CAL_CMEXPAPI( "UserDBObjectHasRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  CAL_CMGETAPI( "UserDBObjectHasRights" ) 
	#define CAL_UserDBObjectHasRights  UserDBObjectHasRights
	#define CHK_UserDBObjectHasRights  TRUE
	#define EXP_UserDBObjectHasRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectHasRights", (RTS_UINTPTR)UserDBObjectHasRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectHasRights
	#define EXT_CmpUserDBUserDBObjectHasRights
	#define GET_CmpUserDBUserDBObjectHasRights  ERR_OK
	#define CAL_CmpUserDBUserDBObjectHasRights pICmpUserDB->IUserDBObjectHasRights
	#define CHK_CmpUserDBUserDBObjectHasRights (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectHasRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectHasRights
	#define EXT_UserDBObjectHasRights
	#define GET_UserDBObjectHasRights(fl)  CAL_CMGETAPI( "UserDBObjectHasRights" ) 
	#define CAL_UserDBObjectHasRights pICmpUserDB->IUserDBObjectHasRights
	#define CHK_UserDBObjectHasRights (pICmpUserDB != NULL)
	#define EXP_UserDBObjectHasRights  CAL_CMEXPAPI( "UserDBObjectHasRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectHasRights  PFUSERDBOBJECTHASRIGHTS pfUserDBObjectHasRights;
	#define EXT_UserDBObjectHasRights  extern PFUSERDBOBJECTHASRIGHTS pfUserDBObjectHasRights;
	#define GET_UserDBObjectHasRights(fl)  s_pfCMGetAPI2( "UserDBObjectHasRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectHasRights, (fl), 0, 0)
	#define CAL_UserDBObjectHasRights  pfUserDBObjectHasRights
	#define CHK_UserDBObjectHasRights  (pfUserDBObjectHasRights != NULL)
	#define EXP_UserDBObjectHasRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectHasRights", (RTS_UINTPTR)UserDBObjectHasRights, 0, 0) 
#endif




/**
 * <description>Get the rights and the denied rights of a user on a specified object</description>
 * <param name="pszObject" type="IN">Full object name (see object tree)</param>
 * <param name="hUser" type="IN">Handle to the user which access rights are requested</param>
 * <element name="pulRights" type="IN">Pointer to get rights of the user. See category "User rights" for details</element>
 * <element name="pulDeniedRights" type="IN">Pointer to get denied rights of the user. See category "User rights" for details</element>
 * <result>Error code</result>
 * <errorcode name="RTS_RESULT" type="ERR_OK">Access rights could be retrieved</errorcode>
 * <errorcode name="RTS_RESULT" type="ERR_PARAMETER">Invalid handles</errorcode>
 */
RTS_RESULT CDECL UserDBObjectGetRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
typedef RTS_RESULT (CDECL * PFUSERDBOBJECTGETRIGHTS) (char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights);
#if defined(CMPUSERDB_NOTIMPLEMENTED) || defined(USERDBOBJECTGETRIGHTS_NOTIMPLEMENTED)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  ERR_NOTIMPLEMENTED
	#define CAL_UserDBObjectGetRights(p0,p1,p2,p3)  (RTS_RESULT)ERR_NOTIMPLEMENTED
	#define CHK_UserDBObjectGetRights  FALSE
	#define EXP_UserDBObjectGetRights  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  CAL_CMGETAPI( "UserDBObjectGetRights" ) 
	#define CAL_UserDBObjectGetRights  UserDBObjectGetRights
	#define CHK_UserDBObjectGetRights  TRUE
	#define EXP_UserDBObjectGetRights  CAL_CMEXPAPI( "UserDBObjectGetRights" ) 
#elif defined(MIXED_LINK) && !defined(CMPUSERDB_EXTERNAL)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  CAL_CMGETAPI( "UserDBObjectGetRights" ) 
	#define CAL_UserDBObjectGetRights  UserDBObjectGetRights
	#define CHK_UserDBObjectGetRights  TRUE
	#define EXP_UserDBObjectGetRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetRights", (RTS_UINTPTR)UserDBObjectGetRights, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpUserDBUserDBObjectGetRights
	#define EXT_CmpUserDBUserDBObjectGetRights
	#define GET_CmpUserDBUserDBObjectGetRights  ERR_OK
	#define CAL_CmpUserDBUserDBObjectGetRights pICmpUserDB->IUserDBObjectGetRights
	#define CHK_CmpUserDBUserDBObjectGetRights (pICmpUserDB != NULL)
	#define EXP_CmpUserDBUserDBObjectGetRights  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_UserDBObjectGetRights
	#define EXT_UserDBObjectGetRights
	#define GET_UserDBObjectGetRights(fl)  CAL_CMGETAPI( "UserDBObjectGetRights" ) 
	#define CAL_UserDBObjectGetRights pICmpUserDB->IUserDBObjectGetRights
	#define CHK_UserDBObjectGetRights (pICmpUserDB != NULL)
	#define EXP_UserDBObjectGetRights  CAL_CMEXPAPI( "UserDBObjectGetRights" ) 
#else /* DYNAMIC_LINK */
	#define USE_UserDBObjectGetRights  PFUSERDBOBJECTGETRIGHTS pfUserDBObjectGetRights;
	#define EXT_UserDBObjectGetRights  extern PFUSERDBOBJECTGETRIGHTS pfUserDBObjectGetRights;
	#define GET_UserDBObjectGetRights(fl)  s_pfCMGetAPI2( "UserDBObjectGetRights", (RTS_VOID_FCTPTR *)&pfUserDBObjectGetRights, (fl), 0, 0)
	#define CAL_UserDBObjectGetRights  pfUserDBObjectGetRights
	#define CHK_UserDBObjectGetRights  (pfUserDBObjectGetRights != NULL)
	#define EXP_UserDBObjectGetRights  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"UserDBObjectGetRights", (RTS_UINTPTR)UserDBObjectGetRights, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFUSERDBISCONFIGURABLE IUserDBIsConfigurable;
 	PFUSERDBLOAD IUserDBLoad;
 	PFUSERDBSTORE IUserDBStore;
 	PFUSERDBRELEASE IUserDBRelease;
 	PFUSERDBADD IUserDBAdd;
 	PFUSERDBREMOVE IUserDBRemove;
 	PFUSERDBSETPASSWORD IUserDBSetPassword;
 	PFUSERDBGETPASSWORDMD5 IUserDBGetPasswordMD5;
 	PFUSERDBSETPASSWORDMD5 IUserDBSetPasswordMD5;
 	PFUSERDBSETPROPERTY IUserDBSetProperty;
 	PFUSERDBGETFIRST IUserDBGetFirst;
 	PFUSERDBGETNEXT IUserDBGetNext;
 	PFUSERDBOPEN IUserDBOpen;
 	PFUSERDBCLOSE IUserDBClose;
 	PFUSERDBGETNAME IUserDBGetName;
 	PFUSERDBGETPROPERTY IUserDBGetProperty;
 	PFUSERDBCHECKPASSWORD IUserDBCheckPassword;
 	PFUSERDBGETFIRSTGROUP IUserDBGetFirstGroup;
 	PFUSERDBGETNEXTGROUP IUserDBGetNextGroup;
 	PFUSERDBGROUPADD IUserDBGroupAdd;
 	PFUSERDBGROUPREMOVE IUserDBGroupRemove;
 	PFUSERDBGROUPADDUSER IUserDBGroupAddUser;
 	PFUSERDBGROUPREMOVEUSER IUserDBGroupRemoveUser;
 	PFUSERDBGROUPSETPROPERTY IUserDBGroupSetProperty;
 	PFUSERDBGROUPADDMEMBER IUserDBGroupAddMember;
 	PFUSERDBGROUPREMOVEMEMBER IUserDBGroupRemoveMember;
 	PFUSERDBGROUPGETFIRST IUserDBGroupGetFirst;
 	PFUSERDBGROUPGETNEXT IUserDBGroupGetNext;
 	PFUSERDBGROUPOPEN IUserDBGroupOpen;
 	PFUSERDBGROUPCLOSE IUserDBGroupClose;
 	PFUSERDBGROUPGETNAME IUserDBGroupGetName;
 	PFUSERDBGROUPGETPROPERTY IUserDBGroupGetProperty;
 	PFUSERDBGROUPHASUSER IUserDBGroupHasUser;
 	PFUSERDBGROUPGETFIRSTUSER IUserDBGroupGetFirstUser;
 	PFUSERDBGROUPGETNEXTUSER IUserDBGroupGetNextUser;
 	PFUSERDBGROUPHASMEMBER IUserDBGroupHasMember;
 	PFUSERDBGROUPGETFIRSTMEMBER IUserDBGroupGetFirstMember;
 	PFUSERDBGROUPGETNEXTMEMBER IUserDBGroupGetNextMember;
 	PFUSERDBRIGHTSLOAD IUserDBRightsLoad;
 	PFUSERDBRIGHTSSTORE IUserDBRightsStore;
 	PFUSERDBRIGHTSRELEASE IUserDBRightsRelease;
 	PFUSERDBOBJECTADD IUserDBObjectAdd;
 	PFUSERDBOBJECTREMOVE IUserDBObjectRemove;
 	PFUSERDBOBJECTADDCHILD IUserDBObjectAddChild;
 	PFUSERDBOBJECTGETID IUserDBObjectGetID;
 	PFUSERDBOBJECTSETID IUserDBObjectSetID;
 	PFUSERDBOBJECTADDGROUP IUserDBObjectAddGroup;
 	PFUSERDBOBJECTREMOVEGROUP IUserDBObjectRemoveGroup;
 	PFUSERDBOBJECTSETGROUPRIGHTS IUserDBObjectSetGroupRights;
 	PFUSERDBOBJECTSETGROUPDENIEDRIGHTS IUserDBObjectSetGroupDeniedRights;
 	PFUSERDBOBJECTGETFIRST IUserDBObjectGetFirst;
 	PFUSERDBOBJECTGETNEXT IUserDBObjectGetNext;
 	PFUSERDBOBJECTOPEN IUserDBObjectOpen;
 	PFUSERDBOBJECTCLOSE IUserDBObjectClose;
 	PFUSERDBOBJECTGETNAME IUserDBObjectGetName;
 	PFUSERDBOBJECTGETPATH IUserDBObjectGetPath;
 	PFUSERDBOBJECTGETFIRSTCHILD IUserDBObjectGetFirstChild;
 	PFUSERDBOBJECTGETNEXTCHILD IUserDBObjectGetNextChild;
 	PFUSERDBOBJECTGETFATHER IUserDBObjectGetFather;
 	PFUSERDBOBJECTGETFIRSTGROUP IUserDBObjectGetFirstGroup;
 	PFUSERDBOBJECTGETNEXTGROUP IUserDBObjectGetNextGroup;
 	PFUSERDBOBJECTGETGROUPRIGHTS IUserDBObjectGetGroupRights;
 	PFUSERDBOBJECTHASRIGHTS IUserDBObjectHasRights;
 	PFUSERDBOBJECTGETRIGHTS IUserDBObjectGetRights;
 } ICmpUserDB_C;

#ifdef CPLUSPLUS
class ICmpUserDB : public IBase
{
	public:
		virtual RTS_RESULT CDECL IUserDBIsConfigurable(RTS_UI32 *pulPropertyUsers, RTS_UI32 *pulPropertyGroups) =0;
		virtual RTS_RESULT CDECL IUserDBLoad(void) =0;
		virtual RTS_RESULT CDECL IUserDBStore(void) =0;
		virtual RTS_RESULT CDECL IUserDBRelease(void) =0;
		virtual RTS_HANDLE CDECL IUserDBAdd(char *pszUser, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBRemove(RTS_HANDLE hUser) =0;
		virtual RTS_RESULT CDECL IUserDBSetPassword(RTS_HANDLE hUser, char *pszPassword) =0;
		virtual RTS_RESULT CDECL IUserDBGetPasswordMD5(RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL IUserDBSetPasswordMD5(RTS_HANDLE hUser, unsigned char *pbyPasswordMD5, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL IUserDBSetProperty(RTS_HANDLE hUser, RTS_UI32 ulProperty) =0;
		virtual RTS_HANDLE CDECL IUserDBGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGetNext(RTS_HANDLE hPrevUser, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBOpen(char *pszUser, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBClose(RTS_HANDLE hUser) =0;
		virtual RTS_RESULT CDECL IUserDBGetName(RTS_HANDLE hUser, char *pszUser, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL IUserDBGetProperty(RTS_HANDLE hUser, RTS_UI32 *pulProperty) =0;
		virtual RTS_RESULT CDECL IUserDBCheckPassword(RTS_HANDLE hUser, char *pszPassword) =0;
		virtual RTS_HANDLE CDECL IUserDBGetFirstGroup(RTS_HANDLE hUser, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGetNextGroup(RTS_HANDLE hUser, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupAdd(char *pszGroup, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBGroupRemove(RTS_HANDLE hGroup) =0;
		virtual RTS_RESULT CDECL IUserDBGroupAddUser(RTS_HANDLE hGroup, RTS_HANDLE hUser) =0;
		virtual RTS_RESULT CDECL IUserDBGroupRemoveUser(RTS_HANDLE hGroup, RTS_HANDLE hUser) =0;
		virtual RTS_RESULT CDECL IUserDBGroupSetProperty(RTS_HANDLE hGroup, RTS_UI32 ulProperty) =0;
		virtual RTS_RESULT CDECL IUserDBGroupAddMember(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember) =0;
		virtual RTS_RESULT CDECL IUserDBGroupRemoveMember(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupGetNext(RTS_HANDLE hPrevGroup, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupOpen(char *pszGroup, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBGroupClose(RTS_HANDLE hGroup) =0;
		virtual RTS_RESULT CDECL IUserDBGroupGetName(RTS_HANDLE hGroup, char *pszGroup, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL IUserDBGroupGetProperty(RTS_HANDLE hGroup, RTS_UI32 *pulProperty) =0;
		virtual RTS_RESULT CDECL IUserDBGroupHasUser(RTS_HANDLE hGroup, RTS_HANDLE hUser) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupGetFirstUser(RTS_HANDLE hGroup, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupGetNextUser(RTS_HANDLE hGroup, RTS_HANDLE hPrevUser, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBGroupHasMember(RTS_HANDLE hGroup, RTS_HANDLE hGroupMember) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupGetFirstMember(RTS_HANDLE hGroup, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBGroupGetNextMember(RTS_HANDLE hGroup, RTS_HANDLE hPrevGroupMember, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBRightsLoad(void) =0;
		virtual RTS_RESULT CDECL IUserDBRightsStore(void) =0;
		virtual RTS_RESULT CDECL IUserDBRightsRelease(void) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectAdd(char *pszObject, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectRemove(RTS_HANDLE hObject) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectAddChild(RTS_HANDLE hFatherObject, char *pszObject, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetID(RTS_HANDLE hObject, RTS_UI32 *pulID) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetID(RTS_HANDLE hObject, RTS_UI32 ulID) =0;
		virtual RTS_RESULT CDECL IUserDBObjectAddGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup) =0;
		virtual RTS_RESULT CDECL IUserDBObjectRemoveGroup(RTS_HANDLE hObject, RTS_HANDLE hGroup) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectSetGroupDeniedRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 ulDeniedRights) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFirst(RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetNext(RTS_HANDLE hPrevObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectOpen(char *pszObject, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectClose(RTS_HANDLE hObject) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetName(RTS_HANDLE hObject, char *pszObject, int *piMaxLen) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetPath(RTS_HANDLE hObject, char *pszObject, int *piMaxLen) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFirstChild(RTS_HANDLE hFatherObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetNextChild(RTS_HANDLE hFatherObject, RTS_HANDLE hPrevChildObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFather(RTS_HANDLE hChildObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetFirstGroup(RTS_HANDLE hObject, RTS_RESULT *pResult) =0;
		virtual RTS_HANDLE CDECL IUserDBObjectGetNextGroup(RTS_HANDLE hObject, RTS_HANDLE hPrevGroup, RTS_RESULT *pResult) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetGroupRights(RTS_HANDLE hObject, RTS_HANDLE hGroup, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectHasRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 ulRequestedRights) =0;
		virtual RTS_RESULT CDECL IUserDBObjectGetRights(char *pszObject, RTS_HANDLE hUser, RTS_UI32 *pulRights, RTS_UI32 *pulDeniedRights) =0;
};
	#ifndef ITF_CmpUserDB
		#define ITF_CmpUserDB static ICmpUserDB *pICmpUserDB = NULL;
	#endif
	#define EXTITF_CmpUserDB
#else	/*CPLUSPLUS*/
	typedef ICmpUserDB_C		ICmpUserDB;
	#ifndef ITF_CmpUserDB
		#define ITF_CmpUserDB
	#endif
	#define EXTITF_CmpUserDB
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPUSERDBITF_H_*/
