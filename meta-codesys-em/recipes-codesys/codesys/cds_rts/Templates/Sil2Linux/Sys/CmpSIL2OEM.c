/*****************************************************************************
*
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		SIL2 OEM Component Template
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include <sys/mman.h>

#ifdef PATHS_RELATIVE
	#include "CmpSIL2/CmpSIL2.h"
#else
	#include "CmpSIL2.h"
#endif

USE_STMT

/**
 * <category>Static defines</category>
 * <description>Maximum depth of context switches</description>
 */
#ifndef SIL2OEMCTXSTACKSIZE
	#define SIL2OEMCTXSTACKSIZE	20
#endif

/**
 * <category>Static defines</category>
 * <description>Maximum depth of context switches</description>
 */
#ifndef SIL2OEMASSUMEDSTACKSIZE
	#define SIL2OEMASSUMEDSTACKSIZE 0x10000
#endif

RTS_SIL2_OPMODE g_Sil2OpMode RTS_SIL2_ATTRIBUTE = RTS_SIL2_OPMODE_SAFE;
static RTS_UI16 s_abyCtxStack[SIL2OEMCTXSTACKSIZE] RTS_SIL2_ATTRIBUTE = {RTS_SIL2_CALLERCTX_SAFE};
static RTS_UI8 s_byCtxStackDepth RTS_SIL2_ATTRIBUTE = 0;

/* Stack handling */
register void *esp __asm__ ("esp");
static RTS_UI8 *s_pbyInitialSP = 0;
static RTS_UI32 s_uiStackSize = SIL2OEMASSUMEDSTACKSIZE;

/* Memory handling */
extern void *g_dataarea_startaddress;
extern size_t g_dataarea_size;
extern unsigned char g_bDataAreaAllocated;
/* these variables have to de defined in the linker file */
extern unsigned int _startOfSIL2section;
extern unsigned int _endOfSIL2section;

/* example implementation for Runtimecheck with Ranges */
#define CMPSIL2_RUNTIMECHECK_DEFAULT_BLOCKSIZE 0x1000
#define CMPSIL2_RUNTIMECHECK_RANGES \
{ (RTS_HANDLE) 0x00000000, 0x0000 }
/* further example
#define CMPSIL2_RUNTIMECHECK_RANGES \
{ (RTS_HANDLE) 0xA0000000, 0x0F00 },\
{ (RTS_HANDLE) 0xA1000000, 0x0abc },\
{ (RTS_HANDLE) 0xA2000000, 0x5000 },\
{ (RTS_HANDLE) 0xA3000000, 0x1000 }
*/
typedef struct SIL2_RUNTIMECHECK_RANGE_INFO
{
	RTS_HANDLE	pStartAddress;
	RTS_UI32	ulByteRange;
}SIL2_RUNTIMECHECK_RANGE_INFO;

static RTS_UI32 s_ulSIL2_RuntimeCheck_RangeCount = 0;
static RTS_UI32 s_ulSIL2_RuntimeCheck_CurrCRC = 0;
static RTS_UI32 s_ulSIL2_RuntimeCheck_CurrRange = 0;
static RTS_HANDLE s_ulSIL2_RuntimeCheck_CurrPos = 0;

static const SIL2_RUNTIMECHECK_RANGE_INFO s_SIL2_RuntimeCheck_Ranges[] = {
	CMPSIL2_RUNTIMECHECK_RANGES
};

static void _mpuEnable_(void);
static void _mpuDisable_(void);

void SIL2OEMSwitchToSafeCtx(void);
void SIL2OEMSwitchToUnsafeCtx(void);
void SIL2OEMSwitchToPreviousCtx(void);
void SIL2OEMSwitchToSafeCtx_nolock(void);
void SIL2OEMSwitchToPreviousCtx_nolock(void);
 
RTS_RESULT CDECL CmpSIL2OEMHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	RTS_RESULT Result = ERR_OK;

	switch (ulHook)
	{
		case CH_INIT:		
		{
			s_pbyInitialSP = esp;
		}
		case CH_INIT2:
		{
			s_ulSIL2_RuntimeCheck_RangeCount = sizeof(s_SIL2_RuntimeCheck_Ranges)/sizeof(SIL2_RUNTIMECHECK_RANGE_INFO);			
			break;
		}
		case CH_COMM_CYCLE:
		{			
#if 0		/*only for test*/
			RTS_UI32 ulmyCRC = 0xAABBCCDD;
			Result = SIL2OEMRuntimeCheckComplete(ulmyCRC);
			Result = SIL2OEMRuntimeCheckCyclic(ulmyCRC);
#endif
			
			break;
		}
		default:
			break;
	}
	return Result;
}


