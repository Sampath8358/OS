#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2];
    char message[] = "Hello from parent";
    char buffer[100];
    int df[2];
    char message1[] = "Hello from child";
    char buffer1[100];
    
    pipe(fd); 
    printf("%d\n", fd[0]);
    printf("%d\n", fd[1]);
    pipe(df);
     printf("%d\n", df[0]);
    printf("%d\n", df[1]);
    int ret = fork();
    if (ret == 0) {
        //child process
        close(fd[1]);
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);

        close(df[0]); 
        write(df[1], message1, strlen(message1) + 1);
        close(df[1]);
    } else {//parent
        close(fd[0]); 
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);

        close(df[1]);
        read(df[0], buffer1, sizeof(buffer1));
        printf("parent received: %s\n", buffer1);
        close(df[0]);
    }
    return 0;
}
