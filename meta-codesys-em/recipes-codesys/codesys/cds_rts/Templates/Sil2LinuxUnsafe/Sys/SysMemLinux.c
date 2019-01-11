/*lint -save --e{*} */
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <setjmp.h>
#include <sys/mman.h>

#include "sys/shm.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
/*lint -restore */

#include "CmpStd.h"

#ifdef PATHS_RELATIVE
	#include "SysMem/SysMemDep.h"
#else
	#include "SysMemDep.h"
#endif

USE_STMT

int gbSysIsValidPointer = 0;
sigjmp_buf gsig_buf;
unsigned char gsig_addr;
volatile unsigned char * volatile gpTest;
static RTS_I32 bMemlock;
static pthread_mutex_t sMutex;

/* Safe App */
#define SHM_NAME_SAFEDATA    "cds_safeapp_safedata"
#define SHM_NAME_UNSAFEDATA  "cds_safeapp_unsafedata"
#define SHM_NAME_PERSDATA    "cds_safeapp_pers"

void sysarea_safeapp_map(char * pszName, void* pAddress, int length);
void sysarea_safeapp_unmap(char * pszName, void* pAddress, int length);

/* Areas */
#define DATA_AREA_SIZE         0x20000
#define UNSAFE_DATA_AREA_SIZE  0x20000
#define RETAIN_AREA_SIZE       0x10000
#define DATA_AREA_START_ADDRESS     0x1C0000
#define RETAIN_AREA_START_ADDRESS   0x200000


/* Safe App Areas */
#define SAFEAPP_DATA_AREA_START_ADDRESS       ((void*)0xC0000)
#define SAFEAPP_UNSAFEDATA_AREA_START_ADDRESS ((void*)0xE0000)
#define SAFEAPP_PERS_AREA_START_ADDRESS       ((void*)0x100000)


unsigned char g_bDataAreaAllocated RTS_SIL2_ATTRIBUTE = FALSE;
static unsigned char s_bUnsafeDataAreaAllocated = FALSE;
static unsigned char s_bRetainAreaAllocated     = FALSE;

const void *g_dataarea_startaddress = (void *)DATA_AREA_START_ADDRESS;
const size_t g_dataarea_size = (size_t)DATA_AREA_SIZE;

RTS_RESULT CDECL SysMemOSInit(INIT_STRUCT *pInit)
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

RTS_RESULT CDECL SysMemOSHookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
		{
			IMPORT_STMT;
			break;
		}
		case CH_INIT2:
		{
			pthread_mutex_init(&sMutex, 0);
			CAL_SettgGetIntValue(COMPONENT_NAME, SYSMEMKEY_INT_LINUX_MEMLOCK, &bMemlock, SYSMEMKEY_INT_LINUX_MEMLOCK_DEFAULT, 0);
			if(bMemlock)
			{
				int ret = mlockall(MCL_CURRENT |  MCL_FUTURE);
				if (ret < 0) {
					DEBUGP("mlockall: %s", strerror(errno));
				}
			}
			
			sysarea_safeapp_map(SHM_NAME_SAFEDATA,SAFEAPP_DATA_AREA_START_ADDRESS,DATA_AREA_SIZE);
			sysarea_safeapp_map(SHM_NAME_UNSAFEDATA,SAFEAPP_UNSAFEDATA_AREA_START_ADDRESS,UNSAFE_DATA_AREA_SIZE);
			sysarea_safeapp_map(SHM_NAME_PERSDATA,SAFEAPP_PERS_AREA_START_ADDRESS,RETAIN_AREA_SIZE);

			break;
		}
		case CH_EXIT2:
		{
		  
			pthread_mutex_destroy(&sMutex);
			if(bMemlock)
			{
				int ret = munlockall();
				if (ret < 0) {
					DEBUGP("munlockall: %s", strerror(errno));
				}
			}
			sysarea_safeapp_unmap(SHM_NAME_SAFEDATA,SAFEAPP_DATA_AREA_START_ADDRESS,DATA_AREA_SIZE);
			sysarea_safeapp_unmap(SHM_NAME_UNSAFEDATA,SAFEAPP_UNSAFEDATA_AREA_START_ADDRESS,UNSAFE_DATA_AREA_SIZE);
			sysarea_safeapp_unmap(SHM_NAME_PERSDATA,SAFEAPP_PERS_AREA_START_ADDRESS,RETAIN_AREA_SIZE);

			break;
		}
		default:
			break;
	}
	return ERR_OK;
}

