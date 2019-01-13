 
	
	
#ifndef _CMPEMICONEVENTSCONTROLITF_H_
#define _CMPEMICONEVENTSCONTROLITF_H_

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
} ICmpEmiconEventsControl_C;

#ifdef CPLUSPLUS
class ICmpEmiconEventsControl : public IBase
{
	public:
};
	#ifndef ITF_CmpEmiconEventsControl
		#define ITF_CmpEmiconEventsControl static ICmpEmiconEventsControl *pICmpEmiconEventsControl = NULL;
	#endif
	#define EXTITF_CmpEmiconEventsControl
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconEventsControl_C		ICmpEmiconEventsControl;
	#ifndef ITF_CmpEmiconEventsControl
		#define ITF_CmpEmiconEventsControl
	#endif
	#define EXTITF_CmpEmiconEventsControl
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONEVENTSCONTROLITF_H_*/
