#ifndef __FS6818_H__

#define __FS6818_H__
#include "header.h"


//int 1 red 2 blue 3 green
void open_led(int color);
void close_led();

void open_pwm();
void close_pwm();

void insertshm();

#endif 
