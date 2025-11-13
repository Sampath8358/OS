#include <stdio.h>
#include <pthread.h>
#include <unistd.h>  

int count = 0;
pthread_mutex_t lock;

void *funInc(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        count++;
        printf("Ine_count = %d\n",count);
        pthread_mutex_unlock(&lock);
    }
}

void *funDec(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&lock);
        count--;
        printf("Dec_count = %d\n",count);
        pthread_mutex_unlock(&lock);
    }
}

int main(){
    pthread_mutex_init(&lock,NULL);

    pthread_t t1, t2;

    pthread_create(&t1,NULL,funInc,NULL);
    pthread_create(&t2,NULL,funDec,NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);

    pthread_mutex_destroy(&lock);

    printf("Final_value = %d\n",count);
    return 0;
}