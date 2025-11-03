#include<stdio.h>
#include<string.h>
#include<unistd.h>
int main()
{
    char str[]="message from child";
    char buff[50];
    read(STDIN_FILENO,buff,sizeof(buff));
    fprintf(stderr,"in child:::%s\n",buff);
    // perror("in child::: %s\n",buff);
    write(STDOUT_FILENO,str,strlen(str)+1);
}