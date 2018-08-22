#include "zigbee.h"

void init_zigbee(void)
{


}

float read_temperature()
{
	return 0;
}

float read_illusion()
{
	return 0;
}

float read_humidity()
{
	return 0;
}

void setM0Fan(int level)
{

}

void open_m0_pwm()
{

}

void close_m0_pwm()
{

}

void open_m0_led()
{

}

void close_m0_led()
{

}

void zigbee_set(msgtype msg)
{
	//msgcont level
	if(msg.msgc.type == 1)
	{
		// 0 close 1-3 level 
		setM0Fan(msg.msgc.msgcont[0] - 48);
	}else if(msg.msgc.type == 2)
	{
		//cont 0 close 1 open 
		if((msg.msgc.msgcont[0] - 48) == 0)
		{
			close_m0_pwm();
		}
		else 
		{
			open_m0_pwm();
		}
	}else if(msg.msgc.type == 3)
	{
		//0 close 1 open 
		if((msg.msgc.msgcont[0] - 48) == 0)
		{
			close_m0_led();
		}
		else 
		{
			open_m0_led();
		}
	}
}
