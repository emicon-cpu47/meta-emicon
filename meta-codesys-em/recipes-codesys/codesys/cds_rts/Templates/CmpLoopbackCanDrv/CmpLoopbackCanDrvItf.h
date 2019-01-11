 
	
	
#ifndef _CMPLOOPBACKCANDRVITF_H_
#define _CMPLOOPBACKCANDRVITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

#ifdef __cplusplus
extern "C" {
#endif

int CDECL Loopback_CanMiniDriver_Setup(void);
typedef int (CDECL * PFLOOPBACK_CANMINIDRIVER_SETUP) (void);
#if defined(CMPLOOPBACKCANDRV_NOTIMPLEMENTED) || defined(LOOPBACK_CANMINIDRIVER_SETUP_NOTIMPLEMENTED)
	#define USE_Loopback_CanMiniDriver_Setup
	#define EXT_Loopback_CanMiniDriver_Setup
	#define GET_Loopback_CanMiniDriver_Setup(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Loopback_CanMiniDriver_Setup()  (int)ERR_NOTIMPLEMENTED
	#define CHK_Loopback_CanMiniDriver_Setup  FALSE
	#define EXP_Loopback_CanMiniDriver_Setup  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Loopback_CanMiniDriver_Setup
	#define EXT_Loopback_CanMiniDriver_Setup
	#define GET_Loopback_CanMiniDriver_Setup(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Setup" ) 
	#define CAL_Loopback_CanMiniDriver_Setup  Loopback_CanMiniDriver_Setup
	#define CHK_Loopback_CanMiniDriver_Setup  TRUE
	#define EXP_Loopback_CanMiniDriver_Setup  CAL_CMEXPAPI( "Loopback_CanMiniDriver_Setup" ) 
#elif defined(MIXED_LINK) && !defined(CMPLOOPBACKCANDRV_EXTERNAL)
	#define USE_Loopback_CanMiniDriver_Setup
	#define EXT_Loopback_CanMiniDriver_Setup
	#define GET_Loopback_CanMiniDriver_Setup(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Setup" ) 
	#define CAL_Loopback_CanMiniDriver_Setup  Loopback_CanMiniDriver_Setup
	#define CHK_Loopback_CanMiniDriver_Setup  TRUE
	#define EXP_Loopback_CanMiniDriver_Setup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Loopback_CanMiniDriver_Setup", (RTS_UINTPTR)Loopback_CanMiniDriver_Setup, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpLoopbackCanDrvLoopback_CanMiniDriver_Setup
	#define EXT_CmpLoopbackCanDrvLoopback_CanMiniDriver_Setup
	#define GET_CmpLoopbackCanDrvLoopback_CanMiniDriver_Setup  ERR_OK
	#define CAL_CmpLoopbackCanDrvLoopback_CanMiniDriver_Setup pICmpLoopbackCanDrv->ILoopback_CanMiniDriver_Setup
	#define CHK_CmpLoopbackCanDrvLoopback_CanMiniDriver_Setup (pICmpLoopbackCanDrv != NULL)
	#define EXP_CmpLoopbackCanDrvLoopback_CanMiniDriver_Setup  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Loopback_CanMiniDriver_Setup
	#define EXT_Loopback_CanMiniDriver_Setup
	#define GET_Loopback_CanMiniDriver_Setup(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Setup" ) 
	#define CAL_Loopback_CanMiniDriver_Setup pICmpLoopbackCanDrv->ILoopback_CanMiniDriver_Setup
	#define CHK_Loopback_CanMiniDriver_Setup (pICmpLoopbackCanDrv != NULL)
	#define EXP_Loopback_CanMiniDriver_Setup  CAL_CMEXPAPI( "Loopback_CanMiniDriver_Setup" ) 
#else /* DYNAMIC_LINK */
	#define USE_Loopback_CanMiniDriver_Setup  PFLOOPBACK_CANMINIDRIVER_SETUP pfLoopback_CanMiniDriver_Setup;
	#define EXT_Loopback_CanMiniDriver_Setup  extern PFLOOPBACK_CANMINIDRIVER_SETUP pfLoopback_CanMiniDriver_Setup;
	#define GET_Loopback_CanMiniDriver_Setup(fl)  s_pfCMGetAPI2( "Loopback_CanMiniDriver_Setup", (RTS_VOID_FCTPTR *)&pfLoopback_CanMiniDriver_Setup, (fl), 0, 0)
	#define CAL_Loopback_CanMiniDriver_Setup  pfLoopback_CanMiniDriver_Setup
	#define CHK_Loopback_CanMiniDriver_Setup  (pfLoopback_CanMiniDriver_Setup != NULL)
	#define EXP_Loopback_CanMiniDriver_Setup  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Loopback_CanMiniDriver_Setup", (RTS_UINTPTR)Loopback_CanMiniDriver_Setup, 0, 0) 
#endif



int CDECL Loopback_CanMiniDriver_Dispose(void);
typedef int (CDECL * PFLOOPBACK_CANMINIDRIVER_DISPOSE) (void);
#if defined(CMPLOOPBACKCANDRV_NOTIMPLEMENTED) || defined(LOOPBACK_CANMINIDRIVER_DISPOSE_NOTIMPLEMENTED)
	#define USE_Loopback_CanMiniDriver_Dispose
	#define EXT_Loopback_CanMiniDriver_Dispose
	#define GET_Loopback_CanMiniDriver_Dispose(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Loopback_CanMiniDriver_Dispose()  (int)ERR_NOTIMPLEMENTED
	#define CHK_Loopback_CanMiniDriver_Dispose  FALSE
	#define EXP_Loopback_CanMiniDriver_Dispose  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Loopback_CanMiniDriver_Dispose
	#define EXT_Loopback_CanMiniDriver_Dispose
	#define GET_Loopback_CanMiniDriver_Dispose(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Dispose" ) 
	#define CAL_Loopback_CanMiniDriver_Dispose  Loopback_CanMiniDriver_Dispose
	#define CHK_Loopback_CanMiniDriver_Dispose  TRUE
	#define EXP_Loopback_CanMiniDriver_Dispose  CAL_CMEXPAPI( "Loopback_CanMiniDriver_Dispose" ) 
#elif defined(MIXED_LINK) && !defined(CMPLOOPBACKCANDRV_EXTERNAL)
	#define USE_Loopback_CanMiniDriver_Dispose
	#define EXT_Loopback_CanMiniDriver_Dispose
	#define GET_Loopback_CanMiniDriver_Dispose(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Dispose" ) 
	#define CAL_Loopback_CanMiniDriver_Dispose  Loopback_CanMiniDriver_Dispose
	#define CHK_Loopback_CanMiniDriver_Dispose  TRUE
	#define EXP_Loopback_CanMiniDriver_Dispose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Loopback_CanMiniDriver_Dispose", (RTS_UINTPTR)Loopback_CanMiniDriver_Dispose, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpLoopbackCanDrvLoopback_CanMiniDriver_Dispose
	#define EXT_CmpLoopbackCanDrvLoopback_CanMiniDriver_Dispose
	#define GET_CmpLoopbackCanDrvLoopback_CanMiniDriver_Dispose  ERR_OK
	#define CAL_CmpLoopbackCanDrvLoopback_CanMiniDriver_Dispose pICmpLoopbackCanDrv->ILoopback_CanMiniDriver_Dispose
	#define CHK_CmpLoopbackCanDrvLoopback_CanMiniDriver_Dispose (pICmpLoopbackCanDrv != NULL)
	#define EXP_CmpLoopbackCanDrvLoopback_CanMiniDriver_Dispose  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Loopback_CanMiniDriver_Dispose
	#define EXT_Loopback_CanMiniDriver_Dispose
	#define GET_Loopback_CanMiniDriver_Dispose(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Dispose" ) 
	#define CAL_Loopback_CanMiniDriver_Dispose pICmpLoopbackCanDrv->ILoopback_CanMiniDriver_Dispose
	#define CHK_Loopback_CanMiniDriver_Dispose (pICmpLoopbackCanDrv != NULL)
	#define EXP_Loopback_CanMiniDriver_Dispose  CAL_CMEXPAPI( "Loopback_CanMiniDriver_Dispose" ) 
#else /* DYNAMIC_LINK */
	#define USE_Loopback_CanMiniDriver_Dispose  PFLOOPBACK_CANMINIDRIVER_DISPOSE pfLoopback_CanMiniDriver_Dispose;
	#define EXT_Loopback_CanMiniDriver_Dispose  extern PFLOOPBACK_CANMINIDRIVER_DISPOSE pfLoopback_CanMiniDriver_Dispose;
	#define GET_Loopback_CanMiniDriver_Dispose(fl)  s_pfCMGetAPI2( "Loopback_CanMiniDriver_Dispose", (RTS_VOID_FCTPTR *)&pfLoopback_CanMiniDriver_Dispose, (fl), 0, 0)
	#define CAL_Loopback_CanMiniDriver_Dispose  pfLoopback_CanMiniDriver_Dispose
	#define CHK_Loopback_CanMiniDriver_Dispose  (pfLoopback_CanMiniDriver_Dispose != NULL)
	#define EXP_Loopback_CanMiniDriver_Dispose  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Loopback_CanMiniDriver_Dispose", (RTS_UINTPTR)Loopback_CanMiniDriver_Dispose, 0, 0) 
#endif



void CDECL Loopback_CanMiniDriver_Handler(void);
typedef void (CDECL * PFLOOPBACK_CANMINIDRIVER_HANDLER) (void);
#if defined(CMPLOOPBACKCANDRV_NOTIMPLEMENTED) || defined(LOOPBACK_CANMINIDRIVER_HANDLER_NOTIMPLEMENTED)
	#define USE_Loopback_CanMiniDriver_Handler
	#define EXT_Loopback_CanMiniDriver_Handler
	#define GET_Loopback_CanMiniDriver_Handler(fl)  ERR_NOTIMPLEMENTED
	#define CAL_Loopback_CanMiniDriver_Handler()  
	#define CHK_Loopback_CanMiniDriver_Handler  FALSE
	#define EXP_Loopback_CanMiniDriver_Handler  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_Loopback_CanMiniDriver_Handler
	#define EXT_Loopback_CanMiniDriver_Handler
	#define GET_Loopback_CanMiniDriver_Handler(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Handler" ) 
	#define CAL_Loopback_CanMiniDriver_Handler  Loopback_CanMiniDriver_Handler
	#define CHK_Loopback_CanMiniDriver_Handler  TRUE
	#define EXP_Loopback_CanMiniDriver_Handler  CAL_CMEXPAPI( "Loopback_CanMiniDriver_Handler" ) 
#elif defined(MIXED_LINK) && !defined(CMPLOOPBACKCANDRV_EXTERNAL)
	#define USE_Loopback_CanMiniDriver_Handler
	#define EXT_Loopback_CanMiniDriver_Handler
	#define GET_Loopback_CanMiniDriver_Handler(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Handler" ) 
	#define CAL_Loopback_CanMiniDriver_Handler  Loopback_CanMiniDriver_Handler
	#define CHK_Loopback_CanMiniDriver_Handler  TRUE
	#define EXP_Loopback_CanMiniDriver_Handler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Loopback_CanMiniDriver_Handler", (RTS_UINTPTR)Loopback_CanMiniDriver_Handler, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpLoopbackCanDrvLoopback_CanMiniDriver_Handler
	#define EXT_CmpLoopbackCanDrvLoopback_CanMiniDriver_Handler
	#define GET_CmpLoopbackCanDrvLoopback_CanMiniDriver_Handler  ERR_OK
	#define CAL_CmpLoopbackCanDrvLoopback_CanMiniDriver_Handler pICmpLoopbackCanDrv->ILoopback_CanMiniDriver_Handler
	#define CHK_CmpLoopbackCanDrvLoopback_CanMiniDriver_Handler (pICmpLoopbackCanDrv != NULL)
	#define EXP_CmpLoopbackCanDrvLoopback_CanMiniDriver_Handler  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_Loopback_CanMiniDriver_Handler
	#define EXT_Loopback_CanMiniDriver_Handler
	#define GET_Loopback_CanMiniDriver_Handler(fl)  CAL_CMGETAPI( "Loopback_CanMiniDriver_Handler" ) 
	#define CAL_Loopback_CanMiniDriver_Handler pICmpLoopbackCanDrv->ILoopback_CanMiniDriver_Handler
	#define CHK_Loopback_CanMiniDriver_Handler (pICmpLoopbackCanDrv != NULL)
	#define EXP_Loopback_CanMiniDriver_Handler  CAL_CMEXPAPI( "Loopback_CanMiniDriver_Handler" ) 
#else /* DYNAMIC_LINK */
	#define USE_Loopback_CanMiniDriver_Handler  PFLOOPBACK_CANMINIDRIVER_HANDLER pfLoopback_CanMiniDriver_Handler;
	#define EXT_Loopback_CanMiniDriver_Handler  extern PFLOOPBACK_CANMINIDRIVER_HANDLER pfLoopback_CanMiniDriver_Handler;
	#define GET_Loopback_CanMiniDriver_Handler(fl)  s_pfCMGetAPI2( "Loopback_CanMiniDriver_Handler", (RTS_VOID_FCTPTR *)&pfLoopback_CanMiniDriver_Handler, (fl), 0, 0)
	#define CAL_Loopback_CanMiniDriver_Handler  pfLoopback_CanMiniDriver_Handler
	#define CHK_Loopback_CanMiniDriver_Handler  (pfLoopback_CanMiniDriver_Handler != NULL)
	#define EXP_Loopback_CanMiniDriver_Handler  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"Loopback_CanMiniDriver_Handler", (RTS_UINTPTR)Loopback_CanMiniDriver_Handler, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFLOOPBACK_CANMINIDRIVER_SETUP ILoopback_CanMiniDriver_Setup;
 	PFLOOPBACK_CANMINIDRIVER_DISPOSE ILoopback_CanMiniDriver_Dispose;
 	PFLOOPBACK_CANMINIDRIVER_HANDLER ILoopback_CanMiniDriver_Handler;
 } ICmpLoopbackCanDrv_C;

#ifdef CPLUSPLUS
class ICmpLoopbackCanDrv : public IBase
{
	public:
		virtual int CDECL ILoopback_CanMiniDriver_Setup(void) =0;
		virtual int CDECL ILoopback_CanMiniDriver_Dispose(void) =0;
		virtual void CDECL ILoopback_CanMiniDriver_Handler(void) =0;
};
	#ifndef ITF_CmpLoopbackCanDrv
		#define ITF_CmpLoopbackCanDrv static ICmpLoopbackCanDrv *pICmpLoopbackCanDrv = NULL;
	#endif
	#define EXTITF_CmpLoopbackCanDrv
#else	/*CPLUSPLUS*/
	typedef ICmpLoopbackCanDrv_C		ICmpLoopbackCanDrv;
	#ifndef ITF_CmpLoopbackCanDrv
		#define ITF_CmpLoopbackCanDrv
	#endif
	#define EXTITF_CmpLoopbackCanDrv
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPLOOPBACKCANDRVITF_H_*/
