/**
 * <name>CmpTemplate.c</name>
 * <description> 
 *  Example for an empty runtime component frame that can be used as a starting point to develop own components.
 *
 *  MANDATORY FUNCTIONS:
 *  - ComponentEntry()
 *  - ExportFunctions()
 *  - ImportFunctions()
 *  - CmpGetVersion()
 *  - HookFunction()
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */
#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconSysDep.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>
#include <sys/stat.h>


const char *MEM_FILE_NAME[] = {
	"cs1_mem.txt",
	"cs2_mem.txt",
};

static int _fd_cs[2];
static bool _is_emu = false;



#define SPI_PORT "/dev/spidev1.0"
#define SPI_SPEED  100000

#define CS_num_max 2

const uint32_t mem_address[CS_num_max] = {0x4000000, 0x3000000}; //CS1  размер 0x60000
const uint32_t mem_size[CS_num_max] = {0x60000, 0x20000};

uint32_t alloc_mem_size[CS_num_max], page_mask, page_size;
void *mem_pointer[CS_num_max], *virt_addr[CS_num_max];
int fd;
int ret;
uint32_t SockArr[256];

int memory_init (unsigned char cs_num);
int memory_unmap (unsigned char cs_num);
int spi_set(uint32_t speed);
static void spi_transfer(uint8_t const *tx, size_t len);
void CloseAllSocket(void);
void InitAllSocket(void);
int watchdog_enabled = 0;

USE_STMT

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI			IN	Pointer to component mangager function to get a api function
 *		pfCallHook			IN	Pointer to component mangager function to call a hook function
 * </param> 
 * <result>ERR_OK if component could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = NULL;
	pInitStruct->pfDeleteInstance = NULL;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	return ERR_OK;
}

/**
 * <description>Publish exported functions to the component manager, to make them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Import function pointers from other components. Use generated macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/**
 * <description>Hook function to get all broadcast hooks of the component manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();
		memory_init(1);
		memory_init(2);
		InitAllSocket();

		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		break;

	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		memory_unmap(1);
		memory_unmap(2);
		CloseAllSocket();	
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
	{

		EXIT_STMT;
		break;
	}


		default:
			break;
	}
	return ERR_OK;
}


int memory_init (unsigned char cs_num) {
	unsigned char i;
	struct stat sb;
	char buffer[1024] = {0};

    if((cs_num < 1) || (cs_num > CS_num_max)) return -1;
	else i = cs_num - 1;


	page_size = sysconf(_SC_PAGESIZE);
	alloc_mem_size[i] = (((mem_size[i] / page_size) + 1) * page_size);

	if (!_is_emu) {
		page_mask = (page_size - 1);
		fd = open("/dev/mem", O_RDWR | O_SYNC);
		mem_pointer[i] = mmap(NULL,
					alloc_mem_size[i],
					PROT_READ | PROT_WRITE,
					MAP_SHARED,
					fd,
					(mem_address[i] & ~page_mask)
				 );
		if(mem_pointer[i] == MAP_FAILED) { 
			printf("Memory allocation failed: CS%d \n", cs_num);
			fflush(stdout);
			return -1;
		};
		
		virt_addr[i] = (mem_pointer[i] + (mem_address[i] & page_mask));
		printf("Memory is allocated in RAM 0x%X for CS%d, Virtual addr:0x%X \n",
			alloc_mem_size[i], cs_num, virt_addr[i]);

	} else {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Emulation mode detected!");

		_fd_cs[i] = open(MEM_FILE_NAME[i], O_RDWR | O_CREAT,
				 S_IRUSR | S_IRGRP | S_IROTH);
		if (fstat(_fd_cs[i], &sb) == -1){
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
			ERR_FAILED, 0, 
			"Failed: fstat CS: %s",
			strerror(errno));
			return MAP_FAILED;
		}

		if (sb.st_size < alloc_mem_size[i]) {
			for (int j = 0; j < alloc_mem_size[i]/sizeof(buffer); j++)
				write(_fd_cs[i], &buffer, sizeof(buffer));

			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Fail CS sim is written to: %d", alloc_mem_size[i]);
		}

		virt_addr[i] = mmap(0, alloc_mem_size[i], PROT_READ | PROT_WRITE,
		     		    MAP_SHARED, _fd_cs[i], 0);

	}


	fflush(stdout);
	return 0;
}

int memory_unmap (unsigned char cs_num) {
    if((cs_num < 1) || (cs_num > CS_num_max)) return -1;
	
	if(munmap(mem_pointer[cs_num-1], alloc_mem_size[cs_num-1]) == -1)
		printf("Memory dealloc failed: CS%d \n", cs_num);
	else
		printf("Memory is deallocated: CS%d \n", cs_num);
	close(fd);
	return 0;
}


void CDECL CDECL_EXT set_inhibit(set_inhibit_struct *p)
{
	/* Запись в регистр 40000Н любого числа освежает INHIBIT
	*/
	*((unsigned char *)virt_addr[0] + 0x40000) = 123;
}

void CDECL CDECL_EXT set_watchdog(set_watchdog_struct *p)
{
	/*
		Активация циклом 1.6 секунды в регистр 50000Н
	*/
	int output_fd;
	char str[4];
	if (!watchdog_enabled) {
		strcpy(str, "96");
		output_fd = open("/sys/class/gpio/export", O_WRONLY);
		write(output_fd, str, strlen(str));
		close(output_fd);

		strcpy(str, "out");
		output_fd = open("/sys/class/gpio/gpio96/direction", O_WRONLY);
		write(output_fd, str, strlen(str));
		close(output_fd);

		strcpy(str, "0");
		output_fd = open("/sys/class/gpio/gpio96/value", O_WRONLY);
		write(output_fd, str, strlen(str));
		close(output_fd);
		watchdog_enabled = TRUE;
		printf("Watchdog is activated\n");
	}

	*((unsigned char *)virt_addr[0] + 0x50000) = 1;
	
}


// Возвращает указатель на нулевой слот
void CDECL CDECL_EXT get_ptr_to_slot0(get_ptr_to_slot0_struct *p)
{
    if(virt_addr[0] != NULL)
    {
	p->Get_ptr_to_slot0 = (unsigned char*)(virt_addr[0]);
    }
    else
    {
	p->Get_ptr_to_slot0 = 0;
    }
}

// возвращает указатель на ДПМ
void CDECL CDECL_EXT get_ptr_to_dpm(get_ptr_to_dpm_struct *p)
{
    if(virt_addr[1] != NULL)
    {
	p->Get_ptr_to_DPM = (unsigned short*)(virt_addr[1]);
    }
    else
    {
	p->Get_ptr_to_DPM = 0;
    }
}

void CDECL CDECL_EXT get_ptr_to_sock_arr(get_ptr_to_sock_arr_struct *p)
{
	p->Get_ptr_to_sock_arr = SockArr;
}

void CloseAllSocket(void)
{
	int i;
	for (i=0; i<256; i++)
	{
		if (SockArr[i]) 
		{
			close(SockArr[i]);
			SockArr[i]=0;
		}
	}
}

void InitAllSocket(void)
{
	int i;
	for (i=0; i<256; i++) SockArr[i]=0;
}

void CDECL CDECL_EXT syssync(syssync_struct *p)
{
	system("sync");
} 
