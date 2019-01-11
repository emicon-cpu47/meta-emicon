/***************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		SocketCanDrv.c
*	Version:		3.5.0.0
*	Purpose:		Implementaion of CAA Socket Can Mini Driver
*	Author:			PhB
*
******************************************************************************/

#ifdef CAALib

/********** Includes *********/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <ctype.h>
#include <libgen.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <net/if.h>
#include <poll.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <linux/can/error.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <termios.h>
#include <string.h>

#ifdef CAN_OLD_BAUD
#include <linux/can/ioctl.h>
#endif

#ifndef PF_CAN
	#define PF_CAN 29
#endif
#ifndef AF_CAN
	#define AF_CAN PF_CAN
#endif

/* Linux specific part end */

#include "CAADefines.h"
#include "CmpSocketCanDrvDep.h"

USEEXTERN_STMT;

#define Socket_NNET CL2_NNET
#define Socket_NDRIVER CL2_NNET

static char s_interfacename[10];
static CL2I_INFO* s_pInfo[Socket_NNET];
static CMD_INFO cmdInfo;
static CL2I_BYTE s_byDriver[CL2_NNET];
static CL2I_BYTE s_byNet[Socket_NDRIVER];


static CAA_ERROR CMD_Setup(CL2I_BYTE byNet);
static CAA_ERROR CMD_Init(CL2I_BYTE byNet, CL2I_WORD wBaudrate);
static CAA_BOOL  CMD_Send(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio,
			  CAA_ERROR* peError);
static CAA_BOOL  CMD_Receive(CL2I_BYTE byNet, CAA_HANDLE hBlock,
			     CAA_ERROR* peError);
static CAA_ERROR CMD_GetInfo(CL2I_BYTE byNet, CMD_INFO* pInfo);
static CAA_ERROR CMD_Dispose(CL2I_BYTE byNet);
static CAA_ERROR CMD_Identify(CL2I_BYTE byNet, CL2I_BYTE byCount);
static CAA_HANDLE CMD_SetBlock(CL2I_BYTE byNet, CL2I_BYTE byIndex,
			       CAA_HANDLE hBlock, CAA_ERROR* peError);
static CAA_ERROR CMD_SetCycle(CL2I_BYTE byNet, CL2I_BYTE byIndex,
			      CL2I_DWORD dwCycle);
static CAA_ERROR CMD_SetMask(CL2I_BYTE byNet, CL2I_BYTE byIndex,
			     CL2I_DWORD dwValue, CL2I_DWORD dwMask);
static CAA_ERROR CMD_ResetAlarm(CL2I_BYTE byNet);

static CMD_CMDRV cmdInterface[] =
{
	{
		CMD_Setup,
		CMD_Init,
		CMD_Send,
		CMD_Receive,
		CMD_GetInfo,
		CMD_Dispose,
		CMD_Identify,
		CMD_SetBlock,
		CMD_SetCycle,
		CMD_SetMask,
		CMD_ResetAlarm,
		0
	}
};

static struct sockaddr_can addr;
static struct ifreq ifr;
struct sched_param g_sched_param;
static int s_ctrl_cnt = 0;

/*******************************************************************************
 * Start of helper functions
 ******************************************************************************/
#define DRV_MAX_CANCARDS CL2_NNET

/* Filedescriptor arrays */
static long s_fd_write[DRV_MAX_CANCARDS];
static long s_fd_read[DRV_MAX_CANCARDS];

/* Message arrays */
static struct can_frame msg_read[DRV_MAX_CANCARDS];
static struct can_frame msg_write[DRV_MAX_CANCARDS];
static pthread_t s_hRxTask = RTS_INVALID_HANDLE;
static RTS_UI32 s_reset_current[DRV_MAX_CANCARDS];
static RTS_UI32 s_reset_last[DRV_MAX_CANCARDS];

#define MAX_SOCKET_MSG 100 * CL2_NNET

static int global_stop = 0;
static int s_bTimestamps;

//#define SOCKETCAN_ASYNC_SEND

#ifdef SOCKETCAN_ASYNC_SEND

#include <mqueue.h>


typedef struct {
	CL2I_BYTE byNet;
	CAA_HANDLE hBlock;
} SOCKET_TX_HANDLE;

static RTS_HANDLE s_hTxTask = RTS_INVALID_HANDLE;
static mqd_t s_msg_queue = (mqd_t)-1;

