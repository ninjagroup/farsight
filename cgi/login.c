#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cgic.h"

int main(int argc, const char *argv[])
{
	char userbuf[10],pwbuf[10];

	cgiFormString("username",userbuf,10);
	cgiFormString("userpass",pwbuf,10);
	printf("the username:%s,userpass:%s\n",userbuf,pwbuf);
	return 0;
}
