 
	
	
#ifndef _CMPCOREDUMPITF_H_
#define _CMPCOREDUMPITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/**
 * <category>Application code location information</category>
 * <description>
 *	Describes all POUs contained in an application
 * </description>
 */
typedef struct _CODE_LOCATION_STRUCT
{
	RTS_IEC_UINT usiAreaCodeLocation;
	RTS_IEC_UDINT udiOffsetCodeLocation;
	RTS_IEC_UDINT udiCodeSize;
} CODE_LOCATION_STRUCT;

typedef struct _CODE_LOCATION_INFO
{
	RTS_IEC_UDINT udiInfoVersion;
	RTS_IEC_UDINT udiNumPOUs;
	CODE_LOCATION_STRUCT* pPOUs;
} CODE_LOCATION_INFO;

/**
 * <category>Online services</category>
 * <description>
 * </description>
 */
#define SRV_CD_READ_STACK					0x01
#define SRV_CD_REGISTER_APP					0x02

/**
 * <category>Online tags</category>
 * <description>
 * </description>
 */
#define TAG_CD_APP_SESSIONID				0x02
#define TAG_CD_STACK_FRAME					0x83
#define TAG_CD_STACK_FRAME_SIZE				0x04
#define TAG_CD_STACK_FRAME_DATA				0x05
#define TAG_CD_STACK_FRAME_PTR				0x06

/**
 * <category>Static defines</category>
 * <description>Core-Dump file extension. The prefix is the corresponding application name, e.g. "Application.core".</description>
 */
#ifndef CORE_DUMP_FILE_EXTENSION
	#define CORE_DUMP_FILE_EXTENSION			".core"
#endif

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
} ICmpCoreDump_C;

#ifdef CPLUSPLUS
class ICmpCoreDump : public IBase
{
	public:
};
	#ifndef ITF_CmpCoreDump
		#define ITF_CmpCoreDump static ICmpCoreDump *pICmpCoreDump = NULL;
	#endif
	#define EXTITF_CmpCoreDump
#else	/*CPLUSPLUS*/
	typedef ICmpCoreDump_C		ICmpCoreDump;
	#ifndef ITF_CmpCoreDump
		#define ITF_CmpCoreDump
	#endif
	#define EXTITF_CmpCoreDump
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPCOREDUMPITF_H_*/
