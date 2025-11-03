#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
 #include <sys/wait.h>
int main(){
    
    int fd;
    int FD[2];
    int result = pipe(FD);
    printf("pipe = %d\n",result);

    char bufferW[] = "Child Process";
    char bufferR[20];
    pid_t ret = fork();
    if(ret == 0)
    {
        // Child Process
        fd = open("pipe.txt",O_CREAT | O_RDWR, 0644);
        write(fd, bufferW, strlen(bufferW));
        close(fd);
        close(FD[0]);
        write(FD[1],bufferW,sizeof(bufferW));
        close(FD[1]);
        execl("/usr/bin/write", "write", "/home/desd-user28/Desktop/Cdac/Sravan/pipe.txt",NULL);
        //wait(NULL);
    }
   else
    {
        // Parent Process 
        close(FD[1]);
        read(FD[0], bufferR, sizeof(bufferR));
        printf("From child: %s",bufferR);
        close(FD[0]);
        //wait(NULL);
    }
}