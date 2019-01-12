//   
//  CP56Time2a IEC 60870-5-104 time data type implementation   
//   
#include "StdAfx.h"   
#include "CP56Time2a.h"   
   
//   
//  Constructor: decode CP56Time2a data   
//   
CP56Time2a::CP56Time2a(unsigned char *data)   
{   
    CP56Time2aToTime(data, &stime);   
}   
   
CP56Time2a::~CP56Time2a(void)   
{   
}   
   
//   
//  return time string of CP56Time2a decoded   
//   
void CP56Time2a::GetTimeString(char *buf, size_t size)   
{   
    sprintf_s(buf, size,"%2.2d/%2.2d/%4.4d %2.2d:%2.2d:%2.2d.%3.3d", stime.wDay,   
        stime.wMonth, stime.wYear, stime.wHour, stime.wMinute,   
        stime.wSecond, stime.wMilliseconds);   
    return;   
}   
   
//   
//  return SYSTEMTIME structure of CP56Time2a decoded   
//   
SYSTEMTIME CP56Time2a::_GetSystemTime(void)   
{   
    return stime;   
}   
   
//   
//  return FILETIME structure of CP56Time2a decoded   
//   
FILETIME CP56Time2a::_GetFileTime(void)   
{   
    FILETIME ft;   
    SystemTimeToFileTime(&stime, &ft);   
    return ft;   
}   
   
//   
//  return CP56Time2a data of actual time.   
//   
void CP56Time2a::ActualTimeToCP56Time(unsigned char *data)   
{   
    SYSTEMTIME st;   
    GetSystemTime(&st);   
    TimeToCP56Time2a(&st, data);   
}   
   
//   
//  convert FILETIME to CP56Time2a   
//   
void CP56Time2a::TimeToCP56Time2a(FILETIME *ft, unsigned char *data)   
{   
    SYSTEMTIME st;   
    FileTimeToSystemTime(ft, &st);   
    TimeToCP56Time2a(&st, data);   
}   
   
//   
//  convert SYSTEMTIME to CP56Time2a   
//   
void CP56Time2a::TimeToCP56Time2a(SYSTEMTIME *st, unsigned char *data)   
{   
    unsigned int m;   
    m = st->wMilliseconds + 1000 * st->wSecond;   
    data[0] = m & 0xFF;   
    data[1] = (m & 0xFF00)>>8;   
    data[2] = st->wMinute & 0x00FF;  // add valid flag and genuine flag   
    data[3] = st->wHour & 0x00FF;    // add summer flag   
    data[4] = ((st->wDayOfWeek%7)&0x03)<<5 | (st->wDay&0x1F);   
    data[5] = st->wMonth & 0x0F;   
    data[6] = st->wYear - 2000;   
}   
   
//   
//  convert CP56Time2a to FILETIME   
//   
void CP56Time2a::CP56Time2aToTime(unsigned char *data, FILETIME *ft)   
{   
    SYSTEMTIME st;   
    CP56Time2aToTime(data, &st);   
    SystemTimeToFileTime(&st, ft);   
}   
   
//   
//  convert CP56Time2a to SYSTEMTIME   
//   
void CP56Time2a::CP56Time2aToTime(unsigned char *data, SYSTEMTIME *st)   
{   
    unsigned int mili = data[0] | data[1]<<8;   
    st->wSecond      = mili / 1000;   
    st->wMilliseconds = mili - st->wSecond*1000;   
   
    if(data[2] & 0x40)   
        genuine = true;   
    else   
        genuine = false;   
   
    if(data[2] & 0x80)   
        valid = true;   
    else   
        valid = false;   
   
    st->wMinute      = data[2] & 0x3F;;   
    st->wHour        = data[3] & 0x1F;   
   
    if(data[3] & 0x80)   
        summer = true;   
    else   
        summer = false;   
       
    st->wDay     = data[4] & 0x1F;   
    st->wDayOfWeek = (data[4] & 0xE0 ) >> 5;   
    if(st->wDayOfWeek)   // if zero day of week not used.   
        st->wDayOfWeek = (st->wDayOfWeek + 1)%7;   
    st->wMonth       = data[5] & 0x0F;   
    st->wYear        = 2000 + (data[6] & 0x7F);   
}  

 
