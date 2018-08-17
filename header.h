#ifndef __HEADER_H__

#define __HEADER_H__

#define MSGSIZE 100
typedef enum{
	false = 0,
	true
}bool;

//msgtype read 
/*
 *L login 
 *E env msgtype 1 select 2 update 3 delete 
 *C control msgtype 1 fan 2 pwm 3 led       
 *S storage msgtype 1 read 2 write 
 *
 */
typedef struct msgtype{
	char type; 
	int msgtype;
	char msgcont[MSGSIZE];
}msgtype;




#endif 
