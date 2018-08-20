#ifndef __FS6818_H__

#define __FS6818_H__
#include "header.h"

#define LED_RED (*(volatile *)0x00) 
#define LED_BLUE (*(volatile *)0x00) 
#define LED_GREEN (*(volatile *)0x00)

#define LED_RED_ENB (*(volatile *)0x00)
#define LED_GREEN_ENB (*(volatile *)0x00)
#define LED_BLUE_ENB (*(volatile *)0x00)

#define LED_RED_OUT (*(volatile *)0x00)
#define LED_GREEN_OUT (*(volatile *)0x00)
#define LED_BLUE_OUT (*(volatile *)0x00)



//int 1 red 2 blue 3 green
void open_led(int color);
void close_led();

void open_pwm();
void close_pwm();

void insertshm(int,msgtype);

#endif 
