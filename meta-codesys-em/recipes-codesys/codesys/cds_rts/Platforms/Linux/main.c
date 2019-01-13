#include "CmpStd.h"
#include "CMItf.h"
#include "profile.h"

COMPO_INIT_DECLS

StaticComponent SysMainComponentList[] = {
	COMPO_INIT_LIST,
	{NULL, NULL, 0}
};

RTS_RESULT MainLoadComponent2(char *pszName, PF_COMPONENT_ENTRY* ppfComponentEntry)
{
	return ERR_FAILED;
}