#include <signal.h>

void CDECL SIL2OEMException(RTS_SIL2_EXCEPTION Exception)
{
	puts("*** EXCEPTION ***");
	printf("An exception occured and SIL2OEMException was called. (code %x)", Exception);
	exit (1);
}



RTS_SIL2_OPMODE CDECL SIL2OEMGetOperationMode(void)
{
	/* Decide if Runtime is in Debugmode or Safemode */
	/* example implementation: */
	if(g_Sil2OpMode == RTS_SIL2_OPMODE_DEBUG)		
	{
		return RTS_SIL2_OPMODE_DEBUG;
	}
	else if (g_Sil2OpMode == RTS_SIL2_OPMODE_SAFE)
	{
		return RTS_SIL2_OPMODE_SAFE;
	}
	else
	{
		return RTS_SIL2_OPMODE_ERROR;
	}
}

RTS_UI32 CDECL SIL2OEMGetCallerContext(void)
{
	if(s_byCtxStackDepth >= SIL2OEMCTXSTACKSIZE)
		return RTS_SIL2_CALLERCTX_ERROR;

	if(s_abyCtxStack[s_byCtxStackDepth] == RTS_SIL2_CALLERCTX_UNSAFE)
		return RTS_SIL2_CALLERCTX_UNSAFE;
	else if(s_abyCtxStack[s_byCtxStackDepth] == RTS_SIL2_CALLERCTX_SAFE)
		return RTS_SIL2_CALLERCTX_SAFE;
	else
		return RTS_SIL2_CALLERCTX_ERROR;
}


RTS_SIL2_ADDRESSSTATE CDECL SIL2OEMGetMemoryState(RTS_UI8 *pAddress, RTS_UI32 ulLength)
{
	RTS_SIL2_ADDRESSSTATE Result = RTS_SIL2_ADDRESS_UNSAFE;
	void *pAddressEnd = (void*)(pAddress + ulLength);
	
	/* Check if Addressrange is in safe range */
	if((void*)pAddress >= g_dataarea_startaddress && 
	   (void*)pAddress <= g_dataarea_startaddress + g_dataarea_size &&
	   pAddressEnd >= g_dataarea_startaddress &&
	   pAddressEnd <= g_dataarea_startaddress + g_dataarea_size)
	{
		Result = RTS_SIL2_ADDRESS_SAFE;
	}
	else if((void*)pAddress >= (void*)&_startOfSIL2section &&
		(void*)pAddress <= (void*)&_endOfSIL2section &&
		pAddressEnd >= (void*)&_startOfSIL2section &&
		pAddressEnd <= (void*)&_endOfSIL2section)
	{
		Result = RTS_SIL2_ADDRESS_SAFE;
	}

	return Result;
}


RTS_RESULT CDECL SIL2OEMEnterDebugMode(void)
{
	RTS_RESULT Result;

	/* Set Runtime to Debug Mode if possible */
	/* example implementation: */

	if(g_Sil2OpMode == RTS_SIL2_OPMODE_DEBUG)
	{
		Result = ERR_NO_CHANGE;
	}
	else
	{	
		g_Sil2OpMode = RTS_SIL2_OPMODE_DEBUG;
		Result = ERR_OK;		
	}	
	return Result;
}


RTS_RESULT CDECL SIL2OEMStackIsValid(void)
{
	RTS_UI8* pbyCurrentSP = esp;

	if(pbyCurrentSP < s_pbyInitialSP || 
	   pbyCurrentSP > (s_pbyInitialSP + s_uiStackSize))
		return ERR_FAILED;
	else
		return ERR_OK;
}


RTS_RESULT CDECL SIL2OEMExecuteNonSafetyJob(void (*pfNonSafetyJob)(void * pParam),void * pParam)
{
	if(pfNonSafetyJob == NULL ||
	   SIL2OEMGetCallerContext() != RTS_SIL2_CALLERCTX_SAFE)
		return ERR_FAILED;

	SIL2OEMSwitchToUnsafeCtx();
	pfNonSafetyJob(pParam);
	SIL2OEMSwitchToPreviousCtx();

	return ERR_OK;
}

