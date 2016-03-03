#include "apue.h"

static volatile sig_atomic_t sigflag;
static sigset_t newmask,oldmask,zeromask;

void pr_mask(const char *str){
	sigset_t sigset;
	int errno_save;

	errno_save = errno;
	if(sigprocmask(0,NULL,&sigset)<0){
		err_ret("sigprocmask error");
	}else{
		printf("%s",str);
		if(sigismember(&sigset,SIGINT))
			printf(" SIGINT");
		if(sigismember(&sigset,SIGQUIT))
			printf(" SIGQUIT");
		if(sigismember(&sigset,SIGUSR1))
			printf(" SIGUSR1");
		if(sigismember(&sigset,SIGALRM))
			printf(" SIGALRM");

		printf("\n");
	}
	errno = errno_save;
}

Sigfunc *signal(int signo,Sigfunc *func){
	struct sigaction act,oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if(signo==SIGALRM){
	#ifdef SA_INTERRUPT
		act.sa_flags |= SA_INTERRUPT;
	#endif
	}else{
		act.sa_flags |= SA_RESTART; 
	}
	if(sigaction(signo,&act,&oact)<0)
		return (SIG_ERR);
	return oact.sa_handler;
}

static void sig_usr(int signo){
	sigflag = 1;
}

void TELL_WAIT(void){
	if(signal(SIGUSR1,sig_usr)==SIG_ERR)
		err_sys("signal(SIGUSR1) error");
	if(signal(SIGUSR2,sig_usr)==SIG_ERR)
		err_sys("signal(SIGUSR2) error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigaddset(&newmask,SIGUSR1);
	sigaddset(&newmask,SIGUSR2);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask)<0)
		err_sys("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid){
	kill(pid,SIGUSR2);
}

void WAIT_PARENT(void){
	while(sigflag==0)
		sigsuspend(&zeromask);
	sigflag=0;

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
		err_sys("SIG_SETMASK error");
}

void TELL_CHILD(pid_t pid){
	kill(pid,SIGUSR1);
}

void WAIT_CHILD(void){
	while(sigflag==0)
		sigsuspend(&zeromask);
	sigflag=0;

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL)<0)
		err_sys("SIG_SETMASK error");
}

void sig_chld(int signo){
	int status;
	pid_t pid=wait(&status);
	printf("Got SIGCHLD for %d\n",pid);
	printf("Signalled? %d\n",WIFSIGNALED(status));
}

void init_counter(){
	FILE *file;
	file=fopen("counter.txt","w+");
	fprintf(file,"%d",0);
	fclose(file);
}

void inc_counter(char *who){
	int counter;
	FILE *f;

	f=fopen("counter.txt","r");
	fscanf(f,"%d",&counter);
	fclose(f);

	counter++;

	f=fopen("counter.txt","w");
	printf("%s:increasing counter to %d\n",who,counter);
	fprintf(f,"%d",counter);
	fclose(f);
}

int main(void){
	pid_t pid;

	signal(SIGCHLD,sig_chld);
	init_counter();

	TELL_WAIT();
	pid = fork();
	if(pid<0){
		err_sys("fork error");
	}else if(pid==0){
		while(1){
			WAIT_PARENT();
			inc_counter("child");
			TELL_PARENT(getppid());
		}
	}else{
		while(1){
			inc_counter("parent");
			sleep(1);
			TELL_CHILD(pid);
			WAIT_CHILD();
		}
	}
	return 0;
}