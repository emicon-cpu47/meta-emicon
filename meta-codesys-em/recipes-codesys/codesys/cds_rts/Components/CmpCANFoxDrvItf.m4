SET_INTERFACE_NAME(`CmpCANFoxDrv')

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