void TxThread(SYS_TASK_PARAM *ptp)
{
	int stop = 0;
	int resend = 0;
	SOCKET_TX_HANDLE socket_tx_handle;
	CL2I_BYTE byNet = 0;
	CL2I_BLOCK* pBlock;
	RTS_HANDLE hTask = ptp->hTask;
	CL2I_BYTE pbySrc;
	CAA_BOOL xType;
	int i;

	while (stop == 0 && global_stop == 0 && !ptp->bExit) {
		if (resend != 0)
			goto Resend;

        if (mq_receive(s_msg_queue, (char *)&socket_tx_handle,\
            sizeof(SOCKET_TX_HANDLE), 0) != -1) {
			pBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(socket_tx_handle.hBlock);
			byNet = socket_tx_handle.byNet;

			if (pBlock == 0) {
				continue;
			}

			if (byNet == 0xff) {
				continue;
			}

			if(s_bTimestamps && pBlock->dwTSP != 0)
			{
				//check TTL
				RTS_SYSTIME time;
				CL2I_DWORD dwTime, dwTTL;
		
				CAL_SysTimeGetUs(&time);
				dwTime = (CL2I_DWORD)time;
				dwTTL = pBlock->dwTSP;

				if ((dwTTL < dwTime && (dwTime - dwTTL) < 0x80000000) ||
				    (dwTTL > dwTime && (dwTTL - dwTime) >= 0x80000000))
				{
					//dwTTL < dwTime ==> message is not valid anymore ==> discard it
					CAA_SET_RESULT(peError, CMD_TTL_ERROR);
					return CMD_SND_NOT_OK;
				}	
			}

			if ((s_pInfo[s_byDriver[byNet]]->byBusState == CL2_PASSIVE)) {
				s_pInfo[s_byDriver[byNet]]->ctTxErrors++;
				CAL_CL2_MsgFree(byNet, socket_tx_handle.hBlock);
			}

			xType = (pBlock->cobId.X.EID != 0);
			pbySrc=(int)&(pBlock->byData[0]);

			if (xType) { /* Extended transmission */
				msg_write[byNet].can_id = ((pBlock->cobId.X.ID & CAN_EFF_MASK)
							   | CAN_EFF_FLAG);
			} 
			else { /* Standard transmission */
				msg_write[byNet].can_id = (pBlock->cobId.X.ID & CAN_SFF_MASK);
			}

			/* Remote Transmission Request add the RTR FLAG */
			if (pBlock->cobId.X.RTR) {
				msg_write[byNet].can_id = pBlock->cobId.X.ID | CAN_RTR_FLAG;
			}

			msg_write[byNet].can_dlc = pBlock->byLen.X.DLC;

			for (i = 0; i < msg_write[byNet].can_dlc; i++) {
				msg_write[byNet].data[i] = pBlock->byData[i];
			}
		Resend:

			if (write(s_fd_write[byNet], &msg_write[byNet], sizeof(msg_write[byNet])) < 0) 
			{ 		/* Error sending */
#ifndef RTS_DONT_RESEND_ON_NETDOWN
				if (errno == ENETDOWN)
				{
					if(resend++ < 2)
					{
						DEBUGP(".");
						usleep(1000);
						continue;
					}
				}
#endif
                if (errno == ENOBUFS)
                {
                    s_pInfo[s_byDriver[byNet]]->byBusState = CL2_BUSOFF;
                    continue;
                }

				// drop message
				resend = 0;
				s_pInfo[s_byDriver[byNet]]->ctTxErrors++;
                if (s_pInfo[s_byDriver[byNet]]->ctTxErrors >= 128) {
                    s_pInfo[s_byDriver[byNet]]->ctTxErrors=0;
                    s_pInfo[s_byDriver[byNet]]->uiBusAlarm++;
                }
				CAL_CL2_MsgFree(byNet, socket_tx_handle.hBlock);
				DEBUGP("dropped message: %s", strerror(errno));
				continue;
			}
			/* TX succeeded */
			if(s_bTimestamps)
			{
				RTS_SYSTIME time;
				CAL_SysTimeGetUs(&time);
				pBlock->dwTSP = (CL2I_DWORD)time;
			}
			else
				pBlock->dwTSP = 0;
			s_pInfo[s_byDriver[byNet]]->ctMessagesSend++;	
			resend = 0;
			/* Tell CL2 that everything is ok */
			CAL_CL2_MsgSendAckn(byNet, socket_tx_handle.hBlock);
		}
		else {
			DEBUGP("mq_receive failed - reason: %s", strerror(errno));
			continue;
		}
	}

	pthread_exit(0);
}
#endif
void RxThread(void)
{
	CAA_HANDLE hBlock;
	CL2I_BLOCK* pBlock;
	CL2I_BYTE byNet;
	int stop = 0;
	fd_set fdset;
	int ret;
	sigset_t sigset;
	

	/* Change the signal mask */
	sigemptyset(&sigset);
        sigaddset(&sigset,SIGUSR2);

	/* Test if the socket is open if not - wait */
	while (s_fd_read[0] == -1) {
		DEBUGP("Socket not yet initialized...");
		usleep(1000);
	};

	DEBUGP("can RxThread running - listening on %d controllers", s_ctrl_cnt);
	FD_ZERO(&fdset);

	while (stop == 0 && global_stop == 0 ) {
	/* Put all the read file descriptors in (again in) the fdset */
		for (byNet=0; byNet<s_ctrl_cnt; byNet++) {
			FD_SET(s_fd_read[byNet], &fdset);
		}
		if (select (FD_SETSIZE, &fdset, NULL, NULL, NULL) > 0) {
			for (byNet=0; byNet<s_ctrl_cnt; byNet++) {
				/* Now only the fds which have data are in fdset */
				if (FD_ISSET(s_fd_read[byNet], &fdset)) {
					/* read the matching fd (blocking) */
					ret = read(s_fd_read[byNet], &msg_read[byNet],
						   sizeof(msg_read[byNet]));

					if (ret < 0) {
							DEBUGP("can read error:%s", strerror(errno));
					}
					else {
						if (msg_read[byNet].can_id & CAN_ERR_FLAG) {
							if (msg_read[byNet].can_id & CAN_ERR_BUSOFF) {
//								DEBUGP("Bus off");
								s_pInfo[s_byDriver[byNet]]->uiBusAlarm++;
								if (s_pInfo[s_byDriver[byNet]]->uiBusAlarm == 0) {
									s_pInfo[s_byDriver[byNet]]->uiBusAlarm = 1;
								}
								s_pInfo[s_byDriver[byNet]]->byBusState = CL2_BUSOFF;
								usleep(1000);
							}
							if (msg_read[byNet].can_id & CAN_ERR_TX_TIMEOUT) {
								DEBUGP("Tx timeout");
								s_pInfo[s_byDriver[byNet]]->ctTxErrors++;
							}
							if (msg_read[byNet].can_id & CAN_ERR_ACK) {
								//no response -> cable of maybe (on some chips)
								DEBUGP("Ack");
								s_pInfo[s_byDriver[byNet]]->ctTxErrors++;
							}
							if (msg_read[byNet].can_id & CAN_ERR_LOSTARB) {
//								DEBUGP("Lost arb ");
								s_pInfo[s_byDriver[byNet]]->uiBusAlarm++;
								if (s_pInfo[s_byDriver[byNet]]->uiBusAlarm == 0) {
									s_pInfo[s_byDriver[byNet]]->uiBusAlarm = 1;
								}
								s_pInfo[s_byDriver[byNet]]->byBusState = CL2_BUSOFF;
								usleep(1000);
							}
							if (msg_read[byNet].can_id & CAN_ERR_CRTL) { DEBUGP("Crtl %x", msg_write[byNet].data[1]);
								if (msg_write[byNet].data[1] & CAN_ERR_CRTL_RX_OVERFLOW) {
									s_pInfo[s_byDriver[byNet]]->ctDataOverruns++;
									DEBUGP("[RX buffer overflow]");
								}
								if (msg_write[byNet].data[1] & CAN_ERR_CRTL_TX_OVERFLOW) {
									s_pInfo[s_byDriver[byNet]]->ctDataOverruns++;
									DEBUGP("[TX buffer overflow]");
								}
								if (msg_read[byNet].data[1] & CAN_ERR_CRTL_RX_PASSIVE) {
									s_pInfo[s_byDriver[byNet]]->byBusState = CL2_PASSIVE;
									DEBUGP("[RX passive]");
								}
								if (msg_read[byNet].data[1] & CAN_ERR_CRTL_TX_PASSIVE) {
									s_pInfo[s_byDriver[byNet]]->byBusState = CL2_PASSIVE;
									DEBUGP("[TX passive]");
								}
								if (msg_write[byNet].data[1] & CAN_ERR_CRTL_RX_WARNING) {
									s_pInfo[s_byDriver[byNet]]->byBusState = CL2_WARNING;
									DEBUGP("[RX warning]");
								}
								if (msg_write[byNet].data[1] & CAN_ERR_CRTL_TX_WARNING) {
									s_pInfo[s_byDriver[byNet]]->byBusState = CL2_WARNING;
									DEBUGP("[TX warning]");
								}
							}
						}
						else {
							s_pInfo[s_byDriver[byNet]]->byBusState = CL2_ACTIVE;
							s_pInfo[s_byDriver[byNet]]->uiBusAlarm = 0;
							hBlock = CAL_CL2_MsgAlloc(byNet, CAA_pNULL);
							pBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(hBlock);
							if (pBlock != 0) {
								if (msg_read[byNet].can_id & CAN_RTR_FLAG) {
									//RTR occured - only print: #
									//printf("#");
									pBlock->cobId.X.RTR = CAA_TRUE;
										}
								if (msg_read[byNet].can_id & CAN_EFF_FLAG) {
									//EFF - print: x
									//printf("x");
									pBlock->cobId.X.EID = CAA_TRUE;
								}

								pBlock->byLen.B = msg_read[byNet].can_dlc;
								pBlock->byNet = byNet;
								if(s_bTimestamps)
								{
									RTS_SYSTIME time;
									CAL_SysTimeGetUs(&time);
									pBlock->dwTSP = (CL2I_DWORD)time;
								}
								else
									pBlock->dwTSP = 0;
								pBlock->cobId.X.ID = msg_read[byNet].can_id;
								memcpy(pBlock->byData, msg_read[byNet].data, 8);
								s_pInfo[s_byDriver[byNet]]->ctMessagesReceived++;
								CAL_CL2_MsgPutRQueue(byNet, hBlock);
#if 0
								int i;
								DEBUGP("CobID: 0x%x", pBlock->cobId.X.ID & CAN_SFF_MASK);
								DEBUGP("CobID: 0x%x", pBlock->cobId.X.ID);
								DEBUGP("Data: ");
								for (i=0; i<8; i++) {
									printf("%02x ", pBlock->byData[i]);
								}
								DEBUGP("\nDLC: 0x%x", pBlock->byLen.B);
#endif
/*
								if(s_pInfo[s_byDriver[byNet]]->byBusState != CL2_ERR_FREE) {
									s_pInfo[s_byDriver[byNet]]->byBusState = CL2_ACTIVE;

								}
*/
							}
							else {
								s_pInfo[s_byDriver[byNet]]->ctDataOverruns++;
								DEBUGP("can read error: no message handle available");
							}
						}
					}
				}
			}
		}
	}

	pthread_exit(0);
}