typedef struct 	area_info_tag
{
	void *p;
	unsigned long size;
}AreaInfo;

struct ArealistElem
{
	AreaInfo	ai;
	struct ArealistElem *next;
};

static struct ArealistElem *s_pArealistHead = NULL;

static void sysarea_register(void *pArea, unsigned long ulSize)
{
	struct ArealistElem *tmp = (struct ArealistElem *)malloc(sizeof(struct ArealistElem));

	if(!tmp)
	{
		printf("malloc in sysarea_register failed\n");
		return;
	}
	tmp->ai.p = pArea;
	tmp->ai.size = ulSize;
	tmp->next = s_pArealistHead;
	s_pArealistHead = tmp;
}

static unsigned long sysarea_unregister(void *pArea)
{
	unsigned long retval = 0;
	struct ArealistElem *tmp = s_pArealistHead;
	struct ArealistElem *last = NULL;

	while(tmp)
	{
		if(tmp->ai.p == pArea)
			break;
		last = tmp;
		tmp = tmp->next;
	}
	if(!tmp)
	{
		printf("sysarea_unregister failed - area not found\n");
	}
	else
	{
		if(!last)
			s_pArealistHead = tmp->next;
		else
			last->next = tmp->next;
		retval = tmp->ai.size;
		free(tmp);
	}
	return retval;
}

void sysarea_safeapp_map(char * pszName, void* pAddress, int length)
{
     int fd;
     void* pStartArea;
     
     fd = shm_open(pszName, O_RDWR, S_IRWXU | S_IRWXG);

     // check if this shm open was successfully                                                                                                                                                         
     DEBUGP("shm_open: %s,  %d\n",pszName,  fd);
     if(fd < 0)
     {
	  // try to create                                                                                                                                                                              
	  fd = shm_open(pszName,O_RDWR | O_CREAT,S_IRWXU | S_IRWXG);
	  DEBUGP("shm_open create: %s, %d\n",pszName,  fd);

     }
     if(fd < 0)
     {
	  DEBUGP("failed to create shm: %s", pszName);
	  return;
     }
     
     if(ftruncate(fd,length) < 0)
	  DEBUGP("ftruncate failed!");

     // map to address                                                                                                                                                                                  
     pStartArea = mmap(pAddress,length,PROT_READ|PROT_WRITE, MAP_SHARED | MAP_FIXED,fd,0);

     DEBUGP("mmap : %p, asked for %p\n", pStartArea, pAddress);



}

void sysarea_safeapp_unmap(char * pszName, void* pAddress, int length)
{
     munmap(pAddress,length);
     shm_unlink(pszName);
     DEBUGP("munmap: %p, length %d", pAddress, length);
     DEBUGP("smh_unlink: %s", pszName);

}


void* CDECL SysMemAllocData(char *pszComponentName, RTS_SIZE ulSize, RTS_RESULT *pResult)
{
	void *pMem;

	if (ulSize == 0)
		return NULL;

	if (CHK_MemGCGetSize)
		ulSize = CAL_MemGCGetSize(ulSize);
	pMem = calloc(ulSize, 1);
	if (pMem == NULL)
	{
		if (pResult != NULL)
			*pResult = ERR_NOMEMORY;
	}
	else
	{
		if (CHK_MemGCAdd)
			pMem = CAL_MemGCAdd(pszComponentName, pMem, ulSize);
		if (pResult != NULL)
			*pResult = ERR_OK;
	}
	return pMem;
}

