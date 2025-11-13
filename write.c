#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
int main(){
    int fd;
    char WrBuffer[] = "Hi from write.c\n";
    char RdBuffer[100];

    fd = open("desd", O_WRONLY);
    write(fd,WrBuffer,strlen(WrBuffer));
    close(fd);

    fd = open("desd", O_RDONLY);
    read(fd,RdBuffer,sizeof(RdBuffer));
    printf("%s",RdBuffer);
    close(fd);
    
    return 0;
}