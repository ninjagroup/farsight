#ifndef __ENV_LINK_H__

#define __ENV_LINK_H__
#include "header.h"
typedef struct env_info{
	float temperature;
	float humidity;
	float illumination;
	int x;
	int y;
	int z;
	char insert_time[20];
} env_info; 


typedef struct envLink{
	env_info *next;
	int top;
}envLink; 
//init link 
void initLink(envLink *H);
//insert link
int insertLink(msgtype msg);
//get link count 
int linkCount(envLink *H);
//pop elem
env_info popLink();

#endif 
