#ifndef __ENV_LINK_H__

#define __ENV_LINK_H__

typedef struct env_info{
	float temperature;
	float humidity;
	float illumination;
	int x;
	int y;
	int z;
	char insert_time[20];
} env_info; 


typedef struct envLink{
	env_info *next;
	int top;
}envLink; 

#endif 
