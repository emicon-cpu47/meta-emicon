 
	
	
#ifndef _CMPTEMPLATEEVENTIECITF_H_
#define _CMPTEMPLATEEVENTIECITF_H_

#include "CmpStd.h"

 

 




#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>EVTPARAM_EvtTest</description>
 */
typedef struct tagEVTPARAM_EvtTest
{
	RTS_IEC_DWORD dwParam1;		/* a test parameter */
	RTS_IEC_BOOL xParam2;		/* another test parameter */
} EVTPARAM_EvtTest;

#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
} ICmpTemplateEventIEC_C;

#ifdef CPLUSPLUS
class ICmpTemplateEventIEC : public IBase
{
	public:
};
	#ifndef ITF_CmpTemplateEventIEC
		#define ITF_CmpTemplateEventIEC static ICmpTemplateEventIEC *pICmpTemplateEventIEC = NULL;
	#endif
	#define EXTITF_CmpTemplateEventIEC
#else	/*CPLUSPLUS*/
	typedef ICmpTemplateEventIEC_C		ICmpTemplateEventIEC;
	#ifndef ITF_CmpTemplateEventIEC
		#define ITF_CmpTemplateEventIEC
	#endif
	#define EXTITF_CmpTemplateEventIEC
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTEMPLATEEVENTIECITF_H_*/