static RTS_RESULT setbaudrate(CL2I_BYTE byNet, CL2I_WORD wBaudrate)
{
	RTS_RESULT result = ERR_OK;
#ifndef CAN_OLD_BAUD
    struct stat st;
	char interfacename[10];
	char baudratepath[160];
	char baudratefile[80];
	char script[160+80];
    char log_entry[160+80+30];
	int iLen;
    
	iLen = sizeof(interfacename);
	CAL_SettgGetStringValue(COMPONENT_NAME, SOCKETCAN_STRING_INTERFACENAME,\
        interfacename, &iLen, SOCKETCAN_STRING_INTERFACENAME_DEFAULT, 0);
	iLen = sizeof(baudratepath);
	CAL_SettgGetStringValue(COMPONENT_NAME, SOCKETCAN_STRING_SCRIPTPATH, baudratepath, &iLen,\
				SOCKETCAN_STRING_SCRIPTPATH_DEFAULT, 0);
	iLen = sizeof(baudratefile);
	CAL_SettgGetStringValue(COMPONENT_NAME, SOCKETCAN_STRING_SCRIPTNAME, baudratefile, &iLen,\
				SOCKETCAN_STRING_SCRIPTNAME_DEFAULT, 0);

    snprintf(script, sizeof(script), "%s/%s", baudratepath, baudratefile);
    DEBUGP("Script: %s", script);
    
	if (stat(script, &st) != 0) {
        DEBUGP("Sorry no such script");
        snprintf(log_entry, sizeof(log_entry), "Script: %s not found - %s%d will not work!", baudratefile, s_interfacename, byNet);
        CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_OK, 1, log_entry);
        return ERR_FAILED;
	}
    else
    {
        //reuse script - note: size will decrease a little bit but should be ok
        memset(script, 0, sizeof(script));
        snprintf(script, sizeof(script), "sh %s/%s %s%d %d", baudratepath, baudratefile,\
        interfacename, (int)byNet, (int)wBaudrate);
        DEBUGP("Executing: %s", script);
        system(script);
    }
    
#else
	/* old SocketCAN implementation */
	unsigned long* br = (unsigned long*) &ifr.ifr_ifru;

	*br = wBaudrate * 1000;
	if(ioctl(s_fd_write[byNet], SIOCSCANBAUDRATE, &ifr) < 0)
    {
		DEBUGP("Error setting baudrate for %d: %s", byNet, strerror(errno));
		result = ERR_NOT_SUPPORTED;
	}
#endif
	return result;
}

/*******************************************************************************
 * Start of "interface" functions
 ******************************************************************************/

/*
 * This function has to initialize the particular CAN bus chip such, that it
 * reacts to the connected CAN bus in a completely passive manner. The necessary
 * memory should be allocated, so that a subsequent call to xyz_init starts the
 * CAN bus service without further expense. Interrupts should not yet be enabled
 */
static CAA_ERROR CMD_Setup(CL2I_BYTE byNet)
{
	char devname[5] = {0};
	CAA_ERROR result = CMD_SETUP_ERROR;
    int iLen;

	iLen = sizeof(s_interfacename);
	CAL_SettgGetStringValue(COMPONENT_NAME, SOCKETCAN_STRING_INTERFACENAME,\
        s_interfacename, &iLen, SOCKETCAN_STRING_INTERFACENAME_DEFAULT, 0);

	CAL_SettgGetIntValue(COMPONENT_NAME, SOCKETCAN_INT_TIMESTAMPS, &s_bTimestamps, SOCKETCAN_INT_TIMESTAMPS_DEFAULT, 0);
	
	if (ERR_OK != CAL_CMUtlsnprintf(devname, sizeof(devname), "%s%d", s_interfacename, byNet))	{
		DEBUGP("sprintf: %s", strerror(errno));
	}

	CAL_CMUtlSafeStrCpy(ifr.ifr_name, sizeof(ifr.ifr_name), devname);
	addr.can_family = AF_CAN;

	s_fd_write[byNet] = -1;
	s_fd_read[byNet] = -1;

	/* Open CAN Device File for reading */
	if (s_fd_read[byNet] <= 0) {
		s_fd_read[byNet] = socket(PF_CAN, SOCK_RAW, CAN_RAW);
		if (s_fd_read[byNet] <= 0) {
			DEBUGP("Opening socket for reading (%s%d) failed: %s", s_interfacename,
			       byNet, strerror(errno));
			return result;
		} else {
			DEBUGP("Opened socket for reading (%s%d)", s_interfacename, byNet);
		}
	}

	if (ioctl(s_fd_read[byNet], SIOCGIFINDEX, &ifr)) {
		DEBUGP("ioctl(SIOCGIFINDEX): %s", strerror(errno));
		return result;
	}
	addr.can_ifindex = ifr.ifr_ifindex;
/*
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	if(setsockopt(s_fd_write[byNet], SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof(tv))) {
		DEBUGP("%s", strerror(errno));
	}
	can_err_mask_t err_mask = 0xFFFFFFFF;
*/

	can_err_mask_t err_mask = CAN_ERR_BUSOFF | CAN_ERR_TX_TIMEOUT | CAN_ERR_CRTL;
	if (setsockopt(s_fd_read[byNet], SOL_CAN_RAW, CAN_RAW_ERR_FILTER, &err_mask, sizeof(err_mask))) {
		DEBUGP("setsockopt(CAN_RAW_ERR_FILTER): %s", strerror(errno));
	}

	int recv_own_msgs = 1; // 0 = disabled (default), 1 = enabled

	if(setsockopt(s_fd_read[byNet], SOL_CAN_RAW, CAN_RAW_RECV_OWN_MSGS,
		   &recv_own_msgs, sizeof(recv_own_msgs))) {
		DEBUGP("setsockopt(CAN_RAW_RECV_OWN_MSGS): %s", strerror(errno));
	}

	if (bind(s_fd_read[byNet], (struct sockaddr *)&addr, sizeof(struct sockaddr_can))) {
		DEBUGP("bind: %s", strerror(errno));
		return result;
	}
	
	/* We do everything asynchronous (blocking) you can change this by: */
	//fcntl (s_fd_read[byNet], F_SETFL, O_NONBLOCK);

	/* Open CAN Device File for writing */
	if (s_fd_write[byNet] <= 0) {
		s_fd_write[byNet] = socket(PF_CAN, SOCK_RAW, CAN_RAW);
		if (s_fd_write[byNet] <= 0) {
			DEBUGP("Opening socket for writing (%s%d) failed: %s", s_interfacename,
			       byNet, strerror(errno));
			return result;
		} else {
			DEBUGP("Opened socket for writing (%s%d)", s_interfacename, byNet);
		}
	}

	int loopback = 0;
	if(setsockopt(s_fd_write[byNet], SOL_CAN_RAW, CAN_RAW_LOOPBACK, &loopback, sizeof(loopback))) {
		DEBUGP("setsockopt(CAN_RAW_LOOPBACK): %s", strerror(errno));
	}

	if (ioctl(s_fd_write[byNet], SIOCGIFINDEX, &ifr)) {
		DEBUGP("ioctl(SIOCGIFINDEX): %s", strerror(errno));
		return result;
	}
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s_fd_write[byNet], (struct sockaddr *)&addr, sizeof(addr))) {
		DEBUGP("bind: %s", strerror(errno));
		return result;
	}
