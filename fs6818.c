#include "fs6818.h"


void open_led(int color)
{
	if(color == 1)
	{

	}
	else if(color == 2)
	{

	}
	else{

	}
}

void close_led()
{

}

void open_pwm()
{

}

void close_pwm()
{

}

void insertshm(int shmkey,msgtype msg)
{
	int shmid;
	if((shmid = shmget(shmkey,sizeof(msgtype),IPC_CREAT|0777)) < 0)
	{
		perror("fail to insertshm!");
	}
	
	msgtype *msg_shm;
	
	msg_shm = (msgtype *)shmat(shmid,NULL,0);
	*msg_shm = msg;

	shmdt(msg_shm);
}
