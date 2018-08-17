#ifndef __LOGIN_H__

#define __LOGIN_H__


#define ID_PWD_SIZE 20

#include "header.h"

typedef struct login_str{
	char user_id[ID_PWD_SIZE];
	char user_pwd[ID_PWD_SIZE];
} login_str;



//user login  0 success -1 failed 
int do_login(login_str login_str);



#endif 
