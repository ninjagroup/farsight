#ifndef __ENV_INFO_H__

#define __ENV_INFO_H__

#include "header.h"
#include "envLink.h"

#define DATABASE "my.db"
#define N 128

extern env_Link *envHeader;
typedef struct env_info_limit{
	int 	id;
	float temperatureMAX;
	float temperatureMIN;
	float humidityMAX;
	float humidityMIN;
	float illusionMAX;
	float illusionMIN;
} env_info_limit;

void env_init();

bool env_insert(env_info envInfo);
//insert env_info suc = true fail = false 
bool env_insert_msg(msgtype msg);
//select env_info select data push into msg queue
void env_select();

//insert env_info_limit suc = true fail = false  
bool env_limit_insert(msgtype);
//select when startup
env_info_limit env_limit_select();
//select env_info_limit push into msgqueue
void env_limit_select_msg();
//env choice 
void env_set(msgtype);

int history_callback(void *arg,int f_num,char ** f_value,char ** f_name);
#endif
