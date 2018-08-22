#include "hqyj.h"

void do_init()
{
	
	init_zigbee();
	//init databse 
	env_init(&db);
	env_limit = env_limit_select(db);
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
	msg.msgc.type = 4;
	msg.msgtype = 1001;
	int t_flag = 0;
	int i_flag = 0;
	int h_flag = 0;
	//make msg  temperature#illusion#humidity#changetime 
	while(1)
	{


		//read 
		/*
		temperature = read_temperature();
		illusion = read_illusion();
		humidity = read_humidity();
		*/
		temperature = 20;
		illusion = 20;
		humidity = 20;
		getTime(time_str);
		sprintf(msg.msgc.msgcont,"%f#%f#%f#%s#",temperature,illusion,humidity,time_str);
		//normal insert into link if link size > 10 insert into sqlite and shm 
		if(insertLink(&envHeader,msg) > 9)
		{
			//first insertshm
			insertshm(shmkey,msg);
			pthread_mutex_lock(&sqlite_mutex);
			sqlite_flag = 1;
			pthread_cond_signal(&pthread_sqlite_cond);
			pthread_mutex_unlock(&sqlite_mutex);
		}
		
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
		if(msgrcv(msgid_send,&msg,sizeof(msgtype),0,0) < 0)
		{
			perror("fail to client_func msgrcv!");
		}else{
			switch(msg.msgtype)
			{
				case 1002:
					zigbee_set(msg);
					break;
				case 1001:
					env_set(db,msg,msg_recv);
					break;
				case 1004:
					env_set(db,msg,msg_recv);
					break; 


			}

		}
		printf("client...\n");
	}
	return NULL;
}

void * sqlite_func(void * args)
{
	env_info envInfo;
	while(1)
	{
		pthread_mutex_lock(&sqlite_mutex);
		if(!sqlite_flag)
		{
			pthread_cond_wait(&pthread_sqlite_cond,&sqlite_mutex);
		}

		if(linkCount(&envHeader) > 1)
		{
			popLink(&envHeader,&envInfo);
			env_insert(db,envInfo);	
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
	return NULL; 
}

