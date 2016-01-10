#include "apue.h"
#include <fcntl.h>

int my_dup(int olddup,int newdup);

int main(int argc,char **argv){
	int newdup = 3;
	const char *filename = "newfile.txt";
	int fd = open(filename,O_RDWR|O_CREAT);
	int newfd = my_dup(fd,newdup);
	if(write(newfd,"Test new fd",strlen("Test new fd"))<0){
		printf("Use new fd write file failed\n");
		exit(2);
	}else{
		printf("Write successfully\n");
	}
	exit(0);
}

int my_dup(int olddup,int newdup){
	int tempdup;
	int icount = 0;
	int filedes[newdup+1];
	if((tempdup=dup(olddup))==-1){
		printf("the file desp is invalid\n");
		exit(1);
	}else{
		close(tempdup);
	}

	if(newdup==olddup)
		return olddup;
	close(newdup);
	for(icount = 0;icount<newdup+1;icount++){
		filedes[icount] = 0;
		tempdup = dup(olddup);
		if(tempdup<0)
		{
			return -1;
		}else{
			if(tempdup==newdup)
				break;
			else
				filedes[tempdup] = 1;
		}
	}
	for(icount = 0;icount<newdup+1;icount++)
		if(filedes[icount]==1)
			close(icount);
	return tempdup;
}