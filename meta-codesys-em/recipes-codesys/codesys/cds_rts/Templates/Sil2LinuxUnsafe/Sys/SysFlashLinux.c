/* Implements a template flash component based on RAM */
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>
#include "CmpStd.h"

#ifdef PATHS_RELATIVE
	#include "SysFlash/SysFlashDep.h"
#else
	#include "SysFlashDep.h"
#endif

USE_STMT

static int fdCode;
static void *pFlashCode;

#ifndef FLASH_SIZE
    #define FLASH_SIZE   0x80000
#endif
#ifndef FLASH_START_ADDRESS
    #define FLASH_START_ADDRESS   0x40000
#endif

RTS_RESULT CDECL SysFlashOSInit(INIT_STRUCT *pInit)
{
	s_pfCMRegisterAPI = pInit->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInit->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInit->pfCMGetAPI;
	s_pfCMGetAPI2 = pInit->pfCMGetAPI2;
	s_pfCMCallHook = pInit->pfCMCallHook;
	s_pfCMRegisterClass = pInit->pfCMRegisterClass;
	s_pfCMCreateInstance = pInit->pfCMCreateInstance;

	return ERR_OK;
}
 
RTS_RESULT CDECL SysFlashOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT:
		{
			IMPORT_STMT;

			fdCode = open("flashcode.bin",O_RDWR | O_CREAT);
			if (fdCode < 0)
			{
				DEBUGP("open(\"flashcode.bin\"):%s",strerror(errno));
			}
			else
			{
				if(ftruncate(fdCode, FLASH_SIZE) < 0)
				{
					pFlashCode = 0;
					DEBUGP("ftruncate(\"flashcode.bin\"):%s",strerror(errno));
					return ERR_FAILED;
				}

				pFlashCode = mmap((void*)FLASH_START_ADDRESS, FLASH_SIZE, PROT_READ | PROT_EXEC, MAP_SHARED | MAP_FIXED, fdCode, 0);
				if (pFlashCode == MAP_FAILED)
				{
					pFlashCode = 0;
					DEBUGP("mmap(\"flashcode.bin\"):%s",strerror(errno));
					return ERR_FAILED;
				}
			}
			break;
		}
		case CH_EXIT:
		{
			int res;

			if (pFlashCode)
			{
				res = munmap(pFlashCode, FLASH_SIZE);
				pFlashCode = 0;
				if (res <0)
				{
					DEBUGP("munmap:%s",strerror(errno));
				}
			}
			if (fdCode >0)
			{
				res = close(fdCode);
				fdCode = 0;
				if (res <0)
				{
					DEBUGP("close:%s",strerror(errno));
				}
			}

			EXIT_STMT;
			break;
		}
		default:
			break;
	}
	return ERR_OK;
}

RTS_RESULT CDECL SysFlashInit(FlashArea fa)
{
	return ERR_OK;
}

RTS_RESULT CDECL SysFlashErase_(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)
{
	if((ulOffset + ulSize) > FLASH_SIZE)
		return ERR_PARAMETER;
	else if(pFlashCode == NULL)
		return ERR_FAILED;

	switch (fa)
	{
		case FA_FILE:
		case FA_CODE:
		{
			int res;

			res = mprotect(pFlashCode, FLASH_SIZE, PROT_WRITE);
			if (res <0)
			{
				DEBUGP("mprotect:%s",strerror(errno));
				return ERR_FAILED;
			}

			memset(pFlashCode + ulOffset, 0xff, ulSize);

			res = mprotect(pFlashCode, FLASH_SIZE, PROT_READ | PROT_EXEC);
			if (res <0)
			{
				DEBUGP("mprotect:%s",strerror(errno));
			}
			break;
		}
		default:
			return ERR_NOT_SUPPORTED;
	}
	return ERR_OK;
}

RTS_RESULT CDECL SysFlashRead_(FlashArea fa, char *pcDest, RTS_SIZE ulSize, RTS_SIZE ulOffset)
{
	if ((ulOffset + ulSize) > FLASH_SIZE ||
		pcDest == NULL)
		return ERR_PARAMETER;
	else if(pFlashCode == NULL)
		return ERR_FAILED;

	switch (fa)
	{
		case FA_FILE:
		case FA_CODE:
		{
			memcpy(pcDest, pFlashCode + ulOffset, ulSize);
			break;
		}
		default:
			return ERR_NOT_SUPPORTED;
	}
	return ERR_OK;
}

RTS_RESULT CDECL SysFlashWrite_(FlashArea fa, char *pcSource, RTS_SIZE ulSize, RTS_SIZE ulOffset)
{
	if ((ulOffset + ulSize) > FLASH_SIZE ||
		pcSource == NULL)
		return ERR_PARAMETER;
	else if(pFlashCode == NULL)
		return ERR_FAILED;

	switch (fa)
	{
		case FA_FILE:
		case FA_CODE:
		{
			int res;

			res = mprotect(pFlashCode, FLASH_SIZE, PROT_WRITE);
			if (res <0)
			{
				DEBUGP("mprotect:%s",strerror(errno));
				return ERR_FAILED;
			}

			memcpy(pFlashCode + ulOffset, pcSource, ulSize);

			res = mprotect(pFlashCode, FLASH_SIZE, PROT_READ | PROT_EXEC);
			if (res <0)
			{
				DEBUGP("mprotect:%s",strerror(errno));
			}
			break;
		 }
		default:
			return ERR_NOT_SUPPORTED;
	}
	return ERR_OK;
}

RTS_RESULT CDECL SysFlashFlush_(FlashArea fa, RTS_SIZE ulSize, RTS_SIZE ulOffset)
{
	if ((ulOffset + ulSize) > FLASH_SIZE)
		return ERR_PARAMETER;
	else if(pFlashCode == NULL)
		return ERR_FAILED;

	switch (fa)
	{
		case FA_FILE:
		case FA_CODE:
			msync(pFlashCode, ulSize, MS_SYNC);
			break;
		default:
			return ERR_NOT_SUPPORTED;
	}
	return ERR_OK;
}

RTS_UINTPTR CDECL SysFlashGetPhysicalAddress(FlashArea fa, RTS_RESULT *pResult)
{
	if(pFlashCode == NULL)
	{
		RTS_SETRESULT(pResult, ERR_FAILED);
		return 0;
	}

	switch (fa)
	{
		case FA_FILE:
		case FA_CODE:
		{
			RTS_SETRESULT(pResult, ERR_OK);
			return (RTS_UINTPTR)pFlashCode;
		}
		default:
			RTS_SETRESULT(pResult, ERR_NOT_SUPPORTED);
	}

	return 0;
}

RTS_SIZE CDECL SysFlashGetSize(FlashArea fa, RTS_RESULT *pResult)
{
	switch (fa)
	{
		case FA_FILE:
		case FA_CODE:
		{
			RTS_SETRESULT(pResult, ERR_OK);
			return (RTS_SIZE)FLASH_SIZE;
		}
		default:
			RTS_SETRESULT(pResult, ERR_NOT_SUPPORTED);
	}

	return 0;
}
