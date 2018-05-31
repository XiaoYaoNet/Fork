#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>

int gb=123;
char buf[]="hello\n";

void err_sys(char *str);

int main(void)
{
    int fd,i;
    pid_t pid;
    
    fd=open("./temp",O_CREAT|O_RDWR);
    if(fd<0)
    {
       return -1;
    }
    for(i=0;i<1000;i++)
    {
       if(write(fd,buf,sizeof(buf)-1)!=sizeof(buf)-1)
           err_sys("write error");
    }

    pid=fork();
    if(pid<0)
       err_sys("fork error");
    else if(pid==0)
       sleep(10);
    sleep(5);
    kill(pid,SIGTERM);
    exit(0);
}

void err_sys(char *str)
{
     printf("%s,%s\n",str,strerror(errno));
}
