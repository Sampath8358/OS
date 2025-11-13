#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    int fd;
    char WrBuffer[] = "Hi from read.c\n";
    char RdBuffer[100];

    mkfifo("desd", 0666);

    fd = open("desd", O_RDONLY);
    read(fd,RdBuffer,sizeof(RdBuffer));
    printf("%s",RdBuffer);
    close(fd);
    
    fd = open("desd", O_WRONLY);
    write(fd,WrBuffer,strlen(WrBuffer));
    close(fd);
    return 0;
}