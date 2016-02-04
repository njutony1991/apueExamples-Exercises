#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
char string[] = "hello";
int main(int argc,char **argv){
	int fd;
	char buf[256];

	mknod("fifo",010777,0);
	if(argc==2)
		fd = open("fifo",O_WRONLY);
	else
		fd = open("fifo",O_RDONLY);
	for(;;)
		if(argc==2){
			write(fd,string,6);
			printf("write to pipe\n");
		}
		else{
			read(fd,buf,6);
			printf("read from pipe %s\n",buf);
		}
	exit(0);
}