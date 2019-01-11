 
	
	
#ifndef _CMPDC_TIMER_WECITF_H_
#define _CMPDC_TIMER_WECITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#define CH_USER_1						10000
/*	First user hook
	ulParam1: Not used
	ulParam2: Not used
*/

/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif


#ifdef __cplusplus
}
#endif

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
} ICmpDC_Timer_WEC_C;

#ifdef CPLUSPLUS
class ICmpDC_Timer_WEC : public IBase
{
	public:
};
	#ifndef ITF_CmpDC_Timer_WEC
		#define ITF_CmpDC_Timer_WEC static ICmpDC_Timer_WEC *pICmpDC_Timer_WEC = NULL;
	#endif
	#define EXTITF_CmpDC_Timer_WEC
#else	/*CPLUSPLUS*/
	typedef ICmpDC_Timer_WEC_C		ICmpDC_Timer_WEC;
	#ifndef ITF_CmpDC_Timer_WEC
		#define ITF_CmpDC_Timer_WEC
	#endif
	#define EXTITF_CmpDC_Timer_WEC
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPDC_TIMER_WECITF_H_*/
