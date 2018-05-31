#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

int gb=123;
char buf[]="hello,to stdout\n";

void err_sys(char *str);

int main(void)
{
     int aut;
     pid_t pid;
     
     aut=102;
     if(write(STDOUT_FILENO,buf,sizeof(buf)-1)!=sizeof(buf)-1)
     {
          err_sys("write error");
     }
     printf("before call fork\n");

     pid=vfork();
     if(pid<0)
     {
         err_sys("fork error");
     }else if(pid==0){
         gb--;
         aut++;
     }
     printf("pid=%d,gb=%d,aut=%d\n",getpid(),gb,aut);
     exit(0);
}

void err_sys(char *str)
{
     printf("%s,%s\n",str,strerror(errno));
}
