// 
//	CP56Time2a IEC 60870-5-104 time data type implementation 
// 
#pragma once 
#include <time.h> 
 
class CP56Time2a 
{ 
private: 
	SYSTEMTIME		stime; 
	bool			valid; 
	bool			genuine; 
	bool			summer; 
 
public: 
	CP56Time2a(unsigned char *data); 
	~CP56Time2a(void); 
 
	void GetTimeString(char *buf, size_t size); 
	FILETIME _GetFileTime(void); 
	SYSTEMTIME _GetSystemTime(void); 
	 
	void ActualTimeToCP56Time(unsigned char *data); 
 
	void TimeToCP56Time2a(FILETIME *ft, unsigned char *data); 
	void TimeToCP56Time2a(SYSTEMTIME *st, unsigned char *data); 
 
	void CP56Time2aToTime(unsigned char *data, FILETIME *ft); 
	void CP56Time2aToTime(unsigned char *data, SYSTEMTIME *st); 
}; 