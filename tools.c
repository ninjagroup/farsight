#include "tools.h"

void getTime(char *time_str)
{
	time_t now;
	struct tm * l_time;
	now = time(NULL);
	l_time = localtime(&now);
	sprintf(time_str,"%4d-%02d-%02d %02d:%02d:%02d",l_time->tm_year + 1900\
			,l_time->tm_mon + 1,l_time->tm_mday,l_time->tm_hour,l_time->tm_min,l_time->tm_sec);
	return;
}
