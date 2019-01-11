/**
 * <name>RtsDisableOperations.c</name>
 * <description> 
 *	Template component to handle layer7 services
 *
 *	- CH_INIT3: call InitServiceHandler() from your component hook function
 *	- CH_EXIT3: call ExitServiceHandler() from your component hook function
 *	- TempServiceHandler(): Implements service routines
 * </description>
 *
 * <copyright>(c) 2003-2016 3S-Smart Software Solutions</copyright>
 */

#include "CmpStd.h"

#define SG_TEMP					0x0100
#define TEMP_GET_RTS_VERSION	0x12
#define TAG_TEMP_VERSION_TYPE	0x10

/* Example to read IP address */
#define TEMP_COMMAND_READ_IP	0x13
#define TEMP_TAG_IP_BYTES		0x11
#define TEMP_TAG_SUBNET_BYTES	0x12

/* Example read/set PLC time */
#define TEMP_COMMAND_READ_CLOCK	0x14
#define TEMP_COMMAND_SET_CLOCK	0x15
#define TEMP_TAG_RTC_TIME		0x11
#define TEMP_TAG_RTC_RESULT		0x12

/* Example to attach to UserManagement */
#ifndef CMPUSERMGR_NOTIMPLEMENTED
    #define USERDB_OBJECT_TEMPLATE              "Device.MyObject"
    #define USERDB_OBJECT_TEMPLATE_SERVICE1     USERDB_OBJECT_TEMPLATE ".__GET_RTS_VERSION"
    #define USERDB_OBJECT_TEMPLATE_SERVICE2     USERDB_OBJECT_TEMPLATE ".__COMMAND_READ_IP"
    #define USERDB_OBJECT_TEMPLATE_SERVICE3     USERDB_OBJECT_TEMPLATE ".__COMMAND_READ_CLOCK"
    #define USERDB_OBJECT_TEMPLATE_SERVICE4     USERDB_OBJECT_TEMPLATE ".__COMMAND_SET_CLOCK"    
#endif

static RTS_RESULT CDECL AddMyObjects(void);
static RTS_RESULT CDECL RemoveMyObjects(void);
static RTS_RESULT CDECL TempServiceHandler(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT pduSendBuffer);

static RTS_RESULT CDECL InitServiceHandler(void)
{
	/* Register layer 7 service handler */
	if (CHK_ServerRegisterServiceHandler)
		CAL_ServerRegisterServiceHandler(ADDVENDORID(CMP_VENDORID, SG_TEMP), TempServiceHandler);
    
	/* Example to attach to UserManagement */
	AddMyObjects();
	return ERR_OK;
}

static RTS_RESULT CDECL ExitServiceHandler(void)
{
	if (CHK_ServerUnRegisterServiceHandler)
		CAL_ServerUnRegisterServiceHandler(ADDVENDORID(CMP_VENDORID, SG_TEMP), TempServiceHandler);
    
	RemoveMyObjects();
	return ERR_OK;
}

/* Example to attach to UserManagement */
static RTS_RESULT CDECL AddMyObjects(void)
{
	RTS_RESULT result = ERR_OK;
#ifndef CMPUSERMGR_NOTIMPLEMENTED
	if (CHK_UserMgrObjectAdd)
	{
		RTS_RESULT res;
		CAL_UserMgrObjectAdd(USERDB_OBJECT_TEMPLATE, &res);
		result = RTS_GETRESULT(res, result);
		CAL_UserMgrObjectAdd(USERDB_OBJECT_TEMPLATE_SERVICE1, &res);
		result = RTS_GETRESULT(res, result);
		CAL_UserMgrObjectAdd(USERDB_OBJECT_TEMPLATE_SERVICE2, &res);
		result = RTS_GETRESULT(res, result);
		CAL_UserMgrObjectAdd(USERDB_OBJECT_TEMPLATE_SERVICE3, &res);
		result = RTS_GETRESULT(res, result);
		CAL_UserMgrObjectAdd(USERDB_OBJECT_TEMPLATE_SERVICE4, &res);
		result = RTS_GETRESULT(res, result);
	}

#endif    
	return result;
}

