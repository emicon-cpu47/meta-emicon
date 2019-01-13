 /**
 * <interfacename>CmpEmiconNetwork</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _CMPEMICONNETWORKITF_H_
#define _CMPEMICONNETWORKITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>EmPLCConfigurator_NTPCfg</description>
 */
typedef struct tagEmPLCConfigurator_NTPCfg
{
	RTS_IEC_WORD period;		/* период синхронизации времени в минутах (если 0 то синхронизация не осуществляется) */
	RTS_IEC_BYTE IP1[4];		/* основной IP адрес NTP сервера (4 тетрады) */
	RTS_IEC_BYTE IP2[4];		/* резервный IP адрес NTP сервера (4 тетрады) */
	RTS_IEC_WORD slot1;		/* Номер слота для запроса по основному адресу */
	RTS_IEC_WORD slot2;		/* Номер слота для запроса по резервному адресу */
	RTS_IEC_WORD socket1;		/* Номер сокета для запроса по основному адресу */
	RTS_IEC_WORD socket2;		/* Номер сокета для запроса по резервному адресу */
	RTS_IEC_WORD retries;		/* количество переповторов для каждого запроса */
	RTS_IEC_INT utc_offset;		/* часовой пояс */
} EmPLCConfigurator_NTPCfg;

/**
 * <description>EmPLCConfigurator_TCfgFlagsStruc</description>
 */
typedef struct tagEmPLCConfigurator_TCfgFlagsStruc
{
	RTS_IEC_USINT fCheckReserved : 1;		/* бит 0 = 1, если используется резервирование CPU */
	RTS_IEC_USINT fZeroMappedOnDownload : 1;		/* бит 1 = 1, если требуется обнуление адресуемой памяти при загрузке проекта */
	RTS_IEC_USINT fSwitchNoLink : 1;		/* бит 2 = 1, если требуется переход на резервный CPU при потере связи с УСО */
	RTS_IEC_USINT fDsblNoLinkFlg : 1;		/* бит 3 = 1, если не требуется взведение бита недостоверности входов при отсутствии связи с УСО */
	RTS_IEC_USINT fNoLinkPollEnable : 1;		/* бит 4 = 1, если не требуется исключение из опроса УСО, с которыми нет связи */
	RTS_IEC_USINT fCi31PollOptimize : 1;		/* бит 5 = 1, если требуется выполнять опрос удаленных устройств не в начале, а во время рабочего цикла */
	RTS_IEC_USINT fDisSwitchOnC44InitErr : 1;		/* бит 6 = 1, если не требуется переход на резерный CPU при ошибке инициализации С-44 */
	RTS_IEC_USINT f_switch_ip_x3 : 1;		/* бит 7 = 1, требуется увеличение на 1 IP-адреса канала X3 при переходе на резерв */
} EmPLCConfigurator_TCfgFlagsStruc;

/**
 * <description>EmPLCConfigurator_TCfgFlagsUnion</description>
 */
typedef union
{
	EmPLCConfigurator_TCfgFlagsStruc flags;		
	RTS_IEC_WORD wReg;		
} EmPLCConfigurator_TCfgFlagsUnion;

/**
 * <description>reset_ip</description>
 */
typedef struct tagreset_ip_struct
{
	RTS_IEC_INT reset_ip;				/* VAR_OUTPUT */	
} reset_ip_struct;

void CDECL CDECL_EXT reset_ip(reset_ip_struct *p);
typedef void (CDECL CDECL_EXT* PFRESET_IP_IEC) (reset_ip_struct *p);
#if defined(CMPEMICONNETWORK_NOTIMPLEMENTED) || defined(RESET_IP_NOTIMPLEMENTED)
	#define USE_reset_ip
	#define EXT_reset_ip
	#define GET_reset_ip(fl)  ERR_NOTIMPLEMENTED
	#define CAL_reset_ip(p0) 
	#define CHK_reset_ip  FALSE
	#define EXP_reset_ip  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_reset_ip
	#define EXT_reset_ip
	#define GET_reset_ip(fl)  CAL_CMGETAPI( "reset_ip" ) 
	#define CAL_reset_ip  reset_ip
	#define CHK_reset_ip  TRUE
	#define EXP_reset_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"reset_ip", (RTS_UINTPTR)reset_ip, 1, 0x76DED90E, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONNETWORK_EXTERNAL)
	#define USE_reset_ip
	#define EXT_reset_ip
	#define GET_reset_ip(fl)  CAL_CMGETAPI( "reset_ip" ) 
	#define CAL_reset_ip  reset_ip
	#define CHK_reset_ip  TRUE
	#define EXP_reset_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"reset_ip", (RTS_UINTPTR)reset_ip, 1, 0x76DED90E, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconNetworkreset_ip
	#define EXT_CmpEmiconNetworkreset_ip
	#define GET_CmpEmiconNetworkreset_ip  ERR_OK
	#define CAL_CmpEmiconNetworkreset_ip  reset_ip
	#define CHK_CmpEmiconNetworkreset_ip  TRUE
	#define EXP_CmpEmiconNetworkreset_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"reset_ip", (RTS_UINTPTR)reset_ip, 1, 0x76DED90E, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_reset_ip
	#define EXT_reset_ip
	#define GET_reset_ip(fl)  CAL_CMGETAPI( "reset_ip" ) 
	#define CAL_reset_ip  reset_ip
	#define CHK_reset_ip  TRUE
	#define EXP_reset_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"reset_ip", (RTS_UINTPTR)reset_ip, 1, 0x76DED90E, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_reset_ip  PFRESET_IP_IEC pfreset_ip;
	#define EXT_reset_ip  extern PFRESET_IP_IEC pfreset_ip;
	#define GET_reset_ip(fl)  s_pfCMGetAPI2( "reset_ip", (RTS_VOID_FCTPTR *)&pfreset_ip, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x76DED90E, 0x03050A00)
	#define CAL_reset_ip  pfreset_ip
	#define CHK_reset_ip  (pfreset_ip != NULL)
	#define EXP_reset_ip   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"reset_ip", (RTS_UINTPTR)reset_ip, 1, 0x76DED90E, 0x03050A00) 
