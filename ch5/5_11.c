#include "apue.h"

void pr_stdio(const char *, FILE *);
int is_unbuffered(FILE *);
int is_linebufferd(FILE *);
int buffer_size(FILE *);

int main(void){
	FILE *fp;
	fputs("enter any character\n",stdout);
	if(getchar()==EOF)
		err_sys("getchar error");
	fputs("one line to standard error\n",stderr);

	pr_stdio("stdin",stdin);
	pr_stdio("stdout",stdout);
	pr_stdio("stderr",stderr);

	if((fp = fopen("/etc/passwd","r"))==NULL)
		err_sys("fopen error");
	if(getc(fp)==EOF)
		err_sys("getc error");
	pr_stdio("/etc/passwd",fp);

	exit(0);
}