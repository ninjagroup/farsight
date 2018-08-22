#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cgic.h"
#include <sys/ipc.h>
#include <sys/sem.h>

typedef struct msgc{
	char type;
	char msgcont[150];
}msgc;

typedef struct msgtype{
	long msgtype;
	msgc msgc;
}msgtype;

int cgiMain(int argc,char * argv[])
{
	msgtype msg;
	int msgid;
	int	msgkey = ftok("/home/linux/hqyj.bak/hqyj/README.md",'n');
	if((msgid = msgget(msgkey,IPC_CREAT|0777)) < 0)
	{
		perror("msgget error!");
		return -1;
	}
	int i;
	cgiFormInteger("type",&i,0);
	printf("the i:%d\n",i);
	//send command 
	int pid = getpid();
	msg.msgtype = 1002;
	msg.msgc.type = 2;

	sprintf(msg.msgc.msgcont,"%d",i);
	msgsnd(msgid,&msg,sizeof(msgtype),0);

	cgiHeaderContentType("text/html");
}
