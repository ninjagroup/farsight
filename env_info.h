#ifndef __ENV_INFO_H__

#define __ENV_INFO_H__

#include "header.h"
#include "envLink.h"


typedef struct env_info_limit{
	float temperatureMAX;
	float temperatureMIN;
	float humidityMAX;
	float humidityMIN;
	float illusionMAX;
	float illusionMIN;
} env_info_limit;

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
#endif
