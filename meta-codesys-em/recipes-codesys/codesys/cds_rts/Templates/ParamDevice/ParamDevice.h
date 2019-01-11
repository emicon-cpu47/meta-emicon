#define COMPO_INIT_DECLS \
int SysTime__Entry(INIT_STRUCT *pInitStruct); \
int SysTask__Entry(INIT_STRUCT *pInitStruct); \
int SysTarget__Entry(INIT_STRUCT *pInitStruct); \
int SysSocket__Entry(INIT_STRUCT *pInitStruct); \
int SysSem__Entry(INIT_STRUCT *pInitStruct); \
int SysOut__Entry(INIT_STRUCT *pInitStruct); \
int SysMem__Entry(INIT_STRUCT *pInitStruct); \
int SysExcept__Entry(INIT_STRUCT *pInitStruct); \
int SysCpuHandling__Entry(INIT_STRUCT *pInitStruct); \
int CmpSrv__Entry(INIT_STRUCT *pInitStruct); \
int CmpSettingsEmbedded__Entry(INIT_STRUCT *pInitStruct); \
int CmpRouter__Entry(INIT_STRUCT *pInitStruct); \
int CmpNameServiceServer__Entry(INIT_STRUCT *pInitStruct); \
int CmpNameServiceClient__Entry(INIT_STRUCT *pInitStruct); \
int CmpMemPool__Entry(INIT_STRUCT *pInitStruct); \
int CmpLog__Entry(INIT_STRUCT *pInitStruct); \
int CmpEventMgr__Entry(INIT_STRUCT *pInitStruct); \
int CmpDevice__Entry(INIT_STRUCT *pInitStruct); \
int CmpCommunicationLib__Entry(INIT_STRUCT *pInitStruct); \
int CmpChecksum__Entry(INIT_STRUCT *pInitStruct); \
int CmpChannelServer__Entry(INIT_STRUCT *pInitStruct); \
int CmpChannelMgr__Entry(INIT_STRUCT *pInitStruct); \
int CmpBlkDrvUdp__Entry(INIT_STRUCT *pInitStruct); \
int CmpBlkDrvTcp__Entry(INIT_STRUCT *pInitStruct); \
int CmpBinTagUtil__Entry(INIT_STRUCT *pInitStruct); \
int CmpParamDevice__Entry(INIT_STRUCT *pInitStruct); 


#define COMPO_INIT_LIST \
{"SysTime", SysTime__Entry, 0}, \
{"SysTask", SysTask__Entry, 0}, \
{"SysTarget", SysTarget__Entry, 0}, \
{"SysSocket", SysSocket__Entry, 0}, \
{"SysSem", SysSem__Entry, 0}, \
{"SysOut", SysOut__Entry, 0}, \
{"SysMem", SysMem__Entry, 0}, \
{"SysExcept", SysExcept__Entry, 0}, \
{"SysCpuHandling", SysCpuHandling__Entry, 0}, \
{"CmpSrv", CmpSrv__Entry, 0}, \
{"CmpSettingsEmbedded", CmpSettingsEmbedded__Entry, 0}, \
{"CmpRouter", CmpRouter__Entry, 0}, \
{"CmpNameServiceServer", CmpNameServiceServer__Entry, 0}, \
{"CmpMemPool", CmpMemPool__Entry, 0}, \
{"CmpEventMgr", CmpEventMgr__Entry, 0},\
{"CmpLog", CmpLog__Entry, 0}, \
{"CmpDevice", CmpDevice__Entry, 0}, \
{"CmpCommunicationLib", CmpCommunicationLib__Entry, 0}, \
{"CmpChecksum", CmpChecksum__Entry, 0}, \
{"CmpChannelServer", CmpChannelServer__Entry, 0}, \
{"CmpChannelMgr", CmpChannelMgr__Entry, 0}, \
{"CmpBlkDrvUdp", CmpBlkDrvUdp__Entry, 0}, \
{"CmpBlkDrvTcp", CmpBlkDrvTcp__Entry, 0}, \
{"CmpBinTagUtil", CmpBinTagUtil__Entry, 0}, \
{"CmpParamDevice", CmpParamDevice__Entry, 0}, \
{"", NULL, 0}
