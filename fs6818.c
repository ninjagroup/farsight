#include "fs6818.h"

void init_led()
{
	//init red 
	LED_RED &= ~(3<<24);
	LED_RED_ENB |= (1<<28);
	LED_RED_OUT &= ~(1<<28);
	//init green 
	LED_GREEN &= ~(3<<26);
	LED_GREEN_ENB |= (1<<13);
	LED_GREEN_OUT &= ~(1<<13);
	//init blue 
	LED_BLUE &= ~(3<<24);
	LED_BLUE |= (2<<24);
	LED_BLUE_ENB |= (1<<12);
	LED_BLUE_OUT &= ~(1<<12);
}

void open_led(int color)
{
	/*
	if(color == 1)
	{
		LED_RED_OUT |= (1<<28);
	}
	else if(color == 2)
	{
		LED_GREEN_OUT |= (1<<13);
	}
	else{
		LED_BLUE_OUT |= (1<<12);
	}
	*/
	printf("alarm!!!!\n");
}

void close_led()
{
	/*
	LED_RED_OUT &= ~(1<<28);
	LED_GREEN_OUT &= ~(1<<13);
	LED_BLUE_OUT &= ~(1<12);
	*/
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
