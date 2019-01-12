/**
 * <interfacename>CmpEmiconNetwork</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpEmiconNetwork')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`reset_ip',`(reset_ip_struct *p)',1,0x76DED90E,0x03050A00)

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

DEF_API(`void',`CDECL',`set_ip',`(set_ip_struct *p)',1,0x720F7C91,0x03050A00)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

