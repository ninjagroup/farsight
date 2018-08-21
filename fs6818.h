#ifndef __FS6818_H__

#define __FS6818_H__
#include "header.h"

#define LED_RED       0xC001A024
#define LED_BLUE      0xC001B020 
#define LED_GREEN     0xC001E020
  
#define LED_RED_ENB   0xC001A004
#define LED_GREEN_ENB 0xC001E004
#define LED_BLUE_ENB  0xC001A004

#define LED_RED_OUT   0xC001A000
#define LED_GREEN_OUT 0xC001E000
#define LED_BLUE_OUT  0xC001B000

#define PWM       0xC001C020
#define PWM_ENB   0xC001C004      

int initFlag = 0;

//int 1 red 2 blue 3 green
void open_led(int color);
void close_led();

void open_pwm();
void close_pwm();

void insertshm(int,msgtype);

#endif 
