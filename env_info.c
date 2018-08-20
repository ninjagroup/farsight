#include "env_info.h"

sqlite3 *db;

//
//
void env_init()
{
	char *errmsg;
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}

	if(sqlite3_exec(db,"create table envtable(humiture int)",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else
	{
		printf("The table has created successfully\n");
	}

	if(sqlite3_exec(db,"create table boundtable(upvalue int,downvalue int)",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else
	{
		printf("The table has created successfully\n");
	}
}

env_info_limit env_limit_select()
{
	env_info_limit limit_info;
	limit_info.temperatureMAX = 10;
	limit_info.temperatureMIN = 5;
	limit_info.illusionMAX = 10;
	limit_info.illusionMIN = 5;
	limit_info.humidityMAX = 10;
	limit_info.humidityMIN = 5;
	return limit_info;
}

void env_select()
{
	char sqlstr[128],*errmsg;

	strcpy(sqlstr,"select * from envtable limit 15");

	if(sqlite3_exec(db,sqlstr,history_callback,/*传参*/,&errmsg) != SQLITE_OK)
	{
		printf("error : %s\n,errmsg");
	}
	//msgcont pid 
	//msg queue msgtype pid cont temperature#humid#illusion 
	
}

int history_callback(void *arg,int f_num,char ** f_value,char ** f_name)
{
	sprintf(msg.data, "%s : %s", f_value[1], f_value[2]);
	//发送语句
	
	return 0;
}

bool env_insert(env_info envInfo)
{
	char sql[N] = {};
	char *errmsg;
	sprintf(sql, "insert into envtable values(%d)", env_info);

	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else 
	{
		printf("The data has inserted successfully\n");
	}
	return true;
}

bool env_insert_msg(msgtype msg)
{
	return true;
}

//修改上下限(修改之前先删除后增加)
bool env_limit_insert(msgtype msg)
{
	char sql[N] = {};
	char *errmsg;
	sprintf(sql,"delete from boundtable where id = %d",env_info_limit.id);
	if(sqlite3_exec(db,sql,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}

	//默认id 为1
	sprintf(sql,"insert into boundtable values(%d,%f,%f,%f,%f,%f,%f)",env_info_limit.id,env_info_limit.humidityMAX,env_info_limit.humidityMIN,env_info_limit.illusionMAX,env_info_limit.illusionMIN);
  	
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else 
	{
		printf("The data has inserted successfully\n");
	}
	
	//msgcont temMax#temMin#huMax#huMin#illMax#illuMin 
	return true; 
}

void env_limit_select_msg()
{
	//msgcont pid 
	//msg queue msgtype pid cont temMax#temMin#huMax#huMin#illuMax#illuMin

}
void env_set(msgtype msg,env_Link *H)
{
	while(H->next != NULL)
	{
		if(msg.msgtype == 1001)
		{
			if(msg.type == 2)
			{
				env_limit_select_msg();
			}
		}else if(msg.msgtype == 1004)
		{
			if(msg.type == 1)
			{
				env_insert_msg(msg);
			}else if(msg.type == 2)
			{
				env_select();
			}
		}
		H = H->next;
	}

}
