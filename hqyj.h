#ifndef __HQYJ__H__

#define __HQYJ__H__

#include "goods_info.h"
#include "env_info.h"
#include "zigbee.h"
#include "envLink.h"
#include "fs6818.h"
#include "tools.h"

//pthread_m0 pthread_client
pthread_t pthread_m0, pthread_client;
//pthread_led,pthread_pwm,pthread_fan
pthread_t pthread_led,pthread_pwm,pthread_fan;
//pthread_sqlite 
pthread_t pthread_sqlite;
//pthread_cont led,pwm,fan 
pthread_cond_t pthread_led_cond,pthread_pwm_cond,pthread_fan_cond;
//pthread_cont sqlite 
pthread_cond_t pthread_sqlite_cond;
//mutex  led,pwm,fan 
pthread_mutex_t led_mutex,pwm_mutex,fan_mutex;
//mutex sqlite 
pthread_mutex_t sqlite_mutex;
//flags led,pwm,fan 
int led_flag,pwm_flag,fan_flag;
//flags sqlite 
int sqlite_flag;
//msgid ,shmid
int msgid_send,msgid_recv,shmid;
//env_info header 
envLink envHeader;
//ftok 
key_t msg_send,msg_recv,shmkey;
//max min 
env_info_limit env_limit;
//ledtype 
int ledtype;
//init peripheral
void do_init(void);
//pthread 
void *m0_func(void *args);
void *client_func(void *args);
void *sqlite_func(void *args);
void *led_func(void *args);
void *pwm_func(void *args);
void *fan_func(void *args);
#endif

