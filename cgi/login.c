#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cgic.h"


int cgiMain(int argc, const char *argv[])
{
	char userbuf[10],pwbuf[10];
	
	cgiFormString("username",userbuf,10);
	cgiFormString("userpass",pwbuf,10);
	
	if((strncmp("ninja",userbuf,5) == 0) && (strncmp("1234",pwbuf,4) == 0))
	t
		cgiHeaderContentType("text/html");
		fprintf(cgiOut,"<html><head>\n");
		fprintf(cgiOut,"<title>ninja warehouse</title></head>\n");
		fprintf(cgiOut,"<body>");
		fprintf(cgiOut,"<H1>%s</H1>","login succesfully,skipping...");
		fprintf(cgiOut,"<meta http-equiv=\"refresh\" content=\"0;url=../all.html\" />");
	}
	else{
			cgiHeaderContentType("text/html");
			fprintf(cgiOut, "<HTML>\n");
			fprintf(cgiOut, "<HTML><HEAD>\n");
			fprintf(cgiOut, "<TITLE>logining</TITLE></HEAD>\n");
			fprintf(cgiOut, "<BODY>");
			fprintf(cgiOut, "<script>alert('password or id error!');</script>");		
			fprintf(cgiOut, "<meta http-equiv=\"refresh\" content=\"0;url=../index.html\">");
	}
	
	return 0;
}
