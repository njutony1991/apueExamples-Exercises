#include "apue.h"

#define BSZ 48

int main(){
	FILE *fp;
	int i=0;
	char buf[BSZ];
	memset(buf,'a',BSZ-2);
	printf("my buf0 %s---%ld----\n",buf,(long)strlen(buf));//add  
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	printf("my buf1 %s---%ld----\n",buf,(long)strlen(buf));//add  
	if((fp = fmemopen(buf,BSZ,"w+"))==NULL)
		err_sys("fmemopen failed");

	printf("initial buffer contents: %s\n",buf);
	fprintf(fp,"hello,world");
	printf("before flush: %s\n",buf);
	for(i=0;i<48;i++)  
    { 	if(buf[i]=='\0')  
    	printf("%c",'#');  
      	else  
   	    printf("%c",buf[i]);  
    }
    printf("\n");  
	fflush(fp);
	for(i=0;i<48;i++)  
    { 	if(buf[i]=='\0')  
    	printf("%c",'#');  
      	else  
   	    printf("%c",buf[i]);  
    }  
    printf("\n");
	printf("after flush: %s\n",buf);
	printf("len of string in buf = %ld\n",(long)strlen(buf));

	memset(buf,'b',BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	printf("my buf2 %s-------\n",buf);//add  
	fprintf(fp,"hello world");
	for(i=0;i<48;i++)  
    { 
    	if(buf[i]=='\0')  
    		printf("%c",'#');  
      	else  
    		printf("%c",buf[i]);  
    }  
    printf("\n");
	fseek(fp,0,SEEK_SET);
	for(i=0;i<48;i++)  
    { 
    	if(buf[i]=='\0')  
    		printf("%c",'#');  
      	else  
    		printf("%c",buf[i]);  
    }  
    printf("\n");
	printf("after fseek: %s\n",buf);
	printf("len of string in buf = %ld\n",(long)strlen(buf));

	memset(buf,'c',BSZ-2);
	buf[BSZ-2] = '\0';
	buf[BSZ-1] = 'X';
	printf("my buf3 %s-------\n",buf);//add 
	fprintf(fp,"hello world");
	for(i=0;i<48;i++)  
    { if(buf[i]=='\0')  
    	printf("%c",'#');  
      else  
    	printf("%c",buf[i]);  
    }
    printf("\n");
	fclose(fp);
	for(i=0;i<48;i++)  
    { if(buf[i]=='\0')  
    	printf("%c",'#');  
      else  
    	printf("%c",buf[i]);  
    }
    printf("\n");
	printf("after fclose: %s\n",buf);
	printf("len of string in buf = %ld\n",(long)strlen(buf));
	return (0);
}