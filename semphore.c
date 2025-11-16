#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t sem;
int count;

void* increment(void *args)
{
    while(count != 10)
    {
        sem_wait(&sem);
        count++;
        printf("count_increment: %d\n",count);
        sem_post(&sem);
    }
}

void* decrement(void *args)
{
    while(count > 0)
    {
        sem_wait(&sem);
        count--;
        printf("count_decrement: %d\n",count);
        sem_post(&sem);
    }
}

int main(){
    sem_init(&sem,0,1);

    pthread_t thread1, thread2;

    pthread_attr_t attr1, attr2;
    pthread_attr_init(&attr1);
    pthread_attr_init(&attr2);

    // Set SCHED_RR for both
    pthread_attr_setschedpolicy(&attr1, SCHED_RR);
    pthread_attr_setschedpolicy(&attr2, SCHED_RR);

    // Explicitly use given scheduling
    pthread_attr_setinheritsched(&attr1, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setinheritsched(&attr2, PTHREAD_EXPLICIT_SCHED);

    // Set priorities
    struct sched_param param1, param2;
    param1.sched_priority = 10;   // lower
    param2.sched_priority = 30;   // higher

    pthread_attr_setschedparam(&attr1, &param1);
    pthread_attr_setschedparam(&attr2, &param2);

    // Create threads
    pthread_create(&thread1, &attr1, increment, NULL);
    pthread_create(&thread2, &attr2, decrement, NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

    pthread_attr_destroy(&attr1);
    pthread_attr_destroy(&attr2);

    sem_destroy(&sem);
}
