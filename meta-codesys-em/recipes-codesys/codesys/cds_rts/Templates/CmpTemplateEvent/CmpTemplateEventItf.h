 
	
	
#ifndef _CMPTEMPLATEEVENTITF_H_
#define _CMPTEMPLATEEVENTITF_H_

#include "CmpStd.h"

 

 






typedef struct
{
	IBase_C *pBase;
} ICmpTemplateEvent_C;

#ifdef CPLUSPLUS
class ICmpTemplateEvent : public IBase
{
	public:
};
	#ifndef ITF_CmpTemplateEvent
		#define ITF_CmpTemplateEvent static ICmpTemplateEvent *pICmpTemplateEvent = NULL;
	#endif
	#define EXTITF_CmpTemplateEvent
#else	/*CPLUSPLUS*/
	typedef ICmpTemplateEvent_C		ICmpTemplateEvent;
	#ifndef ITF_CmpTemplateEvent
		#define ITF_CmpTemplateEvent
	#endif
	#define EXTITF_CmpTemplateEvent
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTEMPLATEEVENTITF_H_*/
