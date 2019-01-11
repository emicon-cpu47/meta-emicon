/*****************************************************************************
*
*	Copyright:		© 3S - Smart Software Solutions GmbH, Kempten
*	Program:		Runtime System for the CoDeSys Soft-Plc
*	Module: 		Template component
*	Version:
*	Description:
******************************************************************************/

#include "CmpStd.h"
#include "CmpJitterDep.h"

//#define LINUX_MSQ

#ifdef LINUX_MSQ
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>
#include <errno.h>
#endif

#include <signal.h>

USE_STMT

#define PLOT_MAX_MSG 100

typedef struct {
    long count;
    int jitter;
    long cycletime;
} PLOTSTRUCT;

PLOTSTRUCT s_plot;
    
FILE *fp;
static int s_plotToFile = 1;
static int s_stop = 0;
static int s_cnt = 0;
static Task_Desc *s_pTask = NULL;
static APPLICATION *s_app = NULL;
static int s_firstPlot = 1;

RTS_HANDLE s_hAsyncFileWrite;

#ifdef LINUX_MSQ
static mqd_t s_msg_queue = (mqd_t)-1;
#else
RTS_HANDLE s_msg_queue = RTS_INVALID_HANDLE;
#endif

void printJitterResults();
void plotJitterResults();
void getJitterSummary();
void getTask();
static RTS_HANDLE s_hEventAfterWritingOutputs;

#ifndef RTS_COMPACT_MICRO

DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
/*	Used to exchange function pointers between component manager and components.
	Called at startup for each component.
	pInitStruct:			IN	Pointer to structure with:
		pfExportFunctions	OUT Pointer to function that exports component functions
		pfImportFunctions	OUT Pointer to function that imports functions from other components
		pfGetVersion		OUT Pointer to function to get component version
		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
		pfGetAPI			IN	Pointer to component mangager function to get a api function
		pfCallHook			IN	Pointer to component mangager function to call a hook function
	Return					ERR_OK if library could be initialized, else error code
*/
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = CreateInstance;
	pInitStruct->pfDeleteInstance = DeleteInstance;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

	/* Example to register a class, if it should be used under C++ from another component:
	if (pInitStruct->pfCMRegisterClass != NULL)
		pInitStruct->pfCMRegisterClass(COMPONENT_ID, CLASSID_CCmpJitter);
	*/
	return ERR_OK;
}

static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult)
{
#ifdef CPLUSPLUS
	if (cid == CLASSID_CCmpJitter)
	{
		CCmpJitter *pCCmpJitter = static_cast<CCmpJitter *>(new CCmpJitter());
		return (IBase*)pCCmpJitter->QueryInterface(pCCmpJitter, ITFID_IBase, pResult);
	}
#endif
	return NULL;
}

static RTS_RESULT CDECL DeleteInstance(IBase *pIBase)
{
#ifdef CPLUSPLUS
	pIBase->Release();
	return ERR_OK;
#else
	return ERR_NOTIMPLEMENTED;
#endif
}

static int CDECL ExportFunctions(void)
/*	Export function pointers as api */
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
/*	Get function pointers of other components */
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

void AsyncFileWrite(SYS_TASK_PARAM *ptp)
{
    RTS_RESULT Result;
    RTS_HANDLE hTask = ptp->hTask;
    CAL_SysTaskEnter(hTask);
    char plot[20];
    while (s_stop == 0)
    {
#ifdef LINUX_MSQ
        if (mq_receive(s_msg_queue, (char *)&s_plot, sizeof(PLOTSTRUCT), 0) != -1) {
#else
        if (CAL_SysMsgQRecv(s_msg_queue, (unsigned char *)&s_plot, sizeof(PLOTSTRUCT), MSGQ_TIMEOUT_INFINITE, &Result) != 0) {
#endif
            sprintf(plot, "%10ld %5d %10ld\n", s_plot.count, s_plot.jitter, s_plot.cycletime);
            fputs(plot, fp);
        }
    }
    CAL_SysTaskLeave(hTask);
	CAL_SysTaskEnd(hTask, 0);
}

/* Example for a Hook function */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{
	switch (ulHook)
	{
		case CH_INIT_SYSTEM:
			break;
		case CH_INIT:
			break;
		case CH_INIT2:
            if (s_plotToFile != 0)
            {
                fp = fopen("d1.dat", "w+");
            }
			break;
		case CH_INIT_TASKS:
            if (s_plotToFile != 0)
            {
                RTS_RESULT Result;
#ifdef LINUX_MSQ
                struct mq_attr attr;

                char szDummy[37] = "abcdefghijklmnopqrstuvwxyz1234567890";
                char szName[38];

                /* generate a unique name here for pszName */
                strfry(szDummy);
                sprintf(szName, "/%s", szDummy);
                
                /* initialize the message queue */
                attr.mq_flags = 0;
                attr.mq_maxmsg = 10;
                attr.mq_msgsize = sizeof(PLOTSTRUCT); /* size in bytes! */
#endif
                //create and start idle thread to write plot file
                s_hAsyncFileWrite = CAL_SysTaskCreate("AsyncFileWrite", AsyncFileWrite,\
                    NULL, TASKPRIO_IDLE, 1000, 0, 0, &Result);
                CAL_SysTaskResume(s_hAsyncFileWrite);
#ifdef LINUX_MSQ
                s_msg_queue = mq_open(szName, O_CREAT|O_EXCL|O_RDWR, S_IRWXU|S_IRWXG|S_IRWXO, &attr);
                if (s_msg_queue == -1)
                {
                    printf("\n\nmq_open failed: %s\n", strerror(errno));
                    if (errno == 38)
                        printf("Please enable POSIX Message Queues in your Kernel!\n");
                    exit(-1);
                }
#else
                s_msg_queue = CAL_SysMsgQCreate(PLOT_MAX_MSG, sizeof(PLOTSTRUCT), 0, &Result);
#endif
            }

			break;
		case CH_INIT_COMM:
            /*registering the callback this late means we will not get the jitter
              at startup*/
            getTask();
            if (s_plotToFile != 0)
            {
                s_hEventAfterWritingOutputs = CAL_EventOpen(EVT_AfterWritingOutputs, CMPID_CmpIecTask, NULL);
                CAL_EventRegisterCallbackFunction(s_hEventAfterWritingOutputs, plotJitterResults, 0);
            }
 			break;
		/* Cyclic */
		case CH_COMM_CYCLE:
            //getTask(); //better to do this when a download event occurs!
            printJitterResults();
			break;
		case CH_EXIT_COMM:
            getJitterSummary();
			break;
		case CH_EXIT_TASKS:
            s_stop = 1;
			plotJitterResults();
			CAL_SysTaskExit(s_hAsyncFileWrite, 2000);
			s_hAsyncFileWrite = RTS_INVALID_HANDLE;
			break;
		case CH_EXIT3:
			break;
		case CH_EXIT2:
			break;
		case CH_EXIT:
		{
            if (s_plotToFile != 0)
            {
                CAL_EventUnregisterCallbackFunction(s_hEventAfterWritingOutputs, plotJitterResults);
                fclose(fp);
            }
			EXIT_STMT;
			break;
		}
		case CH_EXIT_SYSTEM:
			break;
		default:
			break;
	}
	return ERR_OK;
}

void getTask()
{
    RTS_RESULT *pResult = NULL;

    //only get first app to keep things easy    
    s_app = CAL_AppGetFirstApp(pResult);

    if (pResult != ERR_OK)
        return;

    //only show first Task
    s_pTask = CAL_IecTaskGetFirst(s_app->szName, pResult);
    if (pResult != ERR_OK || s_pTask == (void *)-1)
        s_pTask = RTS_INVALID_HANDLE;
}

void printJitterResults()
{
    if (s_pTask == RTS_INVALID_HANDLE)
        return;
    
    if (s_pTask->pInfo->iJitterMax > 0)
    {
        printf("\rApplication: \"%s\" Task: \"%s\", Actual Jitter: %4d us"
        ", Max Jitter: %ld us, Interval %ld us", s_app->szName, s_pTask->pInfo->pszName,
        abs(s_pTask->pInfo->iJitter), (long int)s_pTask->pInfo->iJitterMax, (long int)s_pTask->pInfo->dwInterval);
        s_cnt = 0;
    }
}

void plotJitterResults()
{
    if (s_pTask == RTS_INVALID_HANDLE)
        return;
    if (s_firstPlot == 1)
    {
        s_pTask->pInfo->iJitterMax = 0;
        s_firstPlot = 0;
    }
        
    RTS_RESULT Result;
    s_plot.count = s_pTask->pInfo->dwCycleCount;
    s_plot.jitter = abs(s_pTask->pInfo->iJitter);
    s_plot.cycletime = s_pTask->pInfo->dwCycleTime;

#ifdef LINUX_MSQ
    mq_send(s_msg_queue, (char *)&s_plot, sizeof(PLOTSTRUCT), 0);
#else
    CAL_SysMsgQSend(s_msg_queue, (unsigned char *)&s_plot, sizeof(PLOTSTRUCT), 0, 0, &Result);
#endif

    if (s_pTask->pInfo->dwCycleCount >= 1000000) //prevent to make a too big file/ use too much RAM
        raise(2);
}

void getJitterSummary()
{
    RTS_RESULT *pResult = NULL;
    char name[80];
    strcpy(name, s_app->szName);

    if (s_pTask == RTS_INVALID_HANDLE)
        return;
        
    printf("\nSummary:\n"
        "========================================================================\n"
        "Application: \"%s\" Task: \"%s\", Max Jitter: %4d\n"
        "Priority: %d, Kind: %d, Cycles: %ld\n"
        "========================================================================\n",
        s_app->szName, s_pTask->pInfo->pszName,
        abs(s_pTask->pInfo->iJitterMax),
        s_pTask->pInfo->nPriority, s_pTask->pInfo->KindOfTask, (long int)s_pTask->pInfo->dwCycleCount);
        
    for(;;)
    {
        s_pTask = CAL_IecTaskGetNext(name, (RTS_HANDLE)s_pTask, pResult);
        if (s_pTask == (void *)-1)
            return;
        if (pResult != ERR_OK)
            return;

        printf(
            "========================================================================\n"
            "Application: \"%s\" Task: \"%s\", Max Jitter: %4d\n"
            "Priority: %d, Kind: %d, Cycles: %ld\n"
            "========================================================================\n",
            s_app->szName, s_pTask->pInfo->pszName,
            abs(s_pTask->pInfo->iJitterMax),
            s_pTask->pInfo->nPriority, s_pTask->pInfo->KindOfTask, (long int)s_pTask->pInfo->dwCycleCount);
    }
}