static RTS_RESULT CDECL RemoveMyObjects(void)
{
	RTS_RESULT result = ERR_OK;
#ifndef CMPUSERMGR_NOTIMPLEMENTED
	if (CHK_UserMgrObjectOpen && CHK_UserMgrObjectRemove && CHK_UserMgrObjectClose)
	{
		RTS_HANDLE hObject = CAL_UserMgrObjectOpen(USERDB_OBJECT_TEMPLATE, NULL);
		result = RTS_GETRESULT(CAL_UserMgrObjectRemove(hObject), result);
		(void)CAL_UserMgrObjectClose(hObject);

		hObject = CAL_UserMgrObjectOpen(USERDB_OBJECT_TEMPLATE_SERVICE1, NULL);
		result = RTS_GETRESULT(CAL_UserMgrObjectRemove(hObject), result);
		(void)CAL_UserMgrObjectClose(hObject);

		hObject = CAL_UserMgrObjectOpen(USERDB_OBJECT_TEMPLATE_SERVICE2, NULL);
		result = RTS_GETRESULT(CAL_UserMgrObjectRemove(hObject), result);
		(void)CAL_UserMgrObjectClose(hObject);

		hObject = CAL_UserMgrObjectOpen(USERDB_OBJECT_TEMPLATE_SERVICE3, NULL);
		result = RTS_GETRESULT(CAL_UserMgrObjectRemove(hObject), result);
		(void)CAL_UserMgrObjectClose(hObject);

		hObject = CAL_UserMgrObjectOpen(USERDB_OBJECT_TEMPLATE_SERVICE4, NULL);
		result = RTS_GETRESULT(CAL_UserMgrObjectRemove(hObject), result);
		(void)CAL_UserMgrObjectClose(hObject);
	}
#endif   
	return result;
}

static RTS_RESULT CDECL HasAccessRights(char *pszObject, RTS_UI32 ulRequestedRights, RTS_UI32 ulSessionId, BINTAGWRITER *pWriter)
{
#ifndef CMPUSERMGR_NOTIMPLEMENTED
	if (CHK_UserMgrHasAccessRights && CHK_UserMgrAddOnlineAccessError)
	{
		RTS_RESULT result = CAL_UserMgrHasAccessRights(pszObject, ulSessionId, ulRequestedRights);
		if (result != ERR_OK)
		{
			CAL_UserMgrAddOnlineAccessError(pWriter, result, pszObject, ulRequestedRights, ulSessionId);
			return result;
		}
	}
#endif
	return ERR_OK;
}


