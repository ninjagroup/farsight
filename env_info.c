#include "env_info.h"

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
	//msgcont pid 
	//msg queue msgtype pid cont temperature#humid#illusion 
	
	
}

bool env_insert(env_info envInfo)
{
	return true;
}

bool env_insert_msg(msgtype msg)
{
	return true;
}
bool env_limit_insert(msgtype msg)
{
	//msgcont temMax#temMin#huMax#huMin#illMax#illuMin 
	return true; 
}

void env_limit_select_msg()
{
	//msgcont pid 
	//msg queue msgtype pid cont temMax#temMin#huMax#huMin#illuMax#illuMin

}
void env_set(msgtype msg)
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

}
