#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
    char str[]="message from parent";
    char buff[50];
    system("gcc child.c -o child");
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    pipe(fd2);
    pid_t ret;
    ret=fork();
    if(ret==0)
    {
        dup2(fd1[0],STDIN_FILENO);
        dup2(fd2[1],STDOUT_FILENO);
        close(fd1[1]);
        close(fd2[0]);
        execl("./child","child",NULL);
    }
    else{
        close(fd1[0]);
        close(fd2[1]);
        write(fd1[1],str,strlen(str)+1);
        read(fd2[0],buff,sizeof(buff));
        printf("in parent:::%s\n",buff);
        close(fd1[1]);
        close(fd2[0]);
    }
}