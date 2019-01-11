/***********************************************************************
	A template compontent that uses C++ runtime classes
 */
#ifndef _CMPTEMPLATECPP_H_
#define _CMPTEMPLATECPP_H_

#define CMPID_CmpTemplateCPP	12345
#define CLASSID_CCmpTemplateCPP	12345
#define ITFID_ICmpTemplateCPP	12345

#define COMPONENT_NAME "CmpTemplateCPP"
#define COMPONENT_ID	ADDVENDORID(CMP_VENDORID, CMPID_CmpTemplateCPP)
#define COMPONENT_NAME_UNQUOTED CmpTemplateCPP

#include "SysMemItf.h"


#ifndef COMPONENT_NAME
	#error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif

#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
	#define ComponentEntry		CmpTemplateCPP__Entry
#endif




#endif /*_DEP_H_*/
