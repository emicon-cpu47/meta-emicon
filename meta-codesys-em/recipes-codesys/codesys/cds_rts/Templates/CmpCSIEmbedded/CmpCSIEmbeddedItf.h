 
	
	
#ifndef _CMPCSIEMBEDDEDITF_H_
#define _CMPCSIEMBEDDEDITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

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
} ICmpCSIEmbedded_C;

#ifdef CPLUSPLUS
class ICmpCSIEmbedded : public IBase
{
	public:
};
	#ifndef ITF_CmpCSIEmbedded
		#define ITF_CmpCSIEmbedded static ICmpCSIEmbedded *pICmpCSIEmbedded = NULL;
	#endif
	#define EXTITF_CmpCSIEmbedded
#else	/*CPLUSPLUS*/
	typedef ICmpCSIEmbedded_C		ICmpCSIEmbedded;
	#ifndef ITF_CmpCSIEmbedded
		#define ITF_CmpCSIEmbedded
	#endif
	#define EXTITF_CmpCSIEmbedded
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCSIEMBEDDEDITF_H_*/
