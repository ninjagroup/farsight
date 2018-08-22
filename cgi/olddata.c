#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cgic.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct msgc{
	char type;
	char msgcont[150];
}msgc;

typedef struct msgtype{
	long msgtype;
	msgc msgc;
}msgtype;

int main(int argc, const char *argv[])
{
	int msgid,msgid_recv;
	key_t msgkey,msgkey_recv;
	msgtype msg,msg_rcv; 
	msgkey = ftok("/home/linux/hqyj.bak/hqyj/README.md",'n');
	if((msgid = msgget(msgkey,IPC_CREAT|0777)) < 0)
	{
		perror("msgget error!");
		return -1;
	}

	//send command 
	int pid = getpid();
	msg.msgtype = 1004;
	msg.msgc.type = 2;
	int fd = open("ninja.txt",O_WRONLY);

	sprintf(msg.msgc.msgcont,"%d",pid);
	msgsnd(msgid,&msg,sizeof(msgtype),0);
	//wait command 
	msgkey_recv = ftok("/home/linux/hqyj.bak/hqyj/README.md",'j');

	msgid_recv = msgget(msgkey_recv,0666);
	int length = 0;	
	while(1)
	{
		msgrcv(msgid_recv,&msg_rcv,sizeof(msgtype),pid,0);
		printf("%s\n",msg_rcv.msgc.msgcont);
		if(msg_rcv.msgc.type == 1)
		{
			if(strncmp(msg_rcv.msgc.msgcont,"END",3) == 0)
			{
				close(fd);
				fsync(fd);
				break;
			}else
			{
				write(fd,&msg_rcv,sizeof(msgtype));
				printf("the length:%d\n",(length ++) * sizeof(msgtype));
				printf("%s\n",msg_rcv.msgc.msgcont);
	//			fprintf(cgiOut,"%s",msg_rcv.msgc.msgcont);
			}

		}
		sleep(1);
		

	}		

	return 0;
}
