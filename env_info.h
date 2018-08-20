#ifndef __ENV_INFO_H__

#define __ENV_INFO_H__

#include "header.h"
#include "envLink.h"

#define DATABASE "ninja.db"
#define N 128

typedef struct env_info_limit{
	float temperatureMAX;
	float temperatureMIN;
	float humidityMAX;
	float humidityMIN;
	float illusionMAX;
	float illusionMIN;
} env_info_limit;

void env_init(sqlite3 **db);

bool env_insert(sqlite3 *db,env_info envInfo);
//insert env_info suc = true fail = false 
bool env_insert_msg(sqlite3 *db,msgtype msg);
//select env_info select data push into msg queue
void env_select(sqlite3 *db);

//insert env_info_limit suc = true fail = false  
bool env_limit_insert(sqlite3 *,msgtype);
//select when startup
env_info_limit env_limit_select(sqlite3 *db);
//select env_info_limit push into msgqueue
void env_limit_select_msg(sqlite3 *db);
//env choice 
void env_set(sqlite3 *,msgtype);

#endif
