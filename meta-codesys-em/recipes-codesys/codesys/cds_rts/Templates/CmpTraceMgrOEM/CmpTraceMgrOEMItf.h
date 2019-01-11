 
	
	
#ifndef _CMPTRACEMGROEMITF_H_
#define _CMPTRACEMGROEMITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpTraceMgrOEM_C;

#ifdef CPLUSPLUS
class ICmpTraceMgrOEM : public IBase
{
	public:
};
	#ifndef ITF_CmpTraceMgrOEM
		#define ITF_CmpTraceMgrOEM static ICmpTraceMgrOEM *pICmpTraceMgrOEM = NULL;
	#endif
	#define EXTITF_CmpTraceMgrOEM
#else	/*CPLUSPLUS*/
	typedef ICmpTraceMgrOEM_C		ICmpTraceMgrOEM;
	#ifndef ITF_CmpTraceMgrOEM
		#define ITF_CmpTraceMgrOEM
	#endif
	#define EXTITF_CmpTraceMgrOEM
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPTRACEMGROEMITF_H_*/