#ifndef SOCKETCAN_ASYNC_SEND
	fcntl(s_fd_write[byNet], F_SETFL , O_NONBLOCK);
#endif
	s_ctrl_cnt++;
	return CMD_NO_ERROR;
}


/*
 * This function adjusts the baud rate and enables the interrupt handling.
 * Therefore, from now on receiving and sending of CAN bus messages must be
 * possible. Optional acceptance filters may still be configured such, that
 * no messages are received. They do not get adjusted until CMD_SetMask is
 * called. If CMD_SetMask is not supported by the driver, the acceptance filters
 * should be adjusted such that all messages will be received. The higher
 * software layer then cares for an appropriate handling.
*/
static CAA_ERROR CMD_Init(CL2I_BYTE byNet, CL2I_WORD wBaudrate)
{

	RTS_RESULT Result = ERR_FAILED;
#ifdef SOCKETCAN_ASYNC_SEND
	mqd_t msgq_id;
	struct mq_attr attr;
	char szDummy[37] = "abcdefghijklmnopqrstuvwxyz1234567890";
	char szName[38];
#endif 

	Result = setbaudrate(byNet, wBaudrate);
	if (Result) {
            DEBUGP("setting can baudrate failed - %s%d will not work", s_interfacename, byNet);
            return CMD_SETUP_ERROR;
	} 

#ifdef SOCKETCAN_ASYNC_SEND
    /* generate a unique name here for pszName */
	strfry(szDummy);
	CAL_CMUtlsnprintf(szName, sizeof(szName), "/%s", szDummy);

    /* initialize the message queue */
	attr.mq_flags = 0;
	attr.mq_maxmsg = MAX_SOCKET_MSG;
	attr.mq_msgsize = sizeof(SOCKET_TX_HANDLE); /* size in bytes! */

	/* Set up the message queue for communication with TX thread */    
	if (s_msg_queue == (mqd_t)-1) { //only setup one msq
        /* create a blocking msgq */
        msgq_id = mq_open(szName, O_CREAT|O_EXCL|O_RDWR, S_IRWXU|S_IRWXG|S_IRWXO, &attr);
        if (msgq_id == -1) {
            DEBUGP("mq_open: %s", strerror(errno));
            return CMD_SETUP_ERROR;
        } else {
            DEBUGP("Unique name of MsgQ is: %s", szName);
            s_msg_queue = msgq_id;
        }
    }
#endif

	/* Setup the RX and TX threads one time: */
	global_stop = 0;
	if (s_hRxTask == RTS_INVALID_HANDLE) {
		int res;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
		res= pthread_create(&s_hRxTask,&attr, RxThread,NULL); //TASKPRIO_IDLE
		pthread_attr_destroy(&attr);
		if (res!=0)
			DEBUGP("pthread_create:%s",strerror(errno));
	}

#ifdef SOCKETCAN_ASYNC_SEND
	if (s_hTxTask == RTS_INVALID_HANDLE) {
		s_hTxTask = CAL_SysTaskCreate("SocketTXThread", TxThread,\
					      NULL, TASKPRIO_SYSTEM_END, 1000, 0, 0, &Result); //TASKPRIO_SYSTEM_BASE+31
	}
#endif
	memset(s_pInfo[s_byDriver[byNet]], 0, sizeof(CL2I_INFO));
	s_pInfo[s_byDriver[byNet]]->byBusState = CL2_ERR_FREE;

	return CMD_NO_ERROR;
}

