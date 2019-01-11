 
	
	
#ifndef _CMPTEMPLATEEMPTYITF_H_
#define _CMPTEMPLATEEMPTYITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


/** EXTERN LIB SECTION BEGIN **/

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpTemplateEmpty_C;

#ifdef CPLUSPLUS
class ICmpTemplateEmpty : public IBase
{
	public:
};
	#ifndef ITF_CmpTemplateEmpty
		#define ITF_CmpTemplateEmpty static ICmpTemplateEmpty *pICmpTemplateEmpty = NULL;
	#endif
	#define EXTITF_CmpTemplateEmpty
#else	/*CPLUSPLUS*/
	typedef ICmpTemplateEmpty_C		ICmpTemplateEmpty;
	#ifndef ITF_CmpTemplateEmpty
		#define ITF_CmpTemplateEmpty
	#endif
	#define EXTITF_CmpTemplateEmpty
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTEMPLATEEMPTYITF_H_*/
