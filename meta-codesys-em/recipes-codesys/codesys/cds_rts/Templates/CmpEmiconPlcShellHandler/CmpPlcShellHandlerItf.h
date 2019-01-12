 /**
 * <interfacename>test</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPPLCSHELLHANDLERITF_H_
#define _CMPPLCSHELLHANDLERITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpPlcShellHandler_C;

#ifdef CPLUSPLUS
class ICmpPlcShellHandler : public IBase
{
	public:
};
	#ifndef ITF_CmpPlcShellHandler
		#define ITF_CmpPlcShellHandler static ICmpPlcShellHandler *pICmpPlcShellHandler = NULL;
	#endif
	#define EXTITF_CmpPlcShellHandler
#else	/*CPLUSPLUS*/
	typedef ICmpPlcShellHandler_C		ICmpPlcShellHandler;
	#ifndef ITF_CmpPlcShellHandler
		#define ITF_CmpPlcShellHandler
	#endif
	#define EXTITF_CmpPlcShellHandler
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPPLCSHELLHANDLERITF_H_*/
