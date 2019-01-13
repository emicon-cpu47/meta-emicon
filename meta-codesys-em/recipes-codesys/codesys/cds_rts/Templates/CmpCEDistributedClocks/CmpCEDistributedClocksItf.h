 
	
	
#ifndef _CMPCEDISTRIBUTEDCLOCKSITF_H_
#define _CMPCEDISTRIBUTEDCLOCKSITF_H_

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
} ICmpCEDistributedClocks_C;

#ifdef CPLUSPLUS
class ICmpCEDistributedClocks : public IBase
{
	public:
};
	#ifndef ITF_CmpCEDistributedClocks
		#define ITF_CmpCEDistributedClocks static ICmpCEDistributedClocks *pICmpCEDistributedClocks = NULL;
	#endif
	#define EXTITF_CmpCEDistributedClocks
#else	/*CPLUSPLUS*/
	typedef ICmpCEDistributedClocks_C		ICmpCEDistributedClocks;
	#ifndef ITF_CmpCEDistributedClocks
		#define ITF_CmpCEDistributedClocks
	#endif
	#define EXTITF_CmpCEDistributedClocks
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCEDISTRIBUTEDCLOCKSITF_H_*/
