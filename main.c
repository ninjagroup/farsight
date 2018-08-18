#include "hqyj.h"

int main(int argc, const char *argv[])
{

	do_init();
	//init msggid,shmid
	if((msgid_send = msgget(msg_send,IPC_CREAT|IPC_EXCL|0777) < 0))
	{
		if(errno == EEXIST)
		{
			msgid_send = msgget(msg_send,IPC_CREAT);
		}else{
			perror("fail to msgget_send!");
			return -1;
		}
	}

	if((msgid_recv = msgget(msg_recv,IPC_CREAT|IPC_EXCL|0777) < 0))
	{
		if(errno == EEXIST)
		{
			msgid_recv = msgget(msg_recv,IPC_CREAT);
		}else{ 
			perror("fail to msgget_recv!");
			return -1;
		}
	}

	if((shmid = shmget(shmkey,sizeof(msgtype) * 10,IPC_CREAT|IPC_EXCL|0777) < 0))
	{
		if(errno = EEXIST)
		{
			shmid = shmget(shmkey,sizeof(msgtype) * 10,IPC_CREAT);
		}else{
			perror("fail to shmget!");
			return -1;
		}
	}

	//init mutex 
	if(pthread_mutex_init(&led_mutex,NULL) < 0)
	{
		perror("fail to phtread_mutex_init led!");
		return -1;
	}

	if(pthread_mutex_init(&pwm_mutex,NULL) < 0)
	{
		perror("fail to pthread_mutex_init pwm!");
		return -1;
	}

	if(pthread_mutex_init(&fan_mutex,NULL) < 0)
	{
		perror("fail to pthread_mutex_init fan!");
		return -1;
	}

	if(pthread_mutex_init(&sqlite_mutex,NULL) < 0)
	{
		perror("fail to pthread_mutex_init sqlite!");
		return -1;
	}
	//init flags 
	led_flag = 0;
	pwm_flag = 0;
	fan_flag = 0;
	sqlite_flag = 0;
	//init pthread_cont 
	if(pthread_cond_init(&pthread_led_cond,NULL) < 0)
	{
		perror("fail to pthread_cond_init led!");
		return -1;
	}

	if(pthread_cond_init(&pthread_pwm_cond,NULL) < 0)
	{
		perror("fail to pthread_cond_init pwm!");
		return -1;
	}

	if(pthread_cond_init(&pthread_fan_cond,NULL) < 0)
	{
		perror("fail to pthread_cond_init fan!");
		return -1;
	}

	if(pthread_cond_init(&pthread_sqlite_cond,NULL) < 0)
	{
		perror("fail to pthread_cond_init sqlite!");
		return -1;
	}
	//init link 
	initLink(&envHeader);
	//create thread 
	if(pthread_create(&pthread_m0,NULL,m0_func,NULL) < 0)
	{
		perror("fail to pthread create m0!");
		return -1;
	}

	if(pthread_create(&pthread_client,NULL,client_func,NULL) < 0)
	{
		perror("fail to pthread_create client!");
		return -1;
	}

	if(pthread_create(&pthread_sqlite,NULL,sqlite_func,NULL) < 0)
	{
		perror("fail to pthread_create sqlite!");
		return -1;
	}

	if(pthread_create(&pthread_led,NULL,led_func,NULL) < 0)
	{
		perror("fail to pthread_create led!");
		return -1;
	}

	if(pthread_create(&pthread_pwm,NULL,pwm_func,NULL) < 0)
	{
		perror("fail to pthread_create pwm!");
		return -1;
	}

	if(pthread_create(&pthread_fan,NULL,fan_func,NULL) < 0)
	{
		perror("fail to pthread_create fan!");
		return -1;
	}

	//pthread_join 
	pthread_join(pthread_m0,NULL);
	pthread_join(pthread_client,NULL);
	pthread_join(pthread_pwm,NULL);
	pthread_join(pthread_led,NULL);
	pthread_join(pthread_fan,NULL);
	


	return 0;
}
