 
	
	
#ifndef _CMPEMICONEMUITF_H_
#define _CMPEMICONEMUITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"


/** EXTERN LIB SECTION BEGIN **/

/** EXTERN LIB SECTION END **/


#ifdef __cplusplus
extern "C" {
#endif

bool CDECL CmpEmiconEmu_is_emu(void);
typedef bool (CDECL * PFCMPEMICONEMU_IS_EMU) (void);
#if defined(CMPEMICONEMU_NOTIMPLEMENTED) || defined(CMPEMICONEMU_IS_EMU_NOTIMPLEMENTED)
	#define USE_CmpEmiconEmu_is_emu
	#define EXT_CmpEmiconEmu_is_emu
	#define GET_CmpEmiconEmu_is_emu(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconEmu_is_emu()  (bool)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconEmu_is_emu  FALSE
	#define EXP_CmpEmiconEmu_is_emu  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconEmu_is_emu
	#define EXT_CmpEmiconEmu_is_emu
	#define GET_CmpEmiconEmu_is_emu(fl)  CAL_CMGETAPI( "CmpEmiconEmu_is_emu" ) 
	#define CAL_CmpEmiconEmu_is_emu  CmpEmiconEmu_is_emu
	#define CHK_CmpEmiconEmu_is_emu  TRUE
	#define EXP_CmpEmiconEmu_is_emu  CAL_CMEXPAPI( "CmpEmiconEmu_is_emu" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONEMU_EXTERNAL)
	#define USE_CmpEmiconEmu_is_emu
	#define EXT_CmpEmiconEmu_is_emu
	#define GET_CmpEmiconEmu_is_emu(fl)  CAL_CMGETAPI( "CmpEmiconEmu_is_emu" ) 
	#define CAL_CmpEmiconEmu_is_emu  CmpEmiconEmu_is_emu
	#define CHK_CmpEmiconEmu_is_emu  TRUE
	#define EXP_CmpEmiconEmu_is_emu  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconEmu_is_emu", (RTS_UINTPTR)CmpEmiconEmu_is_emu, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconEmuCmpEmiconEmu_is_emu
	#define EXT_CmpEmiconEmuCmpEmiconEmu_is_emu
	#define GET_CmpEmiconEmuCmpEmiconEmu_is_emu  ERR_OK
	#define CAL_CmpEmiconEmuCmpEmiconEmu_is_emu pICmpEmiconEmu->ICmpEmiconEmu_is_emu
	#define CHK_CmpEmiconEmuCmpEmiconEmu_is_emu (pICmpEmiconEmu != NULL)
	#define EXP_CmpEmiconEmuCmpEmiconEmu_is_emu  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconEmu_is_emu
	#define EXT_CmpEmiconEmu_is_emu
	#define GET_CmpEmiconEmu_is_emu(fl)  CAL_CMGETAPI( "CmpEmiconEmu_is_emu" ) 
	#define CAL_CmpEmiconEmu_is_emu pICmpEmiconEmu->ICmpEmiconEmu_is_emu
	#define CHK_CmpEmiconEmu_is_emu (pICmpEmiconEmu != NULL)
	#define EXP_CmpEmiconEmu_is_emu  CAL_CMEXPAPI( "CmpEmiconEmu_is_emu" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconEmu_is_emu  PFCMPEMICONEMU_IS_EMU pfCmpEmiconEmu_is_emu;
	#define EXT_CmpEmiconEmu_is_emu  extern PFCMPEMICONEMU_IS_EMU pfCmpEmiconEmu_is_emu;
	#define GET_CmpEmiconEmu_is_emu(fl)  s_pfCMGetAPI2( "CmpEmiconEmu_is_emu", (RTS_VOID_FCTPTR *)&pfCmpEmiconEmu_is_emu, (fl), 0, 0)
	#define CAL_CmpEmiconEmu_is_emu  pfCmpEmiconEmu_is_emu
	#define CHK_CmpEmiconEmu_is_emu  (pfCmpEmiconEmu_is_emu != NULL)
	#define EXP_CmpEmiconEmu_is_emu  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconEmu_is_emu", (RTS_UINTPTR)CmpEmiconEmu_is_emu, 0, 0) 
#endif




#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCMPEMICONEMU_IS_EMU ICmpEmiconEmu_is_emu;
 } ICmpEmiconEmu_C;

#ifdef CPLUSPLUS
class ICmpEmiconEmu : public IBase
{
	public:
		virtual bool CDECL ICmpEmiconEmu_is_emu(void) =0;
};
	#ifndef ITF_CmpEmiconEmu
		#define ITF_CmpEmiconEmu static ICmpEmiconEmu *pICmpEmiconEmu = NULL;
	#endif
	#define EXTITF_CmpEmiconEmu
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconEmu_C		ICmpEmiconEmu;
	#ifndef ITF_CmpEmiconEmu
		#define ITF_CmpEmiconEmu
	#endif
	#define EXTITF_CmpEmiconEmu
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONEMUITF_H_*/
