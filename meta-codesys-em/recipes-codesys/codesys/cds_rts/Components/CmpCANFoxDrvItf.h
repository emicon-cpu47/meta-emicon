 
	
	
#ifndef _CMPCANFOXDRVITF_H_
#define _CMPCANFOXDRVITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"
#include "CAATypes.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ReceiveEventName "CmpCANFoxReceiveEvent"
#define ErrorEventName "CmpCANFoxErrorEvent"


typedef struct _canfoxhwinfotag_
{
	int NetNumber; /* SIECA32 Net number */ 
	void* Handle;
    char Name[20];
	CAA_BOOL xOpened;
	CAA_BOOL bTxBufferFull;
}CANFOX_HW_INFO;

typedef struct _canfoxinfotag_
{
	RTS_HANDLE hSem;
	CANFOX_HW_INFO hwInfo;
	CAA_WORD wBaudrate;
	unsigned long reset_current;
	unsigned long reset_last;

}CANFOX_INFO;

#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpCANFoxDrv_C;

#ifdef CPLUSPLUS
class ICmpCANFoxDrv : public IBase
{
	public:
};
	#ifndef ITF_CmpCANFoxDrv
		#define ITF_CmpCANFoxDrv static ICmpCANFoxDrv *pICmpCANFoxDrv = NULL;
	#endif
	#define EXTITF_CmpCANFoxDrv
#else	/*CPLUSPLUS*/
	typedef ICmpCANFoxDrv_C		ICmpCANFoxDrv;
	#ifndef ITF_CmpCANFoxDrv
		#define ITF_CmpCANFoxDrv
	#endif
	#define EXTITF_CmpCANFoxDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCANFOXDRVITF_H_*/
