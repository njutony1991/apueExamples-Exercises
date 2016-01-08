#include "apue.h"
#include <error.h>

int main(int argc,char **argv){
	fprintf(stderr, "EACCES: %s\n",strerror(EACCES));
	errno = ENOENT;
	perror(argv[0]);
	exit(0);
}