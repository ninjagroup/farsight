#ifndef __FS6818_H__

#define __FS6818_H__
#include "header.h"

#define LED_RED  
#define LED_BLUE 
#define LED_GREEN 

#define LED_RED_ENB
#define LED_GREEN_ENB
#define LED_BLUE_ENB 

#define LED_RED_OUT 
#define LED_GREEN_OUT 
#define LED_BLUE_OUT 


int initFlag = 0;

//int 1 red 2 blue 3 green
void open_led(int color);
void close_led();

void open_pwm();
void close_pwm();

void insertshm(int,msgtype);

#endif 