/*
 * This function should copy the message into the register of the CAN bus chip.
 * It should prepare the Tx interrupt handling and effect the sending of the
 * message. If the message fails to be sent, the function will return CAA_FALSE.
 * In the Tx interrupt the transferred block should be returned to the higher
 * software layer with a call of the function CL2_MsgSendAckn.
*/

static CAA_BOOL CMD_Send(CL2I_BYTE byNet, CAA_HANDLE hBlock, CL2I_BYTE byPrio,
			 CAA_ERROR* peError)
{
#ifdef SOCKETCAN_ASYNC_SEND
	static SOCKET_TX_HANDLE socket_tx_handle[MAX_SOCKET_MSG];
	static int i_cnt;

	socket_tx_handle[i_cnt].byNet = byNet;
	socket_tx_handle[i_cnt].hBlock = hBlock;

	CAA_SET_RESULT(peError, CMD_NO_ERROR);
	if (mq_send(s_msg_queue, (char *)&socket_tx_handle[i_cnt],\
        sizeof(socket_tx_handle[i_cnt]), 0) == -1) {
		DEBUGP("mq_send: %s", strerror(errno));
        return CMD_SND_NOT_OK;
	}
	if (++i_cnt >= MAX_SOCKET_MSG) {
		i_cnt=0;
	}
#else
	CL2I_BLOCK* pBlock;
	int i;
		
	CAA_SET_RESULT(peError, CMD_NO_ERROR);
	pBlock = (CL2I_BLOCK*)CAL_CL2_MsgGetData(hBlock);
	if(!pBlock)
	{
		DEBUGP("pBlock == 0 ");
		return CMD_SND_NOT_OK;
	}
	if (pBlock->cobId.X.EID ) { /* Extended transmission */
		msg_write[byNet].can_id = ((pBlock->cobId.X.ID & CAN_EFF_MASK)  | CAN_EFF_FLAG);
	} 
	else { /* Standard transmission */
		msg_write[byNet].can_id = (pBlock->cobId.X.ID & CAN_SFF_MASK);
	}
	/* Remote Transmission Request add the RTR FLAG */
	if (pBlock->cobId.X.RTR) {
		msg_write[byNet].can_id = pBlock->cobId.X.ID | CAN_RTR_FLAG;
	}
	msg_write[byNet].can_dlc = pBlock->byLen.X.DLC;
	for (i = 0; i < msg_write[byNet].can_dlc; i++) {
		msg_write[byNet].data[i] = pBlock->byData[i];
	}

	if (write(s_fd_write[byNet], &msg_write[byNet], sizeof(msg_write[byNet])) < 0) 
	{
		DEBUGP("write %s%d: %s", s_interfacename, byNet, strerror(errno));
		return CMD_SND_NOT_OK;
	}
/* TX succeeded */
	if(s_bTimestamps)
	{
		RTS_SYSTIME time;
		CAL_SysTimeGetUs(&time);
		pBlock->dwTSP = (CL2I_DWORD)time;
	}
	else
		pBlock->dwTSP = 0;
	s_pInfo[s_byDriver[byNet]]->ctMessagesSend++;

/* Tell CL2 that everything is ok */
	CAL_CL2_MsgSendAckn(byNet, hBlock);
#endif
	return CMD_SND_OK;
}

