#include <stdio.h>
#include <signal.h>
#include <string.h>

#ifndef SIG2STR_MAX
#define SIG2STR_MAX 500
#endif

int sig2str(int signo,char *str){
	if(signo<=0||signo>=NSIG)
		return -1;
	strcpy(str,sys_siglist[signo]);
	return 0;
}

int main(void){
	char res[SIG2STR_MAX];
	sig2str(SIGABRT,res);
	printf("%s\n",res);
	return 0;
}