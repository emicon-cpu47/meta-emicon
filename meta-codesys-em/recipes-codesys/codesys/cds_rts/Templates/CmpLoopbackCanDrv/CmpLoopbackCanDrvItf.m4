SET_INTERFACE_NAME(`CmpLoopbackCanDrv')

#include "CmpItf.h"

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`int',`CDECL',`Loopback_CanMiniDriver_Setup',`(void)')
DEF_ITF_API(`int',`CDECL',`Loopback_CanMiniDriver_Dispose',`(void)')
DEF_ITF_API(`void',`CDECL',`Loopback_CanMiniDriver_Handler',`(void)')

#ifdef __cplusplus
}
#endif
