#include "envLink.h"

void initLink(envLink *H)
{
	H = (envLink *)malloc(sizeof(envLink));
	if(H == NULL)
	{
		perror("fail to init link!");
	}
	H->next = NULL;
}

int insertLink(envLink *H,msgtype msg)
{
	env_info envInfo; 
	//msg temperature, illusion,humidity,time_str 
	sscanf(msg.msgcont,"#%f#%f#%f#%s",&(envInfo.temperature),&(envInfo.illusion)\
			,&(envInfo.humidity),envInfo.insert_time);
	envInfo.x = 0;
	envInfo.y = 0;
	envInfo.z = 0;
	//insert 
	envLink *envElement = (envLink *)malloc(sizeof(envLink));	
	envElement->envInfo = envInfo;
	envElement->next = H->next; 
	H->next = envElement;
	H->top++;
	return H->top + 1;
}

int linkCount(envLink *H)
{
	return H->top + 1;
}

void popLink(envLink *H,env_info *envInfo)
{
	env_info envinfo; 
	envLink *p;
	if(H->top != -1)
	{
		p = H->next;
		envinfo = p->envInfo;
		*envInfo = envinfo;
		free(p);
		H->next = H->next->next;
		H->top--;
	}
}
