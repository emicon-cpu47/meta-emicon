#define COMPO_INIT_DECLS \
int SysTimer__Entry(INIT_STRUCT *pInitStruct); \
int SysTime__Entry(INIT_STRUCT *pInitStruct); \
int SysTarget__Entry(INIT_STRUCT *pInitStruct); \
int SysSocket__Entry(INIT_STRUCT *pInitStruct); \
int SysOut__Entry(INIT_STRUCT *pInitStruct); \
int SysMem__Entry(INIT_STRUCT *pInitStruct); \
int SysInternalLib__Entry(INIT_STRUCT *pInitStruct); \
int SysInt__Entry(INIT_STRUCT *pInitStruct); \
int SysFlash__Entry(INIT_STRUCT *pInitStruct); \
int SysFileFlash__Entry(INIT_STRUCT *pInitStruct); \
int SysExcept__Entry(INIT_STRUCT *pInitStruct); \
int SysCpuHandling__Entry(INIT_STRUCT *pInitStruct); \
int SysCom__Entry(INIT_STRUCT *pInitStruct); \
int CmpSrv__Entry(INIT_STRUCT *pInitStruct); \
int CmpSettingsEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpScheduleTimer__Entry(INIT_STRUCT *pInitStruct); \
int CmpRouterEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpNameServiceServer__Entry(INIT_STRUCT *pInitStruct); \
int CmpMonitor__Entry(INIT_STRUCT *pInitStruct); \
int CmpMemPool__Entry(INIT_STRUCT *pInitStruct); \
int CmpLogEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpIoMgrEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpIecTask__Entry(INIT_STRUCT *pInitStruct); \
int CmpEventMgr__Entry(INIT_STRUCT *pInitStruct); \
int CmpDevice__Entry(INIT_STRUCT *pInitStruct); \
int CmpCommunicationLib__Entry(INIT_STRUCT *pInitStruct); \
int CmpChecksum__Entry(INIT_STRUCT *pInitStruct); \
int CmpChannelServerEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpChannelMgrEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpBlkDrvUdp__Entry(INIT_STRUCT *pInitStruct); \
int CmpBlkDrvCom__Entry(INIT_STRUCT *pInitStruct); \
int CmpBinTagUtil__Entry(INIT_STRUCT *pInitStruct); \
int CmpAppEmbedded__Entry(INIT_STRUCT *pInitStruct); 
int CmpAppBP__Entry(INIT_STRUCT *pInitStruct); 


#define COMPO_INIT_LIST \
{"SysTimer", SysTimer__Entry, 0}, \
{"SysTime", SysTime__Entry, 0}, \
{"SysTarget", SysTarget__Entry, 0}, \
{"SysSocket", SysSocket__Entry, 0}, \
{"SysOut", SysOut__Entry, 0}, \
{"SysMem", SysMem__Entry, 0}, \
{"SysInternalLib", SysInternalLib__Entry, 0}, \
{"SysInt", SysInt__Entry, 0}, \
{"SysFlash", SysFlash__Entry, 0}, \
{"SysFileFlash", SysFileFlash__Entry, 0}, \
{"SysExcept", SysExcept__Entry, 0}, \
{"SysCpuHandling", SysCpuHandling__Entry, 0}, \
{"SysCom", SysCom__Entry, 0}, \
{"CmpSrv", CmpSrv__Entry, 0}, \
{"CmpSettingsEmbedded", CmpSettingsEmbedded__Entry, 0}, \
{"CmpScheduleTimer", CmpScheduleTimer__Entry, 0}, \
{"CmpRouterEmbedded", CmpRouterEmbedded__Entry, 0}, \
{"CmpNameServiceServer", CmpNameServiceServer__Entry, 0}, \
{"CmpMonitor", CmpMonitor__Entry, 0}, \
{"CmpMemPool", CmpMemPool__Entry, 0}, \
{"CmpLogEmbedded", CmpLogEmbedded__Entry, 0}, \
{"CmpIoMgrEmbedded", CmpIoMgrEmbedded__Entry, 0}, \
{"CmpIecTask", CmpIecTask__Entry, 0}, \
{"CmpEventMgr", CmpEventMgr__Entry, 0}, \
{"CmpDevice", CmpDevice__Entry, 0}, \
{"CmpCommunicationLib", CmpCommunicationLib__Entry, 0}, \
{"CmpChecksum", CmpChecksum__Entry, 0}, \
{"CmpChannelServerEmbedded", CmpChannelServerEmbedded__Entry, 0}, \
{"CmpChannelMgrEmbedded", CmpChannelMgrEmbedded__Entry, 0}, \
{"CmpBlkDrvUdp", CmpBlkDrvUdp__Entry, 0}, \
{"CmpBlkDrvCom", CmpBlkDrvCom__Entry, 0}, \
{"CmpBinTagUtil", CmpBinTagUtil__Entry, 0}, \
{"CmpAppEmbedded", CmpAppEmbedded__Entry, 0}, \
{"CmpAppBP", CmpAppBP__Entry, 0}, \
{"", NULL, 0}


#define COMPO_DYNAMIC_INIT_LIST \
{"SysTimer", NULL, 0}, \
{"SysTime", NULL, 0}, \
{"SysTarget", NULL, 0}, \
{"SysSocket", NULL, 0}, \
{"SysOut", NULL, 0}, \
{"SysMem", NULL, 0}, \
{"SysInternalLib", NULL, 0}, \
{"SysInt", NULL, 0}, \
{"SysFlash", NULL, 0}, \
{"SysFileFlash", NULL, 0}, \
{"SysExcept", NULL, 0}, \
{"SysCpuHandling", NULL, 0}, \
{"SysCom", NULL, 0}, \
{"CmpSrv", NULL, 0}, \
{"CmpSettingsEmbedded", NULL, 0}, \
{"CmpScheduleTimer", NULL, 0}, \
{"CmpRouterEmbedded", NULL, 0}, \
{"CmpNameServiceServer", NULL, 0}, \
{"CmpMonitor", NULL, 0}, \
{"CmpMemPool", NULL, 0}, \
{"CmpLogEmbedded", NULL, 0}, \
{"CmpIoMgrEmbedded", NULL, 0}, \
{"CmpIecTask", NULL, 0}, \
{"CmpEventMgr", NULL, 0}, \
{"CmpDevice", NULL, 0}, \
{"CmpCommunicationLib", NULL, 0}, \
{"CmpChecksum", NULL, 0}, \
{"CmpChannelServerEmbedded", NULL, 0}, \
{"CmpChannelMgrEmbedded", NULL, 0}, \
{"CmpBlkDrvUdp", NULL, 0}, \
{"CmpBlkDrvCom", NULL, 0}, \
{"CmpBinTagUtil", NULL, 0}, \
{"CmpAppEmbedded", NULL, 0}, \
{"CmpAppBP", NULL, 0}, \
{"", NULL, 0}
