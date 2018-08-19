#ifndef __ENV_LINK_H__

#define __ENV_LINK_H__

#include "header.h"
typedef struct env_info{
	float temperature;
	float humidity;
	float illusion;
	int x;
	int y;
	int z;
	char insert_time[20];
} env_info; 


typedef struct envLink{
	struct envLink *next;
	env_info envInfo;
	int top;
}envLink; 
//init link 
void initLink(envLink *H);
//insert link
int insertLink(envLink *H,msgtype msg);
//get link count 
int linkCount(envLink *H);
//pop elem
void popLink(envLink *H,env_info *);

#endif 
