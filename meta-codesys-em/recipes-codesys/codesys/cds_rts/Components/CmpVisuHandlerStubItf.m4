/**
 * <interfacename>CmpVisuHandlerStub</interfacename>
 * <description> 
 *	Interface for the visu handler stub.
 * </description>
 *
 * <copyright>
 * Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 * </copyright>
 */

SET_INTERFACE_NAME(`CmpVisuHandlerStub')

/**
 * <category>Settings</category>
 * <description>The basename for the ipcchannel.
 *	IMPORTANT: The according targetvisustub must have configured the same basename ! </description>
 */
#define CMPVISUHANDLERSTUB_KEY_TARGETVISUPROCESS_IPCBASENAME				"IpcBasename"
#define CMPVISUHANDLERSTUB_KEY_TARGETVISUPROCESS_IPCBASENAME_DEFAULT		"Ipc__Targetvisu__"

/**
 * <category>Settings</category>
 * <description>Setting that decides about the timeout that is used for single ipccalls </description>
 */
#define CMPVISUHANDLERSTUB_KEY_IPCTIMEOUT				"IpcTimeoutMs"
#define CMPVISUHANDLERSTUB_KEY_IPCTIMEOUT_DEFAULT		5000

/**
 * <category>Settings</category>
 * <description>The basename of the sharedmemory. Will be followed by the externid of the specific client.
 * IMPORTANT: The according visualization must have configured the same basename ! </description>
 */
#define CMPVISUHANDLERSTUB_KEY_TARGETVISUPROCESS_SHMBASENAME				"SharedMemoryBasename"
#define CMPVISUHANDLERSTUB_KEY_TARGETVISUPROCESS_SHMBASENAME_DEFAULT		"SHM_EXTERN_TARGETVISU_"

