#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64

int main(){
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char *token; 
    pid_t pid;
    while(1)
    {
        printf("My Shell>");
        //fflush(stdout);

        if(fgets(input, sizeof(input), stdin) == NULL)
        {
           printf("\n");
           break;
        }
        printf("input = %s\n",input);

        input[strcspn(input, "\n")] = 0;
        //printf("index = %d\n",strcspn(input, "\n"));

        if(strcmp(input, "exit") == 0)
            break;
        
        int i = 0;
        token = strtok(input, " ");
        while(token != NULL)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        if(args[0] == NULL)
            continue;
        
        pid = fork();
        if(pid < 0)
        {
            perror("fork failed");
            continue;
        }
        else if (pid == 0)
        {
            execvp(args[0],args);
            perror("exec failed");
            exit(1);
        }
        else
        {
            wait (NULL);
        }
    }
    printf("Existing shell.\n");
    return 0;
}