static RTS_RESULT CDECL TempServiceHandler(RTS_UI32 ulChannelId, HEADER_TAG *pHeaderTag, PROTOCOL_DATA_UNIT pduData, PROTOCOL_DATA_UNIT pduSendBuffer)
{
	int nResult = ERR_OK;
	RTS_I32 nElemType;

	unsigned short usService = pHeaderTag->usService;
	unsigned long ulServiceLength = pHeaderTag->ulServiceLength;
	unsigned char *pData = (unsigned char *)pduData.pData;

	if (pduData.ulCount < ulServiceLength)
		return ERR_PARAMETER;

	switch (usService)
	{
		case TEMP_GET_RTS_VERSION:
		{
			BINTAGREADER reader;
			BINTAGWRITER writer;
			RTS_UI32 ulTagId;
			unsigned short usVersionType = 0xFFFF;
			unsigned char *pucType;
			RTS_UI32 ulSize;

			CAL_BTagReaderInit(&reader, pData, ulServiceLength);
			CAL_BTagWriterInit(&writer, (unsigned char *)pduSendBuffer.pData, pduSendBuffer.ulCount);

			/* Example to attach to UserManagement */
			/* Check specified access right (here: USERDB_RIGHT_VIEW) of the user (represented by its online SessionID) on the specified object! */
			nResult = HasAccessRights(USERDB_OBJECT_TEMPLATE_SERVICE1, USERDB_RIGHT_VIEW, pHeaderTag->ulSessionID, &writer);
			/* If no appropriate access right on the object is configured, deny online access and reply an error! */
			if (nResult != ERR_OK)
			{
				CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
				return ERR_OK;
			}

			for (nResult = CAL_BTagReaderMoveNext(&reader, &nElemType); nElemType == BTAG_ET_STARTTAG; nResult = CAL_BTagReaderMoveNext(&reader, &nElemType))
			{
				CAL_BTagReaderGetTagId(&reader, &ulTagId); /* (TAG_APPL_APPLNAME) toplevel-tag*/

				switch(ulTagId)
				{
					case TAG_TEMP_VERSION_TYPE:
					{
						if(CAL_BTagReaderGetContent(&reader, &pucType, &ulSize) != ERR_OK)
							return ERR_PARAMETER;
						if(ulSize != 2)
							return ERR_PARAMETER;
						usVersionType = *(unsigned short *)pucType;
					}
					default:
						CAL_BTagReaderSkipContent(&reader); 
						break;
				}
				CAL_BTagReaderSkipContent(&reader);
				CAL_BTagReaderMoveNext(&reader, &nElemType); /* consume end-tag */
			}			

			CAL_BTagWriterStartTag(&writer, 0, align_40, 0);
			switch (usVersionType)
			{
				case 1:	/* as int */
				{
					int iVersion = 0x00000104;
					CAL_BTagWriterAppendBlob(&writer, (unsigned char*)&iVersion, sizeof(iVersion));
					break;
				}
				case 2:	/* as string */
				{
					CAL_BTagWriterAppendBlob(&writer, (unsigned char*)RTS_VERSION_STRING, sizeof(RTS_VERSION_STRING));
					break;
				}
				default:
					return ERR_PARAMETER;
			}
			CAL_BTagWriterAppendFillBytes(&writer, 0, align_40);
			CAL_BTagWriterEndTag(&writer, 0);						
			CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
			CAL_ServerFinishRequest(ulChannelId, pduSendBuffer);
			return ERR_OK;
		}
		case TEMP_COMMAND_READ_IP:
		{
			BINTAGWRITER writer;
			RTS_UI32 example_ip = 0x4865A8C0;			/* 192.168.101.72 in network byte order (BIG ENDIAN) */
			RTS_UI32 example_subnet = 0x00FFFFFF;		/* 255.255.255.0 in network byte order (BIG ENDIAN) */

			CAL_BTagWriterInit(&writer, (unsigned char *)pduSendBuffer.pData, pduSendBuffer.ulCount);

			/* Example to attach to UserManagement */
			/* Check specified access right (here: USERDB_RIGHT_VIEW) of the user (represented by its online SessionID) on the specified object! */
			nResult = HasAccessRights(USERDB_OBJECT_TEMPLATE_SERVICE2, USERDB_RIGHT_VIEW, pHeaderTag->ulSessionID, &writer);
			/* If no appropriate access right on the object is configured, deny online access and reply an error! */
			if (nResult != ERR_OK)
			{
				CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
				return ERR_OK;
			}

			CAL_BTagWriterStartTag(&writer, TEMP_TAG_IP_BYTES, align_40, 0);
			CAL_BTagWriterAppendBlob(&writer, (unsigned char*)&example_ip , sizeof(RTS_UI32));
			CAL_BTagWriterEndTag(&writer, TEMP_TAG_IP_BYTES);	

			CAL_BTagWriterStartTag(&writer, TEMP_TAG_SUBNET_BYTES, align_40, 0);
			CAL_BTagWriterAppendBlob(&writer, (unsigned char*)&example_subnet , sizeof(RTS_UI32));
			CAL_BTagWriterEndTag(&writer, TEMP_TAG_SUBNET_BYTES);	

			CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
			CAL_ServerFinishRequest(ulChannelId, pduSendBuffer);
			return ERR_OK;
		}
		case TEMP_COMMAND_READ_CLOCK:
		{
			BINTAGWRITER writer;
			RTS_UI32 uiRtc = 0;	
			RTS_RESULT nGetTimeResult = ERR_FAILED;
			
			CAL_BTagWriterInit(&writer, (unsigned char *)pduSendBuffer.pData, pduSendBuffer.ulCount);

			/* Example to attach to UserManagement */
			/* Check specified access right (here: USERDB_RIGHT_VIEW) of the user (represented by its online SessionID) on the specified object! */
			nResult = HasAccessRights(USERDB_OBJECT_TEMPLATE_SERVICE3, USERDB_RIGHT_VIEW, pHeaderTag->ulSessionID, &writer);
			/* If no appropriate access right on the object is configured, deny online access and reply an error! */
			if (nResult != ERR_OK)
			{
				CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
				return ERR_OK;
			}

			if (CHK_SysTimeRtcGet)
				uiRtc = CAL_SysTimeRtcGet(&nGetTimeResult);
			else
				nGetTimeResult = ERR_NOTIMPLEMENTED;

			CAL_BTagWriterStartTag(&writer, TEMP_TAG_RTC_RESULT, align_40, 0);
			CAL_BTagWriterAppendBlob(&writer, (unsigned char*)&nGetTimeResult, sizeof(RTS_UI32));
			CAL_BTagWriterEndTag(&writer, TEMP_TAG_RTC_RESULT);	

			if (nGetTimeResult == ERR_OK)
			{
				CAL_BTagWriterStartTag(&writer, TEMP_TAG_RTC_TIME, align_40, 0);
				CAL_BTagWriterAppendBlob(&writer, (unsigned char*)&uiRtc , sizeof(RTS_UI32));
				CAL_BTagWriterEndTag(&writer, TEMP_TAG_RTC_TIME);	
			}

			CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
			CAL_ServerFinishRequest(ulChannelId, pduSendBuffer);
			return ERR_OK;
		}	
		case TEMP_COMMAND_SET_CLOCK:
		{
			BINTAGREADER reader;
			BINTAGWRITER writer;
			RTS_UI32 ulTagId;
			RTS_UI32 uiRtc = 0;
			unsigned char *pucType;
			RTS_UI32 ulSize;
			RTS_RESULT nClockResult = ERR_FAILED;

			CAL_BTagReaderInit(&reader, pData, ulServiceLength);
			CAL_BTagWriterInit(&writer, (unsigned char *)pduSendBuffer.pData, pduSendBuffer.ulCount);

			/* Example to attach to UserManagement */
			/* Check specified access right (here: USERDB_RIGHT_MODIFY) of the user (represented by its online SessionID) on the specified object! */
			nResult = HasAccessRights(USERDB_OBJECT_TEMPLATE_SERVICE4, USERDB_RIGHT_MODIFY, pHeaderTag->ulSessionID, &writer);
			/* If no appropriate access right on the object is configured, deny online access and reply an error! */
			if (nResult != ERR_OK)
			{
				CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
				return ERR_OK;
			}

			for (nResult = CAL_BTagReaderMoveNext(&reader, &nElemType); nElemType == BTAG_ET_STARTTAG; nResult = CAL_BTagReaderMoveNext(&reader, &nElemType))
			{
				CAL_BTagReaderGetTagId(&reader, &ulTagId); /* toplevel-tag*/

				switch(ulTagId)
				{
					case TEMP_TAG_RTC_TIME:
					{
						if(CAL_BTagReaderGetContent(&reader, &pucType, &ulSize) != ERR_OK)
						{
							nClockResult = ERR_PARAMETER;
							break;
						}

						if(ulSize != 4)
						{
							nClockResult = ERR_PARAMETER;
							break;
						}

						uiRtc = *(unsigned int *)pucType;

						if (CHK_SysTimeRtcSet)
							nClockResult = CAL_SysTimeRtcSet(uiRtc);
						else
							nClockResult = ERR_NOTIMPLEMENTED;

						break;
					}
					default:
						CAL_BTagReaderSkipContent(&reader); 
						break;
				}

				CAL_BTagReaderSkipContent(&reader);
				CAL_BTagReaderMoveNext(&reader, &nElemType); /* consume end-tag */
			}
			
			CAL_BTagWriterStartTag(&writer, TEMP_TAG_RTC_RESULT, align_40, 0);
			CAL_BTagWriterAppendBlob(&writer, (unsigned char*)&nClockResult , sizeof(RTS_UI32));
			CAL_BTagWriterEndTag(&writer, TEMP_TAG_RTC_RESULT);	
			CAL_BTagWriterFinish(&writer, (unsigned char**)&(pduSendBuffer.pData), &pduSendBuffer.ulCount);
			CAL_ServerFinishRequest(ulChannelId, pduSendBuffer);
			return ERR_OK;
		}
		default:
			break;
	}
	return ERR_FAILED;
}
