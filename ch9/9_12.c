#include "apue.h"
#include <errno.h>
static void sig_up(int signo){
	printf("SIGHUP received,pid = %ld\n",(long)getpid());
}

static void pr_ids(char *name){
	printf("%s: pid= %ld, ppid= %ld,pgrp= %ld,tgrp= %ld\n",name,(long)getpid(),(long)getppid(),(long)getpgrp(),
		(long)tcgetpgrp(STDIN_FILENO));
	fflush(stdout);
}

int main(int argc,char **argv){
	char c;
	pid_t pid;
	pr_ids("parent");
	if((pid=fork())<0){
		err_sys("fork error");
	}else if(pid>0){
		sleep(5);
	}else{
		pr_ids("child");
		signal(SIGHUP, sig_up);
		kill(getpid(),SIGTSTP);
		pr_ids("child");
		if(read(STDIN_FILENO,&c,1)!=1){
			printf("read error %d on controlling TTY\n",errno);
		}
	}
	exit(0);
}