RTS_RESULT CDECL SIL2OEMExecuteNonSafetyJob2(void (*pfNonSafetyJob)(void * pParam), void * pParam, RTS_SIZE iSize)
{
	if (pfNonSafetyJob == NULL ||
	   SIL2OEMGetCallerContext() != RTS_SIL2_CALLERCTX_SAFE)
		return ERR_FAILED;

	if ((pParam == NULL && iSize > 0) || (pParam != NULL && iSize == 0))
		return ERR_PARAMETER;

	SIL2OEMSwitchToUnsafeCtx();
	pfNonSafetyJob(pParam);
	SIL2OEMSwitchToPreviousCtx();

	return ERR_OK;
}


/**
 * Cylic and Complete CRC Functions
 *********************************************************************
 */


RTS_RESULT CDECL SIL2OEMRuntimeCheckCyclic(RTS_UI32 ulCRCExpected)
{
	RTS_RESULT Result = ERR_FAILED;
	
	if(s_ulSIL2_RuntimeCheck_RangeCount && s_SIL2_RuntimeCheck_Ranges[0].pStartAddress)
	{
		RTS_UI32 ulBlocksize = CMPSIL2_RUNTIMECHECK_DEFAULT_BLOCKSIZE;
		RTS_UI32 ulCurrRangeRemaining = 0;
	
		/* Init Cyclic Check */
		if(!s_ulSIL2_RuntimeCheck_CurrPos)
		{
			s_ulSIL2_RuntimeCheck_CurrPos = s_SIL2_RuntimeCheck_Ranges[0].pStartAddress;
			s_ulSIL2_RuntimeCheck_CurrRange = 0;
			s_ulSIL2_RuntimeCheck_CurrCRC = CAL_CRC32Init();
		}
		
		ulCurrRangeRemaining = (RTS_UI32)s_SIL2_RuntimeCheck_Ranges[s_ulSIL2_RuntimeCheck_CurrRange].pStartAddress + (RTS_UI32)s_SIL2_RuntimeCheck_Ranges[s_ulSIL2_RuntimeCheck_CurrRange].ulByteRange - (RTS_UI32)s_ulSIL2_RuntimeCheck_CurrPos;

		if(ulBlocksize > ulCurrRangeRemaining)
		{
			ulBlocksize = ulCurrRangeRemaining;			
		}	
		
		if(ulBlocksize != 0)
		{			
			CAL_CRC32Update2(s_ulSIL2_RuntimeCheck_CurrCRC,s_ulSIL2_RuntimeCheck_CurrPos,ulBlocksize);
		}		
			

		if(ulBlocksize < CMPSIL2_RUNTIMECHECK_DEFAULT_BLOCKSIZE)
		{
			s_ulSIL2_RuntimeCheck_CurrRange++;			
			s_ulSIL2_RuntimeCheck_CurrPos = s_SIL2_RuntimeCheck_Ranges[s_ulSIL2_RuntimeCheck_CurrRange].pStartAddress;
			Result = ERR_PENDING;
		}
		else
		{
			s_ulSIL2_RuntimeCheck_CurrPos = (RTS_HANDLE)((RTS_UI32)s_ulSIL2_RuntimeCheck_CurrPos + ulBlocksize);
			Result = ERR_PENDING;
		}

		if(s_ulSIL2_RuntimeCheck_CurrRange >= s_ulSIL2_RuntimeCheck_RangeCount)
		{
			s_ulSIL2_RuntimeCheck_CurrCRC = CAL_CRC32Finish(s_ulSIL2_RuntimeCheck_CurrCRC);
			if(s_ulSIL2_RuntimeCheck_CurrCRC != ulCRCExpected)
			{
				SIL2OEMException(RTS_SIL2_EXCEPTION_CRC_CYCLIC);
			}
			else
			{
				s_ulSIL2_RuntimeCheck_CurrCRC = 0;
				s_ulSIL2_RuntimeCheck_CurrPos = 0;
				s_ulSIL2_RuntimeCheck_CurrRange = 0;
				Result = ERR_OK;
			}
		}
		
		
		
		

	}
	else
	{
		Result = ERR_NOTINITIALIZED;
	}
	

	return Result;
}

