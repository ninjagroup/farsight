#include "hqyj.h"

void do_init()
{
	
	init_zigbee();
	env_limit = env_limit_select();
	msg_send = ftok("./README.md",'n');
	msg_recv = ftok("./README.md",'j');
	shmkey = ftok("./README.md",'a');

}


void * m0_func(void * args)
{
	float temperature = 0;
	float illusion = 0;
	float humidity = 0;
	char time_str[20];
	msgtype msg;
	msg.type = 4;
	msg.msgtype = 1001;
	int t_flag = 0;
	int i_flag = 0;
	int h_flag = 0;
	while(1)
	{
		//read 
		
		temperature = read_temperature();
		illusion = read_illusion();
		humidity = read_humidity();

		//alam exceed limit 
		if((t_flag = (temperature > env_limit.temperatureMAX || temperature < env_limit.temperatureMIN)) || \
				(i_flag = (illusion > env_limit.illusionMAX || illusion < env_limit.illusionMIN)) || \
				(h_flag = (humidity > env_limit.humidityMAX || humidity < env_limit.humidityMIN)))
		{
			pthread_mutex_lock(&led_mutex);
			if(t_flag)
				ledtype = 1;
			else if(i_flag)
				ledtype = 2;
			else 
				ledtype = 3;
			led_flag = 1;
			pthread_cond_signal(&pthread_led_cond);
			pthread_mutex_unlock(&led_mutex);
			pthread_mutex_lock(&pwm_mutex);
			pwm_flag = 1;
			pthread_cond_signal(&pthread_pwm_cond);
			pthread_mutex_unlock(&pwm_mutex);
		}
		//make msg  temperature#illusion#humidity#changetime 
		getTime(time_str);
		sprintf(msg.msgcont,"%f#%f#%f#%s",temperature,illusion,humidity,time_str);
		printf("the msg:%s\n",msg.msgcont);
		//normal insert into link if link size > 10 insert into sqlite and shm 
		if(insertLink(msg) > 10)
		{
			//first insertshm
			insertshm();
			pthread_mutex_lock(&sqlite_mutex);
			sqlite_flag = 1;
			pthread_cond_signal(&pthread_sqlite_cond);
			pthread_mutex_unlock(&sqlite_mutex);
		}
		//sleep
		sleep(1);		
	}
	return NULL;
}

void * client_func(void * args)
{
	printf("this is client\n");
	msgtype msg;
	
	while(1)
	{
		if(msgrcv(msg_send,&msg,sizeof(msgtype),0,0) < 0)
		{
			perror("fail to client_func msgrcv!");
		}else{
			switch(msg.type)
			{
				case 'C':
					zigbee_set(msg);
					break;
				case 'E':
					env_set(msg);
					break; 

			}

		}
		printf("client...\n");
		sleep(1);
	}
	return NULL;
}

void * sqlite_func(void * args)
{
	printf("this is sqlite\n");
	while(1)
	{
		pthread_mutex_lock(&sqlite_mutex);
		if(!sqlite_flag)
		{
			pthread_cond_wait(&pthread_sqlite_cond,&sqlite_mutex);
		}

		if(linkCount(&envHeader))
		{
			env_insert(popLink(&envHeader));	
		}else{
			sqlite_flag = 0;
		}

		pthread_mutex_unlock(&sqlite_mutex);

	}
	return NULL;
}

void * led_func(void *args)
{
	float temperature = 0;
	float illusion = 0;
	float  humidity = 0;
	printf("this is led\n");
	while(1)
	{
		temperature = read_temperature();
		illusion = read_illusion();
		humidity = read_humidity();
		pthread_mutex_lock(&led_mutex);
		if(!led_flag)
		{
			pthread_cond_wait(&pthread_led_cond,&led_mutex);
		}
		open_led(ledtype);
		sleep(1);
		close_led();
		if((temperature >= env_limit.temperatureMIN && temperature <= env_limit.temperatureMAX) && \
			(illusion >= env_limit.illusionMIN && illusion <= env_limit.illusionMAX) && \
			(humidity >= env_limit.humidityMIN && humidity <= env_limit.humidityMAX))
		{
			led_flag = 0;
		}
		pthread_mutex_unlock(&led_mutex);

	}

	return NULL;
}

void * pwm_func(void * args)
{
	float temperature = 0;
	float illusion = 0;
	float  humidity = 0;
	printf("this is pwm\n");
	while(1){
		temperature = read_temperature();
		illusion = read_illusion();
		humidity = read_humidity();
		pthread_mutex_lock(&pwm_mutex);
		if(!pwm_flag)
		{
			pthread_cond_wait(&pthread_sqlite_cond,&sqlite_mutex);
		}

		open_pwm();
		sleep(1);
		close_pwm();
		if((temperature >= env_limit.temperatureMIN && temperature <= env_limit.temperatureMAX) && \
			(illusion >= env_limit.illusionMIN && illusion <= env_limit.illusionMAX) && \
			(humidity >= env_limit.humidityMIN && humidity <= env_limit.humidityMAX))
		{
			pwm_flag = 0;
		}

		
		pthread_mutex_unlock(&pwm_mutex);


	}
	return NULL;
}

void * fan_func(void * args)
{
	printf("this is fan\n");
	return NULL; 
}

