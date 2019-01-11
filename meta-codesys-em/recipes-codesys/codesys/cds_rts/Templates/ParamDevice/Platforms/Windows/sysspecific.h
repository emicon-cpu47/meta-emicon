#ifndef __SYSSPECIFIC__H__
#define __SYSSPECIFIC__H__

/* 
 * ---WIN32 specific---
 * 
 * This file is included by CmpStd.h.
 * It may contain system specific include files etc. 
 * 
 */

#ifdef CPLUSPLUS
	/* at the moment there is no C++ target visu available */
	#define CREATETARGETVISUINSTANCE_NOTIMPLEMENTED
	#define DESTROYTARGETVISUINSTANCE_NOTIMPLEMENTED
	/* ... and also no user manager */
	#define CMPUSERMGR_NOTIMPLEMENTED
#endif

#include <conio.h>

#include "ParamDevice_NotImpl.h"

#endif	/*__SYSSPECIFIC__H__*/