RTS_RESULT CDECL SIL2OEMRuntimeCheckComplete(RTS_UI32 ulCRCExpected)
{
	RTS_RESULT Result = ERR_FAILED;
	
	for(;;)
	{
		Result = SIL2OEMRuntimeCheckCyclic(0xffffffff);
		if(Result != ERR_PENDING)
		{
			break;
		}
	}

	
	return Result;

}

void _mpuEnable_(void)
{
	int res;

	if(g_bDataAreaAllocated)
	{
		res = mprotect(g_dataarea_startaddress, g_dataarea_size, PROT_READ);
		if(res < 0)
			perror("mprotect");
	}

	res = mprotect(&_startOfSIL2section, &_endOfSIL2section - &_startOfSIL2section, PROT_READ);
	if(res < 0)
		perror("mprotect");
}

void _mpuDisable_(void)
{
	int res;

	if(g_bDataAreaAllocated)
	{
		res = mprotect(g_dataarea_startaddress, g_dataarea_size, PROT_READ | PROT_WRITE);
		if(res < 0)
			perror("mprotect");
	}

	res = mprotect(&_startOfSIL2section, &_endOfSIL2section - &_startOfSIL2section, PROT_READ | PROT_WRITE);

	if(res < 0)
		perror("mprotect");
}

void SIL2OEMSwitchToSafeCtx(void)
{
	RTS_UI32 ulParam;
	CAL_SysIntDisableAll(&ulParam);

	SIL2OEMSwitchToSafeCtx_nolock();

	CAL_SysIntEnableAll(&ulParam);
}

void SIL2OEMSwitchToUnsafeCtx(void)
{
	RTS_UI32 ulParam;
	CAL_SysIntDisableAll(&ulParam);

	if((s_byCtxStackDepth + 1) >= SIL2OEMCTXSTACKSIZE)
	{
		SIL2OEMException(RTS_SIL2_FAIL_GENERAL);
		return;
	}

	s_byCtxStackDepth++;

	s_abyCtxStack[s_byCtxStackDepth] = RTS_SIL2_CALLERCTX_UNSAFE;

	if(g_Sil2OpMode == RTS_SIL2_OPMODE_SAFE)
	{
		_mpuEnable_();
		//DEBUGP("Switch to unsafe context");
	}

	CAL_SysIntEnableAll(&ulParam);
}

void SIL2OEMSwitchToPreviousCtx(void)
{
	RTS_UI32 ulParam;
	CAL_SysIntDisableAll(&ulParam);

	SIL2OEMSwitchToPreviousCtx_nolock();	

	CAL_SysIntEnableAll(&ulParam);
}

void SIL2OEMSwitchToSafeCtx_nolock(void)
{
	if((s_byCtxStackDepth + 1) >= SIL2OEMCTXSTACKSIZE)
	{
		SIL2OEMException(RTS_SIL2_FAIL_GENERAL);
		return;
	}
	
	s_byCtxStackDepth++;

	s_abyCtxStack[s_byCtxStackDepth] = RTS_SIL2_CALLERCTX_SAFE;
	
	if(g_Sil2OpMode == RTS_SIL2_OPMODE_SAFE)
	{
		_mpuDisable_();
		//DEBUGP("Switch to safe context");
	}
}

void SIL2OEMSwitchToPreviousCtx_nolock(void)
{
	if(s_byCtxStackDepth == 0)
	{
		SIL2OEMException(RTS_SIL2_FAIL_GENERAL);
		return;
	}
	
	s_byCtxStackDepth--;
	
	if(g_Sil2OpMode == RTS_SIL2_OPMODE_SAFE &&
		s_abyCtxStack[s_byCtxStackDepth] == RTS_SIL2_CALLERCTX_UNSAFE)
	{
		_mpuEnable_();
		//DEBUGP("Switch to unsafe context");
	}
	else if(g_Sil2OpMode == RTS_SIL2_OPMODE_SAFE &&
			s_abyCtxStack[s_byCtxStackDepth] == RTS_SIL2_CALLERCTX_SAFE)
	{
		_mpuDisable_();
		//DEBUGP("Switch to safe context");
	}

}
