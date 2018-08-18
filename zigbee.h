#ifndef __ZIGBEE_H__

#define __ZIGBEE_H__

#include "header.h"

void init_zigbee();
//read temperature
float read_temperature();
//read illusion 
float read_illusion();
//read humidity 
float read_humidity();
//read x y z 
int read_x();
int read_y();
int read_z();
//control according to msg 
void zigbee_set(msgtype);
//fan 
void setM0Fan(int level);
//pwm 
void close_m0_pwm();
void open_m0_pwm();
//led 
void close_m0_led();
void open_m0_led();

#endif

