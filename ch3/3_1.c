#include "apue.h"

int main(void){
	if(lseek(STDIN_FILENO,0,SEEK_CUR)==-1)
		printf("cann't seek\n");
	else
		printf("can seek\n");
	exit(0);
}