/*
 * This function has to be called during the Rx interrupt handling. It copies
 * the message just received to the specified block buffer that is allocated
 * from the higher layer with CL2_MsgAlloc. CMD_Receive must also be called
 * also in case that CL2_MsgAlloc failed to allocate the block. So the chip
 * can be prepared for further receiving.
 */
static CAA_BOOL CMD_Receive(CL2I_BYTE byNet, CAA_HANDLE hBlock,
			    CAA_ERROR* peError)
{
	DEBUGP("I will never be called!");
	return CMD_NO_MORE_DATA;
}

/*
 * This function enables the higher software layers to request detailed
 * information on the amount of implementation concerning the driver.
 */
static CAA_ERROR CMD_GetInfo(CL2I_BYTE byNet, CMD_INFO* pInfo)
{
	if(pInfo)
	{
		DEBUGP("Info requested");
		pInfo->bySupport = CMD_SUPPORT_EXTCOBID | CMD_SUPPORT_RTRFRAME | CMD_SUPPORT_BUSALARM;
		pInfo->byMaxPrio = 1;

		memcpy((void*)pInfo, (void*)&cmdInfo, sizeof(CMD_INFO));
	}
	return CMD_NO_ERROR;
}

/*
 * This is the last call to the driver. All resources occupied by the driver
 * have to be released. The CAN bus chip must be set to a passive mode, so that
 * it does not influence the operations of an eventually connected CAN bus
 * network.
 */
static CAA_ERROR CMD_Dispose(CL2I_BYTE byNet)
{ /*Called by unregister of CL2. This will leave the chip in reset mode.*/
		
	DEBUGP("CMD_Dispose(%d)", byNet);
	global_stop = 1;

	if (s_hRxTask != RTS_INVALID_HANDLE && s_hRxTask != NULL) {
		pthread_cancel(s_hRxTask);
		s_hRxTask = RTS_INVALID_HANDLE;
	}
	return CMD_NO_ERROR;
}

/*
 * This function provides a method to identify the physical connector of a
 * logical network id (byNet) . For this purpose either a LED located at the
 * connector may flash or a specified test message may be sent periodically
 * via the concerned driver. The documentation of the driver must contain a
 * detailed description of the method used by the driver to get noticed from the
 * outside.
 */
static CAA_ERROR CMD_Identify(CL2I_BYTE byNet, CL2I_BYTE byCount)
{
	return CMD_NO_ERROR;
}

