#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cgic.h"
#include <sys/types.h>
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

int cgiMain(int argc,const char * argv[])
{
	int shmid;
	int key;
	msgtype * msg;
	key = ftok("/home/linux/hqyj.bak/hqyj/README.md",'a');	
	shmid = shmget(key,sizeof(msgtype),IPC_CREAT|0777);
	msg = (msgtype *)shmat(shmid,NULL,0);
	cgiHeaderContentType("text/html");
	fprintf(cgiOut,(msg->msgc).msgcont);
}
