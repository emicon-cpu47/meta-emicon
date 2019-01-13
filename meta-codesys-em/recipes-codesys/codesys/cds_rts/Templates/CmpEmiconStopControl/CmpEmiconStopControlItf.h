 
	
	
#ifndef _CMPEMICONSTOPCONTROLITF_H_
#define _CMPEMICONSTOPCONTROLITF_H_

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
} ICmpEmiconStopControl_C;

#ifdef CPLUSPLUS
class ICmpEmiconStopControl : public IBase
{
	public:
};
	#ifndef ITF_CmpEmiconStopControl
		#define ITF_CmpEmiconStopControl static ICmpEmiconStopControl *pICmpEmiconStopControl = NULL;
	#endif
	#define EXTITF_CmpEmiconStopControl
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconStopControl_C		ICmpEmiconStopControl;
	#ifndef ITF_CmpEmiconStopControl
		#define ITF_CmpEmiconStopControl
	#endif
	#define EXTITF_CmpEmiconStopControl
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONSTOPCONTROLITF_H_*/
