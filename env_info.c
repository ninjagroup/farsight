#include "env_info.h"


//
//
void env_init(sqlite3 **db)
{
	char *errmsg;

	if(sqlite3_open(DATABASE,db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(*db));
		exit(-1);
	}

	if(sqlite3_exec(*db,"create table env(id integer primary key autoincrement,temperature real,humidity real,illusion real,x integer \
		,y integer,z integer,insertdate text)",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else
	{
		printf("The env has created successfully\n");
	}

	if(sqlite3_exec(*db,"create table envlimit(temperatureMAX real,temperatureMIN real,\
		humidityMAX real,humidityMIN real,illusionMAX real,illusionMIN real)",NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else
	{
		printf("The envlimit has created successfully\n");
		if(sqlite3_exec(*db,"insert into envlimit(temperatureMAX,temperatureMIN,\
			humidityMAX,humidityMIN,illusionMAX,illusionMIN) values(40,10,40,10,40,10)",NULL,NULL,&errmsg) != SQLITE_OK)
		{
			printf("%s\n",errmsg);
		}
	}
}

int callback_limit(void *arg,int ncol,char **text,char **name)
{
	int i = 0;
	env_info_limit *env_limit = ((env_info_limit *)arg);
	env_limit->temperatureMAX = atof((text[i]));
	env_limit->temperatureMIN = atof((text[++i]));
	env_limit->humidityMAX = atof((text[++i]));
	env_limit->humidityMIN = atof((text[++i]));
	env_limit->illusionMAX = atof((text[++i]));
	env_limit->illusionMIN = atof((text[++i]));
	return 1;
}


env_info_limit env_limit_select(sqlite3 *db)
{
	char *errmsg;
	char sql[100] = "select * from envlimit limit 1";
	env_info_limit env_limit;
/*

	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		exit(-1);
	}
*/
	if(sqlite3_exec(db,sql,callback_limit,&env_limit,&errmsg) != SQLITE_OK)
	{
		printf("%s\n",errmsg);
	}
	else 
	{
		printf("someone selecting from envlimit!\n");
	}
//	sqlite3_close(db);
	return env_limit;
}
void env_select(sqlite3 *db,msgtype msg,int recv_key)
{
	char *errmsg;
	char sql[150];
	int nRow,nColumn;
	int result;
	char **dbResult; 
	msgtype msg_snd;
	int i,j;
	int index;
	int pid = atoi(msg.msgc.msgcont);
	msg_snd.msgtype = pid;


	//make ftok l
	int msgid = msgget(recv_key,0666);
	strcpy(sql,"select * from env");
	result = sqlite3_get_table( db, sql, &dbResult, &nRow, &nColumn, &errmsg );
	index = nColumn;
	msg_snd.msgc.type = 1;	
	struct msqid_ds md;

	if(result == SQLITE_OK)
	{
		for(i = 0;i < nRow;i++)
		{
			memset(msg_snd.msgc.msgcont,'\0',strlen(msg_snd.msgc.msgcont));
			sprintf(msg_snd.msgc.msgcont,"%s<tr>",msg_snd.msgc.msgcont);
			for(j = 0;j < nColumn;j++)
			{
				sprintf(msg_snd.msgc.msgcont,"<td>%s",msg_snd.msgc.msgcont);
				if(dbResult[index] == NULL)
				{
					strcat(msg_snd.msgc.msgcont,"0");

				}else
				{
					strcat(msg_snd.msgc.msgcont,dbResult[index]);
				}
					sprintf(msg_snd.msgc.msgcont,"%s</td>",msg_snd.msgc.msgcont);

				index++;
			}
		
			sprintf(msg_snd.msgc.msgcont,"%s</tr>",msg_snd.msgc.msgcont);
			msgctl(msgid,IPC_STAT,&md);
			if(md.msg_qnum < 50){
			if(msgsnd(msgid,&msg_snd,sizeof(msgtype),0) < 0)
			{
				perror("env select send part error\n");
			}
			}
			else{
				usleep(100);
			}
			memset(msg_snd.msgc.msgcont,'\0',strlen(msg_snd.msgc.msgcont));
		}
		strcat(msg_snd.msgc.msgcont,"END");
		//send end symbol 
		msgsnd(msgid,&msg_snd,sizeof(msgtype),0);
	}
	sqlite3_free_table(dbResult);
}


bool env_insert(sqlite3 *db,env_info envInfo)
{
	char sql[128];
	char *errmsg;
	/*
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		return false;
	}
	*/
	sprintf(sql, "insert into env(temperature,illusion,humidity,insertdate) values(%f,%f,%f,'%s')",envInfo.temperature,\
			envInfo.illusion,envInfo.humidity,envInfo.insert_time);
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return false;
	}
//	sqlite3_close(db);
	return true;
}

bool env_insert_msg(sqlite3 *db,msgtype msg)
{
//msgcont  temperature#illusion#humidity#changetime
	float temperature;
	float illusion;
	float humidity;
	char insertdate[20];
	char sql[100];
	char * errmsg;

	sscanf(msg.msgc.msgcont,"%f#%f#%f#%s",&temperature,&illusion,&humidity,insertdate);
	sprintf(sql,"insert into env(temperature,illusion,humidity,insertdate) values(%f,%f,%f,%s)",\
			temperature,illusion,humidity,insertdate);

/*
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		return false;
	}
*/
	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
	}
	else 
	{
		printf("insert into env msg mode\n");
	}


	return true;
}

bool env_limit_insert(sqlite3 *db,msgtype msg)
{
	char sql[100];
	char *errmsg;
	float temMax;
	float temMin;
	float huMax;
	float huMin;
	float illMax;
	float illMin;
	
	if(sqlite3_open(DATABASE,&db) != SQLITE_OK)
	{
		printf("error : %s\n", sqlite3_errmsg(db));
		return false;
	}
	//msgcont temMax#temMin#huMax#huMin#illMax#illuMin 
	sscanf(msg.msgc.msgcont,"%f#%f#%f#%f#%f#%f",&temMax,&temMin,&huMax,\
			&huMin,&illMax,&illMin);
	sprintf(sql,"insert into envlimit(temperaturMAX,temperatureMIN,\
		humidityMAX,humidityMIN,illusionMAX,illusionMIN) values(\
			%f,%f,%f,%f,%f,%f)",temMax,temMin,huMax,huMin,illMax,illMin);

	if(sqlite3_exec(db, sql, NULL, NULL, &errmsg) != SQLITE_OK)
	{
		printf("%s\n", errmsg);
		return false;
	}
	else 
	{
		printf("insert into env limit msg mode\n");
	}

	return true; 
}

void env_limit_select_msg(sqlite3 *db)
{
	//msgcont pid 
	//msg queue msgtype pid cont temMax#temMin#huMax#huMin#illuMax#illuMin
	

}
void env_set(sqlite3 *db,msgtype msg,int msg_recv)
{
	if(msg.msgtype == 1001)
	{
		if(msg.msgc.type == 2)
		{
			env_limit_select_msg(db);
		}
	}else if(msg.msgtype == 1004)
	{
		printf("here?\n");
		printf("%d,%s\n",msg.msgc.type,msg.msgc.msgcont);
		if(msg.msgc.type == 1)
		{
			env_insert_msg(db,msg);
		}else if(msg.msgc.type == 2)
		{
			printf("is me?\n");
			env_select(db,msg,msg_recv);
		}
	}
}
