 
	
	
#ifndef _CMPLEDMGRITF_H_
#define _CMPLEDMGRITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


/** EXTERN LIB SECTION BEGIN **/

#ifdef __cplusplus
extern "C" {
#endif

/* NOTE: Add your interface functions here.*/


#ifdef __cplusplus
}
#endif




typedef struct
{
	IBase_C *pBase;
} ICmpLEDMgr_C;

#ifdef CPLUSPLUS
class ICmpLEDMgr : public IBase
{
	public:
};
	#ifndef ITF_CmpLEDMgr
		#define ITF_CmpLEDMgr static ICmpLEDMgr *pICmpLEDMgr = NULL;
	#endif
	#define EXTITF_CmpLEDMgr
#else	/*CPLUSPLUS*/
	typedef ICmpLEDMgr_C		ICmpLEDMgr;
	#ifndef ITF_CmpLEDMgr
		#define ITF_CmpLEDMgr
	#endif
	#define EXTITF_CmpLEDMgr
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPLEDMGRITF_H_*/
