/**
 * <interfacename>CAA_BehaviourModel_Extern</interfacename>
 * <description>
 * </description>
 *
 * <copyright>
 * Copyright (c) 2017-2018 CODESYS GmbH, Copyright (c) 1994-2016 3S-Smart Software Solutions GmbH. All rights reserved.
 * </copyright>
 */

SET_INTERFACE_NAME(`CmpCAABehaviourModel')

#include "CmpItf.h"
#include "CAADefines.h"
#include "CAATypes.h"
#include "CAABehaviourModel.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Interface functions of CAA BehaviourModel*/
DEF_ITF_API(`void',`CDECL',`CBM_ETrig',`(CBM_ETRIG_CLASS* pInstance)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvStart',`(void)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvCyclicAction',`(void)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvAbort',`(void)')
DEF_ITF_API(`void',`CDECL',`CBM_ETrig_prvResetOutputs',`(CBM_ETRIG_CLASS* pInstance)')

#ifdef __cplusplus
}
#endif

