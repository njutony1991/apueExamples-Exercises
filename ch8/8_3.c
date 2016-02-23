#include "apue.h"

int globvar = 6;

int main(void){
	int var;
	pid_t pid;
	int i;
	char buf[50];
	var = 88;
	printf("before vfork\n");
	if((pid=vfork())<0){
		err_sys("vfork error");
	}else if(pid==0){
		globvar++;
		var++;
		fclose(stdout);
		_exit(0);
	}

	i=printf("pid = %ld, glob = %d, var = %d\n",(long)getpid(),globvar,var);
	sprintf(buf,"%d\n",i);
	write(STDOUT_FILENO,buf,strlen(buf));
	exit(0);
}