#endif


/**
 * <description>set_ip</description>
 */
typedef struct tagset_ip_struct
{
	RTS_IEC_STRING iface_name[81];		/* VAR_INPUT */	
	RTS_IEC_STRING ip_addr[81];			/* VAR_INPUT */	
	RTS_IEC_STRING mask[81];			/* VAR_INPUT */	
	RTS_IEC_STRING gateway_addr[81];	/* VAR_INPUT */	
	RTS_IEC_INT set_ip;					/* VAR_OUTPUT */	
} set_ip_struct;

void CDECL CDECL_EXT set_ip(set_ip_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_IP_IEC) (set_ip_struct *p);
#if defined(CMPEMICONNETWORK_NOTIMPLEMENTED) || defined(SET_IP_NOTIMPLEMENTED)
	#define USE_set_ip
	#define EXT_set_ip
	#define GET_set_ip(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_ip(p0) 
	#define CHK_set_ip  FALSE
	#define EXP_set_ip  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_ip
	#define EXT_set_ip
	#define GET_set_ip(fl)  CAL_CMGETAPI( "set_ip" ) 
	#define CAL_set_ip  set_ip
	#define CHK_set_ip  TRUE
	#define EXP_set_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_ip", (RTS_UINTPTR)set_ip, 1, 0x720F7C91, 0x03050A00) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONNETWORK_EXTERNAL)
	#define USE_set_ip
	#define EXT_set_ip
	#define GET_set_ip(fl)  CAL_CMGETAPI( "set_ip" ) 
	#define CAL_set_ip  set_ip
	#define CHK_set_ip  TRUE
	#define EXP_set_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_ip", (RTS_UINTPTR)set_ip, 1, 0x720F7C91, 0x03050A00) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconNetworkset_ip
	#define EXT_CmpEmiconNetworkset_ip
	#define GET_CmpEmiconNetworkset_ip  ERR_OK
	#define CAL_CmpEmiconNetworkset_ip  set_ip
	#define CHK_CmpEmiconNetworkset_ip  TRUE
	#define EXP_CmpEmiconNetworkset_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_ip", (RTS_UINTPTR)set_ip, 1, 0x720F7C91, 0x03050A00) 
#elif defined(CPLUSPLUS)
	#define USE_set_ip
	#define EXT_set_ip
	#define GET_set_ip(fl)  CAL_CMGETAPI( "set_ip" ) 
	#define CAL_set_ip  set_ip
	#define CHK_set_ip  TRUE
	#define EXP_set_ip  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_ip", (RTS_UINTPTR)set_ip, 1, 0x720F7C91, 0x03050A00) 
#else /* DYNAMIC_LINK */
	#define USE_set_ip  PFSET_IP_IEC pfset_ip;
	#define EXT_set_ip  extern PFSET_IP_IEC pfset_ip;
	#define GET_set_ip(fl)  s_pfCMGetAPI2( "set_ip", (RTS_VOID_FCTPTR *)&pfset_ip, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x720F7C91, 0x03050A00)
	#define CAL_set_ip  pfset_ip
	#define CHK_set_ip  (pfset_ip != NULL)
	#define EXP_set_ip   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_ip", (RTS_UINTPTR)set_ip, 1, 0x720F7C91, 0x03050A00) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/




typedef struct
{
	IBase_C *pBase;
} ICmpEmiconNetwork_C;

#ifdef CPLUSPLUS
class ICmpEmiconNetwork : public IBase
{
	public:
};
	#ifndef ITF_CmpEmiconNetwork
		#define ITF_CmpEmiconNetwork static ICmpEmiconNetwork *pICmpEmiconNetwork = NULL;
	#endif
	#define EXTITF_CmpEmiconNetwork
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconNetwork_C		ICmpEmiconNetwork;
	#ifndef ITF_CmpEmiconNetwork
		#define ITF_CmpEmiconNetwork
	#endif
	#define EXTITF_CmpEmiconNetwork
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONNETWORKITF_H_*/
