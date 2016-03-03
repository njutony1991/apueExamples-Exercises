#include "apue.h"
#include <stdio.h>
#include <signal.h>
char buff[1024*1024*1024];

void sig_alarm(int signo){
	printf("SIGALRM caught\n");
}

int main(){
	FILE *f = fopen("towrite","w+");
	alarm(1);
	fwrite(buff,sizeof(char),1024*1024*1024,f);
	exit(0);
}