static CAA_HANDLE CMD_SetBlock(CL2I_BYTE byNet, CL2I_BYTE byIndex,
			       CAA_HANDLE hBlock, CAA_ERROR* peError)
{
	return CAA_hINVALID;
}

static CAA_ERROR CMD_SetCycle(CL2I_BYTE byNet, CL2I_BYTE byIndex,
			      CL2I_DWORD dwCycle)
{
	return CMD_NO_ERROR;
}

static CAA_ERROR CMD_SetMask(CL2I_BYTE byNet, CL2I_BYTE byIndex,
			     CL2I_DWORD dwValue, CL2I_DWORD dwMask)
{
	DEBUGP("SetMask called");
	return CMD_NO_ERROR;
}

/*
 * After the CAN Mini Driver has activated a Bus Alarm (e.g. Bus Off), this
 * function has to be called to force an initialization of the can chip. After
 * that the normal operation mode will be active again.
 */
static CAA_ERROR CMD_ResetAlarm(CL2I_BYTE byNet)
{
#ifndef DONT_RESET_CHIP_ON_BUSALARM
	char can_ifconfig[80];

	s_reset_current[byNet] = CAL_SysTimeGetMs();

	if (s_reset_last[byNet] != 0 && (s_reset_current[byNet] - s_reset_last[byNet]  < 1000) ) {
		return CMD_NO_ERROR;
	}

	s_reset_last[byNet] = s_reset_current[byNet];

	CAL_CMUtlsnprintf(can_ifconfig, sizeof(can_ifconfig), "ifconfig %s%d down", s_interfacename, (int)byNet);
	system(can_ifconfig);
	DEBUGP("%s", can_ifconfig);

	CAL_CMUtlsnprintf(can_ifconfig, sizeof(can_ifconfig), "ifconfig %s%d up", s_interfacename, (int)byNet);
	system(can_ifconfig);
	DEBUGP("%s", can_ifconfig);
#endif
	memset(s_pInfo[s_byDriver[byNet]], 0, sizeof(CL2I_INFO));
	s_pInfo[s_byDriver[byNet]]->byBusState = CL2_ACTIVE;

	return CMD_NO_ERROR;
}

/*
 * Identifies all existing CAN bus channels of a given type and registers them
 * with a specific network number in CAA_CanL2.lib. An error code will be
 * returned from "CL2_CMDRegister", if the specific network number (e.g. byNet)
 * is already occupied by another Can Mini Driver or if there are no more free
 * channels.
 */
int CAAFKT Socket_CanMiniDriver_Setup(void)
{
	CL2I_BYTE byDriver;
	CL2I_BYTE byNet;
	CL2I_BYTE byLastNet = 0;
	CAA_ERROR eError;

	for(byDriver=0; byDriver < Socket_NDRIVER; byDriver++) 
	{
		for(byNet=byLastNet; byNet < CL2_NNET; byNet++)
		{
			DEBUGP("Registering: %d", byNet);
			s_byDriver[byNet] = byDriver;
			s_byNet[byDriver] = byNet;

			/* A call to "CL2_CMDRegister" makes CAA_CanL2.lib
			 * calling the CAN Mini Driver function "CMD_Setup" */
			eError = CAL_CL2_CmdRegister(byNet,
						     &cmdInterface[0],
						     //Size of RX-Msg Pool
						     CL2_NRXMSG,
						     //BusState and Alarm Buffer
						     &s_pInfo[s_byDriver[byNet]]
				);

			if(eError == CL2_NO_ERROR)
			{
				byLastNet = byNet + 1;
				break;
			}
			else if(eError == CL2_INVALID_NETID)
			{
				s_pInfo[s_byDriver[byNet]] = CAA_pNULL;
				s_byDriver[byNet] = Socket_NDRIVER;
				s_byNet[byDriver] = Socket_NNET;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

int CAAFKT Socket_CanMiniDriver_Dispose(void)
{ /* Called by the EXIT3-hook. Is used to unregister from CL2 */
	CL2I_BYTE byDriver;
	CAA_ERROR eError;

	global_stop = 1;

	for(byDriver=0; byDriver < Socket_NDRIVER; byDriver++)
	{
		/*
		 * Each call of "CL2_CmdUnRegister" discharges into a call of
		 * the function "CMD_Dispose", by use of which the driver
		 * specific resources may be released
		 */
		eError = CAL_CL2_CmdUnRegister(s_byNet[byDriver]);
		s_byDriver[s_byNet[byDriver]] = Socket_NDRIVER;
		s_byNet[byDriver] = Socket_NNET;
	}

	return 0;
}
#endif /* CAALib */