void* CDECL SysMemReallocData(char *pszComponentName, void* pData, RTS_SIZE ulSize, RTS_RESULT *pResult)
{
	void *pMem;

	if (pData == NULL)
		return NULL;

	if (CHK_MemGCRemove)
		pData = CAL_MemGCRemove(pszComponentName, pData, &Result);
	if (CHK_MemGCGetSize)
		ulSize = CAL_MemGCGetSize(ulSize);
	pMem = realloc(pData, ulSize);
	if (pMem == NULL)
	{
		if (pResult != NULL)
			*pResult = ERR_NOMEMORY;
	}
	else
	{
		if (CHK_MemGCAdd)
			pMem = CAL_MemGCAdd(pszComponentName, pMem, ulSize);
		if (pResult != NULL)
			*pResult = ERR_OK;
	}
	return pMem;
}

RTS_RESULT SysMemFreeData(char *pszComponentName, void* pData)
{
	RTS_RESULT Result = ERR_OK;

	if (pData == NULL)
		return ERR_PARAMETER;

	if (CHK_MemGCRemove)
		pData = CAL_MemGCRemove(pszComponentName, pData, &Result);

	if  (Result == ERR_MEMORY_OVERWRITE) {
		DEBUGP("Memory was overwritten!");
	}

	if (pData != NULL && Result == ERR_OK) {
			free(pData);
	}
	return Result;
}

