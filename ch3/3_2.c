#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void){
	int fd;
	if((fd = creat("file.hole",FILE_MODE))<0)
		err_sys("create_error");

	if(write(fd,buf1,10) !=10)
		err_sys("buf1 write error");
	printf("now offset: %ld\n",lseek(fd,0,SEEK_CUR));

	if(lseek(fd,16384,SEEK_SET)==-1)
		err_sys("lseek_error");
	printf("now offset: %ld\n",lseek(fd,0,SEEK_CUR));

	if(write(fd,buf2,10) != 10)
		err_sys("buf2 write error");
	printf("now offset: %ld\n",lseek(fd,0,SEEK_CUR));
	exit(0);
}