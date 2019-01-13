/*
 * Модуль реализует системный вызов установки сетевых параметров МЭК библиотеки
 * EmiconConfigurator.
 * Стандартные функции установки IP и Маски, стирают информацию о Gateway.
 * Установку производим с помощью системных вызовов.
 */

#include "CmpStd.h"
#include "CmpEmiconNetworkDep.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <errno.h>
#include <netinet/in.h>
#include <net/route.h>

#if defined(__GLIBC__) && __GLIBC__ >=2 && __GLIBC_MINOR__ >= 1
#include <netpacket/packet.h>
#include <net/ethernet.h>
#else
#include <sys/types.h>
#include <netinet/if_ether.h>
#endif

#include <arpa/inet.h>

int sys_set_ip(char *iface_name, char *ip_addr, char *mask, char *gateway_addr);

USE_STMT

#ifndef RTS_COMPACT_MICRO

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


static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}


static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}


static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif


static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook) {
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
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
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;

	default:
		break;
	}
	return ERR_OK;
}


void CDECL CDECL_EXT reset_ip(reset_ip_struct *p)
{
	system("systemctl restart systemd-networkd");
	//usleep(80000);
}

void CDECL CDECL_EXT set_ip(set_ip_struct *p)
{
	p->set_ip = sys_set_ip(p->iface_name, p->ip_addr, p->mask,
			       p->gateway_addr);
	return;
}
/*
 * Set ip function
 */
int sys_set_ip(char *iface_name, char *ip_addr, char *mask,
	       char *gateway_addr)
{
// ip route flush dev interface
// ip addr flush dev interface
// ip addr add 192.168.1.2/24 broadcast 192.168.1.255 dev eth0
// ip route add default via 192.168.1.1

	uint32_t n;
	uint32_t n_mask = 1;
	uint8_t bits = 0;
	char str[100];

	inet_pton(AF_INET, mask, &n);
	while (n > 0) {
		if (n & n_mask)
			bits++;
		n = n >> 1;
	}

	sprintf(str, "ip addr flush dev %s", iface_name);
	//fprintf(stderr, "%s\n", str);
	system(str);


	sprintf(str, "ip addr add %s/%d dev %s", ip_addr, bits, iface_name);
	//fprintf(stderr, "%s\n", str);
	system(str);

	sprintf(str, "ip route add default via %s", gateway_addr);
	//fprintf(stderr, "%s\n", str);
	system(str);

	return 0;
}
