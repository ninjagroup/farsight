#ifndef __ENV_INFO_H__

#define __ENV_INFO_H__

#include "header.h"
#include "envLink.h"


typedef struct env_info_limit{
	float temperatureMAX;
	float temperatureMIN;
	float humidityMAX;
	float humidityMIN;
	float illuminationMAX;
	float illuminationMIN;
} env_info_limit;
//env_info header 
envLink envHeader;
//insert env_info suc = true fail = false 
bool env_insert(env_info env_info);
//select env_info 
env_info * env_select();

//insert env_info_limit suc = true fail = false  
bool env_limit_insert(env_info_limit env_info_limit);
//select env_info_limit 
env_info_limit env_limit_select();

#endif
