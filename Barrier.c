#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define THREAD_COUNT 4

typedef struct {
    int a;
    int b;
    int ids[4];
}threadArgs;

pthread_barrier_t barrier;

void *fun(void *arg)
{
    threadArgs *ptr = (threadArgs*)arg;
    printf("thread %d is running...\n",ptr->ids);
    pthread_barrier_wait(&barrier);
    int *result = malloc(sizeof(int));
    *result = ptr->a + ptr->b;
    printf("result = %d",*result);
    printf("thread %d is completed...\n",id);

    return *result;
}

int main(){

    pthread_t thread[THREAD_COUNT];
    //int ids[THREAD_COUNT];
    threadArgs args;
    args.a = 10;
    args.b = 7;

    pthread_barrier_init(&barrier,NULL,THREAD_COUNT);

    for(int i = 0; i < THREAD_COUNT; i++)
    {
        args.ids[i] = i + 1;
        pthread_create(&thread[i],NULL,fun,&args);
        
    }

    for(int i = 0; i < THREAD_COUNT; i++)
    {
        int *ret_value;
        pthread_join(thread[i],&ret_value);
    }

    pthread_barrier_destroy(&barrier);
    return 0;

}