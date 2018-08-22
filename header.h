#ifndef __HEADER_H__

#define __HEADER_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <sqlite3.h>






#define MSGSIZE 150
typedef enum{
	false = 0,
	true
}bool;

//msgtype read 
/*
 *L login 1000
 *E env limit msgtype  1001 1 insert 2 select 3 delete  4 insert
 *C control msgtype 1002 1 fan 2 pwm 3 led       
 *S storage msgtype 1003 read 2 write 
 *E env msgtype 1004 1. insert 2. select 
 *R realtime data this is direct read by cgi
 * 
 *
 *
 */
typedef struct msgc{
	char type;
	char msgcont[MSGSIZE];
}msgc;
typedef struct msgtype{
	long msgtype;
	msgc msgc;
}msgtype;




#endif 
