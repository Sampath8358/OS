#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int marks;
    int roll;
}threadArgs;

void *fun(void *arg)
{
    threadArgs *ptr = (threadArgs*)arg;
    int *result = malloc(sizeof(int)); // allocate memory
    *result = ptr->marks + ptr->roll;
    printf("Result inside thread = %d\n", *result);
    return result;
}

int main() {
    pthread_t thread;
    threadArgs args = {60, 63};
    pthread_create(&thread, NULL, fun, &args);

    void *ret;
    pthread_join(thread, &ret);
    printf("Result in main = %p\n", (int*)ret);
    free(ret); // free dynamically allocated memory
}

