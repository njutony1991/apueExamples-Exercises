#include "apue.h"
#include <sys/resource.h>
#include <fcntl.h>

#define BUFFSIZE 100

Sigfunc *signal_intr(int signo,Sigfunc *func){
	struct sigaction act,oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
	#endif
	if(sigaction(signo,&act,&oact)<0)
		return (SIG_ERR);
	return oact.sa_handler;
}


void sig_xfsz(int signo){
	fprintf(stdout,"Caught SIZEXFSZ\n");
}

int main(){
	ssize_t n,nwritten;
	int m;
	char buf[BUFFSIZE+5];
	struct rlimit rlim;
	rlim.rlim_cur = 1024;
	rlim.rlim_max = RLIM_INFINITY;

	if((m=setrlimit(RLIMIT_FSIZE,&rlim))!=0)
		err_sys("setrlimit error");

	int f1 = open("tocopy",O_RDONLY);
	int f2 = open("tocopy.copy",O_RDWR|O_TRUNC);

	signal_intr(SIGXFSZ,sig_xfsz);

	while((n=read(f1,buf,BUFFSIZE))>0)
		if((nwritten=write(f2,buf,n))!= n)
			err_sys("write error,write %d bytes",nwritten);

	if(n<0)
		err_sys("read error");

	exit(0);
}