void* SysMemAllocArea(char *pszComponentName, unsigned short usType, RTS_SIZE ulSize, RTS_RESULT *pResult)
{
	void *pArea = MAP_FAILED;
	void *pStartAddress;


	if(ulSize == 0)
	{
		RTS_SETRESULT(pResult, ERR_OUT_OF_LIMITS);
		return NULL;
	}

	if(IsArea(usType, DA_RETAIN) && !(IsArea(usType, 0x800) || IsArea(usType, DA_DATA) || IsArea(usType, DA_CODE)))
	{
		if(ulSize > RETAIN_AREA_SIZE)
		{
			RTS_SETRESULT(pResult, ERR_OUT_OF_LIMITS);
			return NULL;
		}
		if(!s_bRetainAreaAllocated)
		{
			pArea = mmap((void*)RETAIN_AREA_START_ADDRESS, RETAIN_AREA_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
			if(pArea != MAP_FAILED)
				s_bRetainAreaAllocated = TRUE;
		}
	}
	else if(IsArea(usType, DA_DATA) && !(IsArea(usType, 0x800) || IsArea(usType, DA_RETAIN) || IsArea(usType, DA_CODE)))
	{
		if(ulSize > DATA_AREA_SIZE)
		{
			RTS_SETRESULT(pResult, ERR_OUT_OF_LIMITS);
			return NULL;
		}
		if(!g_bDataAreaAllocated)
		{
			pArea = mmap((void*)DATA_AREA_START_ADDRESS, DATA_AREA_SIZE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
			if(pArea != MAP_FAILED)
				g_bDataAreaAllocated = TRUE;
		}
	}

	if (pArea == MAP_FAILED)
	{
		RTS_SETRESULT(pResult, ERR_FAILED);
		return NULL;
	}

	RTS_SETRESULT(pResult, ERR_OK);
	sysarea_register(pArea,ulSize);

	return pArea;
}

RTS_RESULT SysMemFreeArea(char *pszComponentName, void* pData)
{
	int res;
	unsigned long ulSize;

#ifdef RTS_SIL2
	if (CHK_SIL2OEMGetOperationMode && CAL_SIL2OEMGetOperationMode() != RTS_SIL2_OPMODE_DEBUG)
	{
		if(CHK_SysExceptGenerateException)
		{
			RegContext Context = {0, 0, 0};
			ExceptionCode Exception;
		
			Exception.bOSException = 0;
			Exception.ulCode = RTSEXCPT_ACCESS_VIOLATION;
			CAL_SysExceptGenerateException(RTS_INVALID_HANDLE, Exception, Context);
			return ERR_FAILED;
		}
		else
		{
			DEBUGP("Error: SysExceptGenerateException missing!");
			exit(0);
		}
	}
#endif

	if(pData == NULL)
		return ERR_PARAMETER;

	if((void*)RETAIN_AREA_START_ADDRESS == pData && s_bRetainAreaAllocated)
		s_bRetainAreaAllocated = FALSE;
	else if((void*)DATA_AREA_START_ADDRESS == (unsigned long*)pData && g_bDataAreaAllocated)
		g_bDataAreaAllocated = FALSE;
	else
		return ERR_FAILED;

	ulSize = sysarea_unregister(pData);
	res = munmap(pData, ulSize);
	if (res < 0)
	{
		DEBUGP("munmap: %s", strerror(errno));
		return ERR_FAILED;
	}
	return ERR_OK;
}

void* CDECL SysMemAllocCode(char *pszComponentName, RTS_SIZE ulSize, RTS_RESULT *pResult)
{
	return 	SysMemAllocArea(pszComponentName, DA_CODE, ulSize, pResult);
}

RTS_RESULT CDECL SysMemFreeCode(char *pszComponentName, void* pCode)
{
	return 	SysMemFreeArea(pszComponentName, pCode);
}

RTS_RESULT CDECL SysMemIsValidPointer(void* ptr, RTS_SIZE ulSize, int bWrite)
{
	int ret_val, error = ERR_FAILED;
	if (ptr == NULL)
	{
	  DEBUGP("Invalid pointer: NULL");
	  return error;
	}

#if defined VALID_POINTER_CHECK_MAPPING
	return SysMemIsValidPointerMaping(ptr, ulSize, bWrite);
#endif

	pthread_mutex_lock(&sMutex);
	ret_val = sigsetjmp(gsig_buf, 1);

	if (ret_val == 0)
	{
		gbSysIsValidPointer = 1;
		gpTest = ptr;
		gsig_addr = *gpTest;
		gbSysIsValidPointer = 0;
	}
	if (gpTest == &gsig_addr)
	{
	  DEBUGP("Invalid pointer: %p", ptr);
	}
	else
	{
		error = ERR_OK;
	}
	pthread_mutex_unlock(&sMutex);
	return error;
}

#if defined VALID_POINTER_CHECK_MAPPING

/* #include <time.h> */
RTS_RESULT CDECL SysMemIsValidPointerMapping(void* ptr, unsigned long ulSize, int bWrite)
{
	pid_t actual_process;
	FILE *process_mapping;
	char file_name[255], file_buffer[800], sdummy[6], sname[255];
	unsigned long begin, end, uldummy;
	int save_ptr = 0;
	/* struct timespec now, old;
	clock_gettime(CLOCK_MONOTONIC, &old);
	*/

	actual_process = getpid();

	snprintf(file_name, sizeof(file_name)-1, "/proc/%ld/maps", (unsigned long)actual_process);

	process_mapping = fopen(file_name, "r");

	if (!process_mapping) {
		DEBUGP("Error: %s", strerror(errno));
		return ERR_OK;// we can't read the file, so no memory checking is possible - go on without
	}

	while (!feof(process_mapping)) { // go through the whole file and check memory
		fgets(file_buffer, sizeof(file_buffer), process_mapping);
		sscanf(file_buffer, "%lx-%lx %4s %lx %5s %ld %s", &begin, &end, sdummy, &uldummy, sdummy, &uldummy, sname);
		if (ptr >= begin && ptr <= end) {
			save_ptr = 1;
			break;
		}
	}

	fclose(process_mapping);
	if (save_ptr != 1) {
		DEBUGP("Invalid pointer: %lx", ptr);
		return ERR_FAILED;
	}
/*
	clock_gettime(CLOCK_MONOTONIC, &now);
	DEBUGP("Time elapsed: %ld ns", now.tv_nsec - old.tv_nsec);
*/
	return ERR_OK;
}
#endif

